/**
 *	@file	resize_file.hpp
 *
 *	@brief	resize_file の定義
 */

#ifndef HAMON_FILESYSTEM_RESIZE_FILE_HPP
#define HAMON_FILESYSTEM_RESIZE_FILE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::resize_file;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.34 Resize file[fs.op.resize.file]

void resize_file(path const& p, hamon::uintmax_t size);
void resize_file(path const& p, hamon::uintmax_t size, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_RESIZE_FILE_HPP
