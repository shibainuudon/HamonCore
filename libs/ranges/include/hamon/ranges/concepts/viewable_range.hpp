/**
 *	@file	viewable_range.hpp
 *
 *	@brief	viewable_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_VIEWABLE_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_VIEWABLE_RANGE_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

#if !defined(HAMON_USE_STD_RANGES)
#include <hamon/ranges/concepts/range.hpp>
//#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#endif

namespace hamon
{
namespace ranges
{

namespace detail
{

// [range.refinements]/5

template <typename T>
struct is_initializer_list : public hamon::false_type {};

template <typename T>
struct is_initializer_list<std::initializer_list<T>> : public hamon::true_type {};

} // namespace detail

// [range.refinements]/6

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::viewable_range;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept viewable_range =
	ranges::range<T> &&
	((ranges::view<hamon::remove_cvref_t<T>> && hamon::constructible_from<hamon::remove_cvref_t<T>, T>) ||
	 (!ranges::view<hamon::remove_cvref_t<T>> &&
		 (hamon::is_lvalue_reference<T>::value ||
			 (hamon::movable<hamon::remove_reference_t<T>> &&
			  !detail::is_initializer_list<hamon::remove_cvref_t<T>>::value))));
#else

namespace detail
{

template <typename T>
struct viewable_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<ranges::range<U>::value>,
		typename = hamon::enable_if_t<
			hamon::disjunction<
				hamon::conjunction<
					ranges::view<hamon::remove_cvref_t<U>>,
					hamon::constructible_from<hamon::remove_cvref_t<U>, U>
				>,
				hamon::conjunction<
					hamon::negation<ranges::view<hamon::remove_cvref_t<U>>>,
					hamon::disjunction<
						hamon::is_lvalue_reference<U>,
						hamon::conjunction<
							hamon::movable<hamon::remove_reference_t<U>>,
							hamon::negation<is_initializer_list<hamon::remove_cvref_t<U>>>
						>
					>
				>
			>::value
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using viewable_range = typename ranges::detail::viewable_range_impl<T>::type;

#endif

template <typename T>
using viewable_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::viewable_range<T>>;
#else
	hamon::ranges::viewable_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_VIEWABLE_RANGE_HPP
