/**
 *	@file	pair_fwd.hpp
 *
 *	@brief	pair の前方宣言
 */

#ifndef HAMON_PAIR_PAIR_FWD_HPP
#define HAMON_PAIR_PAIR_FWD_HPP

#include <hamon/pair/config.hpp>

#if defined(HAMON_USE_STD_PAIR)

#include <utility>

namespace hamon
{

using std::pair;

}	// namespace hamon

#else

namespace hamon
{

template <typename T1, typename T2>
struct pair;

}	// namespace hamon

#endif

#endif // HAMON_PAIR_PAIR_FWD_HPP
