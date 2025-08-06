/**
 *	@file	hive_block.hpp
 *
 *	@brief	hive_block の定義
 */

#ifndef HAMON_HIVE_DETAIL_HIVE_BLOCK_HPP
#define HAMON_HIVE_DETAIL_HIVE_BLOCK_HPP

#include <hamon/hive/detail/hive_active_flags.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct hive_block
{
	using size_type = hamon::size_t;	// TODO: capacityとcountのsize_typeはもっと小さい型でも良い (最大でも hive_traits::hard_limits().max なので)

	size_type           m_capacity = 0;
	size_type           m_count    = 0;
	size_type			m_index    = 0;		// イテレータの大小比較のため
	hive_active_flags	m_active_flags;
	T*                  m_elements = nullptr;
	hive_block*	m_active_prev   = nullptr;
	hive_block*	m_active_next   = nullptr;
	hive_block*	m_open_prev     = nullptr;	// TODO: OpenBlocks は一方向リストで良いかも
	hive_block*	m_open_next     = nullptr;
	hive_block*	m_reserved_prev = nullptr;	// TODO: ReservedBlocks は一方向リストで良いかも
	hive_block*	m_reserved_next = nullptr;

	explicit HAMON_CXX14_CONSTEXPR
	hive_block() HAMON_NOEXCEPT
	{}

	template <typename Allocator>
	explicit HAMON_CXX14_CONSTEXPR
	hive_block(Allocator& allocator, size_type capacity)
		: m_capacity(capacity)
		, m_active_flags(allocator, capacity)	// may throw
	{
		using AllocTraits = hamon::allocator_traits<Allocator>;
		m_elements = AllocTraits::allocate(allocator, m_capacity);	// may throw
	}

	// コピー禁止
	hive_block(hive_block const&) = delete;
	hive_block& operator=(hive_block const&) = delete;

	HAMON_CXX14_CONSTEXPR void
	InitializeAsHead() HAMON_NOEXCEPT
	{
		m_index = hamon::numeric_limits<size_type>::max();
		m_active_prev   = this;
		m_active_next   = this;
		m_open_prev     = this;
		m_open_next     = this;
		m_reserved_prev = this;
		m_reserved_next = this;
	}

	HAMON_CXX11_CONSTEXPR bool
	IsWithinLimits(hive_limits block_limits) const HAMON_NOEXCEPT
	{
		return block_limits.min <= m_capacity && m_capacity <= block_limits.max;
	}

	HAMON_CXX14_CONSTEXPR T*
	GetElement(size_type index) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(index < m_capacity);
		return &m_elements[index];
	}

	HAMON_CXX11_CONSTEXPR bool
	Includes(T const* p) const HAMON_NOEXCEPT
	{
		return m_elements <= p && p < (m_elements + m_capacity);
	}

	HAMON_CXX11_CONSTEXPR size_type
	GetIndex(T const* p) const HAMON_NOEXCEPT
	{
		return static_cast<size_type>(p - m_elements);
	}

	HAMON_CXX11_CONSTEXPR bool
	IsFull() const HAMON_NOEXCEPT
	{
		return m_count == m_capacity;
	}

	HAMON_CXX11_CONSTEXPR bool
	IsOpen() const HAMON_NOEXCEPT
	{
		return m_count < m_capacity;
	}

	HAMON_CXX11_CONSTEXPR bool
	IsEmpty() const HAMON_NOEXCEPT
	{
		return m_count == 0;
	}

	HAMON_CXX11_CONSTEXPR hive_block*
	NextBlock() const HAMON_NOEXCEPT
	{
		return m_active_next;
	}

	HAMON_CXX11_CONSTEXPR hive_block*
	PrevBlock() const HAMON_NOEXCEPT
	{
		return m_active_prev;
	}

	HAMON_CXX14_CONSTEXPR size_type
	NextIndex(size_type index) const HAMON_NOEXCEPT
	{
		// TODO
		//HAMON_ASSERT(m_active_flags.Test(index));
		return m_active_flags.NextActiveIndex(index);
	}

	HAMON_CXX14_CONSTEXPR size_type
	PrevIndex(size_type index) const HAMON_NOEXCEPT
	{
		// TODO
		//HAMON_ASSERT(m_active_flags.Test(index));
		return m_active_flags.PrevActiveIndex(index);
	}

	HAMON_CXX11_CONSTEXPR size_type
	FirstIndex() const HAMON_NOEXCEPT
	{
		// TODO この辺りを整理したい
		return this->IsEmpty() ? size_type{0} : m_active_flags.FirstActiveIndex();
	}

	HAMON_CXX11_CONSTEXPR size_type
	LastIndex() const HAMON_NOEXCEPT
	{
		// TODO この辺りを整理したい
		return this->IsEmpty() ? size_type{0} : m_active_flags.LastActiveIndex();
	}

	HAMON_CXX11_CONSTEXPR bool
	IsValidIndex(size_type index) const HAMON_NOEXCEPT
	{
		return index < m_capacity;
	}

	template <typename Allocator, typename... Args>
	HAMON_CXX14_CONSTEXPR size_type
	Emplace(Allocator& allocator, Args&&... args)
	{
		size_type const index = m_active_flags.FirstOpenIndex();

		HAMON_ASSERT(!m_active_flags.Test(index));

		using AllocTraits = hamon::allocator_traits<Allocator>;
		AllocTraits::construct(allocator, m_elements + index, hamon::forward<Args>(args)...);	// may throw

		m_active_flags.Set(index);
		++m_count;

		return index;
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR void
	Erase(Allocator& allocator, size_type index) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(m_active_flags.Test(index));

		using AllocTraits = hamon::allocator_traits<Allocator>;
		AllocTraits::destroy(allocator, m_elements + index);

		m_active_flags.Reset(index);
		--m_count;
	}

	template <typename Allocator>
	HAMON_CXX14_CONSTEXPR void
	Deallocate(Allocator& allocator) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(this->IsEmpty());

		if (m_elements != nullptr)
		{
			using AllocTraits = hamon::allocator_traits<Allocator>;
			AllocTraits::deallocate(allocator, m_elements, m_capacity);
			m_elements = nullptr;
		}

		m_active_flags.Deallocate(allocator, m_capacity);
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_HIVE_DETAIL_HIVE_BLOCK_HPP
