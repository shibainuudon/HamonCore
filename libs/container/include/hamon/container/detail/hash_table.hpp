/**
 *	@file	hash_table.hpp
 *
 *	@brief	hash_table の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_HASH_TABLE_HPP
#define HAMON_CONTAINER_DETAIL_HASH_TABLE_HPP

#include <hamon/container/detail/hash_table_iterator.hpp>
#include <hamon/container/detail/hash_table_bucket.hpp>

#include <hamon/algorithm/max.hpp>
#include <hamon/bit/bit_ceil.hpp>
#include <hamon/bit/has_single_bit.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/make_move_iterator.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/limits/numeric_limits.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace detail
{

template <typename Hash, typename Key>
using nothrow_hash = hamon::bool_constant<noexcept(
	static_cast<hamon::size_t>(hamon::declval<Hash const&>()(hamon::declval<Key const&>())))>;

template <typename Pred, typename Lhs, typename Rhs>
using nothrow_compare = hamon::bool_constant<noexcept(
	static_cast<bool>(hamon::declval<Pred const&>()(hamon::declval<Lhs const&>(), hamon::declval<Rhs const&>())))>;

template <
	typename KeyType,
	typename ValueType,
	typename Hash,
	typename Pred,
	typename Allocator,
	bool Multi
>
struct hash_table
{
private:
	using Bucket = hamon::detail::hash_table_bucket<ValueType, Allocator>;
	using Node   = typename Bucket::node_type;

	using AllocTraits = hamon::allocator_traits<Allocator>;
	using BucketAllocator   = typename AllocTraits::template rebind_alloc<Bucket>;
	using BucketAllocTraits = typename AllocTraits::template rebind_traits<Bucket>;
	using NodeAllocator     = typename AllocTraits::template rebind_alloc<Node>;
	using NodeAllocTraits   = typename AllocTraits::template rebind_traits<Node>;

public:
	using key_type             = KeyType;
	using value_type           = ValueType;
	using hasher               = Hash;
	using key_equal            = Pred;
	using size_type            = typename AllocTraits::size_type;
	using difference_type      = typename AllocTraits::difference_type;
	using node_type            = Node;
	using iterator             = hash_table_iterator<Bucket, false>;
	using const_iterator       = hash_table_iterator<Bucket, true>;
	using local_iterator       = typename Bucket::iterator;
	using const_local_iterator = typename Bucket::const_iterator;

private:
	HAMON_NO_UNIQUE_ADDRESS hasher m_hash;
	HAMON_NO_UNIQUE_ADDRESS key_equal m_key_eq;
	size_type m_size;
	size_type m_bucket_count;
	Bucket* m_buckets;
	float m_max_load_factor;

	static constexpr size_type MinBucketCount() { return 1; }

public:
	HAMON_CXX14_CONSTEXPR
	hash_table(
		hasher const& hf,
		key_equal const& eql)
		: m_hash(hf)
		, m_key_eq(eql)
		, m_size(0)
		, m_bucket_count(0)
		, m_buckets(nullptr)
		, m_max_load_factor(1.0f)
	{}

	HAMON_CXX14_CONSTEXPR
	hash_table(
		size_type n,
		hasher const& hf,
		key_equal const& eql,
		Allocator const& a)
		: m_hash(hf)
		, m_key_eq(eql)
		, m_size(0)
		, m_bucket_count(0)
		, m_buckets(nullptr)
		, m_max_load_factor(1.0f)
	{
		this->create_buckets(a, hamon::max(n, MinBucketCount()));
	}

	hash_table(hash_table const&) = delete;
	hash_table& operator=(hash_table const&) = delete;

	HAMON_CXX14_CONSTEXPR
	hash_table(hash_table&& x) HAMON_NOEXCEPT
		: m_hash(hamon::move(x.m_hash))
		, m_key_eq(hamon::move(x.m_key_eq))
		, m_size(hamon::exchange(x.m_size, size_type{}))
		, m_bucket_count(hamon::exchange(x.m_bucket_count, size_type{}))
		, m_buckets(hamon::exchange(x.m_buckets, nullptr))
		, m_max_load_factor(hamon::move(x.m_max_load_factor))
	{}

	HAMON_CXX14_CONSTEXPR
	hash_table& operator=(hash_table&& x) HAMON_NOEXCEPT
	{
		hash_table(hamon::move(x)).swap(*this);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR void
	swap(hash_table& x) HAMON_NOEXCEPT
	{
		hamon::swap(m_hash,            x.m_hash);
		hamon::swap(m_key_eq,          x.m_key_eq);
		hamon::swap(m_size,            x.m_size);
		hamon::swap(m_bucket_count,    x.m_bucket_count);
		hamon::swap(m_buckets,         x.m_buckets);
		hamon::swap(m_max_load_factor, x.m_max_load_factor);
	}

	HAMON_CXX14_CONSTEXPR void
	copy_from(Allocator& alloc, hash_table const& x)
	{
		this->m_hash = x.m_hash;
		this->m_key_eq = x.m_key_eq;
		this->m_max_load_factor = x.m_max_load_factor;
		this->insert_range(alloc, x.begin(), x.end());
	}

	HAMON_CXX14_CONSTEXPR void
	move_from(Allocator& alloc, hash_table const& x)
	{
		this->m_hash = hamon::move(x.m_hash);
		this->m_key_eq = hamon::move(x.m_key_eq);
		this->m_max_load_factor = hamon::move(x.m_max_load_factor);
		this->insert_range(alloc, hamon::make_move_iterator(x.begin()), hamon::make_move_iterator(x.end()));
	}

	HAMON_CXX14_CONSTEXPR void
	create_buckets(Allocator const& alloc, size_type n)
	{
		HAMON_ASSERT(m_buckets == nullptr);
		HAMON_ASSERT(m_bucket_count == 0u);
		HAMON_ASSERT(n != 0u);

		n = hamon::bit_ceil(n);

		BucketAllocator a(alloc);
		m_buckets = BucketAllocTraits::allocate(a, n);
		m_bucket_count = n;

		for (size_type i = 0; i < m_bucket_count; ++i)
		{
			BucketAllocTraits::construct(a, m_buckets + i);
		}
	}

	HAMON_CXX14_CONSTEXPR void
	destroy_buckets(Allocator& alloc) HAMON_NOEXCEPT
	{
		if (m_buckets != nullptr)
		{
			BucketAllocator bucket_alloc(alloc);

			for (size_type i = 0; i < m_bucket_count; ++i)
			{
				BucketAllocTraits::destroy(bucket_alloc, m_buckets + i);
			}

			BucketAllocTraits::deallocate(bucket_alloc, m_buckets, m_bucket_count);
			m_buckets = nullptr;
			m_bucket_count = 0;
		}
	}

	HAMON_CXX14_CONSTEXPR void
	clear(Allocator& alloc) HAMON_NOEXCEPT
	{
		if (m_buckets != nullptr)
		{
			for (size_type i = 0; i < m_bucket_count; ++i)
			{
				m_buckets[i].clear(alloc);
			}
		}
		m_size = 0;
	}

private:
	HAMON_CXX11_CONSTEXPR iterator
	make_iterator(Bucket* bucket, local_iterator it) const HAMON_NOEXCEPT
	{
		using access = hamon::detail::hash_table_iterator_access;
		return access::make(bucket, m_buckets + m_bucket_count, it);
	}

	HAMON_CXX11_CONSTEXPR Bucket*
	bucket(size_type n) const
	{
		return (HAMON_ASSERT(n < m_bucket_count), &m_buckets[n]);
	}

	HAMON_CXX11_CONSTEXPR Bucket*
	front() const HAMON_NOEXCEPT
	{
		return this->bucket(0);
	}

	HAMON_CXX11_CONSTEXPR Bucket*
	back() const HAMON_NOEXCEPT
	{
		return this->bucket(m_bucket_count - 1);
	}

public:
	HAMON_CXX11_CONSTEXPR iterator
	begin() const HAMON_NOEXCEPT
	{
		return make_iterator(front(), front()->begin());
	}

	HAMON_CXX11_CONSTEXPR iterator
	end() const HAMON_NOEXCEPT
	{
		return make_iterator(back(), back()->end());
	}

	HAMON_CXX11_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		return m_size;
	}

	HAMON_CXX11_CONSTEXPR size_type
	max_size(Allocator const& alloc) const HAMON_NOEXCEPT
	{
		return front()->max_size(alloc);
	}

	template <typename K, typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	try_emplace(Allocator& alloc, K const& k, Args&&... args)
	{
		auto bucket = this->get_bucket(k);
		auto ret = bucket->find_insert_position(Multi, m_key_eq, k);
		if (ret.second)
		{
			auto it = bucket->insert_after(alloc, ret.first, hamon::forward<Args>(args)...);
			++m_size;
			if (this->load_factor() <= this->max_load_factor())
			{
				return {make_iterator(bucket, it), true};
			}

			using access = hamon::detail::forward_list_iterator_access;

			// rehashによってイテレータが無効になるので、ポインタに変換しておく(ポインタは無効にならない)
			auto p = access::ptr(it);

			auto const new_bucket_count =
				static_cast<size_type>(hamon::max(
					static_cast<float>(this->bucket_count()) * 2.0f,
					static_cast<float>(this->size()) / this->max_load_factor()
				));
			this->rehash(alloc, new_bucket_count);

			it = access::make<decltype(it)>(p);
			bucket = this->get_bucket(*it);
			return {make_iterator(bucket, it), true};
		}
		else
		{
			return {make_iterator(bucket, ret.first), false};
		}
	}

private:
	template <typename Arg0, typename... Args,
		typename = hamon::enable_if_t<
			hamon::disjunction<
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<value_type>>,
				hamon::is_same<hamon::remove_cvref_t<Arg0>, hamon::remove_cvref_t<key_type>>
			>::value>>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_impl(hamon::detail::overload_priority<1>,
		Allocator& alloc, Arg0&& arg0, Args&&... args)
	{
		return this->try_emplace(alloc, arg0, hamon::forward<Arg0>(arg0), hamon::forward<Args>(args)...);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace_impl(hamon::detail::overload_priority<0>,
		Allocator& alloc, Args&&... args)
	{
		auto new_node = Bucket::construct_node(alloc, hamon::forward<Args>(args)...);
		auto r = this->try_emplace(alloc, new_node->value(), new_node);
		if (!r.second)
		{
			Bucket::destroy_node(alloc, new_node);
		}
		return r;
	}

public:
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	emplace(Allocator& alloc, Args&&... args)
	{
		return emplace_impl(hamon::detail::overload_priority<1>{},
			alloc, hamon::forward<Args>(args)...);
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	insert_range(Allocator& alloc, Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			this->emplace(alloc, *first);
		}
	}

	HAMON_CXX14_CONSTEXPR node_type*
	extract(const_iterator position) HAMON_NOEXCEPT
	{
		using access = hamon::detail::hash_table_iterator_access;
		auto& bucket = *access::bucket(position);
		auto it = bucket.previous(access::base(position));
		if (it == bucket.end())
		{
			return nullptr;
		}

		auto ret = bucket.extract_after(it);
		--m_size;
		return ret;
	}

	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	insert_node(Allocator& alloc, node_type* node)
	{
		if (node == nullptr)
		{
			return {this->end(), false};
		}

		return this->try_emplace(alloc, node->value(), node);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(Allocator& alloc, const_iterator position) HAMON_NOEXCEPT_IF(
		hamon::detail::nothrow_compare<key_equal, key_type, key_type>::value)
	{
		using access = hamon::detail::hash_table_iterator_access;
		auto bucket = access::bucket(position);
		auto it = bucket->previous(access::base(position));
		if (it == bucket->end())
		{
			return this->end();
		}

		auto ret = bucket->erase_after(alloc, it);
		--m_size;
		return make_iterator(bucket, ret);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase_range(Allocator& alloc, const_iterator first, const_iterator last) HAMON_NOEXCEPT_IF(
		hamon::detail::nothrow_compare<key_equal, key_type, key_type>::value)
	{
		while (first != last)
		{
			first = this->erase(alloc, first);
		}
		return hamon::detail::const_iterator_cast(first);
	}

	template <typename H2, typename P2, bool M2>
	HAMON_CXX14_CONSTEXPR void
	merge(Allocator& alloc, hash_table<KeyType, ValueType, H2, P2, Allocator, M2>& source)
	{
		for (auto it = source.begin(); it != source.end(); )
		{
			auto next = hamon::next(it);
			auto node = source.extract(it);
			auto r = this->insert_node(alloc, node);
			if (!r.second)
			{
				source.insert_node(alloc, node);
			}
			it = next;
		}
	}

	HAMON_CXX11_CONSTEXPR hasher const&
	hash_function() const
	{
		return m_hash;
	}

	HAMON_CXX11_CONSTEXPR key_equal const&
	key_eq() const
	{
		return m_key_eq;
	}

	template <typename K>
	HAMON_CXX14_CONSTEXPR iterator
	find(K const& k) const HAMON_NOEXCEPT_IF(
		hamon::detail::nothrow_hash<hasher, K>::value &&
		hamon::detail::nothrow_compare<key_equal, key_type, K>::value)
	{
		auto bucket = this->get_bucket(k);
		auto it = bucket->find(m_key_eq, k);
		if (it == bucket->end())
		{
			return this->end();
		}
		return make_iterator(bucket, it);
	}

	template <typename K>
	HAMON_CXX14_CONSTEXPR size_type
	count(K const& k) const HAMON_NOEXCEPT_IF(
		hamon::detail::nothrow_hash<hasher, K>::value &&
		hamon::detail::nothrow_compare<key_equal, key_type, K>::value)
	{
		return this->get_bucket(k)->count(m_key_eq, k);
	}

	template <typename K>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(K const& k) const HAMON_NOEXCEPT_IF(
		hamon::detail::nothrow_hash<hasher, K>::value &&
		hamon::detail::nothrow_compare<key_equal, key_type, K>::value)
	{
		auto bucket = this->get_bucket(k);
		auto ret = bucket->equal_range(m_key_eq, k);
		if (ret.first == ret.second)
		{
			return { this->end(), this->end() };
		}
		return { make_iterator(bucket, ret.first), make_iterator(bucket, ret.second) };
	}

	HAMON_CXX11_CONSTEXPR size_type
	bucket_count() const HAMON_NOEXCEPT
	{
		return m_bucket_count;
	}

	HAMON_CXX11_CONSTEXPR size_type
	max_bucket_count() const HAMON_NOEXCEPT
	{
		return (hamon::numeric_limits<size_type>::max() >> 1) + 1;
	}

	HAMON_CXX11_CONSTEXPR size_type
	bucket_size(size_type n) const
	{
		return static_cast<size_type>(this->bucket(n)->distance());
	}

	template <typename K>
	HAMON_CXX11_CONSTEXPR size_type
	bucket_index(K const& k) const
		HAMON_NOEXCEPT_IF(hamon::detail::nothrow_hash<hasher, K>::value)
	{
		return (HAMON_ASSERT(hamon::has_single_bit(this->bucket_count())),
			(m_hash(k) & (this->bucket_count() - 1)));
	}

	template <typename K>
	HAMON_CXX11_CONSTEXPR Bucket*
	get_bucket(K const& k) const
	{
		return this->bucket(this->bucket_index(k));
	}

	HAMON_CXX11_CONSTEXPR local_iterator
	begin(size_type n) const
	{
		return this->bucket(n)->begin();
	}

	HAMON_CXX11_CONSTEXPR local_iterator
	end(size_type n) const
	{
		return this->bucket(n)->end();
	}

	HAMON_CXX11_CONSTEXPR float
	load_factor() const HAMON_NOEXCEPT
	{
		return static_cast<float>(this->size()) /
			static_cast<float>(this->bucket_count());
	}

	HAMON_CXX11_CONSTEXPR float
	max_load_factor() const HAMON_NOEXCEPT
	{
		return m_max_load_factor;
	}

	HAMON_CXX14_CONSTEXPR void
	max_load_factor(float z)
	{
		if (this->load_factor() <= z)
		{
			m_max_load_factor = z;
		}
	}

	HAMON_CXX14_CONSTEXPR void
	rehash(Allocator& alloc, size_type n)
	{
		if (n <= m_bucket_count)
		{
			return;
		}

		hash_table tmp(n, this->hash_function(), this->key_eq(), alloc);	// may throw
		tmp.m_max_load_factor = this->m_max_load_factor;
		tmp.merge(alloc, *this);
		tmp.swap(*this);
		tmp.destroy_buckets(alloc);
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_HASH_TABLE_HPP
