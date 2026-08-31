/**
 *	@file	as_input_view.hpp
 *
 *	@brief	as_input_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_AS_INPUT_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_AS_INPUT_VIEW_HPP

#include <hamon/ranges/fwd.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/approximately_sized_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/reserve_hint.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
//#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

// 25.7.35 As input view[range.as.input]

namespace hamon {
namespace ranges {

// 古いバージョンのclangにおいて、iter_swapの再定義エラーになる場合があるので
// inline namespace で囲む。
inline namespace as_input_view_ns
{

// 25.7.35.2 Class template as_input_view[range.as.input.view]
#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <ranges::input_range V>
	requires ranges::view<V>
#else
template <typename V,
	typename = hamon::enable_if_t<
		hamon::ranges::input_range<V> &&
		hamon::ranges::view<V>
	>>
#endif
class as_input_view : public ranges::view_interface<as_input_view<V>>
{
	V base_ = V();

	// 25.7.35.3 Class template as_input_view::iterator[range.as.input.iterator]
	template <bool Const>
	class iterator
	{
		friend as_input_view;

		using Base = ranges::detail::maybe_const<Const, V>;

		ranges::iterator_t<Base> current_ = ranges::iterator_t<Base>();

		HAMON_CXX11_CONSTEXPR explicit
		iterator(ranges::iterator_t<Base> current)
			// [range.as.input.iterator]/1
			: current_(hamon::move(current))
		{}

	public:
		using difference_type  = ranges::range_difference_t<Base>;
		using value_type       = ranges::range_value_t<Base>;
		using iterator_concept = hamon::input_iterator_tag;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
		iterator()
			requires hamon::default_initializable<ranges::iterator_t<Base>>
		= default;
#else
		template <HAMON_CONSTRAINT_D(hamon::default_initializable, I, ranges::iterator_t<Base>)>
		HAMON_CXX11_CONSTEXPR
		iterator()
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible_v<I>)
		{}
#endif

		iterator(iterator&&) = default;
		iterator& operator=(iterator&&) = default;

		template <bool C2 = Const, typename = hamon::enable_if_t<
			C2 && hamon::convertible_to<ranges::iterator_t<V>, ranges::iterator_t<Base>>>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i)
			// [range.as.input.iterator]/2
			: current_(hamon::move(i.current_))
		{}

		HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		ranges::iterator_t<Base> base() &&
		{
			// [range.as.input.iterator]/3
			return hamon::move(current_);
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		const ranges::iterator_t<Base>& base() const& HAMON_NOEXCEPT
		{
			// [range.as.input.iterator]/4
			return current_;
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		decltype(auto) operator*() const
		{
			return *current_;
		}

		HAMON_CXX14_CONSTEXPR
		iterator& operator++()
		{
			// [range.as.input.iterator]/5
			++current_;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR
		void operator++(int)
		{
			// [range.as.input.iterator]/6
			++*this;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(const iterator& x, const ranges::sentinel_t<Base>& y)
		{
			// [range.as.input.iterator]/7
			return x.current_ == y;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(const iterator& x, const ranges::sentinel_t<Base>& y)
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(const ranges::sentinel_t<Base>& x, const iterator& y)
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(const ranges::sentinel_t<Base>& x, const iterator& y)
		{
			return !(x == y);
		}
#endif

		template <typename Base2 = Base, typename = hamon::enable_if_t<
			hamon::sized_sentinel_for<ranges::sentinel_t<Base2>, ranges::iterator_t<Base2>>>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(const ranges::sentinel_t<Base>& y, const iterator& x)
		{
			// [range.as.input.iterator]/8
			return y - x.current_;
		}

		template <typename Base2 = Base, typename = hamon::enable_if_t<
			hamon::sized_sentinel_for<ranges::sentinel_t<Base2>, ranges::iterator_t<Base2>>>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(const iterator& x, const ranges::sentinel_t<Base>& y)
		{
			// [range.as.input.iterator]/9
			return x.current_ - y;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		ranges::range_rvalue_reference_t<Base> iter_move(const iterator& i)
			HAMON_NOEXCEPT_IF_EXPR(ranges::iter_move(i.current_))
		{
			// [range.as.input.iterator]/10
			return ranges::iter_move(i.current_);
		}

		template <HAMON_CONSTRAINT_D(hamon::indirectly_swappable, I, ranges::iterator_t<Base>)>
		friend HAMON_CXX14_CONSTEXPR
		void iter_swap(const iterator& x, const iterator& y)
			HAMON_NOEXCEPT_IF_EXPR(ranges::iter_swap(x.current_, y.current_))
		{
			// [range.as.input.iterator]/11
			ranges::iter_swap(x.current_, y.current_);
		}
	};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	as_input_view()
		requires hamon::default_initializable<V> = default;
#else
	template <HAMON_CONSTRAINT_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR
	as_input_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible_v<V>)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	as_input_view(V base)
		// [range.as.input.view]/1
		: base_(hamon::move(base))
	{}

	template <HAMON_CONSTRAINT_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	V base() const&
	{
		return base_;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	V base() &&
	{
		return hamon::move(base_);
	}

	template <HAMON_CONSTRAINT_D(ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto begin()
	{
		// [range.as.input.view]/2
		return iterator<false>(ranges::begin(base_));
	}

	template <HAMON_CONSTRAINT_D(ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto begin() const
	{
		// [range.as.input.view]/3
		return iterator<true>(ranges::begin(base_));
	}

	template <HAMON_CONSTRAINT_D(ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end()
	{
		// [range.as.input.view]/4
		return ranges::end(base_);
	}

	template <HAMON_CONSTRAINT_D(ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto end() const
	{
		// [range.as.input.view]/4
		return ranges::end(base_);
	}

	template <HAMON_CONSTRAINT_D(ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto size()
	{
		// [range.as.input.view]/5
		return ranges::size(base_);
	}

	template <HAMON_CONSTRAINT_D(ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto size() const
	{
		// [range.as.input.view]/5
		return ranges::size(base_);
	}

	template <HAMON_CONSTRAINT_D(ranges::approximately_sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto reserve_hint()
	{
		// [range.as.input.view]/6
		return ranges::reserve_hint(base_);
	}

	template <HAMON_CONSTRAINT_D(ranges::approximately_sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto reserve_hint() const
	{
		// [range.as.input.view]/6
		return ranges::reserve_hint(base_);
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
as_input_view(R&&) -> as_input_view<views::all_t<R>>;

#endif

}	// inline namespace as_input_view_ns

// enable_borrowed_range の特殊化
template <typename V>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool enable_borrowed_range<ranges::as_input_view<V>> =
	ranges::enable_borrowed_range<V>;

namespace views {

namespace detail {

// 25.7.35.1 Overview[range.as.input.overview]
struct as_input_fn : public ranges::range_adaptor_closure<as_input_fn>
{
private:
	template <typename R, typename = hamon::enable_if_t<
		ranges::input_range<R> &&
		!ranges::common_range<R> &&
		!ranges::forward_range<R>
	>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<1>)
	{
		return views::all(hamon::forward<R>(r));
	}

	template <typename R>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, hamon::detail::overload_priority<0>)
	{
		return ranges::as_input_view<views::all_t<R>>(hamon::forward<R>(r));
	}

public:
	template <HAMON_CONSTRAINT(ranges::viewable_range, R)>
//		requires requires { ranges::as_input_view(hamon::declval<R>()); }
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r) const
	{
		return impl(hamon::forward<R>(r), hamon::detail::overload_priority<1>{});
	}
};

} // namespace detail

inline namespace cpo
{

// [range.as.input], as input view
HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::as_input_fn as_input{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_AS_INPUT_VIEW_HPP
