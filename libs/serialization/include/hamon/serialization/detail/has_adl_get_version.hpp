/**
 *	@file	has_adl_get_version.hpp
 *
 *	@brief	has_adl_get_versionの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_GET_VERSION_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_GET_VERSION_HPP

#include <hamon/concepts/convertible_to.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename T>
void get_version(T const&) = delete;

template <typename T>
struct has_adl_get_version
{
private:
	template <typename U,
		typename R = decltype(get_version(std::declval<U>()))
	>
	static auto test(int) -> hamon::convertible_to_t<R, version_t>;

	template <typename U>
	static auto test(...) -> std::false_type;

	using type = decltype(test<T>(0));

public:
	static const bool value = type::value;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_GET_VERSION_HPP
