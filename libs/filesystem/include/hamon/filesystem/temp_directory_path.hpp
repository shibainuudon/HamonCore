/**
 *	@file	temp_directory_path.hpp
 *
 *	@brief	temp_directory_path の定義
 */

#ifndef HAMON_FILESYSTEM_TEMP_DIRECTORY_PATH_HPP
#define HAMON_FILESYSTEM_TEMP_DIRECTORY_PATH_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::temp_directory_path;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.39 Temporary directory path[fs.op.temp.dir.path]

path temp_directory_path();
path temp_directory_path(hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_TEMP_DIRECTORY_PATH_HPP
