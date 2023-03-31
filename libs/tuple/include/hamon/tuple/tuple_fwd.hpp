/**
 *	@file	tuple_fwd.hpp
 *
 *	@brief	tuple の前方宣言
 */

#ifndef HAMON_TUPLE_FWD_TUPLE_FWD_HPP
#define HAMON_TUPLE_FWD_TUPLE_FWD_HPP

#include <hamon/tuple/config.hpp>

namespace hamon
{

#if defined(HAMON_USE_STD_TUPLE)

using std::tuple;

#else

template <typename... Types>
class tuple;

#endif

}	// namespace hamon

#endif // HAMON_TUPLE_FWD_TUPLE_FWD_HPP
