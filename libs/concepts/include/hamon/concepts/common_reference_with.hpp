﻿/**
 *	@file	common_reference_with.hpp
 *
 *	@brief	common_reference_with の定義
 */

#ifndef HAMON_CONCEPTS_COMMON_REFERENCE_WITH_HPP
#define HAMON_CONCEPTS_COMMON_REFERENCE_WITH_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::common_reference_with;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>

namespace hamon
{

template <typename T, typename U>
concept common_reference_with =
	hamon::same_as<hamon::common_reference_t<T, U>, hamon::common_reference_t<U, T>> &&
	hamon::convertible_to<T, hamon::common_reference_t<T, U>> &&
	hamon::convertible_to<U, hamon::common_reference_t<T, U>>;

}	// namespace hamon

#else

#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename U>
struct common_reference_with_impl
{
private:
	template <typename T2, typename U2,
		typename C = hamon::common_reference_t<T2, U2>
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<C, hamon::common_reference_t<U2, T2>>,
		hamon::convertible_to<T2, C>,
		hamon::convertible_to<U2, C>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using common_reference_with =
	typename detail::common_reference_with_impl<T, U>::type;

}	// namespace hamon

#endif

namespace hamon
{

template <typename T, typename U>
using common_reference_with_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::common_reference_with<T, U>>;
#else
	hamon::common_reference_with<T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_COMMON_REFERENCE_WITH_HPP
