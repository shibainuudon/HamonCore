/**
 *	@file	hash_table_bucket.hpp
 *
 *	@brief	hash_table_bucket の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_HASH_TABLE_BUCKET_HPP
#define HAMON_CONTAINER_DETAIL_HASH_TABLE_BUCKET_HPP

#include <hamon/container/detail/forward_list_impl.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename Allocator>
struct hash_table_bucket : public hamon::detail::forward_list_impl<T, Allocator>
{
	using base_type      = hamon::detail::forward_list_impl<T, Allocator>;
	using iterator       = typename base_type::iterator;
	using const_iterator = typename base_type::const_iterator;
	using size_type      = typename base_type::size_type;

	HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<const_iterator>
	distance() const
	{
		return hamon::distance(this->begin(), this->end());
	}

	HAMON_CXX14_CONSTEXPR const_iterator
	previous(const_iterator position) const
	{
		auto it = this->before_begin();
		while (it != this->end())
		{
			auto j = it++;
			if (it == position)
			{
				return j;
			}
		}
		return it;
	}

	template <typename Pred, typename K>
	HAMON_CXX14_CONSTEXPR iterator
	find(Pred const& key_eq, K const& k)
	{
		for (auto it = this->begin(); it != this->end(); ++it)
		{
			if (key_eq(*it, k))
			{
				return it;
			}
		}
		return this->end();
	}

	template <typename Pred, typename K>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, iterator>
	equal_range(Pred const& key_eq, K const& k)
	{
		auto it1 = this->find(key_eq, k);
		if (it1 == this->end())
		{
			return {it1, it1};
		}

		for (auto it2 = hamon::next(it1); it2 != this->end(); ++it2)
		{
			if (!key_eq(*it2, k))
			{
				return {it1, it2};
			}
		}

		return {it1, this->end()};
	}

	template <typename Pred, typename K>
	HAMON_CXX14_CONSTEXPR size_type
	count(Pred const& key_eq, K const& k)
	{
		auto rg = this->equal_range(key_eq, k);
		return static_cast<size_type>(hamon::distance(rg.first, rg.second));
	}

	template <typename Pred, typename K>
	HAMON_CXX14_CONSTEXPR hamon::pair<iterator, bool>
	find_insert_position(bool multi, Pred const& key_eq, K const& k)
	{
		if (!multi)
		{
			auto it = this->find(key_eq, k);
			if (it != this->end())
			{
				return {it, false};
			}
			return {this->before_begin(), true};
		}

		auto prev = this->before_begin();
		auto curr = this->begin();
		for (; curr != this->end(); ++prev, ++curr)
		{
			if (key_eq(*curr, k))
			{
				return {prev, true};
			}
		}
		return {this->before_begin(), true};
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_HASH_TABLE_BUCKET_HPP
