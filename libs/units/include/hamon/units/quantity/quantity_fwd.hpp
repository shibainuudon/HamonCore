/**
 *	@file	quantity_fwd.hpp
 *
 *	@brief	quantity の前方宣言
 */

#ifndef HAMON_UNITS_QUANTITY_QUANTITY_FWD_HPP
#define HAMON_UNITS_QUANTITY_QUANTITY_FWD_HPP

#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

template <
	typename T,
	typename Dimension,
	typename Scale = hamon::ratio<1>,
	typename Offset = hamon::ratio<0>
>
class quantity;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_QUANTITY_QUANTITY_FWD_HPP
