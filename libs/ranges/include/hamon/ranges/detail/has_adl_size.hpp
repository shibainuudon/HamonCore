/**
 *	@file	has_adl_size.hpp
 *
 *	@brief	has_adl_size の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_ADL_SIZE_HPP
#define HAMON_RANGES_DETAIL_HAS_ADL_SIZE_HPP

#include <hamon/ranges/concepts/disable_sized_range.hpp>
#include <hamon/ranges/detail/is_integer_like.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if 0
void size(auto&) = delete;
void size(const auto&) = delete;
#else
template <typename T> void size(T&) = delete;
template <typename T> void size(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_size =
	hamon::detail::class_or_enum<hamon::remove_reference_t<T>> &&
	!HAMON_RANGES_DISABLE_SIZED_RANGE(hamon::remove_cvref_t<T>) &&
	requires(T&& t)
	{
		{ hamon::detail::decay_copy(size(hamon::forward<T>(t))) } -> detail::is_integer_like;
	};

#else

template <typename T>
struct has_adl_size_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<
				hamon::remove_reference_t<U>
			>::value>,
		typename = hamon::enable_if_t<
			!HAMON_RANGES_DISABLE_SIZED_RANGE(hamon::remove_cvref_t<U>)
		>,
		typename S = decltype(hamon::detail::decay_copy(size(hamon::declval<U&&>())))
	>
	static auto test(int) -> detail::is_integer_like<S>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_size = typename has_adl_size_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_ADL_SIZE_HPP
