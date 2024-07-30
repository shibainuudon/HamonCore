/**
 *	@file	default_searcher.hpp
 *
 *	@brief	default_searcher クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_DEFAULT_SEARCHER_HPP
#define HAMON_FUNCTIONAL_DEFAULT_SEARCHER_HPP

#include <hamon/functional/config.hpp>

#if defined(__cpp_lib_constexpr_functional) && (__cpp_lib_constexpr_functional >= 201907L)	// P1032R1

namespace hamon
{

using std::default_searcher;

}	// namespace hamon

#else

#include <hamon/algorithm/search.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/pair.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.10.18.2 Class template default_searcher[func.search.default]

template <typename ForwardIterator1, typename BinaryPredicate = hamon::equal_to<>>
class default_searcher
{
public:
	HAMON_CXX14_CONSTEXPR
	default_searcher(
		ForwardIterator1 pat_first, ForwardIterator1 pat_last,
		BinaryPredicate pred = BinaryPredicate())
		// [func.search.default]/1
		: m_pat_first(pat_first)
		, m_pat_last(pat_last)
		, m_pred(pred)
	{}

	template <typename ForwardIterator2>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	hamon::pair<ForwardIterator2, ForwardIterator2>
	operator()(ForwardIterator2 first, ForwardIterator2 last) const
	{
		// [func.search.default]/3
		auto const i = hamon::search(first, last, m_pat_first, m_pat_last, m_pred);
		auto const j = ((i == last) ? last : hamon::next(i, hamon::distance(m_pat_first, m_pat_last)));
		return {i, j};
	}

private:
	HAMON_NO_UNIQUE_ADDRESS ForwardIterator1 m_pat_first;
	HAMON_NO_UNIQUE_ADDRESS ForwardIterator1 m_pat_last;
	HAMON_NO_UNIQUE_ADDRESS BinaryPredicate  m_pred;
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_DEFAULT_SEARCHER_HPP
