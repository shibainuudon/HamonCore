/**
 *	@file	shared_ptr.hpp
 *
 *	@brief	hamon::shared_ptr のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_TYPES_SHARED_PTR_HPP
#define HAMON_SERIALIZATION_TYPES_SHARED_PTR_HPP

#include <hamon/serialization/detail/save_pointer.hpp>
#include <hamon/serialization/detail/load_pointer.hpp>
#include <hamon/serialization/detail/has_class_version.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/memory/shared_ptr.hpp>
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

template <typename Archive, typename SharedPtr>
void save_shared_ptr(Archive& oa, SharedPtr const& sp)
{
	auto const has_value = bool(sp);
	oa << make_nvp("has_value", has_value);
	if (has_value)
	{
		int index = oa.get_shared_ptr_index(sp);
		oa << make_nvp("shared_index", index);
		if (index < 0)
		{
			hamon::serialization::detail::save_pointer(oa, sp.get());

			oa.register_shared_ptr(sp);
		}
	}
}

template <typename Archive, typename SharedPtr>
void load_shared_ptr(Archive& ia, SharedPtr& sp)
{
	bool has_value;
	ia >> make_nvp("has_value", has_value);
	if (has_value)
	{
		int index;
		ia >> make_nvp("shared_index", index);
		if (index < 0)
		{
			typename SharedPtr::element_type* tmp;
			hamon::serialization::detail::load_pointer(ia, tmp);
			sp.reset(tmp);

			ia.register_shared_ptr(sp);
		}
		else
		{
			ia.get_shared_ptr(sp, index);
		}
	}
}

}	// namespace detail

template <typename Archive, typename T>
void save(Archive& oa, hamon::shared_ptr<T> const& sp)
{
	detail::save_shared_ptr(oa, sp);
}

template <typename Archive, typename T>
void load(Archive& ia, hamon::shared_ptr<T>& sp)
{
	detail::load_shared_ptr(ia, sp);
}

// shared_ptr<T[]>は、要素数がわからないのでserialize不可。
template <typename Archive, typename T>
void save(Archive& oa, hamon::shared_ptr<T[]> const& sp) = delete;

template <typename Archive, typename T>
void load(Archive& ia, hamon::shared_ptr<T[]>& sp) = delete;

namespace detail
{

template <typename T>
struct has_class_version<hamon::shared_ptr<T>>
	: public hamon::false_type {};

}	// namespace detail

#if !defined(HAMON_NO_STD)
template <typename Archive, typename T>
void save(Archive& oa, std::shared_ptr<T> const& sp)
{
	detail::save_shared_ptr(oa, sp);
}

template <typename Archive, typename T>
void load(Archive& ia, std::shared_ptr<T>& sp)
{
	detail::load_shared_ptr(ia, sp);
}

// shared_ptr<T[]>は、要素数がわからないのでserialize不可。
template <typename Archive, typename T>
void save(Archive& oa, std::shared_ptr<T[]> const& sp) = delete;

template <typename Archive, typename T>
void load(Archive& ia, std::shared_ptr<T[]>& sp) = delete;

namespace detail
{

template <typename T>
struct has_class_version<std::shared_ptr<T>>
	: public hamon::false_type {};

}	// namespace detail
#endif

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TYPES_SHARED_PTR_HPP
