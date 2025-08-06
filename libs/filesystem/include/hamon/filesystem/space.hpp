/**
 *	@file	space.hpp
 *
 *	@brief	space の定義
 */

#ifndef HAMON_FILESYSTEM_SPACE_HPP
#define HAMON_FILESYSTEM_SPACE_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::space;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/filesystem/space_info.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.35 Space[fs.op.space]

space_info space(path const& p);
space_info space(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_SPACE_HPP
