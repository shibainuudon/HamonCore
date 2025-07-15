/**
 *	@file	priority_queue.hpp
 *
 *	@brief	priority_queue の定義
 */

#ifndef HAMON_QUEUE_PRIORITY_QUEUE_HPP
#define HAMON_QUEUE_PRIORITY_QUEUE_HPP

#include <hamon/queue/priority_queue_fwd.hpp>
#include <hamon/queue/config.hpp>

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE)

#include <hamon/algorithm/make_heap.hpp>
#include <hamon/algorithm/pop_heap.hpp>
#include <hamon/algorithm/push_heap.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/swap.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/has_append_range.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/less.hpp>
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
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 23.6.4 Class template priority_queue[priority.queue]

template <
	typename T,
	typename Container/* = vector<T>*/,
	typename Compare/* = less<typename Container::value_type>*/>
class priority_queue
{
public:
	using value_type      = typename Container::value_type;
	using reference       = typename Container::reference;
	using const_reference = typename Container::const_reference;
	using size_type       = typename Container::size_type;
	using container_type  = Container;
	using value_compare   = Compare;

protected:
	Container c;
	Compare comp;

public:
	HAMON_CXX11_CONSTEXPR
	priority_queue() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<container_type>::value &&
		hamon::is_nothrow_default_constructible<value_compare>::value)
		: c(), comp()
	{}

	HAMON_CXX11_CONSTEXPR explicit
	priority_queue(Compare const& x) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<container_type>::value &&
		hamon::is_nothrow_copy_constructible<value_compare>::value)
		: c(), comp(x)
	{}

	HAMON_CXX14_CONSTEXPR
	priority_queue(Compare const& x, Container const& y)
		: c(y), comp(x)	// [priqueue.cons]/2
	{
		// [priqueue.cons]/1
		// TODO: x defines a strict weak ordering

		// [priqueue.cons]/2
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	HAMON_CXX14_CONSTEXPR
	priority_queue(Compare const& x, Container&& y)
		: c(hamon::move(y)), comp(x)	// [priqueue.cons]/2
	{
		// [priqueue.cons]/1
		// TODO: x defines a strict weak ordering

		// [priqueue.cons]/2
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	priority_queue(InputIterator first, InputIterator last, Compare const& x = Compare())
		: c(first, last), comp(x)	// [priqueue.cons]/4
	{
		// [priqueue.cons]/3
		// TODO: x defines a strict weak ordering

		// [priqueue.cons]/4
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	priority_queue(InputIterator first, InputIterator last, Compare const& x, Container const& y)
		: c(y), comp(x)	// [priqueue.cons]/6
	{
		// [priqueue.cons]/5
		// TODO: x defines a strict weak ordering

		// [priqueue.cons]/6
		c.insert(c.end(), first, last);
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	priority_queue(InputIterator first, InputIterator last, Compare const& x, Container&& y)
		: c(hamon::move(y)), comp(x)	// [priqueue.cons]/6
	{
		// [priqueue.cons]/5
		// TODO: x defines a strict weak ordering

		// [priqueue.cons]/6
		c.insert(c.end(), first, last);
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	priority_queue(hamon::from_range_t, R&& rg, Compare const& x = Compare())
		: c(hamon::ranges::to<Container>(hamon::forward<R>(rg))), comp(x)	// [priqueue.cons]/8
	{
		// [priqueue.cons]/7
		// TODO: x defines a strict weak ordering

		// [priqueue.cons]/8
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR explicit
	priority_queue(Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, Alloc const&>::value &&
		hamon::is_nothrow_default_constructible<value_compare>::value)
		: c(a), comp()	// [priqueue.cons.alloc]/2
	{}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	priority_queue(Compare const& compare, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, Alloc const&>::value &&
		hamon::is_nothrow_copy_constructible<value_compare>::value)
		: c(a), comp(compare)	// [priqueue.cons.alloc]/3
	{}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	priority_queue(Compare const& compare, Container const& cont, Alloc const& a)
		: c(cont, a), comp(compare)	// [priqueue.cons.alloc]/4
	{
		// [priqueue.cons.alloc]/4
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	priority_queue(Compare const& compare, Container&& cont, Alloc const& a)
		: c(hamon::move(cont), a), comp(compare)	// [priqueue.cons.alloc]/5
	{
		// [priqueue.cons.alloc]/5
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	priority_queue(priority_queue const& q, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, container_type const&, Alloc const&>::value &&
		hamon::is_nothrow_copy_constructible<value_compare>::value)
		: c(q.c, a), comp(q.comp)	// [priqueue.cons.alloc]/6
	{}

	template <typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX11_CONSTEXPR
	priority_queue(priority_queue&& q, Alloc const& a) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_constructible<container_type, container_type&&, Alloc const&>::value &&
		hamon::is_nothrow_move_constructible<value_compare>::value)
		: c(hamon::move(q.c), a), comp(hamon::move(q.comp))	// [priqueue.cons.alloc]/7
	{}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	priority_queue(InputIterator first, InputIterator last, Alloc const& a)
		: c(first, last, a), comp()	// [priqueue.cons.alloc]/8
	{
		// [priqueue.cons.alloc]/8
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	priority_queue(InputIterator first, InputIterator last, Compare const& compare, Alloc const& a)
		: c(first, last, a), comp(compare)	// [priqueue.cons.alloc]/9
	{
		// [priqueue.cons.alloc]/9
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	priority_queue(InputIterator first, InputIterator last, Compare const& compare, Container const& cont, Alloc const& a)
		: c(cont, a), comp(compare)	// [priqueue.cons.alloc]/10
	{
		// [priqueue.cons.alloc]/10
		c.insert(c.end(), first, last);
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
		typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	priority_queue(InputIterator first, InputIterator last, Compare const& compare, Container&& cont, Alloc const& a)
		: c(hamon::move(cont), a), comp(compare)	// [priqueue.cons.alloc]/11
	{
		// [priqueue.cons.alloc]/11
		c.insert(c.end(), first, last);
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R),
		typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	priority_queue(hamon::from_range_t, R&& rg, Compare const& compare, Alloc const& a)
		: c(hamon::ranges::to<Container>(hamon::forward<R>(rg), a)), comp(compare)	// [priqueue.cons.alloc]/12
	{
		// [priqueue.cons.alloc]/12
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R),
		typename Alloc, typename = hamon::enable_if_t<hamon::uses_allocator<container_type, Alloc>::value>>	// [priqueue.cons.alloc]/1
	HAMON_CXX14_CONSTEXPR
	priority_queue(hamon::from_range_t, R&& rg, Alloc const& a)
		: c(hamon::ranges::to<Container>(hamon::forward<R>(rg), a)), comp()	// [priqueue.cons.alloc]/13
	{
		// [priqueue.cons.alloc]/13
		hamon::make_heap(c.begin(), c.end(), comp);
	}

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
	HAMON_CXX11_CONSTEXPR const_reference
	top() const HAMON_NOEXCEPT_IF_EXPR(c.front())	// noexcept as an extension
	{
		return c.front();
	}

	HAMON_CXX14_CONSTEXPR void
	push(value_type const& x)
	{
		// [priqueue.members]/1
		c.push_back(x);
		hamon::push_heap(c.begin(), c.end(), comp);
	}

	HAMON_CXX14_CONSTEXPR void
	push(value_type&& x)
	{
		// [priqueue.members]/2
		c.push_back(hamon::move(x));
		hamon::push_heap(c.begin(), c.end(), comp);
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
		// [priqueue.members]/3
		push_range_impl(hamon::forward<R>(rg), hamon::detail::overload_priority<1>{});
		hamon::make_heap(c.begin(), c.end(), comp);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void
	emplace(Args&&... args)
	{
		// [priqueue.members]/5
		c.emplace_back(hamon::forward<Args>(args)...);
		hamon::push_heap(c.begin(), c.end(), comp);
	}

	HAMON_CXX14_CONSTEXPR void
	pop()
	{
		// [priqueue.members]/6
		hamon::pop_heap(c.begin(), c.end(), comp);
		c.pop_back();
	}

	HAMON_CXX14_CONSTEXPR void
	swap(priority_queue& q) HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_swappable<Container>::value &&
		hamon::is_nothrow_swappable<Compare>::value)
	{
		hamon::ranges::swap(c, q.c);
		hamon::ranges::swap(comp, q.comp);
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	typename Compare, typename Container,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::negation<hamon::detail::simple_allocator_t<Container>>
	>::value>,
	typename T = typename Container::value_type
>
priority_queue(Compare, Container)
-> priority_queue<T, Container, Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename T = hamon::detail::iter_value_type<InputIterator>,
	typename Compare = hamon::less<T>,
	typename Container = hamon::vector<T>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::negation<hamon::detail::simple_allocator_t<Container>>
	>::value>
>
priority_queue(InputIterator, InputIterator, Compare = Compare(), Container = Container())
-> priority_queue<T, Container, Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename T = hamon::ranges::range_value_t<R>,
	typename Compare = hamon::less<T>,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>
	>::value>
>
priority_queue(hamon::from_range_t, R&&, Compare = Compare())
-> priority_queue<T, hamon::vector<T>, Compare>;

template <
	typename Compare, typename Container, typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::detail::simple_allocator_t<Allocator>,
		hamon::uses_allocator<Container, Allocator>
	>::value>,
	typename T = typename Container::value_type
>
priority_queue(Compare, Container, Allocator)
-> priority_queue<T, Container, Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>
	>::value>,
	typename T = hamon::detail::iter_value_type<InputIterator>
>
priority_queue(InputIterator, InputIterator, Allocator)
-> priority_queue<T, hamon::vector<T, Allocator>, hamon::less<T>>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Compare, typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::detail::simple_allocator_t<Allocator>
	>::value>,
	typename T = hamon::detail::iter_value_type<InputIterator>
>
priority_queue(InputIterator, InputIterator, Compare, Allocator)
-> priority_queue<T, hamon::vector<T, Allocator>, Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Compare, typename Container, typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::detail::simple_allocator_t<Allocator>,
		hamon::uses_allocator<Container, Allocator>
	>::value>,
	typename T = typename Container::value_type
>
priority_queue(InputIterator, InputIterator, Compare, Container, Allocator)
-> priority_queue<T, Container, Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Compare, typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::negation<hamon::detail::simple_allocator_t<Compare>>,
		hamon::detail::simple_allocator_t<Allocator>
	>::value>,
	typename T = hamon::ranges::range_value_t<R>
>
priority_queue(hamon::from_range_t, R&&, Compare, Allocator)
-> priority_queue<T, hamon::vector<T, Allocator>, Compare>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::simple_allocator_t<Allocator>
	>::value>,
	typename T = hamon::ranges::range_value_t<R>
>
priority_queue(hamon::from_range_t, R&&, Allocator)
-> priority_queue<T, hamon::vector<T, Allocator>>;

#endif

// no equality is provided

template <typename T, typename Container, typename Compare,
	typename = hamon::enable_if_t<hamon::conjunction<	// [priqueue.special]/1
		hamon::is_swappable<Container>,
		hamon::is_swappable<Compare>
	>::value>
>
HAMON_CXX14_CONSTEXPR void
swap(priority_queue<T, Container, Compare>& x, priority_queue<T, Container, Compare>& y)
HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	// [priqueue.special]/2
	x.swap(y);
}

#if 0	// TODO

// [container.adaptors.format], formatter specialization for priority_queue
template <typename charT, typename T, formattable<charT> Container, typename Compare>
struct formatter<priority_queue<T, Container, Compare>, charT>;

#endif

}	// namespace hamon

namespace std
{

template <typename T, typename Container, typename Compare, typename Alloc>
struct uses_allocator<hamon::priority_queue<T, Container, Compare>, Alloc>
	: uses_allocator<Container, Alloc>::type {};

}	// namespace std

#endif

#endif // HAMON_QUEUE_PRIORITY_QUEUE_HPP
