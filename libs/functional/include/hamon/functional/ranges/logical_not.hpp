/**
 *	@file	logical_not.hpp
 *
 *	@brief	ranges::logical_not クラスの定義
 */

#ifndef HAMON_FUNCTIONAL_RANGES_LOGICAL_NOT_HPP
#define HAMON_FUNCTIONAL_RANGES_LOGICAL_NOT_HPP

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

/**
 *	@brief	ranges::logical_not
 */
struct logical_not
{
	template <typename T>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator()(T&& x) const
	HAMON_NOEXCEPT_IF_EXPR(!std::declval<T>())
	->decltype(!hamon::forward<T>(x))
	{
		return !hamon::forward<T>(x);
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_RANGES_LOGICAL_NOT_HPP
