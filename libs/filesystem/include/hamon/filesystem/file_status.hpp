/**
 *	@file	file_status.hpp
 *
 *	@brief	file_status の定義
 */

#ifndef HAMON_FILESYSTEM_FILE_STATUS_HPP
#define HAMON_FILESYSTEM_FILE_STATUS_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::file_status;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/file_type.hpp>
#include <hamon/filesystem/perms.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.9 Class file_status[fs.class.file.status]

class file_status
{
public:
	// [fs.file.status.cons], constructors and destructor
	file_status() noexcept : file_status(file_type::none) {}

	explicit file_status(file_type ft, perms prms = perms::unknown) noexcept;

	file_status(file_status const&) noexcept = default;

	file_status(file_status&&) noexcept = default;

	~file_status();

	// assignments
	file_status& operator=(file_status const&) noexcept = default;
	file_status& operator=(file_status&&) noexcept = default;

	// [fs.file.status.mods], modifiers
	void type(file_type ft) noexcept;
	void permissions(perms prms) noexcept;

	// [fs.file.status.obs], observers
	file_type type() const noexcept;
	perms permissions() const noexcept;

	friend bool operator==(file_status const& lhs, file_status const& rhs) noexcept
	{
		return lhs.type() == rhs.type() && lhs.permissions() == rhs.permissions();
	}
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_FILE_STATUS_HPP
