/**
 *	@file	unit_test_pair_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>

namespace hamon_pair_test
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

static_assert( hamon::is_trivially_destructible<hamon::pair<Trivial,    Trivial>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::pair<NonTrivial, Trivial>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::pair<Trivial,    NonTrivial>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::pair<NonTrivial, NonTrivial>>::value, "");

}	// namespace dtor_test

}	// namespace hamon_pair_test
