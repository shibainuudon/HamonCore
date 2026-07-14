/**
 *	@file	has_adl_cos.hpp
 *
 *	@brief	has_adl_cos の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_COS_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_COS_HPP

#include <hamon/cmath/ranges/detail/is_not_void.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace cos_detail
{

#if 0
void cos(const auto&) = delete;
#else
template <typename T> void cos(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL has_adl_cos =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ cos(t) } -> hamon::detail::is_not_void;
	};

#else

template <typename T>
struct has_adl_cos_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<hamon::detail::class_or_enum<U>>,
		typename S = decltype(cos(hamon::declval<U const&>())),
		typename = hamon::enable_if_t<hamon::detail::is_not_void<S>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL has_adl_cos = has_adl_cos_impl<T>::type::value;

#endif

}	// namespace cos_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_COS_HPP
