/**
 *	@file	dangling.hpp
 *
 *	@brief	ranges::dangling の定義
 */

#ifndef HAMON_RANGES_DANGLING_HPP
#define HAMON_RANGES_DANGLING_HPP

#include <hamon/ranges/config.hpp>

namespace hamon {
namespace ranges {

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::dangling;

#else

struct dangling
{
	constexpr dangling() noexcept = default;

	template <typename... Args>
	constexpr dangling(Args&&...) noexcept {}
};

#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DANGLING_HPP
