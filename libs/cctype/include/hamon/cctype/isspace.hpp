/**
 *	@file	isspace.hpp
 *
 *	@brief	isspace の定義
 */

#ifndef HAMON_CCTYPE_ISSPACE_HPP
#define HAMON_CCTYPE_ISSPACE_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct isspace_fn
{
private:
	static HAMON_CXX11_CONSTEXPR bool
	impl(unsigned char c) HAMON_NOEXCEPT
	{
		return (0x09 <= c && c <= 0x0D) || c == 0x20;
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

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::isspace_fn isspace{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_ISSPACE_HPP
