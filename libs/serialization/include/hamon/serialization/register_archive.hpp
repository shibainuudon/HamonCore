/**
 *	@file	register_archive.hpp
 *
 *	@brief	HAMON_SERIALIZATION_REGISTER_OARCHIVE, HAMON_SERIALIZATION_REGISTER_IARCHIVE の定義
 */

#ifndef HAMON_SERIALIZATION_REGISTER_ARCHIVE_HPP
#define HAMON_SERIALIZATION_REGISTER_ARCHIVE_HPP

#include <hamon/serialization/detail/polymorphic.hpp>

#define HAMON_SERIALIZATION_REGISTER_OARCHIVE(Archive)                          \
namespace hamon { namespace serialization { namespace detail {                  \
template <typename T, typename BindingTag>                                      \
typename polymorphic_serialization_support<Archive, T, bind_oarchive_tag>::type \
instantiate_polymorphic_binding(T*, Archive*, BindingTag);                      \
}}}	// namespace hamon::serialization::detail

#define HAMON_SERIALIZATION_REGISTER_IARCHIVE(Archive)                          \
namespace hamon { namespace serialization { namespace detail {                  \
template <typename T, typename BindingTag>                                      \
typename polymorphic_serialization_support<Archive, T, bind_iarchive_tag>::type \
instantiate_polymorphic_binding(T*, Archive*, BindingTag);                      \
}}}	// namespace hamon::serialization::detail

#endif // HAMON_SERIALIZATION_REGISTER_ARCHIVE_HPP
