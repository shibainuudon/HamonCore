/**
 *	@file	has_adl_save_string.hpp
 *
 *	@brief	has_adl_save_stringの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_STRING_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_STRING_HPP

#include <type_traits>
#include <utility>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename Archive, typename T>
void save_string(Archive&, T const&) = delete;

template <typename... Args>
struct has_adl_save_string
{
private:
	template <typename... Args2>
	static auto test(int) -> decltype(
		save_string(std::declval<Args2>()...),
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

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_STRING_HPP
