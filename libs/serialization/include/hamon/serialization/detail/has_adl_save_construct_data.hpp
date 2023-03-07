/**
 *	@file	has_adl_save_construct_data.hpp
 *
 *	@brief	has_adl_save_construct_dataの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_CONSTRUCT_DATA_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_CONSTRUCT_DATA_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace save_construct_data_detail
{

template <typename Archive, typename T>
void save_construct_data(Archive&, T const*) = delete;

template <typename... Args>
struct has_adl_save_construct_data
{
private:
	template <typename... Args2>
	static auto test(int) -> decltype(
		save_construct_data(hamon::declval<Args2>()...),
		hamon::true_type());

	template <typename... Args2>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<Args...>(0));

public:
	static const bool value = type::value;
};

}	// namespace save_construct_data_detail

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_CONSTRUCT_DATA_HPP
