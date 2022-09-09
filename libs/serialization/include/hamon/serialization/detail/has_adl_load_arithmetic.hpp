/**
 *	@file	has_adl_load_arithmetic.hpp
 *
 *	@brief	has_adl_load_arithmeticの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_ARITHMETIC_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_ARITHMETIC_HPP

#include <type_traits>
#include <utility>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename Archive, typename T>
void load_arithmetic(Archive&, T&) = delete;

template <typename Archive, typename T>
struct has_adl_load_arithmetic
{
private:
	template <typename A2, typename T2>
	static auto test(int) -> decltype(
		load_arithmetic(std::declval<A2&>(), std::declval<T2&>()),
		std::true_type());

	template <typename A2, typename T2>
	static auto test(...) -> std::false_type;

	using type = decltype(test<Archive, T>(0));

public:
	static const bool value = type::value;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_ARITHMETIC_HPP
