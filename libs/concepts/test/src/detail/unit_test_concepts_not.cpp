/**
 *	@file	unit_test_concepts_not.cpp
 *
 *	@brief	HAMON_CONCEPTS_NOT のテスト
 */

#include <hamon/concepts/detail/not.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_NOT_TEST(B, C)	\
	static_assert(B == HAMON_CONCEPTS_NOT(C), "")
#else
#  define HAMON_NOT_TEST(B, C)	\
	static_assert(B == HAMON_CONCEPTS_NOT(C)::value, "")
#endif

namespace hamon_concepts_test {
namespace not_test {

struct S1
{
	S1();
	S1(S1 const&);
};

struct S2
{
	S2();
	S2(S2 const&) = delete;
};

struct S3
{
	S3() = delete;
	S3(S3 const&);
};

struct S4
{
	S4() = delete;
	S4(S4 const&) = delete;
};

HAMON_NOT_TEST(false, hamon::default_initializable<S1>);
HAMON_NOT_TEST(false, hamon::default_initializable<S2>);
HAMON_NOT_TEST(true,  hamon::default_initializable<S3>);
HAMON_NOT_TEST(true,  hamon::default_initializable<S4>);

HAMON_NOT_TEST(false, hamon::copy_constructible<S1>);
HAMON_NOT_TEST(true,  hamon::copy_constructible<S2>);
HAMON_NOT_TEST(false, hamon::copy_constructible<S3>);
HAMON_NOT_TEST(true,  hamon::copy_constructible<S4>);

}	// namespace not_test
}	// namespace hamon_concepts_test

#undef HAMON_NOT_TEST
