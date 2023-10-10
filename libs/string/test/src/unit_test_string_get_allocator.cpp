/**
 *	@file	unit_test_string_get_allocator.cpp
 *
 *	@brief	get_allocator のテスト
 *
 *	constexpr allocator_type get_allocator() const noexcept;
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace get_allocator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
GetAllocatorTest()
{
	using string = hamon::basic_string<CharT>;
	using Allocator = typename string::allocator_type;

	{
		Allocator const alloc{};
		string const s(alloc);
		static_assert(noexcept(s.get_allocator()), "");
		static_assert(hamon::is_same<decltype(s.get_allocator()), Allocator>::value, "");
		VERIFY(s.get_allocator() == alloc);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, GetAllocatorTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(GetAllocatorTest<TypeParam>());
}

}	// namespace get_allocator_test
}	// namespace string_test
}	// namespace hamon_test
