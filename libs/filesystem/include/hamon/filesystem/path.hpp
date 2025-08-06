/**
 *	@file	path.hpp
 *
 *	@brief	path の定義
 */

#ifndef HAMON_FILESYSTEM_PATH_HPP
#define HAMON_FILESYSTEM_PATH_HPP

#include <hamon/filesystem/config.hpp>

#if !defined(HAMON_USE_STD_FILESYSTEM)

namespace hamon
{
}	// namespace hamon

#else

#include <hamon/chrono/time_point.hpp>
//#include <hamon/chrono/file_clock.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/error_code.hpp>
#include <hamon/system_error/system_error.hpp>
#include <locale>

namespace hamon
{
namespace filesystem
{

// [fs.class.path], paths
class path;

// [fs.path.nonmember], path non-member functions
void swap(path& lhs, path& rhs) noexcept;
size_t hash_value(const path& p) noexcept;

// [fs.class.filesystem.error], filesystem errors
class filesystem_error;

// [fs.class.directory.entry], directory entries
class directory_entry;

// [fs.class.directory.iterator], directory iterators
class directory_iterator;

// [fs.dir.itr.nonmembers], range access for directory iterators
directory_iterator begin(directory_iterator iter) noexcept;
directory_iterator end(directory_iterator) noexcept;

// [fs.class.rec.dir.itr], recursive directory iterators
class recursive_directory_iterator;

// [fs.rec.dir.itr.nonmembers], range access for recursive directory iterators
recursive_directory_iterator begin(recursive_directory_iterator iter) noexcept;
recursive_directory_iterator end(recursive_directory_iterator) noexcept;

// [fs.class.file.status], file status
class file_status;

struct space_info
{
	uintmax_t capacity;
	uintmax_t free;
	uintmax_t available;

	friend bool operator==(const space_info&, const space_info&) = default;
};

// [fs.enum], enumerations
enum class file_type;
enum class perms;
enum class perm_options;
enum class copy_options;
enum class directory_options;

using file_time_type = hamon::chrono::time_point<hamon::chrono::file_clock>;

// [fs.op.funcs], filesystem operations
path absolute(const path& p);
path absolute(const path& p, hamon::error_code& ec);

path canonical(const path& p);
path canonical(const path& p, hamon::error_code& ec);

void copy(const path& from, const path& to);
void copy(const path& from, const path& to, hamon::error_code& ec);
void copy(const path& from, const path& to, copy_options options);
void copy(const path& from, const path& to, copy_options options, hamon::error_code& ec);

bool copy_file(const path& from, const path& to);
bool copy_file(const path& from, const path& to, hamon::error_code& ec);
bool copy_file(const path& from, const path& to, copy_options option);
bool copy_file(const path& from, const path& to, copy_options option, hamon::error_code& ec);

void copy_symlink(const path& existing_symlink, const path& new_symlink);
void copy_symlink(const path& existing_symlink, const path& new_symlink, hamon::error_code& ec) noexcept;

bool create_directories(const path& p);
bool create_directories(const path& p, hamon::error_code& ec);

bool create_directory(const path& p);
bool create_directory(const path& p, hamon::error_code& ec) noexcept;

bool create_directory(const path& p, const path& attributes);
bool create_directory(const path& p, const path& attributes, hamon::error_code& ec) noexcept;

void create_directory_symlink(const path& to, const path& new_symlink);
void create_directory_symlink(const path& to, const path& new_symlink, hamon::error_code& ec) noexcept;

void create_hard_link(const path& to, const path& new_hard_link);
void create_hard_link(const path& to, const path& new_hard_link, hamon::error_code& ec) noexcept;

void create_symlink(const path& to, const path& new_symlink);
void create_symlink(const path& to, const path& new_symlink, hamon::error_code& ec) noexcept;

path current_path();
path current_path(hamon::error_code& ec);
void current_path(const path& p);
void current_path(const path& p, hamon::error_code& ec) noexcept;

bool equivalent(const path& p1, const path& p2);
bool equivalent(const path& p1, const path& p2, hamon::error_code& ec) noexcept;

bool exists(file_status s) noexcept;
bool exists(const path& p);
bool exists(const path& p, hamon::error_code& ec) noexcept;

uintmax_t file_size(const path& p);
uintmax_t file_size(const path& p, hamon::error_code& ec) noexcept;

uintmax_t hard_link_count(const path& p);
uintmax_t hard_link_count(const path& p, hamon::error_code& ec) noexcept;

bool is_block_file(file_status s) noexcept;
bool is_block_file(const path& p);
bool is_block_file(const path& p, hamon::error_code& ec) noexcept;

bool is_character_file(file_status s) noexcept;
bool is_character_file(const path& p);
bool is_character_file(const path& p, hamon::error_code& ec) noexcept;

bool is_directory(file_status s) noexcept;
bool is_directory(const path& p);
bool is_directory(const path& p, hamon::error_code& ec) noexcept;

bool is_empty(const path& p);
bool is_empty(const path& p, hamon::error_code& ec);

bool is_fifo(file_status s) noexcept;
bool is_fifo(const path& p);
bool is_fifo(const path& p, hamon::error_code& ec) noexcept;

bool is_other(file_status s) noexcept;
bool is_other(const path& p);
bool is_other(const path& p, hamon::error_code& ec) noexcept;

bool is_regular_file(file_status s) noexcept;
bool is_regular_file(const path& p);
bool is_regular_file(const path& p, hamon::error_code& ec) noexcept;

bool is_socket(file_status s) noexcept;
bool is_socket(const path& p);
bool is_socket(const path& p, hamon::error_code& ec) noexcept;

bool is_symlink(file_status s) noexcept;
bool is_symlink(const path& p);
bool is_symlink(const path& p, hamon::error_code& ec) noexcept;

file_time_type last_write_time(const path& p);
file_time_type last_write_time(const path& p, hamon::error_code& ec) noexcept;
void last_write_time(const path& p, file_time_type new_time);
void last_write_time(const path& p, file_time_type new_time, hamon::error_code& ec) noexcept;

void permissions(const path& p, perms prms, perm_options opts=perm_options::replace);
void permissions(const path& p, perms prms, hamon::error_code& ec) noexcept;
void permissions(const path& p, perms prms, perm_options opts, hamon::error_code& ec);

path proximate(const path& p, hamon::error_code& ec);
path proximate(const path& p, const path& base = current_path());
path proximate(const path& p, const path& base, hamon::error_code& ec);

path read_symlink(const path& p);
path read_symlink(const path& p, hamon::error_code& ec);

path relative(const path& p, hamon::error_code& ec);
path relative(const path& p, const path& base = current_path());
path relative(const path& p, const path& base, hamon::error_code& ec);

bool remove(const path& p);
bool remove(const path& p, hamon::error_code& ec) noexcept;

uintmax_t remove_all(const path& p);
uintmax_t remove_all(const path& p, hamon::error_code& ec);

void rename(const path& from, const path& to);
void rename(const path& from, const path& to, hamon::error_code& ec) noexcept;

void resize_file(const path& p, uintmax_t size);
void resize_file(const path& p, uintmax_t size, hamon::error_code& ec) noexcept;

space_info space(const path& p);
space_info space(const path& p, hamon::error_code& ec) noexcept;

file_status status(const path& p);
file_status status(const path& p, hamon::error_code& ec) noexcept;

bool status_known(file_status s) noexcept;

file_status symlink_status(const path& p);
file_status symlink_status(const path& p, hamon::error_code& ec) noexcept;

path temp_directory_path();
path temp_directory_path(hamon::error_code& ec);

path weakly_canonical(const path& p);
path weakly_canonical(const path& p, hamon::error_code& ec);

}	// namespace filesystem
}	// namespace hamon

namespace std
{

#if 0	// TODO

// [fs.path.fmtr], formatting support
template <class charT>
struct formatter<filesystem::path, charT>;

// [fs.path.hash], hash support
template <class T>
struct hash;

template <>
struct hash<filesystem::path>;

#endif

}	// namespace std

namespace hamon
{
namespace ranges
{

#if 0	// TODO

template <>
inline constexpr bool enable_borrowed_range<hamon::filesystem::directory_iterator> = true;

template <>
inline constexpr bool enable_borrowed_range<hamon::filesystem::recursive_directory_iterator> = true;

template <>
inline constexpr bool enable_view<hamon::filesystem::directory_iterator> = true;

template <>
inline constexpr bool enable_view<hamon::filesystem::recursive_directory_iterator> = true;

#endif

}	// namespace ranges
}	// namespace hamon

namespace hamon
{
namespace filesystem
{

// 31.12.6 Class path[fs.class.path]

class path
{
public:
	using value_type  = see below;
	using string_type = hamon::basic_string<value_type>;
	static constexpr value_type preferred_separator = see below;

	// [fs.enum.path.format], enumeration format
	enum format
	{
		native_format,
		generic_format,
		auto_format
	};

	// [fs.path.construct], constructors and destructor
	path() noexcept;
	path(const path& p);
	path(path&& p) noexcept;
	path(string_type&& source, format fmt = auto_format);
	template<class Source>
	path(const Source& source, format fmt = auto_format);
	template<class InputIterator>
	path(InputIterator first, InputIterator last, format fmt = auto_format);
	template<class Source>
	path(const Source& source, const std::locale& loc, format fmt = auto_format);
	template<class InputIterator>
	path(InputIterator first, InputIterator last, const std::locale& loc, format fmt = auto_format);
	~path();

	// [fs.path.assign], assignments
	path& operator=(const path& p);
	path& operator=(path&& p) noexcept;
	path& operator=(string_type&& source);
	path& assign(string_type&& source);
	template<class Source>
	path& operator=(const Source& source);
	template<class Source>
	path& assign(const Source& source);
	template<class InputIterator>
	path& assign(InputIterator first, InputIterator last);

	// [fs.path.append], appends
	path& operator/=(const path& p);
	template<class Source>
	path& operator/=(const Source& source);
	template<class Source>
	path& append(const Source& source);
	template<class InputIterator>
	path& append(InputIterator first, InputIterator last);

	// [fs.path.concat], concatenation
	path& operator+=(const path& x);
	path& operator+=(const string_type& x);
	path& operator+=(hamon::basic_string_view<value_type> x);
	path& operator+=(const value_type* x);
	path& operator+=(value_type x);
	template<class Source>
	path& operator+=(const Source& x);
	template<class EcharT>
	path& operator+=(EcharT x);
	template<class Source>
	path& concat(const Source& x);
	template<class InputIterator>
	path& concat(InputIterator first, InputIterator last);

	// [fs.path.modifiers], modifiers
	void  clear() noexcept;
	path& make_preferred();
	path& remove_filename();
	path& replace_filename(const path& replacement);
	path& replace_extension(const path& replacement = path());
	void  swap(path& rhs) noexcept;

	// [fs.path.nonmember], non-member operators
	friend bool operator==(const path& lhs, const path& rhs) noexcept;
	friend hamon::strong_ordering operator<=>(const path& lhs, const path& rhs) noexcept;

	friend path operator/(const path& lhs, const path& rhs);

	// [fs.path.native.obs], native format observers
	const string_type& native() const noexcept;
	const value_type* c_str() const noexcept;
	operator string_type() const;

	template<class EcharT, class traits = hamon::char_traits<EcharT>,
		class Allocator = hamon::allocator<EcharT>>
	hamon::basic_string<EcharT, traits, Allocator>
	string(const Allocator& a = Allocator()) const;

	hamon::string    display_string() const;
	hamon::string    system_encoded_string() const;
	hamon::wstring   wstring() const;
	hamon::u8string  u8string() const;
	hamon::u16string u16string() const;
	hamon::u32string u32string() const;

	// [fs.path.generic.obs], generic format observers
	template<class EcharT, class traits = hamon::char_traits<EcharT>,
		class Allocator = hamon::allocator<EcharT>>
	hamon::basic_string<EcharT, traits, Allocator>
	generic_string(const Allocator& a = Allocator()) const;

	hamon::string    generic_display_string() const;
	hamon::string    generic_system_encoded_string() const;
	hamon::wstring   generic_wstring() const;
	hamon::u8string  generic_u8string() const;
	hamon::u16string generic_u16string() const;
	hamon::u32string generic_u32string() const;

	// [fs.path.compare], compare
	int compare(const path& p) const noexcept;
	int compare(const string_type& s) const;
	int compare(hamon::basic_string_view<value_type> s) const;
	int compare(const value_type* s) const;

	// [fs.path.decompose], decomposition
	path root_name() const;
	path root_directory() const;
	path root_path() const;
	path relative_path() const;
	path parent_path() const;
	path filename() const;
	path stem() const;
	path extension() const;

	// [fs.path.query], query
	bool empty() const noexcept;
	bool has_root_name() const;
	bool has_root_directory() const;
	bool has_root_path() const;
	bool has_relative_path() const;
	bool has_parent_path() const;
	bool has_filename() const;
	bool has_stem() const;
	bool has_extension() const;
	bool is_absolute() const;
	bool is_relative() const;

	// [fs.path.gen], generation
	path lexically_normal() const;
	path lexically_relative(const path& base) const;
	path lexically_proximate(const path& base) const;

	// [fs.path.itr], iterators
	class iterator;
	using const_iterator = iterator;

	iterator begin() const;
	iterator end() const;

	// [fs.path.io], path inserter and extractor
	template<class charT, class traits>
	friend std::basic_ostream<charT, traits>&
	operator<<(std::basic_ostream<charT, traits>& os, const path& p);

	template<class charT, class traits>
	friend std::basic_istream<charT, traits>&
	operator>>(std::basic_istream<charT, traits>& is, path& p);
};

// 31.12.7 Class filesystem_error[fs.class.filesystem.error]

class filesystem_error : public hamon::system_error
{
public:
	filesystem_error(const string& what_arg, error_code ec);
	filesystem_error(const string& what_arg, const path& p1, error_code ec);
	filesystem_error(const string& what_arg, const path& p1, const path& p2, error_code ec);

	const path& path1() const noexcept;
	const path& path2() const noexcept;
	const char* what() const noexcept override;
};

// 31.12.8.2 Enum class file_type[fs.enum.file.type]

enum class file_type
{
	none,
	not_found,
	regular,
	directory,
	symlink,
	block,
	character,
	fifo,
	socket,
//	implementation-defined,
	unknown,
};

// 31.12.8.3 Enum class copy_options[fs.enum.copy.opts]

enum class copy_options
{
	none,
	skip_existing,
	overwrite_existing,
	update_existing,
	recursive,
	copy_symlinks,
	skip_symlinks,
	directories_only,
	create_symlinks,
	create_hard_links,
};

// 31.12.8.4 Enum class perms[fs.enum.perms]

enum class perms
{
	none         = 0,
	owner_read   = 0400,
	owner_write  = 0200,
	owner_exec   = 0100,
	owner_all    = 0700,  // owner_read | owner_write | owner_exec
	group_read   = 040,
	group_write  = 020,
	group_exec   = 010,
	group_all    = 070,   // group_read | group_write | group_exec
	others_read  = 04,
	others_write = 02,
	others_exec  = 01,
	others_all   = 07,    // others_read | others_write | others_exec
	all          = 0777,  // owner_all | group_all | others_all
	set_uid      = 04000,
	set_gid      = 02000,
	sticky_bit   = 01000,
	mask         = 07777, // all | set_uid | set_gid | sticky_bit
	unknown      = 0xFFFF,
};

// 31.12.8.5 Enum class perm_options[fs.enum.perm.opts]

enum class perm_options
{
	replace,
	add,
	remove,
	nofollow,
};

// 31.12.8.6 Enum class directory_options[fs.enum.dir.opts]

enum class directory_options
{
	none,
	follow_directory_symlink,
	skip_permission_denied
};

// 31.12.9 Class file_status[fs.class.file.status]

class file_status
{
public:
	// [fs.file.status.cons], constructors and destructor
	file_status() noexcept : file_status(file_type::none) {}
	explicit file_status(file_type ft, perms prms = perms::unknown) noexcept;
	file_status(const file_status&) noexcept = default;
	file_status(file_status&&) noexcept = default;
	~file_status();

	// assignments
	file_status& operator=(const file_status&) noexcept = default;
	file_status& operator=(file_status&&) noexcept = default;

	// [fs.file.status.mods], modifiers
	void       type(file_type ft) noexcept;
	void       permissions(perms prms) noexcept;

	// [fs.file.status.obs], observers
	file_type  type() const noexcept;
	perms      permissions() const noexcept;

	friend bool operator==(const file_status& lhs, const file_status& rhs) noexcept
	{
		return lhs.type() == rhs.type() && lhs.permissions() == rhs.permissions();
	}
};

// 31.12.10 Class directory_entry[fs.class.directory.entry]

class directory_entry
{
public:
	// [fs.dir.entry.cons], constructors and destructor
	directory_entry() noexcept = default;
	directory_entry(const directory_entry&) = default;
	directory_entry(directory_entry&&) noexcept = default;
	explicit directory_entry(const filesystem::path& p);
	directory_entry(const filesystem::path& p, error_code& ec);
	~directory_entry();

	// assignments
	directory_entry& operator=(const directory_entry&) = default;
	directory_entry& operator=(directory_entry&&) noexcept = default;

	// [fs.dir.entry.mods], modifiers
	void assign(const filesystem::path& p);
	void assign(const filesystem::path& p, error_code& ec);
	void replace_filename(const filesystem::path& p);
	void replace_filename(const filesystem::path& p, error_code& ec);
	void refresh();
	void refresh(error_code& ec) noexcept;

	// [fs.dir.entry.obs], observers
	const filesystem::path& path() const noexcept;
	operator const filesystem::path& () const noexcept;
	bool exists() const;
	bool exists(error_code& ec) const noexcept;
	bool is_block_file() const;
	bool is_block_file(error_code& ec) const noexcept;
	bool is_character_file() const;
	bool is_character_file(error_code& ec) const noexcept;
	bool is_directory() const;
	bool is_directory(error_code& ec) const noexcept;
	bool is_fifo() const;
	bool is_fifo(error_code& ec) const noexcept;
	bool is_other() const;
	bool is_other(error_code& ec) const noexcept;
	bool is_regular_file() const;
	bool is_regular_file(error_code& ec) const noexcept;
	bool is_socket() const;
	bool is_socket(error_code& ec) const noexcept;
	bool is_symlink() const;
	bool is_symlink(error_code& ec) const noexcept;
	uintmax_t file_size() const;
	uintmax_t file_size(error_code& ec) const noexcept;
	uintmax_t hard_link_count() const;
	uintmax_t hard_link_count(error_code& ec) const noexcept;
	file_time_type last_write_time() const;
	file_time_type last_write_time(error_code& ec) const noexcept;
	file_status status() const;
	file_status status(error_code& ec) const noexcept;
	file_status symlink_status() const;
	file_status symlink_status(error_code& ec) const noexcept;

	bool operator==(const directory_entry& rhs) const noexcept;
	strong_ordering operator<=>(const directory_entry& rhs) const noexcept;

	// [fs.dir.entry.io], inserter
	template<class charT, class traits>
	friend std::basic_ostream<charT, traits>&
	operator<<(std::basic_ostream<charT, traits>& os, const directory_entry& d);

private:
	filesystem::path path-object;        // exposition only
};

// 31.12.11 Class directory_iterator[fs.class.directory.iterator]

class directory_iterator
{
public:
	using iterator_category = input_iterator_tag;
	using value_type        = directory_entry;
	using difference_type   = ptrdiff_t;
	using pointer           = const directory_entry*;
	using reference         = const directory_entry&;

	// [fs.dir.itr.members], member functions
	directory_iterator() noexcept;
	explicit directory_iterator(const path& p);
	directory_iterator(const path& p, directory_options options);
	directory_iterator(const path& p, error_code& ec);
	directory_iterator(const path& p, directory_options options, error_code& ec);
	directory_iterator(const directory_iterator& rhs);
	directory_iterator(directory_iterator&& rhs) noexcept;
	~directory_iterator();

	directory_iterator& operator=(const directory_iterator& rhs);
	directory_iterator& operator=(directory_iterator&& rhs) noexcept;

	const directory_entry& operator*() const;
	const directory_entry* operator->() const;
	directory_iterator& operator++();
	directory_iterator& increment(error_code& ec);

	bool operator==(default_sentinel_t) const noexcept
	{
		return *this == directory_iterator();
	}

	// other members as required by [input.iterators], input iterators
};

// 31.12.12 Class recursive_directory_iterator[fs.class.rec.dir.itr]

class recursive_directory_iterator
{
public:
	using iterator_category = input_iterator_tag;
	using value_type        = directory_entry;
	using difference_type   = ptrdiff_t;
	using pointer           = const directory_entry*;
	using reference         = const directory_entry&;

	// [fs.rec.dir.itr.members], constructors and destructor
	recursive_directory_iterator() noexcept;
	explicit recursive_directory_iterator(const path& p);
	recursive_directory_iterator(const path& p, directory_options options);
	recursive_directory_iterator(const path& p, directory_options options, error_code& ec);
	recursive_directory_iterator(const path& p, error_code& ec);
	recursive_directory_iterator(const recursive_directory_iterator& rhs);
	recursive_directory_iterator(recursive_directory_iterator&& rhs) noexcept;
	~recursive_directory_iterator();

	// [fs.rec.dir.itr.members], observers
	directory_options  options() const;
	int                depth() const;
	bool               recursion_pending() const;

	const directory_entry& operator*() const;
	const directory_entry* operator->() const;

	// [fs.rec.dir.itr.members], modifiers
	recursive_directory_iterator&
	operator=(const recursive_directory_iterator& rhs);

	recursive_directory_iterator&
	operator=(recursive_directory_iterator&& rhs) noexcept;

	recursive_directory_iterator& operator++();
	recursive_directory_iterator& increment(error_code& ec);

	void pop();
	void pop(error_code& ec);
	void disable_recursion_pending();

	bool operator==(default_sentinel_t) const noexcept
	{
		return *this == recursive_directory_iterator();
	}

	// other members as required by [input.iterators], input iterators
};

}	// namespace filesystem
}	// namespace hamon

#endif

#endif // HAMON_FILESYSTEM_PATH_HPP
