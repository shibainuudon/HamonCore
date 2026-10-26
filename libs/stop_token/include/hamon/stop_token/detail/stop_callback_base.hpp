/**
 *	@file	stop_callback_base.hpp
 *
 *	@brief	stop_callback_base の定義
 */

#ifndef HAMON_STOP_TOKEN_DETAIL_STOP_CALLBACK_BASE_HPP
#define HAMON_STOP_TOKEN_DETAIL_STOP_CALLBACK_BASE_HPP

#include <hamon/atomic.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

struct stop_callback_base
{
#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)
	using callback_fn_t = void(stop_callback_base*) noexcept;
#else
	using callback_fn_t = void(stop_callback_base*);
#endif

	explicit stop_callback_base(callback_fn_t* callback_fn)
		: m_callback_fn(callback_fn)
	{}

	void invoke() noexcept { m_callback_fn(this); }

	callback_fn_t* m_callback_fn;
	hamon::atomic<bool> m_completed{false};
	bool* m_destroyed{nullptr};
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_STOP_TOKEN_DETAIL_STOP_CALLBACK_BASE_HPP
