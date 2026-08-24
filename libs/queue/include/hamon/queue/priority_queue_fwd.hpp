/**
 *	@file	priority_queue_fwd.hpp
 *
 *	@brief	priority_queue の前方宣言
 */

#ifndef HAMON_QUEUE_PRIORITY_QUEUE_FWD_HPP
#define HAMON_QUEUE_PRIORITY_QUEUE_FWD_HPP

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

#endif // HAMON_QUEUE_PRIORITY_QUEUE_FWD_HPP
