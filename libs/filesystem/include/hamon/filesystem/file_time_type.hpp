/**
 *	@file	file_time_type.hpp
 *
 *	@brief	file_time_type の定義
 */

#ifndef HAMON_FILESYSTEM_FILE_TIME_TYPE_HPP
#define HAMON_FILESYSTEM_FILE_TIME_TYPE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::file_time_type;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/file_clock.hpp>

namespace hamon
{
namespace filesystem
{

using file_time_type = hamon::chrono::time_point<hamon::chrono::file_clock>;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_FILE_TIME_TYPE_HPP
