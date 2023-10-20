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
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/string/char_traits.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_trivial.hpp>
#include <hamon/type_traits/is_standard_layout.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/assert.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <ostream>

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

template <typename CharT, typename Traits = hamon::char_traits<CharT>>
class basic_string_view;

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename CharT, typename Traits>
concept has_operator_string_view =
	requires(T& d)
	{
		d.operator hamon::basic_string_view<CharT, Traits>();
	};

#else

template <typename T, typename CharT, typename Traits, typename = hamon::void_t<>>
struct has_operator_string_view : hamon::false_type {};

template <typename T, typename CharT, typename Traits>
struct has_operator_string_view<T, CharT, Traits,
	hamon::void_t<decltype(hamon::declval<T&>().operator hamon::basic_string_view<CharT, Traits>())>> : hamon::true_type {};

#endif

template <typename T, typename CharT, typename Traits>
using has_operator_string_view_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::has_operator_string_view<T, CharT, Traits>>;
#else
	hamon::detail::has_operator_string_view<T, CharT, Traits>;
#endif

}	// namespace detail

template <typename CharT, typename Traits>
class basic_string_view
{
private:
	static_assert(!hamon::is_array<CharT>::value, "");
	static_assert(hamon::is_trivial<CharT>::value && hamon::is_standard_layout<CharT>::value, "");
	static_assert(hamon::is_same<CharT, typename Traits::char_type>::value, "[string.view.template.general]/1 Note1");

public:
	// types
	using traits_type		        = Traits;
	using value_type		        = CharT;
	using pointer		            = value_type*;
	using const_pointer	            = value_type const*;
	using reference		            = value_type&;
	using const_reference	        = value_type const&;
	using const_iterator	        = value_type const*;
	using iterator		            = const_iterator;	// implementation-defined;
	using const_reverse_iterator    = hamon::reverse_iterator<const_iterator>;
	using reverse_iterator	        = const_reverse_iterator;
	using size_type		            = hamon::size_t;
	using difference_type	        = hamon::ptrdiff_t;

	HAMON_STATIC_CONSTEXPR size_type npos = size_type(-1);

	// [string.view.cons], construction and assignment
	HAMON_CONSTEXPR
	basic_string_view() HAMON_NOEXCEPT
		: m_data{nullptr}
		, m_size{0}
	{
		// [string.view.cons]/1
	}

	HAMON_CONSTEXPR
	basic_string_view(basic_string_view const&) HAMON_NOEXCEPT = default;

	HAMON_CXX14_CONSTEXPR basic_string_view&
	operator=(basic_string_view const&) HAMON_NOEXCEPT = default;

	HAMON_CONSTEXPR
	basic_string_view(CharT const* str) HAMON_NOEXCEPT
		: basic_string_view(str, traits_type::length(str))	// [string.view.cons]/3
	{}
	
	basic_string_view(hamon::nullptr_t) = delete;

	HAMON_CONSTEXPR
	basic_string_view(CharT const* str, size_type len) HAMON_NOEXCEPT
		: m_data{str} , m_size{len}	// [string.view.cons]/6
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),		// [string.view.cons]/7.1
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, End),	// [string.view.cons]/7.2
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::same_as_t<hamon::iter_value_t<It>, CharT>,			// [string.view.cons]/7.3
			hamon::negation<hamon::convertible_to_t<End, size_type>>	// [string.view.cons]/7.4
		>::value>
	>
	HAMON_CONSTEXPR
	basic_string_view(It begin, End end)
		: m_data(hamon::to_address(begin))
		, m_size(static_cast<size_type>(end - begin))
	{
		// [string.view.cons]/9
	}

	template <typename R,
		typename = hamon::enable_if_t<
			!hamon::is_same<hamon::remove_cvref_t<R>, basic_string_view>::value &&		// [string.view.cons]/12.1
			ranges::contiguous_range_t<R>::value && ranges::sized_range_t<R>::value &&	// [string.view.cons]/12.2
			hamon::is_same<ranges::range_value_t<R>, CharT>::value &&					// [string.view.cons]/12.3
			!hamon::is_convertible<R, CharT const*>::value &&							// [string.view.cons]/12.4
			!hamon::detail::has_operator_string_view_t<hamon::remove_cvref_t<R>, CharT, Traits>::value			// [string.view.cons]/12.5
		>
	>
	constexpr explicit basic_string_view(R&& r)
		: m_data(ranges::data(r)), m_size(ranges::size(r))	// [string.view.cons]/13
	{}

	// [string.view.iterators], iterator support

	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	begin() const HAMON_NOEXCEPT
	{
		// [string.view.iterators]/3
		return this->m_data;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	end() const HAMON_NOEXCEPT
	{
		// [string.view.iterators]/4
		return this->begin() + this->size();
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	cbegin() const HAMON_NOEXCEPT
	{
		// [string.view.iterators]/3
		return this->m_data;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	cend() const HAMON_NOEXCEPT
	{
		// [string.view.iterators]/4
		return this->begin() + this->size();
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	rbegin() const HAMON_NOEXCEPT
	{
		// [string.view.iterators]/5
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	rend() const HAMON_NOEXCEPT
	{
		// [string.view.iterators]/6
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	crbegin() const HAMON_NOEXCEPT
	{
		// [string.view.iterators]/5
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	crend() const HAMON_NOEXCEPT
	{
		// [string.view.iterators]/6
		return const_reverse_iterator(this->begin());
	}

	// [string.view.capacity], capacity

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		// [string.view.capacity]/1
		return this->m_size;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	length() const HAMON_NOEXCEPT
	{
		// [string.view.capacity]/1
		return this->m_size;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	max_size() const HAMON_NOEXCEPT
	{
		// [string.view.capacity]/2
		// TODO
		return (npos - sizeof(size_type) - sizeof(void*)) / sizeof(value_type) / 4;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		// [string.view.capacity]/3
		return this->m_size == 0;
	}

	// [string.view.access], element access

	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	operator[](size_type pos) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(pos < this->size()),	// [string.view.access]/1
			this->m_data[pos];					// [string.view.access]/2
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	at(size_type pos) const
	{
		return (pos >= size()) ?	// [string.view.access]/6
			(hamon::detail::throw_out_of_range("basic_string_view::at"), *this->m_data) :
			this->m_data[pos];		// [string.view.access]/5
	}

HAMON_WARNING_POP()

	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	front() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(!this->empty()),	// [string.view.access]/7
			this->m_data[0];				// [string.view.access]/8
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	back() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(!this->empty()),	// [string.view.access]/10
			this->m_data[this->size() - 1];	// [string.view.access]/11
	}

	HAMON_NODISCARD HAMON_CONSTEXPR const_pointer
	data() const HAMON_NOEXCEPT
	{
		return this->m_data;		// [string.view.access]/13
	}

	// [string.view.modifiers], modifiers

	HAMON_CXX14_CONSTEXPR void
	remove_prefix(size_type n) HAMON_NOEXCEPT
	{
		// [string.view.modifiers]/1
		HAMON_ASSERT(n <= this->size());

		// [string.view.modifiers]/2
		this->m_data += n;
		this->m_size -= n;
	}

	HAMON_CXX14_CONSTEXPR void
	remove_suffix(size_type n) HAMON_NOEXCEPT
	{
		// [string.view.modifiers]/3
		HAMON_ASSERT(n <= this->size());

		// [string.view.modifiers]/4
		this->m_size -= n;
	}

	HAMON_CXX14_CONSTEXPR void
	swap(basic_string_view& sv) HAMON_NOEXCEPT
	{
		// [string.view.modifiers]/5
		hamon::swap(this->m_data, sv.m_data);
		hamon::swap(this->m_size, sv.m_size);
	}

	// [string.view.ops], string operations

	// copy
	HAMON_CXX14_CONSTEXPR size_type
	copy(CharT* dest, size_type n, size_type pos = 0) const
	{
		// [string.view.ops]/5
		if (pos > size())
		{
			hamon::detail::throw_out_of_range("basic_string_view::copy");
		}

		// [string.view.ops]/1
		size_type const rlen = hamon::min(n, size() - pos);
		// [string.view.ops]/3
		traits_type::copy(dest, data() + pos, rlen);
		// [string.view.ops]/4
		return rlen;
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	// substr
	HAMON_NODISCARD HAMON_CONSTEXPR basic_string_view
	substr(size_type pos = 0, size_type n = npos) const
	{
		return pos <= size() ?
			basic_string_view{data() + pos, hamon::min(n, size() - pos)} :	// [string.view.ops]/9
			(hamon::detail::throw_out_of_range("basic_string_view::substr"), basic_string_view{});	// [string.view.ops]/10
	}

HAMON_WARNING_POP()

	// compare
	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(basic_string_view sv) const HAMON_NOEXCEPT
	{
		return compare_impl(*this, sv);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(size_type pos1, size_type n1, basic_string_view sv) const
	{
		// [string.view.ops]/15
		return this->substr(pos1, n1).compare(sv);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(size_type pos1, size_type n1,
		basic_string_view sv, size_type pos2, size_type n2) const
	{
		// [string.view.ops]/16
		return this->substr(pos1, n1).compare(sv.substr(pos2, n2));
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(CharT const* s) const HAMON_NOEXCEPT
	{
		// [string.view.ops]/17
		return this->compare(basic_string_view{s});
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(size_type pos1, size_type n1, CharT const* s) const
	{
		// [string.view.ops]/18
		return this->substr(pos1, n1).compare(basic_string_view{s});
	}

	HAMON_NODISCARD HAMON_CONSTEXPR int
	compare(size_type pos1, size_type n1, CharT const* s, size_type n2) const
	{
		// [string.view.ops]/19
		return this->substr(pos1, n1).compare(basic_string_view(s, n2));
	}

	// starts_with
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	starts_with(basic_string_view sv) const HAMON_NOEXCEPT
	{
		// [string.view.ops]/20
		return this->substr(0, sv.size()) == sv;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	starts_with(CharT c) const HAMON_NOEXCEPT
	{
		// [string.view.ops]/21
		return !this->empty() && traits_type::eq(this->front(), c);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	starts_with(CharT const* s) const HAMON_NOEXCEPT
	{
		// [string.view.ops]/22
		return this->starts_with(basic_string_view(s));
	}

	// ends_with
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	ends_with(basic_string_view sv) const HAMON_NOEXCEPT
	{
		// [string.view.ops]/23
		return this->size() >= sv.size() &&
			this->compare(this->size() - sv.size(), npos, sv) == 0;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	ends_with(CharT c) const HAMON_NOEXCEPT
	{
		// [string.view.ops]/24
		return !this->empty() && traits_type::eq(this->back(), c);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	ends_with(CharT const* s) const HAMON_NOEXCEPT
	{
		// [string.view.ops]/25
		return this->ends_with(basic_string_view(s));
	}

	// contains
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	contains(basic_string_view sv) const HAMON_NOEXCEPT
	{
		// [string.view.ops]/26
		return find(sv) != npos;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	contains(CharT c) const HAMON_NOEXCEPT
	{
		// [string.view.ops]/26
		return find(c) != npos;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR bool
	contains(CharT const* s) const
	{
		// [string.view.ops]/26
		return find(s) != npos;
	}

	// [string.view.find], searching
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find(basic_string_view s, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.view.find]/3
		// [string.view.find]/4
		// [string.view.find]/5
#if HAMON_CXX_STANDARD < 14
		return
			pos + s.size() > this->size() ?
				npos :
			traits_type::compare(this->data() + pos, s.data(), s.size()) == 0 ?
				pos :
			find(s, pos + 1);
#else
		for (auto xpos = pos; xpos + s.size() <= this->size(); ++xpos)
		{
			if (traits_type::compare(this->data() + xpos, s.data(), s.size()) == 0)
			{
				return xpos;
			}
		}

		return npos;
#endif
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find(CharT c, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.3
		return find(basic_string_view(hamon::addressof(c), 1), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.2
		return find(basic_string_view(s, n), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find(CharT const* s, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.1
		return find(basic_string_view(s), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	rfind(basic_string_view s, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.view.find]/6
		// [string.view.find]/7
		// [string.view.find]/8
#if HAMON_CXX_STANDARD < 14
		return
			pos > this->size() - s.size() ?
				rfind(s, this->size() - s.size()) :
			traits_type::compare(this->data() + pos, s.data(), s.size()) == 0 ?
				pos :
			pos > 0 ?
				rfind(s, pos - 1) :
			npos;
#else
		auto xpos = hamon::min(pos, this->size() - s.size());

		do
		{
			if (traits_type::compare(this->data() + xpos, s.data(), s.size()) == 0)
			{
				return xpos;
			}
		}
		while (xpos-- > 0);

		return npos;
#endif
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	rfind(CharT c, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.3
		return rfind(basic_string_view(hamon::addressof(c), 1), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.2
		return rfind(basic_string_view(s, n), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.1
		return rfind(basic_string_view(s), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_of(basic_string_view s, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.view.find]/9
		// [string.view.find]/10
		// [string.view.find]/11
#if HAMON_CXX_STANDARD < 14
		return
			pos >= this->size() ?
				npos :
			traits_type::find(s.data(), s.size(), (*this)[pos]) ?
				pos :
			find_first_of(s, pos + 1);
#else
		for (auto xpos = pos; xpos < this->size(); ++xpos)
		{
			if (traits_type::find(s.data(), s.size(), (*this)[xpos]))
			{
				return xpos;
			}
		}

		return npos;
#endif
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_of(CharT c, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.3
		return find_first_of(basic_string_view(hamon::addressof(c), 1), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.2
		return find_first_of(basic_string_view(s, n), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.1
		return find_first_of(basic_string_view(s), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_of(basic_string_view s, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.view.find]/12
		// [string.view.find]/13
		// [string.view.find]/14
#if HAMON_CXX_STANDARD < 14
		return
			pos > this->size() - 1 ?
				find_last_of(s, this->size() - 1) :
			traits_type::find(s.data(), s.size(), (*this)[pos]) ?
				pos :
			pos > 0 ?
				find_last_of(s, pos - 1) :
			npos;

#else
		auto xpos = hamon::min(pos, this->size() - 1);

		do
		{
			if (traits_type::find(s.data(), s.size(), (*this)[xpos]))
			{
				return xpos;
			}
		}
		while (xpos-- > 0);

		return npos;
#endif
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_of(CharT c, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.3
		return find_last_of(basic_string_view(hamon::addressof(c), 1), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.2
		return find_last_of(basic_string_view(s, n), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.1
		return find_last_of(basic_string_view(s), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_not_of(basic_string_view s, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.view.find]/15
		// [string.view.find]/16
		// [string.view.find]/17
#if HAMON_CXX_STANDARD < 14
		return
			pos >= this->size() ?
				npos :
			!traits_type::find(s.data(), s.size(), (*this)[pos]) ?
				pos :
			find_first_not_of(s, pos + 1);
#else
		for (auto xpos = pos; xpos < this->size(); ++xpos)
		{
			if (!traits_type::find(s.data(), s.size(), (*this)[xpos]))
			{
				return xpos;
			}
		}

		return npos;
#endif
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_not_of(CharT c, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.3
		return find_first_not_of(basic_string_view(hamon::addressof(c), 1), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.2
		return find_first_not_of(basic_string_view(s, n), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.1
		return find_first_not_of(basic_string_view(s), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_not_of(basic_string_view s, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.view.find]/18
		// [string.view.find]/19
		// [string.view.find]/20
#if HAMON_CXX_STANDARD < 14
		return
			pos > this->size() - 1 ?
				find_last_not_of(s, this->size() - 1) :
			!traits_type::find(s.data(), s.size(), (*this)[pos]) ?
				pos :
			pos > 0 ?
				find_last_not_of(s, pos - 1) :
			npos;
#else
		auto xpos = hamon::min(pos, this->size() - 1);

		do
		{
			if (!traits_type::find(s.data(), s.size(), (*this)[xpos]))
			{
				return xpos;
			}
		}
		while (xpos-- > 0);

		return npos;
#endif
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_not_of(CharT c, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.3
		return find_last_not_of(basic_string_view(hamon::addressof(c), 1), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos, size_type n) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.2
		return find_last_not_of(basic_string_view(s, n), pos);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.view.find]/2.1
		return find_last_not_of(basic_string_view(s), pos);
	}

private:
	static HAMON_CONSTEXPR int
	compare_impl2(int ret, size_type n1, size_type n2) HAMON_NOEXCEPT
	{
		return
			ret != 0 ? ret :
			n1 <  n2 ? -1 :
			n1 == n2 ? 0 :
			/*n1 > n2 ?*/ 1;
	}

	static HAMON_CONSTEXPR int
	compare_impl(basic_string_view sv1, basic_string_view sv2) HAMON_NOEXCEPT
	{
		return compare_impl2(
			traits_type::compare(sv1.data(), sv2.data(), hamon::min(sv1.size(), sv2.size())),
			sv1.size(), sv2.size());
	}

	const_pointer	m_data;
	size_type		m_size;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

// [string.view.deduct], deduction guides

template <
	HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),	// [string.view.deduct]/1.1
	HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, End)	// [string.view.deduct]/1.2
>
basic_string_view(It, End)
	-> basic_string_view<hamon::iter_value_t<It>>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::contiguous_range, R)>	// [string.view.deduct]/2
basic_string_view(R&&)
	-> basic_string_view<ranges::range_value_t<R>>;

#endif

// [string.view.comparison], non-member comparison functions

template <typename CharT, typename Traits>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(
	basic_string_view<CharT, Traits> lhs,
	basic_string_view<CharT, Traits> rhs) HAMON_NOEXCEPT
{
	// [string.view.comparison]/2
	return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename Traits, int = 1>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(
	basic_string_view<CharT, Traits> lhs,
	hamon::type_identity_t<basic_string_view<CharT, Traits>> rhs) HAMON_NOEXCEPT
{
	// [string.view.comparison]/2
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
	// [string.view.comparison]/3
	using R = detail::char_traits_cmp_cat_t<Traits>;
	// [string.view.comparison]/5
	return static_cast<R>(lhs.compare(rhs) <=> 0);
}

template <typename CharT, typename Traits, int = 1>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator<=>(
	basic_string_view<CharT, Traits> lhs,
	hamon::type_identity_t<basic_string_view<CharT, Traits>> rhs) HAMON_NOEXCEPT
-> detail::char_traits_cmp_cat_t<Traits>
{
	// [string.view.comparison]/3
	using R = detail::char_traits_cmp_cat_t<Traits>;
	// [string.view.comparison]/5
	return static_cast<R>(lhs.compare(rhs) <=> 0);
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

// [string.view.io], inserters and extractors

template <typename CharT, typename Traits1, typename Traits2>
inline std::basic_ostream<CharT, Traits1>&
operator<<(
	std::basic_ostream<CharT, Traits1>& os,
	basic_string_view<CharT, Traits2> sv)
{
	// TODO
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

namespace HAMON_HASH_NAMESPACE
{

// [string.view.hash], hash support

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

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{
inline namespace literals
{
inline namespace string_view_literals
{

// [string.view.literals], suffix for basic_string_view literals

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
