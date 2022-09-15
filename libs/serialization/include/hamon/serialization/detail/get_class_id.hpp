/**
 *	@file	get_class_id.hpp
 *
 *	@brief	get_class_idの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_GET_CLASS_ID_HPP
#define HAMON_SERIALIZATION_DETAIL_GET_CLASS_ID_HPP

#include <hamon/serialization/access.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace get_class_id_detail
{

struct get_class_id_fn
{
private:
	// t.get_class_id();
	template <typename T,
		typename = hamon::enable_if_t<access::has_member_get_class_id<T const&>::value>>
	static const char* impl(T const& t, hamon::detail::overload_priority<1>)
	{
		return access::get_class_id(t);
	}

	// fallback
	template <typename T>
	static const char* impl(T const&, hamon::detail::overload_priority<0>)
	{
		return "";
	}

public:
	template <typename T>
	const char* operator()(T const& t) const
	{
		return impl(t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace get_class_id_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
get_class_id_detail::get_class_id_fn get_class_id{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_GET_CLASS_ID_HPP
