/**
 *	@file	seed.hpp
 *
 *	@brief
 */

#ifndef HAMON_DEBUG_DETAIL_SEED_HPP
#define HAMON_DEBUG_DETAIL_SEED_HPP

#include <hamon/debug/detail/value_expression.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace debug
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
		return value_expression<T>(std::forward<T>(v));
	}
};

}	// namespace detail

}	// namespace debug

}	// namespace hamon

#endif // HAMON_DEBUG_DETAIL_SEED_HPP
