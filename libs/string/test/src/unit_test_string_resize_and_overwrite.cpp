/**
 *	@file	unit_test_string_resize_and_overwrite.cpp
 *
 *	@brief	resize_and_overwrite のテスト
 *
 *	template<class Operation>
 *	constexpr void resize_and_overwrite(size_type n, Operation op);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/string/char_traits.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace resize_and_overwrite_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline HAMON_CXX20_CONSTEXPR bool
ResizeAndOverwriteTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	
	{
		auto p = Helper::abcd();
		string s;
		s.resize_and_overwrite(16, [p](CharT* buf, hamon::size_t /*buf_size*/)
		{
			const auto to_copy = hamon::char_traits<CharT>::length(p);
			//std::memcpy(buf + sz, p, to_copy);
			for (hamon::size_t i = 0; i < to_copy; ++i)
			{
				buf[i] = p[i];
			}
			return to_copy;
		});
		VERIFY(s.length() == 4);
		VERIFY(s[4] == CharT{});
		VERIFY(s == string(p));
	}

	{
		auto p = Helper::long_str();
		string s;
		auto const sz = s.size();
		s.resize_and_overwrite(16, [p, sz](CharT* buf, hamon::size_t buf_size)
		{
			const auto to_copy = hamon::min(buf_size - sz, hamon::char_traits<CharT>::length(p));
			//std::memcpy(buf + sz, p, to_copy);
			for (hamon::size_t i = 0; i < to_copy; ++i)
			{
				buf[i] = p[i];
			}
			return sz + to_copy;
		});
		VERIFY(s.length() == 16);
		VERIFY(s[16] == CharT{});
		VERIFY(s == string(p).substr(0, 16));
	}

	{
		auto p = Helper::ABCDE();
		string s = Helper::abcd();
		auto const sz = s.size();
		s.resize_and_overwrite(16, [p, sz](CharT* buf, hamon::size_t buf_size)
		{
			const auto to_copy = hamon::min(buf_size - sz, hamon::char_traits<CharT>::length(p));
			for (hamon::size_t i = 0; i < to_copy; ++i)
			{
				buf[sz + i] = p[i];
			}
			return sz + to_copy;
		});
		VERIFY(s.length() == 9);
		VERIFY(s[9] == CharT{});
		VERIFY(s == string(Helper::abcd()) + string(Helper::ABCDE()));
	}

	{
		auto p = Helper::long_str();
		string s = p;
		s.resize_and_overwrite(10, [](CharT*, hamon::size_t buf_size)
		{
			return buf_size;
		});
		VERIFY(s.length() == 10);
		VERIFY(s[10] == CharT{});
		VERIFY(s == string(p).substr(0, 10));
	}

	{
		auto p = Helper::long_str();
		string s = p;
		s.resize_and_overwrite(10, [](CharT*, hamon::size_t)
		{
			return 5;
		});
		VERIFY(s.length() == 5);
		VERIFY(s[5] == CharT{});
		VERIFY(s == string(p).substr(0, 5));
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ResizeAndOverwriteTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ResizeAndOverwriteTest<TypeParam>());
}

}	// namespace resize_and_overwrite_test
}	// namespace string_test
}	// namespace hamon_test
