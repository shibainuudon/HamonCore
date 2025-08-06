/**
 *	@file	hive_iterator.hpp
 *
 *	@brief	hive_iterator の定義
 */

#ifndef HAMON_HIVE_DETAIL_HIVE_ITERATOR_HPP
#define HAMON_HIVE_DETAIL_HIVE_ITERATOR_HPP

#include <hamon/hive/detail/hive_block.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/tuple/tie.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename HiveImpl, bool Const>
struct hive_iterator
{
public:
	using iterator_concept  = hamon::bidirectional_iterator_tag;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = typename HiveImpl::value_type;
	using difference_type   = typename HiveImpl::difference_type;
	using pointer           = hamon::conditional_t<Const, typename HiveImpl::const_pointer, typename HiveImpl::pointer>;
	using reference         = hamon::conditional_t<Const, typename HiveImpl::const_reference, typename HiveImpl::reference>;

private:
	using Block = hive_block<value_type>;
	using SizeType = typename Block::size_type;

	Block*	 m_block;
	SizeType m_index;

	friend hive_iterator<HiveImpl, !Const>;
	friend HiveImpl;

private:
	explicit HAMON_CXX11_CONSTEXPR
	hive_iterator(Block* block) HAMON_NOEXCEPT
		: m_block(block)
		, m_index(block ? block->FirstIndex() : 0)
	{}

	explicit HAMON_CXX11_CONSTEXPR
	hive_iterator(Block* block, SizeType index) HAMON_NOEXCEPT
		: m_block(block)
		, m_index(index)
	{}

public:
	HAMON_CXX11_CONSTEXPR
	hive_iterator() HAMON_NOEXCEPT
		: m_block(nullptr)
		, m_index(0)
	{}

	template <bool C, typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	hive_iterator(hive_iterator<HiveImpl, C> const& i) HAMON_NOEXCEPT
		: m_block(i.m_block)
		, m_index(i.m_index)
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	reference operator*() const HAMON_NOEXCEPT
	{
		return *(this->operator->());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	pointer operator->() const HAMON_NOEXCEPT
	{
		return m_block->GetElement(m_index);
	}

	HAMON_CXX14_CONSTEXPR
	hive_iterator& operator++() HAMON_NOEXCEPT
	{
		m_index = m_block->NextIndex(m_index);
		if (!m_block->IsValidIndex(m_index))
		{
			m_block = m_block->NextBlock();
			m_index = m_block->FirstIndex();
		}
		return *this;
	}

	HAMON_CXX14_CONSTEXPR
	hive_iterator operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR
	hive_iterator& operator--() HAMON_NOEXCEPT
	{
		m_index = m_block->PrevIndex(m_index);
		if (!m_block->IsValidIndex(m_index))
		{
			m_block = m_block->PrevBlock();
			m_index = m_block->LastIndex();
		}
		return *this;
	}

	HAMON_CXX14_CONSTEXPR
	hive_iterator operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator==(hive_iterator const& x, hive_iterator const& y) HAMON_NOEXCEPT
	{
		return x.m_block == y.m_block &&
			x.m_index == y.m_index;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator!=(hive_iterator const& x, hive_iterator const& y) HAMON_NOEXCEPT
	{
		return !(x == y);
	}
#endif

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator<(hive_iterator const& x, hive_iterator const& y) HAMON_NOEXCEPT
	{
		return
			(x.m_block == nullptr || y.m_block == nullptr) ?
				x.m_block < y.m_block :
			hamon::tie(x.m_block->m_index, x.m_index) <
			hamon::tie(y.m_block->m_index, y.m_index);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator>(hive_iterator const& x, hive_iterator const& y) HAMON_NOEXCEPT
	{
		return y < x;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator<=(hive_iterator const& x, hive_iterator const& y) HAMON_NOEXCEPT
	{
		return !(y < x);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator>=(hive_iterator const& x, hive_iterator const& y) HAMON_NOEXCEPT
	{
		return !(x < y);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR hamon::strong_ordering
	operator<=>(hive_iterator const& x, hive_iterator const& y) HAMON_NOEXCEPT
	{
		return
			(x.m_block == nullptr || y.m_block == nullptr) ?
				x.m_block <=> y.m_block :
			hamon::tie(x.m_block->m_index, x.m_index) <=>
			hamon::tie(y.m_block->m_index, y.m_index);
	}
#endif
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_HIVE_DETAIL_HIVE_ITERATOR_HPP
