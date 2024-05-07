/**
 *	@file	reverse_iterator.hpp
 *
 *	@brief	reverse_iterator の定義
 */

#ifndef HAMON_ITERATOR_REVERSE_ITERATOR_HPP
#define HAMON_ITERATOR_REVERSE_ITERATOR_HPP

#include <hamon/concepts/config.hpp>

#if (HAMON_CXX_STANDARD >= 17) && defined(HAMON_USE_STD_CONCEPTS) && defined(HAMON_USE_STD_RANGES_ITERATOR)
#    define HAMON_USE_STD_REVERSE_ITERATOR
#endif

#if defined(HAMON_USE_STD_REVERSE_ITERATOR)

#include <iterator>

namespace hamon
{

using std::reverse_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/disable_sized_sentinel_for.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/compare/compare_three_way_result.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 25.5.1.2 Class template reverse_iterator[reverse.iterator]

template <typename Iterator>
class reverse_iterator
{
private:
    template <typename>
    friend class reverse_iterator;

	using iter_cat = typename hamon::iterator_traits<Iterator>::iterator_category;

public:
	using iterator_type     = Iterator;
	
	// [reverse.iterator]/1
	using iterator_concept  = hamon::conditional_t<
		hamon::random_access_iterator_t<Iterator>::value,
		hamon::random_access_iterator_tag,	// [reverse.iterator]/1.1
		hamon::bidirectional_iterator_tag>;	// [reverse.iterator]/1.2
	
	// [reverse.iterator]/2
	using iterator_category = hamon::conditional_t<
		hamon::derived_from_t<iter_cat, hamon::random_access_iterator_tag>::value,
		hamon::random_access_iterator_tag,	// [reverse.iterator]/2.1
		iter_cat>;							// [reverse.iterator]/2.2
	
	using value_type        = hamon::iter_value_t<Iterator>;
	using difference_type   = hamon::iter_difference_t<Iterator>;
	using pointer           = typename hamon::iterator_traits<Iterator>::pointer;
	using reference         = hamon::iter_reference_t<Iterator>;

	// [reverse.iter.cons]/1
	HAMON_CXX11_CONSTEXPR reverse_iterator() = default;

	HAMON_CXX11_CONSTEXPR explicit
	reverse_iterator(Iterator x)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<Iterator>::value)
		// [reverse.iter.cons]/2
		: current(hamon::move(x))
	{}

	template <typename U,
		typename = hamon::enable_if_t<
			// [reverse.iter.cons]/3
			!hamon::is_same<U, Iterator>::value &&
			hamon::convertible_to_t<U const&, Iterator>::value>>
	HAMON_CXX11_CONSTEXPR
	reverse_iterator(reverse_iterator<U> const& u)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_constructible<Iterator, U const&>::value)
		// [reverse.iter.cons]/4
		: current(u.current)
	{}

	template <typename U,
		typename = hamon::enable_if_t<
			// [reverse.iter.cons]/5
			!hamon::is_same<U, Iterator>::value &&
			hamon::convertible_to_t<U const&, Iterator>::value &&
			hamon::assignable_from_t<Iterator&, U const&>::value>>
	HAMON_CXX14_CONSTEXPR reverse_iterator&
	operator=(reverse_iterator<U> const& u)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_assignable<Iterator&, U const&>::value)
	{
		// [reverse.iter.cons]/6
		current = u.current;
		// [reverse.iter.cons]/7
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	Iterator base() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<Iterator>::value)
	{
		// [reverse.iter.conv]/1
		return current;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR			// nodiscard as an extension
	reference operator*() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<Iterator>::value &&
		HAMON_NOEXCEPT_EXPR(*--(hamon::declval<Iterator&>())))
	{
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 110000)) &&	\
	defined(HAMON_HAS_CXX14_CONSTEXPR)
		// [reverse.iter.elem]/1
		Iterator tmp = current;
		return *--tmp;
#else
		// gcc10までだと、なぜか↑のコードがconstexprにならない
		return *hamon::ranges::prev(current);	// workaround
#endif
	}

private:
	template <typename I2,
		typename = hamon::enable_if_t<hamon::is_pointer<I2>::value>>
	HAMON_CXX11_CONSTEXPR pointer
	op_arrow_impl(hamon::detail::overload_priority<1>) const
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_convertible<I2, pointer>::value)
	{
		// [reverse.iter.elem]/2.1
		return hamon::ranges::prev(current);
	}

	template <typename I2,
		typename R = decltype(hamon::declval<I2>().operator->())>
	HAMON_CXX11_CONSTEXPR pointer
	op_arrow_impl(hamon::detail::overload_priority<0>) const
        HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_copy_constructible<I2>::value &&
			HAMON_NOEXCEPT_EXPR(--(hamon::declval<I2&>())) &&
			HAMON_NOEXCEPT_EXPR(pointer(hamon::declval<I2>().operator->())))
	{
		// [reverse.iter.elem]/2.2
		return hamon::ranges::prev(current).operator->();
	}

public:
	template <typename I2 = Iterator>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	operator->() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		op_arrow_impl<I2>(hamon::detail::overload_priority<1>{}))
	->decltype(op_arrow_impl<I2>(hamon::detail::overload_priority<1>{}))
	{
		return op_arrow_impl<I2>(hamon::detail::overload_priority<1>{});
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator&
	operator++() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		--hamon::declval<Iterator&>())
	{
		// [reverse.iter.nav]/3
		--current;
		// [reverse.iter.nav]/4
		return *this;
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator
	operator++(int) HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_copy_constructible<Iterator>::value &&
		HAMON_NOEXCEPT_EXPR(--hamon::declval<Iterator&>()))
	{
		// [reverse.iter.nav]/5
		reverse_iterator tmp = *this;
		--current;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator&
	operator--() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		++hamon::declval<Iterator&>())
	{
		// [reverse.iter.nav]/6
		++current;
		// [reverse.iter.nav]/7
		return *this;
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator
	operator--(int) HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_copy_constructible<Iterator>::value &&
		HAMON_NOEXCEPT_EXPR(++hamon::declval<Iterator&>()))
	{
		// [reverse.iter.nav]/8
		reverse_iterator tmp = *this;
		++current;
		return tmp;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reverse_iterator		// nodiscard as an extension
	operator+(difference_type n) const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		reverse_iterator(hamon::declval<Iterator const&>() - n))
	{
		// [reverse.iter.nav]/1
		return reverse_iterator(current - n);
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator&
	operator+=(difference_type n) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::declval<Iterator&>() -= n)
	{
		// [reverse.iter.nav]/9
		current -= n;
		// [reverse.iter.nav]/10
		return *this;
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reverse_iterator		// nodiscard as an extension
	operator-(difference_type n) const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		reverse_iterator(hamon::declval<Iterator const&>() + n))
	{
		// [reverse.iter.nav]/2
		return reverse_iterator(current + n);
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator&
	operator-=(difference_type n) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::declval<Iterator&>() += n)
	{
		// [reverse.iter.nav]/11
		current += n;
		// [reverse.iter.nav]/12
		return *this;
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference				// nodiscard as an extension
	operator[](difference_type n) const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		reference(hamon::declval<Iterator const&>()[n]))
	{
		// [reverse.iter.elem]/3
		return current[-n-1];
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::iter_rvalue_reference_t<Iterator>
	iter_move(reverse_iterator const& i) HAMON_NOEXCEPT_IF(
		// [reverse.iter.nonmember]/4
		hamon::is_nothrow_copy_constructible<Iterator>::value &&
		HAMON_NOEXCEPT_EXPR(hamon::ranges::iter_move(--hamon::declval<Iterator&>())))
	{
#if defined(HAMON_HAS_CXX14_CONSTEXPR)
		// [reverse.iter.nonmember]/3
		auto tmp = i.base();
		return hamon::ranges::iter_move(--tmp);
#else
		return hamon::ranges::iter_move(hamon::ranges::prev(i.base()));
#endif
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::indirectly_swappable, Iterator, Iterator2)>
	friend HAMON_CXX14_CONSTEXPR void
	iter_swap(
		reverse_iterator const& x,
		reverse_iterator<Iterator2> const& y)
		HAMON_NOEXCEPT_IF(		// [reverse.iter.nonmember]/6
			hamon::is_nothrow_copy_constructible<Iterator>::value &&
			hamon::is_nothrow_copy_constructible<Iterator2>::value &&
			HAMON_NOEXCEPT_EXPR(hamon::ranges::iter_swap(
				--hamon::declval<Iterator&>(),
				--hamon::declval<Iterator2&>())))
	{
		// [reverse.iter.nonmember]/5
		auto xtmp = x.base();
		auto ytmp = y.base();
		hamon::ranges::iter_swap(--xtmp, --ytmp);
	}

protected:
	Iterator current{};
};

template <typename Iterator1, typename Iterator2,
	// [reverse.iter.cmp]/1
	typename R = decltype(hamon::declval<Iterator1>() == hamon::declval<Iterator2>()),
	typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(
	reverse_iterator<Iterator1> const& x,
	reverse_iterator<Iterator2> const& y)
	HAMON_NOEXCEPT_IF_EXPR(bool(x.base() == y.base()))	// noexcept as an extension
{
	// [reverse.iter.cmp]/2
	return x.base() == y.base();
}

template <typename Iterator1, typename Iterator2,
	// [reverse.iter.cmp]/3
	typename R = decltype(hamon::declval<Iterator1>() != hamon::declval<Iterator2>()),
	typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(
	reverse_iterator<Iterator1> const& x,
	reverse_iterator<Iterator2> const& y)
	HAMON_NOEXCEPT_IF_EXPR(bool(x.base() != y.base()))	// noexcept as an extension
{
	// [reverse.iter.cmp]/4
	return x.base() != y.base();
}

template <typename Iterator1, typename Iterator2,
	// [reverse.iter.cmp]/5
	typename R = decltype(hamon::declval<Iterator1>() > hamon::declval<Iterator2>()),
	typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(
	reverse_iterator<Iterator1> const& x,
	reverse_iterator<Iterator2> const& y)
	HAMON_NOEXCEPT_IF_EXPR(bool(x.base() > y.base()))	// noexcept as an extension
{
	// [reverse.iter.cmp]/6
	return x.base() > y.base();
}

template <typename Iterator1, typename Iterator2,
	// [reverse.iter.cmp]/7
	typename R = decltype(hamon::declval<Iterator1>() < hamon::declval<Iterator2>()),
	typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(
	reverse_iterator<Iterator1> const& x,
	reverse_iterator<Iterator2> const& y)
	HAMON_NOEXCEPT_IF_EXPR(bool(x.base() < y.base()))	// noexcept as an extension
{
	// [reverse.iter.cmp]/8
	return x.base() < y.base();
}

template <typename Iterator1, typename Iterator2,
	// [reverse.iter.cmp]/9
	typename R = decltype(hamon::declval<Iterator1>() >= hamon::declval<Iterator2>()),
	typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(
	reverse_iterator<Iterator1> const& x,
	reverse_iterator<Iterator2> const& y)
	HAMON_NOEXCEPT_IF_EXPR(bool(x.base() >= y.base()))	// noexcept as an extension
{
	// [reverse.iter.cmp]/10
	return x.base() >= y.base();
}

template <typename Iterator1, typename Iterator2,
	// [reverse.iter.cmp]/11
	typename R = decltype(hamon::declval<Iterator1>() <= hamon::declval<Iterator2>()),
	typename = hamon::enable_if_t<hamon::convertible_to_t<R, bool>::value>
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(
	reverse_iterator<Iterator1> const& x,
	reverse_iterator<Iterator2> const& y)
	HAMON_NOEXCEPT_IF_EXPR(bool(x.base() <= y.base()))	// noexcept as an extension
{
	// [reverse.iter.cmp]/12
	return x.base() <= y.base();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename Iterator1, hamon::three_way_comparable_with<Iterator1> Iterator2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 110000))
hamon::compare_three_way_result_t<Iterator1, Iterator2>
#else
// gcc10までだと、なぜか↑のコードがinternal compiler errorになる
auto	// workaround
#endif
operator<=>(
	reverse_iterator<Iterator1> const& x,
	reverse_iterator<Iterator2> const& y)
	HAMON_NOEXCEPT_IF_EXPR(x.base() <=> y.base())	// noexcept as an extension
{
	// [reverse.iter.cmp]/13
	return y.base() <=> x.base();
}

#endif

template <typename Iterator1, typename Iterator2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
operator-(
	reverse_iterator<Iterator1> const& x,
	reverse_iterator<Iterator2> const& y)
	HAMON_NOEXCEPT_IF_EXPR(y.base() - x.base())	// noexcept as an extension
	-> decltype(y.base() - x.base())
{
	// [reverse.iter.nonmember]/1
	return y.base() - x.base();
}

template <typename Iterator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
reverse_iterator<Iterator>
operator+(
	hamon::iter_difference_t<Iterator> n,
	reverse_iterator<Iterator> const& x)
	HAMON_NOEXCEPT_IF_EXPR(x + n)	// noexcept as an extension
{
	// [reverse.iter.nonmember]/2
	return reverse_iterator<Iterator>(x.base() - n);
}

namespace reverse_iterator_detail
{
template <typename T, typename>
using disable_sized_sentinel_for_helper = T;
}	// namespace reverse_iterator_detail

template <typename Iterator1, typename Iterator2>
//	requires (!hamon::sized_sentinel_for<Iterator1, Iterator2>)
HAMON_SPECIALIZE_DISABLE_SIZED_SENTINEL_FOR(true,
	reverse_iterator<Iterator1>,
	reverse_iterator_detail::disable_sized_sentinel_for_helper<
		reverse_iterator<Iterator2>,
		hamon::enable_if_t<!hamon::sized_sentinel_for_t<Iterator1, Iterator2>::value>
	>);

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_REVERSE_ITERATOR_HPP
