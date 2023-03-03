/**
 *	@file	base_object.hpp
 *
 *	@brief	base_objectの定義
 */

#ifndef HAMON_SERIALIZATION_BASE_OBJECT_HPP
#define HAMON_SERIALIZATION_BASE_OBJECT_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_base_of.hpp>

namespace hamon
{

namespace serialization
{

template <typename Base, typename Derived,
	typename = hamon::enable_if_t<
		hamon::is_base_of<Base, Derived>::value
	>
>
Base& base_object(Derived& d)
{
	// TODO access::up_cast<Base&>(d);
	return static_cast<Base&>(d);
}

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_BASE_OBJECT_HPP
