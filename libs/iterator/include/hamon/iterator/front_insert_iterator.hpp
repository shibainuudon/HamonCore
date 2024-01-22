/**
 *	@file	front_insert_iterator.hpp
 *
 *	@brief	front_insert_iterator の定義
 */

#ifndef HAMON_ITERATOR_FRONT_INSERT_ITERATOR_HPP
#define HAMON_ITERATOR_FRONT_INSERT_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

#include <iterator>

namespace hamon
{

using std::front_insert_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/output_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 25.5.2.3 Class template front_insert_iterator[front.insert.iterator]

template <typename Container>
class front_insert_iterator
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
	front_insert_iterator(Container& x)
		HAMON_NOEXCEPT	// noexcept as an extension
		// [front.insert.iter.ops]/1
		: container(hamon::addressof(x))
	{}

	HAMON_CXX14_CONSTEXPR front_insert_iterator&
	operator=(typename Container::value_type const& value)
	{
		// [front.insert.iter.ops]/2
		container->push_front(value);
		// [front.insert.iter.ops]/3
		return *this;
	}

	HAMON_CXX14_CONSTEXPR front_insert_iterator&
	operator=(typename Container::value_type&& value)
	{
		// [front.insert.iter.ops]/4
		container->push_front(hamon::move(value));
		// [front.insert.iter.ops]/5
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	front_insert_iterator&
	operator*() HAMON_NOEXCEPT		// noexcept as an extension
	{
		// [front.insert.iter.ops]/6
		return *this;
	}

	HAMON_CXX14_CONSTEXPR front_insert_iterator&
	operator++() HAMON_NOEXCEPT		// noexcept as an extension
	{
		// [front.insert.iter.ops]/7
		return *this;
	}

	HAMON_CXX14_CONSTEXPR front_insert_iterator
	operator++(int) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [front.insert.iter.ops]/7
		return *this;
	}
};
}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_FRONT_INSERT_ITERATOR_HPP
