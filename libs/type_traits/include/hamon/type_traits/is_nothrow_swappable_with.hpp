/**
 *	@file	is_nothrow_swappable_with.hpp
 *
 *	@brief	is_nothrow_swappable_with の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_swappable) && (__cpp_lib_is_swappable >= 201603)

namespace hamon
{

using std::is_nothrow_swappable_with;

}	// namespace hamon

#else

#include <hamon/type_traits/is_swappable_with.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief		型T と 型U がSwap可能かつ、そのSwapが例外を投げないか調べる
 *
 *	@tparam		T	チェックする型
 *	@tparam		U	チェックする型
 *
 *	@require	型Tと型Uは両方とも完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_swappable_withは、型T と 型U がSwappableコンセプトを満たしており、そのswap関数が例外を投げないならtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	型TとUは参照でなければswapできないのでTとUが参照でない場合、結果はfalseとなる。
 */
template <typename T, typename U>
struct is_nothrow_swappable_with;

namespace is_nothrow_swappable_detail
{

using std::swap;

#if defined(HAMON_HAS_CXX11_NOEXCEPT)

template <typename T, typename U>
struct is_nothrow_swappable_with_impl_2
{
private:
	template <typename T2, typename U2>
	static hamon::bool_constant<
		HAMON_NOEXCEPT_EXPR(swap(hamon::declval<T2>(), hamon::declval<U2>())) &&
		HAMON_NOEXCEPT_EXPR(swap(hamon::declval<U2>(), hamon::declval<T2>()))
	>
	test(int);

	template <typename, typename>
	static hamon::false_type test(...);

public:
	using type = decltype(test<T, U>(0));
};

#else

template <typename T, typename U>
struct is_nothrow_swappable_with_impl_2
{
	using type = hamon::true_type;
};

#endif

template <typename T, typename U, bool = hamon::is_swappable_with<T, U>::value>
struct is_nothrow_swappable_with_impl
	: public is_nothrow_swappable_with_impl_2<T, U>::type
{};

template <typename T, typename U>
struct is_nothrow_swappable_with_impl<T, U, false>
	: public hamon::false_type
{};

}	// namespace is_nothrow_swappable_detail

template <typename T, typename U>
struct is_nothrow_swappable_with
	: public is_nothrow_swappable_detail::is_nothrow_swappable_with_impl<T, U>
{};

}	// namespace hamon

#endif

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
