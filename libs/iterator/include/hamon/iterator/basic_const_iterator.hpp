/**
 *	@file	basic_const_iterator.hpp
 *
 *	@brief	basic_const_iterator の定義
 */

#ifndef HAMON_ITERATOR_BASIC_CONST_ITERATOR_HPP
#define HAMON_ITERATOR_BASIC_CONST_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(__cpp_lib_ranges_as_const) && (__cpp_lib_ranges_as_const >= 202207L)

#define HAMON_USE_STD_BASIC_CONST_ITERATOR

namespace hamon
{

using std::basic_const_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/contiguous_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/concepts/common_with.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/totally_ordered_with.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/ranges/detail/different_from.hpp>
#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename I>
struct is_const_iterator : public hamon::false_type {};

// [const.iterators.iterator]/1
template <typename I>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
concept not_a_const_iterator = !hamon::detail::is_const_iterator<I>::value;
#else
using not_a_const_iterator = hamon::negation<hamon::detail::is_const_iterator<I>>;
#endif

template <HAMON_CONSTRAINED_PARAM(hamon::indirectly_readable, I)>
using iter_const_rvalue_reference_t =
	hamon::common_reference_t<hamon::iter_value_t<I> const&&, hamon::iter_rvalue_reference_t<I>>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// [const.iterators.types]/2
template <typename I>
struct basic_const_iterator_iterator_category
{};

template <hamon::forward_iterator I>
struct basic_const_iterator_iterator_category<I>
{
	using iterator_category =
		typename hamon::iterator_traits<I>::iterator_category;
};

#else

template <typename I, typename = void>
struct basic_const_iterator_iterator_category
{};

template <typename I>
struct basic_const_iterator_iterator_category<I,
	hamon::enable_if_t<hamon::forward_iterator_t<I>::value>>
{
	using iterator_category =
		typename hamon::iterator_traits<I>::iterator_category;
};

#endif

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iterator)>
class basic_const_iterator
	: public hamon::detail::basic_const_iterator_iterator_category<Iterator>
{
private:
	Iterator m_current = Iterator();

	using reference = hamon::iter_const_reference_t<Iterator>;
	using rvalue_reference =
		hamon::detail::iter_const_rvalue_reference_t<Iterator>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <hamon::input_iterator It2>
#else
	template <typename, typename>
#endif
	friend class basic_const_iterator;

public:
	// [const.iterators.types]

	using iterator_concept =
		hamon::conditional_t<hamon::contiguous_iterator_t<Iterator>::value,
			hamon::contiguous_iterator_tag,		// [const.iterators.types]/1.1
		hamon::conditional_t<hamon::random_access_iterator_t<Iterator>::value,
			hamon::random_access_iterator_tag,	// [const.iterators.types]/1.2
		hamon::conditional_t<hamon::bidirectional_iterator_t<Iterator>::value,
			hamon::bidirectional_iterator_tag,	// [const.iterators.types]/1.3
		hamon::conditional_t<hamon::forward_iterator_t<Iterator>::value,
			hamon::forward_iterator_tag,		// [const.iterators.types]/1.4
			hamon::input_iterator_tag			// [const.iterators.types]/1.5
	>>>>;
	// using iterator_category = see below;  // not always present
	using value_type = hamon::iter_value_t<Iterator>;
	using difference_type = hamon::iter_difference_t<Iterator>;

	// [const.iterators.ops]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	basic_const_iterator()
		requires hamon::default_initializable<Iterator>
		= default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, I, Iterator)>
	HAMON_CXX11_CONSTEXPR
	basic_const_iterator()
		: m_current(){}
#endif

	HAMON_CXX11_CONSTEXPR
	basic_const_iterator(Iterator current)
		: m_current(hamon::move(current))			// [const.iterators.ops]/1
	{}
	
	template <HAMON_CONSTRAINED_PARAM(hamon::convertible_to, Iterator, U)>
	HAMON_CXX11_CONSTEXPR
	basic_const_iterator(basic_const_iterator<U> current)
		: m_current(hamon::move(current.m_current))	// [const.iterators.ops]/2
	{}
	
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::different_from, basic_const_iterator, T),
		typename = hamon::enable_if_t<hamon::convertible_to_t<T, Iterator>::value>
	>
//		requires hamon::convertible_to<T, Iterator>
	HAMON_CXX11_CONSTEXPR
	basic_const_iterator(T&& current)
		: m_current(hamon::forward<T>(current))		// [const.iterators.ops]/3
	{}

	HAMON_CXX11_CONSTEXPR Iterator const&
	base() const & noexcept
	{
		// [const.iterators.ops]/4
		return m_current;
	}

	HAMON_CXX14_CONSTEXPR Iterator
	base() &&
	{
		// [const.iterators.ops]/5
		return hamon::move(m_current);
	}

	HAMON_CXX11_CONSTEXPR reference
	operator*() const
	{
		// [const.iterators.ops]/6
		return static_cast<reference>(*m_current);
	}

	// operator->()
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_CXX11_CONSTEXPR auto const*
	operator->() const
		requires hamon::is_lvalue_reference_v<hamon::iter_reference_t<Iterator>> &&
			hamon::same_as<hamon::remove_cvref_t<hamon::iter_reference_t<Iterator>>, value_type>
	{
		// [const.iterators.ops]/7
		if constexpr (hamon::contiguous_iterator_t<Iterator>::value)
		{
			return hamon::to_address(m_current);
		}
		else
		{
			return hamon::addressof(*m_current);
		}
	}
#else
private:
	template <HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, I)>
	HAMON_CXX11_CONSTEXPR auto
	op_arrow_impl(I current, hamon::detail::overload_priority<1>) const
	->decltype(hamon::to_address(current))
	{
		return hamon::to_address(current);
	}

	template <typename I>
	HAMON_CXX11_CONSTEXPR auto
	op_arrow_impl(I current, hamon::detail::overload_priority<0>) const
	->decltype(hamon::addressof(*current))
	{
		return hamon::addressof(*current);
	}

public:
	template <typename I = Iterator,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_lvalue_reference<hamon::iter_reference_t<I>>,
			hamon::same_as_t<hamon::remove_cvref_t<hamon::iter_reference_t<I>>, value_type>
		>::value>
	>
	HAMON_CXX11_CONSTEXPR auto
	operator->() const
	->hamon::add_pointer_t<
		hamon::add_const_t<
			hamon::remove_pointer_t<
				decltype(op_arrow_impl(m_current, hamon::detail::overload_priority<1>{}))>>>
	{
		return op_arrow_impl(m_current, hamon::detail::overload_priority<1>{});
	}
#endif

	HAMON_CXX14_CONSTEXPR basic_const_iterator&
	operator++()
	{
		// [const.iterators.ops]/8
		++m_current;
		return *this;
	}

	// operator++(int)
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_CXX14_CONSTEXPR void
	operator++(int)
	{
		// [const.iterators.ops]/9
		++m_current;
	}

	HAMON_CXX14_CONSTEXPR basic_const_iterator
	operator++(int)
		requires hamon::forward_iterator<Iterator>
	{
		// [const.iterators.ops]/10
		auto tmp = *this;
		++*this;
		return tmp;
	}
#else
private:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::forward_iterator, I, Iterator)>
	HAMON_CXX14_CONSTEXPR basic_const_iterator
	increment_impl(hamon::detail::overload_priority<1>)
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR void
	increment_impl(hamon::detail::overload_priority<0>)
	{
		++m_current;
	}

public:
	HAMON_CXX14_CONSTEXPR auto
	operator++(int)
	->decltype(increment_impl(hamon::detail::overload_priority<1>{}))
	{
		return increment_impl(hamon::detail::overload_priority<1>{});
	}
#endif

	template <HAMON_CONSTRAINED_PARAM_D(hamon::bidirectional_iterator, I, Iterator)>
	HAMON_CXX14_CONSTEXPR basic_const_iterator&
	operator--()
//		requires hamon::bidirectional_iterator<Iterator>
	{
		// [const.iterators.ops]/11
		--m_current;
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::bidirectional_iterator, I, Iterator)>
	HAMON_CXX14_CONSTEXPR basic_const_iterator
	operator--(int)
//		requires hamon::bidirectional_iterator<Iterator>
	{
		// [const.iterators.ops]/12
		auto tmp = *this;
		--*this;
		return tmp;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	HAMON_CXX14_CONSTEXPR basic_const_iterator&
	operator+=(difference_type n)
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/14
		m_current += n;
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	HAMON_CXX14_CONSTEXPR basic_const_iterator&
	operator-=(difference_type n)
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/14
		m_current -= n;
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	HAMON_CXX11_CONSTEXPR reference
	operator[](difference_type n) const
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/15
		return static_cast<reference>(m_current[n]);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iterator, S)>
	HAMON_CXX11_CONSTEXPR bool
	operator==(S const& s) const
	{
		// [const.iterators.ops]/16
		return m_current == s;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_CXX11_CONSTEXPR bool
	operator==(basic_const_iterator const& y) const
	{
		return m_current == y.m_current;
	}

	HAMON_CXX11_CONSTEXPR bool
	operator!=(basic_const_iterator const& y) const
	{
		return m_current != y.m_current;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::not_a_const_iterator, I)>
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(I const& x, basic_const_iterator const& y)
	{
		return x == y.m_current;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::not_a_const_iterator, I)>
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(I const& x, basic_const_iterator const& y)
	{
		return x != y.m_current;
	}
#endif

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	HAMON_CXX11_CONSTEXPR bool
	operator<(basic_const_iterator const& y) const
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/18
		return m_current < y.m_current;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	HAMON_CXX11_CONSTEXPR bool
	operator>(basic_const_iterator const& y) const
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/18
		return m_current > y.m_current;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	HAMON_CXX11_CONSTEXPR bool
	operator<=(basic_const_iterator const& y) const
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/18
		return m_current <= y.m_current;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	HAMON_CXX11_CONSTEXPR bool
	operator>=(basic_const_iterator const& y) const
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/18
		return m_current >= y.m_current;
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_CXX11_CONSTEXPR auto
	operator<=>(basic_const_iterator const& y) const
		requires hamon::random_access_iterator<Iterator> && hamon::three_way_comparable<Iterator>
	{
		// [const.iterators.ops]/18
		return m_current <=> y.m_current;
	}
#endif

private:
	// clang15までだとテンプレートが無限に再帰的インスタンス化されてしまう。
	// それを防ぐためにこれらのクラスが必要。

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::different_from, basic_const_iterator, I)>
	struct TotallyOrdered : public hamon::conjunction<
		hamon::random_access_iterator_t<Iterator>,
		hamon::totally_ordered_with_t<Iterator, I>
	>{};

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::different_from, basic_const_iterator, I)>
	struct ThreeWayComparable : public hamon::conjunction<
		hamon::random_access_iterator_t<Iterator>,
		hamon::totally_ordered_with_t<Iterator, I>,
		hamon::three_way_comparable_with_t<Iterator, I>
	>{};
#endif

	template <typename S>
	struct SizedSentinel : public hamon::conjunction<
		hamon::sized_sentinel_for_t<S, Iterator>
	>{};

public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::different_from, basic_const_iterator, I),
		typename = hamon::enable_if_t<TotallyOrdered<I>::value>>
	HAMON_CXX11_CONSTEXPR bool
	operator<(I const& y) const
//		requires hamon::random_access_iterator<Iterator> && hamon::totally_ordered_with<Iterator, I>
	{
		// [const.iterators.ops]/20
		return m_current < y;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::different_from, basic_const_iterator, I),
		typename = hamon::enable_if_t<TotallyOrdered<I>::value>>
	HAMON_CXX11_CONSTEXPR bool
	operator>(I const& y) const
//		requires hamon::random_access_iterator<Iterator> && hamon::totally_ordered_with<Iterator, I>
	{
		// [const.iterators.ops]/20
		return m_current > y;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::different_from, basic_const_iterator, I),
		typename = hamon::enable_if_t<TotallyOrdered<I>::value>>
	HAMON_CXX11_CONSTEXPR bool
	operator<=(I const& y) const
//		requires hamon::random_access_iterator<Iterator> && hamon::totally_ordered_with<Iterator, I>
	{
		// [const.iterators.ops]/20
		return m_current <= y;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::different_from, basic_const_iterator, I),
		typename = hamon::enable_if_t<TotallyOrdered<I>::value>>
	HAMON_CXX11_CONSTEXPR bool
	operator>=(I const& y) const
//		requires hamon::random_access_iterator<Iterator> && hamon::totally_ordered_with<Iterator, I>
	{
		// [const.iterators.ops]/20
		return m_current >= y;
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::different_from, basic_const_iterator, I),
		typename = hamon::enable_if_t<ThreeWayComparable<I>::value>>
	HAMON_CXX11_CONSTEXPR auto
	operator<=>(I const& y) const
//		requires hamon::random_access_iterator<Iterator> && hamon::totally_ordered_with<Iterator, I> &&
//			hamon::three_way_comparable_with<Iterator, I>
	{
		// [const.iterators.ops]/20
		return m_current <=> y;
	}
#endif

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::not_a_const_iterator, I),
		typename = hamon::enable_if_t<TotallyOrdered<I>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator<(I const& x, basic_const_iterator const& y)
//		requires hamon::random_access_iterator<Iterator> && hamon::totally_ordered_with<Iterator, I>
	{
		// [const.iterators.ops]/22
		return x < y.m_current;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::not_a_const_iterator, I),
		typename = hamon::enable_if_t<TotallyOrdered<I>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator>(I const& x, basic_const_iterator const& y)
//		requires hamon::random_access_iterator<Iterator> && hamon::totally_ordered_with<Iterator, I>
	{
		// [const.iterators.ops]/22
		return x > y.m_current;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::not_a_const_iterator, I),
		typename = hamon::enable_if_t<TotallyOrdered<I>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator<=(I const& x, basic_const_iterator const& y)
//		requires hamon::random_access_iterator<Iterator> && hamon::totally_ordered_with<Iterator, I>
	{
		// [const.iterators.ops]/22
		return x <= y.m_current;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::not_a_const_iterator, I),
		typename = hamon::enable_if_t<TotallyOrdered<I>::value>>
	friend HAMON_CXX11_CONSTEXPR bool
	operator>=(I const& x, basic_const_iterator const& y)
//		requires hamon::random_access_iterator<Iterator> && hamon::totally_ordered_with<Iterator, I>
	{
		// [const.iterators.ops]/22
		return x >= y.m_current;
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	friend HAMON_CXX11_CONSTEXPR basic_const_iterator
	operator+(basic_const_iterator const& i, difference_type n)
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/23
		return basic_const_iterator(i.m_current + n);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	friend HAMON_CXX11_CONSTEXPR basic_const_iterator
	operator+(difference_type n, basic_const_iterator const& i)
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/23
		return basic_const_iterator(i.m_current + n);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::random_access_iterator, I, Iterator)>
	friend HAMON_CXX11_CONSTEXPR basic_const_iterator
	operator-(basic_const_iterator const& i, difference_type n)
//		requires hamon::random_access_iterator<Iterator>
	{
		// [const.iterators.ops]/24
		return basic_const_iterator(i.m_current - n);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iterator, S)>
	HAMON_CXX11_CONSTEXPR difference_type
	operator-(S const& y) const
	{
		// [const.iterators.ops]/25
		return m_current - y;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::not_a_const_iterator, S),
		typename = hamon::enable_if_t<SizedSentinel<S>::value>>
//		requires hamon::sized_sentinel_for<S, Iterator>
	friend HAMON_CXX11_CONSTEXPR difference_type
	operator-(S const& x, basic_const_iterator const& y)
	{
		// [const.iterators.ops]/26
		return x - y.m_current;
	}

	friend HAMON_CXX11_CONSTEXPR rvalue_reference
	iter_move(basic_const_iterator const& i)
		noexcept(noexcept(static_cast<rvalue_reference>(ranges::iter_move(i.m_current))))
	{
		return static_cast<rvalue_reference>(ranges::iter_move(i.m_current));
	}
};

namespace detail
{

template <typename I>
struct is_const_iterator<basic_const_iterator<I>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

namespace HAMON_COMMON_TYPE_NAMESPACE
{

// [const.iterators.iterator], class template basic_const_iterator

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, hamon::common_with<T> U>
requires hamon::input_iterator<hamon::common_type_t<T, U>>
struct common_type<hamon::basic_const_iterator<T>, U>
{
	using type = hamon::basic_const_iterator<hamon::common_type_t<T, U>>;
};

template <typename T, hamon::common_with<T> U>
requires hamon::input_iterator<hamon::common_type_t<T, U>>
struct common_type<U, hamon::basic_const_iterator<T>>
{
	using type = hamon::basic_const_iterator<hamon::common_type_t<T, U>>;
};

template <typename T, hamon::common_with<T> U>
requires hamon::input_iterator<hamon::common_type_t<T, U>>
struct common_type<hamon::basic_const_iterator<T>, hamon::basic_const_iterator<U>>
{
	using type = hamon::basic_const_iterator<hamon::common_type_t<T, U>>;
};

#else

namespace detail
{

template <typename T, typename U, typename = void>
struct basic_const_iterator_common_type {};

template <typename T, typename U>
struct basic_const_iterator_common_type<T, U,
	hamon::enable_if_t<hamon::conjunction<
		hamon::common_with_t<T, U>,
		hamon::input_iterator_t<hamon::common_type_t<T, U>>
	>::value>>
{
	using type = hamon::basic_const_iterator<hamon::common_type_t<T, U>>;
};

}	// namespace detail

// Visual Studio 2019 だと、テンプレートの特殊化が曖昧になってしまう
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1938))
template <typename T, typename U>
struct common_type<hamon::basic_const_iterator<T>, U>
	: public detail::basic_const_iterator_common_type<T, U>
{};

template <typename T, typename U>
struct common_type<U, hamon::basic_const_iterator<T>>
	: public detail::basic_const_iterator_common_type<T, U>
{};
#endif

template <typename T, typename U>
struct common_type<hamon::basic_const_iterator<T>, hamon::basic_const_iterator<U>>
	: public detail::basic_const_iterator_common_type<T, U>
{};

#endif

}	// namespace HAMON_COMMON_TYPE_NAMESPACE

#endif

#endif // HAMON_ITERATOR_BASIC_CONST_ITERATOR_HPP
