/**
 *	@file	unique_ptr.hpp
 *
 *	@brief	std::unique_ptr のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_UNIQUE_PTR_HPP
#define HAMON_SERIALIZATION_UNIQUE_PTR_HPP

#include <hamon/serialization/detail/save_pointer.hpp>
#include <hamon/serialization/detail/load_pointer.hpp>
#include <hamon/serialization/detail/has_class_version.hpp>
#include <hamon/serialization/nvp.hpp>
#include <memory>

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T>
void save(Archive& oa, std::unique_ptr<T> const& t)
{
	auto const has_value = bool(t);
	oa << make_nvp("has_value", has_value);
	if (has_value)
	{
		hamon::serialization::detail::save_pointer(oa, t.get());
	}
}

template <typename Archive, typename T>
void load(Archive& ia, std::unique_ptr<T>& t)
{
	bool has_value;
	ia >> make_nvp("has_value", has_value);
	if (has_value)
	{
		T* tmp;
		hamon::serialization::detail::load_pointer(ia, tmp);
		t.reset(tmp);
	}
}

// unique_ptr<T[]>は、要素数がわからないのでserialize不可。
template <typename Archive, typename T>
void save(Archive& oa, std::unique_ptr<T[]> const& t) = delete;

template <typename Archive, typename T>
void load(Archive& ia, std::unique_ptr<T[]>& t) = delete;

namespace detail
{

template <typename T>
struct has_class_version<std::unique_ptr<T>>
	: public std::false_type {};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_UNIQUE_PTR_HPP
