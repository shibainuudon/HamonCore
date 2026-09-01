/**
 *	@file	put_money.hpp
 *
 *	@brief	put_money の定義
 */

#ifndef HAMON_IOMANIP_PUT_MONEY_HPP
#define HAMON_IOMANIP_PUT_MONEY_HPP

#include <iomanip>

namespace hamon
{

using std::put_money;

#if 0	// TODO
// [ext.manip], extended manipulators
template <typename moneyT>
unspecified put_money(const moneyT& mon, bool intl = false);
#endif

}	// namespace hamon

#endif // HAMON_IOMANIP_PUT_MONEY_HPP
