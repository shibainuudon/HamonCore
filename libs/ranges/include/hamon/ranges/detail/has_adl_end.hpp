/**
 *	@file	has_adl_end.hpp
 *
 *	@brief	has_adl_end の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_ADL_END_HPP
#define HAMON_RANGES_DETAIL_HAS_ADL_END_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

// Poison pills so that unqualified lookup doesn't find std::end.
#if 0
void end(auto&) = delete;
void end(const auto&) = delete;
#else
template <typename T> void end(T&) = delete;
template <typename T> void end(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_end =
	hamon::detail::class_or_enum<hamon::remove_reference_t<T>> &&
	requires(T& t)
	{
		{ hamon::detail::decay_copy(end(t)) } -> hamon::sentinel_for<decltype(ranges::begin(t))>;
	};

#else

template <typename T>
struct has_adl_end_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<
				hamon::remove_reference_t<U>
			>::value>,
		typename E = decltype(hamon::detail::decay_copy(end(std::declval<U&>()))),
		typename B = decltype(ranges::begin(std::declval<U&>()))
	>
	static auto test(int) -> hamon::sentinel_for<E, B>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_end = typename has_adl_end_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_ADL_END_HPP
