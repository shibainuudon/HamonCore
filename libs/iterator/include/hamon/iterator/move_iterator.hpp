/**
 *	@file	move_iterator.hpp
 *
 *	@brief	move_iterator の定義
 */

#ifndef HAMON_ITERATOR_MOVE_ITERATOR_HPP
#define HAMON_ITERATOR_MOVE_ITERATOR_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 17)
#    define HAMON_USE_STD_MOVE_ITERATOR
#endif

#if defined(HAMON_USE_STD_MOVE_ITERATOR)

#include <iterator>

namespace hamon
{

using std::move_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>

namespace hamon
{

template <typename Iter>
class move_iterator
{
private:
	Iter m_i;
public:
	using iterator_type     = Iter;
	using iterator_category = hamon::iterator_category<iterator_type>;
	using value_type        = hamon::iter_value_t<iterator_type>;
	using difference_type   = hamon::iter_difference_t<iterator_type>;
	using pointer           = iterator_type;
	using reference         = hamon::iter_rvalue_reference_t<iterator_type>;

	HAMON_CXX14_CONSTEXPR move_iterator(): m_i() {}
	HAMON_CXX14_CONSTEXPR explicit move_iterator(Iter x): m_i(x) {}
	template <typename U>
	HAMON_CXX14_CONSTEXPR move_iterator(move_iterator<U> const& other) : m_i(other.base()) {}
	HAMON_CXX14_CONSTEXPR Iter base() const { return m_i; }
	HAMON_CXX14_CONSTEXPR reference operator*() const { return static_cast<reference>(*m_i); }
//	HAMON_CXX14_CONSTEXPR pointer  operator->() const { return m_i; }
	HAMON_CXX14_CONSTEXPR move_iterator& operator++() { ++m_i; return *this; }
	HAMON_CXX14_CONSTEXPR move_iterator  operator++(int) { move_iterator tmp(*this); ++m_i; return tmp; }
	HAMON_CXX14_CONSTEXPR move_iterator& operator--() { --m_i; return *this; }
	HAMON_CXX14_CONSTEXPR move_iterator  operator--(int) { move_iterator tmp(*this); --m_i; return tmp; }
	HAMON_CXX14_CONSTEXPR move_iterator  operator+ (difference_type n) const { return move_iterator(m_i + n); }
	HAMON_CXX14_CONSTEXPR move_iterator& operator+=(difference_type n) { m_i += n; return *this; }
	HAMON_CXX14_CONSTEXPR move_iterator  operator- (difference_type n) const { return move_iterator(m_i - n); }
	HAMON_CXX14_CONSTEXPR move_iterator& operator-=(difference_type n) { m_i -= n; return *this; }
	HAMON_CXX14_CONSTEXPR reference operator[](difference_type n) const { return static_cast<reference>(m_i[n]); }
};

template <typename Iter1, typename Iter2>
inline HAMON_CXX14_CONSTEXPR bool
operator==(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
inline HAMON_CXX14_CONSTEXPR bool
operator<(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
inline HAMON_CXX14_CONSTEXPR bool
operator!=(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
inline HAMON_CXX14_CONSTEXPR bool
operator>(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
inline HAMON_CXX14_CONSTEXPR bool
operator>=(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() >= rhs.base();
}

template <typename Iter1, typename Iter2>
inline HAMON_CXX14_CONSTEXPR bool
operator<=(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
{
	return lhs.base() <= rhs.base();
}

template <typename Iter1, typename Iter2>
inline HAMON_CXX14_CONSTEXPR auto
operator-(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
-> decltype(lhs.base() - rhs.base())
{
	return lhs.base() - rhs.base();
}

template <typename Iter>
inline HAMON_CXX14_CONSTEXPR move_iterator<Iter>
operator+(typename move_iterator<Iter>::difference_type n, move_iterator<Iter> const& rhs)
{
	return move_iterator<Iter>(rhs.base() + n);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_MOVE_ITERATOR_HPP
