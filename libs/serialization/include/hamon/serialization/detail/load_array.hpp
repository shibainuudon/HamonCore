/**
 *	@file	load_array.hpp
 *
 *	@brief	load_arrayの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_ARRAY_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_ARRAY_HPP

#include <hamon/serialization/detail/has_adl_load_array.hpp>
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

namespace load_array_detail
{

struct load_array_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load_array<Archive&, T&>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<1>)
	{
		load_array(ar, t);
	}

	template <typename Archive, typename T>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<0>)
	{
		for (auto&& x : t)
		{
			ar >> x;
		}
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace load_array_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR load_array_detail::load_array_fn load_array{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_ARRAY_HPP
