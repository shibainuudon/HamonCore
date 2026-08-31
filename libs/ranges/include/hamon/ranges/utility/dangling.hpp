/**
 *	@file	dangling.hpp
 *
 *	@brief	ranges::dangling の定義
 */

#ifndef HAMON_RANGES_UTILITY_DANGLING_HPP
#define HAMON_RANGES_UTILITY_DANGLING_HPP

namespace hamon {
namespace ranges {

struct dangling
{
	constexpr dangling() noexcept = default;

	template <typename... Args>
	constexpr dangling(Args&&...) noexcept {}
};

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_DANGLING_HPP
