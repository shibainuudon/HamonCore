/**
 *	@file	is_directory.hpp
 *
 *	@brief	is_directory の定義
 */

#ifndef HAMON_FILESYSTEM_IS_DIRECTORY_HPP
#define HAMON_FILESYSTEM_IS_DIRECTORY_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::is_directory;

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

// 31.12.13.19 Is directory[fs.op.is.directory]

bool is_directory(file_status s) noexcept;
bool is_directory(path const& p);
bool is_directory(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_IS_DIRECTORY_HPP
