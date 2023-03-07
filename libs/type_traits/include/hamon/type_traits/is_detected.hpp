/**
 *	@file	is_detected.hpp
 *
 *	@brief	is_detected の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_DETECTED_HPP
#define HAMON_TYPE_TRAITS_IS_DETECTED_HPP

#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

template <typename AlwaysVoid, template <typename...> class Op, typename... Args>
struct is_detected_impl
	: public hamon::false_type
{};

template <template <typename...> class Op, typename... Args>
struct is_detected_impl<hamon::void_t<Op<Args...>>, Op, Args...>
	: public hamon::true_type
{};

}	// namespace detail

/**
 *	@brief		Op<Args...>が有効な型かどうかを取得する
 *
 *	@tparam		Op
 *	@tparam		Args
 * 
 *	void_t を使った detection idiom を、さらに簡単にするユーティリティ
 * 
 *	@code
 *	// コピー代入が可能かどうか
 *	template <typename T>
 *	using copy_assignable = decltype(hamon::declval<T&>() = hamon::declval<T const&>());
 *
 *	// value_type型を持っているかどうか
 *	template <typename T>
 *	using has_value_type = typename T::value_type;
 * 
 *	static_assert( hamon::is_detected<copy_assignable, int>::value, "");
 *	static_assert(!hamon::is_detected<copy_assignable, std::unique_ptr<int>>::value, "");
 *	static_assert( hamon::is_detected<copy_assignable, std::shared_ptr<int>>::value, "");
 *	static_assert( hamon::is_detected<copy_assignable, std::vector<int>>::value, "");
 * 
 *	static_assert(!hamon::is_detected<has_value_type, int>::value, "");
 *	static_assert(!hamon::is_detected<has_value_type, std::unique_ptr<int>>::value, "");
 *	static_assert(!hamon::is_detected<has_value_type, std::shared_ptr<int>>::value, "");
 *	static_assert( hamon::is_detected<has_value_type, std::vector<int>>::value, "");
 * 
 *	@endcode
 */
template <template <typename...> class Op, typename... Args>
using is_detected = detail::is_detected_impl<void, Op, Args...>;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_DETECTED_HPP
