/**
 *	@file	stack.hpp
 *
 *	@brief	stack の定義
 */

#ifndef HAMON_STACK_STACK_HPP
#define HAMON_STACK_STACK_HPP

#include <hamon/stack/stack_fwd.hpp>
#include <hamon/stack/config.hpp>

#if !defined(HAMON_USE_STD_STACK)

#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/compare/compare_three_way_result.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/has_append_range.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/deque.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/memory/uses_allocator.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/utility/to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail { struct stack_access; }

// 23.6.6 Class template stack[stack]

template <typename T, typename Container /*= deque<T>*/>
class stack
{
public:
	using value_type      = typename Container::value_type;
	using reference       = typename Container::reference;
	using const_reference = typename Container::const_reference;
	using size_type       = typename Container::size_type;
	using container_type  = Container;

protected:
	Container c;

public:
	HAMON_CXX11_CONSTEXPR
	stack() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<Container>::value)
		: c()
	{}

	HAMON_CXX11_CONSTEXPR explicit
	stack(Container const& cont) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<Container>::value)
		: c(cont)	// [stack.cons]/1
	{}

	HAMON_CXX11_CONSTEXPR explicit
	stack(Container&& cont) HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_move_constructible<Container>::value)
		: c(hamon::move(cont))	// [stack.cons]/2
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX11_CONSTEXPR
	stack(InputIterator first, InputIterator last) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<Container, InputIterator, InputIterator>::value)
		: c(first, last)	// [stack.cons]/3
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX11_CONSTEXPR
	stack(hamon::from_range_t, R&& rg)
		: c(hamon::ranges::to<Container>(hamon::forward<R>(rg)))	// [stack.cons]/4
	{}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [stack.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR explicit
	stack(Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<Container, Alloc const&>::value)
		: c(a)	// [stack.cons.alloc]/2
	{}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [stack.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	stack(Container const& cont, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<Container, Container const&, Alloc const&>::value)
		: c(cont, a)	// [stack.cons.alloc]/3
	{}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [stack.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	stack(Container&& cont, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<Container, Container&&, Alloc const&>::value)
		: c(hamon::move(cont), a)	// [stack.cons.alloc]/4
	{}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [stack.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	stack(stack const& s, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<Container, Container const&, Alloc const&>::value)
		: c(s.c, a)	// [stack.cons.alloc]/5
	{}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [stack.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	stack(stack&& s, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<Container, Container&&, Alloc const&>::value)
		: c(hamon::move(s.c), a)	// [stack.cons.alloc]/6
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>		// [stack.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	stack(InputIterator first, InputIterator last, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<Container, InputIterator, InputIterator, Alloc const&>::value)
		: c(first, last, a)	// [stack.cons.alloc]/7
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R),
		typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>		// [stack.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	stack(hamon::from_range_t, R&& rg, Alloc const& a)
		: c(hamon::ranges::to<Container>(hamon::forward<R>(rg), a))	// [stack.cons.alloc]/8
	{}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT_IF_EXPR(c.empty())	// noexcept as an extension
	{
		return c.empty();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT_IF_EXPR(c.size())	// noexcept as an extension
	{
		return c.size();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference
	top() HAMON_NOEXCEPT_IF_EXPR(c.back())	// noexcept as an extension
	{
		return c.back();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference
	top() const HAMON_NOEXCEPT_IF_EXPR(c.back())	// noexcept as an extension
	{
		return c.back();
	}

	HAMON_CXX14_CONSTEXPR void
	push(value_type const& x)
	{
		c.push_back(x);
	}

	HAMON_CXX14_CONSTEXPR void
	push(value_type&& x)
	{
		c.push_back(hamon::move(x));
	}

private:
	template <typename R, typename = hamon::enable_if_t<
		hamon::detail::has_append_range<Container, R>::value>>
	HAMON_CXX14_CONSTEXPR void
	push_range_impl(R&& rg, hamon::detail::overload_priority<1>)
	{
		c.append_range(hamon::forward<R>(rg));
	}

	template <typename R>
	HAMON_CXX14_CONSTEXPR void
	push_range_impl(R&& rg, hamon::detail::overload_priority<0>)
	{
		hamon::ranges::copy(rg, hamon::back_inserter(c));
	}

public:
	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	push_range(R&& rg)
	{
		// [stack.mod]/1
		push_range_impl(hamon::forward<R>(rg), hamon::detail::overload_priority<1>{});
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR auto//decltype(auto)
	emplace(Args&&... args)
	->decltype(c.emplace_back(hamon::forward<Args>(args)...))
	{
		return c.emplace_back(hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR void
	pop() HAMON_NOEXCEPT_IF_EXPR(c.pop_back())	// noexcept as an extension
	{
		c.pop_back();
	}

	HAMON_CXX14_CONSTEXPR void
	swap(stack& s) HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_swappable<Container>::value)
	{
		using std::swap;
		swap(c, s.c);
	}

private:
	friend struct detail::stack_access;
};

namespace detail
{

struct stack_access
{
	template <typename T, typename Container>
	static HAMON_CXX11_CONSTEXPR Container const&
	get_container(hamon::stack<T, Container> const& s)
	{
		return s.c;
	}
};

}	// namespace detail

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	typename Container,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Container>>				// [container.adaptors.general]/6.3
	>::value>
>
stack(Container)
-> stack<typename Container::value_type, Container>;

template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
stack(InputIterator, InputIterator)
-> stack<hamon::detail::iter_value_type<InputIterator>>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R)>
stack(hamon::from_range_t, R&&)
-> stack<hamon::ranges::range_value_t<R>>;

template <typename Container, typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Container>>,				// [container.adaptors.general]/6.3
		hamon::detail::simple_allocator_t<Allocator>,
		hamon::uses_allocator<Container, Allocator>									// [container.adaptors.general]/6.5
	>::value>
>
stack(Container, Allocator)
-> stack<typename Container::value_type, Container>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>								// [container.adaptors.general]/6.4
	>::value>,
	typename T = hamon::detail::iter_value_type<InputIterator>
>
stack(InputIterator, InputIterator, Allocator)
-> stack<T, hamon::deque<T, Allocator>>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>								// [container.adaptors.general]/6.4
	>::value>,
	typename T = hamon::ranges::range_value_t<R>
>
stack(hamon::from_range_t, R&&, Allocator)
-> stack<T, hamon::deque<T, Allocator>>;

#endif

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator==(stack<T, Container> const& x, stack<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() == hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::stack_access;
	return access::get_container(x) == access::get_container(y);	// [stack.ops]/1
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator!=(stack<T, Container> const& x, stack<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() != hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::stack_access;
	return access::get_container(x) != access::get_container(y);	// [stack.ops]/2
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<(stack<T, Container> const& x, stack<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() < hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::stack_access;
	return access::get_container(x) < access::get_container(y);	// [stack.ops]/3
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>(stack<T, Container> const& x, stack<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() > hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::stack_access;
	return access::get_container(x) > access::get_container(y);	// [stack.ops]/4
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<=(stack<T, Container> const& x, stack<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() <= hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::stack_access;
	return access::get_container(x) <= access::get_container(y);	// [stack.ops]/5
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>=(stack<T, Container> const& x, stack<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() >= hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::stack_access;
	return access::get_container(x) >= access::get_container(y);	// [stack.ops]/6
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, hamon::three_way_comparable Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR hamon::compare_three_way_result_t<Container>
operator<=>(stack<T, Container> const& x, stack<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() <=> hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::stack_access;
	return access::get_container(x) <=> access::get_container(y);	// [stack.ops]/7
}

#endif

template <typename T, typename Container,
	typename = hamon::enable_if_t<hamon::is_swappable<Container>::value>>	// [stack.special]/1
HAMON_CXX14_CONSTEXPR void
swap(stack<T, Container>& x, stack<T, Container>& y)
HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	x.swap(y);	// [stack.special]/2
}

template <typename T, typename Container, typename Alloc>
struct uses_allocator<stack<T, Container>, Alloc>
	: uses_allocator<Container, Alloc>::type {};

#if 0	// TODO

// [container.adaptors.format], formatter specialization for stack
template <typename charT, typename T, formattable<charT> Container>
struct formatter<stack<T, Container>, charT>;

#endif

}	// namespace hamon

#endif

#endif // HAMON_STACK_STACK_HPP
