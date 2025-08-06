/**
 *	@file	is_socket.hpp
 *
 *	@brief	is_socket の定義
 */

#ifndef HAMON_FILESYSTEM_IS_SOCKET_HPP
#define HAMON_FILESYSTEM_IS_SOCKET_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::is_socket;

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

// 31.12.13.24 Is socket[fs.op.is.socket]

bool is_socket(file_status s) noexcept;
bool is_socket(path const& p);
bool is_socket(path const& p, hamon::error_code& ec) noexcept;

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_IS_SOCKET_HPP
