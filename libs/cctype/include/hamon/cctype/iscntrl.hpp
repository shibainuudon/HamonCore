/**
 *	@file	iscntrl.hpp
 *
 *	@brief	iscntrl の定義
 */

#ifndef HAMON_CCTYPE_ISCNTRL_HPP
#define HAMON_CCTYPE_ISCNTRL_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct iscntrl_fn
{
private:
	static HAMON_CXX11_CONSTEXPR bool
	impl(unsigned char c) HAMON_NOEXCEPT
	{
		return c <= 0x1F || c == 0x7F;
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

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::iscntrl_fn iscntrl{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_ISCNTRL_HPP
