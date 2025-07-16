/**
 *	@file	vector_iterator.hpp
 *
 *	@brief	vector_iterator の定義
 */

#ifndef HAMON_VECTOR_DETAIL_VECTOR_ITERATOR_HPP
#define HAMON_VECTOR_DETAIL_VECTOR_ITERATOR_HPP

#include <hamon/vector/vector_fwd.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/iterator/contiguous_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename Allocator, bool Const>
struct vector_iterator
{
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;

	friend vector_iterator<T, Allocator, !Const>;
	friend vector<T, Allocator>;

public:
	using iterator_concept  = hamon::contiguous_iterator_tag;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = typename AllocTraits::difference_type;
	using pointer           = hamon::conditional_t<Const, T const*, T*>;
	using reference         = hamon::conditional_t<Const, T const&, T&>;

	HAMON_CXX11_CONSTEXPR
	vector_iterator() HAMON_NOEXCEPT
		: m_ptr()
	{}

private:
	HAMON_CXX11_CONSTEXPR
	vector_iterator(pointer ptr) HAMON_NOEXCEPT
		: m_ptr(ptr)
	{}

public:
	template <bool C, typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	vector_iterator(vector_iterator<T, Allocator, C> const& i) HAMON_NOEXCEPT
		: m_ptr(const_cast<pointer>(i.m_ptr))
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	reference operator*() const HAMON_NOEXCEPT
	{
		return *m_ptr;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	pointer operator->() const HAMON_NOEXCEPT
	{
		return m_ptr;
	}

	HAMON_CXX14_CONSTEXPR vector_iterator&
	operator++() HAMON_NOEXCEPT
	{
		++m_ptr;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR vector_iterator
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR vector_iterator&
	operator--() HAMON_NOEXCEPT
	{
		--m_ptr;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR vector_iterator
	operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR vector_iterator&
	operator+=(difference_type n) HAMON_NOEXCEPT
	{
		m_ptr += n;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR vector_iterator&
	operator-=(difference_type n) HAMON_NOEXCEPT
	{
		m_ptr -= n;
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
	operator[](difference_type n) const HAMON_NOEXCEPT
	{
		return m_ptr[n];
	}

private:
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR vector_iterator
	operator+(vector_iterator const& i, difference_type n) HAMON_NOEXCEPT
	{
		return vector_iterator(i.m_ptr + n);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR vector_iterator
	operator+(difference_type n, vector_iterator const& i) HAMON_NOEXCEPT
	{
		return vector_iterator(i.m_ptr + n);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR vector_iterator
	operator-(vector_iterator const& i, difference_type n) HAMON_NOEXCEPT
	{
		return vector_iterator(i.m_ptr - n);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type
	operator-(vector_iterator const& lhs, vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return static_cast<difference_type>(lhs.m_ptr - rhs.m_ptr);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator==(vector_iterator const& lhs, vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_ptr == rhs.m_ptr;
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR hamon::strong_ordering
	operator<=>(vector_iterator const& lhs, vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_ptr <=> rhs.m_ptr;
	}
#else
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator!=(vector_iterator const& lhs, vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator<(vector_iterator const& lhs, vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_ptr < rhs.m_ptr;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator>(vector_iterator const& lhs, vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return rhs < lhs;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator<=(vector_iterator const& lhs, vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(rhs < lhs);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator>=(vector_iterator const& lhs, vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs < rhs);
	}
#endif
private:
	pointer m_ptr;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_VECTOR_DETAIL_VECTOR_ITERATOR_HPP
