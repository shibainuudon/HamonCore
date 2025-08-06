/**
 *	@file	absolute.hpp
 *
 *	@brief	absolute の定義
 */

#ifndef HAMON_FILESYSTEM_ABSOLUTE_HPP
#define HAMON_FILESYSTEM_ABSOLUTE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::absolute;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.2 Absolute[fs.op.absolute]

path absolute(path const& p);
path absolute(path const& p, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_ABSOLUTE_HPP
