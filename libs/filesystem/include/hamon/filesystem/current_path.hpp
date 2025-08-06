/**
 *	@file	current_path.hpp
 *
 *	@brief	current_path の定義
 */

#ifndef HAMON_FILESYSTEM_CURRENT_PATH_HPP
#define HAMON_FILESYSTEM_CURRENT_PATH_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::current_path;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.12 Current path[fs.op.current.path]

path current_path();
path current_path(hamon::error_code& ec);
void current_path(path const& p);
void current_path(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_CURRENT_PATH_HPP
