/**
 *	@file	slide_view.hpp
 *
 *	@brief	slide_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_SLIDE_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_SLIDE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_slide) && (__cpp_lib_ranges_slide >= 202202L)

namespace hamon {
namespace ranges {

using std::ranges::slide_view;

namespace views {

using std::ranges::views::slide;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/counted_view.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/adaptors/detail/cached_value.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/algorithm/ranges/max.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
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

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename V>
concept slide_caches_nothing =
	hamon::ranges::random_access_range<V> &&
	hamon::ranges::sized_range<V>;

template <typename V>
using slide_caches_nothing_t = hamon::bool_constant<slide_caches_nothing<V>>;

template <typename V>
concept slide_caches_last =
	!slide_caches_nothing<V> &&
	hamon::ranges::bidirectional_range<V> &&
	hamon::ranges::common_range<V>;

template <typename V>
using slide_caches_last_t = hamon::bool_constant<slide_caches_last<V>>;

template <typename V>
concept slide_caches_first =
	!slide_caches_nothing<V> &&
	!slide_caches_last<V>;

template <typename V>
using slide_caches_first_t = hamon::bool_constant<slide_caches_first<V>>;

template <typename V>
concept not_slide_caches_first =
	!slide_caches_first<V>;

#else

template <typename V>
using slide_caches_nothing = hamon::conjunction<
	hamon::ranges::random_access_range<V>,
	hamon::ranges::sized_range<V>>;

template <typename V>
using slide_caches_nothing_t = slide_caches_nothing<V>;

template <typename V>
using slide_caches_last = hamon::conjunction<
	hamon::negation<slide_caches_nothing<V>>,
	hamon::ranges::bidirectional_range<V>,
	hamon::ranges::common_range<V>>;

template <typename V>
using slide_caches_last_t = slide_caches_last<V>;

template <typename V>
using slide_caches_first = hamon::conjunction<
	hamon::negation<slide_caches_nothing<V>>,
	hamon::negation<slide_caches_last<V>>>;

template <typename V>
using slide_caches_first_t = slide_caches_first<V>;

template <typename V>
using not_slide_caches_first =
	hamon::negation<slide_caches_first<V>>;

#endif

}	// namespace detail

// 26.7.29.2 Class template slide_view[range.slide.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::forward_range V>
	requires hamon::ranges::view<V>
#else
template <typename V,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::forward_range_t<V>,
		hamon::ranges::view_t<V>
	>::value>
>
#endif
class slide_view : public hamon::ranges::view_interface<slide_view<V>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS V m_base;
	hamon::ranges::range_difference_t<V> m_n;

	using cache_type =
		hamon::ranges::detail::cached_value<
			!hamon::ranges::detail::slide_caches_nothing_t<V>::value,
			hamon::ranges::iterator_t<V>
		>;

	HAMON_NO_UNIQUE_ADDRESS cache_type m_cache;

private:
	template <typename Base, typename = void>
	class iterator_base
	{
	private:
		using BaseDifference = hamon::ranges::range_difference_t<Base>;

	protected:
		HAMON_CXX14_CONSTEXPR void increment() HAMON_NOEXCEPT {}
		HAMON_CXX14_CONSTEXPR void decrement() HAMON_NOEXCEPT {}
		HAMON_CXX14_CONSTEXPR void add_assign(BaseDifference) HAMON_NOEXCEPT {}
		HAMON_CXX14_CONSTEXPR void sub_assign(BaseDifference) HAMON_NOEXCEPT {}
	};

	template <typename Base>
	class iterator_base<Base,
		hamon::enable_if_t<hamon::ranges::detail::slide_caches_first_t<Base>::value>>
	{
	private:
		using BaseIter = hamon::ranges::iterator_t<Base>;
		using BaseDifference = hamon::ranges::range_difference_t<Base>;

	protected:
		HAMON_NO_UNIQUE_ADDRESS BaseIter m_last_ele{}; // present only if Base models slide_caches_first

	protected:
		iterator_base() = default;

		HAMON_CXX11_CONSTEXPR explicit
		iterator_base(BaseIter last_ele)
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<BaseIter>::value)	// noexcept as an extension
			: m_last_ele(hamon::move(last_ele))
		{}

		HAMON_CXX14_CONSTEXPR void increment()
			HAMON_NOEXCEPT_IF_EXPR(++m_last_ele)	// noexcept as an extension
		{
			++m_last_ele;
		}

		HAMON_CXX14_CONSTEXPR void decrement()
			HAMON_NOEXCEPT_IF_EXPR(--m_last_ele)	// noexcept as an extension
		{
			--m_last_ele;
		}

		HAMON_CXX14_CONSTEXPR void add_assign(BaseDifference x)
			HAMON_NOEXCEPT_IF_EXPR(m_last_ele += x)	// noexcept as an extension
		{
			m_last_ele += x;
		}

		HAMON_CXX14_CONSTEXPR void sub_assign(BaseDifference x)
			HAMON_NOEXCEPT_IF_EXPR(m_last_ele -= x)	// noexcept as an extension
		{
			m_last_ele -= x;
		}
	};

	// [range.slide.iterator], class template slide_view​::​iterator
	template <bool Const>
	class iterator : public iterator_base<hamon::ranges::detail::maybe_const<Const, V>>
	{
	private:
		friend slide_view;

		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseIter = hamon::ranges::iterator_t<Base>;
		using BaseDifference = hamon::ranges::range_difference_t<Base>;

		using IteratorBase = iterator_base<Base>;

	private:
		HAMON_NO_UNIQUE_ADDRESS BaseIter m_current{};
//		BaseIter m_last_ele  = BaseIter(); // present only if Base models slide_caches_first
		BaseDifference m_n = 0;

	private:
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_slide_caches_first, B2, Base)>
		HAMON_CXX11_CONSTEXPR
		iterator(BaseIter current, BaseDifference n)
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<BaseIter>::value)	// noexcept as an extension
			// [range.slide.iterator]/3
			: m_current(hamon::move(current))
			, m_n(n)
		{}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::slide_caches_first, B2, Base)>
		HAMON_CXX11_CONSTEXPR
		iterator(BaseIter current, BaseIter last_ele, BaseDifference n)
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<BaseIter>::value)	// noexcept as an extension
			// [range.slide.iterator]/4
			: IteratorBase(hamon::move(last_ele))
			, m_current(hamon::move(current))
			, m_n(n)
		{}

	public:
		using iterator_category = hamon::input_iterator_tag;
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::random_access_range_t<Base>::value,
				hamon::random_access_iterator_tag,	// [range.slide.iterator]/1.1
			hamon::conditional_t<hamon::ranges::bidirectional_range_t<Base>::value,
				hamon::bidirectional_iterator_tag,	// [range.slide.iterator]/1.2
				hamon::forward_iterator_tag			// [range.slide.iterator]/1.3
			>>;
		using value_type = decltype(hamon::views::counted(m_current, m_n));
		using difference_type = BaseDifference;

		iterator() = default;
		
		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<
					hamon::ranges::iterator_t<V>,
					hamon::ranges::iterator_t<B2>
				>::value>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<BaseIter, hamon::ranges::iterator_t<V>>::value)
			// [range.slide.iterator]/5
			: m_current(hamon::move(i.m_current))
			, m_n(i.m_n)
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		value_type operator*() const
			// [range.slide.iterator]/6
			HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
				hamon::views::counted(m_current, m_n))

		HAMON_CXX14_CONSTEXPR iterator& operator++()
			HAMON_NOEXCEPT_IF_EXPR(++m_current)	// noexcept as an extension
		{
			// [range.slide.iterator]/7
			// Preconditions: m_current and m_last_ele (if present) are incrementable.

			// [range.slide.iterator]/8
			++m_current;

			IteratorBase::increment();

			// [range.slide.iterator]/9
			return *this;
		}

		HAMON_CXX14_CONSTEXPR iterator operator++(int)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_copy_constructible<BaseIter>::value &&
				HAMON_NOEXCEPT_EXPR(++m_current))
		{
			// [range.slide.iterator]/10
			auto tmp = *this;
			++*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator--()
			HAMON_NOEXCEPT_IF_EXPR(--m_current)	// noexcept as an extension
		{
			// [range.slide.iterator]/11
			// Preconditions: m_current and m_last_ele (if present) are decrementable.

			// [range.slide.iterator]/12
			--m_current;

			IteratorBase::decrement();

			// [range.slide.iterator]/13
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator operator--(int)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_copy_constructible<BaseIter>::value &&
				HAMON_NOEXCEPT_EXPR(--m_current))
		{
			// [range.slide.iterator]/14
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator+=(difference_type x)
			HAMON_NOEXCEPT_IF_EXPR(m_current += x)	// noexcept as an extension
		{
			// [range.slide.iterator]/15
			// Preconditions: m_current + x and m_last_ele + x (if m_last_ele is present) have well-defined behavior.

			// [range.slide.iterator]/16
			m_current += x;

			IteratorBase::add_assign(x);

			// [range.slide.iterator]/17
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator-=(difference_type x)
			HAMON_NOEXCEPT_IF_EXPR(m_current -= x)	// noexcept as an extension
		{
			// [range.slide.iterator]/18
			// Preconditions: m_current - x and m_last_ele - x (if m_last_ele is present) have well-defined behavior.

			// [range.slide.iterator]/19
			m_current -= x;

			IteratorBase::sub_assign(x);

			// [range.slide.iterator]/20
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		value_type operator[](difference_type n) const
			// [range.slide.iterator]/21
			HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
				hamon::views::counted(m_current + n, m_n))

	private:
		// [range.slide.iterator]/22
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::slide_caches_first, B2, Base)>
		HAMON_CXX11_CONSTEXPR bool
		equal_impl(iterator const& y, hamon::detail::overload_priority<1>) const
			HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
				static_cast<bool>(this->m_last_ele == y.m_last_ele))

		HAMON_CXX11_CONSTEXPR bool
		equal_impl(iterator const& y, hamon::detail::overload_priority<0>) const
			HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
				static_cast<bool>(this->m_current == y.m_current))

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
				x.equal_impl(y, hamon::detail::overload_priority<1>{}))

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))	// noexcept as an extension
#endif
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<(iterator const& x, iterator const& y)
			// [range.slide.iterator]/23
			HAMON_NOEXCEPT_RETURN(x.m_current < y.m_current)	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>(iterator const& x, iterator const& y)
			// [range.slide.iterator]/24
			HAMON_NOEXCEPT_RETURN(y < x)	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<=(iterator const& x, iterator const& y)
			// [range.slide.iterator]/25
			HAMON_NOEXCEPT_RETURN(!(y < x))	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>=(iterator const& x, iterator const& y)
			// [range.slide.iterator]/26
			HAMON_NOEXCEPT_RETURN(!(x < y))	// noexcept as an extension

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator<=>(iterator const& x, iterator const& y) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::declval<BaseIter const&>() <=> hamon::declval<BaseIter const&>())
			requires hamon::ranges::random_access_range<Base> &&
				hamon::three_way_comparable<BaseIter>
		{
			// [range.slide.iterator]/27
			return x.m_current <=> y.m_current;
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator const& i, difference_type n) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(hamon::declval<BaseIter&>() += hamon::declval<difference_type>()) &&
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.slide.iterator]/28
			auto r = i;
			r += n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type n, iterator const& i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(hamon::declval<BaseIter&>() += hamon::declval<difference_type>()) &&
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.slide.iterator]/28
			auto r = i;
			r += n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator const& i, difference_type n) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(hamon::declval<BaseIter&>() -= hamon::declval<difference_type>()) &&
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.slide.iterator]/29
			auto r = i;
			r -= n;
			return r;
		}

		// [range.slide.iterator]/30
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::slide_caches_first, B2, Base)>
		HAMON_CXX11_CONSTEXPR difference_type
		distance_impl(iterator const& y, hamon::detail::overload_priority<1>) const
			HAMON_NOEXCEPT_RETURN(this->m_last_ele - y.m_last_ele)		// noexcept as an extension

		HAMON_CXX11_CONSTEXPR difference_type
		distance_impl(iterator const& y, hamon::detail::overload_priority<0>) const
			HAMON_NOEXCEPT_RETURN(this->m_current - y.m_current)		// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::sized_sentinel_for, BaseIter, BaseIter2, BaseIter)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
				x.distance_impl(y, hamon::detail::overload_priority<1>{}))
	};

	// [range.slide.sentinel], class slide_view​::​sentinel
	class sentinel
	{
	private:
		friend slide_view;
		
		using BaseSent = hamon::ranges::sentinel_t<V>;

	private:
		HAMON_NO_UNIQUE_ADDRESS BaseSent m_end{};

	private:
		HAMON_CXX11_CONSTEXPR explicit
		sentinel(BaseSent end) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<BaseSent>::value)
			// [range.slide.sentinel]/2
			: m_end(hamon::move(end))
		{}

	public:
		sentinel() = default;

	private:
		HAMON_CXX11_CONSTEXPR bool
		equal_impl(iterator<false> const& x) const
			// [range.slide.sentinel]/3
			HAMON_NOEXCEPT_RETURN(x.m_last_ele == m_end)	// noexcept as an extension

		HAMON_CXX11_CONSTEXPR hamon::ranges::range_difference_t<V>
		distance_impl(iterator<false> const& x) const
			// [range.slide.sentinel]/4
			HAMON_NOEXCEPT_RETURN(x.m_last_ele - m_end)	// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator<false> const& x, sentinel const& y)
			HAMON_NOEXCEPT_RETURN(y.equal_impl(x))		// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator<false> const& x, sentinel const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(sentinel const& x, iterator<false> const& y)
			HAMON_NOEXCEPT_RETURN(y == x)				// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(sentinel const& x, iterator<false> const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension
#endif

		template <typename V2 = V,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::sentinel_t<V2>,
					hamon::ranges::iterator_t<V2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_difference_t<V>
		operator-(iterator<false> const& x, sentinel const& y)
			HAMON_NOEXCEPT_RETURN(y.distance_impl(x))	// noexcept as an extension

		template <typename V2 = V,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::sentinel_t<V2>,
					hamon::ranges::iterator_t<V2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_difference_t<V>
		operator-(sentinel const& y, iterator<false> const& x)
			// [range.slide.sentinel]/5
			HAMON_NOEXCEPT_RETURN(-y.distance_impl(x))	// noexcept as an extension
	};

public:
	HAMON_CXX11_CONSTEXPR explicit
	slide_view(V base, hamon::ranges::range_difference_t<V> n)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<V>::value)	// noexcept as an extension
		// [range.slide.view]/2
		: m_base(hamon::move(base))
		, m_n(n)
	{
#if HAMON_CXX_STANDARD >= 14
		// [range.slide.view]/1
		HAMON_ASSERT(n > 0);
#endif
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	V base() const& HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_copy_constructible<V>::value)
	{
		return m_base;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	V base() && HAMON_NOEXCEPT_IF(			// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
	{
		return hamon::move(m_base);
	}

private:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::slide_caches_first, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator<false>
	begin_impl(hamon::detail::overload_priority<1>)
	{
		// [range.slide.view]/4
		auto first = hamon::ranges::begin(m_base);
		if (m_cache.has_value())
		{
			return iterator<false>(hamon::move(first), m_cache.value(), m_n);
		}

		auto last = hamon::ranges::next(first, m_n - 1, hamon::ranges::end(m_base));
		m_cache = last;

		// [range.slide.view]/3.1
		return iterator<false>(hamon::move(first), hamon::move(last), m_n);
	}

	HAMON_CXX14_CONSTEXPR iterator<false>
	begin_impl(hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V>>::value &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(m_base)))
	{
		// [range.slide.view]/3.2
		return iterator<false>(hamon::ranges::begin(m_base), m_n);
	}

public:
	template <typename V2 = V,
		typename = hamon::enable_if_t<
			!(hamon::ranges::detail::simple_view_t<V2>::value &&
			hamon::ranges::detail::slide_caches_nothing_t<V2 const>::value)>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator<false> begin() HAMON_NOEXCEPT_RETURN(	// noexcept as an extension
		begin_impl(hamon::detail::overload_priority<1>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::slide_caches_nothing, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V const>>::value &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(m_base)))
	{
		// [range.slide.view]/5
		return iterator<true>(hamon::ranges::begin(m_base), m_n);
	}

private:
	HAMON_CXX14_CONSTEXPR hamon::ranges::range_difference_t<V>
	size_impl() HAMON_NOEXCEPT_RETURN(	// noexcept as an extension
		hamon::ranges::max(hamon::ranges::distance(m_base) - m_n + 1, hamon::ranges::range_difference_t<V>(0)))

	HAMON_CXX11_CONSTEXPR hamon::ranges::range_difference_t<V const>
	size_impl() const HAMON_NOEXCEPT_RETURN(	// noexcept as an extension
		hamon::ranges::max(hamon::ranges::distance(m_base) - m_n + 1, hamon::ranges::range_difference_t<V const>(0)))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::slide_caches_nothing, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator<false>
	end_impl(hamon::detail::overload_priority<3>)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V>>::value &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(m_base) + size_impl()))
	{
		// [range.slide.view]/6.1
		return iterator<false>(
			hamon::ranges::begin(m_base) + size_impl(),
			m_n);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::slide_caches_last, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator<false>
	end_impl(hamon::detail::overload_priority<2>)
	{
		// [range.slide.view]/7
		if (m_cache.has_value())
		{
			return iterator<false>(m_cache.value(), m_n);
		}

		auto last = hamon::ranges::prev(hamon::ranges::end(m_base), m_n - 1, hamon::ranges::begin(m_base));
		m_cache = last;

		// [range.slide.view]/6.2
		return iterator<false>(hamon::move(last), m_n);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator<false>
	end_impl(hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<hamon::ranges::sentinel_t<V>>::value &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::end(m_base)))
	{
		auto last = hamon::ranges::end(m_base);

		// [range.slide.view]/6.3
		return iterator<false>(last, last, m_n);
	}

	HAMON_CXX14_CONSTEXPR sentinel
	end_impl(hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<hamon::ranges::sentinel_t<V>>::value &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::end(m_base)))
	{
		// [range.slide.view]/6.4
		return sentinel(hamon::ranges::end(m_base));
	}

public:
	template <typename V2 = V,
		typename = hamon::enable_if_t<
			!(hamon::ranges::detail::simple_view_t<V2>::value &&
			hamon::ranges::detail::slide_caches_nothing_t<V2 const>::value)>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR			// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
		end_impl(hamon::detail::overload_priority<3>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::slide_caches_nothing, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR			// nodiscard as an extension
	iterator<true> end() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(begin()) &&
		HAMON_NOEXCEPT_EXPR(size_impl()) &&
		HAMON_NOEXCEPT_EXPR(hamon::declval<iterator<true>>() + hamon::declval<hamon::ranges::range_difference_t<V const>>()))
	{
		// [range.slide.view]/8
		return begin() + size_impl();
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto		// nodiscard as an extension
	size() HAMON_NOEXCEPT_DECLTYPE_RETURN(			// noexcept as an extension
		// [range.slide.view]/9
		hamon::ranges::detail::to_unsigned_like(size_impl()))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto		// nodiscard as an extension
	size() const HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		// [range.slide.view]/9
		hamon::ranges::detail::to_unsigned_like(size_impl()))
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
slide_view(R&&, hamon::ranges::range_difference_t<R>) -> slide_view<hamon::views::all_t<R>>;

#endif

// enable_borrowed_range の特殊化
template <typename V>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(V),
	hamon::ranges::slide_view<V>);

namespace views {

namespace detail {

// 26.7.29.1 Overview[range.slide.overview]

struct slide_fn
{
public:
	// [range.slide.overview]/2
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, hamon::ranges::range_difference_t<R> n) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::slide_view<hamon::views::all_t<R>>(hamon::forward<R>(r), n))

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<T>, T>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T&& n) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::detail::make_range_adaptor(
				hamon::bind_back(*this, hamon::forward<T>(n))))
};

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::slide_fn slide{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN
#undef HAMON_NOEXCEPT_RETURN

#endif

#endif // HAMON_RANGES_ADAPTORS_SLIDE_VIEW_HPP
