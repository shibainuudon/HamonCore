/**
 *	@file	remove.hpp
 *
 *	@brief	remove の定義
 */

#ifndef HAMON_FILESYSTEM_REMOVE_HPP
#define HAMON_FILESYSTEM_REMOVE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::remove;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.31 Remove[fs.op.remove]

bool remove(path const& p);
bool remove(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_REMOVE_HPP
