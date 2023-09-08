/**
 *	@file	contiguous_iterator_tag.hpp
 *
 *	@brief	contiguous_iterator_tag の定義
 */

#ifndef HAMON_ITERATOR_CONTIGUOUS_ITERATOR_TAG_HPP
#define HAMON_ITERATOR_CONTIGUOUS_ITERATOR_TAG_HPP

#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <iterator>

namespace hamon
{

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)
using std::contiguous_iterator_tag;
#else
struct contiguous_iterator_tag : public hamon::random_access_iterator_tag {};
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONTIGUOUS_ITERATOR_TAG_HPP
