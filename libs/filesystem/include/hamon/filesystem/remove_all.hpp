/**
 *	@file	remove_all.hpp
 *
 *	@brief	remove_all の定義
 */

#ifndef HAMON_FILESYSTEM_REMOVE_ALL_HPP
#define HAMON_FILESYSTEM_REMOVE_ALL_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::remove_all;

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

// 31.12.13.32 Remove all[fs.op.remove.all]

hamon::uintmax_t remove_all(path const& p);
hamon::uintmax_t remove_all(path const& p, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_REMOVE_ALL_HPP
