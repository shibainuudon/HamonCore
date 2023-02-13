/**
 *	@file	unit_test_concepts_and.cpp
 *
 *	@brief	HAMON_CONCEPTS_AND のテスト
 */

#include <hamon/concepts/detail/and.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_AND_TEST(B, C1, C2)	\
	static_assert(B == HAMON_CONCEPTS_AND(C1, C2), "")
#else
#  define HAMON_AND_TEST(B, C1, C2)	\
	static_assert(B == HAMON_CONCEPTS_AND(C1, C2)::value, "")
#endif

namespace hamon_concepts_test {
namespace and_test {

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

HAMON_AND_TEST(true,  hamon::default_initializable<S1>, hamon::copy_constructible<S1>);
HAMON_AND_TEST(false, hamon::default_initializable<S2>, hamon::copy_constructible<S2>);
HAMON_AND_TEST(false, hamon::default_initializable<S3>, hamon::copy_constructible<S3>);
HAMON_AND_TEST(false, hamon::default_initializable<S4>, hamon::copy_constructible<S4>);

}	// namespace and_test
}	// namespace hamon_concepts_test

#undef HAMON_AND_TEST
