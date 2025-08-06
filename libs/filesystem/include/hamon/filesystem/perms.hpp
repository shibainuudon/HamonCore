/**
 *	@file	perms.hpp
 *
 *	@brief	perms の定義
 */

#ifndef HAMON_FILESYSTEM_PERMS_HPP
#define HAMON_FILESYSTEM_PERMS_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::perms;

}	// namespace filesystem
}	// namespace hamon

#else

namespace hamon
{
namespace filesystem
{

// 31.12.8.4 Enum class perms[fs.enum.perms]

enum class perms
{
	none = 0,

	owner_read  = 0400,
	owner_write = 0200,
	owner_exec  = 0100,
	owner_all   = 0700,

	group_read  = 040,
	group_write = 020,
	group_exec  = 010,
	group_all   = 070,

	others_read  = 04,
	others_write = 02,
	others_exec  = 01,
	others_all   = 07,

	all = 0777,

	set_uid    = 04000,
	set_gid    = 02000,
	sticky_bit = 01000,
	mask       = 07777,
	unknown    = 0xFFFF,
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_PERMS_HPP
