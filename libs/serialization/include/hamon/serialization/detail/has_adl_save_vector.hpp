/**
 *	@file	has_adl_save_vector.hpp
 *
 *	@brief	has_adl_save_vectorの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_VECTOR_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_VECTOR_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace save_vector_detail
{

template <typename Archive, typename T>
void save_vector(Archive&, T const&) = delete;

template <typename... Args>
struct has_adl_save_vector
{
private:
	template <typename... Args2>
	static auto test(int) -> decltype(
		save_vector(hamon::declval<Args2>()...),
		hamon::true_type());

	template <typename... Args2>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<Args...>(0));

public:
	static const bool value = type::value;
};

}	// namespace save_vector_detail

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_SAVE_VECTOR_HPP
