/**
 *	@file	get_money.hpp
 *
 *	@brief	get_money の定義
 */

#ifndef HAMON_IOMANIP_GET_MONEY_HPP
#define HAMON_IOMANIP_GET_MONEY_HPP

#include <iomanip>

namespace hamon
{

using std::get_money;

#if 0	// TODO
// [ext.manip], extended manipulators
template <typename moneyT>
unspecified get_money(moneyT& mon, bool intl = false);
#endif

}	// namespace hamon

#endif // HAMON_IOMANIP_GET_MONEY_HPP
