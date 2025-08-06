/**
 *	@file	filesystem_error.hpp
 *
 *	@brief	filesystem_error の定義
 */

#ifndef HAMON_FILESYSTEM_FILESYSTEM_ERROR_HPP
#define HAMON_FILESYSTEM_FILESYSTEM_ERROR_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::filesystem_error;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/system_error/error_code.hpp>
#include <hamon/system_error/system_error.hpp>
#include <hamon/string.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.7 Class filesystem_error[fs.class.filesystem.error]

class filesystem_error : public hamon::system_error
{
public:
	filesystem_error(hamon::string const& what_arg, hamon::error_code ec);
	filesystem_error(hamon::string const& what_arg, path const& p1, hamon::error_code ec);
	filesystem_error(hamon::string const& what_arg, path const& p1, path const& p2, hamon::error_code ec);

	path const& path1() const noexcept;
	path const& path2() const noexcept;
	char const* what() const noexcept override;
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_FILESYSTEM_ERROR_HPP
