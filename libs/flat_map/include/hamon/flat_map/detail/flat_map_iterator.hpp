/**
 *	@file	flat_map_iterator.hpp
 *
 *	@brief	flat_map_iterator の定義
 */

#ifndef HAMON_FLAT_MAP_DETAIL_FLAT_MAP_ITERATOR_HPP
#define HAMON_FLAT_MAP_DETAIL_FLAT_MAP_ITERATOR_HPP

#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Owner, typename KeyContainer, typename MappedContainer, bool Const>
struct flat_map_iterator
{
private:
	using key_iterator = typename KeyContainer::const_iterator;

	using mapped_iterator = hamon::conditional_t<
		Const,
		typename MappedContainer::const_iterator,
		typename MappedContainer::iterator>;

	using reference = hamon::conditional_t<
		Const,
		typename Owner::const_reference,
		typename Owner::reference>;

	struct arrow_proxy
	{
		reference m_ref;
		HAMON_CXX14_CONSTEXPR reference* operator->() { return hamon::addressof(m_ref); }
	};

	key_iterator m_key_iter;
	mapped_iterator m_mapped_iter;

	friend Owner;

	template <typename, typename, typename, bool>
	friend struct flat_map_iterator;

public:
	using iterator_concept = hamon::random_access_iterator_tag;
	// `flat_map_iterator` only satisfy "Cpp17InputIterator" named requirements, because
	// its `reference` is not a reference type.
	// However, to avoid surprising runtime behaviour when it is used with the
	// Cpp17 algorithms or operations, iterator_category is set to random_access_iterator_tag.
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = typename Owner::value_type;
	using difference_type   = typename Owner::difference_type;

	flat_map_iterator() = default;

	template <bool C, typename = hamon::enable_if_t<C == Const || Const>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to_t<typename KeyContainer::iterator, key_iterator>,
			hamon::convertible_to_t<typename MappedContainer::iterator, mapped_iterator>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	flat_map_iterator(flat_map_iterator<Owner, KeyContainer, MappedContainer, C> i)
		: m_key_iter(hamon::move(i.m_key_iter))
		, m_mapped_iter(hamon::move(i.m_mapped_iter))
	{}

	HAMON_CXX11_CONSTEXPR
	flat_map_iterator(key_iterator key_iter, mapped_iterator mapped_iter)
		: m_key_iter(hamon::move(key_iter))
		, m_mapped_iter(hamon::move(mapped_iter))
	{}

	HAMON_CXX11_CONSTEXPR reference
	operator*() const
	{
		return reference(*m_key_iter, *m_mapped_iter);
	}

	HAMON_CXX11_CONSTEXPR arrow_proxy
	operator->() const
	{
		return arrow_proxy{**this};
	}

	HAMON_CXX14_CONSTEXPR flat_map_iterator&
	operator++()
	{
		++m_key_iter;
		++m_mapped_iter;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR flat_map_iterator
	operator++(int)
	{
		flat_map_iterator tmp(*this);
		++*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR flat_map_iterator&
	operator--()
	{
		--m_key_iter;
		--m_mapped_iter;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR flat_map_iterator
	operator--(int)
	{
		flat_map_iterator tmp(*this);
		--*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR flat_map_iterator&
	operator+=(difference_type x)
	{
		m_key_iter += x;
		m_mapped_iter += x;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR flat_map_iterator&
	operator-=(difference_type x)
	{
		m_key_iter -= x;
		m_mapped_iter -= x;
		return *this;
	}

	HAMON_CXX11_CONSTEXPR reference
	operator[](difference_type n) const
	{
		return *(*this + n);
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator==(flat_map_iterator const& x, flat_map_iterator const& y)
	{
		return x.m_key_iter == y.m_key_iter;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(flat_map_iterator const& x, flat_map_iterator const& y)
	{
		return !(x == y);
	}
#endif

	friend HAMON_CXX11_CONSTEXPR bool
	operator<(flat_map_iterator const& x, flat_map_iterator const& y)
	{
		return x.m_key_iter < y.m_key_iter;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator>(flat_map_iterator const& x, flat_map_iterator const& y)
	{
		return y < x;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator<=(flat_map_iterator const& x, flat_map_iterator const& y)
	{
		return !(y < x);
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator>=(flat_map_iterator const& x, flat_map_iterator const& y)
	{
		return !(x < y);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CXX11_CONSTEXPR auto
	operator<=>(flat_map_iterator const& x, flat_map_iterator const& y)
		requires hamon::three_way_comparable<key_iterator>
	{
		return x.m_key_iter <=> y.m_key_iter;
	}
#endif

	friend HAMON_CXX14_CONSTEXPR flat_map_iterator
	operator+(flat_map_iterator const& i, difference_type n)
	{
		auto tmp = i;
		tmp += n;
		return tmp;
	}

	friend HAMON_CXX11_CONSTEXPR flat_map_iterator
	operator+(difference_type n, flat_map_iterator const& i)
	{
		return i + n;
	}

	friend HAMON_CXX14_CONSTEXPR flat_map_iterator
	operator-(flat_map_iterator const& i, difference_type n)
	{
		auto tmp = i;
		tmp -= n;
		return tmp;
	}

	friend HAMON_CXX11_CONSTEXPR difference_type
	operator-(flat_map_iterator const& x, flat_map_iterator const& y)
	{
		return difference_type(x.m_key_iter - y.m_key_iter);
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FLAT_MAP_DETAIL_FLAT_MAP_ITERATOR_HPP
