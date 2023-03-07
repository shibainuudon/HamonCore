/**
 *	@file	any.hpp
 *
 *	@brief	any の定義
 */

#ifndef HAMON_QVM_COMMON_ANY_HPP
#define HAMON_QVM_COMMON_ANY_HPP

#include <hamon/qvm/detail/reduce.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/logical_or.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	any
 */
template <
	template <typename, hamon::size_t...> class GenType,
	hamon::size_t... Ns
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
any(GenType<bool, Ns...> const& v) HAMON_NOEXCEPT
{
	return hamon::qvm::detail::reduce(v, false, hamon::logical_or<>{});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_COMMON_ANY_HPP
