/**
 *	@file	is_other.hpp
 *
 *	@brief	is_other の定義
 */

#ifndef HAMON_FILESYSTEM_IS_OTHER_HPP
#define HAMON_FILESYSTEM_IS_OTHER_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::is_other;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/file_status.hpp>
#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.22 Is other[fs.op.is.other]

bool is_other(file_status s) noexcept;
bool is_other(path const& p);
bool is_other(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_IS_OTHER_HPP
