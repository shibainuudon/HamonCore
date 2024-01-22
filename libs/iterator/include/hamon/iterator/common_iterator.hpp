/**
 *	@file	common_iterator.hpp
 *
 *	@brief	common_iterator の定義
 */

#ifndef HAMON_ITERATOR_COMMON_ITERATOR_HPP
#define HAMON_ITERATOR_COMMON_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

#define HAMON_USE_STD_COMMON_ITERATOR

namespace hamon
{

using std::common_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/detail/can_reference.hpp>
#include <hamon/iterator/detail/dereferenceable.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/equality_comparable_with.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/in_place_type_t.hpp>
#include <hamon/utility/in_place_index_t.hpp>
#include <hamon/variant.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace common_iterator_detail
{

// has_arrow

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename I>
concept has_arrow =
	requires(I const& i) { i.operator->(); };

template <typename I>
using has_arrow_t = hamon::bool_constant<has_arrow<I>>;

#else

template <typename I, typename = void>
struct has_arrow
	: public hamon::false_type {};

template <typename I>
struct has_arrow<I, hamon::void_t<decltype(hamon::declval<I const&>().operator->())>>
	: public hamon::true_type {};

template <typename I>
using has_arrow_t = has_arrow<I>;

#endif

// has_post_increment

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename I>
concept has_post_increment =
	requires(I& i) {{ *i++ } -> hamon::detail::can_reference; };

template <typename I>
using has_post_increment_t = hamon::bool_constant<has_post_increment<I>>;

#else

template <typename I, typename = void>
struct has_post_increment
	: public hamon::false_type {};

template <typename I>
struct has_post_increment<I, hamon::void_t<decltype(*hamon::declval<I&>()++)>>
	: public hamon::detail::can_reference<decltype(*hamon::declval<I&>()++)> {};

template <typename I>
using has_post_increment_t = has_post_increment<I>;

#endif

}	// namespace common_iterator_detail

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::input_or_output_iterator I, hamon::sentinel_for<I> S>
	requires (!hamon::same_as<I, S> && hamon::copyable<I>)
#else
template <typename I, typename S,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::input_or_output_iterator_t<I>,
		hamon::sentinel_for_t<S, I>,
		hamon::negation<hamon::same_as_t<I, S>>,
		hamon::copyable_t<I>
	>::value>>
#endif
class common_iterator
{
public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_CXX11_CONSTEXPR common_iterator()
		requires hamon::default_initializable<I> = default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, I2, I)>
	HAMON_CXX11_CONSTEXPR
	common_iterator() HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_default_constructible<I>::value &&
		hamon::is_nothrow_default_constructible<S>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR
	common_iterator(I i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<I>::value)
		// [common.iter.const]/1
		: m_v{hamon::in_place_type_t<I>{}, hamon::move(i)}
	{}

	HAMON_CXX11_CONSTEXPR
	common_iterator(S s) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<S>::value)
		// [common.iter.const]/2
		: m_v{hamon::in_place_type_t<S>{}, hamon::move(s)}
	{}

private:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <hamon::input_or_output_iterator I2, hamon::sentinel_for<I2> S2>
		requires (!hamon::same_as<I2, S2> && hamon::copyable<I2>)
#else
	template <typename, typename, typename>
#endif
	friend class common_iterator;

	template <typename I2, typename S2>
	static HAMON_CXX11_CONSTEXPR hamon::variant<I, S>
	ctor_helper(common_iterator<I2, S2> const& x)
	{
		return
			// [common.iter.const]/3
			HAMON_ASSERT(!x.m_v.valueless_by_exception()),
			// [common.iter.const]/4
			(x.m_v.index() == 0 ?
				hamon::variant<I, S>{hamon::in_place_index_t<0>{}, hamon::get<0>(x.m_v)} :
				hamon::variant<I, S>{hamon::in_place_index_t<1>{}, hamon::get<1>(x.m_v)});
	}

public:
	template <typename I2, typename S2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to_t<I2 const&, I>,
			hamon::convertible_to_t<S2 const&, S>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	common_iterator(common_iterator<I2, S2> const& x)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<I, I2 const&>::value &&
			hamon::is_nothrow_constructible<S, S2 const&>::value)
		: m_v{ctor_helper(x)}
	{}

	template <typename I2, typename S2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to_t<I2 const&, I>,
			hamon::convertible_to_t<S2 const&, S>,
			hamon::assignable_from_t<I&, I2 const&>,
			hamon::assignable_from_t<S&, S2 const&>
		>::value>>
	HAMON_CXX14_CONSTEXPR common_iterator&
	operator=(common_iterator<I2, S2> const& x)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<I, I2 const&>::value &&
			hamon::is_nothrow_constructible<S, S2 const&>::value &&
			hamon::is_nothrow_assignable<I&, I2 const&>::value &&
			hamon::is_nothrow_assignable<S&, S2 const&>::value)
	{
		// [common.iter.const]/5
		HAMON_ASSERT(!x.m_v.valueless_by_exception());

		if (m_v.index() == 0 && x.m_v.index() == 0)
		{
			// [common.iter.const]/6.1
			hamon::get<0>(m_v) = hamon::get<0>(x.m_v);
		}
		else if (m_v.index() == 1 && x.m_v.index() == 1)
		{
			// [common.iter.const]/6.1
			hamon::get<1>(m_v) = hamon::get<1>(x.m_v);
		}
		else if (x.m_v.index() == 0)
		{
			// [common.iter.const]/6.2
			m_v.template emplace<0>(hamon::get<0>(x.m_v));
		}
		else // if (x.m_v.index() == 1)
		{
			// [common.iter.const]/6.2
			m_v.template emplace<1>(hamon::get<1>(x.m_v));
		}

		// [common.iter.const]/7
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	operator*()
	-> decltype(*hamon::declval<I&>())
	{
		return
			// [common.iter.access]/1
			HAMON_ASSERT(hamon::holds_alternative<I>(m_v)),
			// [common.iter.access]/2
			*hamon::get<I>(m_v);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::detail::dereferenceable, I2, I const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	operator*() const
	-> decltype(*hamon::declval<I2&>())
	{
		return
			// [common.iter.access]/1
			HAMON_ASSERT(hamon::holds_alternative<I>(m_v)),
			// [common.iter.access]/2
			*hamon::get<I>(m_v);
	}

private:
	template <typename I2 = I,
		typename = hamon::enable_if_t<
			hamon::is_pointer<I2>::value ||
			hamon::common_iterator_detail::has_arrow_t<I2>::value>>
	HAMON_CXX11_CONSTEXPR auto
	arrow_impl(hamon::detail::overload_priority<2>) const
	-> I
	{
		// [common.iter.access]/5.1
		return hamon::get<I>(m_v);
	}

	template <typename I2 = I,
		typename = hamon::enable_if_t<
			hamon::is_reference<hamon::iter_reference_t<I2>>::value>>
	HAMON_CXX11_CONSTEXPR auto
	arrow_impl(hamon::detail::overload_priority<1>) const
	-> decltype(hamon::addressof(*hamon::declval<I2&>()))
	{
		// [common.iter.access]/5.2
		//auto&& tmp = *hamon::get<I>(m_v);
		//return hamon::addressof(tmp);
		return hamon::addressof(*hamon::get<I>(m_v));
	}

	// [common.iter.access]/5.3
	class proxy
	{
	private:
		friend common_iterator;

		hamon::iter_value_t<I> m_keep;

		HAMON_CXX11_CONSTEXPR
		proxy(hamon::iter_reference_t<I>&& x) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<hamon::iter_value_t<I>, hamon::iter_reference_t<I>>::value)
			: m_keep(hamon::move(x))
		{}

	public:
		HAMON_CXX11_CONSTEXPR hamon::iter_value_t<I> const*
		operator->() const HAMON_NOEXCEPT
		{
			return hamon::addressof(m_keep);
		}
	};

	HAMON_CXX11_CONSTEXPR proxy
	arrow_impl(hamon::detail::overload_priority<0>) const
	{
		return proxy{ *hamon::get<I>(m_v) };
	}

public:
	template <typename I2 = I,
		// [common.iter.access]/3
		typename = hamon::enable_if_t<
			hamon::indirectly_readable_t<I2 const>::value &&
			(hamon::common_iterator_detail::has_arrow_t<I2>::value ||
			 hamon::is_reference<hamon::iter_reference_t<I2>>::value ||
			 hamon::constructible_from_t<hamon::iter_value_t<I2>, hamon::iter_reference_t<I2>>::value)
		>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	operator->() const
	->decltype(arrow_impl(hamon::detail::overload_priority<2>{}))
	{
		return
			// [common.iter.access]/4
			HAMON_ASSERT(hamon::holds_alternative<I>(m_v)),
			arrow_impl(hamon::detail::overload_priority<2>{});
	}

	HAMON_CXX14_CONSTEXPR common_iterator& operator++()
	{
		// [common.iter.nav]/1
		HAMON_ASSERT(hamon::holds_alternative<I>(m_v));
		// [common.iter.nav]/2
		++hamon::get<I>(m_v);
		// [common.iter.nav]/3
		return *this;
	}

private:
	// [common.iter.nav]/5
	template <typename I2 = I,
		typename = hamon::enable_if_t<
			hamon::forward_iterator_t<I2>::value>>
	HAMON_CXX14_CONSTEXPR common_iterator
	increment_impl(hamon::detail::overload_priority<2>)
	{
		common_iterator tmp = *this;
		++*this;
		return tmp;
	}

	template <typename I2 = I,
		typename = hamon::enable_if_t<
			common_iterator_detail::has_post_increment_t<I2>::value ||
			!(hamon::indirectly_readable_t<I2>::value &&
			  hamon::constructible_from_t<hamon::iter_value_t<I2>, hamon::iter_reference_t<I2>>::value &&
			  hamon::move_constructible_t<hamon::iter_value_t<I2>>::value)>>
	HAMON_CXX14_CONSTEXPR auto
	increment_impl(hamon::detail::overload_priority<1>)
	-> decltype(hamon::declval<I2&>()++)
	{
		return hamon::get<I>(m_v)++;
	}

	class postfix_proxy
	{
	private:
		friend common_iterator;

		hamon::iter_value_t<I> m_keep;

#if defined(HAMON_MSVC)
		// MSVCは、friend指定してもエラーになってしまうので、
		// 仕方なくpublicにする。
	public:
#endif
		HAMON_CXX11_CONSTEXPR
		postfix_proxy(hamon::iter_reference_t<I>&& x) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<hamon::iter_value_t<I>, hamon::iter_reference_t<I>>::value)
			: m_keep(hamon::forward<hamon::iter_reference_t<I>>(x))
		{}

	public:
		HAMON_CXX11_CONSTEXPR hamon::iter_value_t<I> const&
		operator*() const HAMON_NOEXCEPT
		{
			return m_keep;
		}
	};

	HAMON_CXX14_CONSTEXPR postfix_proxy
	increment_impl(hamon::detail::overload_priority<0>)
	{
		postfix_proxy p(**this);
		++*this;
		return p;
	}

public:
	HAMON_CXX14_CONSTEXPR auto
	operator++(int)
	-> decltype(increment_impl(hamon::detail::overload_priority<2>{}))
	{
		// [common.iter.nav]/4
		HAMON_ASSERT(hamon::holds_alternative<I>(m_v));

		return increment_impl(hamon::detail::overload_priority<2>{});
	}

private:
	template <typename I2, typename S2,
		typename = hamon::enable_if_t<hamon::equality_comparable_with_t<I, I2>::value>>
	static HAMON_CXX11_CONSTEXPR bool
	equal_impl(common_iterator const& x, common_iterator<I2, S2> const& y, hamon::detail::overload_priority<1>)
	{
		return
			// [common.iter.cmp]/3
			HAMON_ASSERT(!x.m_v.valueless_by_exception()),
			HAMON_ASSERT(!y.m_v.valueless_by_exception()),
			// [common.iter.cmp]/4
			x.m_v.index() == 0 && y.m_v.index() == 0 ? hamon::get<0>(x.m_v) == hamon::get<0>(y.m_v) :
			x.m_v.index() == 0 && y.m_v.index() == 1 ? hamon::get<0>(x.m_v) == hamon::get<1>(y.m_v) :
			x.m_v.index() == 1 && y.m_v.index() == 0 ? hamon::get<1>(x.m_v) == hamon::get<0>(y.m_v) :
			/*x.m_v.index() == 1 && y.m_v.index() == 1 ?*/ true;
	}

	template <typename I2, typename S2>
	static HAMON_CXX11_CONSTEXPR bool
	equal_impl(common_iterator const& x, common_iterator<I2, S2> const& y, hamon::detail::overload_priority<0>)
	{
		return
			// [common.iter.cmp]/1
			HAMON_ASSERT(!x.m_v.valueless_by_exception()),
			HAMON_ASSERT(!y.m_v.valueless_by_exception()),
			// [common.iter.cmp]/2
			x.m_v.index() == 0 && y.m_v.index() == 1 ? hamon::get<0>(x.m_v) == hamon::get<1>(y.m_v) :
			x.m_v.index() == 1 && y.m_v.index() == 0 ? hamon::get<1>(x.m_v) == hamon::get<0>(y.m_v) :
			/*x.m_v.index() == y.m_v.index() ?*/ true;
	}

	template <typename I2, typename S2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::sentinel_for_t<S2, I>,
			hamon::sentinel_for_t<S, I2>
		>::value>>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool operator==(common_iterator const& x, common_iterator<I2, S2> const& y)
	{
		return common_iterator::equal_impl(x, y, hamon::detail::overload_priority<1>{});
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	template <typename I2, typename S2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::sentinel_for_t<S2, I>,
			hamon::sentinel_for_t<S, I2>
		>::value>>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool operator!=(common_iterator const& x, common_iterator<I2, S2> const& y)
	{
		return !(x == y);
	}
#endif

	template <typename I2, typename S2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::sized_sentinel_for_t<I2, I>,
			hamon::sized_sentinel_for_t<S2, I>,
			hamon::sized_sentinel_for_t<S, I2>
		>::value>>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::iter_difference_t<I2>
	operator-(common_iterator const& x, common_iterator<I2, S2> const& y)
	{
		return
			// [common.iter.cmp]/5
			HAMON_ASSERT(!x.m_v.valueless_by_exception()),
			HAMON_ASSERT(!y.m_v.valueless_by_exception()),
			// [common.iter.cmp]/6
			x.m_v.index() == 0 && y.m_v.index() == 0 ? hamon::get<0>(x.m_v) - hamon::get<0>(y.m_v) :
			x.m_v.index() == 0 && y.m_v.index() == 1 ? hamon::get<0>(x.m_v) - hamon::get<1>(y.m_v) :
			x.m_v.index() == 1 && y.m_v.index() == 0 ? hamon::get<1>(x.m_v) - hamon::get<0>(y.m_v) :
			/*x.m_v.index() == 1 && y.m_v.index() == 1 ?*/ 0;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::input_iterator, I2, I)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	iter_move(common_iterator const& i)
		HAMON_NOEXCEPT_IF_EXPR(
			hamon::ranges::iter_move(hamon::declval<I2 const&>()))
	->decltype(hamon::ranges::iter_move(hamon::declval<I2 const&>()))
	{
		return
			// [common.iter.cust]/1
			HAMON_ASSERT(hamon::holds_alternative<I>(i.m_v)),
			// [common.iter.cust]/2
			hamon::ranges::iter_move(hamon::get<I>(i.m_v));
	}

	template <typename S2, HAMON_CONSTRAINED_PARAM(hamon::indirectly_swappable, I, I2)>
	friend HAMON_CXX14_CONSTEXPR void
	iter_swap(common_iterator const& x, common_iterator<I2, S2> const& y)
		HAMON_NOEXCEPT_IF_EXPR(
			hamon::ranges::iter_swap(hamon::declval<I const&>(), hamon::declval<I2 const&>()))
	{
		// [common.iter.cust]/3
		HAMON_ASSERT(hamon::holds_alternative<I>(x.m_v));
		HAMON_ASSERT(hamon::holds_alternative<I2>(y.m_v));

		// [common.iter.cust]/4
		hamon::ranges::iter_swap(hamon::get<I>(x.m_v), hamon::get<I2>(y.m_v));
	}

private:
	hamon::variant<I, S> m_v;
};

template <typename I, typename S>
struct incrementable_traits<hamon::common_iterator<I, S>>
{
	using difference_type = hamon::iter_difference_t<I>;
};

namespace common_iterator_detail
{

// [common.iter.types]/1

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename I>
concept denotes_forward_iter =
	requires { typename hamon::iterator_traits<I>::iterator_category; } &&
	hamon::derived_from<typename hamon::iterator_traits<I>::iterator_category, hamon::forward_iterator_tag>;

template <typename I>
using denotes_forward_iter_t = hamon::bool_constant<denotes_forward_iter<I>>;

#else

template <typename I, typename = void>
struct denotes_forward_iter
	: public hamon::false_type {};

template <typename I>
struct denotes_forward_iter<I, hamon::void_t<typename hamon::iterator_traits<I>::iterator_category>>
	: public hamon::derived_from<typename hamon::iterator_traits<I>::iterator_category, hamon::forward_iterator_tag> {};

template <typename I>
using denotes_forward_iter_t = denotes_forward_iter<I>;

#endif

template <typename I, typename S,
	bool = hamon::integral_t<hamon::iter_difference_t<I>>::value>
struct iterator_category_base
{
	using iterator_category = hamon::conditional_t<
		denotes_forward_iter_t<I>::value,
		hamon::forward_iterator_tag,
		hamon::input_iterator_tag
	>;
};

template <typename I, typename S>
struct iterator_category_base<I, S, false>
{
};

// [common.iter.types]/2.2
template <typename I, typename S,
	bool = hamon::common_iterator_detail::has_arrow_t<hamon::common_iterator<I, S>>::value>
struct pointer
{
	using type = void;
};

template <typename I, typename S>
struct pointer<I, S, true>
{
	using type = decltype(hamon::declval<hamon::common_iterator<I, S> const&>().operator->());
};

}	// namespace common_iterator_detail

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::input_iterator I, typename S>
struct iterator_traits<hamon::common_iterator<I, S>>
#else
template <typename I, typename S>
struct iterator_traits<
	hamon::detail::enable_iterator_traits_helper<
		hamon::common_iterator<I, S>,
		hamon::enable_if_t<hamon::input_iterator_t<I>::value>
	>
>
#endif
	: public common_iterator_detail::iterator_category_base<I, S>
{
	// [common.iter.types]/2.1
	using iterator_concept = hamon::conditional_t<
		hamon::forward_iterator_t<I>::value,
		hamon::forward_iterator_tag,
		hamon::input_iterator_tag
	>;
	//using iterator_category = see below;  // not always present
	using value_type = hamon::iter_value_t<I>;
	using difference_type = hamon::iter_difference_t<I>;
	// [common.iter.types]/2.2
	using pointer = typename common_iterator_detail::pointer<I, S>::type;
	using reference = hamon::iter_reference_t<I>;
};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_COMMON_ITERATOR_HPP
