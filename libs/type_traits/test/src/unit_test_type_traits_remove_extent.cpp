/**
 *	@file	unit_test_type_traits_remove_extent.cpp
 *
 *	@brief	remove_extent のテスト
 */

#include <hamon/type_traits/remove_extent.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::remove_extent, /**/          , /**/);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const         , const);
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile,       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile, const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_extent,                &,                &);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_extent, *               , *               );
HAMON_TRANSFORM_TEST(hamon::remove_extent, * const         , * const         );
HAMON_TRANSFORM_TEST(hamon::remove_extent, *       volatile, *       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_extent, * const volatile, * const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          *, const          *);
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile *,       volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile *, const volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_extent,                [2],               );
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          [2], const         );
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile [2],       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile [2], const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_extent,                [2][3],                [3]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          [2][3], const          [3]);
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile [2][3],       volatile [3]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile [2][3], const volatile [3]);
HAMON_TRANSFORM_TEST(hamon::remove_extent,                [5][10][20],                [10][20]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          [5][10][20], const          [10][20]);
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile [5][10][20],       volatile [10][20]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile [5][10][20], const volatile [10][20]);
HAMON_TRANSFORM_TEST(hamon::remove_extent,                [],               );
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          [], const         );
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile [],       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile [], const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_extent,                [][3],                [3]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          [][3], const          [3]);
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile [][3],       volatile [3]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile [][3], const volatile [3]);
HAMON_TRANSFORM_TEST(hamon::remove_extent,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_extent,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_extent,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_extent,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_extent, const volatile (&&)[2], const volatile (&&)[2]);
