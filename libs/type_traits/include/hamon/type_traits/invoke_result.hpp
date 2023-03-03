/**
 *	@file	invoke_result.hpp
 *
 *	@brief	invoke_result の定義
 */

#ifndef HAMON_TYPE_TRAITS_INVOKE_RESULT_HPP
#define HAMON_TYPE_TRAITS_INVOKE_RESULT_HPP

#include <hamon/functional/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703) && \
	defined(HAMON_USE_STD_REFERENCE_WRAPPER)

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

#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/type_traits/unwrap_reference.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_base_of.hpp>
#include <hamon/type_traits/is_member_object_pointer.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace detail
{

// invoke_result_failure
struct invoke_result_failure
{};

// invoke_result_memfun_ref
template <typename MemFn, typename Obj, typename... Args>
struct invoke_result_memfun_ref
{
private:
	template <typename UF, typename UArg0, typename... UArgs>
	static auto test(int) -> hamon::type_identity<
		decltype((std::declval<UArg0>().*std::declval<UF>())(std::declval<UArgs>()...))>;

	template <typename...>
	static auto test(...) -> invoke_result_failure;

public:
	using type = decltype(test<MemFn, Obj, Args...>(0));
};

// invoke_result_memfun_deref
template <typename MemFn, typename Obj, typename... Args>
struct invoke_result_memfun_deref
{
private:
	template <typename UF, typename UArg0, typename... UArgs>
	static auto test(int) -> hamon::type_identity<
		decltype(((*std::declval<UArg0>()).*std::declval<UF>())(std::declval<UArgs>()...))>;

	template <typename...>
	static auto test(...) -> invoke_result_failure;

public:
	using type = decltype(test<MemFn, Obj, Args...>(0));
};

// invoke_result_memobj_ref
template <typename MemPtr, typename Obj>
struct invoke_result_memobj_ref
{
private:
	template <typename F, typename T>
	static auto test(int) -> hamon::type_identity<
		decltype(std::declval<T>().*std::declval<F>())>;

	template <typename...>
	static auto test(...) -> invoke_result_failure;

public:
	using type = decltype(test<MemPtr, Obj>(0));
};

// invoke_result_memobj_deref
template <typename MemPtr, typename Arg>
struct invoke_result_memobj_deref
{
private:
	template <typename F, typename T>
	static auto test(int) -> hamon::type_identity<
		decltype((*std::declval<T>()).*std::declval<F>())>;

	template <typename...>
	static auto test(...) -> invoke_result_failure;

public:
	using type = decltype(test<MemPtr, Arg>(0));
};

// invoke_result_memobj
template <typename MemPtr, typename Arg>
struct invoke_result_memobj;

template <typename Res, typename Class, typename Arg>
struct invoke_result_memobj<Res Class::*, Arg>
{
private:
	using Argval = hamon::remove_cvref_t<Arg>;
	using MemPtr = Res Class::*;

public:
	using type = typename hamon::conditional_t<
		hamon::disjunction<
			hamon::is_same<Argval, Class>,
			hamon::is_base_of<Class, Argval>
		>::value,
		invoke_result_memobj_ref<MemPtr, Arg>,
		invoke_result_memobj_deref<MemPtr, Arg>
	>::type;
};

// invoke_result_memfun
template <typename MemPtr, typename Arg, typename... Args>
struct invoke_result_memfun;

template <typename Res, typename Class, typename Arg, typename... Args>
struct invoke_result_memfun<Res Class::*, Arg, Args...>
{
private:
	using Argval = hamon::remove_reference_t<Arg>;
	using MemPtr = Res Class::*;

public:
	using type = typename hamon::conditional_t<
		hamon::is_base_of<Class, Argval>::value,
		invoke_result_memfun_ref<MemPtr, Arg, Args...>,
		invoke_result_memfun_deref<MemPtr, Arg, Args...>
	>::type;
};

// invoke_result_other
template <typename F, typename... Args>
struct invoke_result_other
{
private:
	template <typename U, typename... UArgs>
	static auto test(int) -> hamon::type_identity<decltype(std::declval<U>()(std::declval<UArgs>()...))>;

	template <typename...>
	static auto test(...) -> invoke_result_failure;

public:
	using type = decltype(test<F, Args...>(0));
};

// invoke_result_impl
template <bool, bool, typename F, typename... Args>
struct invoke_result_impl
{
	using type = invoke_result_failure;
};

template <typename MemPtr, typename Arg>
struct invoke_result_impl<true, false, MemPtr, Arg>
	: public invoke_result_memobj<
		hamon::decay_t<MemPtr>,
		hamon::unwrap_reference_t<Arg>
	>
{};

template <typename MemPtr, typename Arg, typename... Args>
struct invoke_result_impl<false, true, MemPtr, Arg, Args...>
	: public invoke_result_memfun<
		hamon::decay_t<MemPtr>,
		hamon::unwrap_reference_t<Arg>,
		Args...
	>
{};

template <typename F, typename... Args>
struct invoke_result_impl<false, false, F, Args...>
	: public invoke_result_other<F, Args...>
{
};

// detail::invoke_result
template <typename F, typename... ArgTypes>
struct invoke_result
	: public invoke_result_impl<
		hamon::is_member_object_pointer<hamon::remove_reference_t<F>>::value,
		std::is_member_function_pointer<hamon::remove_reference_t<F>>::value,
		F, ArgTypes...
	>::type
{};

}	// namespace detail

// invoke_result
template <typename F, typename... ArgTypes>
struct invoke_result
	: public hamon::detail::invoke_result<F, ArgTypes...>
{
	//static_assert(std::__is_complete_or_unbounded(__type_identity<F>{}),
	//	"F must be a complete class or an unbounded array");
	//static_assert((std::__is_complete_or_unbounded(
	//	__type_identity<ArgTypes>{}) && ...),
	//	"each argument type must be a complete class or an unbounded array");
};

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
