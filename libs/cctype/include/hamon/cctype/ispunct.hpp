/**
 *	@file	ispunct.hpp
 *
 *	@brief	ispunct の定義
 */

#ifndef HAMON_CCTYPE_ISPUNCT_HPP
#define HAMON_CCTYPE_ISPUNCT_HPP

#include <hamon/cctype/isalnum.hpp>
#include <hamon/cctype/isgraph.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct ispunct_fn
{
private:
	static HAMON_CXX11_CONSTEXPR bool
	impl(unsigned char c) HAMON_NOEXCEPT
	{
		return hamon::isgraph(c) && !hamon::isalnum(c);
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

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::ispunct_fn ispunct{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_ISPUNCT_HPP
