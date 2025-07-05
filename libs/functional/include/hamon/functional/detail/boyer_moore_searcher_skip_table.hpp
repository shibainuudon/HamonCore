/**
 *	@file	boyer_moore_searcher_skip_table.hpp
 *
 *	@brief	boyer_moore_searcher_skip_table クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_DETAIL_BOYER_MOORE_SEARCHER_SKIP_TABLE_HPP
#define HAMON_FUNCTIONAL_DETAIL_BOYER_MOORE_SEARCHER_SKIP_TABLE_HPP

#include <hamon/algorithm/fill_n.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/limits.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/unordered_map.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Key, typename Value, typename Hash, typename BinaryPredicate,
	bool useArray =
		hamon::is_integral<Key>::value &&
		sizeof(Key) == 1 &&
		hamon::is_same<Hash, hamon::hash<Key>>::value &&
		hamon::is_same<BinaryPredicate, hamon::equal_to<>>::value
>
class boyer_moore_searcher_skip_table;

// General case for BM data searching; use a map
template <typename Key, typename Value, typename Hash, typename BinaryPredicate>
class boyer_moore_searcher_skip_table<Key, Value, Hash, BinaryPredicate, false>
{
private:
	using key_type   = Key;
	using value_type = Value;

	value_type const m_default_value;
	hamon::unordered_map<Key, Value, Hash, BinaryPredicate> m_table;

public:
	HAMON_CXX14_CONSTEXPR explicit
	boyer_moore_searcher_skip_table(hamon::size_t sz, value_type default_value, Hash hash, BinaryPredicate pred)
		: m_default_value(default_value)
		, m_table(sz, hash, pred)
	{}

	HAMON_CXX14_CONSTEXPR
	void insert(key_type const& key, value_type val)
	{
		m_table[key] = val;
	}

	HAMON_CXX14_CONSTEXPR
	value_type operator[](key_type const& key) const
	{
		auto it = m_table.find(key);
		return it == m_table.end() ? m_default_value : it->second;
	}
};

// Special case small numeric values; use an array
template <typename Key, typename Value, typename Hash, typename BinaryPredicate>
class boyer_moore_searcher_skip_table<Key, Value, Hash, BinaryPredicate, true>
{
private:
	using key_type   = Key;
	using value_type = Value;

	using unsigned_key_type = hamon::make_unsigned_t<key_type>;
	static_assert(hamon::numeric_limits<unsigned_key_type>::max() < 256, "");

	hamon::array<value_type, 256> m_table;

public:
	HAMON_CXX14_CONSTEXPR explicit
	boyer_moore_searcher_skip_table(hamon::size_t, value_type default_value, Hash, BinaryPredicate)
	{
		hamon::fill_n(m_table.data(), m_table.size(), default_value);
	}

	HAMON_CXX14_CONSTEXPR
	void insert(key_type key, value_type val)
	{
		m_table[static_cast<unsigned_key_type>(key)] = val;
	}

	HAMON_CXX14_CONSTEXPR
	value_type operator[](key_type key) const
	{
		return m_table[static_cast<unsigned_key_type>(key)];
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_DETAIL_BOYER_MOORE_SEARCHER_SKIP_TABLE_HPP
