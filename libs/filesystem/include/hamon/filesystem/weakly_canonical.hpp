/**
 *	@file	weakly_canonical.hpp
 *
 *	@brief	weakly_canonical の定義
 */

#ifndef HAMON_FILESYSTEM_WEAKLY_CANONICAL_HPP
#define HAMON_FILESYSTEM_WEAKLY_CANONICAL_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::weakly_canonical;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.40 Weakly canonical[fs.op.weakly.canonical]

path weakly_canonical(path const& p);
path weakly_canonical(path const& p, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_WEAKLY_CANONICAL_HPP
