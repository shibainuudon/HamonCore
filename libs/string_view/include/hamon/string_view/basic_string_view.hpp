/**
 *	@file	basic_string_view.hpp
 *
 *	@brief	basic_string_view クラステンプレートの定義
 */

#ifndef HAMON_STRING_VIEW_BASIC_STRING_VIEW_HPP
#define HAMON_STRING_VIEW_BASIC_STRING_VIEW_HPP

#include <hamon/string_view/config.hpp>

#if defined(HAMON_USE_STD_STRING_VIEW)

namespace hamon
{

using std::basic_string_view;

}	// namespace hamon

#else

#include <hamon/algorithm/min.hpp>
#include <hamon/algorithm/clamp.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/string/char_traits.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_trivial.hpp>
#include <hamon/type_traits/is_standard_layout.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <limits>
#include <ostream>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

namespace hamon
{

template <typename CharT, typename Traits = hamon::char_traits<CharT>>
class basic_string_view
{
private:
	static_assert(!hamon::is_array<CharT>::value, "");
	static_assert(hamon::is_trivial<CharT>::value && hamon::is_standard_layout<CharT>::value, "");
	static_assert(hamon::is_same<CharT, typename Traits::char_type>::value, "");

public:
	using traits_type		        = Traits;
	using value_type		        = CharT;
	using pointer		            = value_type*;
	using const_pointer	            = value_type const*;
	using reference		            = value_type&;
	using const_reference	        = value_type const&;
	using const_iterator	        = value_type const*;
	using iterator		            = const_iterator;
	using const_reverse_iterator    = hamon::reverse_iterator<const_iterator>;
	using reverse_iterator	        = const_reverse_iterator;
	using size_type		            = hamon::size_t;
	using difference_type	        = std::ptrdiff_t;

	HAMON_STATIC_CONSTEXPR size_type npos = size_type(-1);

	HAMON_CONSTEXPR
	basic_string_view() HAMON_NOEXCEPT
		: m_len{0}
		, m_str{nullptr}
	{}

	HAMON_CONSTEXPR
	basic_string_view(basic_string_view const&) HAMON_NOEXCEPT = default;

	HAMON_CONSTEXPR
	basic_string_view(CharT const* s, size_type count) HAMON_NOEXCEPT
		: m_len{count}
		, m_str{s}
	{}

	HAMON_CONSTEXPR
	basic_string_view(CharT const* s) HAMON_NOEXCEPT
		: m_len{traits_type::length(s)}
		, m_str{s}
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, End),
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::same_as_t<hamon::iter_value_t<It>, CharT>,
			hamon::negation<hamon::convertible_to_t<End, size_type>>
		>::value>
	>
	HAMON_CONSTEXPR
	basic_string_view(It first, End last)
		: m_len(static_cast<size_type>(last - first))
		, m_str(hamon::to_address(first))
	{}

	HAMON_CXX14_CONSTEXPR basic_string_view&
	operator=(basic_string_view const&) HAMON_NOEXCEPT = default;

	// [string.view.iterators], iterator support

	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	begin() const HAMON_NOEXCEPT
	{
		return this->m_str;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	end() const HAMON_NOEXCEPT
	{
		return this->m_str + this->m_len;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	cbegin() const HAMON_NOEXCEPT
	{
		return this->m_str;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	cend() const HAMON_NOEXCEPT
	{
		return this->m_str + this->m_len;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	rbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	rend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	crbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	crend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

	// [string.view.capacity], capacity

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		return this->m_len;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	length() const HAMON_NOEXCEPT
	{
		return m_len;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	max_size() const HAMON_NOEXCEPT
	{
		return (npos - sizeof(size_type) - sizeof(void*)) / sizeof(value_type) / 4;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		return this->m_len == 0;
	}

	// [string.view.access], element access

	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	operator[](size_type pos) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(pos < this->m_len),
			*(this->m_str + pos);
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	at(size_type pos) const
	{
		return (pos >= m_len) ?
			(throw_out_of_range("basic_string_view::at"), *this->m_str) :
			*(this->m_str + pos);
	}

HAMON_WARNING_POP()

	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	front() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(this->m_len > 0u),
			*this->m_str;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	back() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(this->m_len > 0u),
			*(this->m_str + this->m_len - 1);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_pointer
	data() const HAMON_NOEXCEPT
	{
		return this->m_str;
	}

	// remove_prefix
	HAMON_CXX14_CONSTEXPR void
	remove_prefix(size_type n) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(this->m_len >= n);
		this->m_str += n;
		this->m_len -= n;
	}

	// remove_suffix
	HAMON_CXX14_CONSTEXPR void
	remove_suffix(size_type n) HAMON_NOEXCEPT
	{
		this->m_len -= n;
	}

	// swap
	HAMON_CXX14_CONSTEXPR void
	swap(basic_string_view& sv) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		*this = sv;
		sv = tmp;
	}

	// copy
	HAMON_CXX14_CONSTEXPR size_type
	copy(CharT* dest, size_type count, size_type pos = 0) const
	{
		if (pos > size())
		{
			throw_out_of_range("basic_string_view::copy");
		}

		size_type const rlen = hamon::min(count, m_len - pos);
		traits_type::copy(dest, data() + pos, rlen);
		return rlen;
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	// substr
	HAMON_NODISCARD HAMON_CONSTEXPR basic_string_view
	substr(size_type pos = 0, size_type count = npos) const
	{
		return pos <= size() ?
			basic_string_view{m_str + pos, hamon::min(count, m_len - pos)} :
			(throw_out_of_range("basic_string_view::substr"), basic_string_view{});
	}

HAMON_WARNING_POP()

	// compare
	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(basic_string_view sv) const HAMON_NOEXCEPT
	{
		return compare_impl(*this, sv);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(size_type pos1, size_type count1, basic_string_view sv) const
	{
		return this->substr(pos1, count1).compare(sv);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(size_type pos1, size_type count1,
		basic_string_view sv, size_type pos2, size_type count2) const
	{
		return this->substr(pos1, count1).compare(sv.substr(pos2, count2));
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(CharT const* s) const HAMON_NOEXCEPT
	{
		return this->compare(basic_string_view{s});
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(size_type pos1, size_type count1, CharT const* s) const
	{
		return this->substr(pos1, count1).compare(basic_string_view{s});
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(size_type pos1, size_type count1, CharT const* s, size_type count2) const
	{
		return this->substr(pos1, count1).compare(basic_string_view(s, count2));
	}

	// starts_with
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	starts_with(basic_string_view sv) const HAMON_NOEXCEPT
	{
		return this->substr(0, sv.size()) == sv;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	starts_with(CharT c) const HAMON_NOEXCEPT
	{
		return !this->empty() && traits_type::eq(this->front(), c);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	starts_with(CharT const* s) const HAMON_NOEXCEPT
	{
		return this->starts_with(basic_string_view(s));
	}

	// ends_with
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	ends_with(basic_string_view sv) const HAMON_NOEXCEPT
	{
		return this->size() >= sv.size() && this->compare(this->size() - sv.size(), npos, sv) == 0;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	ends_with(CharT c) const HAMON_NOEXCEPT
	{
		return !this->empty() && traits_type::eq(this->back(), c);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	ends_with(CharT const* s) const HAMON_NOEXCEPT
	{
		return this->ends_with(basic_string_view(s));
	}

	// contains
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	contains(basic_string_view sv) const HAMON_NOEXCEPT
	{
		return find(sv) != npos;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	contains(CharT c) const HAMON_NOEXCEPT
	{
		return find(c) != npos;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	contains(CharT const* s) const
	{
		return find(s) != npos;
	}

	// find
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find(basic_string_view sv, size_type pos = 0) const HAMON_NOEXCEPT
	{
		return this->find(sv.m_str, pos, sv.m_len);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find(CharT c, size_type pos = 0) const HAMON_NOEXCEPT
	{
		return (pos < this->m_len) ?
			find_impl(traits_type::find(this->m_str + pos, this->m_len - pos, c), this->m_str) :
			npos;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		return
			(n == 0) ?
				(pos <= this->m_len ? pos : npos) :
			(n > this->m_len) ?
				npos :
			find_impl(s, pos, n, this->m_str, this->m_len);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find(CharT const* s, size_type pos = 0) const HAMON_NOEXCEPT
	{
		return this->find(s, pos, traits_type::length(s));
	}

	// rfind
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	rfind(basic_string_view sv, size_type pos = npos) const HAMON_NOEXCEPT
	{
		return this->rfind(sv.m_str, pos, sv.m_len);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	rfind(CharT c, size_type pos = npos) const HAMON_NOEXCEPT
	{
		return
			(this->m_len < 1) ?
				npos :
				rfind_impl(c, hamon::min(size_type(this->m_len - 1), pos), this->m_str);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		return 
			(this->m_len < n) ?
				npos :
				rfind_impl(s, hamon::min(size_type(this->m_len - n), pos), n, this->m_str);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos = npos) const HAMON_NOEXCEPT
	{
		return this->rfind(s, pos, traits_type::length(s));
	}

	// find_first_of
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_of(basic_string_view sv, size_type pos = 0) const HAMON_NOEXCEPT
	{
		return this->find_first_of(sv.m_str, pos, sv.m_len);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_of(CharT c, size_type pos = 0) const HAMON_NOEXCEPT
	{
		return this->find(c, pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		return find_first_of_impl(s, pos, n, this->m_str, this->m_len);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos = 0) const HAMON_NOEXCEPT
	{
		return this->find_first_of(s, pos, traits_type::length(s));
	}

	// find_last_of
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_of(basic_string_view sv, size_type pos = npos) const HAMON_NOEXCEPT
	{
		return this->find_last_of(sv.m_str, pos, sv.m_len);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_of(CharT c, size_type pos = npos) const HAMON_NOEXCEPT
	{
		return this->rfind(c, pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		return
			!(this->m_len && n) ?
				npos :
				find_last_of_impl(s, hamon::min(size_type(this->m_len - n), pos), n, this->m_str);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos = npos) const HAMON_NOEXCEPT
	{
		return this->find_last_of(s, pos, traits_type::length(s));
	}

	// find_first_not_of
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_not_of(basic_string_view sv, size_type pos = 0) const HAMON_NOEXCEPT
	{
		return this->find_first_not_of(sv.m_str, pos, sv.m_len);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_not_of(CharT c, size_type pos = 0) const HAMON_NOEXCEPT
	{
		return find_first_not_of_impl(c, pos, this->m_str, this->m_len);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		return find_first_not_of_impl(s, pos, n, this->m_str, this->m_len);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos = 0) const HAMON_NOEXCEPT
	{
		return this->find_first_not_of(s, pos, traits_type::length(s));
	}

	// find_last_not_of
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_not_of(basic_string_view sv, size_type pos = npos) const HAMON_NOEXCEPT
	{
		return this->find_last_not_of(sv.m_str, pos, sv.m_len);
	}
	
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_not_of(CharT c, size_type pos = npos) const HAMON_NOEXCEPT
	{
		return
			this->m_len == 0 ?
				npos :
				find_last_not_of_impl(c, hamon::min(size_type(this->m_len - 1), pos), this->m_str);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		return
			this->m_len == 0 ?
				npos :
				find_last_not_of_impl(s, hamon::min(size_type(this->m_len - 1), pos), n, this->m_str);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos = npos) const HAMON_NOEXCEPT
	{
		return this->find_last_not_of(s, pos, traits_type::length(s));
	}

private:
	static HAMON_CONSTEXPR int
	compare_length(size_type n1, size_type n2) HAMON_NOEXCEPT
	{
		using limits = std::numeric_limits<int>;
		return static_cast<int>(hamon::clamp(
			static_cast<difference_type>(n1) - static_cast<difference_type>(n2),
			static_cast<difference_type>(limits::min()),
			static_cast<difference_type>(limits::max())));
	}

	static HAMON_CONSTEXPR int
	compare_impl2(int ret, size_type n1, size_type n2) HAMON_NOEXCEPT
	{
		return ret == 0 ? compare_length(n1, n2) : ret;
	}

	static HAMON_CONSTEXPR int
	compare_impl(basic_string_view sv1, basic_string_view sv2) HAMON_NOEXCEPT
	{
		return compare_impl2(
			traits_type::compare(sv1.m_str, sv2.m_str, hamon::min(sv1.m_len, sv2.m_len)),
			sv1.m_len, sv2.m_len);
	}

	static HAMON_CONSTEXPR size_type
	find_impl(CharT const* p, CharT const* str) HAMON_NOEXCEPT
	{
		return p ? static_cast<size_type>(p - str) : npos;
	}

	static HAMON_CONSTEXPR size_type
	find_impl(CharT const* s, size_type pos, size_type n, CharT const* str, size_type len) HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD < 14
		return
			pos > len - n ?
				npos :
			(traits_type::eq(str[pos], s[0]) &&
			traits_type::compare(str + pos + 1, s + 1, n - 1) == 0) ?
				pos :
			find_impl(s, pos + 1, n, str, len);
#else
		for (; pos <= len - n; ++pos)
		{
			if (traits_type::eq(str[pos], s[0]) &&
				traits_type::compare(str + pos + 1, s + 1, n - 1) == 0)
			{
				return pos;
			}
		}

		return npos;
#endif
	}

	static HAMON_CONSTEXPR size_type
	rfind_impl(CharT c, size_type pos, CharT const* str) HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD < 14
		return
			traits_type::eq(str[pos], c) ?
				pos :
			(pos > 0) ?
				rfind_impl(c, pos - 1, str) :
				npos;
#else
		do
		{
			if (traits_type::eq(str[pos], c))
			{
				return pos;
			}
		}
		while (pos-- > 0);

		return npos;
#endif
	}

	static HAMON_CONSTEXPR size_type
	rfind_impl(CharT const* s, size_type pos, size_type n, CharT const* str) HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD < 14
		return
			(traits_type::compare(str + pos, s, n) == 0) ?
				pos :
			(pos > 0) ?
				rfind_impl(s, pos - 1, n, str) :
				npos;
#else
		do
		{
			if (traits_type::compare(str + pos, s, n) == 0)
			{
				return pos;
			}
		}
		while (pos-- > 0);

		return npos;
#endif
	}

	static HAMON_CONSTEXPR size_type
	find_first_of_impl(CharT const* s, size_type pos, size_type n, CharT const* str, size_type len) HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD < 14
		return
			!(n && pos < len) ?
				npos :
			traits_type::find(s, n, str[pos]) ?
				pos :
				find_first_of_impl(s, pos + 1, n, str, len);
#else
		for (; n && pos < len; ++pos)
		{
			CharT const* p = traits_type::find(s, n, str[pos]);
			if (p)
			{
				return pos;
			}
		}

		return npos;
#endif
	}

	static HAMON_CONSTEXPR size_type
	find_last_of_impl(CharT const* s, size_type pos, size_type n, CharT const* str) HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD < 14
		return
			traits_type::find(s, n, str[pos]) ?
				pos :
			(pos > 0) ?
				find_last_of_impl(s, pos - 1, n, str):
				npos;
#else
		do
		{
			if (traits_type::find(s, n, str[pos]))
			{
				return pos;
			}
		}
		while (pos-- > 0);

		return npos;
#endif
	}

	static HAMON_CONSTEXPR size_type
	find_first_not_of_impl(CharT c, size_type pos, CharT const* str, size_type len) HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD < 14
		return
			pos >= len ?
				npos :
			!traits_type::eq(str[pos], c) ?
				pos :
				find_first_not_of_impl(c, pos + 1, str, len);
#else
		for (; pos < len; ++pos)
		{
			if (!traits_type::eq(str[pos], c))
			{
				return pos;
			}
		}

		return npos;
#endif
	}
	
	static HAMON_CONSTEXPR size_type
	find_first_not_of_impl(CharT const* s, size_type pos, size_type n, CharT const* str, size_type len) HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD < 14
		return
			pos >= len ?
				npos :
			!traits_type::find(s, n, str[pos]) ?
				pos :
				find_first_not_of_impl(s, pos + 1, n, str, len);
#else
		for (; pos < len; ++pos)
		{
			if (!traits_type::find(s, n, str[pos]))
			{
				return pos;
			}
		}

		return npos;
#endif
	}

	static HAMON_CONSTEXPR size_type
	find_last_not_of_impl(CharT c, size_type pos, CharT const* str) HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD < 14
		return
			!traits_type::eq(str[pos], c) ?
				pos :
			pos > 0 ?
				find_last_not_of_impl(c, pos - 1, str) :
				npos;
#else
		do
		{
			if (!traits_type::eq(str[pos], c))
			{
				return pos;
			}
		}
		while (pos-- > 0);

		return npos;
#endif
	}

	static HAMON_CONSTEXPR size_type
	find_last_not_of_impl(CharT const* s, size_type pos, size_type n, CharT const* str) HAMON_NOEXCEPT
	{
#if HAMON_CXX_STANDARD < 14
		return
			!traits_type::find(s, n, str[pos]) ?
				pos :
			pos > 0 ?
				find_last_not_of_impl(s, pos - 1, n, str) :
				npos;
#else
		do
		{
			if (!traits_type::find(s, n, str[pos]))
			{
				return pos;
			}
		}
		while (pos-- > 0);

		return npos;
#endif
	}

	HAMON_NORETURN static void throw_out_of_range(char const* msg)
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		throw std::out_of_range(msg);
#else
		(void)msg;
		std::abort();
#endif
	}

	size_type		m_len;
	CharT const*	m_str;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),
	HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, End)
>
basic_string_view(It, End) -> basic_string_view<hamon::iter_value_t<It>>;

#endif

template <typename CharT, typename Traits>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename Traits, int = 1>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(
	basic_string_view<CharT, Traits> lhs,
	hamon::type_identity_t<basic_string_view<CharT, Traits>> rhs) HAMON_NOEXCEPT
{
	return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename CharT, typename Traits>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator<=>(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
-> detail::char_traits_cmp_cat_t<Traits>
{
	using cat = detail::char_traits_cmp_cat_t<Traits>;
	return static_cast<cat>(lhs.compare(rhs) <=> 0);
}

template <typename CharT, typename Traits, int = 1>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator<=>(
	basic_string_view<CharT, Traits> lhs,
	hamon::type_identity_t<basic_string_view<CharT, Traits>> rhs) HAMON_NOEXCEPT
-> detail::char_traits_cmp_cat_t<Traits>
{
	using cat = detail::char_traits_cmp_cat_t<Traits>;
	return static_cast<cat>(lhs.compare(rhs) <=> 0);
}

#else

template <typename CharT, typename Traits, int = 2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(
	hamon::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename Traits>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator!=(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, int = 1>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator!=(
	basic_string_view<CharT, Traits> lhs,
	hamon::type_identity_t<basic_string_view<CharT, Traits>> rhs) HAMON_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, int = 2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator!=(
	hamon::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits, int = 1>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<(
	basic_string_view<CharT, Traits> lhs,
	hamon::type_identity_t<basic_string_view<CharT, Traits>> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits, int = 2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<(
	hamon::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits, int = 1>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>(
	basic_string_view<CharT, Traits> lhs,
	hamon::type_identity_t<basic_string_view<CharT, Traits>> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits, int = 2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>(
	hamon::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<=(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits, int = 1>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<=(
	basic_string_view<CharT, Traits> lhs,
	hamon::type_identity_t<basic_string_view<CharT, Traits>> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits, int = 2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<=(
	hamon::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>=(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename Traits, int = 1>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>=(
	basic_string_view<CharT, Traits> lhs,
	hamon::type_identity_t<basic_string_view<CharT, Traits>> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename Traits, int = 2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>=(
	hamon::type_identity_t<basic_string_view<CharT, Traits>> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	return lhs.compare(rhs) >= 0;
}

#endif // defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename CharT, typename Traits1, typename Traits2>
inline std::basic_ostream<CharT, Traits1>&
operator<<(
	std::basic_ostream<CharT, Traits1>& os,
	basic_string_view<CharT, Traits2> sv)
{
	return os.write(sv.data(), static_cast<std::streamsize>(sv.size()));
}

}	// namespace hamon

#endif	// defined(HAMON_USE_STD_STRING_VIEW)

#include <hamon/functional/config.hpp>

#if !defined(HAMON_USE_STD_STRING_VIEW) || !defined(HAMON_USE_STD_HASH)

#if 0	// TODO hash support
#include <hamon/functional/hash.hpp>
#include <hamon/hash_functions/murmur_hash_3.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace HAMON_HASH_NAMESPACE
{

template <typename CharT, typename Traits>
struct hash<hamon::basic_string_view<CharT, Traits>>
{
	HAMON_CXX14_CONSTEXPR hamon::size_t
	operator()(hamon::basic_string_view<CharT, Traits> const& sv) const HAMON_NOEXCEPT
	{
		return hamon::murmur_hash_3{}(sv.data(), sv.data() + sv.length());
	}
};

}	// namespace HAMON_HASH_NAMESPACE
#endif

#endif	// !defined(HAMON_USE_STD_STRING_VIEW) || !defined(HAMON_USE_STD_HASH)

#include <hamon/ranges/config.hpp>

#if !defined(HAMON_USE_STD_STRING_VIEW) || !defined(HAMON_USE_STD_RANGES)

#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/enable_view.hpp>

HAMON_RANGES_START_NAMESPACE

template <typename CharT, typename Traits>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon::basic_string_view<CharT, Traits>);

template <typename CharT, typename Traits>
HAMON_RANGES_SPECIALIZE_ENABLE_VIEW(true, hamon::basic_string_view<CharT, Traits>);

HAMON_RANGES_END_NAMESPACE

#endif	// !defined(HAMON_USE_STD_STRING_VIEW) || !defined(HAMON_USE_STD_RANGES)

#include <cstddef>

namespace hamon
{
inline namespace literals
{
inline namespace string_view_literals
{

HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::basic_string_view<char>
operator"" _sv(char const* str, hamon::size_t len) HAMON_NOEXCEPT
{
	return hamon::basic_string_view<char>{str, len};
}

HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::basic_string_view<wchar_t>
operator"" _sv(wchar_t const* str, hamon::size_t len) HAMON_NOEXCEPT
{
	return hamon::basic_string_view<wchar_t>{str, len};
}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::basic_string_view<char8_t>
operator"" _sv(char8_t const* str, hamon::size_t len) HAMON_NOEXCEPT
{
	return hamon::basic_string_view<char8_t>{str, len};
}
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::basic_string_view<char16_t>
operator"" _sv(char16_t const* str, hamon::size_t len) HAMON_NOEXCEPT
{
	return hamon::basic_string_view<char16_t>{str, len};
}
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::basic_string_view<char32_t>
operator"" _sv(char32_t const* str, hamon::size_t len) HAMON_NOEXCEPT
{
	return hamon::basic_string_view<char32_t>{str, len};
}
#endif

}	// namespace string_literals
}	// namespace literals
}	// namespace hamon

#endif // HAMON_STRING_VIEW_BASIC_STRING_VIEW_HPP
