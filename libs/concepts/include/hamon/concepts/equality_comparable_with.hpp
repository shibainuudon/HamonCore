﻿/**
 *	@file	equality_comparable_with.hpp
 *
 *	@brief	equality_comparable_with の定義
 */

#ifndef HAMON_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP
#define HAMON_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP

#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::equality_comparable_with;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/detail/cref.hpp>
#include <hamon/concepts/detail/weakly_eq_cmp_with.hpp>
#include <hamon/type_traits/common_reference.hpp>

namespace hamon
{

template <typename T, typename U>
concept equality_comparable_with =
	hamon::equality_comparable<T> &&
	hamon::equality_comparable<U> &&
	hamon::common_reference_with<detail::cref<T>, detail::cref<U>> &&
	hamon::equality_comparable<hamon::common_reference_t<detail::cref<T>, detail::cref<U>>> &&
	detail::weakly_eq_cmp_with<T, U>;

}	// namespace hamon

#else

#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/detail/cref.hpp>
#include <hamon/concepts/detail/weakly_eq_cmp_with.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T, typename U>
struct equality_comparable_with_impl
{
private:
	template <typename T2, typename U2>
	static auto test(int) -> hamon::conjunction<
		hamon::equality_comparable<T2>,
		hamon::equality_comparable<U2>,
		hamon::common_reference_with<detail::cref<T2>, detail::cref<U2>>,
		hamon::equality_comparable<hamon::common_reference_t<detail::cref<T2>, detail::cref<U2>>>,
		detail::weakly_eq_cmp_with<T2, U2>>;

	template <typename T2, typename U2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using equality_comparable_with =
	typename detail::equality_comparable_with_impl<T, U>::type;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T, typename U>
using equality_comparable_with_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::equality_comparable_with<T, U>>;
#else
	hamon::equality_comparable_with<T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_EQUALITY_COMPARABLE_WITH_HPP