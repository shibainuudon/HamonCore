/**
 *	@file	stride_view.hpp
 *
 *	@brief	stride_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_STRIDE_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_STRIDE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_stride) && (__cpp_lib_ranges_stride >= 202207L)

namespace hamon {
namespace ranges {

using std::ranges::stride_view;

namespace views {

using std::ranges::views::stride;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/adaptors/detail/div_ceil.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/negation.hpp>
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

// 26.7.31.2 Class template stride_view[range.stride.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range V>
	requires hamon::ranges::view<V>
#else
template <typename V,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::input_range_t<V>,
		hamon::ranges::view_t<V>
	>::value>>
#endif
class stride_view : public hamon::ranges::view_interface<stride_view<V>>
{
private:
	using Difference = hamon::ranges::range_difference_t<V>;

	HAMON_NO_UNIQUE_ADDRESS V m_base;
	Difference m_stride;

private:
	template <typename Base,
		bool = hamon::ranges::forward_range_t<Base>::value>
	struct iterator_category_base
	{
	private:
		using BaseIter = hamon::ranges::iterator_t<Base>;
		using C = typename hamon::iterator_traits<BaseIter>::iterator_category;
	public:
		using iterator_category =
			hamon::conditional_t<hamon::derived_from_t<C, hamon::random_access_iterator_tag>::value,
				hamon::random_access_iterator_tag, C>;
	};

	template <typename Base>
	struct iterator_category_base<Base, false>
	{};

private:
	// [range.stride.iterator], class template stride_view​::​iterator
	template <bool Const>
	class iterator
		: public iterator_category_base<hamon::ranges::detail::maybe_const<Const, V>>
	{
	private:
		friend stride_view;

		using Parent = hamon::ranges::detail::maybe_const<Const, stride_view>;
		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseIter = hamon::ranges::iterator_t<Base>;
		using BaseSent = hamon::ranges::sentinel_t<Base>;
		using BaseDifference = hamon::ranges::range_difference_t<Base>;

	private:
		HAMON_NO_UNIQUE_ADDRESS BaseIter m_current{};
		HAMON_NO_UNIQUE_ADDRESS BaseSent m_end{};
		BaseDifference m_stride = 0;
		BaseDifference m_missing = 0;

	private:
		HAMON_CXX11_CONSTEXPR
		iterator(Parent* parent, BaseIter current, BaseDifference missing = 0)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::ranges::end(parent->m_base)) &&
				hamon::is_nothrow_move_constructible<BaseIter>::value &&
				hamon::is_nothrow_move_constructible<BaseSent>::value)
			// [range.stride.iterator]/3
			: m_current(hamon::move(current))
			, m_end(hamon::ranges::end(parent->m_base))
			, m_stride(parent->m_stride)
			, m_missing(missing)
		{}

	public:
		using difference_type = BaseDifference;
		using value_type = hamon::ranges::range_value_t<Base>;
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::random_access_range_t<Base>::value,
				hamon::random_access_iterator_tag,
			hamon::conditional_t<hamon::ranges::bidirectional_range_t<Base>::value,
				hamon::bidirectional_iterator_tag,
			hamon::conditional_t<hamon::ranges::forward_range_t<Base>::value,
				hamon::forward_iterator_tag,
				input_iterator_tag
			>>>;
		//using iterator_category = see below;    // not always present

#if defined(HAMON_HAS_CXX20_CONCEPTS)
		iterator()
			requires hamon::default_initializable<BaseIter>
		= default;
#else
		template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, I2, BaseIter)>
		HAMON_CXX11_CONSTEXPR
		iterator() HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<I2>::value)
		{}
#endif

		template <typename V2 = V,
			typename = hamon::enable_if_t<Const &&
				hamon::convertible_to_t<hamon::ranges::iterator_t<V2>, BaseIter>::value &&
				hamon::convertible_to_t<hamon::ranges::sentinel_t<V2>, BaseSent>::value>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<BaseIter, hamon::ranges::iterator_t<V2>>::value &&
			hamon::is_nothrow_constructible<BaseSent, hamon::ranges::sentinel_t<V2>>::value)
			// [range.stride.iterator]/4
			: m_current(hamon::move(i.m_current))
			, m_end(hamon::move(i.m_end))
			, m_stride(i.m_stride)
			, m_missing(i.m_missing)
		{}

		HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		BaseIter base() && HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<BaseIter>::value)
		{
			// [range.stride.iterator]/5
			return hamon::move(m_current);
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		BaseIter const& base() const& HAMON_NOEXCEPT
		{
			// [range.stride.iterator]/6
			return m_current;
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		operator*() const
			HAMON_NOEXCEPT_DECLTYPE_RETURN(*m_current)	// noexcept as an extension

		HAMON_CXX14_CONSTEXPR iterator& operator++()	// noexcept(false)
		{
			// [range.stride.iterator]/7
			HAMON_ASSERT(m_current != m_end);

			// [range.stride.iterator]/8
			m_missing = hamon::ranges::advance(m_current, m_stride, m_end);
			return *this;
		}

	private:
		HAMON_CXX14_CONSTEXPR void
		increment_impl(hamon::detail::overload_priority<0>)	// noexcept(false)
		{
			// [range.stride.iterator]/9
			++*this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator
		increment_impl(hamon::detail::overload_priority<1>)	// noexcept(false)
		{
			// [range.stride.iterator]/10
			auto tmp = *this;
			++*this;
			return tmp;
		}

	public:
		HAMON_CXX14_CONSTEXPR
		auto operator++(int)	// noexcept(false)
		->decltype(increment_impl(hamon::detail::overload_priority<1>{}))
		{
			return increment_impl(hamon::detail::overload_priority<1>{});
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator--()	// noexcept(false)
		{
			// [range.stride.iterator]/11
			hamon::ranges::advance(m_current, m_missing - m_stride);
			m_missing = 0;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator operator--(int)	// noexcept(false)
		{
			// [range.stride.iterator]/12
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator+=(difference_type n)	// noexcept(false)
		{
			// [range.stride.iterator]/14
			if (n > 0)
			{
				// [range.stride.iterator]/13
				HAMON_ASSERT(hamon::ranges::distance(m_current, m_end) > m_stride * (n - 1));

				hamon::ranges::advance(m_current, m_stride * (n - 1));
				m_missing = hamon::ranges::advance(m_current, m_stride, m_end);
			}
			else if (n < 0)
			{
				hamon::ranges::advance(m_current, m_stride * n + m_missing);
				m_missing = 0;
			}
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator-=(difference_type n)	// noexcept(false)
		{
			// [range.stride.iterator]/15
			return *this += -n;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator[](difference_type n) const	// noexcept(false)
		->decltype(*m_current)
		{
			return *(*this + n);
		}

	private:
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, hamon::default_sentinel_t)
			// [range.stride.iterator]/16
			HAMON_NOEXCEPT_RETURN(x.m_current == x.m_end)	// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, hamon::default_sentinel_t y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(hamon::default_sentinel_t x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(y == x)				// noexcept as an extension

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(hamon::default_sentinel_t x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, I2, BaseIter)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y)
			// [range.stride.iterator]/17
			HAMON_NOEXCEPT_RETURN(x.m_current == y.m_current)	// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, I2, BaseIter)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))			// noexcept as an extension
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<(iterator const& x, iterator const& y)
			// [range.stride.iterator]/18
			HAMON_NOEXCEPT_RETURN(x.m_current < y.m_current)	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>(iterator const& x, iterator const& y)
			// [range.stride.iterator]/19
			HAMON_NOEXCEPT_RETURN(y < x)				// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<=(iterator const& x, iterator const& y)
			// [range.stride.iterator]/20
			HAMON_NOEXCEPT_RETURN(!(y < x))				// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>=(iterator const& x, iterator const& y)
			// [range.stride.iterator]/21
			HAMON_NOEXCEPT_RETURN(!(x < y))				// noexcept as an extension

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator<=>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current <=> y.m_current)	// noexcept as an extension
			requires hamon::ranges::random_access_range<Base> &&
				hamon::three_way_comparable<BaseIter>
		{
			// [range.stride.iterator]/22
			return x.m_current <=> y.m_current;
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator const& x, difference_type n)	// noexcept(false)
		{
			// [range.stride.iterator]/23
			auto r = x;
			r += n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type n, iterator const& x)	// noexcept(false)
		{
			// [range.stride.iterator]/23
			auto r = x;
			r += n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator const& x, difference_type n)	// noexcept(false)
		{
			// [range.stride.iterator]/24
			auto r = x;
			r -= n;
			return r;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		static HAMON_CXX11_CONSTEXPR difference_type
		distance_impl(iterator const& x, iterator const& y, difference_type N, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
		{
			// [range.stride.iterator]/25.1
			return (N + x.m_missing - y.m_missing) / x.m_stride;
		}

		static HAMON_CXX11_CONSTEXPR difference_type
		distance_impl(iterator const& x, iterator const&, difference_type N, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
		{
			return N < 0 ?
				// [range.stride.iterator]/25.2
				-hamon::ranges::detail::div_ceil(-N, x.m_stride) :
				// [range.stride.iterator]/25.3
				 hamon::ranges::detail::div_ceil( N, x.m_stride);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::sized_sentinel_for, BaseIter, I2, BaseIter)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current - y.m_current)	// noexcept as an extension
		{
			// [range.stride.iterator]/25
			return distance_impl(x, y, x.m_current - y.m_current, hamon::detail::overload_priority<1>{});
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::sized_sentinel_for, BaseIter, S2, BaseSent)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(hamon::default_sentinel_t, iterator const& x)
			HAMON_NOEXCEPT_IF_EXPR(x.m_end - x.m_current)	// noexcept as an extension
		{
			// [range.stride.iterator]/26
			return hamon::ranges::detail::div_ceil(x.m_end - x.m_current, x.m_stride);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::sized_sentinel_for, BaseIter, S2, BaseSent)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, hamon::default_sentinel_t y)
			// [range.stride.iterator]/27
			HAMON_NOEXCEPT_RETURN(-(y - x))		// noexcept as an extension

#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_rvalue_reference_t<Base>
		iter_move(iterator const& i)
			HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_move(i.m_current))
		{
			// [range.stride.iterator]/28
			return hamon::ranges::iter_move(i.m_current);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::indirectly_swappable, I2, BaseIter)>
		friend HAMON_CXX14_CONSTEXPR void
		iter_swap(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_swap(x.m_current, y.m_current))
		{
			// [range.stride.iterator]/29
			hamon::ranges::iter_swap(x.m_current, y.m_current);
		}
#endif
	};

public:
	HAMON_CXX11_CONSTEXPR explicit
	stride_view(V base, Difference stride) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
		// [range.stride.view]/2
		: m_base(hamon::move(base))
		, m_stride(stride)
	{
#if HAMON_CXX_STANDARD >= 14
		// [range.stride.view]/1
		HAMON_ASSERT(stride > 0);
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

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	Difference stride() const HAMON_NOEXCEPT
	{
		// [range.stride.view]/3
		return m_stride;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator<false> begin() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(m_base)) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V>>::value)
	{
		return iterator<false>(this, hamon::ranges::begin(m_base));
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(m_base)) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V const>>::value)
	{
		return iterator<true>(this, hamon::ranges::begin(m_base));
	}

private:
	template <typename This, typename V2,
		bool Const = hamon::is_const<V2>::value,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::common_range_t<V2>,
			hamon::ranges::sized_range_t<V2>,
			hamon::ranges::forward_range_t<V2>
		>::value>>
	static HAMON_CXX11_CONSTEXPR iterator<Const>
	end_impl(This* this_, V2& base, Difference stride, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(hamon::ranges::distance(base)) &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::end(base)) &&
			hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<Const>(this_, hamon::ranges::end(base),
			(stride - hamon::ranges::distance(base) % stride) % stride);
	}

	template <typename This, typename V2,
		bool Const = hamon::is_const<V2>::value,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::common_range_t<V2>,
			hamon::negation<hamon::ranges::bidirectional_range_t<V2>>
		>::value>>
	static HAMON_CXX11_CONSTEXPR iterator<Const>
	end_impl(This* this_, V2& base, Difference, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(hamon::ranges::end(base)) &&
			hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<Const>(this_, hamon::ranges::end(base));
	}

	template <typename This, typename V2>
	static HAMON_CXX11_CONSTEXPR hamon::default_sentinel_t
	end_impl(This*, V2&, Difference, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT	// noexcept as an extension
	{
		return hamon::default_sentinel;
	}

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	end() HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
		end_impl(this, m_base, m_stride, hamon::detail::overload_priority<2>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	end() const HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		end_impl(this, m_base, m_stride, hamon::detail::overload_priority<2>{}))

private:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::sized_range, V2)>
	static HAMON_CXX11_CONSTEXPR auto
	size_impl(V2& base, Difference stride, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::distance(base))	// noexcept as an extension
	->decltype(hamon::ranges::detail::to_unsigned_like(stride))
	{
		// [range.stride.view]/4
		return hamon::ranges::detail::to_unsigned_like(
			hamon::ranges::detail::div_ceil(
				hamon::ranges::distance(base), stride));
	}

	template <typename V2>
	static void size_impl(V2&, Difference, hamon::detail::overload_priority<0>);

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto		// nodiscard as an extension
	size() HAMON_NOEXCEPT_DECLTYPE_RETURN(			// noexcept as an extension
		size_impl(m_base, m_stride, hamon::detail::overload_priority<1>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto		// nodiscard as an extension
	size() const HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		size_impl(m_base, m_stride, hamon::detail::overload_priority<1>{}))
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
stride_view(R&&, hamon::ranges::range_difference_t<R>)
	-> stride_view<hamon::views::all_t<R>>;

#endif

// enable_borrowed_range の特殊化
template <typename V>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(V),
	hamon::ranges::stride_view<V>);

namespace views {

namespace detail {

// 26.7.31.1 Overview[range.stride.overview]

struct stride_fn
{
	// [range.stride.overview]/2
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, hamon::ranges::range_difference_t<R> stride) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::stride_view<hamon::views::all_t<R>>(
				hamon::forward<R>(r), stride))

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<T>, T>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T&& stride) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::detail::make_range_adaptor(
				hamon::bind_back(*this, hamon::forward<T>(stride))))
};

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::stride_fn stride{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN
#undef HAMON_NOEXCEPT_RETURN

#endif

#endif // HAMON_RANGES_ADAPTORS_STRIDE_VIEW_HPP
