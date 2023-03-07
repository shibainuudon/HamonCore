/**
 *	@file	has_adl_serialize.hpp
 *
 *	@brief	has_adl_serializeの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_SERIALIZE_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_SERIALIZE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace serialize_value_detail
{

template <typename Archive, typename T>
void serialize(Archive&, T&) = delete;

template <typename... Args>
struct has_adl_serialize
{
private:
	template <typename... Args2>
	static auto test(int) -> decltype(
		serialize(hamon::declval<Args2>()...),
		hamon::true_type());

	template <typename... Args2>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<Args...>(0));

public:
	static const bool value = type::value;
};

}	// namespace serialize_value_detail

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_SERIALIZE_HPP
