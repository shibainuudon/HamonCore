/**
 *	@file	has_adl_load_array.hpp
 *
 *	@brief	has_adl_load_arrayの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_ARRAY_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_ARRAY_HPP

#include <type_traits>
#include <utility>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename Archive, typename T>
void load_array(Archive&, T&) = delete;

template <typename... Args>
struct has_adl_load_array
{
private:
	template <typename... Args2>
	static auto test(int) -> decltype(
		load_array(std::declval<Args2>()...),
		std::true_type());

	template <typename... Args2>
	static auto test(...) -> std::false_type;

	using type = decltype(test<Args...>(0));

public:
	static const bool value = type::value;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_ARRAY_HPP
