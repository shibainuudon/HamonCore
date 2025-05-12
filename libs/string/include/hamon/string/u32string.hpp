/**
 *	@file	u32string.hpp
 *
 *	@brief	u32string の定義
 */

#ifndef HAMON_STRING_U32STRING_HPP
#define HAMON_STRING_U32STRING_HPP

#include <hamon/string/basic_string.hpp>
#include <hamon/string/literals.hpp>
#include <hamon/string/typedefs.hpp>
#include <hamon/functional/hash.hpp>

namespace hamon
{

// 27.4.6 Hash support[basic.string.hash]

#if defined(HAMON_HAS_CXX11_CHAR32_T)
template <typename A>
struct hash<hamon::basic_string<char32_t, hamon::char_traits<char32_t>, A>>
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::basic_string<char32_t, hamon::char_traits<char32_t>, A> const& s) const HAMON_NOEXCEPT
	{
		return hamon::detail::hash_array_impl(0, s.data(), s.size());
	}
};
#endif

}	// namespace hamon

#endif // HAMON_STRING_U32STRING_HPP
