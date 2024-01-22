/**
 *	@file	back_insert_iterator.hpp
 *
 *	@brief	back_insert_iterator の定義
 */

#ifndef HAMON_ITERATOR_BACK_INSERT_ITERATOR_HPP
#define HAMON_ITERATOR_BACK_INSERT_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

#include <iterator>

namespace hamon
{

using std::back_insert_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/output_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 25.5.2.2 Class template back_insert_iterator[back.insert.iterator]

template <typename Container>
class back_insert_iterator
{
protected:
	Container* container;

public:
	using iterator_category = hamon::output_iterator_tag;
	using value_type        = void;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = void;
	using reference         = void;
	using container_type    = Container;

	HAMON_CXX14_CONSTEXPR explicit
	back_insert_iterator(Container& x)
		HAMON_NOEXCEPT	// noexcept as an extension
		// [back.insert.iter.ops]/1
		: container(hamon::addressof(x))
	{}

	HAMON_CXX14_CONSTEXPR back_insert_iterator&
	operator=(typename Container::value_type const& value)
	{
		// [back.insert.iter.ops]/2
		container->push_back(value);
		// [back.insert.iter.ops]/3
		return *this;
	}

	HAMON_CXX14_CONSTEXPR back_insert_iterator&
	operator=(typename Container::value_type&& value)
	{
		// [back.insert.iter.ops]/4
		container->push_back(hamon::move(value));
		// [back.insert.iter.ops]/5
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	back_insert_iterator&
	operator*() HAMON_NOEXCEPT		// noexcept as an extension
	{
		// [back.insert.iter.ops]/6
		return *this;
	}

	HAMON_CXX14_CONSTEXPR back_insert_iterator&
	operator++() HAMON_NOEXCEPT		// noexcept as an extension
	{
		// [back.insert.iter.ops]/7
		return *this;
	}

	HAMON_CXX14_CONSTEXPR back_insert_iterator
	operator++(int) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [back.insert.iter.ops]/7
		return *this;
	}
};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_BACK_INSERT_ITERATOR_HPP
