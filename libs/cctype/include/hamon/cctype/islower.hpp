/**
 *	@file	islower.hpp
 *
 *	@brief	islower の定義
 */

#ifndef HAMON_CCTYPE_ISLOWER_HPP
#define HAMON_CCTYPE_ISLOWER_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct islower_fn
{
private:
	static HAMON_CXX11_CONSTEXPR bool
	impl(unsigned char c) HAMON_NOEXCEPT
	{
		return 'a' <= c && c <= 'z';
	}

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	operator()(T c) const HAMON_NOEXCEPT
	{
		return c < 0x80 && impl(static_cast<unsigned char>(c));
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::islower_fn islower{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_ISLOWER_HPP
