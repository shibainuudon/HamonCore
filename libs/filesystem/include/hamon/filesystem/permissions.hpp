/**
 *	@file	permissions.hpp
 *
 *	@brief	permissions の定義
 */

#ifndef HAMON_FILESYSTEM_PERMISSIONS_HPP
#define HAMON_FILESYSTEM_PERMISSIONS_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::permissions;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/perms.hpp>
#include <hamon/filesystem/perm_options.hpp>
#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.27 Permissions[fs.op.permissions]

void permissions(path const& p, perms prms, perm_options opts = perm_options::replace);
void permissions(path const& p, perms prms, hamon::error_code& ec) noexcept;
void permissions(path const& p, perms prms, perm_options opts, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_PERMISSIONS_HPP
