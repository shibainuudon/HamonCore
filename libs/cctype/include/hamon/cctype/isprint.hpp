/**
 *	@file	isprint.hpp
 *
 *	@brief	isprint の定義
 */

#ifndef HAMON_CCTYPE_ISPRINT_HPP
#define HAMON_CCTYPE_ISPRINT_HPP

#include <hamon/cctype/isgraph.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct isprint_fn
{
private:
	static HAMON_CXX11_CONSTEXPR bool
	impl(unsigned char c) HAMON_NOEXCEPT
	{
		return hamon::isgraph(c) || c == ' ';
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

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::isprint_fn isprint{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_ISPRINT_HPP
