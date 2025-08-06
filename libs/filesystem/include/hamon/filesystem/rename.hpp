/**
 *	@file	rename.hpp
 *
 *	@brief	rename の定義
 */

#ifndef HAMON_FILESYSTEM_RENAME_HPP
#define HAMON_FILESYSTEM_RENAME_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::rename;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.33 Rename[fs.op.rename]

void rename(path const& from, path const& to);
void rename(path const& from, path const& to, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_RENAME_HPP
