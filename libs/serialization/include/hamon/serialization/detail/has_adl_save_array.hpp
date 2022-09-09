/**
 *	@file	has_adl_save_array.hpp
 *
 *	@brief	has_adl_save_arrayの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_ARRAY_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_ARRAY_HPP

#include <type_traits>
#include <utility>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename Archive, typename T>
void save_array(Archive&, T const&) = delete;

template <typename Archive, typename T>
struct has_adl_save_array
{
private:
	template <typename A2, typename T2>
	static auto test(int) -> decltype(
		save_array(std::declval<A2&>(), std::declval<T2 const&>()),
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

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_ARRAY_HPP
