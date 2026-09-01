/**
 *	@file	get_time.hpp
 *
 *	@brief	get_time の定義
 */

#ifndef HAMON_IOMANIP_GET_TIME_HPP
#define HAMON_IOMANIP_GET_TIME_HPP

#include <iomanip>

namespace hamon
{

using std::get_time;

#if 0	// TODO
// [ext.manip], extended manipulators
template <typename charT>
unspecified get_time(tm* tmb, const charT* fmt);
#endif

}	// namespace hamon

#endif // HAMON_IOMANIP_GET_TIME_HPP
