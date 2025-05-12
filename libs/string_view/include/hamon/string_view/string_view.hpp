/**
 *	@file	string_view.hpp
 *
 *	@brief	string_view クラスの定義
 */

#ifndef HAMON_STRING_VIEW_STRING_VIEW_HPP
#define HAMON_STRING_VIEW_STRING_VIEW_HPP

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/functional/hash.hpp>

namespace hamon
{

using string_view = hamon::basic_string_view<char>;

// 27.3.6 Hash support[string.view.hash]

template <>
struct hash<hamon::string_view>
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::string_view sv) const HAMON_NOEXCEPT
	{
		return hamon::detail::hash_array_impl(0, sv.data(), sv.size());
	}
};

}	// namespace hamon

#endif // HAMON_STRING_VIEW_STRING_VIEW_HPP
