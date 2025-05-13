/**
 *	@file	queue.hpp
 *
 *	@brief	queue の定義
 */

#ifndef HAMON_QUEUE_QUEUE_HPP
#define HAMON_QUEUE_QUEUE_HPP

#include <hamon/queue/queue_fwd.hpp>
#include <hamon/queue/config.hpp>

#if !defined(HAMON_USE_STD_QUEUE)

#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/compare/compare_three_way_result.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/swap.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/has_append_range.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/deque.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
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
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <memory>	// uses_allocator

namespace hamon
{

namespace detail { struct queue_access; }

// 23.6.3 Class template queue[queue]
template <typename T, typename Container /*= deque<T>*/>
class queue
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
	queue() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<container_type>::value)
		: c()
	{}

	HAMON_CXX11_CONSTEXPR explicit
	queue(container_type const& cont) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<container_type>::value)
		: c(cont)	// [queue.cons]/1
	{}

	HAMON_CXX11_CONSTEXPR explicit
	queue(container_type&& cont) HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_move_constructible<container_type>::value)
		: c(hamon::move(cont))	// [queue.cons]/2
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX11_CONSTEXPR
	queue(InputIterator first, InputIterator last) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, InputIterator, InputIterator>::value)
		: c(first, last)	// [queue.cons]/3
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX11_CONSTEXPR
	queue(hamon::from_range_t, R&& rg)
		: c(hamon::ranges::to<Container>(hamon::forward<R>(rg)))	// [queue.cons]/4
	{}

	template <typename Alloc, typename = hamon::enable_if_t<std::uses_allocator<container_type, Alloc>::value>>	// [queue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR explicit
	queue(Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, Alloc const&>::value)
		: c(a)	// [queue.cons.alloc]/2
	{}

	template <typename Alloc, typename = hamon::enable_if_t<std::uses_allocator<container_type, Alloc>::value>>	// [queue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	queue(container_type const& cont, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, container_type const&, Alloc const&>::value)
		: c(cont, a)	// [queue.cons.alloc]/3
	{}

	template <typename Alloc, typename = hamon::enable_if_t<std::uses_allocator<container_type, Alloc>::value>>	// [queue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	queue(container_type&& cont, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, container_type&&, Alloc const&>::value)
		: c(hamon::move(cont), a)	// [queue.cons.alloc]/4
	{}

	template <typename Alloc, typename = hamon::enable_if_t<std::uses_allocator<container_type, Alloc>::value>>	// [queue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	queue(queue const& q, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, container_type const&, Alloc const&>::value)
		: c(q.c, a)	// [queue.cons.alloc]/5
	{}

	template <typename Alloc, typename = hamon::enable_if_t<std::uses_allocator<container_type, Alloc>::value>>	// [queue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	queue(queue&& q, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, container_type&&, Alloc const&>::value)
		: c(hamon::move(q.c), a)	// [queue.cons.alloc]/6
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc, typename = hamon::enable_if_t<std::uses_allocator<container_type, Alloc>::value>>	// [queue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	queue(InputIterator first, InputIterator last, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, InputIterator, InputIterator, Alloc const&>::value)
		: c(first, last, a)		// [queue.cons.alloc]/7
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R),
		typename Alloc, typename = hamon::enable_if_t<std::uses_allocator<container_type, Alloc>::value>>	// [queue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	queue(hamon::from_range_t, R&& rg, Alloc const& a)
		: c(hamon::ranges::to<Container>(hamon::forward<R>(rg), a))	// [queue.cons.alloc]/8
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
	front() HAMON_NOEXCEPT_IF_EXPR(c.front())	// noexcept as an extension
	{
		return c.front();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference
	front() const HAMON_NOEXCEPT_IF_EXPR(c.front())	// noexcept as an extension
	{
		return c.front();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference
	back() HAMON_NOEXCEPT_IF_EXPR(c.back())	// noexcept as an extension
	{
		return c.back();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference
	back() const HAMON_NOEXCEPT_IF_EXPR(c.back())	// noexcept as an extension
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
		// [queue.mod]/1
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
	pop() HAMON_NOEXCEPT_IF_EXPR(c.pop_front())	// noexcept as an extension
	{
		c.pop_front();
	}

	HAMON_CXX14_CONSTEXPR void
	swap(queue& q) HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_swappable<Container>::value)
	{
		hamon::ranges::swap(c, q.c);
	}

private:
	friend struct detail::queue_access;
};

namespace detail
{

struct queue_access
{
	template <typename T, typename Container>
	static HAMON_CXX11_CONSTEXPR Container const&
	get_container(hamon::queue<T, Container> const& q)
	{
		return q.c;
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
queue(Container)
-> queue<typename Container::value_type, Container>;

template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>	// [container.adaptors.general]/6.1
queue(InputIterator, InputIterator)
-> queue<hamon::detail::iter_value_type<InputIterator>>;

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R)>
queue(hamon::from_range_t, R&&)
-> queue<hamon::ranges::range_value_t<R>>;

template <typename Container, typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>,
		std::uses_allocator<Container, Allocator>									// [container.adaptors.general]/6.5
	>::value>
>
queue(Container, Allocator)
-> queue<typename Container::value_type, Container>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),	// [container.adaptors.general]/6.1
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>								// [container.adaptors.general]/6.4
	>::value>,
	typename T = hamon::detail::iter_value_type<InputIterator>
>
queue(InputIterator, InputIterator, Allocator)
-> queue<T, hamon::deque<T, Allocator>>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>								// [container.adaptors.general]/6.4
	>::value>,
	typename T = hamon::ranges::range_value_t<R>
>
queue(hamon::from_range_t, R&&, Allocator)
-> queue<T, hamon::deque<T, Allocator>>;

#endif

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator==(queue<T, Container> const& x, queue<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() == hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::queue_access;
	return access::get_container(x) == access::get_container(y);	// [queue.ops]/1
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator!=(queue<T, Container> const& x, queue<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() != hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::queue_access;
	return access::get_container(x) != access::get_container(y);	// [queue.ops]/2
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<(queue<T, Container> const& x, queue<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() < hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::queue_access;
	return access::get_container(x) < access::get_container(y);	// [queue.ops]/3
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>(queue<T, Container> const& x, queue<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() > hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::queue_access;
	return access::get_container(x) > access::get_container(y);	// [queue.ops]/4
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<=(queue<T, Container> const& x, queue<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() <= hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::queue_access;
	return access::get_container(x) <= access::get_container(y);	// [queue.ops]/5
}

template <typename T, typename Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>=(queue<T, Container> const& x, queue<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() >= hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::queue_access;
	return access::get_container(x) >= access::get_container(y);	// [queue.ops]/6
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, hamon::three_way_comparable Container>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR hamon::compare_three_way_result_t<Container>
operator<=>(queue<T, Container> const& x, queue<T, Container> const& y)
HAMON_NOEXCEPT_IF_EXPR(hamon::declval<Container const&>() <=> hamon::declval<Container const&>())	// noexcept as an extension
{
	using access = hamon::detail::queue_access;
	return access::get_container(x) <=> access::get_container(y);	// [queue.ops]/7
}

#endif

template <typename T, typename Container,
	typename = hamon::enable_if_t<hamon::is_swappable<Container>::value>>	// [queue.special]/1
HAMON_CXX14_CONSTEXPR void
swap(queue<T, Container>& x, queue<T, Container>& y)
HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	x.swap(y);	// [queue.special]/2
}

#if 0	// TODO

// [container.adaptors.format], formatter specialization for queue
template <typename charT, typename T, formattable<charT> Container>
struct formatter<queue<T, Container>, charT>;

#endif

}	// namespace hamon

namespace std
{

template <typename T, typename Container, typename Alloc>
struct uses_allocator<hamon::queue<T, Container>, Alloc>
    : uses_allocator<Container, Alloc>::type {};

}	// namespace std

#endif

#endif // HAMON_QUEUE_QUEUE_HPP
