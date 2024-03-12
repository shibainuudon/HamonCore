/**
 *	@file	to.hpp
 *
 *	@brief	ranges::to の定義
 */

#ifndef HAMON_RANGES_UTILITY_TO_HPP
#define HAMON_RANGES_UTILITY_TO_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_to_container) && (__cpp_lib_ranges_to_container >= 202202L)

#define HAMON_USE_STD_RANGES_TO

namespace hamon {
namespace ranges {

using std::ranges::to;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/transform_view.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_size_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/inserter.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_volatile.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

template <typename Container, typename Ref, typename = void>
struct has_push_back
	: public hamon::false_type {};

template <typename Container, typename Ref>
struct has_push_back<Container, Ref,
	hamon::void_t<decltype(hamon::declval<Container&>().push_back(hamon::declval<Ref>()))>>
	: public hamon::true_type {};

template <typename Container, typename Ref, typename = void>
struct has_insert_end
	: public hamon::false_type {};

template <typename Container, typename Ref>
struct has_insert_end<Container, Ref,
	hamon::void_t<decltype(hamon::declval<Container&>().insert(hamon::declval<Container&>().begin(), hamon::declval<Ref>()))>>
	: public hamon::true_type {};

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// [range.utility.conv.general]/3
template <typename Container>
constexpr bool reservable_container =
	hamon::ranges::sized_range<Container> &&
	requires(Container& c, hamon::ranges::range_size_t<Container> n)
	{
		c.reserve(n);
		{ c.capacity() } -> hamon::same_as<decltype(n)>;
		{ c.max_size() } -> hamon::same_as<decltype(n)>;
	};

template <typename Container>
using reservable_container_t = hamon::bool_constant<reservable_container<Container>>;

// [range.utility.conv.general]/4
template <typename Container, typename Ref>
constexpr bool container_insertable =
	requires(Container& c, Ref&& ref)
	{
		requires (
			requires { c.push_back(hamon::forward<Ref>(ref)); } ||
			requires { c.insert(c.end(), hamon::forward<Ref>(ref)); });
	};

template <typename Container, typename Ref>
using container_insertable_t = hamon::bool_constant<container_insertable<Container, Ref>>;

// [range.utility.conv.to]/2.1.3
template <typename C, typename R, typename... Args>
concept container_common_constructible =
	// [range.utility.conv.to]/2.1.3.1
	hamon::ranges::common_range<R> &&
	// [range.utility.conv.to]/2.1.3.2
	requires { typename hamon::iterator_traits<hamon::ranges::iterator_t<R>>::iterator_category; } &&
	hamon::derived_from<typename hamon::iterator_traits<hamon::ranges::iterator_t<R>>::iterator_category, hamon::input_iterator_tag> &&
	// [range.utility.conv.to]/2.1.3.3
	hamon::constructible_from<C, hamon::ranges::iterator_t<R>, hamon::ranges::sentinel_t<R>, Args...>;

template <typename C, typename R, typename... Args>
using container_common_constructible_t = hamon::bool_constant<container_common_constructible<C, R, Args...>>;

#else	// defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Container>
struct reservable_container_impl
{
private:
	template <typename C2,
		typename = hamon::enable_if_t<hamon::ranges::sized_range_t<C2>::value>,
		typename SizeType = hamon::ranges::range_size_t<C2>,
		typename = decltype(hamon::declval<C2&>().reserve(hamon::declval<SizeType>())),
		typename R1 = decltype(hamon::declval<C2&>().capacity()),
		typename R2 = decltype(hamon::declval<C2&>().max_size()),
		typename = hamon::enable_if_t<hamon::same_as_t<R1, SizeType>::value>,
		typename = hamon::enable_if_t<hamon::same_as_t<R2, SizeType>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename C2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Container>(0));
};

template <typename Container>
using reservable_container_t =
	typename reservable_container_impl<Container>::type;

template <typename Container, typename Ref>
using container_insertable_t = hamon::disjunction<
	has_push_back<Container, Ref>,
	has_insert_end<Container, Ref>
>;

template <typename C, typename R, typename... Args>
struct container_common_constructible_impl
{
private:
	template <typename C2, typename R2, typename... Args2,
		typename = hamon::enable_if_t<hamon::ranges::common_range_t<R2>::value>,
		typename Cat = typename hamon::iterator_traits<hamon::ranges::iterator_t<R2>>::iterator_category,
		typename = hamon::enable_if_t<hamon::derived_from_t<Cat, hamon::input_iterator_tag>::value>,
		typename = hamon::enable_if_t<hamon::constructible_from_t<C2, hamon::ranges::iterator_t<R2>, hamon::ranges::sentinel_t<R2>, Args2...>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename C2, typename R2, typename... Args2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<C, R, Args...>(0));
};

template <typename C, typename R, typename... Args>
using container_common_constructible_t =
	typename container_common_constructible_impl<C, R, Args...>::type;

#endif	// defined(HAMON_HAS_CXX20_CONCEPTS)

// [range.utility.conv.general]/5

template <typename Ref, typename Container, typename = hamon::enable_if_t<has_push_back<Container, Ref>::value>>
HAMON_CXX11_CONSTEXPR auto
container_inserter_impl(Container& c, hamon::detail::overload_priority<1>)
->decltype(hamon::back_inserter(c))
{
	return hamon::back_inserter(c);
}

template <typename Ref, typename Container, typename = hamon::enable_if_t<has_insert_end<Container, Ref>::value>>
HAMON_CXX11_CONSTEXPR auto
container_inserter_impl(Container& c, hamon::detail::overload_priority<0>)
->decltype(hamon::inserter(c, c.end()))
{
	return hamon::inserter(c, c.end());
}

template <typename Ref, typename Container>
HAMON_CXX11_CONSTEXPR auto
container_inserter(Container& c)
->decltype(container_inserter_impl<Ref>(c, hamon::detail::overload_priority<1>{}))
{
	return container_inserter_impl<Ref>(c, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

// 26.5.7.2 ranges​::​to[range.utility.conv.to]

template <typename C, typename R, typename... Args,
	typename = hamon::enable_if_t<
		hamon::ranges::not_view_t<C>::value &&
		hamon::ranges::input_range_t<R>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
C to(R&& r, Args&&... args);	// to_implから再帰的に呼び出すため、前方宣言が必要

namespace detail
{

// [range.utility.conv.to]/2.1.1
template <typename C, typename R, typename... Args,
	typename = hamon::enable_if_t<
		hamon::constructible_from_t<C, R, Args...>::value>>
HAMON_CXX11_CONSTEXPR C
to_impl2(hamon::detail::overload_priority<4>, R&& r, Args&&... args)
{
	return C(hamon::forward<R>(r), hamon::forward<Args>(args)...);
}

// [range.utility.conv.to]/2.1.2
template <typename C, typename R, typename... Args,
	typename = hamon::enable_if_t<
		hamon::constructible_from_t<C, hamon::from_range_t, R, Args...>::value>>
HAMON_CXX11_CONSTEXPR C
to_impl2(hamon::detail::overload_priority<3>, R&& r, Args&&... args)
{
	return C(hamon::from_range, hamon::forward<R>(r), hamon::forward<Args>(args)...);
}

// [range.utility.conv.to]/2.1.3
template <typename C, typename R, typename... Args,
	typename = hamon::enable_if_t<
		hamon::ranges::detail::container_common_constructible_t<C, R, Args...>::value>>
HAMON_CXX11_CONSTEXPR C
to_impl2(hamon::detail::overload_priority<2>, R&& r, Args&&... args)
{
	return C(hamon::ranges::begin(r), hamon::ranges::end(r), hamon::forward<Args>(args)...);
}

// [range.utility.conv.to]/2.1.4
template <typename C, typename R,
	typename = hamon::enable_if_t<
		hamon::ranges::sized_range_t<R>::value &&
		hamon::ranges::detail::reservable_container_t<C>::value>>
HAMON_CXX14_CONSTEXPR void
to_impl_reserve(C& c, R&& r, hamon::detail::overload_priority<1>)
{
	c.reserve(static_cast<hamon::ranges::range_size_t<C>>(hamon::ranges::size(r)));
}

template <typename C, typename R>
HAMON_CXX14_CONSTEXPR void
to_impl_reserve(C&, R&&, hamon::detail::overload_priority<0>)
{
	// do nothing
}

template <typename C, typename R, typename... Args,
	typename = hamon::enable_if_t<
		hamon::constructible_from_t<C, Args...>::value &&
		hamon::ranges::detail::container_insertable_t<C, hamon::ranges::range_reference_t<R>>::value>>
HAMON_CXX14_CONSTEXPR C
to_impl2(hamon::detail::overload_priority<1>, R&& r, Args&&... args)
{
	C c(hamon::forward<Args>(args)...);
	to_impl_reserve(c, r, hamon::detail::overload_priority<1>{});
	hamon::ranges::copy(r, hamon::ranges::detail::container_inserter<hamon::ranges::range_reference_t<R>>(c));
	return c;
}

// [range.utility.conv.to]/2.1.5
template <typename C, typename R, typename... Args>
HAMON_CXX11_CONSTEXPR C
to_impl2(hamon::detail::overload_priority<0>, R&& r, Args&&... args);

// [range.utility.conv.to]/2.1
template <typename C, typename R, typename... Args,
	typename = hamon::enable_if_t<
		!hamon::ranges::input_range_t<C>::value ||
		hamon::convertible_to_t<hamon::ranges::range_reference_t<R>, hamon::ranges::range_value_t<C>>::value>>
HAMON_CXX11_CONSTEXPR C
to_impl(hamon::detail::overload_priority<2>, R&& r, Args&&... args)
{
	return to_impl2<C>(hamon::detail::overload_priority<4>{}, hamon::forward<R>(r), hamon::forward<Args>(args)...);
}

// [range.utility.conv.to]/2.2

template <typename C>
struct to_recursive_fn
{
	template <typename T>
	HAMON_CXX11_CONSTEXPR hamon::ranges::range_value_t<C>
	operator()(T&& elem) const
	{
		return hamon::ranges::to<hamon::ranges::range_value_t<C>>(hamon::forward<T>(elem));
	}
};

template <typename C, typename R, typename... Args,
	typename = hamon::enable_if_t<
		hamon::ranges::input_range_t<hamon::ranges::range_reference_t<R>>::value>>
HAMON_CXX11_CONSTEXPR C
to_impl(hamon::detail::overload_priority<1>, R&& r, Args&&... args)
{
	return hamon::ranges::to<C>(
		r | hamon::views::transform(to_recursive_fn<C>{}), hamon::forward<Args>(args)...);
}

// [range.utility.conv.to]/2.3
template <typename C, typename R, typename... Args>
HAMON_CXX11_CONSTEXPR C
to_impl(hamon::detail::overload_priority<0>, R&& r, Args&&... args);

}	// namespace detail

template <typename C, typename R, typename... Args, typename>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
C to(R&& r, Args&&... args)
{
	// [range.utility.conv.to]/1
	static_assert(!hamon::is_const<C>::value, "");
	static_assert(!hamon::is_volatile<C>::value, "");
	static_assert( hamon::is_class<C>::value, "");

	return hamon::ranges::detail::to_impl<C>(
		hamon::detail::overload_priority<2>{}, hamon::forward<R>(r), hamon::forward<Args>(args)...);
}

// 26.5.7.3 ranges​::​to adaptors[range.utility.conv.adaptors]

namespace detail {

template <typename C>
struct to_fn
{
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R), typename... Args>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR C
	operator()(R&& r, Args&&... args) const
	{
		return hamon::ranges::to<C>(hamon::forward<R>(r), hamon::forward<Args>(args)...);
	}
};

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::not_view, C), typename... Args>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
auto to(Args&&... args)
->decltype(hamon::ranges::detail::make_range_adaptor(
		hamon::bind_back(hamon::ranges::detail::to_fn<C>{}, hamon::forward<Args>(args)...)))
{
	// [range.utility.conv.adaptors]/1
	static_assert(!hamon::is_const<C>::value, "");
	static_assert(!hamon::is_volatile<C>::value, "");
	static_assert( hamon::is_class<C>::value, "");

	// [range.utility.conv.adaptors]/2
	return hamon::ranges::detail::make_range_adaptor(
		hamon::bind_back(hamon::ranges::detail::to_fn<C>{}, hamon::forward<Args>(args)...));
}

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace detail {

// [range.utility.conv.to]/3
template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R)>
struct phony_input_iterator
{
	using iterator_category = hamon::input_iterator_tag;
	using value_type = hamon::ranges::range_value_t<R>;
	using difference_type = hamon::ptrdiff_t;
	using pointer = hamon::add_pointer_t<hamon::ranges::range_reference_t<R>>;
	using reference = hamon::ranges::range_reference_t<R>;
	reference operator*() const;
	pointer operator->() const;
	phony_input_iterator& operator++();
	phony_input_iterator operator++(int);
	bool operator==(const phony_input_iterator&) const;
};

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <template <typename...> class C, typename R, typename... Args>
concept deduce_direct_constructible =
	requires { C(hamon::declval<R>(), hamon::declval<Args>()...); };

template <template <typename...> class C, typename R, typename... Args>
using deduce_direct_constructible_t =
	hamon::bool_constant<deduce_direct_constructible<C, R, Args...>>;

template <template <typename...> class C, typename R, typename... Args>
concept deduce_from_range_constructible =
	requires { C(hamon::from_range, hamon::declval<R>(), hamon::declval<Args>()...); };

template <template <typename...> class C, typename R, typename... Args>
using deduce_from_range_constructible_t =
	hamon::bool_constant<deduce_from_range_constructible<C, R, Args...>>;

template <template <typename...> class C, typename R, typename... Args>
concept deduce_common_constructible =
	requires { C(hamon::declval<phony_input_iterator<R>>(), hamon::declval<phony_input_iterator<R>>(), hamon::declval<Args>()...); };

template <template <typename...> class C, typename R, typename... Args>
using deduce_common_constructible_t =
	hamon::bool_constant<deduce_common_constructible<C, R, Args...>>;

#else

template <template <typename...> class C, typename R, typename... Args>
struct deduce_direct_constructible_impl
{
private:
	template <template <typename...> class C2, typename R2, typename... Args2,
		typename = decltype(C2(hamon::declval<R2>(), hamon::declval<Args2>()...))>
	static auto test(int) -> hamon::true_type;

	template <template <typename...> class C2, typename R2, typename... Args2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<C, R, Args...>(0));
};

template <template <typename...> class C, typename R, typename... Args>
using deduce_direct_constructible_t =
	typename deduce_direct_constructible_impl<C, R, Args...>::type;

template <template <typename...> class C, typename R, typename... Args>
struct deduce_from_range_constructible_impl
{
private:
	template <template <typename...> class C2, typename R2, typename... Args2,
		typename = decltype(C2(hamon::from_range, hamon::declval<R2>(), hamon::declval<Args2>()...))>
	static auto test(int) -> hamon::true_type;

	template <template <typename...> class C2, typename R2, typename... Args2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<C, R, Args...>(0));
};

template <template <typename...> class C, typename R, typename... Args>
using deduce_from_range_constructible_t =
	typename deduce_from_range_constructible_impl<C, R, Args...>::type;

template <template <typename...> class C, typename R, typename... Args>
struct deduce_common_constructible_impl
{
private:
	template <template <typename...> class C2, typename R2, typename... Args2,
		typename = decltype(C2(hamon::declval<phony_input_iterator<R2>>(), hamon::declval<phony_input_iterator<R2>>(), hamon::declval<Args2>()...))>
	static auto test(int) -> hamon::true_type;

	template <template <typename...> class C2, typename R2, typename... Args2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<C, R, Args...>(0));
};

template <template <typename...> class C, typename R, typename... Args>
using deduce_common_constructible_t =
	typename deduce_common_constructible_impl<C, R, Args...>::type;

#endif

// [range.utility.conv.to]/4.1
template <template <typename...> class C, typename R, typename... Args,
	typename = hamon::enable_if_t<deduce_direct_constructible_t<C, R, Args...>::value>>
auto deduce_helper_impl(hamon::detail::overload_priority<3>)
{
	return static_cast<decltype(C(hamon::declval<R>(), hamon::declval<Args>()...))*>(nullptr);
}

// [range.utility.conv.to]/4.2
template <template <typename...> class C, typename R, typename... Args,
	typename = hamon::enable_if_t<deduce_from_range_constructible_t<C, R, Args...>::value>>
auto deduce_helper_impl(hamon::detail::overload_priority<2>)
{
	return static_cast<decltype(C(hamon::from_range, hamon::declval<R>(), hamon::declval<Args>()...))*>(nullptr);
}

// [range.utility.conv.to]/4.3
template <template <typename...> class C, typename R, typename... Args,
	typename = hamon::enable_if_t<deduce_common_constructible_t<C, R, Args...>::value>>
auto deduce_helper_impl(hamon::detail::overload_priority<1>)
{
	return static_cast<decltype(C(hamon::declval<phony_input_iterator<R>>(), hamon::declval<phony_input_iterator<R>>(), hamon::declval<Args>()...))*>(nullptr);
}

// [range.utility.conv.to]/4.4
template <template <typename...> class C, typename R, typename... Args>
auto deduce_helper_impl(hamon::detail::overload_priority<0>);

// [range.utility.conv.to]/4
template <template <typename...> class C, typename R, typename... Args>
auto deduce_helper()
{
	return deduce_helper_impl<C, R, Args...>(hamon::detail::overload_priority<3>{});
}

}	// namespace detail

// 26.5.7.2 ranges​::​to[range.utility.conv.to]

template <template <typename...> class C, HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R), typename... Args>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
auto to(R&& r, Args&&... args)
{
	// [range.utility.conv.to]/5
	using DEDUCED = hamon::remove_pointer_t<decltype(hamon::ranges::detail::deduce_helper<C, R, Args...>())>;
	return hamon::ranges::to<DEDUCED>(hamon::forward<R>(r), hamon::forward<Args>(args)...);
}

// 26.5.7.3 ranges​::​to adaptors[range.utility.conv.adaptors]

namespace detail
{

template <template <typename...> class C>
struct to_deduced_fn
{
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R), typename... Args>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, Args&&... args) const
	{
		return hamon::ranges::to<C>(hamon::forward<R>(r), hamon::forward<Args>(args)...);
	}
};

}	// namespace detail

template <template <typename...> class C, typename... Args>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
auto to(Args&&... args)
{
	// [range.utility.conv.adaptors]/2
	return hamon::ranges::detail::make_range_adaptor(
		hamon::bind_back(hamon::ranges::detail::to_deduced_fn<C>{}, hamon::forward<Args>(args)...));
}

#endif	// defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_UTILITY_TO_HPP
