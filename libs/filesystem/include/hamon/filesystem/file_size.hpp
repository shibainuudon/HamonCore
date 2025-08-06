/**
 *	@file	file_size.hpp
 *
 *	@brief	file_size の定義
 */

#ifndef HAMON_FILESYSTEM_FILE_SIZE_HPP
#define HAMON_FILESYSTEM_FILE_SIZE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::file_size;

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

// 31.12.13.15 File size[fs.op.file.size]

hamon::uintmax_t file_size(path const& p);
hamon::uintmax_t file_size(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_FILE_SIZE_HPP
