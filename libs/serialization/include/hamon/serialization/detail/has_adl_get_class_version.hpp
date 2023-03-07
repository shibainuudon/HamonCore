/**
 *	@file	has_adl_get_class_version.hpp
 *
 *	@brief	has_adl_get_class_versionの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_ADL_GET_CLASS_VERSION_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_ADL_GET_CLASS_VERSION_HPP

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace get_class_version_detail
{

template <typename T>
void get_class_version(T const&) = delete;

template <typename T>
struct has_adl_get_class_version
{
private:
	template <typename U,
		typename R = decltype(get_class_version(hamon::declval<U>()))
	>
	static auto test(int) -> hamon::convertible_to_t<R, version_t>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<T>(0));

public:
	static const bool value = type::value;
};

}	// namespace get_class_version_detail

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_ADL_GET_CLASS_VERSION_HPP
