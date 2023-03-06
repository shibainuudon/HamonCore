/**
 *	@file	addressof_impl.hpp
 *
 *	@brief	addressof_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_ADDRESSOF_IMPL_HPP
#define HAMON_MEMORY_DETAIL_ADDRESSOF_IMPL_HPP

#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_member_address_op_overloaded
{
	template <typename U>
	static auto test(int, hamon::type_identity<decltype(std::declval<U>().operator&())>* = nullptr) -> hamon::true_type;
	template <typename...>
	static auto test(...) -> hamon::false_type;

	static bool const value = hamon::type_identity<decltype(test<T>(0))>::type::value;
};

template <typename T>
struct is_nonmember_address_op_overloaded
{
	template <typename U>
	static auto test(int, hamon::type_identity<decltype(operator&(std::declval<U>()))>* = nullptr) -> hamon::true_type;
	template <typename...>
	static auto test(...) -> hamon::false_type;

	static bool const value = hamon::type_identity<decltype(test<T>(0))>::type::value;
};

template <typename T>
struct is_address_op_overloaded
	: public hamon::bool_constant<
		  is_member_address_op_overloaded<T>::value ||
		  is_nonmember_address_op_overloaded<T>::value
	  >
{};

template <typename T, bool = is_address_op_overloaded<T>::value>
struct addressof_impl;

template <typename T>
struct addressof_impl<T, true>
{
	template <typename U>
	static U* get(U& t) HAMON_NOEXCEPT
	{
		return reinterpret_cast<U*>(
			&const_cast<char&>(
				reinterpret_cast<char const volatile&>(t)));
	}
};

template <typename T>
struct addressof_impl<T, false>
{
	template <typename U>
	static HAMON_CONSTEXPR U* get(U& t) HAMON_NOEXCEPT
	{
		return &t;
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_ADDRESSOF_IMPL_HPP
