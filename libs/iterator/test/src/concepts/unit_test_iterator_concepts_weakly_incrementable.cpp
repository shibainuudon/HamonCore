/**
 *	@file	unit_test_iterator_concepts_weakly_incrementable.cpp
 *
 *	@brief	weakly_incrementable のテスト
 */

#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <memory>
#include "iterator_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_WEAKLY_INCREMENTABLE_TEST(B, ...)	\
	static_assert(B == hamon::weakly_incrementable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::weakly_incrementable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_WEAKLY_INCREMENTABLE_TEST(B, ...)	\
	static_assert(B == hamon::weakly_incrementable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::weakly_incrementable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace weakly_incrementable_test
{

HAMON_WEAKLY_INCREMENTABLE_TEST(true,  int               *);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  int const         *);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  int       volatile*);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  int const volatile*);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int               * const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int const         * const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int       volatile* const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int const volatile* const);

HAMON_WEAKLY_INCREMENTABLE_TEST(true,  int               **);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  int const         **);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  int       volatile**);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  int const volatile**);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int               ** const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int const         ** const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int       volatile** const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int const volatile** const);

HAMON_WEAKLY_INCREMENTABLE_TEST(false, void               *);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void const         *);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void       volatile*);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void const volatile*);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void               * const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void const         * const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void       volatile* const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void const volatile* const);

HAMON_WEAKLY_INCREMENTABLE_TEST(true,  void               **);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  void const         **);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  void       volatile**);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  void const volatile**);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void               ** const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void const         ** const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void       volatile** const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, void const volatile** const);

HAMON_WEAKLY_INCREMENTABLE_TEST(false, std::unique_ptr<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, std::shared_ptr<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, hamon::vector<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  hamon::vector<int>::iterator);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  hamon::vector<int>::const_iterator);

HAMON_WEAKLY_INCREMENTABLE_TEST(false, int[]);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int[2]);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int&);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, int&&);

struct X
{
	friend auto operator++(X&)->X&;
	friend auto operator++(X&, int)->X&;
	using difference_type = int;
};
struct Y
{
	friend auto operator++(Y&)->Y;		// 前置インクリメントは参照を返さないといけない
	friend auto operator++(Y&, int)->Y&;
	using difference_type = int;
};
struct Z
{
	friend auto operator++(Z&)->Z&;
	friend auto operator++(Z&, int)->void;	// 後置インクリメントは何を返しても良い
	using difference_type = int;
};
struct W
{
	friend auto operator++(W&)->W&;
	friend auto operator++(W&, int)->W&;
//	using difference_type = int;		// difference_type が定義されてないといけない
};

HAMON_WEAKLY_INCREMENTABLE_TEST(true,  X);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, X&);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, X const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, X const&);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, Y);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, Y&);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, Y const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, Y const&);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  Z);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, Z&);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, Z const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, Z const&);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, W);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, W&);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, W const);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, W const&);

HAMON_WEAKLY_INCREMENTABLE_TEST(true,  weakly_incrementable_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  incrementable_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, indirectly_readable_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(false, indirectly_writable_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  input_or_output_iterator_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  input_iterator_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  output_iterator_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  forward_iterator_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  bidirectional_iterator_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  random_access_iterator_wrapper<int>);
HAMON_WEAKLY_INCREMENTABLE_TEST(true,  contiguous_iterator_wrapper<int>);

}	// namespace weakly_incrementable_test

}	// namespace hamon_iterator_test

#undef HAMON_WEAKLY_INCREMENTABLE_TEST
