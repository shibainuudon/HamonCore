/**
 *	@file	read_symlink.hpp
 *
 *	@brief	read_symlink の定義
 */

#ifndef HAMON_FILESYSTEM_READ_SYMLINK_HPP
#define HAMON_FILESYSTEM_READ_SYMLINK_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::read_symlink;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.29 Read symlink[fs.op.read.symlink]

path read_symlink(path const& p);
path read_symlink(path const& p, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_READ_SYMLINK_HPP
