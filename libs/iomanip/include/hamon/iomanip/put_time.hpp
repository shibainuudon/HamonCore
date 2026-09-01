/**
 *	@file	put_time.hpp
 *
 *	@brief	put_time の定義
 */

#ifndef HAMON_IOMANIP_PUT_TIME_HPP
#define HAMON_IOMANIP_PUT_TIME_HPP

#include <iomanip>

namespace hamon
{

using std::put_time;

#if 0	// TODO
// [ext.manip], extended manipulators
template <typename charT>
unspecified put_time(const tm* tmb, const charT* fmt);
#endif

}	// namespace hamon

#endif // HAMON_IOMANIP_PUT_TIME_HPP
