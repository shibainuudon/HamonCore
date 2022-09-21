/**
 *	@file	load_pointer.hpp
 *
 *	@brief	load_pointerの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_POINTER_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_POINTER_HPP

#include <hamon/serialization/detail/pointer_loader.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace load_pointer_detail
{

struct load_pointer_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<std::is_class<T>::value>>
	static void impl(Archive& ar, T*& p, hamon::detail::overload_priority<1>)
	{
		std::string id;
		ar >> make_nvp("class_id", id);
		hamon::serialization::detail::pointer_loader<Archive>::get_instance().load(ar, id, p);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T*& p, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::detail::pointer_loader<Archive>::get_instance().load(ar, "", p);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T*& p) const
	{
		impl(ar, p, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace load_pointer_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
load_pointer_detail::load_pointer_fn load_pointer{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_POINTER_HPP
