/**
 *	@file	weak_ptr.hpp
 *
 *	@brief	hamon::weak_ptr のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_TYPES_WEAK_PTR_HPP
#define HAMON_SERIALIZATION_TYPES_WEAK_PTR_HPP

#include <hamon/serialization/types/shared_ptr.hpp>
#include <hamon/serialization/detail/has_class_version.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <memory>
#endif

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T>
void save(Archive& oa, hamon::weak_ptr<T> const& t)
{
	save(oa, t.lock());
}

template <typename Archive, typename T>
void load(Archive& ia, hamon::weak_ptr<T>& t)
{
	hamon::shared_ptr<T> sp;
	load(ia, sp);
	t = sp;
}

namespace detail
{

template <typename T>
struct has_class_version<hamon::weak_ptr<T>>
	: public hamon::false_type {};

}	// namespace detail

#if !defined(HAMON_NO_STD)
template <typename Archive, typename T>
void save(Archive& oa, std::weak_ptr<T> const& t)
{
	save(oa, t.lock());
}

template <typename Archive, typename T>
void load(Archive& ia, std::weak_ptr<T>& t)
{
	std::shared_ptr<T> sp;
	load(ia, sp);
	t = sp;
}

namespace detail
{

template <typename T>
struct has_class_version<std::weak_ptr<T>>
	: public hamon::false_type {};

}	// namespace detail
#endif

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TYPES_WEAK_PTR_HPP
