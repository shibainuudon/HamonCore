/**
 *	@file	view_interface.hpp
 *
 *	@brief	ranges::view_interface の定義
 */

#ifndef HAMON_RANGES_VIEWS_VIEW_INTERFACE_HPP
#define HAMON_RANGES_VIEWS_VIEW_INTERFACE_HPP

#include <hamon/ranges/views/view_interface_fwd.hpp>
#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::view_interface;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/cbegin.hpp>
#include <hamon/ranges/cend.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

namespace detail
{

template <typename T>
using ranges_empty_invocable_impl =
	decltype(hamon::ranges::empty(hamon::declval<T>()));

template <typename T>
using ranges_empty_invocable =
	hamon::is_detected<ranges_empty_invocable_impl, T>;

}	// namespace detail

// [view.interface.general]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <typename D>
requires hamon::is_class<D>::value && hamon::same_as<D, hamon::remove_cv_t<D>>
#else
template <typename D, typename>
#endif
class view_interface
{
private:
	HAMON_CXX14_CONSTEXPR D& derived() noexcept
	{
		return static_cast<D&>(*this);
	}

	HAMON_CXX11_CONSTEXPR D const& derived() const noexcept
	{
		return static_cast<D const&>(*this);
	}

	template <typename R,
		typename = hamon::enable_if_t<ranges::sized_range_t<R>::value>>
	static HAMON_CXX11_CONSTEXPR bool
	empry_impl(R& r, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_IF_EXPR(ranges::size(r) == 0)
	{
		return ranges::size(r) == 0;
	}

	template <typename R>
	static HAMON_CXX11_CONSTEXPR bool
	empry_impl(R& r, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_IF_EXPR(bool(ranges::begin(r) == ranges::end(r)))
	{
		return ranges::begin(r) == ranges::end(r);
	}

public:
	template <typename R = D,
		typename = hamon::enable_if_t<
			ranges::sized_range_t<R>::value ||
			ranges::forward_range_t<R>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
	empty()
	HAMON_NOEXCEPT_IF_EXPR(empry_impl(hamon::declval<R&>(), hamon::detail::overload_priority<1>{}))	// noexcept as an extension
	{
		return empry_impl(derived(), hamon::detail::overload_priority<1>{});
	}

	template <typename R = D const,
		typename = hamon::enable_if_t<
			ranges::sized_range_t<R>::value ||
			ranges::forward_range_t<R>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	empty() const
	HAMON_NOEXCEPT_IF_EXPR(empry_impl(hamon::declval<R&>(), hamon::detail::overload_priority<1>{}))	// noexcept as an extension
	{
		return empry_impl(derived(), hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::input_range, R, D)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	cbegin()
	HAMON_NOEXCEPT_IF_EXPR(ranges::cbegin(hamon::declval<R&>()))	// noexcept as an extension
	->decltype(ranges::cbegin(hamon::declval<R&>()))
	{
		return ranges::cbegin(derived());
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::input_range, R, D const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	cbegin() const
	HAMON_NOEXCEPT_IF_EXPR(ranges::cbegin(hamon::declval<R&>()))	// noexcept as an extension
	->decltype(ranges::cbegin(hamon::declval<R&>()))
	{
		return ranges::cbegin(derived());
	}
	
	template <HAMON_CONSTRAINED_PARAM_D(ranges::input_range, R, D)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	cend()
	HAMON_NOEXCEPT_IF_EXPR(ranges::cend(hamon::declval<R&>()))	// noexcept as an extension
	->decltype(ranges::cend(hamon::declval<R&>()))
	{
		return ranges::cend(derived());
	}
	
	template <HAMON_CONSTRAINED_PARAM_D(ranges::input_range, R, D const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	cend() const
	HAMON_NOEXCEPT_IF_EXPR(ranges::cend(hamon::declval<R&>()))	// noexcept as an extension
	->decltype(ranges::cend(hamon::declval<R&>()))
	{
		return ranges::cend(derived());
	}

	template <typename R = D,
		typename = hamon::enable_if_t<detail::ranges_empty_invocable<R&>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR explicit	// nodiscard as an extension
	operator bool()
	HAMON_NOEXCEPT_IF_EXPR(ranges::empty(hamon::declval<R&>()))	// noexcept as an extension
	{
		return !ranges::empty(derived());
	}

	template <typename R = D const,
		typename = hamon::enable_if_t<detail::ranges_empty_invocable<R&>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR explicit	// nodiscard as an extension
	operator bool() const
	HAMON_NOEXCEPT_IF_EXPR(ranges::empty(hamon::declval<R&>()))	// noexcept as an extension
	{
		return !ranges::empty(derived());
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::range, R, D),
		typename = hamon::enable_if_t<hamon::contiguous_iterator_t<ranges::iterator_t<R>>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	data()
	HAMON_NOEXCEPT_IF_EXPR(hamon::to_address(ranges::begin(hamon::declval<R&>())))	// noexcept as an extension
	->decltype(hamon::to_address(ranges::begin(hamon::declval<R&>())))
	{
		return hamon::to_address(ranges::begin(derived()));
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::range, R, D const),
		typename = hamon::enable_if_t<hamon::contiguous_iterator_t<ranges::iterator_t<R>>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	data() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::to_address(ranges::begin(hamon::declval<R&>())))	// noexcept as an extension
	->decltype(hamon::to_address(ranges::begin(hamon::declval<R&>())))
	{
		return hamon::to_address(ranges::begin(derived()));
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, R, D),
		typename = hamon::enable_if_t<hamon::sized_sentinel_for_t<ranges::sentinel_t<R>, ranges::iterator_t<R>>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	size()
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::detail::to_unsigned_like(ranges::end(hamon::declval<R&>()) - ranges::begin(hamon::declval<R&>())))	// noexcept as an extension
	->decltype(hamon::ranges::detail::to_unsigned_like(ranges::end(hamon::declval<R&>()) - ranges::begin(hamon::declval<R&>())))
	{
		return hamon::ranges::detail::to_unsigned_like(ranges::end(derived()) - ranges::begin(derived()));
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, R, D const),
		typename = hamon::enable_if_t<hamon::sized_sentinel_for_t<ranges::sentinel_t<R>, ranges::iterator_t<R>>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	size() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::detail::to_unsigned_like(ranges::end(hamon::declval<R&>()) - ranges::begin(hamon::declval<R&>())))	// noexcept as an extension
	->decltype(hamon::ranges::detail::to_unsigned_like(ranges::end(hamon::declval<R&>()) - ranges::begin(hamon::declval<R&>())))
	{
		return hamon::ranges::detail::to_unsigned_like(ranges::end(derived()) - ranges::begin(derived()));
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, R, D)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	front()
	HAMON_NOEXCEPT_IF_EXPR(*ranges::begin(hamon::declval<R&>()))	// noexcept as an extension
	->decltype((*ranges::begin(hamon::declval<R&>())))
	{
		return HAMON_ASSERT(!empty()),	// [view.interface.members]/1
			*ranges::begin(derived());	// [view.interface.members]/2
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, R, D const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	front() const
	HAMON_NOEXCEPT_IF_EXPR(*ranges::begin(hamon::declval<R&>()))	// noexcept as an extension
	->decltype((*ranges::begin(hamon::declval<R&>())))
	{
		return HAMON_ASSERT(!empty()),	// [view.interface.members]/1
			*ranges::begin(derived());	// [view.interface.members]/2
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::bidirectional_range, R, D),
		typename = hamon::enable_if_t<ranges::common_range_t<R>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	back()
	HAMON_NOEXCEPT_IF_EXPR(*ranges::prev(ranges::end(hamon::declval<R&>())))	// noexcept as an extension
	->decltype((*ranges::prev(ranges::end(hamon::declval<R&>()))))
	{
		return HAMON_ASSERT(!empty()),				// [view.interface.members]/3
			*ranges::prev(ranges::end(derived()));	// [view.interface.members]/4
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::bidirectional_range, R, D const),
		typename = hamon::enable_if_t<ranges::common_range_t<R>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	back() const
	HAMON_NOEXCEPT_IF_EXPR(*ranges::prev(ranges::end(hamon::declval<R&>())))	// noexcept as an extension
	->decltype((*ranges::prev(ranges::end(hamon::declval<R&>()))))
	{
		return HAMON_ASSERT(!empty()),				// [view.interface.members]/3
			*ranges::prev(ranges::end(derived()));	// [view.interface.members]/4
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::random_access_range, R, D)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	operator[](ranges::range_difference_t<R> n)
	HAMON_NOEXCEPT_IF_EXPR(ranges::begin(hamon::declval<R&>())[n])	// noexcept as an extension
	->decltype((ranges::begin(hamon::declval<R&>())[n]))
	{
		return ranges::begin(derived())[n];
	}
	
	template <HAMON_CONSTRAINED_PARAM_D(ranges::random_access_range, R, D const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	operator[](ranges::range_difference_t<R> n) const
	HAMON_NOEXCEPT_IF_EXPR(ranges::begin(hamon::declval<R&>())[n])	// noexcept as an extension
	->decltype((ranges::begin(hamon::declval<R&>())[n]))
	{
		return ranges::begin(derived())[n];
	}
};

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_VIEWS_VIEW_INTERFACE_HPP
