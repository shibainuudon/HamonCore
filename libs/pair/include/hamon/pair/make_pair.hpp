/**
 *	@file	make_pair.hpp
 *
 *	@brief	make_pair の定義
 */

#ifndef HAMON_PAIR_MAKE_PAIR_HPP
#define HAMON_PAIR_MAKE_PAIR_HPP

#include <hamon/pair/config.hpp>

#if defined(HAMON_USE_STD_PAIR)

#include <utility>

namespace hamon
{

using std::make_pair;

}	// namespace hamon

#else

#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/unwrap_ref_decay.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T1, typename T2>
inline HAMON_CXX11_CONSTEXPR
hamon::pair<hamon::unwrap_ref_decay_t<T1>, hamon::unwrap_ref_decay_t<T2>>
make_pair(T1&& x, T2&& y)
{
	// [pairs.spec]/6
	return hamon::pair<hamon::unwrap_ref_decay_t<T1>, hamon::unwrap_ref_decay_t<T2>>(
		hamon::forward<T1>(x), hamon::forward<T2>(y));
}

}	// namespace hamon

#endif

#endif // HAMON_PAIR_MAKE_PAIR_HPP
