/**
 *	@file	has_adl_load_arithmetic.hpp
 *
 *	@brief	has_adl_load_arithmeticの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_ARITHMETIC_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_ARITHMETIC_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace load_arithmetic_detail
{

template <typename Archive, typename T>
void load_arithmetic(Archive&, T&) = delete;

template <typename... Args>
struct has_adl_load_arithmetic
{
private:
	template <typename... Args2>
	static auto test(int) -> decltype(
		load_arithmetic(hamon::declval<Args2>()...),
		hamon::true_type());

	template <typename... Args2>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<Args...>(0));

public:
	static const bool value = type::value;
};

}	// namespace load_arithmetic_detail

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_ARITHMETIC_HPP
