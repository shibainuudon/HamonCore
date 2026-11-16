/**
 *	@file	unique_ptr.hpp
 *
 *	@brief	hamon::unique_ptr のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_TYPES_UNIQUE_PTR_HPP
#define HAMON_SERIALIZATION_TYPES_UNIQUE_PTR_HPP

#include <hamon/serialization/detail/save_pointer.hpp>
#include <hamon/serialization/detail/load_pointer.hpp>
#include <hamon/serialization/detail/has_class_version.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <memory>
#endif

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename Archive, typename UniquePtr>
void save_unique_ptr(Archive& oa, UniquePtr const& up)
{
	auto const has_value = bool(up);
	oa << make_nvp("has_value", has_value);
	if (has_value)
	{
		hamon::serialization::detail::save_pointer(oa, up.get());
	}
}

template <typename Archive, typename UniquePtr>
void load_unique_ptr(Archive& ia, UniquePtr& up)
{
	bool has_value;
	ia >> make_nvp("has_value", has_value);
	if (has_value)
	{
		typename UniquePtr::element_type* tmp;
		hamon::serialization::detail::load_pointer(ia, tmp);
		up.reset(tmp);
	}
}

}	// namespace detail

template <typename Archive, typename T>
void save(Archive& oa, hamon::unique_ptr<T> const& up)
{
	save_unique_ptr(oa, up);
}

template <typename Archive, typename T>
void load(Archive& ia, hamon::unique_ptr<T>& up)
{
	load_unique_ptr(ia, up);
}

// unique_ptr<T[]>は、要素数がわからないのでserialize不可。
template <typename Archive, typename T>
void save(Archive& oa, hamon::unique_ptr<T[]> const& up) = delete;

template <typename Archive, typename T>
void load(Archive& ia, hamon::unique_ptr<T[]>& up) = delete;

namespace detail
{

template <typename T>
struct has_class_version<hamon::unique_ptr<T>>
	: public hamon::false_type {};

}	// namespace detail

#if !defined(HAMON_NO_STD)
template <typename Archive, typename T>
void save(Archive& oa, std::unique_ptr<T> const& up)
{
	save_unique_ptr(oa, up);
}

template <typename Archive, typename T>
void load(Archive& ia, std::unique_ptr<T>& up)
{
	load_unique_ptr(ia, up);
}

// unique_ptr<T[]>は、要素数がわからないのでserialize不可。
template <typename Archive, typename T>
void save(Archive& oa, std::unique_ptr<T[]> const& up) = delete;

template <typename Archive, typename T>
void load(Archive& ia, std::unique_ptr<T[]>& up) = delete;

namespace detail
{

template <typename T>
struct has_class_version<std::unique_ptr<T>>
	: public hamon::false_type {};

}	// namespace detail
#endif

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TYPES_UNIQUE_PTR_HPP
