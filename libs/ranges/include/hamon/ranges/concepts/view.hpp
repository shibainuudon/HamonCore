/**
 *	@file	view.hpp
 *
 *	@brief	view の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_VIEW_HPP
#define HAMON_RANGES_CONCEPTS_VIEW_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES)
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/enable_view.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{
namespace ranges
{

// [range.view]/1

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::view;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL view =
	ranges::range<T> &&
	hamon::movable<T> &&
	hamon::ranges::enable_view<T>;

#else

namespace detail
{

template <typename T>
struct view_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<ranges::range<U>>,
		typename = hamon::enable_if_t<hamon::movable<U>>,
		typename = hamon::enable_if_t<hamon::ranges::enable_view<U>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
HAMON_CONCEPT_OR_BOOL view =
	ranges::detail::view_impl<T>::type::value;

#endif

// !view<T>

template <typename T>
HAMON_CONCEPT_OR_BOOL not_view = !hamon::ranges::view<T>;

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_VIEW_HPP
