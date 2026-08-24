/**
 *	@file	queue_fwd.hpp
 *
 *	@brief	queue の前方宣言
 */

#ifndef HAMON_QUEUE_QUEUE_FWD_HPP
#define HAMON_QUEUE_QUEUE_FWD_HPP

#include <hamon/deque.hpp>

namespace hamon
{

// [queue], class template queue
template <typename T, typename Container = hamon::deque<T>>
class queue;

}	// namespace hamon

#endif // HAMON_QUEUE_QUEUE_FWD_HPP
