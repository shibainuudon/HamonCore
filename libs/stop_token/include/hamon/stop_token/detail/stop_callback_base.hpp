/**
 *	@file	stop_callback_base.hpp
 *
 *	@brief	stop_callback_base の定義
 */

#ifndef HAMON_STOP_TOKEN_DETAIL_STOP_CALLBACK_BASE_HPP
#define HAMON_STOP_TOKEN_DETAIL_STOP_CALLBACK_BASE_HPP

#include <hamon/config.hpp>

#include <atomic>	// TODO

namespace hamon
{
namespace detail
{

struct stop_callback_base
{
#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)
	using __callback_fn_t = void(stop_callback_base*) noexcept;
#else
	using __callback_fn_t = void(stop_callback_base*);
#endif

	explicit stop_callback_base(__callback_fn_t* __callback_fn) : __callback_fn_(__callback_fn) {}

	void __invoke() noexcept { __callback_fn_(this); }

	__callback_fn_t* __callback_fn_;
	std::atomic<bool> __completed_ = false;
	bool* __destroyed_ = nullptr;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_STOP_TOKEN_DETAIL_STOP_CALLBACK_BASE_HPP
