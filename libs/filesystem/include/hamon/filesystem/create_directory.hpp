/**
 *	@file	create_directory.hpp
 *
 *	@brief	create_directory の定義
 */

#ifndef HAMON_FILESYSTEM_CREATE_DIRECTORY_HPP
#define HAMON_FILESYSTEM_CREATE_DIRECTORY_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::create_directory;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.8 Create directory[fs.op.create.directory]

bool create_directory(path const& p);
bool create_directory(path const& p, hamon::error_code& ec) noexcept;

bool create_directory(path const& p, path const& attributes);
bool create_directory(path const& p, path const& attributes, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_CREATE_DIRECTORY_HPP
