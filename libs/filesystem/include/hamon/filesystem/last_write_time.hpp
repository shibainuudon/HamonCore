/**
 *	@file	last_write_time.hpp
 *
 *	@brief	last_write_time の定義
 */

#ifndef HAMON_FILESYSTEM_LAST_WRITE_TIME_HPP
#define HAMON_FILESYSTEM_LAST_WRITE_TIME_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::last_write_time;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/file_time_type.hpp>
#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.26 Last write time[fs.op.last.write.time]

file_time_type last_write_time(path const& p);
file_time_type last_write_time(path const& p, hamon::error_code& ec) noexcept;
void last_write_time(path const& p, file_time_type new_time);
void last_write_time(path const& p, file_time_type new_time, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_LAST_WRITE_TIME_HPP
