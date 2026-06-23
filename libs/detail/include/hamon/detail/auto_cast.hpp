/**
 *	@file	auto_cast.hpp
 *
 *	@brief	HAMON_AUTO_CAST の定義
 */

#ifndef HAMON_DETAIL_AUTO_CAST_HPP
#define HAMON_DETAIL_AUTO_CAST_HPP

#include <hamon/type_traits/decay.hpp>

// C++23 で追加された、auto(x) 形式のキャスト
#define HAMON_AUTO_CAST(expr) static_cast<hamon::decay_t<decltype((expr))>>(expr)

#endif // HAMON_DETAIL_AUTO_CAST_HPP
