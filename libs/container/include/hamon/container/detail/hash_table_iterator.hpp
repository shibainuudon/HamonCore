/**
 *	@file	hash_table_iterator.hpp
 *
 *	@brief	hash_table_iterator の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_HASH_TABLE_ITERATOR_HPP
#define HAMON_CONTAINER_DETAIL_HASH_TABLE_ITERATOR_HPP

#include <hamon/container/detail/forward_list_iterator.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct hash_table_iterator_access;

template <typename Bucket, bool Const>
struct hash_table_iterator
{
private:
	using InnerIterator = hamon::conditional_t<Const,
		typename Bucket::const_iterator,
		typename Bucket::iterator>;

public:
	using iterator_category = typename InnerIterator::iterator_category;
	using value_type        = typename InnerIterator::value_type;
	using difference_type   = typename InnerIterator::difference_type;
	using pointer           = typename InnerIterator::pointer;
	using reference         = typename InnerIterator::reference;

private:
	Bucket* m_bucket;
	Bucket* m_bucket_end;
	InnerIterator m_inner_it;

private:
	HAMON_CXX14_CONSTEXPR void
	satisfy() HAMON_NOEXCEPT
	{
		while (m_bucket + 1 < m_bucket_end && m_inner_it == m_bucket->end())
		{
			++m_bucket;
			m_inner_it = m_bucket->begin();
		}
	}

	HAMON_CXX14_CONSTEXPR
	hash_table_iterator(Bucket* bucket, Bucket* bucket_end, InnerIterator it) HAMON_NOEXCEPT
		: m_bucket(bucket)
		, m_bucket_end(bucket_end)
		, m_inner_it(it)
	{
		satisfy();
	}

public:
	HAMON_CXX11_CONSTEXPR
	hash_table_iterator() HAMON_NOEXCEPT
		: m_bucket(nullptr)
		, m_bucket_end(nullptr)
		, m_inner_it()
	{}

	template <bool C, typename = hamon::enable_if_t<C == Const || Const>>
	HAMON_CXX11_CONSTEXPR
	hash_table_iterator(hash_table_iterator<Bucket, C> const& i) HAMON_NOEXCEPT
		: m_bucket(i.m_bucket)
		, m_bucket_end(i.m_bucket_end)
		, m_inner_it(i.m_inner_it)
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	reference operator*() const HAMON_NOEXCEPT
	{
		return *m_inner_it;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	pointer operator->() const HAMON_NOEXCEPT
	{
		return hamon::pointer_traits<pointer>::pointer_to(**this);
	}

	HAMON_CXX14_CONSTEXPR hash_table_iterator&
	operator++() HAMON_NOEXCEPT
	{
		++m_inner_it;
		satisfy();
		return *this;
	}

	HAMON_CXX14_CONSTEXPR hash_table_iterator
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

private:
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator==(hash_table_iterator const& lhs, hash_table_iterator const& rhs) HAMON_NOEXCEPT
	{
		return lhs.m_inner_it == rhs.m_inner_it;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator!=(hash_table_iterator const& lhs, hash_table_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}
#endif

private:
	friend struct hash_table_iterator<Bucket, !Const>;
	friend struct hash_table_iterator_access;
};

struct hash_table_iterator_access
{
	template <typename Bucket>
	static HAMON_CXX11_CONSTEXPR hash_table_iterator<Bucket, false>
	make(Bucket* bucket, Bucket* bucket_end, typename Bucket::iterator it)
	{
		return hash_table_iterator<Bucket, false>{bucket, bucket_end, it};
	}

	template <typename Bucket>
	static HAMON_CXX11_CONSTEXPR hash_table_iterator<Bucket, true>
	make(Bucket const* bucket, Bucket const* bucket_end, typename Bucket::const_iterator it)
	{
		return hash_table_iterator<Bucket, true>{const_cast<Bucket*>(bucket), const_cast<Bucket*>(bucket_end), it};
	}

	template <typename Bucket, bool Const>
	static HAMON_CXX11_CONSTEXPR Bucket*
	bucket(hash_table_iterator<Bucket, Const> it) HAMON_NOEXCEPT
	{
		return it.m_bucket;
	}

	template <typename Bucket, bool Const>
	static HAMON_CXX11_CONSTEXPR Bucket*
	bucket_end(hash_table_iterator<Bucket, Const> it) HAMON_NOEXCEPT
	{
		return it.m_bucket_end;
	}

	template <typename Bucket, bool Const>
	static HAMON_CXX11_CONSTEXPR
	typename hash_table_iterator<Bucket, Const>::InnerIterator
	base(hash_table_iterator<Bucket, Const> it) HAMON_NOEXCEPT
	{
		return it.m_inner_it;
	}
};

template <typename Bucket>
HAMON_CXX11_CONSTEXPR hash_table_iterator<Bucket, false>
const_iterator_cast(hash_table_iterator<Bucket, true> const& x) HAMON_NOEXCEPT
{
	using access = hamon::detail::hash_table_iterator_access;
	return access::make(
		access::bucket(x), access::bucket_end(x),
		hamon::detail::const_iterator_cast(access::base(x)));
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_HASH_TABLE_ITERATOR_HPP
