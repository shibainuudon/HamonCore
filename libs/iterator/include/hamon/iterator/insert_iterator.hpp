/**
 *	@file	insert_iterator.hpp
 *
 *	@brief	insert_iterator の定義
 */

#ifndef HAMON_ITERATOR_INSERT_ITERATOR_HPP
#define HAMON_ITERATOR_INSERT_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR) && \
	!defined(HAMON_APPLE_CLANG)	// apple clang の insert_iterator はコンパイルエラーになる

#define HAMON_USE_STD_INSERT_ITERATOR

#include <iterator>

namespace hamon
{

using std::insert_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/output_iterator_tag.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Container>
class insert_iterator
{
protected:
	using Iterator = hamon::ranges::iterator_t<Container>;

	Container*	container;
	Iterator	iter;

public:
	using iterator_category = hamon::output_iterator_tag;
	using value_type        = void;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = void;
	using reference         = void;
	using container_type    = Container;

	HAMON_CXX14_CONSTEXPR
	insert_iterator(Container& x, hamon::ranges::iterator_t<Container> i)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<Iterator>::value)
		// [insert.iter.ops]/1
		: container(hamon::addressof(x))
		, iter(hamon::move(i))
	{}

	HAMON_CXX14_CONSTEXPR insert_iterator&
	operator=(typename Container::value_type const& value)
	{
		// [insert.iter.ops]/2
		iter = container->insert(iter, value);
		++iter;
		// [insert.iter.ops]/3
		return *this;
	}

	HAMON_CXX14_CONSTEXPR insert_iterator&
	operator=(typename Container::value_type&& value)
	{
		// [insert.iter.ops]/4
		iter = container->insert(iter, hamon::move(value));
		++iter;
		// [insert.iter.ops]/5
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	insert_iterator&
	operator*() HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [insert.iter.ops]/6
		return *this;
	}

	HAMON_CXX14_CONSTEXPR insert_iterator&
	operator++() HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [insert.iter.ops]/7
		return *this;
	}

	HAMON_CXX14_CONSTEXPR insert_iterator&
	operator++(int) HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [insert.iter.ops]/7
		return *this;
	}
};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_INSERT_ITERATOR_HPP
