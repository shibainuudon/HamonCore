/**
 *	@file	hive_active_flags.hpp
 *
 *	@brief	hive_active_flags の定義
 */

#ifndef HAMON_HIVE_DETAIL_HIVE_ACTIVE_FLAGS_HPP
#define HAMON_HIVE_DETAIL_HIVE_ACTIVE_FLAGS_HPP

#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/countl_zero.hpp>
#include <hamon/bit/countr_one.hpp>
#include <hamon/bit/countr_zero.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/bit/shr.hpp>
#include <hamon/cmath/round_up.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uint64_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct hive_active_flags
{
private:
	using size_type = hamon::size_t;
	using WordType = hamon::uint64_t;

	static const hamon::size_t BitsPerWord = hamon::bitsof<WordType>();
	static const size_type InvalidIndex = static_cast<size_type>(~0ULL);

private:
	// 下位ビットから数えて最初の1のビット
	static HAMON_CXX11_CONSTEXPR size_type
	FirstOneBit(hamon::uint64_t val)
	{
		return static_cast<size_type>(hamon::countr_zero(val));
	}

	// 下位ビットから数えて最後の1のビット
	static HAMON_CXX11_CONSTEXPR size_type
	LastOneBit(hamon::uint64_t val)
	{
		return hamon::bitsof(val) - static_cast<size_type>(hamon::countl_zero(val)) - 1;
	}

	// 下位ビットから数えて最初の0のビット
	static HAMON_CXX11_CONSTEXPR size_type
	FirstZeroBit(hamon::uint64_t val)
	{
		return static_cast<size_type>(hamon::countr_one(val));
	}

	// 下位ビットから数えて次の1のビット
	static HAMON_CXX14_CONSTEXPR size_type
	NextOneBit(hamon::uint64_t val, size_type index) HAMON_NOEXCEPT
	{
		val = hamon::shr(val, static_cast<unsigned int>(index + 1));
		val = hamon::shl(val, static_cast<unsigned int>(index + 1));
		return FirstOneBit(val);
	}

	// 下位ビットから数えて前の1のビット
	static HAMON_CXX14_CONSTEXPR size_type
	PrevOneBit(hamon::uint64_t val, size_type index) HAMON_NOEXCEPT
	{
		val = hamon::shl(val, static_cast<unsigned int>(hamon::bitsof(val) - index));
		val = hamon::shr(val, static_cast<unsigned int>(hamon::bitsof(val) - index));
		return LastOneBit(val);
	}

private:
	WordType*	m_value        = nullptr;
	WordType	m_active_flags = 0;
	WordType	m_open_flags   = hamon::numeric_limits<WordType>::max();

private:
	static HAMON_CXX14_CONSTEXPR size_type
	CalcNWords(size_type capacity)
	{
		if (capacity == 0)
		{
			return 1;
		}

		return static_cast<hamon::size_t>(hamon::round_up(capacity, BitsPerWord)) / BitsPerWord;
	}

	static HAMON_CXX11_CONSTEXPR size_type
	WhichWord(size_type index)
	{
		return index / BitsPerWord;
	}

	static HAMON_CXX11_CONSTEXPR size_type
	WhichBit(size_type index)
	{
		return index % BitsPerWord;
	}

	HAMON_CXX14_CONSTEXPR WordType&
	GetWord(hamon::size_t pos) HAMON_NOEXCEPT
	{
		return m_value[WhichWord(pos)];
	}

	HAMON_CXX14_CONSTEXPR WordType const&
	GetWord(hamon::size_t pos) const HAMON_NOEXCEPT
	{
		return m_value[WhichWord(pos)];
	}

	static HAMON_CXX14_CONSTEXPR size_type
	CalcIndex(size_type w, size_type b)
	{
		return w * BitsPerWord + b;
	}

public:
	explicit HAMON_CXX14_CONSTEXPR
	hive_active_flags() HAMON_NOEXCEPT
	{}

	template <typename Allocator>
	explicit HAMON_CXX14_CONSTEXPR
	hive_active_flags(Allocator& allocator, size_type capacity)
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;
		using WordAllocator   = typename AllocTraits::template rebind_alloc<WordType>;
		using WordAllocTraits = typename AllocTraits::template rebind_traits<WordType>;

		auto const nwords = CalcNWords(capacity);

		WordAllocator word_allocator(allocator);
		m_value = WordAllocTraits::allocate(word_allocator, nwords);	// may throw
		hamon::detail::uninitialized_value_construct_n_impl(word_allocator, m_value, nwords);	// may throw
	}

	// コピー禁止
	hive_active_flags(hive_active_flags const&) = delete;
	hive_active_flags& operator=(hive_active_flags const&) = delete;

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR void
	Deallocate(Allocator& allocator, size_type capacity) HAMON_NOEXCEPT
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;
		using WordAllocator   = typename AllocTraits::template rebind_alloc<WordType>;
		using WordAllocTraits = typename AllocTraits::template rebind_traits<WordType>;

		if (m_value != nullptr)
		{
			auto const nwords = CalcNWords(capacity);

			WordAllocator word_allocator(allocator);
			WordAllocTraits::deallocate(word_allocator, m_value, nwords);
			m_value = nullptr;
		}
	}

	HAMON_CXX14_CONSTEXPR bool
	Test(size_type index) const HAMON_NOEXCEPT
	{
		return (GetWord(index) & (1ULL << WhichBit(index))) != 0;
	}

	HAMON_CXX14_CONSTEXPR void
	Set(size_type index) HAMON_NOEXCEPT
	{
		GetWord(index) |= (1ULL << WhichBit(index));
		m_active_flags |= (1ULL << WhichWord(index));
		if (GetWord(index) == WordType(~0ULL))
		{
			m_open_flags &= ~(1ULL << WhichWord(index));
		}
	}

	HAMON_CXX14_CONSTEXPR void
	Reset(size_type index) HAMON_NOEXCEPT
	{
		GetWord(index) &= ~(1ULL << WhichBit(index));
		m_open_flags |= (1ULL << WhichWord(index));
		if (GetWord(index) == 0)
		{
			m_active_flags &= ~(1ULL << WhichWord(index));
		}
	}

	HAMON_CXX14_CONSTEXPR size_type
	FirstActiveIndex() const HAMON_NOEXCEPT
	{
		auto const w = FirstOneBit(m_active_flags);
		auto const b = FirstOneBit(m_value[w]);
		return CalcIndex(w, b);
	}

	HAMON_CXX14_CONSTEXPR size_type
	LastActiveIndex() const HAMON_NOEXCEPT
	{
		auto const w = LastOneBit(m_active_flags);
		auto const b = LastOneBit(m_value[w]);
		return CalcIndex(w, b);
	}

	HAMON_CXX14_CONSTEXPR size_type
	FirstOpenIndex() const HAMON_NOEXCEPT
	{
		auto const w = FirstOneBit(m_open_flags);
		auto const b = FirstZeroBit(m_value[w]);
		return CalcIndex(w, b);
	}

	HAMON_CXX14_CONSTEXPR size_type
	NextActiveIndex(size_type index) const HAMON_NOEXCEPT
	{
		if (m_value != nullptr)
		{
			{
				auto const b = NextOneBit(GetWord(index), WhichBit(index));
				if (b < BitsPerWord)
				{
					auto const w = WhichWord(index);
					return CalcIndex(w, b);
				}
			}
			{
				auto const w = NextOneBit(m_active_flags, WhichWord(index));
				if (w < BitsPerWord)
				{
					auto const b = FirstOneBit(m_value[w]);
					return CalcIndex(w, b);
				}
			}
		}
		return InvalidIndex;
	}

	HAMON_CXX14_CONSTEXPR size_type
	PrevActiveIndex(size_type index) const HAMON_NOEXCEPT
	{
		if (m_value != nullptr)
		{
			{
				auto const b = PrevOneBit(GetWord(index), WhichBit(index));
				if (b < BitsPerWord)
				{
					auto const w = WhichWord(index);
					return CalcIndex(w, b);
				}
			}
			{
				auto const w = PrevOneBit(m_active_flags, WhichWord(index));
				if (w < BitsPerWord)
				{
					auto const b = LastOneBit(m_value[w]);
					return CalcIndex(w, b);
				}
			}
		}
		return InvalidIndex;
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_HIVE_DETAIL_HIVE_ACTIVE_FLAGS_HPP
