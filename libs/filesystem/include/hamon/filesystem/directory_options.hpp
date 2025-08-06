/**
 *	@file	directory_options.hpp
 *
 *	@brief	directory_options の定義
 */

#ifndef HAMON_FILESYSTEM_DIRECTORY_OPTIONS_HPP
#define HAMON_FILESYSTEM_DIRECTORY_OPTIONS_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::directory_options;

}	// namespace filesystem
}	// namespace hamon

#else

namespace hamon
{
namespace filesystem
{

// 31.12.8.6 Enum class directory_options[fs.enum.dir.opts]

enum class directory_options
{
	none                     = 0,
	follow_directory_symlink = 1 << 0,
	skip_permission_denied   = 1 << 1,
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_DIRECTORY_OPTIONS_HPP
