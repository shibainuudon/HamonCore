﻿/**
 *	@file	weak_ptr.hpp
 *
 *	@brief	std::weak_ptr のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_TYPES_WEAK_PTR_HPP
#define HAMON_SERIALIZATION_TYPES_WEAK_PTR_HPP

#include <hamon/serialization/types/shared_ptr.hpp>
#include <hamon/serialization/detail/has_class_version.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <memory>

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T>
void save(Archive& oa, std::weak_ptr<T> const& t)
{
	auto sp = t.lock();
	save(oa, sp);
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

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TYPES_WEAK_PTR_HPP
