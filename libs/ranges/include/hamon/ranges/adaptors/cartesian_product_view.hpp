/**
 *	@file	cartesian_product_view.hpp
 *
 *	@brief	cartesian_product_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_CARTESIAN_PRODUCT_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_CARTESIAN_PRODUCT_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_cartesian_product) && (__cpp_lib_ranges_cartesian_product >= 202207L)

namespace hamon {
namespace ranges {

using std::ranges::cartesian_product_view;

namespace views {

using std::ranges::views::cartesian_product;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/all_random_access.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/detail/tuple_transform.hpp>
#include <hamon/ranges/detail/tuple_for_each.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/utility/detail/make_unsigned_like_t.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace hamon {
namespace ranges {

// 26.7.32.2 Class template cartesian_product_view[range.cartesian.view]

namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <bool Const, typename First, typename... Vs>
concept cartesian_product_is_random_access =
	(hamon::ranges::random_access_range<hamon::ranges::detail::maybe_const<Const, First>> && ... &&
	(hamon::ranges::random_access_range<hamon::ranges::detail::maybe_const<Const, Vs>> &&
	 hamon::ranges::sized_range<hamon::ranges::detail::maybe_const<Const, Vs>>));

template <bool Const, typename First, typename... Vs>
using cartesian_product_is_random_access_t = hamon::bool_constant<cartesian_product_is_random_access<Const, First, Vs...>>;

template <typename R>
concept cartesian_product_common_arg =
	hamon::ranges::common_range<R> ||
	(hamon::ranges::sized_range<R> && hamon::ranges::random_access_range<R>);

template <bool Const, typename First, typename... Vs>
concept cartesian_product_is_bidirectional =
	(hamon::ranges::bidirectional_range<hamon::ranges::detail::maybe_const<Const, First>> && ... &&
	(hamon::ranges::bidirectional_range<hamon::ranges::detail::maybe_const<Const, Vs>> &&
	 cartesian_product_common_arg<hamon::ranges::detail::maybe_const<Const, Vs>>));

template <bool Const, typename First, typename... Vs>
using cartesian_product_is_bidirectional_t = hamon::bool_constant<cartesian_product_is_bidirectional<Const, First, Vs...>>;

template <typename First, typename...>
concept cartesian_product_is_common = cartesian_product_common_arg<First>;

template <typename First, typename... Vs>
using cartesian_product_is_common_t = hamon::bool_constant<cartesian_product_is_common<First, Vs...>>;

template <typename... Vs>
concept cartesian_product_is_sized = (hamon::ranges::sized_range<Vs> && ...);

template <typename... Vs>
using cartesian_product_is_sized_t = hamon::bool_constant<cartesian_product_is_sized<Vs...>>;

template <bool Const, template <typename> class FirstSent, typename First, typename... Vs>
concept cartesian_is_sized_sentinel = (
	hamon::sized_sentinel_for<
		FirstSent<hamon::ranges::detail::maybe_const<Const, First>>,
		hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, First>>
	> && ... &&
	(hamon::ranges::sized_range<hamon::ranges::detail::maybe_const<Const, Vs>> &&
	 hamon::sized_sentinel_for<
		hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, Vs>>,
		hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, Vs>>
	 >)
);

template <bool Const, template <typename> class FirstSent, typename First, typename... Vs>
using cartesian_is_sized_sentinel_t = hamon::bool_constant<cartesian_is_sized_sentinel<Const, FirstSent, First, Vs...>>;

#else

template <bool Const, typename First, typename... Vs>
using cartesian_product_is_random_access = hamon::conjunction<
	hamon::ranges::random_access_range_t<hamon::ranges::detail::maybe_const<Const, First>>,
	hamon::ranges::random_access_range_t<hamon::ranges::detail::maybe_const<Const, Vs>>...,
	hamon::ranges::sized_range_t<hamon::ranges::detail::maybe_const<Const, Vs>>...
>;

template <bool Const, typename First, typename... Vs>
using cartesian_product_is_random_access_t = cartesian_product_is_random_access<Const, First, Vs...>;

template <typename R>
using cartesian_product_common_arg = hamon::disjunction<
	hamon::ranges::common_range_t<R>,
	hamon::conjunction<
		hamon::ranges::sized_range_t<R>,
		hamon::ranges::random_access_range_t<R>
	>
>;

template <bool Const, typename First, typename... Vs>
using cartesian_product_is_bidirectional = hamon::conjunction<
	hamon::ranges::bidirectional_range_t<hamon::ranges::detail::maybe_const<Const, First>>,
	hamon::ranges::bidirectional_range_t<hamon::ranges::detail::maybe_const<Const, Vs>>...,
	cartesian_product_common_arg<hamon::ranges::detail::maybe_const<Const, Vs>>...
>;

template <bool Const, typename First, typename... Vs>
using cartesian_product_is_bidirectional_t = cartesian_product_is_bidirectional<Const, First, Vs...>;

template <typename First, typename...>
using cartesian_product_is_common = cartesian_product_common_arg<First>;

template <typename First, typename... Vs>
using cartesian_product_is_common_t = cartesian_product_is_common<First, Vs...>;

template <typename... Vs>
using cartesian_product_is_sized = hamon::conjunction<hamon::ranges::sized_range_t<Vs>...>;

template <typename... Vs>
using cartesian_product_is_sized_t = cartesian_product_is_sized<Vs...>;

template <bool Const, template <typename...> class FirstSent, typename First, typename... Vs>
using cartesian_is_sized_sentinel = hamon::conjunction<
	hamon::sized_sentinel_for_t<
		FirstSent<hamon::ranges::detail::maybe_const<Const, First>>,
		hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, First>>
	>,
	hamon::ranges::sized_range_t<hamon::ranges::detail::maybe_const<Const, Vs>>...,
	hamon::sized_sentinel_for_t<
		hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, Vs>>,
		hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, Vs>>
	>...
>;

template <bool Const, template <typename...> class FirstSent, typename First, typename... Vs>
using cartesian_is_sized_sentinel_t = cartesian_is_sized_sentinel<Const, FirstSent, First, Vs...>;

#endif

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::common_range, R)>
HAMON_CXX11_CONSTEXPR auto cartesian_common_arg_end_impl(R& r, hamon::detail::overload_priority<1>)
->decltype(hamon::ranges::end(r))
{
	return hamon::ranges::end(r);
}

template <typename R>
HAMON_CXX11_CONSTEXPR auto cartesian_common_arg_end_impl(R& r, hamon::detail::overload_priority<0>)
->decltype(hamon::ranges::begin(r) + hamon::ranges::distance(r))
{
	return hamon::ranges::begin(r) + hamon::ranges::distance(r);
}

template <HAMON_CONSTRAINED_PARAM(cartesian_product_common_arg, R)>
HAMON_CXX11_CONSTEXPR auto cartesian_common_arg_end(R& r)
->decltype(cartesian_common_arg_end_impl(r, hamon::detail::overload_priority<1>{}))
{
	return cartesian_common_arg_end_impl(r, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

inline namespace cartesian_product_view_ns
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range First, hamon::ranges::forward_range... Vs>
	requires (hamon::ranges::view<First> && ... && hamon::ranges::view<Vs>)
#else
// C++20 Concepts が使えないとき、
// テンプレートパラメータパックはテンプレートパラメータリストの最後でなければならないので、
// enable_if で制約することができない。
template <typename First, typename... Vs>
#endif
class cartesian_product_view : public hamon::ranges::view_interface<cartesian_product_view<First, Vs...>>
{
private:
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	static_assert(hamon::ranges::input_range_t<First>::value, "");
	static_assert(hamon::ranges::view_t<First>::value, "");
	static_assert(hamon::conjunction<hamon::ranges::forward_range_t<Vs>...>::value, "");
	static_assert(hamon::conjunction<hamon::ranges::view_t<Vs>...>::value, "");
#endif

	template <bool Const>
	using Difference = hamon::common_type_t<
		hamon::ptrdiff_t,	// TODO
        hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<Const, First>>,
		hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<Const, Vs>>...>;

	// [range.cartesian.view]/7
	// TODO
	// [range.cartesian.view]/8
	// Recommended practice: The return type should be the smallest unsigned-integer-like
	// type that is sufficiently wide to store the product of the maximum sizes
	// of all the underlying ranges, if such a type exists.
	template <bool Const>
	using SizeType = hamon::ranges::detail::make_unsigned_like_t<Difference<Const>>;

	template <bool Const>
	using IterTuple = hamon::tuple<
		hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, First>>,
		hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, Vs>>...>;

private:
	HAMON_NO_UNIQUE_ADDRESS hamon::tuple<First, Vs...> m_bases;
	
private:
	// [range.cartesian.iterator], class template cartesian_product_view​::​iterator
	template <bool Const>
	class iterator
	{
	private:
		friend cartesian_product_view;

		using Parent = hamon::ranges::detail::maybe_const<Const, cartesian_product_view>;

		Parent* m_parent = nullptr;
		IterTuple<Const> m_current;

	public:
		using iterator_category = hamon::input_iterator_tag;
		using iterator_concept  =
			hamon::conditional_t<hamon::ranges::detail::cartesian_product_is_random_access_t<Const, First, Vs...>::value,
				hamon::random_access_iterator_tag,
			hamon::conditional_t<hamon::ranges::detail::cartesian_product_is_bidirectional_t<Const, First, Vs...>::value,
				hamon::bidirectional_iterator_tag,
			hamon::conditional_t<hamon::ranges::forward_range_t<hamon::ranges::detail::maybe_const<Const, First>>::value,
				hamon::forward_iterator_tag,
				hamon::input_iterator_tag
			>>>;
		using value_type = hamon::tuple<
			hamon::ranges::range_value_t<hamon::ranges::detail::maybe_const<Const, First>>,
			hamon::ranges::range_value_t<hamon::ranges::detail::maybe_const<Const, Vs>>...>;
		using reference = hamon::tuple<
			hamon::ranges::range_reference_t<hamon::ranges::detail::maybe_const<Const, First>>,
			hamon::ranges::range_reference_t<hamon::ranges::detail::maybe_const<Const, Vs>>...>;

		// TODO
		// [range.cartesian.iterator]/3
		// Recommended practice: iterator​::​difference_type should be the smallest signed-integer-like type
		// that is sufficiently wide to store the product of the maximum sizes of all underlying ranges
		// if such a type exists.
		using difference_type = Difference<Const>;

		iterator() = default;

		template <bool C2 = Const,
			typename = hamon::enable_if_t<hamon::conjunction<
				hamon::bool_constant<C2>,
				hamon::convertible_to_t<hamon::ranges::iterator_t<First>, hamon::ranges::iterator_t<First const>>,
				hamon::convertible_to_t<hamon::ranges::iterator_t<Vs>, hamon::ranges::iterator_t<Vs const>>...
			>::value>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i)
			// [range.cartesian.iterator]/11
			: m_parent(i.m_parent)
			, m_current(hamon::move(i.m_current))
		{}

	private:
		struct dereference_fn
		{
			template <typename I>
			HAMON_CXX11_CONSTEXPR auto operator()(I& i) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(*i)
		};

	public:
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator*() const
		->decltype(hamon::ranges::detail::tuple_transform(dereference_fn{}, m_current))
		{
			// [range.cartesian.iterator]/12
			return hamon::ranges::detail::tuple_transform(dereference_fn{}, m_current);
		}

		HAMON_CXX14_CONSTEXPR iterator& operator++()
		{
			// [range.cartesian.iterator]/13
			next();
			return *this;
		}

	private:
		HAMON_CXX14_CONSTEXPR void post_increment(hamon::detail::overload_priority<0>)
		{
			// [range.cartesian.iterator]/14
			++*this;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<hamon::ranges::detail::maybe_const<C2, First>>::value>>
		HAMON_CXX14_CONSTEXPR iterator post_increment(hamon::detail::overload_priority<1>)
		{
			// [range.cartesian.iterator]/15
			auto tmp = *this;
			++*this;
			return tmp;
		}

	public:
		HAMON_CXX14_CONSTEXPR auto operator++(int)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			post_increment(hamon::detail::overload_priority<1>{}))

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_product_is_bidirectional_t<C2, First, Vs...>::value>>
		HAMON_CXX14_CONSTEXPR iterator& operator--()
		{
			// [range.cartesian.iterator]/16
			prev();
			return *this;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_product_is_bidirectional_t<C2, First, Vs...>::value>>
		HAMON_CXX14_CONSTEXPR iterator operator--(int)
		{
			// [range.cartesian.iterator]/17
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_product_is_random_access_t<C2, First, Vs...>::value>>
		HAMON_CXX14_CONSTEXPR iterator& operator+=(difference_type x)
		{
			advance(x);

			// [range.cartesian.iterator]/21
			return *this;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_product_is_random_access_t<C2, First, Vs...>::value>>
		HAMON_CXX14_CONSTEXPR iterator& operator-=(difference_type x)
		{
			// [range.cartesian.iterator]/23
			*this += -x;
			return *this;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_product_is_random_access_t<C2, First, Vs...>::value>>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		reference operator[](difference_type n) const
		{
			// [range.cartesian.iterator]/24
			return *((*this) + n);
		}

	private:
		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::equality_comparable_t<hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<C2, First>>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y)
		{
			// [range.cartesian.iterator]/25
			return x.m_current == y.m_current;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::equality_comparable_t<hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<C2, First>>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y)
		{
			return !(x == y);
		}
#endif

		template <hamon::size_t N, hamon::size_t I = 0>
		struct is_end
		{
			static HAMON_CXX11_CONSTEXPR bool
			invoke(iterator const& x)
			{
				// [range.cartesian.iterator]/26
				return (hamon::adl_get<I>(x.m_current) == hamon::ranges::end(hamon::adl_get<I>(x.m_parent->m_bases))) ?
					true : is_end<N, I + 1>::invoke(x);
			}
		};

		template <hamon::size_t I>
		struct is_end<I, I>
		{
			static HAMON_CXX11_CONSTEXPR bool
			invoke(iterator const&)
			{
				return false;
			}
		};

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, hamon::default_sentinel_t)
		{
			// [range.cartesian.iterator]/26
			return is_end<1 + sizeof...(Vs)>::invoke(x);
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, hamon::default_sentinel_t y)
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(hamon::default_sentinel_t x, iterator const& y)
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(hamon::default_sentinel_t x, iterator const& y)
		{
			return !(x == y);
		}
#endif

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::all_random_access_t<C2, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator<=>(iterator const& x, iterator const& y)
		{
			// [range.cartesian.iterator]/27
			return x.m_current <=> y.m_current;
		}

#else
		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::all_random_access_t<C2, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<(iterator const& x, iterator const& y)
		{
			return x.m_current < y.m_current;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::all_random_access_t<C2, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>(iterator const& x, iterator const& y)
		{
			return y < x;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::all_random_access_t<C2, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<=(iterator const& x, iterator const& y)
		{
			return !(x > y);
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::all_random_access_t<C2, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>=(iterator const& x, iterator const& y)
		{
			return !(x < y);
		}
#endif

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_product_is_random_access_t<C2, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator const& x, difference_type y)
		{
			// [range.cartesian.iterator]/28
			return iterator(x) += y;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_product_is_random_access_t<C2, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type x, iterator const& y)
		{
			// [range.cartesian.iterator]/29
			return y + x;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_product_is_random_access_t<C2, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator const& x, difference_type y)
		{
			// [range.cartesian.iterator]/30
			return iterator(x) -= y;
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_is_sized_sentinel_t<C2, hamon::ranges::iterator_t, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y)
		{
			// [range.cartesian.iterator]/31
			return x.distance_from(y.m_current);
		}

		using EndTuple = hamon::tuple<
			hamon::ranges::sentinel_t<hamon::ranges::detail::maybe_const<Const, First>>,
			hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, Vs>>...>;

		// [range.cartesian.iterator]/32
		template <hamon::size_t... Is>
		HAMON_CXX11_CONSTEXPR EndTuple
		end_tuple(hamon::index_sequence<Is...>) const
		{
			return EndTuple
			{
				hamon::ranges::end(hamon::adl_get<0>(m_parent->m_bases)),
				hamon::ranges::begin(hamon::adl_get<Is + 1>(m_parent->m_bases))...
			};
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_is_sized_sentinel_t<C2, hamon::ranges::sentinel_t, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& i, hamon::default_sentinel_t)
		{
			// [range.cartesian.iterator]/33
			return i.distance_from(i.end_tuple(hamon::make_index_sequence<sizeof...(Vs)>{}));
		}

		template <bool C2 = Const, typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_is_sized_sentinel_t<C2, hamon::ranges::sentinel_t, First, Vs...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(hamon::default_sentinel_t s, iterator const& i)
		{
			// [range.cartesian.iterator]/34
			return -(i - s);
		}

		// [range.cartesian.iterator]/36
		template <typename Seq>
		struct is_iter_move_noexcept;

		template <hamon::size_t... N>
		struct is_iter_move_noexcept<hamon::index_sequence<N...>>
			: hamon::conjunction<
				hamon::is_nothrow_move_constructible<
					hamon::ranges::range_rvalue_reference_t<
						hamon::ranges::detail::maybe_const<Const, First>
					>
				>,
				hamon::is_nothrow_move_constructible<
					hamon::ranges::range_rvalue_reference_t<
						hamon::ranges::detail::maybe_const<Const, Vs>
					>
				>...,
				hamon::bool_constant<
					HAMON_NOEXCEPT_EXPR(hamon::ranges::iter_move(
						hamon::adl_get<N>(hamon::declval<iterator const&>().m_current)))
				>...
			>
		{};

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto iter_move(iterator const& i)
			HAMON_NOEXCEPT_IF(is_iter_move_noexcept<hamon::make_index_sequence<1 + sizeof...(Vs)>>::value)
		->decltype(hamon::ranges::detail::tuple_transform(hamon::ranges::iter_move, hamon::declval<IterTuple<Const> const&>()))
		{
			// [range.cartesian.iterator]/35
			return hamon::ranges::detail::tuple_transform(hamon::ranges::iter_move, i.m_current);
		}

		// [range.cartesian.iterator]/38
		template <typename Seq>
		struct is_iter_swap_noexcept;

		template <hamon::size_t... N>
		struct is_iter_swap_noexcept<hamon::index_sequence<N...>>
			: hamon::conjunction<
				hamon::bool_constant<
					HAMON_NOEXCEPT_EXPR(hamon::ranges::iter_swap(
						hamon::adl_get<N>(hamon::declval<iterator const&>().m_current),
						hamon::adl_get<N>(hamon::declval<iterator const&>().m_current)))
				>...
			>
		{};

		template <bool C2 = Const,
			typename = hamon::enable_if_t<hamon::conjunction<
				hamon::indirectly_swappable_t<hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<C2, First>>>,
				hamon::indirectly_swappable_t<hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<C2, Vs>>>...
			>::value>>
		friend HAMON_CXX14_CONSTEXPR void iter_swap(iterator const& l, iterator const& r)
			HAMON_NOEXCEPT_IF(is_iter_swap_noexcept<hamon::make_index_sequence<1 + sizeof...(Vs)>>::value)
		{
			hamon::ranges::detail::tuple_for_each2(hamon::ranges::iter_swap, l.m_current, r.m_current);
		}

	private:
		// [range.cartesian.iterator]/5
		template <typename Iter, hamon::size_t N>
		struct next_impl
		{
			static HAMON_CXX14_CONSTEXPR void invoke(Iter& x)
			{
				auto& bases = hamon::adl_get<N>(x.m_parent->m_bases);
				auto& it = hamon::adl_get<N>(x.m_current);
				++it;
				if (it == hamon::ranges::end(bases))
				{
					it = hamon::ranges::begin(bases);
					next_impl<Iter, N - 1>::invoke(x);
				}
			}
		};

		template <typename Iter>
		struct next_impl<Iter, 0>
		{
			static HAMON_CXX14_CONSTEXPR void invoke(Iter& x)
			{
				auto& it = hamon::adl_get<0>(x.m_current);
				++it;
			}
		};

		template <hamon::size_t N = sizeof...(Vs)>
		HAMON_CXX14_CONSTEXPR void next()
		{
			next_impl<iterator, N>::invoke(*this);
		}

		// [range.cartesian.iterator]/6
		template <typename Iter, hamon::size_t N>
		struct prev_impl
		{
			static HAMON_CXX14_CONSTEXPR void invoke(Iter& x)
			{
				auto& bases = hamon::adl_get<N>(x.m_parent->m_bases);
				auto& it = hamon::adl_get<N>(x.m_current);
				if (it == hamon::ranges::begin(bases))
				{
					it = hamon::ranges::detail::cartesian_common_arg_end(bases);
					prev_impl<Iter, N - 1>::invoke(x);
				}
				--it;
			}
		};

		template <typename Iter>
		struct prev_impl<Iter,  0>
		{
			static HAMON_CXX14_CONSTEXPR void invoke(Iter& x)
			{
				auto& it = hamon::adl_get<0>(x.m_current);
				--it;
			}
		};

		template <hamon::size_t N = sizeof...(Vs)>
		HAMON_CXX14_CONSTEXPR void prev()
		{
			prev_impl<iterator, N>::invoke(*this);
		}

		template <typename Iter, hamon::size_t N>
		struct advance_impl
		{
			static HAMON_CXX14_CONSTEXPR void invoke(Iter& i, difference_type x)
			{
				if (x == 0)
				{
					return;
				}

				auto& bases = hamon::adl_get<N>(i.m_parent->m_bases);
				auto& it = hamon::adl_get<N>(i.m_current);
				using I = hamon::remove_reference_t<decltype(it)>;
				auto size = static_cast<difference_type>(hamon::ranges::size(bases));
				auto first = hamon::ranges::begin(bases);
				auto pos = it - first;
				auto new_pos = (pos + x) % size;
				auto next_x  = (pos + x) / size;
				if (new_pos < 0)
				{
					new_pos += size;
					next_x -= 1;
				}
				it = first + static_cast<hamon::iter_difference_t<I>>(new_pos);
				advance_impl<Iter, N - 1>::invoke(i, next_x);
			}
		};

		template <typename Iter>
		struct advance_impl<Iter,  0>
		{
			static HAMON_CXX14_CONSTEXPR void invoke(Iter& i, difference_type x)
			{
				auto& it = hamon::adl_get<0>(i.m_current);
				using I = hamon::remove_reference_t<decltype(it)>;
				it += static_cast<hamon::iter_difference_t<I>>(x);
			}
		};

		HAMON_CXX14_CONSTEXPR void advance(difference_type x)
		{
			// [range.cartesian.iterator]/19
			HAMON_ASSERT(x >= hamon::ranges::distance(*this, hamon::ranges::begin(*m_parent)));
			HAMON_ASSERT(x <= hamon::ranges::distance(*this, hamon::ranges::end(*m_parent)));

			advance_impl<iterator, sizeof...(Vs)>::invoke(*this, x);
		}

		template <typename Iter, hamon::size_t N>
		struct distance_from_impl
		{
			template <typename Tuple>
			static HAMON_CXX11_CONSTEXPR difference_type invoke(Iter const& x, Tuple const& t)
			{
				return static_cast<difference_type>(hamon::ranges::size(hamon::adl_get<N>(x.m_parent->m_bases))) *
					distance_from_impl<Iter, N - 1>::invoke(x, t) +
					static_cast<difference_type>(hamon::adl_get<N>(x.m_current) - hamon::adl_get<N>(t));
			}
		};

		template <typename Iter>
		struct distance_from_impl<Iter, 0>
		{
			template <typename Tuple>
			static HAMON_CXX11_CONSTEXPR difference_type invoke(Iter const& x, Tuple const& t)
			{
				return static_cast<difference_type>(hamon::adl_get<0>(x.m_current) - hamon::adl_get<0>(t));
			}
		};

		template <hamon::size_t N = sizeof...(Vs), typename Tuple>
		HAMON_CXX11_CONSTEXPR difference_type distance_from(Tuple const& t) const
		{
			return distance_from_impl<iterator, N>::invoke(*this, t);
		}

		HAMON_CXX11_CONSTEXPR iterator(Parent& parent, IterTuple<Const> current)
			// [range.cartesian.iterator]/10
			: m_parent(hamon::addressof(parent))
			, m_current(hamon::move(current))
		{}
	};

public:
	HAMON_CXX11_CONSTEXPR cartesian_product_view() = default;
	
	HAMON_CXX11_CONSTEXPR explicit
	cartesian_product_view(First first_base, Vs... bases)
		HAMON_NOEXCEPT_IF(hamon::conjunction<	// noexcept as an extension
			hamon::is_nothrow_move_constructible<First>,
			hamon::is_nothrow_move_constructible<Vs>...>::value)
		// [range.cartesian.view]/1
		: m_bases(hamon::move(first_base), hamon::move(bases)...)
	{}

	template <typename First2 = First,
		typename = hamon::enable_if_t<!hamon::conjunction<
			hamon::ranges::detail::simple_view_t<First2>,
			hamon::ranges::detail::simple_view_t<Vs>...
		>::value>
	>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator<false> begin()
	{
		// [range.cartesian.view]/2
		return iterator<false>(*this, hamon::ranges::detail::tuple_transform(hamon::ranges::begin, m_bases));
	}

	template <typename First2 = First,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::range_t<First2 const>,
			hamon::ranges::range_t<Vs const>...
		>::value>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const
	{
		// [range.cartesian.view]/3
		return iterator<true>(*this, hamon::ranges::detail::tuple_transform(hamon::ranges::begin, m_bases));
	}

private:
	template <hamon::size_t N, hamon::size_t I = 0>
	struct is_empty_impl
	{
		template <typename Bases>
		static HAMON_CXX11_CONSTEXPR bool
		invoke(Bases& bases)
		{
			// [range.cartesian.view]/4.2
			return hamon::ranges::empty(hamon::adl_get<I + 1>(bases)) ? true : is_empty_impl<N, I + 1>::invoke(bases);
		}
	};

	template <hamon::size_t I>
	struct is_empty_impl<I, I>
	{
		template <typename Bases>
		static HAMON_CXX11_CONSTEXPR bool
		invoke(Bases&)
		{
			return false;
		}
	};

	template <typename This, typename Bases, hamon::size_t... Is,
		bool Const = hamon::is_const<Bases>::value	// [range.cartesian.view]/4.1
	>
	static HAMON_CXX14_CONSTEXPR iterator<Const>
	end_impl(This* this_, Bases& bases, hamon::index_sequence<Is...>)
	{
		// [range.cartesian.view]/4.2
		bool const is_empty = is_empty_impl<sizeof...(Is)>::invoke(bases);

		// [range.cartesian.view]/4.3
		IterTuple<Const> const iter_tuple = 
		{
			(is_empty ? hamon::ranges::begin(hamon::adl_get<0>(bases)) : hamon::ranges::detail::cartesian_common_arg_end(hamon::adl_get<0>(bases))),
			hamon::ranges::begin(hamon::adl_get<Is + 1>(bases))...
		};

		// [range.cartesian.view]/5
		return iterator<Const>(*this_, hamon::move(iter_tuple));
	}

public:
	template <typename First2 = First,
		typename = hamon::enable_if_t<!hamon::conjunction<
			hamon::ranges::detail::simple_view_t<First2>,
			hamon::ranges::detail::simple_view_t<Vs>...
		>::value>,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::cartesian_product_is_common_t<First2, Vs...>::value
		>
	>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator<false> end()
	{
		return end_impl(this, m_bases, hamon::make_index_sequence<sizeof...(Vs)>{});
	}

private:
	template <typename First2 = First, typename = hamon::enable_if_t<
		hamon::ranges::detail::cartesian_product_is_common_t<First2 const, Vs const...>::value>>
	HAMON_CXX11_CONSTEXPR iterator<true>
	end_impl(hamon::detail::overload_priority<1>) const
	{
		return end_impl(this, m_bases, hamon::make_index_sequence<sizeof...(Vs)>{});
	}
	
	HAMON_CXX11_CONSTEXPR hamon::default_sentinel_t
	end_impl(hamon::detail::overload_priority<0>) const HAMON_NOEXCEPT
	{
		// [range.cartesian.view]/6
		return hamon::default_sentinel;
	}

public:
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto end() const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		end_impl(hamon::detail::overload_priority<1>{}))

private:
	// [range.cartesian.view]/11
	template <hamon::size_t N, hamon::size_t I = 0>
	struct size_impl
	{
		template <typename Bases, bool Const = hamon::is_const<Bases>::value>
		static HAMON_CXX11_CONSTEXPR SizeType<Const>
		invoke(Bases& bases)
		{
			// [range.cartesian.view]/10
			// TODO オーバーフローチェック

			// [range.cartesian.view]/9
			return static_cast<SizeType<Const>>(hamon::ranges::size(hamon::adl_get<I>(bases))) *
				size_impl<N, I + 1>::invoke(bases);
		}
	};

	template <hamon::size_t I>
	struct size_impl<I, I>
	{
		template <typename Bases, bool Const = hamon::is_const<Bases>::value>
		static HAMON_CXX11_CONSTEXPR SizeType<Const>
		invoke(Bases&)
		{
			return static_cast<SizeType<Const>>(1);
		}
	};

public:
	template <typename First2 = First, typename = hamon::enable_if_t<
		hamon::ranges::detail::cartesian_product_is_sized_t<First2, Vs...>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto size()
	->decltype(size_impl<1 + sizeof...(Vs)>::invoke(hamon::declval<hamon::tuple<First2, Vs...>&>()))
	{
		return size_impl<1 + sizeof...(Vs)>::invoke(m_bases);
	}

	template <typename First2 = First, typename = hamon::enable_if_t<
		hamon::ranges::detail::cartesian_product_is_sized_t<First2 const, Vs const...>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto size() const
	->decltype(size_impl<1 + sizeof...(Vs)>::invoke(hamon::declval<hamon::tuple<First2, Vs...> const&>()))
	{
		return size_impl<1 + sizeof...(Vs)>::invoke(m_bases);
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename... Vs>
cartesian_product_view(Vs&&...)
	-> cartesian_product_view<hamon::views::all_t<Vs>...>;

#else

// C++20 Concepts が使えないとき、↑の書き方だと
// Deduction guide より普通のコンストラクタのほうが優先して適用されてしまう。

template <typename First, typename... Vs>
cartesian_product_view(First&&, Vs&&...)
	-> cartesian_product_view<hamon::views::all_t<First>, hamon::views::all_t<Vs>...>;

#endif

#endif

}	// inline namespace cartesian_product_view_ns

namespace views {

namespace detail {

// 26.7.32.1 Overview[range.cartesian.overview]

struct cartesian_product_fn
{
	// [range.cartesian.overview]/2.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()() const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::views::single(hamon::tuple<>{}))

	// [range.cartesian.overview]/2.2
	template <typename... Rs>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()(Rs&&... rs) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::cartesian_product_view<hamon::views::all_t<Rs>...>{hamon::forward<Rs>(rs)...})
};

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::cartesian_product_fn cartesian_product{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

#endif

#endif // HAMON_RANGES_ADAPTORS_CARTESIAN_PRODUCT_VIEW_HPP
