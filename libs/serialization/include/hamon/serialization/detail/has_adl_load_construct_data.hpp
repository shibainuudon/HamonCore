/**
 *	@file	has_adl_load_construct_data.hpp
 *
 *	@brief	has_adl_load_construct_dataの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_CONSTRUCT_DATA_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_CONSTRUCT_DATA_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <utility>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace load_construct_data_detail
{

template <typename Archive, typename T>
void load_construct_data(Archive&, T*) = delete;

template <typename... Args>
struct has_adl_load_construct_data
{
private:
	template <typename... Args2>
	static auto test(int) -> decltype(
		load_construct_data(std::declval<Args2>()...),
		hamon::true_type());

	template <typename... Args2>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<Args...>(0));

public:
	static const bool value = type::value;
};

}	// namespace load_construct_data_detail

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_CONSTRUCT_DATA_HPP
