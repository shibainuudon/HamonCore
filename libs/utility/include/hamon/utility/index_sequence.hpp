/**
 *	@file	index_sequence.hpp
 *
 *	@brief	index_sequence を定義
 */

#ifndef HAMON_UTILITY_INDEX_SEQUENCE_HPP
#define HAMON_UTILITY_INDEX_SEQUENCE_HPP

#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace hamon
{

using std::index_sequence;

}	// namespace hamon

#else

#include <hamon/utility/integer_sequence.hpp>
#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

template <hamon::size_t... I>
using index_sequence = hamon::integer_sequence<hamon::size_t, I...>;

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_INDEX_SEQUENCE_HPP
