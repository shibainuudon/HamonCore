/**
 *	@file	invoke_result.hpp
 *
 *	@brief	invoke_result の定義
 */

#ifndef HAMON_TYPE_TRAITS_INVOKE_RESULT_HPP
#define HAMON_TYPE_TRAITS_INVOKE_RESULT_HPP

#include <type_traits>

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703)

namespace hamon
{

using std::invoke_result;

}	// namespace hamon

#else

namespace hamon
{

/**
 *	@brief		関数の戻り値の型を取得する。
 *
 *	@tparam		F			関数または関数オブジェクト
 *	@tparam		ArgTypes	引数
 *
 *	@require	型FおよびArgsTypes...パラメータパックの全ての型は完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	invoke_resultは、関数または関数オブジェクトの型Fに対して、
 *	ArgTypes...を引数として渡した場合の戻り値の型を、メンバ型typeとして定義する。
 *
 *	関数呼び出しが可能でない場合、メンバ型typeは定義されない。
 *	有効でない関数オブジェクト、引数を指定した場合にコンパイルエラーにならず、
 *	SFINAEが働く。
 */
template <typename F, typename... ArgTypes>
struct invoke_result;

}	// namespace hamon

#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/add_rvalue_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/detail/cv_traits.hpp>
#include <hamon/type_traits/detail/is_same_or_base_of.hpp>
#include <hamon/type_traits/detail/member_object_pointer_traits.hpp>
#include <hamon/type_traits/detail/member_function_pointer_traits.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace detail
{

// invoke_result_failure
struct invoke_result_failure {};

// is_mem_fn_callable
template <typename MemFn, typename Arg>
struct is_mem_fn_callable
{
	using MemFnCv = detail::member_function_cv_traits_t<hamon::remove_reference_t<MemFn>>;
	using ArgCv   = detail::cv_traits_t<hamon::remove_reference_t<Arg>>;
	HAMON_STATIC_CONSTEXPR bool value =
		std::is_same<ArgCv, detail::cv_qualifier_none>::value ||
		std::is_same<MemFnCv, detail::cv_qualifier_cv>::value ||
		std::is_same<ArgCv, MemFnCv>::value;
};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-volatile-lvalue")

// is_dereferenceable
template <typename T>
struct is_dereferenceable
{
	template <typename U>
	static auto test(int) -> decltype(*std::declval<U>(), std::true_type());
	template <typename...>
	static auto test(...) -> std::false_type;

	using type = decltype(test<T>(0));
	HAMON_STATIC_CONSTEXPR bool value = type::value;
};

HAMON_WARNING_POP()

// invoke_result_memfun_ref
template <typename F, typename Arg0, typename... Args>
struct invoke_result_memfun_ref
{
	template <typename U, typename UArg0, typename... UArgs>
	static auto test(int) -> hamon::type_identity<decltype((std::declval<UArg0>().*std::declval<U>())(std::declval<UArgs>()...))>;
	template <typename...>
	static auto test(...) -> invoke_result_failure;

	using type =
		hamon::conditional_t<
			is_mem_fn_callable<F, Arg0>::value,
			decltype(test<F, Arg0, Args...>(0)),
			invoke_result_failure>;
};

// invoke_result_memfun_deref
template <typename F, typename Arg0, typename... Args>
struct invoke_result_memfun_deref
	: public invoke_result_memfun_ref<F, decltype(*std::declval<Arg0>()), Args...>
{};

// invoke_result_memfun
template <typename MemFn, typename Obj, typename... Args>
struct invoke_result_memfun
{
	using T = typename member_function_pointer_traits<hamon::remove_reference_t<MemFn>>::class_type;
	using ObjVal = hamon::remove_cv_t<hamon::remove_reference_t<Obj>>;
	using type =
		typename hamon::conditional<
			is_same_or_base_of<hamon::decay_t<T>, ObjVal>::value,
			invoke_result_memfun_ref<MemFn, Obj, Args...>,
			hamon::conditional_t<
				is_dereferenceable<Obj>::value,
				invoke_result_memfun_deref<MemFn, Obj, Args...>,
				hamon::type_identity<invoke_result_failure>
			>
		>::type::type;
};

// invoke_result_pmd
template <typename Ret, typename Class, typename Arg>
struct invoke_result_pmd
{
	using ArgVal = hamon::remove_pointer_t<hamon::remove_reference_t<Arg>>;
	using type =
		hamon::conditional_t<
			is_same_or_base_of<hamon::decay_t<Class>, hamon::decay_t<ArgVal>>::value,
			hamon::conditional_t<
				std::is_pointer<hamon::remove_reference_t<Arg>>::value || std::is_lvalue_reference<Arg>::value,
				hamon::add_lvalue_reference<hamon::copy_cv_t<Ret, ArgVal>>,
				hamon::add_rvalue_reference<hamon::copy_cv_t<Ret, ArgVal>>
			>,
			invoke_result_failure
		>;
};

// invoke_result_memobj
template <typename MemPtr, typename... Args>
struct invoke_result_memobj
{
	using type = invoke_result_failure;
};

template <typename MemPtr, typename Obj>
struct invoke_result_memobj<MemPtr, Obj>
{
	using Traits =
		member_object_pointer_traits<
			hamon::remove_reference_t<MemPtr>
		>;

	using type = typename invoke_result_pmd<
		typename Traits::result_type,
		typename Traits::class_type,
		Obj
	>::type;
};

// invoke_result_other
template <typename F, typename... Args>
struct invoke_result_other
{
	template <typename U, typename... UArgs>
	static auto test(int) -> hamon::type_identity<decltype(std::declval<U>()(std::declval<UArgs>()...))>;
	template <typename...>
	static auto test(...) -> invoke_result_failure;

	using type = decltype(test<F, Args...>(0));
};

// invoke_result_impl
template <bool, bool, typename F, typename... Args>
struct invoke_result_impl
{
	using type = invoke_result_failure;
};

template <typename F, typename Arg, typename... Args>
struct invoke_result_impl<true, false, F, Arg, Args...>
	: public invoke_result_memobj<F, Arg, Args...>
{};

template <typename F, typename Arg, typename... Args>
struct invoke_result_impl<false, true, F, Arg, Args...>
	: public invoke_result_memfun<F, Arg, Args...>
{};

template <typename F, typename... Args>
struct invoke_result_impl<false, false, F, Args...>
	: public invoke_result_other<F, Args...>
{};

}	// namespace detail

// invoke_result
template <typename F, typename... ArgTypes>
struct invoke_result
	: public detail::invoke_result_impl<
		std::is_member_object_pointer<hamon::remove_reference_t<F>>::value,
		std::is_member_function_pointer<hamon::remove_reference_t<F>>::value,
		F, ArgTypes...
	>::type
{};

}	// namespace hamon

#endif

namespace hamon
{

/**
 *	@brief	invoke_resultのエイリアステンプレート
 */
template <typename F, typename... ArgTypes>
using invoke_result_t = typename invoke_result<F, ArgTypes...>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_INVOKE_RESULT_HPP
