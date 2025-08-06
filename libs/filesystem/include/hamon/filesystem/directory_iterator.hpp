/**
 *	@file	directory_iterator.hpp
 *
 *	@brief	directory_iterator の定義
 */

#ifndef HAMON_FILESYSTEM_DIRECTORY_ITERATOR_HPP
#define HAMON_FILESYSTEM_DIRECTORY_ITERATOR_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::directory_iterator;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/directory_entry.hpp>
#include <hamon/filesystem/directory_options.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/system_error/error_code.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.11 Class directory_iterator[fs.class.directory.iterator]

class directory_iterator
{
public:
	using iterator_category = hamon::input_iterator_tag;
	using value_type = directory_entry;
	using difference_type = hamon::ptrdiff_t;
	using pointer = directory_entry const*;
	using reference = directory_entry const&;

	// [fs.dir.itr.members], member functions
	directory_iterator() noexcept;
	explicit directory_iterator(path const& p);
	directory_iterator(path const& p, directory_options options);
	directory_iterator(path const& p, hamon::error_code& ec);
	directory_iterator(path const& p, directory_options options, hamon::error_code& ec);
	directory_iterator(directory_iterator const& rhs);
	directory_iterator(directory_iterator&& rhs) noexcept;
	~directory_iterator();

	directory_iterator& operator=(directory_iterator const& rhs);
	directory_iterator& operator=(directory_iterator&& rhs) noexcept;

	directory_entry const& operator*() const;
	directory_entry const* operator->() const;
	directory_iterator& operator++();
	directory_iterator& increment(hamon::error_code& ec);

	bool operator==(hamon::default_sentinel_t) const noexcept;/*
	{
		return *this == directory_iterator();
	}*/

	// other members as required by [input.iterators], input iterators
};

// [fs.dir.itr.nonmembers], range access for directory iterators
directory_iterator begin(directory_iterator iter) noexcept;
directory_iterator end(directory_iterator) noexcept;

}	// namespace filesystem
}	// namespace hamon

#if 0	// TODO
namespace std::ranges
{
template<>
inline constexpr bool enable_borrowed_range<filesystem::directory_iterator> = true;
template<>
inline constexpr bool enable_view<filesystem::directory_iterator> = true;
}
#endif

#endif

#endif // HAMON_FILESYSTEM_DIRECTORY_ITERATOR_HPP
