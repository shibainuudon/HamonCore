/**
 *	@file	copy_file.hpp
 *
 *	@brief	copy_file の定義
 */

#ifndef HAMON_FILESYSTEM_COPY_FILE_HPP
#define HAMON_FILESYSTEM_COPY_FILE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::copy_file;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/filesystem/copy_options.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.5 Copy file[fs.op.copy.file]

bool copy_file(path const& from, path const& to);
bool copy_file(path const& from, path const& to, hamon::error_code& ec);
bool copy_file(path const& from, path const& to, copy_options option);
bool copy_file(path const& from, path const& to, copy_options option, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_COPY_FILE_HPP
