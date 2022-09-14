/**
 *	@file	has_adl_save.hpp
 *
 *	@brief	has_adl_saveの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_HPP

#include <type_traits>
#include <utility>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace save_class_detail
{

template <typename Archive, typename T>
void save(Archive&, T const&) = delete;

template <typename... Args>
struct has_adl_save
{
private:
	template <typename... Args2>
	static auto test(int) -> decltype(
		save(std::declval<Args2>()...),
		std::true_type());

	template <typename... Args2>
	static auto test(...) -> std::false_type;

	using type = decltype(test<Args...>(0));

public:
	static const bool value = type::value;
};

}	// namespace save_class_detail

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_HPP
