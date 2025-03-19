/**
 *	@file	last_spec.hpp
 *
 *	@brief	last_spec の定義
 */

#ifndef HAMON_CHRONO_LAST_SPEC_HPP
#define HAMON_CHRONO_LAST_SPEC_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::last_spec;
using std::chrono::last;

}	// namespace chrono
}	// namespace hamon

#else


namespace hamon {
namespace chrono {

// 30.8.2 Class last_spec[time.cal.last]

struct last_spec
{
	explicit last_spec() = default;
};

// calendrical constants
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR last_spec last {};

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_LAST_SPEC_HPP
