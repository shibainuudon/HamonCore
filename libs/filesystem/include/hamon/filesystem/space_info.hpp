/**
 *	@file	space_info.hpp
 *
 *	@brief	space_info の定義
 */

#ifndef HAMON_FILESYSTEM_SPACE_INFO_HPP
#define HAMON_FILESYSTEM_SPACE_INFO_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::space_info;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/cstdint/uintmax_t.hpp>

namespace hamon
{
namespace filesystem
{

struct space_info
{
	hamon::uintmax_t capacity;
	hamon::uintmax_t free;
	hamon::uintmax_t available;

//	friend bool operator==(space_info const&, space_info const&) = default;
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_SPACE_INFO_HPP
