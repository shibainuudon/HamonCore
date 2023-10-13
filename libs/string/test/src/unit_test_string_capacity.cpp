/**
 *	@file	unit_test_string_capacity.cpp
 *
 *	@brief	キャパシティのテスト
 *
 *	constexpr size_type size() const noexcept;
 *	constexpr size_type length() const noexcept;
 *	constexpr size_type max_size() const noexcept;
 *	constexpr size_type capacity() const noexcept;
 *	[[nodiscard]] constexpr bool empty() const noexcept;
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000)
HAMON_WARNING_DISABLE_GCC("-Wstringop-overread")
#endif

namespace hamon_test
{
namespace string_test
{
namespace capacity_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
CapacityTest()
{
	using string = hamon::basic_string<CharT>;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;

	{
		string const s = Helper::abcde();
		static_assert(noexcept(s.size()), "");
		static_assert(noexcept(s.length()), "");
		static_assert(noexcept(s.max_size()), "");
		static_assert(noexcept(s.capacity()), "");
		static_assert(noexcept(s.empty()), "");
		static_assert(hamon::is_same<decltype(s.size()), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.length()), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.max_size()), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.capacity()), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(s.empty()), bool>::value, "");

		VERIFY(s.size() == 5);
		VERIFY(s.length() == 5);
		VERIFY(s.max_size() > 5);
		VERIFY(s.capacity() >= 5);
		VERIFY(s.empty() == false);
	}
	{
		string const s;

		VERIFY(s.size() == 0);
		VERIFY(s.length() == 0);
		VERIFY(s.max_size() > 0);
		VERIFY(s.capacity() >= 0);
		VERIFY(s.empty() == true);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, CapacityTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CapacityTest<TypeParam>());
}

}	// namespace capacity_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
