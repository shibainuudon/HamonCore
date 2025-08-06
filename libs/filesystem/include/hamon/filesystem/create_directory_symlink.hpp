/**
 *	@file	create_directory_symlink.hpp
 *
 *	@brief	create_directory_symlink の定義
 */

#ifndef HAMON_FILESYSTEM_CREATE_DIRECTORY_SYMLINK_HPP
#define HAMON_FILESYSTEM_CREATE_DIRECTORY_SYMLINK_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::create_directory_symlink;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.9 Create directory symlink[fs.op.create.dir.symlk]

void create_directory_symlink(path const& to, path const& new_symlink);
void create_directory_symlink(path const& to, path const& new_symlink, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_CREATE_DIRECTORY_SYMLINK_HPP
