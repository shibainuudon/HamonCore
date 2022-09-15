/**
 *	@file	export_class.hpp
 *
 *	@brief	export_classの定義
 */

#ifndef HAMON_SERIALIZATION_EXPORT_CLASS_HPP
#define HAMON_SERIALIZATION_EXPORT_CLASS_HPP

#include <hamon/serialization/detail/pointer_saver.hpp>
#include <hamon/serialization/detail/pointer_loader.hpp>
#include <hamon/serialization/binary_iarchive.hpp>
#include <hamon/serialization/binary_oarchive.hpp>
#include <hamon/serialization/json_iarchive.hpp>
#include <hamon/serialization/json_oarchive.hpp>
#include <hamon/serialization/text_iarchive.hpp>
#include <hamon/serialization/text_oarchive.hpp>

namespace hamon
{

namespace serialization
{

template <typename T>
struct class_exporter
{
	class_exporter()
	{
		hamon::serialization::detail::pointer_saver<binary_oarchive>::get_instance().template register_class<T>();
		hamon::serialization::detail::pointer_saver<text_oarchive>::get_instance().template register_class<T>();
		hamon::serialization::detail::pointer_saver<json_oarchive>::get_instance().template register_class<T>();

		hamon::serialization::detail::pointer_loader<binary_iarchive>::get_instance().template register_class<T>();
		hamon::serialization::detail::pointer_loader<text_iarchive>::get_instance().template register_class<T>();
		hamon::serialization::detail::pointer_loader<json_iarchive>::get_instance().template register_class<T>();
	}
};

#define HAMON_SERIALIZATION_EXPORT_CLASS(T) \
	static const hamon::serialization::class_exporter<T> s_serialization_class_exporter{};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_EXPORT_CLASS_HPP
