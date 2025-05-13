/**
 *	@file	priority_queue_fwd.hpp
 *
 *	@brief	priority_queue の前方宣言
 */

#ifndef HAMON_QUEUE_PRIORITY_QUEUE_FWD_HPP
#define HAMON_QUEUE_PRIORITY_QUEUE_FWD_HPP

#include <hamon/queue/config.hpp>

#if defined(HAMON_USE_STD_PRIORITY_QUEUE)

#include <queue>

namespace hamon
{

using std::priority_queue;

}	// namespace hamon

#else

#include <hamon/vector.hpp>
#include <hamon/functional/less.hpp>

namespace hamon
{

 // [priority.queue], class template priority_queue
template <
	typename T,
	typename Container = hamon::vector<T>,
    typename Compare = hamon::less<typename Container::value_type>
>
class priority_queue;

}	// namespace hamon

#endif

#endif // HAMON_QUEUE_PRIORITY_QUEUE_FWD_HPP
