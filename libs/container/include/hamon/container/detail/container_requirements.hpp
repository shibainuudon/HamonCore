﻿/**
 *	@file	container_requirements.hpp
 *
 *	@brief	container_requirements の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_CONTAINER_REQUIREMENTS_HPP
#define HAMON_CONTAINER_DETAIL_CONTAINER_REQUIREMENTS_HPP

#include <hamon/compare/strong_ordering.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/detail/cpp17_forward_iterator.hpp>
#include <hamon/iterator/detail/cpp17_random_access_iterator.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/utility/move.hpp>

namespace hamon {
namespace detail {

#define HAMON_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4101)	// ローカル変数は 1 度も使われていません。
HAMON_WARNING_DISABLE_MSVC(4700)	// 初期化されていないローカル変数 '' が使用されます
HAMON_WARNING_DISABLE_CLANG("-Wunused-variable")
HAMON_WARNING_DISABLE_GCC("-Wunused-variable")
HAMON_WARNING_DISABLE_GCC("-Wunused-but-set-variable")

// 23.2.2.2 Container requirements[container.reqmts]

template <typename X>
void container_requirements_size(hamon::true_type)
{
	X const c{};
	HAMON_STATIC_ASSERT(hamon::is_same<typename X::size_type, decltype(c.size())>::value);
}

template <typename X>
void container_requirements_size(hamon::false_type)
{
}

template <typename X, typename T, bool HasSize = true>
void container_requirements()
{
	using value_type      = typename X::value_type;
	using reference       = typename X::reference;
	using const_reference = typename X::const_reference;
	using iterator        = typename X::iterator;
	using const_iterator  = typename X::const_iterator;
	using difference_type = typename X::difference_type;
	using size_type       = typename X::size_type;

	// typename X::value_type
	HAMON_STATIC_ASSERT(hamon::is_same<value_type, T>::value);

	// typename X::reference
	HAMON_STATIC_ASSERT(hamon::is_same<reference, T&>::value);

	// typename X::const_reference
	HAMON_STATIC_ASSERT(hamon::is_same<const_reference, const T&>::value);

	// typename X::iterator
	HAMON_STATIC_ASSERT(hamon::is_same<T, typename hamon::iterator_traits<iterator>::value_type>::value);
	HAMON_STATIC_ASSERT(hamon::detail::cpp17_forward_iterator_t<iterator>::value);
	HAMON_STATIC_ASSERT(hamon::is_convertible<iterator, const_iterator>::value);

	// typename X::const_iterator
	HAMON_STATIC_ASSERT(hamon::is_same<T, typename hamon::iterator_traits<const_iterator>::value_type>::value);
	HAMON_STATIC_ASSERT(hamon::detail::cpp17_forward_iterator_t<const_iterator>::value);

	// typename X::difference_type
	HAMON_STATIC_ASSERT(hamon::is_signed<difference_type>::value);
	HAMON_STATIC_ASSERT(hamon::is_same<difference_type, typename hamon::iterator_traits<iterator>::difference_type>::value);
	HAMON_STATIC_ASSERT(hamon::is_same<difference_type, typename hamon::iterator_traits<const_iterator>::difference_type>::value);

	// typename X::size_type
	HAMON_STATIC_ASSERT(hamon::is_unsigned<size_type>::value);
	HAMON_STATIC_ASSERT(hamon::is_same<size_type, hamon::make_unsigned_t<difference_type>>::value);

	// default constructor
	{
		X u;
	}
	{
		X u = X();
	}
	// copy constructor
	{
		X const v{};
		X u(v);
	}
	{
		X const v{};
		X u = v;
	}
	// move constructor
	{
		X rv{};
		X u(hamon::move(rv));
	}
	{
		X rv{};
		X u = hamon::move(rv);
	}
	// copy assign
	{
		X t{};
		X const v{};
		HAMON_STATIC_ASSERT(hamon::is_same<X&, decltype(t = v)>::value);
	}
	// move assign
	{
		X t{};
		X rv{};
		HAMON_STATIC_ASSERT(hamon::is_same<X&, decltype(t = hamon::move(rv))>::value);
	}
	// destructor
	{
		X a{};
		a.~X();
	}
	// begin, end, cbegin, cend
	{
		X b{};
		X const c{};
		HAMON_STATIC_ASSERT(hamon::is_same<iterator,       decltype(b.begin())>::value);
		HAMON_STATIC_ASSERT(hamon::is_same<const_iterator, decltype(c.begin())>::value);
		HAMON_STATIC_ASSERT(hamon::is_same<iterator,       decltype(b.end())>::value);
		HAMON_STATIC_ASSERT(hamon::is_same<const_iterator, decltype(c.end())>::value);
		HAMON_STATIC_ASSERT(hamon::is_same<const_iterator, decltype(b.cbegin())>::value);
		HAMON_STATIC_ASSERT(hamon::is_same<const_iterator, decltype(c.cbegin())>::value);
		HAMON_STATIC_ASSERT(hamon::is_same<const_iterator, decltype(b.cend())>::value);
		HAMON_STATIC_ASSERT(hamon::is_same<const_iterator, decltype(c.cend())>::value);
	}
	// operator <=>
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	if constexpr (hamon::detail::cpp17_random_access_iterator_t<iterator>::value)
	{
		X b{};
		{
			auto i = b.begin();
			auto j = b.end();
			HAMON_STATIC_ASSERT(hamon::is_same<hamon::strong_ordering, decltype(i <=> j)>::value);
		}
		{
			auto i = b.cbegin();
			auto j = b.cend();
			HAMON_STATIC_ASSERT(hamon::is_same<hamon::strong_ordering, decltype(i <=> j)>::value);
		}
	}
#endif
	// equality comparison
	{
		X const b{};
		X const c{};
		HAMON_STATIC_ASSERT(hamon::is_same<bool, decltype(c == b)>::value);
		HAMON_STATIC_ASSERT(hamon::is_same<bool, decltype(c != b)>::value);
	}
	// swap
	{
		X t{};
		X s{};
		HAMON_STATIC_ASSERT(hamon::is_same<void, decltype(t.swap(s))>::value);
		HAMON_STATIC_ASSERT(hamon::is_same<void, decltype(swap(t, s))>::value);
	}
	// size
	{
		container_requirements_size<X>(hamon::bool_constant<HasSize>{});
	}
	// max_size
	{
		X const c{};
		HAMON_STATIC_ASSERT(hamon::is_same<size_type, decltype(c.max_size())>::value);
	}
	// empty
	{
		X const c{};
		HAMON_STATIC_ASSERT(hamon::is_same<bool, decltype(c.empty())>::value);
	}
}

HAMON_WARNING_POP()

#undef HAMON_STATIC_ASSERT

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_CONTAINER_REQUIREMENTS_HPP
