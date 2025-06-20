/**
 *	@file	deque_iterator.hpp
 *
 *	@brief	deque_iterator の定義
 */

#ifndef HAMON_DEQUE_DETAIL_DEQUE_ITERATOR_HPP
#define HAMON_DEQUE_DETAIL_DEQUE_ITERATOR_HPP

#include <hamon/compare/strong_ordering.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4308)	// 負の整数定数が符号なしの型に変換されました。

template <typename Deque, typename T, bool Const>
struct deque_iterator
{
private:
	friend deque_iterator<Deque, T, !Const>;
	friend Deque;
	using deque_ptr = hamon::conditional_t<Const, Deque const*, Deque*>;

public:
	//using iterator_concept  = hamon::random_access_iterator_tag;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = typename Deque::difference_type;
	using pointer           = hamon::conditional_t<Const, T const*, T*>;
	using reference         = hamon::conditional_t<Const, T const&, T&>;

	HAMON_CXX11_CONSTEXPR
	deque_iterator() HAMON_NOEXCEPT
		: m_deque()
		, m_offset()
	{}

private:
	HAMON_CXX11_CONSTEXPR
	deque_iterator(deque_ptr p, difference_type offset) HAMON_NOEXCEPT
		: m_deque(p)
		, m_offset(offset)
	{}

public:
	template <bool C,
		typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	deque_iterator(deque_iterator<Deque, T, C> const& i) HAMON_NOEXCEPT
		: m_deque(i.m_deque)
		, m_offset(i.m_offset)
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	reference operator*() const HAMON_NOEXCEPT
	{
		return m_deque->Subscript(m_offset);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	pointer operator->() const HAMON_NOEXCEPT
	{
		return hamon::pointer_traits<pointer>::pointer_to(**this);
	}

	HAMON_CXX14_CONSTEXPR deque_iterator&
	operator++() HAMON_NOEXCEPT
	{
		++m_offset;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR deque_iterator
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR deque_iterator&
	operator--() HAMON_NOEXCEPT
	{
		--m_offset;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR deque_iterator
	operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR deque_iterator&
	operator+=(difference_type n) HAMON_NOEXCEPT
	{
		m_offset += n;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR deque_iterator&
	operator-=(difference_type n) HAMON_NOEXCEPT
	{
		m_offset -= n;
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
	operator[](difference_type n) const HAMON_NOEXCEPT
	{
		return *(*this + n);
	}

private:
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR deque_iterator
	operator+(deque_iterator const& i, difference_type n) HAMON_NOEXCEPT
	{
		return deque_iterator(i.m_deque, i.m_offset + n);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR deque_iterator
	operator+(difference_type n, deque_iterator const& i) HAMON_NOEXCEPT
	{
		return deque_iterator(i.m_deque, i.m_offset + n);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR deque_iterator
	operator-(deque_iterator const& i, difference_type n) HAMON_NOEXCEPT
	{
		return deque_iterator(i.m_deque, i.m_offset - n);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type
	operator-(deque_iterator const& lhs, deque_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_offset - rhs.m_offset;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator==(deque_iterator const& lhs, deque_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_offset == rhs.m_offset;
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR hamon::strong_ordering
	operator<=>(deque_iterator const& lhs, deque_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_offset <=> rhs.m_offset;
	}
#else
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator!=(deque_iterator const& lhs, deque_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator<(deque_iterator const& lhs, deque_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_offset < rhs.m_offset;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator>(deque_iterator const& lhs, deque_iterator const& rhs) HAMON_NOEXCEPT
	{
		return rhs < lhs;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator<=(deque_iterator const& lhs, deque_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(rhs < lhs);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator>=(deque_iterator const& lhs, deque_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs < rhs);
	}
#endif
private:
	deque_ptr		m_deque;
	difference_type m_offset;
};

HAMON_WARNING_POP()

}	// namespace detail

}	// namespace hamon

#endif // HAMON_DEQUE_DETAIL_DEQUE_ITERATOR_HPP
