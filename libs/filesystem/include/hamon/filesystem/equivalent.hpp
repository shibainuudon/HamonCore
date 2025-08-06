/**
 *	@file	equivalent.hpp
 *
 *	@brief	equivalent の定義
 */

#ifndef HAMON_FILESYSTEM_EQUIVALENT_HPP
#define HAMON_FILESYSTEM_EQUIVALENT_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::equivalent;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.13 Equivalent[fs.op.equivalent]

bool equivalent(path const& p1, path const& p2);
bool equivalent(path const& p1, path const& p2, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_EQUIVALENT_HPP
