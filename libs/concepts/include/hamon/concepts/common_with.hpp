/**
 *	@file	common_with.hpp
 *
 *	@brief	common_with の定義
 */

#ifndef HAMON_CONCEPTS_COMMON_WITH_HPP
#define HAMON_CONCEPTS_COMMON_WITH_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/common_reference.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::common_with;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

template <typename T, typename U>
concept common_with =
	hamon::same_as<hamon::common_type_t<T, U>, hamon::common_type_t<U, T>> &&
	requires
	{
		static_cast<hamon::common_type_t<T, U>>(hamon::declval<T>());
		static_cast<hamon::common_type_t<T, U>>(hamon::declval<U>());
	} &&
	hamon::common_reference_with<
		hamon::add_lvalue_reference_t<T const>,
		hamon::add_lvalue_reference_t<U const>
	> &&
	hamon::common_reference_with<
		hamon::add_lvalue_reference_t<hamon::common_type_t<T, U>>,
		hamon::common_reference_t<
			hamon::add_lvalue_reference_t<T const>,
			hamon::add_lvalue_reference_t<U const>
		>
	>;

}	// namespace hamon

#else

#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename U>
struct common_with_impl
{
private:
	template <typename T2, typename U2,
		typename C = hamon::common_type_t<T2, U2>,
		typename = decltype(static_cast<C>(hamon::declval<T2>())),
		typename = decltype(static_cast<C>(hamon::declval<U2>()))
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<
			hamon::common_type_t<T2, U2>,
			hamon::common_type_t<U2, T2>
		>,
		hamon::common_reference_with<
			hamon::add_lvalue_reference_t<T2 const>,
			hamon::add_lvalue_reference_t<U2 const>
		>,
		hamon::common_reference_with<
			hamon::add_lvalue_reference_t<C>,
			hamon::common_reference_t<
				hamon::add_lvalue_reference_t<T2 const>,
				hamon::add_lvalue_reference_t<U2 const>
			>
		>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using common_with =
	typename detail::common_with_impl<T, U>::type;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T, typename U>
using common_with_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::common_with<T, U>>;
#else
	hamon::common_with<T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_COMMON_WITH_HPP
