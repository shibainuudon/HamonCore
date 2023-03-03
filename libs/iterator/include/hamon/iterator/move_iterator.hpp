/**
 *	@file	move_iterator.hpp
 *
 *	@brief	move_iterator の定義
 */

#ifndef HAMON_ITERATOR_MOVE_ITERATOR_HPP
#define HAMON_ITERATOR_MOVE_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

#include <iterator>

namespace hamon
{

#define HAMON_USE_STD_MOVE_ITERATOR

using std::move_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/move_sentinel.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/compare/compare_three_way_result.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <iterator>
#include <utility>

namespace hamon
{

namespace detail
{

//If std::iterator_traits<Iter>::iterator_category is valid and denotes a type:
//
//* if std::iterator_traits<Iter>::iterator_category models
//     std::derived_from<std::random_access_iterator_tag>,
//     member iterator_category is std::random_access_iterator_tag.
//* Otherwise, member iterator_category is the same type as
//     std::iterator_traits<Iter>::iterator_category.
//* Otherwise, there is no member iterator_category.
template <typename Iter, typename = hamon::void_t<>>
struct move_iter_category_base {};

template <typename Iter>
//requires requires { typename hamon::iterator_traits<Iter>::iterator_category; }
struct move_iter_category_base<Iter
	, hamon::void_t<typename hamon::iterator_traits<Iter>::iterator_category>
>
{
	using iterator_category = hamon::conditional_t<
		hamon::derived_from_t<typename hamon::iterator_traits<Iter>::iterator_category, std::random_access_iterator_tag>::value,
		std::random_access_iterator_tag,
		typename hamon::iterator_traits<Iter>::iterator_category
	>;
};

// * std::random_access_iterator_tag, if Iter models
//   std::random_access_iterator. Otherwise,
// * std::bidirectional_iterator_tag, if Iter models
//   std::bidirectional_iterator. Otherwise,
// * std::forward_iterator_tag, if Iter models
//   std::forward_iterator. Otherwise,
// * std::input_iterator_tag.
template <typename Iter>
using move_iter_concept =
	hamon::conditional_t<
		hamon::random_access_iterator_t<Iter>::value,
		std::random_access_iterator_tag,
	hamon::conditional_t<
		hamon::bidirectional_iterator_t<Iter>::value,
		std::bidirectional_iterator_tag,
	hamon::conditional_t<
		hamon::forward_iterator_t<Iter>::value,
		std::forward_iterator_tag,
		std::input_iterator_tag
	>>>;

template <typename U, typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
concept move_iter_conv_constructible =
	(!hamon::is_same<U, Iter>::value) &&
	hamon::convertible_to<U const&, Iter>;
#else
using move_iter_conv_constructible = hamon::conjunction<
	hamon::negation<hamon::is_same<U, Iter>>,
	hamon::convertible_to<U const&, Iter>
>;
#endif

template <typename U, typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
concept move_iter_conv_assignable =
	(!hamon::is_same<U, Iter>::value) &&
	hamon::convertible_to<U const&, Iter> &&
	hamon::assignable_from<Iter&, U const&>;
#else
using move_iter_conv_assignable = hamon::conjunction<
	hamon::negation<hamon::is_same<U, Iter>>,
	hamon::convertible_to<U const&, Iter>,
	hamon::assignable_from<Iter&, U const&>
>;
#endif

}	// namespace detail

template <typename Iter>
class move_iterator
	: public detail::move_iter_category_base<Iter>
{
public:
	using iterator_type    = Iter;
	using iterator_concept = detail::move_iter_concept<Iter>;
	// iterator_category is inherited and not always present
	using value_type       = hamon::iter_value_t<Iter>;
	using difference_type  = hamon::iter_difference_t<Iter>;
	using pointer          = Iter;
	using reference        = hamon::iter_rvalue_reference_t<Iter>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_CXX14_CONSTEXPR
	move_iterator()
		requires std::is_constructible<Iter>::value	// extension
		= default;
#else
	template <typename I = Iter,
		typename = hamon::enable_if_t<std::is_constructible<I>::value>	// extension
	>
	HAMON_CXX14_CONSTEXPR
	move_iterator()
	HAMON_NOEXCEPT_IF(std::is_nothrow_default_constructible<I>::value)	// extension
		: m_current() {}
#endif

	HAMON_CXX14_CONSTEXPR
	explicit move_iterator(Iter i)
	HAMON_NOEXCEPT_IF(std::is_nothrow_move_constructible<Iter>::value)	// extension
		: m_current(std::move(i)) {}

	template <HAMON_CONSTRAINED_PARAM(detail::move_iter_conv_constructible, Iter, U)>
	HAMON_CXX14_CONSTEXPR
	move_iterator(move_iterator<U> const& u)
	HAMON_NOEXCEPT_IF((std::is_nothrow_constructible<Iter, U const&>::value))	// extension
		: m_current(u.base()) {}

	template <HAMON_CONSTRAINED_PARAM(detail::move_iter_conv_assignable, Iter, U)>
	HAMON_CXX14_CONSTEXPR move_iterator&
	operator=(move_iterator<U> const& u)
	HAMON_NOEXCEPT_IF((std::is_nothrow_assignable<Iter&, U const&>::value))	// extension
	{
		m_current = u.base();
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR Iter const&
	base() const & HAMON_NOEXCEPT
	{
		return m_current;
	}
	
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR Iter
	base() &&
	HAMON_NOEXCEPT_IF(std::is_nothrow_move_constructible<Iter>::value)	// extension
	{
		return std::move(m_current);
	}

	// DEPRECATED
	// HAMON_NODISCARD HAMON_CXX14_CONSTEXPR pointer
	// operator->() const { return m_current; }

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reference
	operator*() const
	HAMON_NOEXCEPT_IF_EXPR(ranges::iter_move(this->m_current))	// extension
	{
		return ranges::iter_move(m_current);
	}
	
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reference
	operator[](difference_type n) const
	HAMON_NOEXCEPT_IF_EXPR(ranges::iter_move(this->m_current + n))	// extension
	{
		return ranges::iter_move(m_current + n);
	}

	HAMON_CXX14_CONSTEXPR
	move_iterator& operator++()
	HAMON_NOEXCEPT_IF_EXPR(++this->m_current)	// extension
	{
		++m_current;
		return *this;
	}

private:
	HAMON_CXX14_CONSTEXPR move_iterator
	post_increment(std::true_type)
	HAMON_NOEXCEPT_IF(
		std::is_nothrow_copy_constructible<Iter>::value &&
		HAMON_NOEXCEPT_EXPR(++std::declval<Iter&>()))	// extension
	{
		move_iterator tmp(*this);
		++m_current;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR void
	post_increment(std::false_type)
	HAMON_NOEXCEPT_IF(
		HAMON_NOEXCEPT_EXPR(++std::declval<Iter&>()))	// extension
	{
		++m_current;
	}

public:
	HAMON_CXX14_CONSTEXPR auto
	operator++(int)
	HAMON_NOEXCEPT_IF_EXPR(post_increment(hamon::forward_iterator_t<Iter>{}))	// extension
	->decltype(post_increment(hamon::forward_iterator_t<Iter>{}))
	{
		return post_increment(hamon::forward_iterator_t<Iter>{});
	}

	HAMON_CXX14_CONSTEXPR move_iterator&
	operator--()
	HAMON_NOEXCEPT_IF_EXPR(--this->m_current)	// extension
	{
		--m_current;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR move_iterator
	operator--(int)
	HAMON_NOEXCEPT_IF(
		std::is_nothrow_copy_constructible<Iter>::value &&
		HAMON_NOEXCEPT_EXPR(--this->m_current))	// extension
	{
		move_iterator tmp(*this);
		--m_current;
		return tmp;
	}
	
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR move_iterator
	operator+(difference_type n) const
	HAMON_NOEXCEPT_IF_EXPR(move_iterator(this->m_current + n))	// extension
	{
		return move_iterator(m_current + n);
	}
	
	HAMON_CXX14_CONSTEXPR move_iterator&
	operator+=(difference_type n)
	HAMON_NOEXCEPT_IF_EXPR(this->m_current += n)	// extension
	{
		m_current += n;
		return *this;
	}
	
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR move_iterator
	operator-(difference_type n) const
	HAMON_NOEXCEPT_IF_EXPR(move_iterator(this->m_current - n))	// extension
	{
		return move_iterator(m_current - n);
	}
	
	HAMON_CXX14_CONSTEXPR move_iterator&
	operator-=(difference_type n)
	HAMON_NOEXCEPT_IF_EXPR(this->m_current -= n)	// extension
	{
		m_current -= n;
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent)>
	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR bool
	operator==(move_iterator const& lhs, move_sentinel<Sent> const& rhs)
	HAMON_NOEXCEPT_IF_EXPR(bool(lhs.base() == rhs.base()))	// extension
	{
		return lhs.base() == rhs.base();
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	template <HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent)>
	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR bool
	operator!=(move_iterator const& lhs, move_sentinel<Sent> const& rhs)
	HAMON_NOEXCEPT_IF_EXPR(bool(!(lhs == rhs)))	// extension
	{
		return !(lhs == rhs);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent)>
	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR bool
	operator==(move_sentinel<Sent> const& lhs, move_iterator const& rhs)
	HAMON_NOEXCEPT_IF_EXPR(bool(rhs == lhs))	// extension
	{
		return rhs == lhs;
	}
	
	template <HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent)>
	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR bool
	operator!=(move_sentinel<Sent> const& lhs, move_iterator const& rhs)
	HAMON_NOEXCEPT_IF_EXPR(bool(!(lhs == rhs)))	// extension
	{
		return !(lhs == rhs);
	}
#endif

	template <HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iter, Sent)>
	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<Iter>
	operator-(move_sentinel<Sent> const& lhs, move_iterator const& rhs)
	HAMON_NOEXCEPT_IF_EXPR(lhs.base() - rhs.base())	// extension
	{
		return lhs.base() - rhs.base();
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iter, Sent)>
	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<Iter>
	operator-(move_iterator const& lhs, move_sentinel<Sent> const& rhs)
	HAMON_NOEXCEPT_IF_EXPR(lhs.base() - rhs.base())	// extension
	{
		return lhs.base() - rhs.base();
	}

	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR hamon::iter_rvalue_reference_t<Iter>
	iter_move(move_iterator const& i)
	HAMON_NOEXCEPT_IF_EXPR(ranges::iter_move(i.m_current))
	{
		return ranges::iter_move(i.m_current);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::indirectly_swappable, Iter, It2)>
	friend HAMON_CXX14_CONSTEXPR void
	iter_swap(move_iterator const& lhs, move_iterator<It2> const& rhs)
	HAMON_NOEXCEPT_IF_EXPR(ranges::iter_swap(lhs.base(), rhs.base()))
	{
		return ranges::iter_swap(lhs.base(), rhs.base());
	}

private:
	Iter m_current{};
};

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR auto
operator==(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
HAMON_NOEXCEPT_IF_EXPR(bool(lhs.base() == rhs.base()))	// extension
-> decltype(bool(lhs.base() == rhs.base()))
{
	return lhs.base() == rhs.base();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR auto
operator!=(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
HAMON_NOEXCEPT_IF_EXPR(bool(!(lhs == rhs)))	// extension
-> decltype(bool(!(lhs == rhs)))
{
	return !(lhs == rhs);
}
#endif

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR auto
operator<(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
HAMON_NOEXCEPT_IF_EXPR(bool(lhs.base() < rhs.base()))	// extension
-> decltype(bool(lhs.base() < rhs.base()))
{
	return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR auto
operator>(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
HAMON_NOEXCEPT_IF_EXPR(bool(rhs < lhs))	// extension
-> decltype(bool(rhs < lhs))
{
	return rhs < lhs;
}

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR auto
operator<=(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
HAMON_NOEXCEPT_IF_EXPR(bool(!(rhs < lhs)))	// extension
-> decltype(bool(!(rhs < lhs)))
{
	return !(rhs < lhs);
}

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR auto
operator>=(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
HAMON_NOEXCEPT_IF_EXPR(bool(!(lhs < rhs)))	// extension
-> decltype(bool(!(lhs < rhs)))
{
	return !(lhs < rhs);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename Iter1, HAMON_CONSTRAINED_PARAM(hamon::three_way_comparable_with, Iter1, Iter2)>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR auto
operator<=>(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
HAMON_NOEXCEPT_IF_EXPR(lhs.base() <=> rhs.base())	// extension
-> hamon::compare_three_way_result_t<Iter1, Iter2>
{
	return lhs.base() <=> rhs.base();
}
#endif

template <typename Iter1, typename Iter2>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR auto
operator-(move_iterator<Iter1> const& lhs, move_iterator<Iter2> const& rhs)
HAMON_NOEXCEPT_IF_EXPR(lhs.base() - rhs.base())	// extension
->decltype(lhs.base() - rhs.base())
{
	return lhs.base() - rhs.base();
}

template <typename Iter>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR move_iterator<Iter>
operator+(hamon::iter_difference_t<Iter> n, move_iterator<Iter> const& x)
HAMON_NOEXCEPT_IF_EXPR(x + n)	// extension
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires requires { { x.base() + n } -> hamon::same_as<Iter>; }
#endif
{
	return x + n;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_MOVE_ITERATOR_HPP
