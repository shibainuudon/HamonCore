/**
 *	@file	canonical.hpp
 *
 *	@brief	canonical の定義
 */

#ifndef HAMON_FILESYSTEM_CANONICAL_HPP
#define HAMON_FILESYSTEM_CANONICAL_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::canonical;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.3 Canonical[fs.op.canonical]

path canonical(path const& p);
path canonical(path const& p, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_CANONICAL_HPP
