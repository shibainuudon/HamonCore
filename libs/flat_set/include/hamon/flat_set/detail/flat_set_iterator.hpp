/**
 *	@file	flat_set_iterator.hpp
 *
 *	@brief	flat_set_iterator の定義
 */

#ifndef HAMON_FLAT_SET_DETAIL_FLAT_SET_ITERATOR_HPP
#define HAMON_FLAT_SET_DETAIL_FLAT_SET_ITERATOR_HPP

#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Owner, typename KeyContainer>
struct flat_set_iterator
{
private:
	friend Owner;

	using base_iterator = typename KeyContainer::const_iterator;

	base_iterator m_base;

public:
	using iterator_concept  = hamon::random_access_iterator_tag;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = typename base_iterator::value_type;
	using difference_type   = typename base_iterator::difference_type;
	using pointer           = typename base_iterator::pointer;
	using reference         = typename base_iterator::reference;

private:
	explicit HAMON_CXX11_CONSTEXPR
	flat_set_iterator(base_iterator it)
		: m_base(hamon::move(it))
	{}

	HAMON_CXX11_CONSTEXPR base_iterator base() const
		noexcept(noexcept(base_iterator(m_base)))
	{
		return m_base;
	}

public:
	flat_set_iterator() = default;

	HAMON_CXX11_CONSTEXPR reference
	operator*() const
	{
		return *m_base;
	}

	HAMON_CXX11_CONSTEXPR pointer
	operator->() const
	{
		return hamon::pointer_traits<pointer>::pointer_to(**this);
	}

	HAMON_CXX14_CONSTEXPR flat_set_iterator&
	operator++()
	{
		++m_base;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR flat_set_iterator
	operator++(int)
	{
		flat_set_iterator tmp(*this);
		++*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR flat_set_iterator&
	operator--()
	{
		--m_base;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR flat_set_iterator
	operator--(int)
	{
		flat_set_iterator tmp(*this);
		--*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR flat_set_iterator&
	operator+=(difference_type x)
	{
		m_base += x;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR flat_set_iterator&
	operator-=(difference_type x)
	{
		m_base -= x;
		return *this;
	}

	HAMON_CXX11_CONSTEXPR reference
	operator[](difference_type n) const
	{
		return *(*this + n);
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator==(flat_set_iterator const& x, flat_set_iterator const& y)
	{
		return x.m_base == y.m_base;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(flat_set_iterator const& x, flat_set_iterator const& y)
	{
		return !(x == y);
	}
#endif

	friend HAMON_CXX11_CONSTEXPR bool
	operator<(flat_set_iterator const& x, flat_set_iterator const& y)
	{
		return x.m_base < y.m_base;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator>(flat_set_iterator const& x, flat_set_iterator const& y)
	{
		return y < x;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator<=(flat_set_iterator const& x, flat_set_iterator const& y)
	{
		return !(y < x);
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator>=(flat_set_iterator const& x, flat_set_iterator const& y)
	{
		return !(x < y);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CXX11_CONSTEXPR auto
	operator<=>(flat_set_iterator const& x, flat_set_iterator const& y)
		requires hamon::three_way_comparable<base_iterator>
	{
		return x.m_base <=> y.m_base;
	}
#endif

	friend HAMON_CXX14_CONSTEXPR flat_set_iterator
	operator+(flat_set_iterator const& i, difference_type n)
	{
		auto tmp = i;
		tmp += n;
		return tmp;
	}

	friend HAMON_CXX11_CONSTEXPR flat_set_iterator
	operator+(difference_type n, flat_set_iterator const& i)
	{
		return i + n;
	}

	friend HAMON_CXX14_CONSTEXPR flat_set_iterator
	operator-(flat_set_iterator const& i, difference_type n)
	{
		auto tmp = i;
		tmp -= n;
		return tmp;
	}

	friend HAMON_CXX11_CONSTEXPR difference_type
	operator-(flat_set_iterator const& x, flat_set_iterator const& y)
	{
		return x.m_base - y.m_base;
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FLAT_SET_DETAIL_FLAT_SET_ITERATOR_HPP
