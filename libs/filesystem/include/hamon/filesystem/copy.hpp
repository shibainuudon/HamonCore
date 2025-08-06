/**
 *	@file	copy.hpp
 *
 *	@brief	copy の定義
 */

#ifndef HAMON_FILESYSTEM_COPY_HPP
#define HAMON_FILESYSTEM_COPY_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::copy;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/filesystem/copy_options.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.4 Copy[fs.op.copy]

void copy(path const& from, path const& to);
void copy(path const& from, path const& to, hamon::error_code& ec);
void copy(path const& from, path const& to, copy_options options);
void copy(path const& from, path const& to, copy_options options, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_COPY_HPP
