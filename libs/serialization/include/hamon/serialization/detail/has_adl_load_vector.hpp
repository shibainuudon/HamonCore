/**
 *	@file	has_adl_load_vector.hpp
 *
 *	@brief	has_adl_load_vectorの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_VECTOR_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_VECTOR_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <utility>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace load_vector_detail
{

template <typename Archive, typename T>
void load_vector(Archive&, T&) = delete;

template <typename... Args>
struct has_adl_load_vector
{
private:
	template <typename... Args2>
	static auto test(int) -> decltype(
		load_vector(std::declval<Args2>()...),
		hamon::true_type());

	template <typename... Args2>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<Args...>(0));

public:
	static const bool value = type::value;
};

}	// namespace load_vector_detail

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_LOAD_VECTOR_HPP
