/**
 *	@file	make_index_sequence.hpp
 *
 *	@brief	make_index_sequence を定義
 */

#ifndef HAMON_UTILITY_MAKE_INDEX_SEQUENCE_HPP
#define HAMON_UTILITY_MAKE_INDEX_SEQUENCE_HPP

#include <hamon/utility/index_sequence.hpp>
#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace hamon
{

using std::make_index_sequence;

}	// namespace hamon

#else

#include <hamon/utility/make_integer_sequence.hpp>
#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

template <hamon::size_t N>
using make_index_sequence = hamon::make_integer_sequence<hamon::size_t, N>;

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_MAKE_INDEX_SEQUENCE_HPP
