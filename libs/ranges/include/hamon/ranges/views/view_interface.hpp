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
#include <hamon/ranges/empty.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <type_traits>

namespace hamon
{
namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept ranges_empty_invocable =
	requires { hamon::ranges::empty(std::declval<T>()); };

#else

template <typename T>
using ranges_empty_invocable_impl =
	decltype(hamon::ranges::empty(std::declval<T>()));

template <typename T>
using ranges_empty_invocable =
	hamon::is_detected<ranges_empty_invocable_impl, T>;

#endif

}	// namespace detail

template <
	typename Derived
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, typename
#endif
>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires std::is_class<Derived>::value && hamon::same_as<Derived, hamon::remove_cv_t<Derived>>
#endif
class view_interface
{
private:
	template <typename D>
	HAMON_CXX14_CONSTEXPR D& derived() HAMON_NOEXCEPT
	{
		static_assert(hamon::derived_from_t<hamon::remove_cv_t<D>, view_interface<Derived>>::value, "");
		static_assert(ranges::view_t<hamon::remove_cv_t<D>>::value, "");
		return static_cast<D&>(*this);
	}

	template <typename D>
	HAMON_CXX11_CONSTEXPR D& derived() const HAMON_NOEXCEPT
	{
		static_assert(hamon::derived_from_t<hamon::remove_cv_t<D>, view_interface<Derived>>::value, "");
		static_assert(ranges::view_t<hamon::remove_cv_t<D>>::value, "");
		return static_cast<D&>(*this);
	}

	template <typename T>
	static constexpr bool
	s_empty(T& t)
	HAMON_NOEXCEPT_IF_EXPR(bool(ranges::begin(t) == ranges::end(t)))
	{
		return ranges::begin(t) == ranges::end(t);
	}

	template <typename T>
	static constexpr auto
	s_data(T& t)
	HAMON_NOEXCEPT_IF_EXPR(hamon::to_address(ranges::begin(t)))
	->decltype(hamon::to_address(ranges::begin(t)))
	{
		return hamon::to_address(ranges::begin(t));
	}

	template <typename T>
	static constexpr auto
	s_size(T& t)
	HAMON_NOEXCEPT_IF_EXPR(ranges::end(t) - ranges::begin(t))
	->decltype(ranges::end(t) - ranges::begin(t))
	{
		return ranges::end(t) - ranges::begin(t);
	}

public:
	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, D, Derived)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool empty()
	HAMON_NOEXCEPT_IF_EXPR(s_empty(derived<D>()))
	{
		return s_empty(derived<D>());
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, D, Derived const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool empty() const
	HAMON_NOEXCEPT_IF_EXPR(s_empty(derived<D>()))
	{
		return s_empty(derived<D>());
	}

	template <typename D = Derived
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<detail::ranges_empty_invocable<D&>::value>
#endif
	>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR explicit operator bool()
	HAMON_NOEXCEPT_IF_EXPR(ranges::empty(derived<D>()))
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires detail::ranges_empty_invocable<D&>
#endif
	{
		return !ranges::empty(derived<D>());
	}

	template <typename D = Derived const
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<detail::ranges_empty_invocable<D&>::value>
#endif
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR explicit operator bool() const
	HAMON_NOEXCEPT_IF_EXPR(ranges::empty(derived<D>()))
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires detail::ranges_empty_invocable<D&>
#endif
	{
		return !ranges::empty(derived<D>());
	}

	template <typename D = Derived,
		typename = hamon::enable_if_t<hamon::contiguous_iterator_t<ranges::iterator_t<D>>::value>
	>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto data()
	HAMON_NOEXCEPT_IF_EXPR(s_data(derived<D>()))
	->decltype(s_data(derived<D>()))
	{
		return s_data(derived<D>());
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::range, D, Derived const),
		typename = hamon::enable_if_t<hamon::contiguous_iterator_t<ranges::iterator_t<D>>::value>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto data() const
	HAMON_NOEXCEPT_IF_EXPR(s_data(derived<D>()))
	->decltype(s_data(derived<D>()))
	{
		return s_data(derived<D>());
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, D, Derived),
		typename = hamon::enable_if_t<hamon::sized_sentinel_for_t<ranges::sentinel_t<D>, ranges::iterator_t<D>>::value>
	>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto size()
	HAMON_NOEXCEPT_IF_EXPR(s_size(derived<D>()))
	->decltype(s_size(derived<D>()))
	{
		return s_size(derived<D>());
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, D, Derived const),
		typename = hamon::enable_if_t<hamon::sized_sentinel_for_t<ranges::sentinel_t<D>, ranges::iterator_t<D>>::value>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto size() const
	HAMON_NOEXCEPT_IF_EXPR(s_size(derived<D>()))
	->decltype(s_size(derived<D>()))
	{
		return s_size(derived<D>());
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, D, Derived)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto front()
	->decltype((*ranges::begin(derived<D>())))
	{
		return HAMON_ASSERT(!empty()),
			*ranges::begin(derived<D>());
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::forward_range, D, Derived const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto front() const
	->decltype((*ranges::begin(derived<D>())))
	{
		return HAMON_ASSERT(!empty()),
			*ranges::begin(derived<D>());
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::bidirectional_range, D, Derived),
		typename = hamon::enable_if_t<ranges::common_range_t<D>::value>
	>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto back()
	->decltype((*ranges::prev(ranges::end(derived<D>()))))
	{
		return HAMON_ASSERT(!empty()),
			*ranges::prev(ranges::end(derived<D>()));
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::bidirectional_range, D, Derived const),
		typename = hamon::enable_if_t<ranges::common_range_t<D>::value>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto back() const
	->decltype((*ranges::prev(ranges::end(derived<D>()))))
	{
		return HAMON_ASSERT(!empty()),
			*ranges::prev(ranges::end(derived<D>()));
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::random_access_range, D, Derived)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto
	operator[](ranges::range_difference_t<D> n)
	->decltype((ranges::begin(derived<D>())[n]))
	{
		return ranges::begin(derived<D>())[n];
	}

	template <HAMON_CONSTRAINED_PARAM_D(ranges::random_access_range, D, Derived const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator[](ranges::range_difference_t<D> n) const
	->decltype((ranges::begin(derived<D>())[n]))
	{
		return ranges::begin(derived<D>())[n];
	}
};

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_VIEWS_VIEW_INTERFACE_HPP
