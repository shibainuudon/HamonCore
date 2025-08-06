/**
 *	@file	copy_options.hpp
 *
 *	@brief	copy_options の定義
 */

#ifndef HAMON_FILESYSTEM_COPY_OPTIONS_HPP
#define HAMON_FILESYSTEM_COPY_OPTIONS_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::copy_options;

}	// namespace filesystem
}	// namespace hamon

#else

namespace hamon
{
namespace filesystem
{

// 31.12.8.3 Enum class copy_options[fs.enum.copy.opts]

enum class copy_options
{
	none               = 0,
	skip_existing      = 1 << 0,
	overwrite_existing = 1 << 1,
	update_existing    = 1 << 2,
	recursive          = 1 << 3,
	copy_symlinks      = 1 << 4,
	skip_symlinks      = 1 << 5,
	directories_only   = 1 << 6,
	create_symlinks    = 1 << 7,
	create_hard_links  = 1 << 8,
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_COPY_OPTIONS_HPP
