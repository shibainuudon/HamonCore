/**
 *	@file	exists.hpp
 *
 *	@brief	exists の定義
 */

#ifndef HAMON_FILESYSTEM_EXISTS_HPP
#define HAMON_FILESYSTEM_EXISTS_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::exists;

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

// 31.12.13.14 Exists[fs.op.exists]

bool exists(file_status s) noexcept;
bool exists(path const& p);
bool exists(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_EXISTS_HPP
