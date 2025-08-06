/**
 *	@file	path.hpp
 *
 *	@brief	path の定義
 */

#ifndef HAMON_FILESYSTEM_PATH_HPP
#define HAMON_FILESYSTEM_PATH_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::path;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/compare/strong_ordering.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/config.hpp>
#include <locale>
#include <ostream>
#include <istream>

namespace hamon
{
namespace filesystem
{

// 31.12.6 Class path[fs.class.path]

class path
{
public:
#if defined(HAMON_PLATFORM_WIN32)
	using value_type = wchar_t;
	static constexpr value_type preferred_separator = L'\\';
#else
	using value_type = char;
	static constexpr value_type preferred_separator = '/';
#endif
	using string_type = hamon::basic_string<value_type>;

	// [fs.enum.path.format], enumeration format
	enum format
	{
		native_format,
		generic_format,
		auto_format
	};

	// [fs.path.construct], constructors and destructor
	path() noexcept;

	path(path const& p);

	path(path&& p) noexcept;

	path(string_type&& source, format fmt = auto_format);

	template <typename Source>
	path(Source const& source, format fmt = auto_format);

	template <typename InputIterator>
	path(InputIterator first, InputIterator last, format fmt = auto_format);

	template <typename Source>
	path(Source const& source, std::locale const& loc, format fmt = auto_format);

	template <typename InputIterator>
	path(InputIterator first, InputIterator last, std::locale const& loc, format fmt = auto_format);

	~path();

	// [fs.path.assign], assignments
	path& operator=(path const& p);

	path& operator=(path&& p) noexcept;

	path& operator=(string_type&& source);

	path& assign(string_type&& source);

	template <typename Source>
	path& operator=(Source const& source);

	template <typename Source>
	path& assign(Source const& source);

	template <typename InputIterator>
	path& assign(InputIterator first, InputIterator last);

	// [fs.path.append], appends
	path& operator/=(path const& p);

	template <typename Source>
	path& operator/=(Source const& source);

	template <typename Source>
	path& append(Source const& source);

	template <typename InputIterator>
	path& append(InputIterator first, InputIterator last);

	// [fs.path.concat], concatenation
	path& operator+=(path const& x);

	path& operator+=(string_type const& x);

	path& operator+=(hamon::basic_string_view<value_type> x);

	path& operator+=(value_type const* x);

	path& operator+=(value_type x);

	template <typename Source>
	path& operator+=(Source const& x);

	template <typename EcharT>
	path& operator+=(EcharT x);

	template <typename Source>
	path& concat(Source const& x);

	template <typename InputIterator>
	path& concat(InputIterator first, InputIterator last);

	// [fs.path.modifiers], modifiers
	void clear() noexcept;

	path& make_preferred();

	path& remove_filename();

	path& replace_filename(path const& replacement);

	path& replace_extension(path const& replacement = path());

	void swap(path& rhs) noexcept;

	// [fs.path.nonmember], non-member operators
	friend bool operator==(path const& lhs, path const& rhs) noexcept;

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend hamon::strong_ordering operator<=>(path const& lhs, path const& rhs) noexcept;
#endif

	friend path operator/(path const& lhs, path const& rhs);

	// [fs.path.native.obs], native format observers
	string_type const& native() const noexcept;
	value_type const* c_str() const noexcept;
	operator string_type() const;

	template <
		typename EcharT,
		typename traits = hamon::char_traits<EcharT>,
		typename Allocator = hamon::allocator<EcharT>>
	hamon::basic_string<EcharT, traits, Allocator>
	string(Allocator const& a = Allocator()) const;

	hamon::string display_string() const;

	hamon::string system_encoded_string() const;

	hamon::wstring wstring() const;

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	hamon::u8string u8string() const;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	hamon::u16string u16string() const;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	hamon::u32string u32string() const;
#endif

	// [fs.path.generic.obs], generic format observers
	template <
		typename EcharT,
		typename traits = hamon::char_traits<EcharT>,
		typename Allocator = hamon::allocator<EcharT>>
	hamon::basic_string<EcharT, traits, Allocator>
	generic_string(Allocator const& a = Allocator()) const;

	hamon::string generic_display_string() const;

	hamon::string generic_system_encoded_string() const;

	hamon::wstring generic_wstring() const;

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	hamon::u8string generic_u8string() const;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	hamon::u16string generic_u16string() const;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	hamon::u32string generic_u32string() const;
#endif

	// [fs.path.compare], compare
	int compare(path const& p) const noexcept;
	int compare(string_type const& s) const;
	int compare(hamon::basic_string_view<value_type> s) const;
	int compare(value_type const* s) const;

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
	path lexically_relative(path const& base) const;
	path lexically_proximate(path const& base) const;

	// [fs.path.itr], iterators
	class iterator;
	using const_iterator = iterator;

	iterator begin() const;
	iterator end() const;

	// [fs.path.io], path inserter and extractor
	template <typename charT, typename traits>
	friend std::basic_ostream<charT, traits>&
	operator<<(std::basic_ostream<charT, traits>& os, path const& p);

	template <typename charT, typename traits>
	friend std::basic_istream<charT, traits>&
	operator>>(std::basic_istream<charT, traits>& is, path& p);
};

// [fs.path.nonmember], path non-member functions
void swap(path& lhs, path& rhs) noexcept;
size_t hash_value(path const& p) noexcept;

}	// namespace filesystem
}	// namespace hamon

#if 0	// TODO
namespace std
{

// [fs.path.fmtr], formatting support
template <typename charT>
struct formatter<filesystem::path, charT>;

// [fs.path.hash], hash support
template <typename T>
struct hash;

template <>
struct hash<filesystem::path>;

}
#endif

#endif

#endif // HAMON_FILESYSTEM_PATH_HPP
