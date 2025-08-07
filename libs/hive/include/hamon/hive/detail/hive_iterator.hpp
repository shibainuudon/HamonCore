/**
 *	@file	hive_iterator.hpp
 *
 *	@brief	hive_iterator の定義
 */

#ifndef HAMON_HIVE_DETAIL_HIVE_ITERATOR_HPP
#define HAMON_HIVE_DETAIL_HIVE_ITERATOR_HPP

#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>

namespace hamon
{

namespace detail
{

template <typename Owner, bool Const>
struct hive_iterator
{
public:
	using iterator_concept  = hamon::bidirectional_iterator_tag;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = typename Owner::value_type;
	using difference_type   = typename Owner::difference_type;
	using pointer           = hamon::conditional_t<Const, typename Owner::const_pointer, typename Owner::pointer>;
	using reference         = hamon::conditional_t<Const, typename Owner::const_reference, typename Owner::reference>;

private:

public:
	HAMON_CXX11_CONSTEXPR
	hive_iterator() HAMON_NOEXCEPT;

	template <bool C, typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	hive_iterator(hive_iterator<Owner, C> const& i) HAMON_NOEXCEPT;

	reference operator*() const;

	pointer operator->() const;

	hive_iterator& operator++();

	hive_iterator operator++(int)
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	hive_iterator& operator--();

	hive_iterator operator--(int)
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator==(hive_iterator const& x, hive_iterator const& y);

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(hive_iterator const& x, hive_iterator const& y)
	{
		return !(x == y);
	}
#endif

	friend HAMON_CXX11_CONSTEXPR bool
	operator<(hive_iterator const& x, hive_iterator const& y);

	friend HAMON_CXX11_CONSTEXPR bool
	operator>(hive_iterator const& x, hive_iterator const& y)
	{
		return y < x;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator<=(hive_iterator const& x, hive_iterator const& y)
	{
		return !(y < x);
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator>=(hive_iterator const& x, hive_iterator const& y)
	{
		return !(x < y);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CXX11_CONSTEXPR hamon::strong_ordering
	operator<=>(hive_iterator const& x, hive_iterator const& y);
#endif
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_HIVE_DETAIL_HIVE_ITERATOR_HPP
