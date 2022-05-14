/**
 *	@file	constexpr_test.hpp
 *
 *	@brief	
 */

#ifndef UNIT_TEST_FND_TEST_COMMON_CONSTEXPR_TEST_HPP
#define UNIT_TEST_FND_TEST_COMMON_CONSTEXPR_TEST_HPP

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX11_CONSTEXPR)

#  define HAMON_CXX11_CONSTEXPR_EXPECT_EQ(x, y)	\
	static_assert((x) == (y), "");	\
	EXPECT_EQ(x, y)

#  define HAMON_CXX11_CONSTEXPR_EXPECT_NE(x, y)	\
	static_assert((x) != (y), "");	\
	EXPECT_NE(x, y)

#  define HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(x)	\
	static_assert((x), #x);	\
	EXPECT_TRUE(x)

#  define HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x)	\
	static_assert(!(x), #x);	\
	EXPECT_FALSE(x)

#else

#  define HAMON_CXX11_CONSTEXPR_EXPECT_EQ(x, y)	\
	EXPECT_EQ(x, y)

#  define HAMON_CXX11_CONSTEXPR_EXPECT_NE(x, y)	\
	EXPECT_NE(x, y)

#  define HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(x)	\
	EXPECT_TRUE(x)

#  define HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(x)	\
	EXPECT_FALSE(x)

#endif


#if defined(HAMON_HAS_CXX14_CONSTEXPR)

#  define HAMON_CXX14_CONSTEXPR_EXPECT_EQ(x, y)	\
	static_assert((x) == (y), "");	\
	EXPECT_EQ(x, y)

#  define HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(x)	\
	static_assert((x), #x);	\
	EXPECT_TRUE(x)

#  define HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(x)	\
	static_assert(!(x), #x);	\
	EXPECT_FALSE(x)

#else

#  define HAMON_CXX14_CONSTEXPR_EXPECT_EQ(x, y)	\
	EXPECT_EQ(x, y)

#  define HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(x)	\
	EXPECT_TRUE(x)

#  define HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(x)	\
	EXPECT_FALSE(x)

#endif


#if defined(HAMON_HAS_CXX17_CONSTEXPR)

#  define HAMON_CXX17_CONSTEXPR_EXPECT_EQ(x, y)	\
	static_assert((x) == (y), "");	\
	EXPECT_EQ(x, y)

#  define HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(x)	\
	static_assert((x), #x);	\
	EXPECT_TRUE(x)

#  define HAMON_CXX17_CONSTEXPR_EXPECT_FALSE(x)	\
	static_assert(!(x), #x);	\
	EXPECT_FALSE(x)

#else

#  define HAMON_CXX17_CONSTEXPR_EXPECT_EQ(x, y)	\
	EXPECT_EQ(x, y)

#  define HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(x)	\
	EXPECT_TRUE(x)

#  define HAMON_CXX17_CONSTEXPR_EXPECT_FALSE(x)	\
	EXPECT_FALSE(x)

#endif

#endif // UNIT_TEST_FND_TEST_COMMON_CONSTEXPR_TEST_HPP
