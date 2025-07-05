/**
 *	@file	boyer_moore_horspool_searcher.hpp
 *
 *	@brief	boyer_moore_horspool_searcher クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_BOYER_MOORE_HORSPOOL_SEARCHER_HPP
#define HAMON_FUNCTIONAL_BOYER_MOORE_HORSPOOL_SEARCHER_HPP

#include <hamon/functional/config.hpp>

#if 0//defined(__cpp_lib_boyer_moore_searcher) && (__cpp_lib_boyer_moore_searcher >= 201603L)

namespace hamon
{

using std::boyer_moore_horspool_searcher;

}	// namespace hamon

#else

#include <hamon/functional/detail/boyer_moore_searcher_skip_table.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/memory/make_shared.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.10.18.4 Class template boyer_moore_horspool_searcher[func.search.bmh]

template <
	typename RandomAccessIterator1,
	typename Hash = hamon::hash<typename hamon::iterator_traits<RandomAccessIterator1>::value_type>,
	typename BinaryPredicate = hamon::equal_to<>
>
class boyer_moore_horspool_searcher
{
private:
	using difference_type = typename hamon::iterator_traits<RandomAccessIterator1>::difference_type;
	using key_type        = typename hamon::iterator_traits<RandomAccessIterator1>::value_type;
	using skip_table_type = hamon::detail::boyer_moore_searcher_skip_table<key_type, difference_type, Hash, BinaryPredicate>;

public:
	HAMON_CXX14_CONSTEXPR
	boyer_moore_horspool_searcher(
		RandomAccessIterator1 pat_first,
		RandomAccessIterator1 pat_last,
		Hash hf = Hash(),
		BinaryPredicate pred = BinaryPredicate())
		: m_pat_first(pat_first)
		, m_pat_last(pat_last)
		, m_pred(pred)
		, m_pattern_length(pat_last - pat_first)
		, m_skip_table(hamon::make_shared<skip_table_type>(
			static_cast<hamon::size_t>(m_pattern_length), m_pattern_length, hf, m_pred))
	{
		if (pat_first == pat_last)
		{
			return;
		}

		--pat_last;
		difference_type i = 0;
		while (pat_first != pat_last)
		{
			m_skip_table->insert(*pat_first, m_pattern_length - 1 - i);
			++pat_first;
			++i;
		}
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

		if (m_pattern_length > last - first)
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

private:
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

			current += skip_table[current[m_pattern_length - 1]];
		}

		return hamon::make_pair(l, l);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_BOYER_MOORE_HORSPOOL_SEARCHER_HPP
