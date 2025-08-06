/**
 *	@file	is_regular_file.hpp
 *
 *	@brief	is_regular_file の定義
 */

#ifndef HAMON_FILESYSTEM_IS_REGULAR_FILE_HPP
#define HAMON_FILESYSTEM_IS_REGULAR_FILE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::is_regular_file;

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

// 31.12.13.23 Is regular file[fs.op.is.regular.file]

bool is_regular_file(file_status s) noexcept;
bool is_regular_file(path const& p);
bool is_regular_file(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_IS_REGULAR_FILE_HPP
