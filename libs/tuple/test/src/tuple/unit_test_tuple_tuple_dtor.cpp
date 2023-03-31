/**
 *	@file	unit_test_tuple_tuple_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>

namespace hamon_tuple_test
{

namespace dtor_test
{

struct Trivial {};

struct NonTrivial
{
	~NonTrivial();
};

static_assert( hamon::is_trivially_destructible<Trivial>::value, "");
static_assert(!hamon::is_trivially_destructible<NonTrivial>::value, "");

static_assert( hamon::is_trivially_destructible<hamon::tuple<Trivial,    Trivial>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::tuple<NonTrivial, Trivial>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::tuple<Trivial,    NonTrivial>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::tuple<NonTrivial, NonTrivial>>::value, "");

}	// namespace dtor_test

}	// namespace hamon_tuple_test
