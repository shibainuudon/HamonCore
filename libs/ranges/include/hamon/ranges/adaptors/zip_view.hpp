/**
 *	@file	zip_view.hpp
 *
 *	@brief	zip_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_ZIP_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_ZIP_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_zip) && (__cpp_lib_ranges_zip >= 202110L)

namespace hamon {
namespace ranges {

using std::ranges::zip_view;

namespace views {

using std::ranges::views::zip;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
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
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/make_unsigned_like_t.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/algorithm/ranges/any_of.hpp>
#include <hamon/algorithm/ranges/min.hpp>
#include <hamon/cmath/ranges/abs.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace hamon {
namespace ranges {

namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename... Rs>
concept zip_is_common_impl =
	(sizeof...(Rs) == 1 && (hamon::ranges::common_range<Rs> && ...)) ||
	(!(hamon::ranges::bidirectional_range<Rs> && ...) && (hamon::ranges::common_range<Rs> && ...)) ||
	((hamon::ranges::random_access_range<Rs> && ...) && (hamon::ranges::sized_range<Rs> && ...));

template <bool Const, typename... Views>
using zip_is_common_t = hamon::bool_constant<zip_is_common_impl<hamon::ranges::detail::maybe_const<Const, Views>...>>;

template <bool Const, typename... Views>
concept all_random_access =
	(hamon::ranges::random_access_range<hamon::ranges::detail::maybe_const<Const, Views>> && ...);

template <bool Const, typename... Views>
using all_random_access_t = hamon::bool_constant<all_random_access<Const, Views...>>;

template <bool Const, typename... Views>
concept all_bidirectional =
	(hamon::ranges::bidirectional_range<hamon::ranges::detail::maybe_const<Const, Views>> && ...);

template <bool Const, typename... Views>
using all_bidirectional_t = hamon::bool_constant<all_bidirectional<Const, Views...>>;

template <bool Const, typename... Views>
concept all_forward =
	(hamon::ranges::forward_range<hamon::ranges::detail::maybe_const<Const, Views>> && ...);

template <bool Const, typename... Views>
using all_forward_t = hamon::bool_constant<all_forward<Const, Views...>>;

template <bool Const, typename... Views>
concept all_sized =
	(hamon::ranges::sized_range<hamon::ranges::detail::maybe_const<Const, Views>> && ...);

template <bool Const, typename... Views>
using all_sized_t = hamon::bool_constant<all_sized<Const, Views...>>;

template <bool Const, typename... Views>
concept all_range =
	(hamon::ranges::range<hamon::ranges::detail::maybe_const<Const, Views>> && ...);

template <bool Const, typename... Views>
using all_range_t = hamon::bool_constant<all_range<Const, Views...>>;

template <bool Const, typename... Views>
concept all_simple_view =
	(hamon::ranges::detail::simple_view<hamon::ranges::detail::maybe_const<Const, Views>> && ...);

template <bool Const, typename... Views>
using all_simple_view_t = hamon::bool_constant<all_simple_view<Const, Views...>>;

#else

template <typename... Rs>
using zip_is_common_impl = hamon::disjunction<
	hamon::conjunction<
		hamon::bool_constant<sizeof...(Rs) == 1>,
		hamon::conjunction<hamon::ranges::common_range_t<Rs>...>
	>,
	hamon::conjunction<
		hamon::negation<hamon::conjunction<hamon::ranges::bidirectional_range_t<Rs>...>>,
		hamon::conjunction<hamon::ranges::common_range_t<Rs>...>
	>,
	hamon::conjunction<
		hamon::conjunction<hamon::ranges::random_access_range_t<Rs>...>,
		hamon::conjunction<hamon::ranges::sized_range_t<Rs>...>
	>
>;

template <bool Const, typename... Views>
using zip_is_common_t = zip_is_common_impl<hamon::ranges::detail::maybe_const<Const, Views>...>;

template <bool Const, typename... Views>
using all_random_access_t = hamon::conjunction<
	hamon::ranges::random_access_range_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

template <bool Const, typename... Views>
using all_bidirectional_t = hamon::conjunction<
	hamon::ranges::bidirectional_range_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

template <bool Const, typename... Views>
using all_forward_t = hamon::conjunction<
	hamon::ranges::forward_range_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

template <bool Const, typename... Views>
using all_sized_t = hamon::conjunction<
	hamon::ranges::sized_range_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

template <bool Const, typename... Views>
using all_range_t = hamon::conjunction<
	hamon::ranges::range_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

template <bool Const, typename... Views>
using all_simple_view_t = hamon::conjunction<
	hamon::ranges::detail::simple_view_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

#endif

template <typename F>
struct tuple_transform_fn
{
	F& m_f;

	template <typename... Ts>
	HAMON_CXX11_CONSTEXPR auto operator()(Ts&&... elements) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::tuple<hamon::invoke_result_t<F&, Ts>...>(
			hamon::invoke(m_f, hamon::forward<Ts>(elements))...))
};

template <typename F, typename Tuple>
HAMON_CXX11_CONSTEXPR auto tuple_transform(F&& f, Tuple&& t)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	hamon::apply(tuple_transform_fn<F>{f}, hamon::forward<Tuple>(t)))

template <typename... Types>
HAMON_CXX14_CONSTEXPR void swallow(Types...) HAMON_NOEXCEPT {}

template <typename F>
struct tuple_for_each_fn
{
	F& m_f;

	template <typename... Ts>
	HAMON_CXX14_CONSTEXPR auto operator()(Ts&&... elements) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		swallow((hamon::invoke(m_f, hamon::forward<Ts>(elements)), 0)...))
};

template <typename F, typename Tuple>
HAMON_CXX14_CONSTEXPR auto tuple_for_each(F&& f, Tuple&& t)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	hamon::apply(tuple_for_each_fn<F>{f}, hamon::forward<Tuple>(t)))

template <typename F, typename Tuple1, typename Tuple2, hamon::size_t... I>
HAMON_CXX14_CONSTEXPR auto
tuple_for_each2_impl(F&& f, Tuple1&& t1, Tuple2&& t2, hamon::index_sequence<I...>)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	swallow((hamon::invoke(
		hamon::forward<F>(f),
		hamon::adl_get<I>(hamon::forward<Tuple1>(t1)),
		hamon::adl_get<I>(hamon::forward<Tuple2>(t2))), 0)...))

template <typename F, typename Tuple1, typename Tuple2>
HAMON_CXX14_CONSTEXPR auto
tuple_for_each2(F&& f, Tuple1&& t1, Tuple2&& t2)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	tuple_for_each2_impl(
		hamon::forward<F>(f),
		hamon::forward<Tuple1>(t1),
		hamon::forward<Tuple2>(t2),
		hamon::make_index_sequence<std::tuple_size<hamon::remove_reference_t<Tuple1>>::value>{}))

template <typename F, typename Tuple1, typename Tuple2, hamon::size_t... I>
HAMON_CXX11_CONSTEXPR auto
tuple_transform2_impl(F&& f, Tuple1&& t1, Tuple2&& t2, hamon::index_sequence<I...>)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	hamon::make_tuple(
		hamon::invoke(
			hamon::forward<F>(f),
			hamon::adl_get<I>(hamon::forward<Tuple1>(t1)),
			hamon::adl_get<I>(hamon::forward<Tuple2>(t2)))...))

template <typename F, typename Tuple1, typename Tuple2>
HAMON_CXX11_CONSTEXPR auto
tuple_transform2(F&& f, Tuple1&& t1, Tuple2&& t2)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	tuple_transform2_impl(
		hamon::forward<F>(f),
		hamon::forward<Tuple1>(t1),
		hamon::forward<Tuple2>(t2),
		hamon::make_index_sequence<std::tuple_size<hamon::remove_reference_t<Tuple1>>::value>{}))

// zip_view::iteratorのprivateメンバに、
// zip_transform_viewからアクセスする必要があるので、そのためのクラス
struct zip_view_iterator_access
{
	template <typename Iterator>
	static HAMON_CXX11_CONSTEXPR auto
	get_current(Iterator& it) HAMON_NOEXCEPT
	->decltype(it.m_current)
	{
		return it.m_current;
	}
};

}	// namespace detail

// 26.7.24.2 Class template zip_view[range.zip.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range... Views>
	requires (hamon::ranges::view<Views> && ...) && (sizeof...(Views) > 0)
#else
// C++20 Concepts が使えないとき、
// テンプレートパラメータパックはテンプレートパラメータリストの最後でなければならないので、
// enable_if で制約することができない。
template <typename... Views>
#endif
class zip_view : public hamon::ranges::view_interface<zip_view<Views...>>
{
private:
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	static_assert(hamon::conjunction<hamon::ranges::input_range_t<Views>...>::value, "");
	static_assert(hamon::conjunction<hamon::ranges::view_t<Views>...>::value, "");
	static_assert(sizeof...(Views) > 0, "");
#endif

	HAMON_NO_UNIQUE_ADDRESS hamon::tuple<Views...> m_views;

	// [range.zip.iterator]/2
	template <bool Const,
		bool = hamon::ranges::detail::all_forward_t<Const, Views...>::value>
	struct iterator_category_base
	{
		using iterator_category = hamon::input_iterator_tag;
	};

	template <bool Const>
	struct iterator_category_base<Const, false>
	{};

	// [range.zip.iterator], class template zip_view​::​iterator
	template <bool Const>
	class iterator
		: public iterator_category_base<Const>
	{
	private:
		friend zip_view;
		friend hamon::ranges::detail::zip_view_iterator_access;

		template <bool C, typename V>
		using IteratorT = hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<C, V>>;

		using MyTuple = hamon::tuple<IteratorT<Const, Views>...>;

		HAMON_NO_UNIQUE_ADDRESS MyTuple	m_current;
		
	private:
		HAMON_CXX11_CONSTEXPR explicit
		iterator(MyTuple current) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<MyTuple>::value)
			// [range.zip.iterator]/4
			: m_current(hamon::move(current))
		{}

	public:
		//using iterator_category = hamon::input_iterator_tag;		// not always present
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::detail::all_random_access_t<Const, Views...>::value,
				hamon::random_access_iterator_tag,	// [range.zip.iterator]/1.1
			hamon::conditional_t<hamon::ranges::detail::all_bidirectional_t<Const, Views...>::value,
				hamon::bidirectional_iterator_tag,	// [range.zip.iterator]/1.2
			hamon::conditional_t<hamon::ranges::detail::all_forward_t<Const, Views...>::value,
				hamon::forward_iterator_tag,		// [range.zip.iterator]/1.3
				hamon::input_iterator_tag			// [range.zip.iterator]/1.4
			>>>;

		using value_type = hamon::tuple<hamon::ranges::range_value_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;
		using difference_type = hamon::common_type_t<hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

	private:
		struct dereference_fn
		{
			template <typename I>
			HAMON_CXX11_CONSTEXPR auto operator()(I& i) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(*i)
		};

		struct increment_fn
		{
			template <typename I>
			HAMON_CXX14_CONSTEXPR void operator()(I& i) const
				HAMON_NOEXCEPT_IF_EXPR(++i)
			{
				++i;
			}
		};

		struct decrement_fn
		{
			template <typename I>
			HAMON_CXX14_CONSTEXPR void operator()(I& i) const
				HAMON_NOEXCEPT_IF_EXPR(--i)
			{
				--i;
			}
		};

		struct add_assign_fn
		{
			difference_type const& x;

			template <typename I>
			HAMON_CXX14_CONSTEXPR void operator()(I& i) const
				HAMON_NOEXCEPT_IF_EXPR(i += hamon::iter_difference_t<I>(x))
			{
				i += hamon::iter_difference_t<I>(x);
			}
		};

		struct sub_assign_fn
		{
			difference_type const& x;

			template <typename I>
			HAMON_CXX14_CONSTEXPR void operator()(I& i) const
				HAMON_NOEXCEPT_IF_EXPR(i -= hamon::iter_difference_t<I>(x))
			{
				i -= hamon::iter_difference_t<I>(x);
			}
		};

		struct subscript_fn
		{
			difference_type const& n;

			template <typename I>
			HAMON_CXX11_CONSTEXPR auto operator()(I& i) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(
					i[hamon::iter_difference_t<I>(n)])
		};

		struct any_of_fn
		{
			template <typename... Bools>
			HAMON_CXX14_CONSTEXPR bool
			operator()(Bools... equals) const HAMON_NOEXCEPT
			{
				bool const a[] = {equals...};
				return hamon::ranges::any_of(a, hamon::identity{});
			}
		};

		struct equal_fn
		{
			template <typename I, typename J>
			HAMON_CXX11_CONSTEXPR auto
			operator()(I const& i, J const& j) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(bool(i == j))
		};

		struct min_abs_distance_fn
		{
			template <typename... Types>
			HAMON_CXX11_CONSTEXPR auto
			operator()(Types... dist) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(
					hamon::ranges::min({dist...}, hamon::ranges::less{}, hamon::ranges::abs))
		};

		struct distance_fn
		{
			template <typename I, typename J>
			HAMON_CXX11_CONSTEXPR auto
			operator()(I const& i, J const& j) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(difference_type(i - j))
		};

	public:
		iterator() = default;
		
		template <bool C2 = Const,
			typename = hamon::enable_if_t<hamon::conjunction<
				hamon::bool_constant<C2>,
				hamon::convertible_to_t<
					IteratorT<!C2, Views>,
					IteratorT<C2, Views>
				>...
			>::value>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i)
			HAMON_NOEXCEPT_IF(hamon::conjunction<	// noexcept as an extension
				hamon::is_nothrow_convertible<
					IteratorT<!C2, Views>,
					IteratorT<C2, Views>
				>...
			>::value)
			// [range.zip.iterator]/5
			: m_current(hamon::move(i.m_current))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator*() const
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::detail::tuple_transform(dereference_fn{}, m_current))	// noexcept as an extension
		->decltype(hamon::ranges::detail::tuple_transform(dereference_fn{}, m_current))
		{
			// [range.zip.iterator]/6
			return hamon::ranges::detail::tuple_transform(dereference_fn{}, m_current);
		}

	private:
		HAMON_CXX14_CONSTEXPR void
		pre_increment() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::ranges::detail::tuple_for_each(increment_fn{}, m_current))
		{
			// [range.zip.iterator]/7
			hamon::ranges::detail::tuple_for_each(increment_fn{}, m_current);
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_forward_t<C2, Views...>::value>>
		HAMON_CXX14_CONSTEXPR iterator
		post_increment(hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				//hamon::is_nothrow_copy_constructible<iterator>::value &&
				hamon::is_nothrow_copy_constructible<MyTuple>::value &&
				HAMON_NOEXCEPT_EXPR(pre_increment()))
		{
			// [range.zip.iterator]/9
			auto tmp = *this;
			pre_increment();
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR void
		post_increment(hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(pre_increment())	// noexcept as an extension
		{
			// [range.zip.iterator]/8
			pre_increment();
		}

	public:
		HAMON_CXX14_CONSTEXPR iterator&
		operator++() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			pre_increment())
		{
			// [range.zip.iterator]/7
			pre_increment();
			return *this;
		}

		HAMON_CXX14_CONSTEXPR auto operator++(int)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			post_increment(hamon::detail::overload_priority<1>{}))

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_bidirectional_t<C2, Views...>::value>>
		HAMON_CXX14_CONSTEXPR iterator&
		operator--() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::ranges::detail::tuple_for_each(decrement_fn{}, m_current))
		{
			// [range.zip.iterator]/10
			hamon::ranges::detail::tuple_for_each(decrement_fn{}, m_current);
			return *this;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_bidirectional_t<C2, Views...>::value>>
		HAMON_CXX14_CONSTEXPR iterator operator--(int)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				//hamon::is_nothrow_copy_constructible<iterator>::value &&
				hamon::is_nothrow_copy_constructible<MyTuple>::value &&
				HAMON_NOEXCEPT_EXPR(--*this))
		{
			// [range.zip.iterator]/11
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_CXX14_CONSTEXPR iterator&
		operator+=(difference_type x) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::ranges::detail::tuple_for_each(add_assign_fn{x}, m_current))
		{
			// [range.zip.iterator]/12
			hamon::ranges::detail::tuple_for_each(add_assign_fn{x}, m_current);
			return *this;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_CXX14_CONSTEXPR iterator&
		operator-=(difference_type x) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::ranges::detail::tuple_for_each(sub_assign_fn{x}, m_current))
		{
			// [range.zip.iterator]/13
			hamon::ranges::detail::tuple_for_each(sub_assign_fn{x}, m_current);
			return *this;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		operator[](difference_type n) const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::ranges::detail::tuple_transform(subscript_fn{n}, m_current))
		->decltype(hamon::ranges::detail::tuple_transform(subscript_fn{n}, hamon::declval<hamon::tuple<IteratorT<C2, Views>...> const&>()))
		{
			// [range.zip.iterator]/14
			return hamon::ranges::detail::tuple_transform(subscript_fn{n}, m_current);
		}

	private:
		template <bool C2>
		using AllEqualityComparable =
			hamon::conjunction<hamon::equality_comparable_t<IteratorT<C2, Views>>...>;

		template <bool C2,
			typename = hamon::enable_if_t<hamon::ranges::detail::all_bidirectional_t<C2, Views...>::value>>
		static HAMON_CXX11_CONSTEXPR bool
		equal_impl(iterator const& x, iterator const& y, hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current == y.m_current)	// noexcept as an extension
		{
			// [range.zip.iterator]/15.1
			return x.m_current == y.m_current;
		}

		static HAMON_CXX11_CONSTEXPR bool
		equal_impl(iterator const& x, iterator const& y, hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(hamon::apply(	// noexcept as an extension
				any_of_fn{},
				hamon::ranges::detail::tuple_transform2(equal_fn{}, x.m_current, y.m_current)))
		{
			// [range.zip.iterator]/15.2
			return hamon::apply(
				any_of_fn{},
				hamon::ranges::detail::tuple_transform2(equal_fn{}, x.m_current, y.m_current));
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<AllEqualityComparable<C2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
				equal_impl(x, y, hamon::detail::overload_priority<1>{}))
		{
			// [range.zip.iterator]/15
			return equal_impl(x, y, hamon::detail::overload_priority<1>{});
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		operator<=>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current <=> y.m_current)	// noexcept as an extension
		{
			// [range.zip.iterator]/16
			return x.m_current <=> y.m_current;
		}
#else
		template <bool C2 = Const,
			typename = hamon::enable_if_t<AllEqualityComparable<C2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator<(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current < y.m_current)	// noexcept as an extension
		{
			return x.m_current < y.m_current;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y < x)	// noexcept as an extension
		{
			return y < x;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator<=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x > y))	// noexcept as an extension
		{
			return !(x > y);
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator>=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x < y))	// noexcept as an extension
		{
			return !(x < y);
		}
#endif
		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
		operator+(iterator const& i, difference_type n)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_copy_constructible<iterator>::value &&
				HAMON_NOEXCEPT_EXPR(hamon::declval<iterator&>() += n))
		{
			// [range.zip.iterator]/17
			auto r = i;
			r += n;
			return r;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
		operator+(difference_type n, iterator const& i)
			HAMON_NOEXCEPT_IF_EXPR(i + n)	// noexcept as an extension
		{
			// [range.zip.iterator]/17
			return i + n;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access_t<C2, Views...>::value>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
		operator-(iterator const& i, difference_type n)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_copy_constructible<iterator>::value &&
				HAMON_NOEXCEPT_EXPR(hamon::declval<iterator&>() -= n))
		{
			// [range.zip.iterator]/18
			auto r = i;
			r -= n;
			return r;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<hamon::conjunction<
				hamon::sized_sentinel_for_t<
					IteratorT<C2, Views>,
					IteratorT<C2, Views>>...
			>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type	// nodiscard as an extension
		operator-(iterator const& x, iterator const& y) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::apply(
				min_abs_distance_fn{},
				hamon::ranges::detail::tuple_transform2(distance_fn{}, x.m_current, y.m_current)))
		{
			// [range.zip.iterator]/19
			// [range.zip.iterator]/20
			return hamon::apply(
				min_abs_distance_fn{},
				hamon::ranges::detail::tuple_transform2(distance_fn{}, x.m_current, y.m_current));
		}

#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		iter_move(iterator const& i)
			// [range.zip.iterator]/22
			HAMON_NOEXCEPT_IF(
				(hamon::conjunction<hamon::bool_constant<HAMON_NOEXCEPT_EXPR(
					hamon::ranges::iter_move(hamon::declval<IteratorT<Const, Views> const&>()))>...
				>::value) &&
				(hamon::conjunction<
					hamon::is_nothrow_move_constructible<
						hamon::ranges::range_rvalue_reference_t<
							hamon::ranges::detail::maybe_const<Const, Views>>>...
				>::value))
		->decltype(hamon::ranges::detail::tuple_transform(hamon::ranges::iter_move, hamon::declval<MyTuple const&>()))
		{
			// [range.zip.iterator]/21
			return hamon::ranges::detail::tuple_transform(hamon::ranges::iter_move, i.m_current);
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<hamon::conjunction<
				hamon::indirectly_swappable_t<IteratorT<C2, Views>>...
			>::value>>
		friend HAMON_CXX14_CONSTEXPR void
		iter_swap(iterator const& l, iterator const& r)
			// [range.zip.iterator]/24
			HAMON_NOEXCEPT_IF((hamon::conjunction<
				hamon::bool_constant<HAMON_NOEXCEPT_EXPR(
					hamon::ranges::iter_swap(
						hamon::declval<IteratorT<Const, Views>&>(),
						hamon::declval<IteratorT<Const, Views>&>()))>...
			>::value))
		{
			// [range.zip.iterator]/23
			hamon::ranges::detail::tuple_for_each2(hamon::ranges::iter_swap, l.m_current, r.m_current);
		}
#endif
	};

	// [range.zip.sentinel], class template zip_view​::​sentinel
	template <bool Const>
	class sentinel
	{
	private:
		friend zip_view;

		template <bool C, typename V>
		using SentinelT = hamon::ranges::sentinel_t<hamon::ranges::detail::maybe_const<C, V>>;

		template <bool C, typename V>
		using IteratorT = hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<C, V>>;

		template <bool C, typename V>
		using DistanceT = hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<C, V>>;

		using MyTuple = hamon::tuple<SentinelT<Const, Views>...>;

		HAMON_NO_UNIQUE_ADDRESS MyTuple m_end;
		
		HAMON_CXX11_CONSTEXPR explicit
		sentinel(MyTuple end) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<MyTuple>::value)
			// [range.zip.sentinel]/1
			: m_end(end)
		{}

	public:
		sentinel() = default;

		template <bool C2 = Const,
			typename = hamon::enable_if_t<hamon::conjunction<
				hamon::bool_constant<C2>,
				hamon::convertible_to_t<
					SentinelT<!C2, Views>,
					SentinelT<C2, Views>
				>...
			>::value>>
		HAMON_CXX11_CONSTEXPR sentinel(sentinel<!Const> i)
			HAMON_NOEXCEPT_IF(hamon::conjunction<	// noexcept as an extension
				hamon::is_nothrow_convertible<
					SentinelT<!C2, Views>,
					SentinelT<C2, Views>
				>...
			>::value)
			// [range.zip.sentinel]/2
			: m_end(hamon::move(i.m_end))
		{}

	private:
		struct any_of_fn
		{
			template <typename... Bools>
			HAMON_CXX14_CONSTEXPR bool
			operator()(Bools... equals) const HAMON_NOEXCEPT	// noexcept as an extension
			{
				bool const a[] = {equals...};
				return hamon::ranges::any_of(a, hamon::identity{});
			}
		};

		struct equal_fn
		{
			template <typename I, typename J>
			HAMON_CXX11_CONSTEXPR bool
			operator()(I const& i, J const& j) const
				HAMON_NOEXCEPT_IF_EXPR(bool(i == j))	// noexcept as an extension
			{
				return bool(i == j);
			}
		};

		template <bool OtherConst>
		HAMON_CXX11_CONSTEXPR bool
		equal_impl(iterator<OtherConst> const& x) const
		HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::apply(
				any_of_fn{},
				hamon::ranges::detail::tuple_transform2(equal_fn{}, x.m_current, m_end)))
		{
			// [range.zip.sentinel]/3
			return hamon::apply(
				any_of_fn{},
				hamon::ranges::detail::tuple_transform2(equal_fn{}, x.m_current, m_end));
		}

		template <bool OtherConst>
		using AllSentinelFor = hamon::conjunction<
			hamon::sentinel_for_t<
				SentinelT<Const, Views>,
				IteratorT<OtherConst, Views>
			>...>;

		template <bool OtherConst,
			typename = hamon::enable_if_t<AllSentinelFor<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(y.equal_impl(x))	// noexcept as an extension
		{
			return y.equal_impl(x);
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst,
			typename = hamon::enable_if_t<AllSentinelFor<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<AllSentinelFor<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)		// noexcept as an extension
		{
			return y == x;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<AllSentinelFor<OtherConst>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		// [range.zip.sentinel]/5
		template <typename D>
		struct min_abs_distance_fn
		{
			template <typename... Types>
			HAMON_CXX11_CONSTEXPR D operator()(Types... dist) const
				HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
					hamon::ranges::min({dist...}, hamon::ranges::less{}, hamon::ranges::abs))
			{
				return hamon::ranges::min({dist...}, hamon::ranges::less{}, hamon::ranges::abs);
			}
		};

		// [range.zip.sentinel]/4
		template <typename D>
		struct distance_fn
		{
			template <typename I, typename J>
			HAMON_CXX11_CONSTEXPR D operator()(I const& i, J const& j) const
				HAMON_NOEXCEPT_IF_EXPR(D(i - j))	// noexcept as an extension
			{
				return D(i - j);
			}
		};

		template <bool OtherConst,
			typename D = hamon::common_type_t<DistanceT<OtherConst, Views>...>>
		HAMON_CXX11_CONSTEXPR D
		distance_impl(iterator<OtherConst> const& x) const
		HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::apply(
				min_abs_distance_fn<D>{},
				hamon::ranges::detail::tuple_transform2(distance_fn<D>{}, x.m_current, m_end)))
		{
			return hamon::apply(
				min_abs_distance_fn<D>{},
				hamon::ranges::detail::tuple_transform2(distance_fn<D>{}, x.m_current, m_end));
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<hamon::conjunction<
				hamon::sized_sentinel_for_t<
					SentinelT<Const, Views>,
					IteratorT<OtherConst, Views>
				>...
			>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::common_type_t<DistanceT<OtherConst, Views>...>
		operator-(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(y.distance_impl(x))	// noexcept as an extension
		{
			return y.distance_impl(x);
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<hamon::conjunction<
				hamon::sized_sentinel_for_t<
					SentinelT<Const, Views>,
					IteratorT<OtherConst, Views>
				>...
			>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::common_type_t<DistanceT<OtherConst, Views>...>
		operator-(sentinel const& y, iterator<OtherConst> const& x)
			HAMON_NOEXCEPT_IF_EXPR(-(x - y))	// noexcept as an extension
		{
			// [range.zip.sentinel]/6
			return -(x - y);
		}
	};

private:
	template <typename>
	struct always_true : public hamon::true_type {};

	template <typename>
	struct always_false : public hamon::false_type {};

	// begin
	template <typename ViewsTuple, bool Const = hamon::is_const<ViewsTuple>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::all_range_t<Const, Views...>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	begin_impl2(ViewsTuple& views, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		iterator<Const>(hamon::ranges::detail::tuple_transform(hamon::ranges::begin, views)))

	template <typename ViewsTuple>
	static void
	begin_impl2(ViewsTuple& views, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT;

	template <typename ViewsTuple>
	static HAMON_CXX11_CONSTEXPR auto
	begin_impl(ViewsTuple& views)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		begin_impl2(views, hamon::detail::overload_priority<1>{}))

	// end
	template <typename ViewsTuple, bool Const = hamon::is_const<ViewsTuple>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::all_range_t<Const, Views...>::value &&
			!hamon::ranges::detail::zip_is_common_t<Const, Views...>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl2(ViewsTuple& views, hamon::detail::overload_priority<3>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
		sentinel<Const>(hamon::ranges::detail::tuple_transform(hamon::ranges::end, views)))

	template <typename ViewsTuple, bool Const = hamon::is_const<ViewsTuple>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::all_random_access_t<Const, Views...>::value>>
	static HAMON_CXX11_CONSTEXPR iterator<Const>
	end_impl2(ViewsTuple& views, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_IF_EXPR(begin_impl(views))	// noexcept as an extension
	{
		return begin_impl(views) + hamon::iter_difference_t<iterator<Const>>(size_impl(views));
	}

	template <typename ViewsTuple, bool Const = hamon::is_const<ViewsTuple>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::all_range_t<Const, Views...>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl2(ViewsTuple& views, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
		iterator<Const>(hamon::ranges::detail::tuple_transform(hamon::ranges::end, views)))

	template <typename ViewsTuple>
	static void
	end_impl2(ViewsTuple& views, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT;

	template <typename ViewsTuple>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl(ViewsTuple& views)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		end_impl2(views, hamon::detail::overload_priority<3>{}))

	// size
	struct size_fn
	{
		template <typename... Types,
			typename CT = hamon::ranges::detail::make_unsigned_like_t<hamon::common_type_t<Types...>>>
		HAMON_CXX11_CONSTEXPR auto operator()(Types... sizes) const	// noexcept as an extension
			HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::ranges::min({CT(sizes)...}))
	};
	
	template <typename ViewsTuple>
	static HAMON_CXX11_CONSTEXPR auto
	size_impl2(ViewsTuple& views, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		hamon::apply(size_fn{}, hamon::ranges::detail::tuple_transform(hamon::ranges::size, views)))

	template <typename ViewsTuple>
	static void
	size_impl2(ViewsTuple& views, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT;

	template <typename ViewsTuple>
	static HAMON_CXX11_CONSTEXPR auto
	size_impl(ViewsTuple& views)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		size_impl2(views, hamon::detail::overload_priority<1>{}))

public:
	zip_view() = default;

	HAMON_CXX11_CONSTEXPR explicit
	zip_view(Views... views) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::conjunction<hamon::is_nothrow_move_constructible<Views>...>::value)
		// [range.zip.view]/2
		: m_views(hamon::move(views)...)
	{}

	template <typename Dummy = void, bool Const = always_false<Dummy>::value,
		typename = hamon::enable_if_t<
			!hamon::ranges::detail::all_simple_view_t<Const, Views...>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto		// nodiscard as an extension
	begin() HAMON_NOEXCEPT_DECLTYPE_RETURN(			// noexcept as an extension
		begin_impl(m_views))

	template <typename Dummy = void, bool Const = always_true<Dummy>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::all_range_t<Const, Views...>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto		// nodiscard as an extension
	begin() const HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		begin_impl(m_views))

	template <typename Dummy = void, bool Const = always_false<Dummy>::value,
		typename = hamon::enable_if_t<
			!hamon::ranges::detail::all_simple_view_t<Const, Views...>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto		// nodiscard as an extension
	end() HAMON_NOEXCEPT_DECLTYPE_RETURN(			// noexcept as an extension
		end_impl(m_views))

	template <typename Dummy = void, bool Const = always_true<Dummy>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::all_range_t<Const, Views...>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto		// nodiscard as an extension
	end() const HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
		end_impl(m_views))

	template <typename Dummy = void, bool Const = always_false<Dummy>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::all_sized_t<Const, Views...>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto		// nodiscard as an extension
	size() HAMON_NOEXCEPT_DECLTYPE_RETURN(			// noexcept as an extension
		size_impl(m_views))

	template <typename Dummy = void, bool Const = always_true<Dummy>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::all_sized_t<Const, Views...>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto		// nodiscard as an extension
	size() const HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		size_impl(m_views))
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename... Rs>
zip_view(Rs&&...) -> zip_view<hamon::views::all_t<Rs>...>;

#endif

// enable_borrowed_range の特殊化
template <typename... Views>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	hamon::conjunction<hamon::bool_constant<HAMON_RANGES_ENABLE_BORROWED_RANGE(Views)>...>::value,
	hamon::ranges::zip_view<Views...>);

namespace views {

namespace detail {

// 26.7.24.1 Overview[range.zip.overview]

struct zip_fn
{
private:
	static HAMON_CXX11_CONSTEXPR auto
	impl(hamon::detail::overload_priority<1>)
		// [range.zip.overview]/2.1
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::empty_view<hamon::tuple<>>{})

	template <typename... Args,
		typename = hamon::enable_if_t<(sizeof...(Args) > 0)>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(hamon::detail::overload_priority<0>, Args&&... args)
		// [range.zip.overview]/2.2
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::zip_view<
				hamon::views::all_t<Args>...
			>(hamon::forward<Args>(args)...))

public:
	template <typename... Args>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()(Args&&... args) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(impl(
			hamon::detail::overload_priority<1>{},
			hamon::forward<Args>(args)...))
};

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::zip_fn zip{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

#endif

#endif // HAMON_RANGES_ADAPTORS_ZIP_VIEW_HPP
