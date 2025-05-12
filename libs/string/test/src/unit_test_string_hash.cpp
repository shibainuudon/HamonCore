/**
 *	@file	unit_test_string_hash.cpp
 *
 *	@brief	hash のテスト
 */

#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace hash_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
HAMON_CXX20_CONSTEXPR bool test()
{
	using S = hamon::basic_string<CharT>;
	using SV = hamon::basic_string_view<CharT>;
	using Helper = StringTestHelper<CharT>;

	auto const s1 = S(Helper::abcd());
	auto const s2 = s1.substr(0, 3);
	auto const s3 = S(Helper::abc());
	auto const s4 = S(Helper::abb());

	auto const h = hamon::hash<S>{};

	VERIFY(h(s1) == h(s1));
	VERIFY(h(s1) != h(s2));
	VERIFY(h(s1) != h(s3));
	VERIFY(h(s1) != h(s4));
	VERIFY(h(s2) == h(s2));
	VERIFY(h(s2) == h(s3));
	VERIFY(h(s2) != h(s4));
	VERIFY(h(s3) == h(s3));
	VERIFY(h(s3) != h(s4));
	VERIFY(h(s4) == h(s4));

	VERIFY(hamon::hash<S>()(s1) == hamon::hash<SV>()(SV(s1)));
	VERIFY(hamon::hash<S>()(s2) == hamon::hash<SV>()(SV(s2)));
	VERIFY(hamon::hash<S>()(s3) == hamon::hash<SV>()(SV(s3)));
	VERIFY(hamon::hash<S>()(s4) == hamon::hash<SV>()(SV(s4)));

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, HashTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<TypeParam>());
}

}	// namespace hash_test
}	// namespace string_test
}	// namespace hamon_test
