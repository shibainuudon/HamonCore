/**
 *	@file	load_string.hpp
 *
 *	@brief	load_stringの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_STRING_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_STRING_HPP

#include <hamon/serialization/detail/has_adl_load_string.hpp>
#include <hamon/serialization/detail/load_vector.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace load_string_detail
{

struct load_string_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load_string<Archive&, T&>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<1>)
	{
		load_string(ar, t);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<0>)
	{
		hamon::serialization::detail::load_vector(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace load_string_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
load_string_detail::load_string_fn load_string{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_STRING_HPP
