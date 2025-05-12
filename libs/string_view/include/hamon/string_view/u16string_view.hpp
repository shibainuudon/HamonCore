/**
 *	@file	u16string_view.hpp
 *
 *	@brief	u16string_view クラスの定義
 */

#ifndef HAMON_STRING_VIEW_U16STRING_VIEW_HPP
#define HAMON_STRING_VIEW_U16STRING_VIEW_HPP

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX11_CHAR16_T)

using u16string_view = hamon::basic_string_view<char16_t>;

template <>
struct hash<hamon::u16string_view>
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::u16string_view sv) const HAMON_NOEXCEPT
	{
		return hamon::detail::hash_array_impl(0, sv.data(), sv.size());
	}
};

#endif

}	// namespace hamon

#endif // HAMON_STRING_VIEW_U16STRING_VIEW_HPP
