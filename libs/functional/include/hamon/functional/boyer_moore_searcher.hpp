/**
 *	@file	boyer_moore_searcher.hpp
 *
 *	@brief	boyer_moore_searcher クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_BOYER_MOORE_SEARCHER_HPP
#define HAMON_FUNCTIONAL_BOYER_MOORE_SEARCHER_HPP

#include <hamon/functional/config.hpp>

#if 0//defined(__cpp_lib_boyer_moore_searcher) && (__cpp_lib_boyer_moore_searcher >= 201603L)

namespace hamon
{

using std::boyer_moore_searcher;

}	// namespace hamon

#else

#include <hamon/functional/detail/boyer_moore_searcher_skip_table.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/memory/allocate_shared.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/make_shared.hpp>
#include <hamon/memory/make_unique.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.10.18.3 Class template boyer_moore_searcher[func.search.bm]

template <
	typename RandomAccessIterator1,
	typename Hash = hamon::hash<typename hamon::iterator_traits<RandomAccessIterator1>::value_type>,
	typename BinaryPredicate = hamon::equal_to<>
>
class boyer_moore_searcher
{
private:
	using difference_type = typename hamon::iterator_traits<RandomAccessIterator1>::difference_type;
	using key_type        = typename hamon::iterator_traits<RandomAccessIterator1>::value_type;
	using skip_table_type = hamon::detail::boyer_moore_searcher_skip_table<key_type, difference_type, Hash, BinaryPredicate>;

public:
	HAMON_CXX14_CONSTEXPR
	boyer_moore_searcher(
		RandomAccessIterator1 pat_first,
		RandomAccessIterator1 pat_last,
		Hash hf = Hash(),
		BinaryPredicate pred = BinaryPredicate())
		: m_pat_first(pat_first)
		, m_pat_last(pat_last)
		, m_pred(pred)
		, m_pattern_length(pat_last - pat_first)
		, m_skip_table(hamon::make_shared<skip_table_type>(
			static_cast<hamon::size_t>(m_pattern_length), -1, hf, m_pred))
		, m_suffix(hamon::allocate_shared<difference_type[]>(
			hamon::allocator<difference_type>(), static_cast<hamon::size_t>(m_pattern_length + 1)))
	{
		difference_type i = 0;
		while (pat_first != pat_last)
		{
			m_skip_table->insert(*pat_first, i);
			++pat_first;
			++i;
		}

		this->build_suffix_table(m_pat_first, m_pat_last, m_pred);
	}

	template <typename RandomAccessIterator2>
	HAMON_CXX14_CONSTEXPR
	hamon::pair<RandomAccessIterator2, RandomAccessIterator2>
	operator()(RandomAccessIterator2 first, RandomAccessIterator2 last) const
	{
		static_assert(hamon::is_same<
			hamon::remove_cvref_t<typename hamon::iterator_traits<RandomAccessIterator1>::value_type>,
			hamon::remove_cvref_t<typename hamon::iterator_traits<RandomAccessIterator2>::value_type>>::value,
			"Corpus and Pattern iterators must point to the same type");

		if (first == last)
		{
			return hamon::make_pair(last, last);
		}

		if (m_pat_first == m_pat_last)
		{
			return hamon::make_pair(first, first);
		}

		if (m_pattern_length >(last - first))
		{
			return hamon::make_pair(last, last);
		}

		return this->search(first, last);
	}

private:
	RandomAccessIterator1 m_pat_first;
	RandomAccessIterator1 m_pat_last;
	BinaryPredicate m_pred;
	difference_type m_pattern_length;
	hamon::shared_ptr<skip_table_type> m_skip_table;
	hamon::shared_ptr<difference_type[]> m_suffix;

private:
	HAMON_CXX14_CONSTEXPR
	void build_suffix_table(RandomAccessIterator1 first, RandomAccessIterator1 last, BinaryPredicate pred)
	{
		difference_type const count = last - first;

		if (count == 0)
		{
			return;
		}

		auto scratch = hamon::make_unique<difference_type[]>(static_cast<hamon::size_t>(count));

		this->compute_bm_prefix(first, last, pred, scratch);
		for (difference_type i = 0; i <= count; ++i)
		{
			m_suffix[i] = count - scratch[static_cast<hamon::size_t>(count) - 1];
		}

		using ReverseIter = hamon::reverse_iterator<RandomAccessIterator1>;
		this->compute_bm_prefix(ReverseIter(last), ReverseIter(first), pred, scratch);

		for (difference_type i = 0; i != count; ++i)
		{
			auto const j = count - scratch[static_cast<hamon::size_t>(i)];
			auto const k = i - scratch[static_cast<hamon::size_t>(i)] + 1;

			if (m_suffix[j] > k)
			{
				m_suffix[j] = k;
			}
		}
	}

	template <typename Iterator, typename Container>
	HAMON_CXX14_CONSTEXPR
	void compute_bm_prefix(Iterator first, Iterator last, BinaryPredicate pred, Container& prefix)
	{
		difference_type const count = last - first;

		prefix[0] = 0;
		difference_type k  = 0;

		for (difference_type i = 1; i != count; ++i)
		{
			while (k > 0 && !pred(first[k], first[i]))
			{
				k = prefix[static_cast<hamon::size_t>(k - 1)];
			}

			if (pred(first[k], first[i]))
			{
				++k;
			}

			prefix[static_cast<hamon::size_t>(i)] = k;
		}
	}

	template <typename RandomAccessIterator2>
	HAMON_CXX14_CONSTEXPR
	hamon::pair<RandomAccessIterator2, RandomAccessIterator2>
	search(RandomAccessIterator2 f, RandomAccessIterator2 l) const
	{
		RandomAccessIterator2 current = f;
		RandomAccessIterator2 const last = l - m_pattern_length;
		skip_table_type const& skip_table = *m_skip_table;

		while (current <= last)
		{
			difference_type j = m_pattern_length;
			while (m_pred(m_pat_first[j - 1], current[j - 1]))
			{
				--j;
				if (j == 0)
				{
					return hamon::make_pair(current, current + m_pattern_length);
				}
			}

			difference_type const k = skip_table[current[j - 1]];
			difference_type const m = j - k - 1;
			if (k < j && m > m_suffix[j])
			{
				current += m;
			}
			else
			{
				current += m_suffix[j];
			}
		}

		return hamon::make_pair(l, l);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_BOYER_MOORE_SEARCHER_HPP
