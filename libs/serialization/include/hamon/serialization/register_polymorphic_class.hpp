/**
 *	@file	register_polymorphic_class.hpp
 *
 *	@brief	HAMON_SERIALIZATION_REGISTER_POLYMORPHIC_CLASS の定義
 */

#ifndef HAMON_SERIALIZATION_REGISTER_POLYMORPHIC_CLASS_HPP
#define HAMON_SERIALIZATION_REGISTER_POLYMORPHIC_CLASS_HPP

#include <hamon/serialization/detail/polymorphic.hpp>
#include <hamon/serialization/detail/singleton.hpp>

#define HAMON_SERIALIZATION_REGISTER_POLYMORPHIC_CLASS(T)                      \
	static auto const& s_hamon_serialization_register_polymorphic_class ## T = \
		::hamon::serialization::detail::singleton<                             \
			::hamon::serialization::detail::bind_to_archives<T>                \
		>::get_instance();                                                     \

#endif // HAMON_SERIALIZATION_REGISTER_POLYMORPHIC_CLASS_HPP
