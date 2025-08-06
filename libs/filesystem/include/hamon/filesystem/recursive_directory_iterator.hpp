/**
 *	@file	recursive_directory_iterator.hpp
 *
 *	@brief	recursive_directory_iterator の定義
 */

#ifndef HAMON_FILESYSTEM_RECURSIVE_DIRECTORY_ITERATOR_HPP
#define HAMON_FILESYSTEM_RECURSIVE_DIRECTORY_ITERATOR_HPP

#include <hamon/filesystem/config.hpp>

#if defined(HAMON_USE_STD_FILESYSTEM)

#include <filesystem>

namespace hamon
{
namespace filesystem
{

using std::filesystem::recursive_directory_iterator;

}	// namespace filesystem
}	// namespace hamon

#else

#include <hamon/filesystem/directory_entry.hpp>
#include <hamon/filesystem/directory_options.hpp>
#include <hamon/filesystem/path.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>

namespace hamon
{
namespace filesystem
{

// 31.12.12 Class recursive_directory_iterator[fs.class.rec.dir.itr]

class recursive_directory_iterator
{
public:
	using iterator_category = hamon::input_iterator_tag;
	using value_type = directory_entry;
	using difference_type = hamon::ptrdiff_t;
	using pointer = directory_entry const*;
	using reference = directory_entry const&;

	// [fs.rec.dir.itr.members], constructors and destructor
	recursive_directory_iterator() noexcept;
	explicit recursive_directory_iterator(path const& p);
	recursive_directory_iterator(path const& p, directory_options options);
	recursive_directory_iterator(path const& p, directory_options options, hamon::error_code& ec);
	recursive_directory_iterator(path const& p, hamon::error_code& ec);
	recursive_directory_iterator(recursive_directory_iterator const& rhs);
	recursive_directory_iterator(recursive_directory_iterator&& rhs) noexcept;
	~recursive_directory_iterator();

	// [fs.rec.dir.itr.members], observers
	directory_options options() const;
	int depth() const;
	bool recursion_pending() const;

	directory_entry const& operator*() const;
	directory_entry const* operator->() const;

	// [fs.rec.dir.itr.members], modifiers
	recursive_directory_iterator&
	operator=(recursive_directory_iterator const& rhs);

	recursive_directory_iterator&
	operator=(recursive_directory_iterator&& rhs) noexcept;

	recursive_directory_iterator& operator++();

	recursive_directory_iterator& increment(hamon::error_code& ec);

	void pop();

	void pop(hamon::error_code& ec);

	void disable_recursion_pending();

	bool operator==(hamon::default_sentinel_t) const noexcept;/*
	{
		return *this == recursive_directory_iterator();
	}*/

	// other members as required by [input.iterators], input iterators
};

// [fs.rec.dir.itr.nonmembers], range access for recursive directory iterators
recursive_directory_iterator begin(recursive_directory_iterator iter) noexcept;
recursive_directory_iterator end(recursive_directory_iterator) noexcept;

}	// namespace filesystem
}	// namespace hamon

#if 0	// TODO
namespace std::ranges
{
template<>
inline constexpr bool enable_borrowed_range<filesystem::recursive_directory_iterator> = true;
template<>
inline constexpr bool enable_view<filesystem::recursive_directory_iterator> = true;
}
#endif

#endif

#endif // HAMON_FILESYSTEM_RECURSIVE_DIRECTORY_ITERATOR_HPP
