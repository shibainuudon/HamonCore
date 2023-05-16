/**
 *	@file	unit_test_optional_observers.cpp
 *
 *	@brief	Observers関数のテスト
 *
 *	constexpr const T* operator->() const noexcept;
 *	constexpr T* operator->() noexcept;
 *	constexpr const T& operator*() const & noexcept;
 *	constexpr T& operator*() & noexcept;
 *	constexpr T&& operator*() && noexcept;
 *	constexpr const T&& operator*() const && noexcept;
 *	constexpr explicit operator bool() const noexcept;
 *	constexpr bool has_value() const noexcept;
 *	constexpr const T& value() const &;
 *	constexpr T& value() &;
 *	constexpr T&& value() &&;
 *	constexpr const T&& value() const &&;
 *	template<class U> constexpr T value_or(U&& v) const &;
 *	template<class U> constexpr T value_or(U&& v) &&;
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace observers_test
{

struct S
{
	int i;
};

inline void* operator&(S const&)
{
	return nullptr;
}

GTEST_TEST(OptionalTest, ObserversTest)
{
	{
		hamon::optional<S> o{ S{ 51 } };
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE((*o).i == 51);
		EXPECT_TRUE((*hamon::move(o)).i == 51);
		EXPECT_TRUE(o->i == 51);
		EXPECT_TRUE(o->i == (*o).i);
		EXPECT_TRUE(&o->i == &(*o).i);
		EXPECT_TRUE(hamon::move(o)->i == 51);
		EXPECT_TRUE(o.value().i == 51);
		EXPECT_TRUE(o.value().i == (*o).i);
		EXPECT_TRUE(&o.value().i == &(*o).i);
		EXPECT_TRUE(hamon::move(o).value().i == 51);
		S fallback{ 3 };
		EXPECT_TRUE(o.value_or(fallback).i == 51);
		EXPECT_TRUE(o.value_or(fallback).i == (*o).i);
		EXPECT_TRUE(hamon::move(o).value_or(fallback).i == 51);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<S> o{ S{ 51 } };
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((bool)o);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((*o).i == 51);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((*hamon::move(o)).i == 51);
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(o->i == 51);
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(o->i == (*o).i);
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(&o->i == &(*o).i);
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(hamon::move(o)->i == 51);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o.value().i == 51);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o.value().i == (*o).i);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(&o.value().i == &(*o).i);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::move(o).value().i == 51);
		HAMON_CXX11_CONSTEXPR S fallback{ 3 };
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o.value_or(fallback).i == 51);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o.value_or(fallback).i == (*o).i);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::move(o).value_or(fallback).i == 51);
	}
	{
		hamon::optional<S> o;
		EXPECT_TRUE(!o);
		EXPECT_THROW((void)o.value(), hamon::bad_optional_access);
		EXPECT_THROW((void)hamon::move(o).value(), hamon::bad_optional_access);
		S fallback{ 3 };
		EXPECT_TRUE(o.value_or(fallback).i == 3);
		EXPECT_TRUE(hamon::move(o).value_or(fallback).i == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<S> o;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!o);
		EXPECT_THROW((void)o.value(), hamon::bad_optional_access);
		EXPECT_THROW((void)hamon::move(o).value(), hamon::bad_optional_access);
		HAMON_CXX11_CONSTEXPR S fallback{ 3 };
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(o.value_or(fallback).i == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::move(o).value_or(fallback).i == 3);
	}
}

}	// namespace observers_test

}	// namespace hamon_optional_test
