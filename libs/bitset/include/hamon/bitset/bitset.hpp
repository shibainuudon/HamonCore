/**
 *	@file	bitset.hpp
 *
 *	@brief	bitset の定義
 */

#ifndef HAMON_BITSET_BITSET_HPP
#define HAMON_BITSET_BITSET_HPP

#include <hamon/bitset/config.hpp>

#if defined(HAMON_USE_STD_BITSET)

#include <bitset>

namespace hamon
{

using std::bitset;

}	// namespace hamon

#else

#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/any_of.hpp>
#include <hamon/algorithm/all_of.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/array.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/popcount.hpp>
#include <hamon/cmath/round_up.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uint8_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/cstring/strlen.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/rbegin.hpp>
#include <hamon/iterator/rend.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/stdexcept/invalid_argument.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/stdexcept/overflow_error.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <ios>				// std::ios_base
#include <istream>			// std::basic_istream
#include <locale>			// std::use_facet, std::ctype
#include <memory>			// std::allocator
#include <ostream>			// std::basic_ostream

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

namespace bitset_detail
{

template <typename T, hamon::size_t NBits, hamon::size_t NWords>
struct bitset_impl
{
private:
	static_assert(hamon::is_unsigned<T>::value, "");

	static const hamon::size_t BitsPerWord = hamon::bitsof<T>();
	static const hamon::size_t HighestWordBits =
		(NBits % BitsPerWord) == 0 ? BitsPerWord : (NBits % BitsPerWord);
	static const hamon::size_t WordsPerULongLong = sizeof(unsigned long long) / sizeof(T);

	hamon::array<T, NWords>	m_value;

public:
	HAMON_CXX11_CONSTEXPR bitset_impl() HAMON_NOEXCEPT
		: m_value{}
	{}

private:
	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR
	bitset_impl(unsigned long long val, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
		: m_value{{ static_cast<T>((val >> (BitsPerWord * Is)) & bitmask(Is))... }}
	{}

public:
	HAMON_CXX11_CONSTEXPR
	bitset_impl(unsigned long long val) HAMON_NOEXCEPT
		: bitset_impl(val, hamon::make_index_sequence<(NWords > WordsPerULongLong) ? WordsPerULongLong : NWords>{})
	{}

private:
	struct make_word_op
	{
		template <typename U1, typename U2>
		HAMON_CXX11_CONSTEXPR U1 operator()(U1 lhs, U2 rhs) const HAMON_NOEXCEPT
		{
			return static_cast<U1>((static_cast<hamon::uintmax_t>(lhs) << 1) + rhs);
		}
	};

	static HAMON_CXX11_CONSTEXPR T
	make_word(hamon::array<bool, NBits> const& ar, hamon::size_t i) HAMON_NOEXCEPT
	{
		return hamon::accumulate(
			hamon::make_reverse_iterator(hamon::begin(ar) + hamon::min(i + BitsPerWord, NBits)),
			hamon::make_reverse_iterator(hamon::begin(ar) + i),
			T{},
			make_word_op{});
	}

	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR
	bitset_impl(hamon::array<bool, NBits> const& ar, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
		: m_value{{ make_word(ar, Is * BitsPerWord)... }}
	{}

public:
	HAMON_CXX11_CONSTEXPR
	bitset_impl(hamon::array<bool, NBits> const& ar) HAMON_NOEXCEPT
		: bitset_impl(ar, hamon::make_index_sequence<NWords>{})
	{}

private:
	struct count_op
	{
	public:
		HAMON_CXX11_CONSTEXPR hamon::size_t
		operator()(hamon::size_t lhs, T rhs) const HAMON_NOEXCEPT
		{
			return lhs + static_cast<hamon::size_t>(hamon::popcount(rhs));
		}
	};

public:
	HAMON_CXX11_CONSTEXPR hamon::size_t count() const HAMON_NOEXCEPT
	{
		return hamon::accumulate(
			hamon::begin(m_value),
			hamon::end(m_value),
			hamon::size_t{},
			count_op{});
	}

	HAMON_CXX11_CONSTEXPR bitset_impl operator~() const HAMON_NOEXCEPT
	{
		return not_impl(hamon::make_index_sequence<NWords>{});
	}

private:
	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR hamon::array<T, NWords>
	shift_left_impl_1(
		hamon::size_t wshift,
		hamon::index_sequence<Is...>) const HAMON_NOEXCEPT
	{
		return {{(Is < wshift ? T{} : static_cast<T>(m_value[Is - wshift] & bitmask(Is)))...}};
	}

	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR hamon::array<T, NWords>
	shift_left_impl_2(
		hamon::size_t wshift,
		hamon::size_t offset,
		hamon::size_t sub_offset,
		hamon::index_sequence<Is...>) const HAMON_NOEXCEPT
	{
		return {{static_cast<T>(
			Is < wshift ?
				T{} :
			Is == wshift ?
				(m_value[0] << offset) & bitmask(Is) :
			((m_value[Is - wshift] << offset) |
			 (m_value[Is - wshift - 1] >> sub_offset)) & bitmask(Is))...
		}};
	}

	HAMON_CXX11_CONSTEXPR bitset_impl
	shift_left_impl(hamon::size_t wshift, hamon::size_t offset) const HAMON_NOEXCEPT
	{
		return offset == 0 ?
			shift_left_impl_1(wshift, hamon::make_index_sequence<NWords>{}) :
			shift_left_impl_2(wshift, offset, BitsPerWord - offset, hamon::make_index_sequence<NWords>{});
	}

public:
	HAMON_CXX11_CONSTEXPR bitset_impl
	operator<<(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return pos == 0 ? *this :
			shift_left_impl(pos / BitsPerWord, pos % BitsPerWord);
	}

private:
	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR hamon::array<T, NWords>
	shift_right_impl_1(
		hamon::size_t wshift,
		hamon::size_t limit,
		hamon::index_sequence<Is...>) const HAMON_NOEXCEPT
	{
		return {{(Is >limit ? T{} : m_value[Is + wshift])...}};
	}

	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR hamon::array<T, NWords>
	shift_right_impl_2(
		hamon::size_t wshift,
		hamon::size_t offset,
		hamon::size_t limit,
		hamon::size_t sub_offset,
		hamon::index_sequence<Is...>) const HAMON_NOEXCEPT
	{
		return {{static_cast<T>(
			Is > limit ?
				T{} :
			Is == limit ?
				m_value[NWords-1] >> offset :
			((m_value[Is + wshift] >> offset) |
			 (m_value[Is + wshift + 1] << sub_offset)))...
		}};
	}
	
	HAMON_CXX11_CONSTEXPR bitset_impl
	shift_right_impl(hamon::size_t wshift, hamon::size_t offset) const HAMON_NOEXCEPT
	{
		return offset == 0 ?
			shift_right_impl_1(wshift, NWords - wshift - 1, hamon::make_index_sequence<NWords>{}) :
			shift_right_impl_2(wshift, offset, NWords - wshift - 1, BitsPerWord - offset, hamon::make_index_sequence<NWords>{});
	}

public:
	HAMON_CXX11_CONSTEXPR bitset_impl
	operator>>(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return pos == 0 ? *this :
			shift_right_impl(pos / BitsPerWord, pos % BitsPerWord);
	}

private:
	HAMON_CXX11_CONSTEXPR
	bitset_impl(hamon::array<T, NWords> const& ar) HAMON_NOEXCEPT
		: m_value{ar}
	{}

	HAMON_CXX11_CONSTEXPR T bitmask(hamon::size_t I) const HAMON_NOEXCEPT
	{
		return I == (NWords - 1) ?
			T(-1) >> (BitsPerWord - HighestWordBits) :
			T(-1);
	}

	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR bitset_impl
	not_impl(hamon::index_sequence<Is...>) const HAMON_NOEXCEPT
	{
		return {hamon::array<T, NWords>{{T(~m_value[Is] & bitmask(Is))...}}};
	}

	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR bitset_impl
	and_impl(bitset_impl const& rhs, hamon::index_sequence<Is...>) const HAMON_NOEXCEPT
	{
		return {hamon::array<T, NWords>{{T(m_value[Is] & rhs.m_value[Is])...}}};
	}

	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR bitset_impl
	or_impl(bitset_impl const& rhs, hamon::index_sequence<Is...>) const HAMON_NOEXCEPT
	{
		return {hamon::array<T, NWords>{{T(m_value[Is] | rhs.m_value[Is])...}}};
	}

	template <hamon::size_t... Is>
	HAMON_CXX11_CONSTEXPR bitset_impl
	xor_impl(bitset_impl const& rhs, hamon::index_sequence<Is...>) const HAMON_NOEXCEPT
	{
		return {hamon::array<T, NWords>{{T(m_value[Is] ^ rhs.m_value[Is])...}}};
	}

public:
	HAMON_CXX11_CONSTEXPR bitset_impl
	operator&(bitset_impl const& rhs) const HAMON_NOEXCEPT
	{
		return and_impl(rhs, hamon::make_index_sequence<NWords>{});
	}

	HAMON_CXX11_CONSTEXPR bitset_impl
	operator|(bitset_impl const& rhs) const HAMON_NOEXCEPT
	{
		return or_impl(rhs, hamon::make_index_sequence<NWords>{});
	}

	HAMON_CXX11_CONSTEXPR bitset_impl
	operator^(bitset_impl const& rhs) const HAMON_NOEXCEPT
	{
		return xor_impl(rhs, hamon::make_index_sequence<NWords>{});
	}

	HAMON_CXX11_CONSTEXPR bool
	operator==(bitset_impl const& rhs) const HAMON_NOEXCEPT
	{
		return hamon::equal(
			hamon::begin(m_value),
			hamon::end(m_value),
			hamon::begin(rhs.m_value));
	}

	HAMON_CXX14_CONSTEXPR T&
	get_word(hamon::size_t pos) HAMON_NOEXCEPT
	{
		return m_value[whichword(pos)];
	}

	HAMON_CXX11_CONSTEXPR T const&
	get_word(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return m_value[whichword(pos)];
	}

	HAMON_CXX11_CONSTEXPR T
	get_bit(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return T(1 << whichbit(pos));
	}

private:
	struct not_equal_zero
	{
		template <typename U>
		HAMON_CXX11_CONSTEXPR bool operator()(U x) const HAMON_NOEXCEPT
		{
			return x != 0;
		}
	};

	template <typename UInt, hamon::size_t WordsPerUInt = sizeof(UInt) / sizeof(T)>
	HAMON_CXX11_CONSTEXPR bool is_overflow() const HAMON_NOEXCEPT
	{
		return WordsPerUInt < NWords &&
			hamon::any_of(
				hamon::begin(m_value) + WordsPerUInt,
				hamon::end(m_value),
				not_equal_zero{});
	}

	struct to_integer_op
	{
		template <typename U1, typename U2>
		HAMON_CXX11_CONSTEXPR U1 operator()(U1 lhs, U2 rhs) const HAMON_NOEXCEPT
		{
			return static_cast<U1>((static_cast<hamon::uintmax_t>(lhs) << BitsPerWord) + rhs);
		}
	};

	template <typename UInt>
	HAMON_CXX11_CONSTEXPR UInt to_integer() const
	{
		return
			is_overflow<UInt>() ?
				(hamon::detail::throw_overflow_error("bitset::to_integer"), UInt{}) :
			hamon::accumulate(
				hamon::rbegin(m_value),
				hamon::rend(m_value),
				UInt{},
				to_integer_op{});
	}

public:
	HAMON_CXX11_CONSTEXPR unsigned long
	to_ulong() const
	{
		return to_integer<unsigned long>();
	}

	HAMON_CXX11_CONSTEXPR unsigned long long
	to_ullong() const
	{
		return to_integer<unsigned long long>();
	}

	HAMON_CXX11_CONSTEXPR hamon::size_t
	hash() const HAMON_NOEXCEPT
	{
		return hamon::hash(m_value);
	}

private:
	HAMON_CXX11_CONSTEXPR hamon::size_t
	whichword(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return pos / BitsPerWord;
	}

	HAMON_CXX11_CONSTEXPR hamon::size_t
	whichbit(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return pos % BitsPerWord;
	}
};

template <typename T, hamon::size_t NBits>
struct bitset_impl<T, NBits, 1>
{
private:
	static_assert(hamon::is_unsigned<T>::value, "");

	static const hamon::size_t BitsPerWord = hamon::bitsof<T>();

	T	m_value;

public:
	HAMON_CXX11_CONSTEXPR
	bitset_impl() HAMON_NOEXCEPT
		: m_value()
	{}

	HAMON_CXX11_CONSTEXPR
	bitset_impl(unsigned long long val) HAMON_NOEXCEPT
		: m_value(static_cast<T>(val & bitmask()))
	{}

private:
	struct make_word_op
	{
		template <typename U1, typename U2>
		HAMON_CXX11_CONSTEXPR U1 operator()(U1 lhs, U2 rhs) const HAMON_NOEXCEPT
		{
			return static_cast<U1>((static_cast<hamon::uintmax_t>(lhs) << 1) + rhs);
		}
	};

	static HAMON_CXX11_CONSTEXPR T
	make_word(hamon::array<bool, NBits> const& ar) HAMON_NOEXCEPT
	{
		return hamon::accumulate(
			hamon::rbegin(ar),
			hamon::rend(ar),
			T{},
			make_word_op{});
	}

public:
	HAMON_CXX11_CONSTEXPR
	bitset_impl(hamon::array<bool, NBits> const& ar) HAMON_NOEXCEPT
		: bitset_impl(make_word(ar))
	{}

	HAMON_CXX11_CONSTEXPR hamon::size_t count() const HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(hamon::popcount(m_value));
	}

private:
	HAMON_CXX11_CONSTEXPR T bitmask() const HAMON_NOEXCEPT
	{
		return T(-1) >> (BitsPerWord - NBits);
	}

public:
	HAMON_CXX11_CONSTEXPR bitset_impl
	operator~() const HAMON_NOEXCEPT
	{
		return {(unsigned long long)(~m_value & bitmask())};
	}

	HAMON_CXX11_CONSTEXPR bitset_impl
	operator<<(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return {(unsigned long long)((m_value << pos) & bitmask())};
	}

	HAMON_CXX11_CONSTEXPR bitset_impl
	operator>>(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return {(unsigned long long)((m_value >> pos))};
	}

	HAMON_CXX11_CONSTEXPR bitset_impl
	operator&(bitset_impl const& rhs) const HAMON_NOEXCEPT
	{
		return {(unsigned long long)(m_value & rhs.m_value)};
	}

	HAMON_CXX11_CONSTEXPR bitset_impl
	operator|(bitset_impl const& rhs) const HAMON_NOEXCEPT
	{
		return {(unsigned long long)(m_value | rhs.m_value)};
	}

	HAMON_CXX11_CONSTEXPR bitset_impl
	operator^(bitset_impl const& rhs) const HAMON_NOEXCEPT
	{
		return {(unsigned long long)(m_value ^ rhs.m_value)};
	}

	HAMON_CXX11_CONSTEXPR bool
	operator==(bitset_impl const& rhs) const HAMON_NOEXCEPT
	{
		return m_value == rhs.m_value;
	}

	HAMON_CXX14_CONSTEXPR T&
	get_word(hamon::size_t) HAMON_NOEXCEPT
	{
		return m_value;
	}

	HAMON_CXX11_CONSTEXPR T const&
	get_word(hamon::size_t) const HAMON_NOEXCEPT
	{
		return m_value;
	}

	HAMON_CXX11_CONSTEXPR T
	get_bit(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return T(1 << pos);
	}

	HAMON_CXX11_CONSTEXPR unsigned long
	to_ulong() const HAMON_NOEXCEPT
	{
		return static_cast<unsigned long>(m_value);
	}

	HAMON_CXX11_CONSTEXPR unsigned long long
	to_ullong() const HAMON_NOEXCEPT
	{
		return static_cast<unsigned long long>(m_value);
	}

	HAMON_CXX11_CONSTEXPR hamon::size_t
	hash() const HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(m_value);
	}
};

template <typename T, hamon::size_t NBits>
struct bitset_impl<T, NBits, 0>
{
	HAMON_CXX11_CONSTEXPR bitset_impl() HAMON_NOEXCEPT {}
	HAMON_CXX11_CONSTEXPR bitset_impl(unsigned long long) HAMON_NOEXCEPT {}
	HAMON_CXX11_CONSTEXPR bitset_impl(hamon::array<bool, NBits> const&) HAMON_NOEXCEPT {}
	HAMON_CXX11_CONSTEXPR hamon::size_t count() const HAMON_NOEXCEPT { return 0; }
	HAMON_CXX11_CONSTEXPR bitset_impl operator~() const HAMON_NOEXCEPT { return {}; }
	HAMON_CXX11_CONSTEXPR bitset_impl operator<<(hamon::size_t) const HAMON_NOEXCEPT { return {}; }
	HAMON_CXX11_CONSTEXPR bitset_impl operator>>(hamon::size_t) const HAMON_NOEXCEPT { return {}; }
	HAMON_CXX11_CONSTEXPR bitset_impl operator&(bitset_impl const&) const HAMON_NOEXCEPT { return {}; }
	HAMON_CXX11_CONSTEXPR bitset_impl operator|(bitset_impl const&) const HAMON_NOEXCEPT { return {}; }
	HAMON_CXX11_CONSTEXPR bitset_impl operator^(bitset_impl const&) const HAMON_NOEXCEPT { return {}; }
	HAMON_CXX11_CONSTEXPR bool operator==(bitset_impl const&) const HAMON_NOEXCEPT { return true; }

	T& get_word(hamon::size_t)
	{
		hamon::detail::throw_out_of_range("bitset_impl::get_word");
	}

	T const& get_word(hamon::size_t) const
	{
		hamon::detail::throw_out_of_range("bitset_impl::get_word");
	}

	HAMON_CXX11_CONSTEXPR T get_bit(hamon::size_t) const HAMON_NOEXCEPT { return 0; }
	HAMON_CXX11_CONSTEXPR unsigned long to_ulong() const HAMON_NOEXCEPT { return 0; }
	HAMON_CXX11_CONSTEXPR unsigned long long to_ullong() const HAMON_NOEXCEPT { return 0; }
	HAMON_CXX11_CONSTEXPR hamon::size_t hash() const HAMON_NOEXCEPT { return 0; }
};

}	// namespace bitset_detail

template <hamon::size_t N>
class bitset
{
private:
	using WordType =
		hamon::conditional_t<(N <=  8),
			hamon::uint8_t,
		hamon::conditional_t<(N <= 16),
			hamon::uint16_t,
			hamon::uint32_t
		>>;
	static const hamon::size_t BitsPerWord = hamon::bitsof<WordType>();
	static const hamon::size_t NWords = static_cast<hamon::size_t>(hamon::round_up(N, BitsPerWord)) / BitsPerWord;

	using Impl = bitset_detail::bitset_impl<WordType, N, NWords>;
	Impl	m_impl;

public:
	// bit reference
	class reference
	{
		friend class bitset;

		WordType*	m_word;
		WordType	m_mask;

		HAMON_CXX11_CONSTEXPR reference() = delete;

		HAMON_CXX11_CONSTEXPR
		reference(WordType* word, WordType mask) HAMON_NOEXCEPT
			: m_word(word)
			, m_mask(mask)
		{}

	public:
		HAMON_CXX11_CONSTEXPR reference(reference const&) = default;

#if defined(HAMON_HAS_CXX20_CONSTEXPR)
		constexpr ~reference() HAMON_NOEXCEPT {}
#else
		// C++規格とは異なってしまうが、constexprにするため
		// デストラクタをtrivialにする。
		~reference() HAMON_NOEXCEPT = default;
#endif
		
		// for b[i] = x;
		HAMON_CXX14_CONSTEXPR reference&
		operator=(bool x) HAMON_NOEXCEPT
		{
			if (x)
			{
				*m_word = static_cast<WordType>(*m_word | m_mask);
			}
			else
			{
				*m_word = static_cast<WordType>(*m_word & ~m_mask);
			}

			return *this;
		}

		// for b[i] = b[j];
		HAMON_CXX14_CONSTEXPR reference&
		operator=(reference const& rhs) HAMON_NOEXCEPT
		{
			return this->operator=(rhs.operator bool());
		}

		// flips the bit
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
		operator~() const HAMON_NOEXCEPT
		{
			return !this->operator bool();
		}

		// for x = b[i];
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
		operator bool() const HAMON_NOEXCEPT
		{
			return (*m_word & m_mask) != 0;
		}

		// for b[i].flip();
		HAMON_CXX14_CONSTEXPR reference& flip() HAMON_NOEXCEPT
		{
			*m_word ^= m_mask;
			return *this;
		}
	};

	// [bitset.cons], constructors
	HAMON_CXX11_CONSTEXPR
	bitset() HAMON_NOEXCEPT
		: m_impl()
	{}

	HAMON_CXX11_CONSTEXPR
	bitset(unsigned long long val) HAMON_NOEXCEPT
		: m_impl(val)
	{}

private:
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wunused-but-set-parameter")

	template <typename Traits, typename CharT, typename SizeType, hamon::size_t... Is>
	static HAMON_CXX11_CONSTEXPR hamon::array<bool, N>
	string_to_bool_array_impl(CharT const* str, SizeType n, CharT one, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
	{
		return {{ (Is < n && Traits::eq(*(str + n - Is - 1), one))... }};
	}

HAMON_WARNING_POP()

	template <typename CharT, typename Traits>
	struct is_valid_char
	{
		CharT zero;
		CharT one;

		HAMON_CXX11_CONSTEXPR bool operator()(CharT c) const HAMON_NOEXCEPT
		{
			return Traits::eq(c, zero) || Traits::eq(c, one);
		}
	};

	template <typename Traits, typename CharT, typename SizeType>
	static HAMON_CXX11_CONSTEXPR bool
	is_valid_string(CharT const* str, SizeType pos, SizeType n, CharT zero, CharT one) HAMON_NOEXCEPT
	{
		return hamon::all_of(
			str + pos,
			str + pos + n,
			is_valid_char<CharT, Traits>{zero, one});
	}

	template <typename Traits, typename CharT, typename SizeType>
	static HAMON_CXX11_CONSTEXPR hamon::array<bool, N>
	string_to_bool_array_2(CharT const* str, SizeType pos, SizeType n, CharT zero, CharT one)
	{
		return
			!is_valid_string<Traits>(str, pos, n, zero, one) ?
				(hamon::detail::throw_invalid_argument("bitset::bitset"), hamon::array<bool, N>{}) :
			string_to_bool_array_impl<Traits>(
				str + pos,
				hamon::min(N, n),
				one,
				hamon::make_index_sequence<N>{});
	}

	template <typename Traits, typename CharT, typename SizeType>
	static HAMON_CXX11_CONSTEXPR hamon::array<bool, N>
	string_to_bool_array(CharT const* str, SizeType len, SizeType pos, SizeType n, CharT zero, CharT one)
	{
		return
			pos > len ?	// [bitset.cons]/7
				(hamon::detail::throw_out_of_range("bitset::bitset"), hamon::array<bool, N>{}) :
			string_to_bool_array_2<Traits>(str, pos, hamon::min(n, len - pos), zero, one);
	}

public:
	template <typename CharT, typename Traits, typename Allocator>
	HAMON_CXX11_CONSTEXPR explicit
	bitset(
		hamon::basic_string<CharT, Traits, Allocator> const& str,
		typename hamon::basic_string<CharT, Traits, Allocator>::size_type pos = 0,
		typename hamon::basic_string<CharT, Traits, Allocator>::size_type n = hamon::basic_string<CharT, Traits, Allocator>::npos,
		CharT zero = CharT('0'),
		CharT one = CharT('1'))
		: m_impl(string_to_bool_array<Traits>(str.c_str(), str.length(), pos, n, zero, one))
	{}

	template <typename CharT>
	HAMON_CXX11_CONSTEXPR explicit
	bitset(
		CharT const* str,
		typename hamon::basic_string<CharT>::size_type n = hamon::basic_string<CharT>::npos,
		CharT zero = CharT('0'),
		CharT one = CharT('1'))
		: m_impl(string_to_bool_array<hamon::char_traits<CharT>>(str, hamon::ct::strlen(str), hamon::size_t(0), n, zero, one))
	{}

	// [bitset.members], bitset operations
	HAMON_CXX14_CONSTEXPR bitset&
	operator&=(bitset const& rhs) HAMON_NOEXCEPT
	{
		*this = *this & rhs;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR bitset&
	operator|=(bitset const& rhs) HAMON_NOEXCEPT
	{
		*this = *this | rhs;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR bitset&
	operator^=(bitset const& rhs) HAMON_NOEXCEPT
	{
		*this = *this ^ rhs;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR bitset&
	operator<<=(hamon::size_t pos) HAMON_NOEXCEPT
	{
		*this = *this << pos;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR bitset&
	operator>>=(hamon::size_t pos) HAMON_NOEXCEPT
	{
		*this = *this >> pos;
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bitset
	operator<<(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return
			pos >= N ? bitset{} :
			pos == 0 ? *this :
			bitset{m_impl << pos};
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bitset
	operator>>(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return
			pos >= N ? bitset{} :
			pos == 0 ? *this :
			bitset{m_impl >> pos};
	}
	
	HAMON_CXX14_CONSTEXPR bitset&
	set() HAMON_NOEXCEPT
	{
		// [bitset.members]/13
		m_impl = ~Impl{};

		// [bitset.members]/14
		return *this;
	}
	
	HAMON_CXX14_CONSTEXPR bitset&
	set(hamon::size_t pos, bool val = true)
	{
		// [bitset.members]/17
		if (pos >= N)
		{
			hamon::detail::throw_out_of_range("bitset::set");
		}

		// [bitset.members]/15
		if (val)
		{
			unchecked_set(pos);
		}
		else
		{
			unchecked_reset(pos);
		}

		// [bitset.members]/16
		return *this;
	}

	HAMON_CXX14_CONSTEXPR bitset&
	reset() HAMON_NOEXCEPT
	{
		// [bitset.members]/18
		m_impl = Impl{};

		// [bitset.members]/19
		return *this;
	}

	HAMON_CXX14_CONSTEXPR bitset&
	reset(hamon::size_t pos)
	{
		// [bitset.members]/22
		if (pos >= N)
		{
			hamon::detail::throw_out_of_range("bitset::reset");
		}

		// [bitset.members]/20
		unchecked_reset(pos);

		// [bitset.members]/21
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bitset
	operator~() const HAMON_NOEXCEPT
	{
		return bitset{~m_impl};
	}

	HAMON_CXX14_CONSTEXPR bitset&
	flip() HAMON_NOEXCEPT
	{
		// [bitset.members]/25
		m_impl = ~m_impl;

		// [bitset.members]/26
		return *this;
	}

	HAMON_CXX14_CONSTEXPR bitset&
	flip(hamon::size_t pos)
	{
		// [bitset.members]/29
		if (pos >= N)
		{
			hamon::detail::throw_out_of_range("bitset::flip");
		}

		// [bitset.members]/27
		if (unchecked_test(pos))
		{
			unchecked_reset(pos);
		}
		else
		{
			unchecked_set(pos);
		}

		// [bitset.members]/28
		return *this;
	}

	// element access
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	operator[](hamon::size_t pos) const
	{
		return unchecked_test(pos);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reference
	operator[](hamon::size_t pos)
	{
		return reference(&m_impl.get_word(pos), m_impl.get_bit(pos));
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR unsigned long
	to_ulong() const
	{
		return m_impl.to_ulong();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR unsigned long long
	to_ullong() const
	{
		return m_impl.to_ullong();
	}

	template <
		typename CharT = char,
		typename Traits = hamon::char_traits<CharT>,
		typename Allocator = std::allocator<CharT>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::basic_string<CharT, Traits, Allocator>
	to_string(CharT zero = CharT('0'), CharT one = CharT('1')) const
	{
HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (100000 <= HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 110000)
HAMON_WARNING_DISABLE_GCC("-Wtype-limits")	// GCC10 だと不要な警告が出る
#endif
		hamon::basic_string<CharT, Traits, Allocator> s(N, zero);
		for (hamon::size_t i = 0; i < N; ++i)
		{
			if (unchecked_test(i))
			{
				s[N - i - 1] = one;
			}
		}
		return s;
HAMON_WARNING_POP()
	}

	// observers
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	count() const HAMON_NOEXCEPT
	{
		// [bitset.members]/43
		return m_impl.count();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	size() const HAMON_NOEXCEPT
	{
		// [bitset.members]/44
		return N;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	operator==(bitset const& rhs) const HAMON_NOEXCEPT
	{
		// [bitset.members]/45
		return m_impl == rhs.m_impl;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	operator!=(bitset const& rhs) const HAMON_NOEXCEPT
	{
		return !(*this == rhs);
	}
#endif

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	test(hamon::size_t pos) const
	{
		return pos >= N ?			// [bitset.members]/47
			(hamon::detail::throw_out_of_range("bitset::test"), false) :
			unchecked_test(pos);	// [bitset.members]/46
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	all() const HAMON_NOEXCEPT
	{
		// [bitset.members]/48
		return count() == size();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	any() const HAMON_NOEXCEPT
	{
		// [bitset.members]/49
		return count() != 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	none() const HAMON_NOEXCEPT
	{
		// [bitset.members]/50
		return count() == 0;
	}

	// extension
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	hash() const HAMON_NOEXCEPT
	{
		return m_impl.hash();
	}

private:
	HAMON_CXX11_CONSTEXPR
	bitset(Impl const& impl)
		: m_impl(impl)
	{}

	HAMON_CXX11_CONSTEXPR bool unchecked_test(hamon::size_t pos) const
	{
		return (m_impl.get_word(pos) & m_impl.get_bit(pos)) != 0;
	}

	HAMON_CXX14_CONSTEXPR void unchecked_set(hamon::size_t pos)
	{
		auto& w = m_impl.get_word(pos);
		w = static_cast<WordType>(w | m_impl.get_bit(pos));
	}

	HAMON_CXX14_CONSTEXPR void unchecked_reset(hamon::size_t pos)
	{
		auto& w = m_impl.get_word(pos);
		w = static_cast<WordType>(w & ~m_impl.get_bit(pos));
	}

private:
	template <hamon::size_t M>
	friend HAMON_CXX11_CONSTEXPR bitset<M>
	operator&(bitset<M> const& lhs, bitset<M> const& rhs) HAMON_NOEXCEPT;

	template <hamon::size_t M>
	friend HAMON_CXX11_CONSTEXPR bitset<M>
	operator|(bitset<M> const& lhs, bitset<M> const& rhs) HAMON_NOEXCEPT;

	template <hamon::size_t M>
	friend HAMON_CXX11_CONSTEXPR bitset<M>
	operator^(bitset<M> const& lhs, bitset<M> const& rhs) HAMON_NOEXCEPT;
};

// [bitset.operators], bitset operators
template <hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bitset<N>
operator&(bitset<N> const& lhs, bitset<N> const& rhs) HAMON_NOEXCEPT
{
	// [bitset.operators]/1
	return bitset<N>{lhs.m_impl & rhs.m_impl};
}

template <hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bitset<N>
operator|(bitset<N> const& lhs, bitset<N> const& rhs) HAMON_NOEXCEPT
{
	// [bitset.operators]/2
	return bitset<N>{lhs.m_impl | rhs.m_impl};
}

template <hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bitset<N>
operator^(bitset<N> const& lhs, bitset<N> const& rhs) HAMON_NOEXCEPT
{
	// [bitset.operators]/3
	return bitset<N>{lhs.m_impl ^ rhs.m_impl};
}

HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 130000)
HAMON_WARNING_DISABLE_GCC("-Wdangling-reference")
#endif

template <typename CharT, typename Traits, hamon::size_t N>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, bitset<N>& x)
{
	std::ios_base::iostate state = std::ios_base::goodbit;
	typename std::basic_istream<CharT, Traits>::sentry sen(is);
	if (sen)
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		try
		{
#endif
			hamon::basic_string<CharT, Traits> str;
			auto const& ct = std::use_facet<std::ctype<CharT>>(is.getloc());
			hamon::size_t count = 0;
			CharT const zero = ct.widen('0');
			CharT const one  = ct.widen('1');
			while (count != N)
			{
				typename Traits::int_type i = is.rdbuf()->sgetc();
				if (Traits::eq_int_type(i, Traits::eof()))
				{
					state |= std::ios_base::eofbit;
					break;
				}

				CharT ch = Traits::to_char_type(i);
				if (!Traits::eq(ch, zero) && !Traits::eq(ch, one))
				{
					break;
				}

				str.push_back(ch);
				++count;
				is.rdbuf()->sbumpc();
			}

			x = bitset<N>(str);
			
			// [bitset.operators]/6
			if (count == 0 && N > 0)
			{
				state |= std::ios_base::failbit;
			}
#if !defined(HAMON_NO_EXCEPTIONS)
		}
		catch (...)
		{
			state |= std::ios_base::badbit;
		}
#endif
		is.setstate(state);
	}

	// [bitset.operators]/7
	return is;
}

HAMON_WARNING_POP()

template <typename CharT, typename Traits, hamon::size_t N>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, bitset<N> const& x)
{
	// [bitset.operators]/8
	return os << x.template to_string<CharT, Traits>
		(std::use_facet<std::ctype<CharT>>(os.getloc()).widen('0'),
		 std::use_facet<std::ctype<CharT>>(os.getloc()).widen('1'));
}

}	// namespace hamon

#include <functional>

namespace std
{

// [bitset.hash], hash support
template <hamon::size_t N>
struct hash<hamon::bitset<N>>
{
	HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR // extension
	hamon::size_t operator()(hamon::bitset<N> const& x) const HAMON_NOEXCEPT
	{
		return x.hash();
	}
};

}	// namespace std

HAMON_WARNING_POP()

#endif

#endif // HAMON_BITSET_BITSET_HPP
