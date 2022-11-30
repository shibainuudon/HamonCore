/**
 *	@file	all.hpp
 *
 *	@brief	all の定義
 */

#ifndef HAMON_QVM_COMMON_ALL_HPP
#define HAMON_QVM_COMMON_ALL_HPP

#include <hamon/qvm/detail/reduce.hpp>
#include <hamon/functional/logical_and.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

/**
 *	@brief	all
 */
template <
	template <typename, std::size_t...> class GenType,
	std::size_t... Ns
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
all(GenType<bool, Ns...> const& v) HAMON_NOEXCEPT
{
	return hamon::qvm::detail::reduce(v, true, hamon::logical_and<>{});
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_COMMON_ALL_HPP
