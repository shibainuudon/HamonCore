/**
 *	@file	perm_options.hpp
 *
 *	@brief	perm_options の定義
 */

#ifndef HAMON_FILESYSTEM_PERM_OPTIONS_HPP
#define HAMON_FILESYSTEM_PERM_OPTIONS_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::perm_options;

}	// namespace filesystem
}	// namespace hamon

#else

namespace hamon
{
namespace filesystem
{

// 31.12.8.5 Enum class perm_options[fs.enum.perm.opts]

enum class perm_options
{
	replace  = 1 << 0,
	add      = 1 << 1,
	remove   = 1 << 2,
	nofollow = 1 << 3,
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_PERM_OPTIONS_HPP
