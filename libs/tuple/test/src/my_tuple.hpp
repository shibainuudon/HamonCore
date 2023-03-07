/**
 *	@file	my_tuple.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_TUPLE_MY_TUPLE_HPP
#define UNIT_TEST_TUPLE_MY_TUPLE_HPP

//#include <hamon/cstddef/size_t.hpp>
//#include <hamon/tuple/tuple_element.hpp>
//#include <hamon/type_traits/nth.hpp>

namespace hamon_tuple_test
{

template <typename... Types>
struct MyTuple
{
};

}	// namespace hamon_tuple_test

#if 0
namespace std
{

template <hamon::size_t I, typename... Types>
struct tuple_element<I, hamon_tuple_test::MyTuple<Types...>>
{
public:
	static_assert(I < sizeof...(Types), "tuple_element index out of range");
	using type = hamon::nth_t<I, Types...>;
};

}	// namespace std
#endif

#endif // UNIT_TEST_TUPLE_MY_TUPLE_HPP
