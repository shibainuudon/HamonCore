﻿/**
 *	@file	unit_test_random_concepts_uniform_random_bit_generator.cpp
 *
 *	@brief	uniform_random_bit_generator のテスト
 */

#include <hamon/random/concepts/uniform_random_bit_generator.hpp>
#include <hamon/random/engines/xorshift.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH();
HAMON_WARNING_DISABLE_MSVC(4146);

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(B, ...)	\
	static_assert(B == hamon::uniform_random_bit_generator<__VA_ARGS__>, "")
#else
#  define HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(B, ...)	\
	static_assert(B == hamon::uniform_random_bit_generator<__VA_ARGS__>::value, "")
#endif

namespace hamon_random_test
{

namespace uniform_random_bit_generator_test
{

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, hamon::xorshift32);
HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, hamon::xorshift64);
HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, hamon::xorshift128);
HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, hamon::xorwow);
HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, hamon::xorshift64star);
HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, hamon::xorshift1024star);
HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, hamon::xorshift128plus);

struct G1
{
  unsigned char operator()();
  static constexpr unsigned char min() { return 0; }
  static constexpr unsigned char max() { return 10; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G1);

struct G2
{
  unsigned operator()();
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return -1U; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G2);

struct G3
{
  unsigned long long operator()();
  static constexpr unsigned long long min() { return 0; }
  static constexpr unsigned long long max() { return -1ULL; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G3);

struct G4
{
  unsigned operator()(int = 0, int = 0); // extra params, with default args
  static constexpr unsigned min(long = 0) { return 0; }
  static constexpr unsigned max(void* = nullptr) { return -1U; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G4);

struct G5
{
  unsigned operator()() &; // ref-qualifier
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return 10; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G5);

struct G6
{
  unsigned operator()() const; // cv-qualifier
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return 10; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G6);

struct G7
{
  unsigned operator()() volatile; // cv-qualifier
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return 10; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G7);

struct G8
{
  unsigned operator()() const volatile; // cv-qualifiers
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return 10; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G8);

struct G9
{
  unsigned operator()() const volatile; // cv-qualifiers
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return 10; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G9);

struct G10
{
  unsigned operator()() const volatile & noexcept; // cv/ref/noexcept
  static constexpr unsigned min() noexcept { return 0; }
  static constexpr unsigned max() noexcept { return 10; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(true, G10);

// Negative tests.

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, void);
HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, int);
HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, unsigned(*)());

struct N1
{
  unsigned operator()();
  constexpr unsigned min() const { return 0; } // non-static
  static constexpr unsigned max() { return 1; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N1);

struct N2
{
  unsigned operator()();
  static constexpr unsigned min() { return 0; }
  constexpr unsigned max() const { return 1; } // non-static
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N2);

struct N3
{
  unsigned operator()();
  // no N3::min()
  static constexpr unsigned max() { return 1; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N3);

struct N4
{
  unsigned operator()();
  static constexpr unsigned min() { return 0; }
  // no N4::max()
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N4);

struct N5
{
  // no operator()
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return 1; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N5);

struct N6
{
  int operator()(); // returns signed integral
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return 1; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N6);

struct N7
{
  unsigned operator()();
  static constexpr unsigned long min() { return 0; } // different return type
  static constexpr unsigned max() { return 1; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N7);

struct N8
{
  unsigned operator()();
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned long max() { return 1; } // different return type
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N8);

struct N9
{
  unsigned operator()();
  static constexpr unsigned long min() { return 0; } // different return type
  static constexpr unsigned long max() { return 1; } // different return type
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N9);

struct N10
{
  unsigned operator()() &&; // ref-qualifier
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return 1; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N10);

struct N11
{
  unsigned operator()() const &&; // ref-qualifier
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return 1; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N11);

struct N12
{
  unsigned operator()();
  static unsigned min() { return 0; } // not constexpr
  static constexpr unsigned max() { return 1; }
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N12); // LWG 3150

struct N13
{
  unsigned operator()();
  static constexpr unsigned min() { return 0; }
  static unsigned max() { return 1; } // not constexpr
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N13); // LWG 3150

struct N14
{
  unsigned operator()();
  static constexpr unsigned min() { return 1; }
  static constexpr unsigned max() { return 0; } // max not greater than min
};

HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST(false, N14); // LWG 3150

}	// namespace uniform_random_bit_generator_test

}	// namespace hamon_random_test

#undef HAMON_UNIFORM_RANDOM_BIT_GENERATOR_TEST

HAMON_WARNING_POP();
