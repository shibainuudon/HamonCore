/**
 *	@file	hard_link_count.hpp
 *
 *	@brief	hard_link_count の定義
 */

#ifndef HAMON_FILESYSTEM_HARD_LINK_COUNT_HPP
#define HAMON_FILESYSTEM_HARD_LINK_COUNT_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::hard_link_count;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.16 Hard link count[fs.op.hard.lk.ct]

hamon::uintmax_t hard_link_count(path const& p);
hamon::uintmax_t hard_link_count(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_HARD_LINK_COUNT_HPP
