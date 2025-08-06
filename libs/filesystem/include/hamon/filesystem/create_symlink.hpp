/**
 *	@file	create_symlink.hpp
 *
 *	@brief	create_symlink の定義
 */

#ifndef HAMON_FILESYSTEM_CREATE_SYMLINK_HPP
#define HAMON_FILESYSTEM_CREATE_SYMLINK_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::create_symlink;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.11 Create symlink[fs.op.create.symlink]

void create_symlink(path const& to, path const& new_symlink);
void create_symlink(path const& to, path const& new_symlink, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_CREATE_SYMLINK_HPP
