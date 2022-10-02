/**
 *	@file	reverse_iterator.hpp
 *
 *	@brief	reverse_iterator の定義
 */

#ifndef HAMON_ITERATOR_REVERSE_ITERATOR_HPP
#define HAMON_ITERATOR_REVERSE_ITERATOR_HPP

#include <hamon/concepts/config.hpp>

#if (HAMON_CXX_STANDARD >= 17) && defined(HAMON_USE_STD_CONCEPTS)
#    define HAMON_USE_STD_REVERSE_ITERATOR
#endif

#if defined(HAMON_USE_STD_REVERSE_ITERATOR)

#include <iterator>

namespace hamon
{

using std::reverse_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/prev.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/compare/compare_three_way_result.hpp>
#include <hamon/memory/addressof.hpp>

namespace hamon
{

template <typename Iter>
class reverse_iterator
{
public:
	using iterator_type     = Iter;
	using iterator_category = typename hamon::iterator_traits<Iter>::iterator_category;
	using value_type        = hamon::iter_value_t<Iter>;
	using difference_type   = hamon::iter_difference_t<Iter>;
	using pointer           = typename hamon::iterator_traits<Iter>::pointer;
	using reference         = hamon::iter_reference_t<Iter>;

	HAMON_CONSTEXPR reverse_iterator()
		: current() {}

	HAMON_CONSTEXPR explicit reverse_iterator(iterator_type x)
		: current(x) {}

	template <typename U>
	HAMON_CONSTEXPR reverse_iterator(reverse_iterator<U> const& u)
		: current(u.base()) {}

	template <typename U>
	HAMON_CXX14_CONSTEXPR reverse_iterator&
	operator=(reverse_iterator<U> const& u)
	{
		current = u.base(); return *this;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR iterator_type base() const
	{
		return current;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR reference operator*() const
	{
		return *hamon::prev(current);
	}

	HAMON_NODISCARD HAMON_CONSTEXPR pointer operator->() const
	{
		return hamon::addressof(operator*());
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator& operator++()
	{
		--current;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator operator++(int)
	{
		reverse_iterator tmp(*this);
		--current;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator& operator--()
	{
		++current;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator operator--(int)
	{
		reverse_iterator tmp(*this);
		++current;
		return tmp;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR reverse_iterator
	operator+ (difference_type n) const
	{
		return reverse_iterator(current - n);
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator&
	operator+=(difference_type n)
	{
		current -= n;
		return *this;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR reverse_iterator
	operator- (difference_type n) const
	{
		return reverse_iterator(current + n);
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator&
	operator-=(difference_type n)
	{
		current += n;
		return *this;
	}

	HAMON_NODISCARD HAMON_CONSTEXPR reference
	operator[](difference_type n) const
	{
		return *(*this + n);
	}

protected:
	Iter current;
};

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator==(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return rhs.base() == lhs.base();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON) && defined(HAMON_HAS_STD_COMPARE)

template <typename Iter1, hamon::three_way_comparable_with<Iter1> Iter2>
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::compare_three_way_result_t<Iter1, Iter2>
operator<=>(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return rhs.base() <=> lhs.base();
}

#else

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return rhs.base() < lhs.base();
}

#endif

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator!=(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return rhs.base() != lhs.base();
}

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return rhs.base() > lhs.base();
}

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator>=(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return rhs.base() >= lhs.base();
}

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
operator<=(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
{
	return rhs.base() <= lhs.base();
}

#endif

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CONSTEXPR auto
operator-(reverse_iterator<Iter1> const& lhs, reverse_iterator<Iter2> const& rhs)
->decltype(rhs.base() - lhs.base())
{
	return rhs.base() - lhs.base();
}

template <class Iter>
HAMON_NODISCARD inline HAMON_CONSTEXPR reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n, reverse_iterator<Iter> const& it)
{
	return reverse_iterator<Iter>(it.base() - n);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_REVERSE_ITERATOR_HPP
