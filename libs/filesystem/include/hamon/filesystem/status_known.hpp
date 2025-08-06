/**
 *	@file	status_known.hpp
 *
 *	@brief	status_known の定義
 */

#ifndef HAMON_FILESYSTEM_STATUS_KNOWN_HPP
#define HAMON_FILESYSTEM_STATUS_KNOWN_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::status_known;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/file_status.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.13.37 Status known[fs.op.status.known]

bool status_known(file_status s) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_STATUS_KNOWN_HPP
