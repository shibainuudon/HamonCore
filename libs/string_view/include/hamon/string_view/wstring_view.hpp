/**
 *	@file	wstring_view.hpp
 *
 *	@brief	wstring_view クラスの定義
 */

#ifndef HAMON_STRING_VIEW_WSTRING_VIEW_HPP
#define HAMON_STRING_VIEW_WSTRING_VIEW_HPP

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/functional/hash.hpp>

namespace hamon
{

using wstring_view = hamon::basic_string_view<wchar_t>;

template <>
struct hash<hamon::wstring_view>
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::wstring_view sv) const HAMON_NOEXCEPT
	{
		return hamon::detail::hash_array_impl(0, sv.data(), sv.size());
	}
};

}	// namespace hamon

#endif // HAMON_STRING_VIEW_WSTRING_VIEW_HPP
