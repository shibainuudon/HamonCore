/**
 *	@file	has_class_version.hpp
 *
 *	@brief	has_class_versionの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_HAS_CLASS_VERSION_HPP
#define HAMON_SERIALIZATION_DETAIL_HAS_CLASS_VERSION_HPP

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename T>
struct has_class_version : public hamon::true_type {};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_HAS_CLASS_VERSION_HPP
