/**
 *	@file	view.hpp
 *
 *	@brief	view の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_VIEW_HPP
#define HAMON_RANGES_CONCEPTS_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon
{
namespace ranges
{

using std::ranges::view;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/enable_view.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{
namespace ranges
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept view =
	ranges::range<T> &&
	hamon::movable<T> &&
	HAMON_RANGES_ENABLE_VIEW(T);

#else

namespace detail
{

template <typename T>
struct view_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<ranges::range<U>::value>,
		typename = hamon::enable_if_t<hamon::movable_t<U>::value>,
		typename = hamon::enable_if_t<HAMON_RANGES_ENABLE_VIEW(U)>
	>
	static auto test(int) -> std::true_type;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using view = typename ranges::detail::view_impl<T>::type;

#endif

}	// namespace ranges
}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{
namespace ranges
{

template <typename T>
using view_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::view<T>>;
#else
	hamon::ranges::view<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_VIEW_HPP
