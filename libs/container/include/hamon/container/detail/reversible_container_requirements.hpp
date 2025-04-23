/**
 *	@file	reversible_container_requirements.hpp
 *
 *	@brief	reversible_container_requirements の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_REVERSIBLE_CONTAINER_REQUIREMENTS_HPP
#define HAMON_CONTAINER_DETAIL_REVERSIBLE_CONTAINER_REQUIREMENTS_HPP

#include <hamon/iterator/detail/cpp17_bidirectional_iterator.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon {
namespace detail {

#define HAMON_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

// 23.2.2.3 Reversible container requirements[container.rev.reqmts]

template <typename X, typename T>
void reversible_container_requirements()
{
	using iterator               = typename X::iterator;
	using const_iterator         = typename X::const_iterator;
	using reverse_iterator       = typename X::reverse_iterator;
	using const_reverse_iterator = typename X::const_reverse_iterator;

	// [container.rev.reqmts]/1
	HAMON_STATIC_ASSERT(hamon::detail::cpp17_bidirectional_iterator_t<iterator>::value);
	HAMON_STATIC_ASSERT(hamon::detail::cpp17_bidirectional_iterator_t<const_iterator>::value);

	// [container.rev.reqmts]/2
	HAMON_STATIC_ASSERT(hamon::is_same<iterator, typename reverse_iterator::iterator_type>::value);
	HAMON_STATIC_ASSERT(hamon::is_same<T, typename hamon::iterator_traits<reverse_iterator>::value_type>::value);

	// [container.rev.reqmts]/3
	HAMON_STATIC_ASSERT(hamon::is_same<const_iterator, typename const_reverse_iterator::iterator_type>::value);
	HAMON_STATIC_ASSERT(hamon::is_same<T, typename hamon::iterator_traits<const_reverse_iterator>::value_type>::value);

	// [container.rev.reqmts]/4
	HAMON_STATIC_ASSERT(hamon::is_same<reverse_iterator,       decltype(hamon::declval<X&      >().rbegin())>::value);
	HAMON_STATIC_ASSERT(hamon::is_same<const_reverse_iterator, decltype(hamon::declval<X const&>().rbegin())>::value);

	// [container.rev.reqmts]/7
	HAMON_STATIC_ASSERT(hamon::is_same<reverse_iterator,       decltype(hamon::declval<X&      >().rend())>::value);
	HAMON_STATIC_ASSERT(hamon::is_same<const_reverse_iterator, decltype(hamon::declval<X const&>().rend())>::value);

	// [container.rev.reqmts]/10
	HAMON_STATIC_ASSERT(hamon::is_same<const_reverse_iterator, decltype(hamon::declval<X&      >().crbegin())>::value);
	HAMON_STATIC_ASSERT(hamon::is_same<const_reverse_iterator, decltype(hamon::declval<X const&>().crbegin())>::value);

	// [container.rev.reqmts]/13
	HAMON_STATIC_ASSERT(hamon::is_same<const_reverse_iterator, decltype(hamon::declval<X&      >().crend())>::value);
	HAMON_STATIC_ASSERT(hamon::is_same<const_reverse_iterator, decltype(hamon::declval<X const&>().crend())>::value);
}

#undef HAMON_STATIC_ASSERT

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_REVERSIBLE_CONTAINER_REQUIREMENTS_HPP
