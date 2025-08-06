/**
 *	@file	is_empty.hpp
 *
 *	@brief	is_empty の定義
 */

#ifndef HAMON_FILESYSTEM_IS_EMPTY_HPP
#define HAMON_FILESYSTEM_IS_EMPTY_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::is_empty;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.20 Is empty[fs.op.is.empty]

bool is_empty(path const& p);
bool is_empty(path const& p, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_IS_EMPTY_HPP
