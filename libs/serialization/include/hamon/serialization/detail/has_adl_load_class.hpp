/**
 *	@file	has_adl_load_class.hpp
 *
 *	@brief	has_adl_load_classの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_CLASS_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_CLASS_HPP

#include <type_traits>
#include <utility>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename Archive, typename T>
void load_class(Archive&, T&) = delete;

template <typename Archive, typename T>
struct has_adl_load_class
{
private:
	template <typename A2, typename T2>
	static auto test(int) -> decltype(
		load_class(std::declval<A2&>(), std::declval<T2&>()),
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

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_CLASS_HPP
