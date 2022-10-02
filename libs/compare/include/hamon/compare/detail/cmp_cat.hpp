/**
 *	@file	cmp_cat.hpp
 *
 *	@brief	cmp_cat の定義
 */

#ifndef HAMON_COMPARE_DETAIL_CMP_CAT_HPP
#define HAMON_COMPARE_DETAIL_CMP_CAT_HPP

namespace hamon
{

namespace cmp_cat
{

using type = signed char;

enum class Ord : type { equivalent = 0, less = -1, greater = 1 };

enum class Ncmp : type { unordered = 2 };

struct unspec
{
	constexpr unspec(unspec*) noexcept {}
};

}	// namespace cmp_cat

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_CMP_CAT_HPP
