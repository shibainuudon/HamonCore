/**
 *	@file	relative.hpp
 *
 *	@brief	relative の定義
 */

#ifndef HAMON_FILESYSTEM_RELATIVE_HPP
#define HAMON_FILESYSTEM_RELATIVE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::relative;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/filesystem/current_path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.30 Relative[fs.op.relative]
path relative(path const& p, hamon::error_code& ec);
path relative(path const& p, path const& base = current_path());
path relative(path const& p, path const& base, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_RELATIVE_HPP
