/**
 *	@file	atomic_wait_state.hpp
 *
 *	@brief	atomic_wait_state の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_WAIT_STATE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_WAIT_STATE_HPP

#include <hamon/atomic/detail/wait_on_address_native.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/new/hardware_destructive_interference_size.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4324)	// アラインメント指定子のために構造体がパッドされました
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000)
HAMON_WARNING_DISABLE_GCC("-Winterference-size")
#endif

// false sharing を避けるためにアラインを設定
struct alignas(hamon::hardware_destructive_interference_size) atomic_wait_state
{
	hamon::detail::native_wait_t platform_state{};
};

HAMON_WARNING_POP()

inline atomic_wait_state* get_atomic_wait_state(void const* ptr)
{
	constexpr hamon::size_t table_size = 1 << 8;
	static atomic_wait_state tbl[table_size] {};
	auto hasher = std::hash<void const*>{};
	return &tbl[hasher(ptr) & (table_size - 1)];
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_WAIT_STATE_HPP
