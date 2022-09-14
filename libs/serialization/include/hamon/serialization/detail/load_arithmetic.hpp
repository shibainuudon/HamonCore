/**
 *	@file	load_arithmetic.hpp
 *
 *	@brief	load_arithmeticの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_LOAD_ARITHMETIC_HPP
#define HAMON_SERIALIZATION_DETAIL_LOAD_ARITHMETIC_HPP

#include <hamon/serialization/detail/has_adl_load_arithmetic.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

namespace load_arithmetic_detail
{

struct load_arithmetic_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_load_arithmetic<Archive&, T&>::value>>
	static void impl(Archive& ar, T& t, hamon::detail::overload_priority<1>)
	{
		load_arithmetic(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace load_arithmetic_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
load_arithmetic_detail::load_arithmetic_fn load_arithmetic{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_LOAD_ARITHMETIC_HPP
