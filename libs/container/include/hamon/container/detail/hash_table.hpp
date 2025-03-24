/**
 *	@file	hash_table.hpp
 *
 *	@brief	hash_table の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_HASH_TABLE_HPP
#define HAMON_CONTAINER_DETAIL_HASH_TABLE_HPP

#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename HashTable, bool Const>
struct hash_table_iterator
{
public:
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = typename HashTable::value_type;
	using difference_type   = typename HashTable::difference_type;
	using pointer           = hamon::conditional_t<Const, value_type const*, value_type*>;
	using reference         = hamon::conditional_t<Const, value_type const&, value_type&>;

	hash_table_iterator() HAMON_NOEXCEPT;

	template <bool C, typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	hash_table_iterator(hash_table_iterator<HashTable, C> const& i);

	reference operator*() const;
	pointer operator->() const;
	hash_table_iterator& operator++();
	hash_table_iterator operator++(int);

private:
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator==(hash_table_iterator const& /*lhs*/, hash_table_iterator const& /*rhs*/) HAMON_NOEXCEPT
	{
		return true;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator!=(hash_table_iterator const& lhs, hash_table_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif

private:
	friend struct hash_table_iterator<HashTable, !Const>;
};

template <typename T>
struct hash_table_node
{
public:
	using value_type = T;
};

template <
	bool Multi,
	typename KeyType,
	typename ValueType,
	typename Hash,
	typename Compare,
	typename SizeType = hamon::size_t,
	typename DifferenceType = hamon::ptrdiff_t
>
struct hash_table
{
public:
	using value_type           = ValueType;
	using key_type             = KeyType;
	using size_type            = SizeType;
	using difference_type      = DifferenceType;
	using node_type            = hash_table_node<value_type>;
	using iterator             = hash_table_iterator<hash_table, false>;
	using const_iterator       = hash_table_iterator<hash_table, true>;
	using local_iterator       = hash_table_iterator<hash_table, false>;
	using const_local_iterator = hash_table_iterator<hash_table, true>;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_HASH_TABLE_HPP
