/**
 *	@file	counted_iterator.hpp
 *
 *	@brief	counted_iterator の定義
 */

#ifndef HAMON_ITERATOR_COUNTED_ITERATOR_HPP
#define HAMON_ITERATOR_COUNTED_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::counted_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/detail/iter_traits.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/detail/dereferenceable.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/common_with.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace detail
{

template <typename I, typename = void>
struct counted_iterator_value_type_base {};

template <typename I>
struct counted_iterator_value_type_base<I, hamon::enable_if_t<hamon::indirectly_readable_t<I>::value>>
{
	using value_type = hamon::iter_value_t<I>;
};

template <typename I, typename = void>
struct counted_iterator_iterator_concept_base {};

template <typename I>
struct counted_iterator_iterator_concept_base<I, hamon::void_t<typename I::iterator_concept>>
{
	using iterator_concept = typename I::iterator_concept;
};

template <typename I, typename = void>
struct counted_iterator_iterator_category_base {};

template <typename I>
struct counted_iterator_iterator_category_base<I, hamon::void_t<typename I::iterator_category>>
{
	using iterator_category = typename I::iterator_category;
};

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, I)>
class counted_iterator
	: public detail::counted_iterator_value_type_base<I>
	, public detail::counted_iterator_iterator_concept_base<I>
	, public detail::counted_iterator_iterator_category_base<I>
{
public:
	using iterator_type = I;
	//using value_type = hamon::iter_value_t<I>;	// present only if I models indirectly_readable
	using difference_type = hamon::iter_difference_t<I>;
	//using iterator_concept = typename I::iterator_concept;      // present only if the qualified-id I​::​iterator_concept is valid and denotes a type
	//using iterator_category = typename I::iterator_category;    // present only if the qualified-id I​::​iterator_category is valid and denotes a type
	
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_CXX11_CONSTEXPR counted_iterator()
		requires hamon::default_initializable<I> = default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, I2, I)>
	HAMON_CXX11_CONSTEXPR
	counted_iterator()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<I>::value)
	{}
#endif
	
	HAMON_CXX11_CONSTEXPR
	counted_iterator(I i, difference_type n)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<I>::value)	// noexcept as an extension
		// [counted.iter.const]/2
		: m_current(hamon::move(i))
		, m_length(n)
	{
#if HAMON_CXX_STANDARD >= 14
		// [counted.iter.const]/1
		HAMON_ASSERT(n >= 0);
#endif
	}

	template <typename I2,
		typename = hamon::enable_if_t<
			hamon::convertible_to_t<I2 const&, I>::value>>
	HAMON_CXX11_CONSTEXPR
	counted_iterator(counted_iterator<I2> const& x)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_constructible<I, I2 const&>::value)
		// [counted.iter.const]/3
		: m_current(x.base())
		, m_length(x.count())
	{}

	template <typename I2,
		typename = hamon::enable_if_t<
			hamon::assignable_from_t<I&, I2 const&>::value>>
	HAMON_CXX14_CONSTEXPR counted_iterator&
	operator=(counted_iterator<I2> const& x)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_assignable<I&, I2 const&>::value)
	{
		// [counted.iter.const]/4
		m_current = x.base();
		m_length = x.count();

		// [counted.iter.const]/5
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	I const& base() const& HAMON_NOEXCEPT
	{
		// [counted.iter.access]/1
		return m_current;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	I base() && HAMON_NOEXCEPT_IF(			// noexcept as an extension
		hamon::is_nothrow_move_constructible<I>::value)
	{
		// [counted.iter.access]/2
		return hamon::move(m_current);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	difference_type count() const HAMON_NOEXCEPT
	{
		// [counted.iter.access]/3
		return m_length;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto operator*()
	HAMON_NOEXCEPT_IF_EXPR(*hamon::declval<I>())	// noexcept as an extension
	->decltype(*hamon::declval<I>())
	{
		// [counted.iter.elem]/1
		HAMON_ASSERT(m_length > 0);

		// [counted.iter.elem]/2
		return *m_current;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::detail::dereferenceable, I2, I const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto operator*() const
	HAMON_NOEXCEPT_IF_EXPR(*hamon::declval<I2>())	// noexcept as an extension
	->decltype(*hamon::declval<I2>())
	{
		return
			HAMON_ASSERT(m_length > 0),	// [counted.iter.elem]/1
			*m_current;	// [counted.iter.elem]/2
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::contiguous_iterator, I2, I)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto operator->() const HAMON_NOEXCEPT
	->decltype(hamon::to_address(hamon::declval<I2>()))
	{
		// [counted.iter.elem]/3
		return hamon::to_address(m_current);
	}

	HAMON_CXX14_CONSTEXPR counted_iterator& operator++()
	HAMON_NOEXCEPT_IF_EXPR(++hamon::declval<I&>())	// noexcept as an extension
	{
		// [counted.iter.nav]/1
		HAMON_ASSERT(m_length > 0);

		// [counted.iter.nav]/2
		++m_current;
		--m_length;
		return *this;
	}

private:
	HAMON_CXX20_CONSTEXPR auto
	increment_impl(hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_IF_EXPR(hamon::declval<I&>()++)	// noexcept as an extension
	->decltype(hamon::declval<I&>()++)
	{
		// [counted.iter.nav]/3
		HAMON_ASSERT(m_length > 0);

		// [counted.iter.nav]/4
		--m_length;
#if !defined(HAMON_NO_EXCEPTIONS)
		try
		{
			return m_current++;
		}
		catch (...)
		{
			++m_length;
			throw;
		}
#else
		return m_current++;
#endif
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::forward_iterator, I2, I)>
	HAMON_CXX14_CONSTEXPR counted_iterator
	increment_impl(hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_copy_constructible<I>::value &&
		HAMON_NOEXCEPT_EXPR(++hamon::declval<I&>()))
	{
		// [counted.iter.nav]/5
		counted_iterator tmp = *this;
		++*this;
		return tmp;
	}

public:
	HAMON_CXX14_CONSTEXPR
	auto operator++(int)
	HAMON_NOEXCEPT_IF_EXPR(increment_impl(hamon::detail::overload_priority<1>{}))	// noexcept as an extension
	->decltype(increment_impl(hamon::detail::overload_priority<1>{}))
	{
		return increment_impl(hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::bidirectional_iterator, I2, I)>
	HAMON_CXX14_CONSTEXPR
	counted_iterator& operator--()
	HAMON_NOEXCEPT_IF_EXPR(--hamon::declval<I2&>())	// noexcept as an extension
	{
		// [counted.iter.nav]/6
		--m_current;
		++m_length;
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::bidirectional_iterator, I2, I)>
	HAMON_CXX14_CONSTEXPR
	counted_iterator operator--(int)
	HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_copy_constructible<I2>::value &&
		HAMON_NOEXCEPT_EXPR(--hamon::declval<I2&>()))
	{
		// [counted.iter.nav]/7
		counted_iterator tmp = *this;
		--*this;
		return tmp;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I2, I)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	counted_iterator operator+(difference_type n) const
	HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_move_constructible<I2>::value &&
		HAMON_NOEXCEPT_EXPR(hamon::declval<I2&>() + n))
	{
		// [counted.iter.nav]/8
		return counted_iterator(m_current + n, m_length - n);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I2, I)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR counted_iterator	// nodiscard as an extension
	operator+(difference_type n, counted_iterator const& x)
	HAMON_NOEXCEPT_IF_EXPR(x + n)	// noexcept as an extension
	{
		// [counted.iter.nav]/9
		return x + n;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I2, I)>
	HAMON_CXX14_CONSTEXPR counted_iterator&
	operator+=(difference_type n)
	HAMON_NOEXCEPT_IF_EXPR(hamon::declval<I2&>() += n)	// noexcept as an extension
	{
		// [counted.iter.nav]/10
		HAMON_ASSERT(n <= m_length);

		// [counted.iter.nav]/11
		m_current += n;
		m_length -= n;
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I2, I)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR counted_iterator	// nodiscard as an extension
	operator-(difference_type n) const
	HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_move_constructible<I2>::value &&
		HAMON_NOEXCEPT_EXPR(hamon::declval<I2&>() - n))
	{
		// [counted.iter.nav]/12
		return counted_iterator(m_current - n, m_length + n);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::common_with, I, I2)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR hamon::iter_difference_t<I2>	// nodiscard as an extension
	operator-(counted_iterator const& x, counted_iterator<I2> const& y)
	HAMON_NOEXCEPT		// noexcept as an extension
	{
		return
			HAMON_ASSERT(SameSequence(x, y)),	// [counted.iter.nav]/13
			(y.m_length - x.m_length);			// [counted.iter.nav]/14
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type	// nodiscard as an extension
	operator-(counted_iterator const& x, hamon::default_sentinel_t)
	HAMON_NOEXCEPT		// noexcept as an extension
	{
		// [counted.iter.nav]/15
		return -x.m_length;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type	// nodiscard as an extension
	operator-(hamon::default_sentinel_t, counted_iterator const& y)
	HAMON_NOEXCEPT		// noexcept as an extension
	{
		// [counted.iter.nav]/16
		return y.m_length;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I2, I)>
	HAMON_CXX14_CONSTEXPR counted_iterator&
	operator-=(difference_type n)
	HAMON_NOEXCEPT_IF_EXPR(hamon::declval<I2&>() -= n)	// noexcept as an extension
	{
		// [counted.iter.nav]/17
		HAMON_ASSERT(-n <= m_length);

		// [counted.iter.nav]/18
		m_current -= n;
		m_length += n;
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I2, I)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	operator[](difference_type n) const
	HAMON_NOEXCEPT_IF_EXPR(hamon::declval<I2&>()[n])	// noexcept as an extension
	->decltype(hamon::declval<I2&>()[n])
	{
		return
			HAMON_ASSERT(n < m_length),	// [counted.iter.elem]/4
			m_current[n];				// [counted.iter.elem]/5
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::common_with, I, I2)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator==(counted_iterator const& x, counted_iterator<I2> const& y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(SameSequence(x, y)),	// [counted.iter.cmp]/1
			(x.m_length == y.m_length);			// [counted.iter.cmp]/2
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator==(counted_iterator const& x, hamon::default_sentinel_t)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [counted.iter.cmp]/3
		return x.m_length == 0;
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	template <HAMON_CONSTRAINED_PARAM(hamon::common_with, I, I2)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR hamon::strong_ordering	// nodiscard as an extension
	operator<=>(counted_iterator const& x, counted_iterator<I2> const& y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [counted.iter.cmp]/4
		HAMON_ASSERT(SameSequence(x, y));

		// [counted.iter.cmp]/5
		return y.m_length <=> x.m_length;
	}
#else
	template <HAMON_CONSTRAINED_PARAM(hamon::common_with, I, I2)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator!=(counted_iterator const& x, counted_iterator<I2> const& y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		return !(x == y);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::common_with, I, I2)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator<(counted_iterator const& x, counted_iterator<I2> const& y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		return y.m_length < x.m_length;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::common_with, I, I2)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator>(counted_iterator const& x, counted_iterator<I2> const& y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		return y < x;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::common_with, I, I2)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator<=(counted_iterator const& x, counted_iterator<I2> const& y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		return !(x > y);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::common_with, I, I2)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator>=(counted_iterator const& x, counted_iterator<I2> const& y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		return !(x < y);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator!=(counted_iterator const& x, hamon::default_sentinel_t y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		return !(x == y);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator==(hamon::default_sentinel_t x, counted_iterator const& y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		return y == x;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	operator!=(hamon::default_sentinel_t x, counted_iterator const& y)
	HAMON_NOEXCEPT	// noexcept as an extension
	{
		return !(x == y);
	}
#endif

	template <HAMON_CONSTRAINED_PARAM_D(hamon::input_iterator, I2, I)>
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::iter_rvalue_reference_t<I>
	iter_move(counted_iterator const& i)
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_move(i.base()))
	{
		return
			HAMON_ASSERT(i.count() > 0),		// [counted.iter.cust]/1
			hamon::ranges::iter_move(i.base());	// [counted.iter.cust]/2
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::indirectly_swappable, I, I2)>
	friend HAMON_CXX14_CONSTEXPR void
	iter_swap(counted_iterator const& x, counted_iterator<I2> const& y)
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iter_swap(x.base(), y.base()))
	{
		// [counted.iter.cust]/3
		HAMON_ASSERT(x.count() > 0 && y.count() > 0);

		// [counted.iter.cust]/4
		hamon::ranges::iter_swap(x.base(), y.base());
	}

private:
	I m_current = I();
	difference_type m_length = 0;

private:
	// [counted.iterator]/3
	template <typename I1, typename I2, typename CD>
	static HAMON_CXX11_CONSTEXPR bool
	SameSequenceImpl2(counted_iterator<I1> const& i1, counted_iterator<I2> const& i2, CD diff)
	{
		using CI = hamon::common_type_t<I1, I2>;
		return (diff < 0) ?
			hamon::ranges::next(static_cast<CI>(i2.base()), -diff) == static_cast<CI>(i1.base()) :
			hamon::ranges::next(static_cast<CI>(i1.base()),  diff) == static_cast<CI>(i2.base());
	}

	template <typename I1, typename I2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::forward_iterator_t<I1>,
			hamon::forward_iterator_t<I2>
		>::value>>
	static HAMON_CXX11_CONSTEXPR bool
	SameSequenceImpl(counted_iterator<I1> const& i1, counted_iterator<I2> const& i2, hamon::detail::overload_priority<1>)
	{
		using CD = hamon::common_type_t<hamon::iter_difference_t<I1>, hamon::iter_difference_t<I2>>;
		return SameSequenceImpl2(i1, i2, static_cast<CD>(i1.count()) - static_cast<CD>(i2.count()));
	}

	template <typename I1, typename I2>
	static HAMON_CXX11_CONSTEXPR bool
	SameSequenceImpl(counted_iterator<I1> const&, counted_iterator<I2> const&, hamon::detail::overload_priority<0>)
	{
		return true;
	}

	template <typename I1, typename I2>
	static HAMON_CXX11_CONSTEXPR bool
	SameSequence(counted_iterator<I1> const& i1, counted_iterator<I2> const& i2)
	{
		return SameSequenceImpl(i1, i2, hamon::detail::overload_priority<1>{});
	}
};

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::input_iterator I>
requires hamon::same_as<hamon::detail::iter_traits<I>, iterator_traits<I>>   // see [iterator.concepts.general]
struct iterator_traits<counted_iterator<I>> : iterator_traits<I>
#else
template <typename I>
struct iterator_traits<
	detail::enable_iterator_traits_helper<
		counted_iterator<I>,
		hamon::enable_if_t<hamon::conjunction<
			hamon::input_iterator_t<I>,
			hamon::same_as_t<hamon::detail::iter_traits<I>, iterator_traits<I>>
		>::value>>> : iterator_traits<I>
#endif
{
	using pointer = hamon::conditional_t<
		hamon::contiguous_iterator_t<I>::value,
			hamon::add_pointer_t<hamon::iter_reference_t<I>>,
			void
	>;
};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_COUNTED_ITERATOR_HPP
