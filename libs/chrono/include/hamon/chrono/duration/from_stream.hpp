/**
 *	@file	from_stream.hpp
 *
 *	@brief	from_stream()の定義
 */

#ifndef HAMON_CHRONO_DURATION_FROM_STREAM_HPP
#define HAMON_CHRONO_DURATION_FROM_STREAM_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::from_stream;

}	// namespace chrono
}	// namespace hamon

#else


namespace hamon {
namespace chrono {

// TODO

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_DURATION_FROM_STREAM_HPP
