/**
 *	@file	create_directories.hpp
 *
 *	@brief	create_directories の定義
 */

#ifndef HAMON_FILESYSTEM_CREATE_DIRECTORIES_HPP
#define HAMON_FILESYSTEM_CREATE_DIRECTORIES_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::create_directories;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.7 Create directories[fs.op.create.directories]

bool create_directories(path const& p);
bool create_directories(path const& p, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_CREATE_DIRECTORIES_HPP
