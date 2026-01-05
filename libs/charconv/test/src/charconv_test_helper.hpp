/**
 *	@file	charconv_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_CHARCONV_TEST_HELPER_HPP
#define HAMON_CHARCONV_TEST_HELPER_HPP


namespace hamon_charconv_test
{

template <typename T>
struct nan_str;

template <>
struct nan_str<float>
{
	static constexpr const char* nan_str1()
	{
		return "nan";
	}

	static constexpr const char* nan_str2()
	{
#if defined(HAMON_USE_STD_CHARCONV) && defined(HAMON_STDLIB_DINKUMWARE)
		return "-nan(ind)";
#else
		return "-nan";
#endif
	}

	static constexpr const char* snan_str1()
	{
#if !defined(HAMON_USE_STD_CHARCONV)
		// 自前実装のときは "nan(snan)"
		return "nan(snan)";
#elif defined(HAMON_STDLIB_DINKUMWARE)
		// Microsoft-STLのとき
#  if defined(HAMON_MSVC)
		// MSVCのときは "nan" (floatの時のみ)
		return "nan";
#  else
		// Clang のときは "nan(snan)"
		return "nan(snan)";
#  endif
#else
		// 上記以外のときは "nan"
		return "nan";
#endif
	}

	static constexpr const char* snan_str2()
	{
#if !defined(HAMON_USE_STD_CHARCONV)
		// 自前実装のときは "nan(snan)"
		return "-nan(snan)";
#elif defined(HAMON_STDLIB_DINKUMWARE)
		// Microsoft-STLのとき
#  if defined(HAMON_MSVC)
		// MSVCのときは "nan" (floatの時のみ)
		return "-nan";
#  else
		// Clang のときは "nan(snan)"
		return "-nan(snan)";
#  endif
#else
		// 上記以外のときは "nan"
		return "-nan";
#endif
	}
};

template <>
struct nan_str<double>
{
	static constexpr const char* nan_str1()
	{
		return "nan";
	}

	static constexpr const char* nan_str2()
	{
#if defined(HAMON_USE_STD_CHARCONV) && defined(HAMON_STDLIB_DINKUMWARE)
		return "-nan(ind)";
#else
		return "-nan";
#endif
	}

	static constexpr const char* snan_str1()
	{
#if !defined(HAMON_USE_STD_CHARCONV)
		// 自前実装のときは "nan(snan)"
		return "nan(snan)";
#elif defined(HAMON_STDLIB_DINKUMWARE)
		// Microsoft-STLのときは "nan(snan)"
		return "nan(snan)";
#else
		// 上記以外のときは "nan"
		return "nan";
#endif
	}

	static constexpr const char* snan_str2()
	{
#if !defined(HAMON_USE_STD_CHARCONV)
		// 自前実装のときは "nan(snan)"
		return "-nan(snan)";
#elif defined(HAMON_STDLIB_DINKUMWARE)
		// Microsoft-STLのときは "nan(snan)"
		return "-nan(snan)";
#else
		// 上記以外のときは "nan"
		return "-nan";
#endif
	}
};

}	// namespace hamon_charconv_test

#endif // HAMON_CHARCONV_TEST_HELPER_HPP
