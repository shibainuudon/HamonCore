/**
 *	@file	unit_test_type_traits_remove_all_extents.cpp
 *
 *	@brief	remove_all_extents のテスト
 */

#include <hamon/type_traits/remove_all_extents.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::remove_all_extents, /**/          , /**/);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const         , const);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile,       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile, const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,                &,                &);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, *               , *               );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, * const         , * const         );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, *       volatile, *       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, * const volatile, * const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          *, const          *);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile *,       volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile *, const volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,                [2],               );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          [2], const         );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile [2],       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile [2], const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,                [2][3],               );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          [2][3], const         );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile [2][3],       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile [2][3], const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,                [5][10][20],               );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          [5][10][20], const         );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile [5][10][20],       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile [5][10][20], const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,                [],               );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          [], const         );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile [],       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile [], const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,                [][3],               );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          [][3], const         );
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile [][3],       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile [][3], const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_all_extents, const volatile (&&)[2], const volatile (&&)[2]);
