/**
 *	@file	file_type.hpp
 *
 *	@brief	file_type の定義
 */

#ifndef HAMON_FILESYSTEM_FILE_TYPE_HPP
#define HAMON_FILESYSTEM_FILE_TYPE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::file_type;

}	// namespace filesystem
}	// namespace hamon

#else

namespace hamon
{
namespace filesystem
{

// 31.12.8.2 Enum class file_type[fs.enum.file.type]

enum class file_type
{
	none = 0,
	not_found = -1,
	regular = 1,
	directory,
	symlink,
	block,
	character,
	fifo,
	socket,
	unknown
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_FILE_TYPE_HPP
