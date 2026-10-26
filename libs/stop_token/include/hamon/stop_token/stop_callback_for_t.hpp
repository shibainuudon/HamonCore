/**
 *	@file	stop_callback_for_t.hpp
 *
 *	@brief	stop_callback_for_t の定義
 */

#ifndef HAMON_STOP_TOKEN_STOP_CALLBACK_FOR_T_HPP
#define HAMON_STOP_TOKEN_STOP_CALLBACK_FOR_T_HPP

namespace hamon
{

// 32.3.2 Header <stop_token> synopsis[thread.stoptoken.syn]

template <typename T, typename CallbackFn>
using stop_callback_for_t = typename T::template callback_type<CallbackFn>;

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_CALLBACK_FOR_T_HPP
