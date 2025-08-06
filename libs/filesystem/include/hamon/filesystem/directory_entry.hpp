/**
 *	@file	directory_entry.hpp
 *
 *	@brief	directory_entry の定義
 */

#ifndef HAMON_FILESYSTEM_DIRECTORY_ENTRY_HPP
#define HAMON_FILESYSTEM_DIRECTORY_ENTRY_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::directory_entry;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/path.hpp>
#include <hamon/filesystem/file_time_type.hpp>
#include <hamon/filesystem/file_status.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/system_error/error_code.hpp>
#include <ostream>

namespace hamon
{
namespace filesystem
{

// 31.12.10 Class directory_entry[fs.class.directory.entry]

class directory_entry
{
public:
	// [fs.dir.entry.cons], constructors and destructor
	directory_entry() noexcept = default;

	directory_entry(directory_entry const&) = default;

	directory_entry(directory_entry&&) noexcept = default;

	explicit directory_entry(filesystem::path const& p);

	directory_entry(filesystem::path const& p, hamon::error_code& ec);

	~directory_entry();

	// assignments
	directory_entry& operator=(directory_entry const&) = default;

	directory_entry& operator=(directory_entry&&) noexcept = default;

	// [fs.dir.entry.mods], modifiers
	void assign(filesystem::path const& p);

	void assign(filesystem::path const& p, hamon::error_code& ec);

	void replace_filename(filesystem::path const& p);

	void replace_filename(filesystem::path const& p, hamon::error_code& ec);

	void refresh();

	void refresh(hamon::error_code& ec) noexcept;

	// [fs.dir.entry.obs], observers
	filesystem::path const& path() const noexcept;

	operator filesystem::path const& () const noexcept;

	bool exists() const;

	bool exists(hamon::error_code& ec) const noexcept;

	bool is_block_file() const;

	bool is_block_file(hamon::error_code& ec) const noexcept;

	bool is_character_file() const;

	bool is_character_file(hamon::error_code& ec) const noexcept;

	bool is_directory() const;

	bool is_directory(hamon::error_code& ec) const noexcept;

	bool is_fifo() const;

	bool is_fifo(hamon::error_code& ec) const noexcept;

	bool is_other() const;

	bool is_other(hamon::error_code& ec) const noexcept;

	bool is_regular_file() const;

	bool is_regular_file(hamon::error_code& ec) const noexcept;

	bool is_socket() const;

	bool is_socket(hamon::error_code& ec) const noexcept;

	bool is_symlink() const;

	bool is_symlink(hamon::error_code& ec) const noexcept;

	hamon::uintmax_t file_size() const;

	hamon::uintmax_t file_size(hamon::error_code& ec) const noexcept;

	hamon::uintmax_t hard_link_count() const;

	hamon::uintmax_t hard_link_count(hamon::error_code& ec) const noexcept;

	file_time_type last_write_time() const;

	file_time_type last_write_time(hamon::error_code& ec) const noexcept;

	file_status status() const;

	file_status status(hamon::error_code& ec) const noexcept;

	file_status symlink_status() const;

	file_status symlink_status(hamon::error_code& ec) const noexcept;

	bool operator==(directory_entry const& rhs) const noexcept;

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	hamon::strong_ordering operator<=>(directory_entry const& rhs) const noexcept;
#endif

	// [fs.dir.entry.io], inserter
	template <typename charT, typename traits>
	friend std::basic_ostream<charT, traits>&
	operator<<(std::basic_ostream<charT, traits>& os, directory_entry const& d);

private:
	filesystem::path path_object;        // exposition only
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_DIRECTORY_ENTRY_HPP
