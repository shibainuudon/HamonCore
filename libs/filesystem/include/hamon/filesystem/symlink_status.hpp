/**
 *	@file	symlink_status.hpp
 *
 *	@brief	symlink_status の定義
 */

#ifndef HAMON_FILESYSTEM_SYMLINK_STATUS_HPP
#define HAMON_FILESYSTEM_SYMLINK_STATUS_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::symlink_status;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/file_status.hpp>
#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.38 Symlink status[fs.op.symlink.status]

file_status symlink_status(path const& p);
file_status symlink_status(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_SYMLINK_STATUS_HPP
