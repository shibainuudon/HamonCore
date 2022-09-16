/**
 *	@file	weak_ptr.hpp
 *
 *	@brief	weak_ptrのシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_WEAK_PTR_HPP
#define HAMON_SERIALIZATION_WEAK_PTR_HPP

#include <hamon/serialization/shared_ptr.hpp>
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

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_WEAK_PTR_HPP
