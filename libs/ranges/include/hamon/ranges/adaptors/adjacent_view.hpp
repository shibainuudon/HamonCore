/**
 *	@file	adjacent_view.hpp
 *
 *	@brief	adjacent_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_ADJACENT_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_ADJACENT_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_zip) && (__cpp_lib_ranges_zip >= 202110L)

#include <hamon/cstddef/size_t.hpp>

namespace hamon {
namespace ranges {

using std::ranges::adjacent_view;

namespace views {

using std::ranges::views::adjacent;
using std::ranges::views::pairwise;

// variable templates が使える場合も使えない場合も、
// hamon::views::adjacent_t<N>{}
// の形で使えるようにする。
template <hamon::size_t N>
using adjacent_t = decltype(adjacent<N>);

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/detail/tuple_transform.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/array.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

#define HAMON_NOEXCEPT_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	{ return __VA_ARGS__; }

namespace hamon {
namespace ranges {

namespace detail {

// adjacent_view::iteratorのprivateメンバに、
// adjacent_transform_viewからアクセスする必要があるので、そのためのクラス
struct adjacent_view_iterator_access
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

inline namespace adjacent_view_ns
{

// 26.7.26.2 Class template adjacent_view[range.adjacent.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::forward_range V, hamon::size_t N>
	requires hamon::ranges::view<V> && (N > 0)
#else
template <typename V, hamon::size_t N,
	typename = hamon::enable_if_t<
		hamon::ranges::forward_range_t<V>::value &&
		hamon::ranges::view_t<V>::value &&
		(N > 0)>>
#endif
class adjacent_view : public hamon::ranges::view_interface<adjacent_view<V, N>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();

	struct as_sentinel {};

	// [range.adjacent.iterator], class template adjacent_view​::​iterator
	template <bool Const>
	class iterator
	{
	private:
		friend adjacent_view;
		friend hamon::ranges::detail::adjacent_view_iterator_access;

		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseIter = hamon::ranges::iterator_t<Base>;

		hamon::array<BaseIter, N> m_current{};

		HAMON_CXX14_CONSTEXPR
		iterator(BaseIter first, hamon::ranges::sentinel_t<Base> last)
		{
			// [range.adjacent.iterator]/3
			m_current[0] = first;
			for (hamon::size_t i = 1; i < N; ++i)
			{
				hamon::ranges::advance(first, 1, last);
				m_current[i] = first;
			}
		}

		// [range.adjacent.iterator]/4
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR
		iterator(as_sentinel, BaseIter first, BaseIter last, hamon::detail::overload_priority<1>)
		{
			m_current[N-1] = last;
			for (hamon::size_t i = 1; i < N; ++i)
			{
				hamon::ranges::advance(last, -1, first);
				m_current[N-1 - i] = last;
			}
		}

		HAMON_CXX14_CONSTEXPR
		iterator(as_sentinel, BaseIter, BaseIter last, hamon::detail::overload_priority<0>)
		{
			m_current.fill(last);
		}

		HAMON_CXX11_CONSTEXPR
		iterator(as_sentinel, BaseIter first, BaseIter last)
			: iterator(as_sentinel{}, first, last, hamon::detail::overload_priority<1>{})
		{}

		template <typename T, hamon::size_t>
		using repeated_tuple_helper = T;

		template <typename T, typename Seq>
		struct repeated_tuple_impl;

		template <typename T, hamon::size_t... Is>
		struct repeated_tuple_impl<T, hamon::index_sequence<Is...>>
		{
			using type = hamon::tuple<repeated_tuple_helper<T, Is>...>;
		};

		template <typename T, hamon::size_t M>
		using repeated_tuple =
			typename repeated_tuple_impl<T, hamon::make_index_sequence<M>>::type;

	public:
		using iterator_category = hamon::input_iterator_tag;
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::random_access_range_t<Base>::value,
				hamon::random_access_iterator_tag,
			hamon::conditional_t<hamon::ranges::bidirectional_range_t<Base>::value,
				hamon::bidirectional_iterator_tag,
				hamon::forward_iterator_tag
			>>;
		using value_type = repeated_tuple<hamon::ranges::range_value_t<Base>, N>;
		using difference_type = hamon::ranges::range_difference_t<Base>;

		iterator() = default;

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<
					hamon::ranges::iterator_t<V>,
					hamon::ranges::iterator_t<B2>
				>::value>>
		HAMON_CXX14_CONSTEXPR
		iterator(iterator<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_convertible<hamon::ranges::iterator_t<V>, BaseIter>::value)
		{
			// [range.adjacent.iterator]/5
			for (hamon::size_t j = 0; j < N; ++j)
			{
				m_current[j] = hamon::move(i.m_current[j]);
			}
		}

	private:
		struct dereference_fn
		{
			template <typename T>
			HAMON_CXX11_CONSTEXPR auto operator()(T& i) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(*i)	// noexcept as an extension
		};

	public:
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator*() const
			// [range.adjacent.iterator]/6
			HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
				hamon::ranges::detail::tuple_transform(dereference_fn{}, m_current))

		HAMON_CXX14_CONSTEXPR iterator&
		operator++() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			++m_current.back())
		{
			// [range.adjacent.iterator]/7
			// Preconditions: m_current.back() is incrementable.
			// TODO

			// [range.adjacent.iterator]/8
			for (auto& it : m_current)
			{
				++it;
			}

			// [range.adjacent.iterator]/9
			return *this;
		}

		HAMON_CXX14_CONSTEXPR iterator
		operator++(int) HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_copy_constructible<iterator>::value &&
			HAMON_NOEXCEPT_EXPR(++*this))
		{
			// [range.adjacent.iterator]/10
			auto tmp = *this;
			++*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator--() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			--m_current.front())
		{
			// [range.adjacent.iterator]/11
			// Preconditions: m_current.front() is decrementable.
			// TODO

			// [range.adjacent.iterator]/12
			for (auto& it : m_current)
			{
				--it;
			}

			// [range.adjacent.iterator]/13
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator
		operator--(int) HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_copy_constructible<iterator>::value &&
			HAMON_NOEXCEPT_EXPR(--*this))
		{
			// [range.adjacent.iterator]/14
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator+=(difference_type x)
			HAMON_NOEXCEPT_IF_EXPR(m_current.back() += x)	// noexcept as an extension
		{
			// [range.adjacent.iterator]/15
			// Preconditions: m_current.back() + x has well-defined behavior.
			// TODO

			// [range.adjacent.iterator]/16
			for (auto& it : m_current)
			{
				it += x;
			}

			// [range.adjacent.iterator]/17
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator-=(difference_type x)
			HAMON_NOEXCEPT_IF_EXPR(m_current.front() -= x)	// noexcept as an extension
		{
			// [range.adjacent.iterator]/18
			// Preconditions: m_current.front() - x has well-defined behavior.
			// TODO

			// [range.adjacent.iterator]/19
			for (auto& it : m_current)
			{
				it -= x;
			}

			// [range.adjacent.iterator]/20
			return *this;
		}

	private:
		struct subscript_fn
		{
			difference_type const& n;

			template <typename T>
			HAMON_CXX11_CONSTEXPR auto operator()(T& i) const
			HAMON_NOEXCEPT_DECLTYPE_RETURN(i[n])	// noexcept as an extension
		};

		template <typename Current>
		HAMON_CXX11_CONSTEXPR
		auto subscript_impl(difference_type n, Current const& current, hamon::detail::overload_priority<1>) const
			// [range.adjacent.iterator]/21
			HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
				hamon::ranges::detail::tuple_transform(subscript_fn{n}, current))
		
		template <typename Current>
		void subscript_impl(difference_type, Current const&, hamon::detail::overload_priority<0>) const;

	public:
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator[](difference_type n) const
			// [range.adjacent.iterator]/21
			HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
				subscript_impl(n, m_current, hamon::detail::overload_priority<1>{}))

	private:
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y)
			// [range.adjacent.iterator]/22
			HAMON_NOEXCEPT_RETURN(x.m_current.back() == y.m_current.back())	// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))	// noexcept as an extension
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<(iterator const& x, iterator const& y)
			// [range.adjacent.iterator]/23
			HAMON_NOEXCEPT_RETURN(x.m_current.back() < y.m_current.back())	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>(iterator const& x, iterator const& y)
			// [range.adjacent.iterator]/24
			HAMON_NOEXCEPT_RETURN(y < x)	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<=(iterator const& x, iterator const& y)
			// [range.adjacent.iterator]/25
			HAMON_NOEXCEPT_RETURN(!(y < x))	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>=(iterator const& x, iterator const& y)
			// [range.adjacent.iterator]/26
			HAMON_NOEXCEPT_RETURN(!(x < y))	// noexcept as an extension

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator<=>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current.back() <=> y.m_current.back())	// noexcept as an extension
			requires hamon::ranges::random_access_range<Base> &&
				hamon::three_way_comparable<BaseIter>
		{
			// [range.adjacent.iterator]/27
			return x.m_current.back() <=> y.m_current.back();
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator const& i, difference_type n)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::declval<iterator&>() += n) &&
				hamon::is_nothrow_copy_constructible<iterator>::value)
		{
			// [range.adjacent.iterator]/28
			auto r = i;
			r += n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type n, iterator const& i)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::declval<iterator&>() += n) &&
				hamon::is_nothrow_copy_constructible<iterator>::value)
		{
			// [range.adjacent.iterator]/28
			auto r = i;
			r += n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator const& i, difference_type n)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::declval<iterator&>() -= n) &&
				hamon::is_nothrow_copy_constructible<iterator>::value)
		{
			// [range.adjacent.iterator]/29
			auto r = i;
			r -= n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::sized_sentinel_for, BaseIter, BaseIter2, BaseIter)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y)
			// [range.adjacent.iterator]/30
			HAMON_NOEXCEPT_RETURN(x.m_current.back() - y.m_current.back())	// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto iter_move(iterator const& i)
			// [range.adjacent.iterator]/32
			HAMON_NOEXCEPT_IF(
				HAMON_NOEXCEPT_EXPR(hamon::ranges::iter_move(hamon::declval<BaseIter const&>())) &&
				hamon::is_nothrow_move_constructible<hamon::ranges::range_rvalue_reference_t<Base>>::value)
		->decltype(hamon::ranges::detail::tuple_transform(hamon::ranges::iter_move, hamon::declval<hamon::array<BaseIter, N> const&>()))
		{
			// [range.adjacent.iterator]/31
			return hamon::ranges::detail::tuple_transform(hamon::ranges::iter_move, i.m_current);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::indirectly_swappable, BaseIter2, BaseIter)>
		friend HAMON_CXX14_CONSTEXPR
		void iter_swap(iterator const& l, iterator const& r)
			// [range.adjacent.iterator]/35
			HAMON_NOEXCEPT_IF_EXPR(
				hamon::ranges::iter_swap(
					hamon::declval<BaseIter>(),
					hamon::declval<BaseIter>()))
		{
			// [range.adjacent.iterator]/33
			// Preconditions: None of the iterators in l.m_current is equal to an iterator in r.m_current
			// TODO

			// [range.adjacent.iterator]/34
			for (hamon::size_t i = 0; i < N; ++i)
			{
				hamon::ranges::iter_swap(l.m_current[i], r.m_current[i]);
			}
		}
	};

	// [range.adjacent.sentinel], class template adjacent_view​::​sentinel
	template <bool Const>
	class sentinel
	{
	private:
		friend adjacent_view;

		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseSent = hamon::ranges::sentinel_t<Base>;

		template <bool OtherConst>
		using BaseIterT =
			hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<OtherConst, V>>;

		template <bool OtherConst>
		using BaseDifferenceT =
			hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<OtherConst, V>>;

		HAMON_NO_UNIQUE_ADDRESS BaseSent m_end{};

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(BaseSent end) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<BaseSent>::value)
			// [range.adjacent.sentinel]/1
			: m_end(hamon::move(end))
		{}

	public:
		sentinel() = default;

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<
					hamon::ranges::sentinel_t<V>,
					hamon::ranges::sentinel_t<B2>
				>::value>>
		HAMON_CXX11_CONSTEXPR
		sentinel(sentinel<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_convertible<hamon::ranges::sentinel_t<V>, BaseSent>::value)
			// [range.adjacent.sentinel]/2
			: m_end(hamon::move(i.m_end))
		{}

	private:
		template <bool OtherConst>
		HAMON_CXX11_CONSTEXPR bool
		equal_impl(iterator<OtherConst> const& x) const
			// [range.adjacent.sentinel]/3
			HAMON_NOEXCEPT_RETURN(x.m_current.back() == m_end)	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_RETURN(y.equal_impl(x))	// noexcept as an extension
		
#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_RETURN(y == x)	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))	// noexcept as an extension
#endif

		template <bool OtherConst>
		HAMON_CXX11_CONSTEXPR BaseDifferenceT<OtherConst>
		distance_impl(iterator<OtherConst> const& x) const
			// [range.adjacent.sentinel]/4
			HAMON_NOEXCEPT_RETURN(x.m_current.back() - m_end)	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		BaseDifferenceT<OtherConst>
		operator-(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_RETURN(y.distance_impl(x))	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		BaseDifferenceT<OtherConst>
		operator-(sentinel const& y, iterator<OtherConst> const& x)
			// [range.adjacent.sentinel]/5
			HAMON_NOEXCEPT_RETURN(-(x - y))	// noexcept as an extension
	};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_CXX11_CONSTEXPR
	adjacent_view()
		requires hamon::default_initializable<V>
	= default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR
	adjacent_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<V>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	adjacent_view(V base) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
		// [range.adjacent.view]/1
		: m_base(hamon::move(base))
	{}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	V base() const& HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<V>::value)
	{
		return m_base;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	V base() && HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
	{
		return hamon::move(m_base);
	}

private:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::range, V2),
		bool Const = hamon::is_const<V2>::value>
	static HAMON_CXX11_CONSTEXPR iterator<Const>
	begin_impl(V2& base, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
			iterator<Const>(hamon::ranges::begin(base), hamon::ranges::end(base)))

	template <typename V2>
	static void
	begin_impl(V2& base, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT;

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto     // nodiscard as an extension
	begin() HAMON_NOEXCEPT_DECLTYPE_RETURN(        // noexcept as an extension
		begin_impl(m_base, hamon::detail::overload_priority<1>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto     // nodiscard as an extension
	begin() const HAMON_NOEXCEPT_DECLTYPE_RETURN(  // noexcept as an extension
		begin_impl(m_base, hamon::detail::overload_priority<1>{}))

private:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::common_range, V2),
		bool Const = hamon::is_const<V2>::value>
	static HAMON_CXX11_CONSTEXPR iterator<Const>
	end_impl(V2& base, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
			iterator<Const>(as_sentinel{}, hamon::ranges::begin(base), hamon::ranges::end(base)))

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::range, V2),
		bool Const = hamon::is_const<V2>::value>
	static HAMON_CXX11_CONSTEXPR sentinel<Const>
	end_impl(V2& base, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
			sentinel<Const>(hamon::ranges::end(base)))

	template <typename V2>
	static void
	end_impl(V2& base, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT;

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto   // nodiscard as an extension
	end() HAMON_NOEXCEPT_DECLTYPE_RETURN(        // noexcept as an extension
		end_impl(m_base, hamon::detail::overload_priority<2>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto   // nodiscard as an extension
	end() const HAMON_NOEXCEPT_DECLTYPE_RETURN(  // noexcept as an extension
		end_impl(m_base, hamon::detail::overload_priority<2>{}))

private:
	template <typename ST>
	static HAMON_CXX11_CONSTEXPR ST
	size_impl2(ST sz) HAMON_NOEXCEPT
	{
		// [range.adjacent.view]/2
		using CT = hamon::common_type_t<ST, hamon::size_t>;
		return static_cast<ST>(
			static_cast<CT>(sz) - hamon::min<CT>(static_cast<CT>(sz), N - 1));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::sized_range, V2)>
	static HAMON_CXX11_CONSTEXPR auto
	size_impl(V2& base, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
			size_impl2(hamon::ranges::size(base)))

	template <typename V2>
	static void
	size_impl(V2& base, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT;

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto    // nodiscard as an extension
	size() HAMON_NOEXCEPT_DECLTYPE_RETURN(		  // noexcept as an extension
		size_impl(m_base, hamon::detail::overload_priority<1>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto    // nodiscard as an extension
	size() const HAMON_NOEXCEPT_DECLTYPE_RETURN(  // noexcept as an extension
		size_impl(m_base, hamon::detail::overload_priority<1>{}))
};

}	// inline namespace adjacent_view_ns

// enable_borrowed_range の特殊化
template <typename V, hamon::size_t N>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(V),
	hamon::ranges::adjacent_view<V, N>);

namespace views {

namespace detail {

// 26.7.26.1 Overview[range.adjacent.overview]

template <hamon::size_t N>
struct adjacent_fn : public hamon::ranges::range_adaptor_closure<adjacent_fn<N>>
{
	// [range.enumerate.overview]/2
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()(R&& r) const
		// [range.enumerate.overview]/2.2
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::adjacent_view<hamon::views::all_t<R>, N>{hamon::forward<R>(r)})
};

template <>
struct adjacent_fn<0> : public hamon::ranges::range_adaptor_closure<adjacent_fn<0>>
{
	// [range.enumerate.overview]/2
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()(R&&) const
		// [range.enumerate.overview]/2.1
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::empty_view<hamon::tuple<>>{})
};

} // namespace detail

inline namespace cpo
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <hamon::size_t N>
HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::adjacent_fn<N> adjacent{};

#endif

// variable templates が使える場合も使えない場合も、
// hamon::views::adjacent_t<N>{}
// の形で使えるようにする。
template <hamon::size_t N>
using adjacent_t = detail::adjacent_fn<N>;

HAMON_INLINE_VAR HAMON_CONSTEXPR
auto pairwise = detail::adjacent_fn<2>{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN
#undef HAMON_NOEXCEPT_RETURN

#endif

#endif // HAMON_RANGES_ADAPTORS_ADJACENT_VIEW_HPP
