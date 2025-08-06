/**
 *	@file	is_block_file.hpp
 *
 *	@brief	is_block_file の定義
 */

#ifndef HAMON_FILESYSTEM_IS_BLOCK_FILE_HPP
#define HAMON_FILESYSTEM_IS_BLOCK_FILE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::is_block_file;

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

// 31.12.13.17 Is block file[fs.op.is.block.file]

bool is_block_file(file_status s) noexcept;
bool is_block_file(path const& p);
bool is_block_file(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_IS_BLOCK_FILE_HPP
