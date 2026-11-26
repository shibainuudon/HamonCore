/**
 *	@file	seed.hpp
 *
 *	@brief
 */

#ifndef HAMON_POWER_ASSERT_DETAIL_SEED_HPP
#define HAMON_POWER_ASSERT_DETAIL_SEED_HPP

#include <hamon/power_assert/detail/value_expression.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace power_assert
{
namespace detail
{

class seed
{
public:
	// ->* is highest precedence left to right operator
	template <typename T>
	HAMON_CONSTEXPR value_expression<T>
	operator->*(T&& v) const
	{
		return value_expression<T>(hamon::forward<T>(v));
	}
};

}	// namespace detail
}	// namespace power_assert
}	// namespace hamon

#endif // HAMON_POWER_ASSERT_DETAIL_SEED_HPP
