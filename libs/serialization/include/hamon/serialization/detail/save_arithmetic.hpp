/**
 *	@file	save_arithmetic.hpp
 *
 *	@brief	save_arithmeticの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_SAVE_ARITHMETIC_HPP
#define HAMON_SERIALIZATION_DETAIL_SAVE_ARITHMETIC_HPP

#include <hamon/serialization/detail/has_adl_save_arithmetic.hpp>
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

namespace save_arithmetic_detail
{

struct save_arithmetic_fn
{
private:
	template <typename Archive, typename T,
		typename = hamon::enable_if_t<has_adl_save_arithmetic<Archive&, T const&>::value>>
	static void impl(Archive& ar, T const& t, hamon::detail::overload_priority<1>)
	{
		save_arithmetic(ar, t);
	}

public:
	template <typename Archive, typename T>
	void operator()(Archive& ar, T const& t) const
	{
		impl(ar, t, hamon::detail::overload_priority<1>{});
	}
};

}	// namespace save_arithmetic_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
save_arithmetic_detail::save_arithmetic_fn save_arithmetic{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_SAVE_ARITHMETIC_HPP
