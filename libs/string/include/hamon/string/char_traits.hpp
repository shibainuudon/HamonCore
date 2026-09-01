/**
 *	@file	char_traits.hpp
 *
 *	@brief	char_traits クラステンプレートの定義
 */

#ifndef HAMON_STRING_CHAR_TRAITS_HPP
#define HAMON_STRING_CHAR_TRAITS_HPP

#include <hamon/string/char_traits_fwd.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uint_least16_t.hpp>
#include <hamon/cstdint/uint_least32_t.hpp>
#include <hamon/ios/streamoff.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <ios>		// streampos, u8streampos, u16streampos, u32streampos, wstreampos
#include <cwchar>	// mbstate_t, wmemcmp, wcslen, wmemchr, wmemmove, wmemcpy, wmemset
#include <cstdio>	// EOF
#include <cstring>	// memcmp, strlen, memchr, memmove, memcpy, memset

namespace hamon
{

namespace detail
{

struct char_traits_fallback
{
	template <typename char_type>
	static HAMON_CXX14_CONSTEXPR
	int compare(char_type const* s1, char_type const* s2, hamon::size_t n)
	{
		for (; 0 < n; --n, ++s1, ++s2)
		{
			if (*s1 != *s2)
			{
				return *s1 < *s2 ? -1 : 1;
			}
		}

		return 0;
	}

	template <typename char_type>
	static HAMON_CXX14_CONSTEXPR
	hamon::size_t length(char_type const* s)
	{
		size_t count = 0;
		while (*s != char_type())
		{
			++count;
			++s;
		}

		return count;
	}

	template <typename char_type>
	static HAMON_CXX14_CONSTEXPR
	char_type const* find(char_type const* s, hamon::size_t n, char_type const& a)
	{
		for (; 0 < n; --n, ++s)
		{
			if (*s == a)
			{
				return s;
			}
		}

		return nullptr;
	}

	template <typename char_type>
	static HAMON_CXX14_CONSTEXPR
	char_type* move(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (s2 < s1 && s1 < s2 + n)
		{
			// copy backward
			for (hamon::size_t i = n; i != 0; --i)
			{
				s1[i - 1] = s2[i - 1];
			}
		}
		else
		{
			// copy forward
			for (hamon::size_t i = 0; i != n; ++i)
			{
				s1[i] = s2[i];
			}
		}

		return s1;
	}

	template <typename char_type>
	static HAMON_CXX14_CONSTEXPR
	char_type* copy(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		for (hamon::size_t i = 0; i != n; ++i)
		{
			s1[i] = s2[i];
		}

		return s1;
	}

	template <typename char_type>
	static HAMON_CXX14_CONSTEXPR
	char_type* assign(char_type* s, hamon::size_t n, char_type a)
	{
		for (char_type* p = s; n > 0; --n, ++p)
		{
			*p = a;
		}

		return s;
	}
};

}	// namespace detail


// 27.2 Character traits[char.traits]

template <class charT>
struct char_traits;

// 27.2.4.2 struct char_traits<char>[char.traits.specializations.char]
template <>
struct char_traits<char>
{
	using char_type  = char;
	using int_type   = int;
	using off_type   = hamon::streamoff;
	using pos_type   = std::streampos;
	using state_type = std::mbstate_t;
	using comparison_category = hamon::strong_ordering;

	static HAMON_CXX14_CONSTEXPR
	void assign(char_type& c1, char_type const& c2) noexcept
	{
		c1 = c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq(char_type c1, char_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool lt(char_type c1, char_type c2) noexcept
	{
		return static_cast<unsigned char>(c1) < static_cast<unsigned char>(c2);
	}

	static HAMON_CXX14_CONSTEXPR
	int compare(char_type const* s1, char_type const* s2, hamon::size_t n)
	{
#if defined(HAMON_MSVC) || defined(HAMON_CLANG)
		return __builtin_memcmp(s1, s2, n);
#else
		if (!hamon::is_constant_evaluated())
		{
			return std::memcmp(s1, s2, n);
		}
		return detail::char_traits_fallback::compare(s1, s2, n);
#endif
	}

	static HAMON_CXX14_CONSTEXPR
	hamon::size_t length(char_type const* s)
	{
#if defined(HAMON_MSVC) || defined(HAMON_CLANG)
		return __builtin_strlen(s);
#else
		if (!hamon::is_constant_evaluated())
		{
			return std::strlen(s);
		}
		return detail::char_traits_fallback::length(s);
#endif
	}

	static HAMON_CXX14_CONSTEXPR
	char_type const* find(char_type const* s, hamon::size_t n, char_type const& a)
	{
#if HAMON_HAS_BUILTIN(__builtin_char_memchr) || defined(HAMON_MSVC)
		return __builtin_char_memchr(s, a, n);
#else
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type const*>(std::memchr(s, a, n));
		}
		return detail::char_traits_fallback::find(s, n, a);
#endif
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* move(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memmove(s1, s2, n * sizeof(char_type)));
		}
		return detail::char_traits_fallback::move(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* copy(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memcpy(s1, s2, n * sizeof(char_type)));
		}
		return detail::char_traits_fallback::copy(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* assign(char_type* s, hamon::size_t n, char_type a)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memset(s, a, n));
		}
		return detail::char_traits_fallback::assign(s, n, a);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type not_eof(int_type c) noexcept
	{
		return (c == eof()) ? 0 : c;
	}

	static HAMON_CXX14_CONSTEXPR
	char_type to_char_type(int_type c) noexcept
	{
		return static_cast<char_type>(c);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type to_int_type(char_type c) noexcept
	{
		return static_cast<int_type>(static_cast<unsigned char>(c));
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq_int_type(int_type c1, int_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	int_type eof() noexcept
	{
		return static_cast<int_type>(EOF);
	}
};

#if defined(HAMON_HAS_CXX20_CHAR8_T)
// 27.2.4.3 struct char_traits<char8_t>[char.traits.specializations.char8.t]
template <>
struct char_traits<char8_t>
{
	using char_type  = char8_t;
	using int_type   = unsigned int;
	using off_type   = hamon::streamoff;
	using pos_type   = std::u8streampos;
	using state_type = std::mbstate_t;
	using comparison_category = hamon::strong_ordering;

	static HAMON_CXX14_CONSTEXPR
	void assign(char_type& c1, char_type const& c2) noexcept
	{
		c1 = c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq(char_type c1, char_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool lt(char_type c1, char_type c2) noexcept
	{
		return c1 < c2;
	}

	static HAMON_CXX14_CONSTEXPR
	int compare(char_type const* s1, char_type const* s2, hamon::size_t n)
	{
#if defined(HAMON_MSVC)
		return __builtin_memcmp(s1, s2, n);
#else
		if (!hamon::is_constant_evaluated())
		{
			return std::memcmp(s1, s2, n);
		}
		return detail::char_traits_fallback::compare(s1, s2, n);
#endif
	}

	static HAMON_CXX14_CONSTEXPR
	hamon::size_t length(char_type const* s)
	{
#if defined(HAMON_MSVC)
		return __builtin_u8strlen(s);
#else
		if (!hamon::is_constant_evaluated())
		{
			return std::strlen(reinterpret_cast<char const*>(s));
		}
		return detail::char_traits_fallback::length(s);
#endif
	}

	static HAMON_CXX14_CONSTEXPR
	char_type const* find(char_type const* s, hamon::size_t n, char_type const& a)
	{
#if defined(HAMON_MSVC)
		return __builtin_u8memchr(s, a, n);
#else
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type const*>(std::memchr(s, a, n));
		}
		return detail::char_traits_fallback::find(s, n, a);
#endif
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* move(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memmove(s1, s2, n * sizeof(char_type)));
		}
		return detail::char_traits_fallback::move(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* copy(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memcpy(s1, s2, n * sizeof(char_type)));
		}
		return detail::char_traits_fallback::copy(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* assign(char_type* s, hamon::size_t n, char_type a)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memset(s, a, n));
		}
		return detail::char_traits_fallback::assign(s, n, a);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type not_eof(int_type c) noexcept
	{
		return !eq_int_type(c, eof()) ? c : to_int_type(char_type());
	}

	static HAMON_CXX14_CONSTEXPR
	char_type to_char_type(int_type c) noexcept
	{
		return static_cast<char_type>(c);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type to_int_type(char_type c) noexcept
	{
		return static_cast<int_type>(c);
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq_int_type(int_type c1, int_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	int_type eof() noexcept
	{
		return static_cast<int_type>(-1);
	}
};
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
// 27.2.4.4 struct char_traits<char16_t>[char.traits.specializations.char16.t]
template <>
struct char_traits<char16_t>
{
	using char_type  = char16_t;
	using int_type   = hamon::uint_least16_t;
	using off_type   = hamon::streamoff;
	using pos_type   = std::u16streampos;
	using state_type = std::mbstate_t;
	using comparison_category = hamon::strong_ordering;

	static HAMON_CXX14_CONSTEXPR
	void assign(char_type& c1, char_type const& c2) noexcept
	{
		c1 = c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq(char_type c1, char_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool lt(char_type c1, char_type c2) noexcept
	{
		return c1 < c2;
	}

	static HAMON_CXX14_CONSTEXPR
	int compare(char_type const* s1, char_type const* s2, hamon::size_t n)
	{
		return detail::char_traits_fallback::compare(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	hamon::size_t length(char_type const* s)
	{
		return detail::char_traits_fallback::length(s);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type const* find(char_type const* s, hamon::size_t n, char_type const& a)
	{
		return detail::char_traits_fallback::find(s, n, a);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* move(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memmove(s1, s2, n * sizeof(char_type)));
		}
		return detail::char_traits_fallback::move(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* copy(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memcpy(s1, s2, n * sizeof(char_type)));
		}
		return detail::char_traits_fallback::copy(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* assign(char_type* s, hamon::size_t n, char_type a)
	{
		return detail::char_traits_fallback::assign(s, n, a);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type not_eof(int_type c) noexcept
	{
		return !eq_int_type(c, eof()) ? c : to_int_type(char_type());
	}

	static HAMON_CXX14_CONSTEXPR
	char_type to_char_type(int_type c) noexcept
	{
		return static_cast<char_type>(c);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type to_int_type(char_type c) noexcept
	{
		return static_cast<int_type>(c);
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq_int_type(int_type c1, int_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	int_type eof() noexcept
	{
		return static_cast<int_type>(-1);
	}
};
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
// 27.2.4.5 struct char_traits<char32_t>[char.traits.specializations.char32.t]
template <>
struct char_traits<char32_t>
{
	using char_type  = char32_t;
	using int_type   = hamon::uint_least32_t;
	using off_type   = hamon::streamoff;
	using pos_type   = std::u32streampos;
	using state_type = std::mbstate_t;
	using comparison_category = hamon::strong_ordering;

	static HAMON_CXX14_CONSTEXPR
	void assign(char_type& c1, char_type const& c2) noexcept
	{
		c1 = c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq(char_type c1, char_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool lt(char_type c1, char_type c2) noexcept
	{
		return c1 < c2;
	}

	static HAMON_CXX14_CONSTEXPR
	int compare(char_type const* s1, char_type const* s2, hamon::size_t n)
	{
		return detail::char_traits_fallback::compare(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	hamon::size_t length(char_type const* s)
	{
		return detail::char_traits_fallback::length(s);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type const* find(char_type const* s, hamon::size_t n, char_type const& a)
	{
		return detail::char_traits_fallback::find(s, n, a);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* move(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memmove(s1, s2, n * sizeof(char_type)));
		}
		return detail::char_traits_fallback::move(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* copy(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return static_cast<char_type*>(std::memcpy(s1, s2, n * sizeof(char_type)));
		}
		return detail::char_traits_fallback::copy(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* assign(char_type* s, hamon::size_t n, char_type a)
	{
		return detail::char_traits_fallback::assign(s, n, a);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type not_eof(int_type c) noexcept
	{
		return !eq_int_type(c, eof()) ? c : to_int_type(char_type());
	}

	static HAMON_CXX14_CONSTEXPR
	char_type to_char_type(int_type c) noexcept
	{
		return static_cast<char_type>(c);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type to_int_type(char_type c) noexcept
	{
		return static_cast<int_type>(c);
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq_int_type(int_type c1, int_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	int_type eof() noexcept
	{
		return static_cast<int_type>(-1);
	}
};
#endif

// 27.2.4.6 struct char_traits<wchar_t>[char.traits.specializations.wchar.t]
template <>
struct char_traits<wchar_t>
{
	using char_type  = wchar_t;
	using int_type   = std::wint_t;
	using off_type   = hamon::streamoff;
	using pos_type   = std::wstreampos;
	using state_type = std::mbstate_t;
	using comparison_category = hamon::strong_ordering;

	static HAMON_CXX14_CONSTEXPR
	void assign(char_type& c1, char_type const& c2) noexcept
	{
		c1 = c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq(char_type c1, char_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	bool lt(char_type c1, char_type c2) noexcept
	{
		return c1 < c2;
	}

	static HAMON_CXX14_CONSTEXPR
	int compare(char_type const* s1, char_type const* s2, hamon::size_t n)
	{
#if HAMON_HAS_BUILTIN(__builtin_wmemcmp) || defined(HAMON_MSVC)
		return __builtin_wmemcmp(s1, s2, n);
#else
		if (!hamon::is_constant_evaluated())
		{
			return std::wmemcmp(s1, s2, n);
		}
		return detail::char_traits_fallback::compare(s1, s2, n);
#endif
	}

	static HAMON_CXX14_CONSTEXPR
	hamon::size_t length(char_type const* s)
	{
#if HAMON_HAS_BUILTIN(__builtin_wcslen) || defined(HAMON_MSVC)
		return __builtin_wcslen(s);
#else
		if (!hamon::is_constant_evaluated())
		{
			return std::wcslen(s);
		}
		return detail::char_traits_fallback::length(s);
#endif
	}

	static HAMON_CXX14_CONSTEXPR
	char_type const* find(char_type const* s, hamon::size_t n, char_type const& a)
	{
#if HAMON_HAS_BUILTIN(__builtin_wmemchr) || defined(HAMON_MSVC)
		return __builtin_wmemchr(s, a, n);
#else
		if (!hamon::is_constant_evaluated())
		{
			return std::wmemchr(s, a, n);
		}
		return detail::char_traits_fallback::find(s, n, a);
#endif
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* move(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return std::wmemmove(s1, s2, n);
		}
		return detail::char_traits_fallback::move(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* copy(char_type* s1, char_type const* s2, hamon::size_t n)
	{
		if (!hamon::is_constant_evaluated())
		{
			return std::wmemcpy(s1, s2, n);
		}
		return detail::char_traits_fallback::copy(s1, s2, n);
	}

	static HAMON_CXX14_CONSTEXPR
	char_type* assign(char_type* s, hamon::size_t n, char_type a)
	{
		if (!hamon::is_constant_evaluated())
		{
			return std::wmemset(s, a, n);
		}
		return detail::char_traits_fallback::assign(s, n, a);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type not_eof(int_type c) noexcept
	{
		return !eq_int_type(c, eof()) ? c : to_int_type(char_type());
	}

	static HAMON_CXX14_CONSTEXPR
	char_type to_char_type(int_type c) noexcept
	{
		return static_cast<char_type>(c);
	}

	static HAMON_CXX14_CONSTEXPR
	int_type to_int_type(char_type c) noexcept
	{
		return static_cast<int_type>(c);
	}

	static HAMON_CXX14_CONSTEXPR
	bool eq_int_type(int_type c1, int_type c2) noexcept
	{
		return c1 == c2;
	}

	static HAMON_CXX14_CONSTEXPR
	int_type eof() noexcept
	{
		return static_cast<int_type>(WEOF);
	}
};

}	// namespace hamon

#include <hamon/compare/common_comparison_category.hpp>
#include <hamon/type_traits/is_void.hpp>

namespace hamon
{

namespace detail
{

template <typename Traits>
struct char_traits_cmp_cat
{
	using type = typename Traits::comparison_category;
	static_assert(!hamon::is_void<hamon::common_comparison_category_t<type>>::value, "");
};

template <typename Traits>
using char_traits_cmp_cat_t = typename char_traits_cmp_cat<Traits>::type;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_STRING_CHAR_TRAITS_HPP
