/**
 *	@file	unit_test_variant_visit_r.cpp
 *
 *	@brief	visit<R>() のテスト
 *
 *	template<class R, class Visitor, class... Variants>
 *	constexpr R visit(Visitor&& vis, Variants&&... vars);
 */

#include <hamon/variant/visit.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/variant/get.hpp>
#include <hamon/variant/bad_variant_access.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace visit_r_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct F0
{
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR int operator()(Args&&...) &       { return 1; }

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR int operator()(Args&&...) const&  { return 2; }

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR int operator()(Args&&...) &&      { return 3; }

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR int operator()(Args&&...) const&& { return 4; }
};

inline HAMON_CXX14_CONSTEXPR bool VisitorForwardingTest()
{
	F0 f;
	F0 const cf;
	{
		VERIFY(hamon::visit<int>(f) == 1);
		VERIFY(hamon::visit<int>(cf) == 2);
		VERIFY(hamon::visit<int>(hamon::move(f)) == 3);
		VERIFY(hamon::visit<int>(hamon::move(cf)) == 4);
		//hamon::visit<void>(f);
		//hamon::visit<void>(cf);
		//hamon::visit<void>(hamon::move(f));
		//hamon::visit<void>(hamon::move(cf));
	}
	{
		const hamon::variant<float> v(hamon::in_place_index_t<0>{}, 0.5f);
		VERIFY(hamon::visit<long>(f, v) == 1);
		VERIFY(hamon::visit<long>(cf, v) == 2);
		VERIFY(hamon::visit<long>(hamon::move(f), v) == 3);
		VERIFY(hamon::visit<long>(hamon::move(cf), v) == 4);
		hamon::visit<void>(f, v);
		hamon::visit<void>(cf, v);
		hamon::visit<void>(hamon::move(f), v);
		hamon::visit<void>(hamon::move(cf), v);
	}
	{
		const hamon::variant<int, const long> v(hamon::in_place_index_t<0>{}, 42);
		VERIFY(hamon::visit<long long>(f, v) == 1);
		VERIFY(hamon::visit<long long>(cf, v) == 2);
		VERIFY(hamon::visit<long long>(hamon::move(f), v) == 3);
		VERIFY(hamon::visit<long long>(hamon::move(cf), v) == 4);
		hamon::visit<void>(f, v);
		hamon::visit<void>(cf, v);
		hamon::visit<void>(hamon::move(f), v);
		hamon::visit<void>(hamon::move(cf), v);
	}
	{
		const hamon::variant<const int, float> v1(hamon::in_place_index_t<0>{}, 42);
		const hamon::variant<int, long, double> v2(hamon::in_place_index_t<1>{}, 42);
		VERIFY(hamon::visit<int>(f, v1, v2) == 1);
		VERIFY(hamon::visit<int>(cf, v1, v2) == 2);
		VERIFY(hamon::visit<int>(hamon::move(f), v1, v2) == 3);
		VERIFY(hamon::visit<int>(hamon::move(cf), v1, v2) == 4);
		hamon::visit<void>(f, v1, v2);
		hamon::visit<void>(cf, v1, v2);
		hamon::visit<void>(hamon::move(f), v1, v2);
		hamon::visit<void>(hamon::move(cf), v1, v2);
	}
	{
		const hamon::variant<const int, float> v1(hamon::in_place_index_t<1>{}, 1.0f);
		const hamon::variant<const int, float> v2(hamon::in_place_index_t<0>{}, 2);
		const hamon::variant<int, long, double> v3(hamon::in_place_index_t<0>{}, 3);
		const hamon::variant<int, long, double> v4(hamon::in_place_index_t<2>{}, 4);
		const hamon::variant<int, long, double> v5(hamon::in_place_index_t<1>{}, 5);
		VERIFY(hamon::visit<long>(f, v1, v2, v3, v4, v5) == 1);
		VERIFY(hamon::visit<long>(cf, v1, v2, v3, v4, v5) == 2);
		VERIFY(hamon::visit<long>(hamon::move(f), v1, v2, v3, v4, v5) == 3);
		VERIFY(hamon::visit<long>(hamon::move(cf), v1, v2, v3, v4, v5) == 4);
		hamon::visit<void>(f, v1, v2, v3, v4, v5);
		hamon::visit<void>(cf, v1, v2, v3, v4, v5);
		hamon::visit<void>(hamon::move(f), v1, v2, v3, v4, v5);
		hamon::visit<void>(hamon::move(cf), v1, v2, v3, v4, v5);
	}
	return true;
}

struct F1
{
	template <typename Arg>
	HAMON_CXX14_CONSTEXPR int operator()(Arg&)        const { return 1; }
	
	template <typename Arg>
	HAMON_CXX14_CONSTEXPR int operator()(Arg const&)  const { return 2; }
	
	template <typename Arg>
	HAMON_CXX14_CONSTEXPR int operator()(Arg&&)       const { return 3; }

	template <typename Arg>
	HAMON_CXX14_CONSTEXPR int operator()(Arg const&&) const { return 4; }
};

inline HAMON_CXX14_CONSTEXPR bool ArgumentForwardingTest()
{
	F1 f;
	{
		hamon::variant<float> v(hamon::in_place_index_t<0>{}, 0.5f);
		const auto& cv = v;
		VERIFY(hamon::visit<int>(f, v) == 1);
		VERIFY(hamon::visit<int>(f, cv) == 2);
		VERIFY(hamon::visit<int>(f, hamon::move(v)) == 3);
		VERIFY(hamon::visit<int>(f, hamon::move(cv)) == 4);
		hamon::visit<void>(f, v);
		hamon::visit<void>(f, cv);
		hamon::visit<void>(f, hamon::move(v));
		hamon::visit<void>(f, hamon::move(cv));
	}
	{
		hamon::variant<const float> v(hamon::in_place_index_t<0>{}, 0.5f);
		const auto& cv = v;
		VERIFY(hamon::visit<int>(f, v) == 2);
		VERIFY(hamon::visit<int>(f, cv) == 2);
		VERIFY(hamon::visit<int>(f, hamon::move(v)) == 4);
		VERIFY(hamon::visit<int>(f, hamon::move(cv)) == 4);
		hamon::visit<void>(f, v);
		hamon::visit<void>(f, cv);
		hamon::visit<void>(f, hamon::move(v));
		hamon::visit<void>(f, hamon::move(cv));
	}
	{
		hamon::variant<int, const long> v(hamon::in_place_index_t<0>{}, 42);
		const auto& cv = v;
		VERIFY(hamon::visit<long>(f, v) == 1);
		VERIFY(hamon::visit<long>(f, cv) == 2);
		VERIFY(hamon::visit<long>(f, hamon::move(v)) == 3);
		VERIFY(hamon::visit<long>(f, hamon::move(cv)) == 4);
		hamon::visit<void>(f, v);
		hamon::visit<void>(f, cv);
		hamon::visit<void>(f, hamon::move(v));
		hamon::visit<void>(f, hamon::move(cv));
	}
	{
		hamon::variant<int, const long> v(hamon::in_place_index_t<1>{}, 42);
		const auto& cv = v;
		VERIFY(hamon::visit<long long>(f, v) == 2);
		VERIFY(hamon::visit<long long>(f, cv) == 2);
		VERIFY(hamon::visit<long long>(f, hamon::move(v)) == 4);
		VERIFY(hamon::visit<long long>(f, hamon::move(cv)) == 4);
		hamon::visit<void>(f, v);
		hamon::visit<void>(f, cv);
		hamon::visit<void>(f, hamon::move(v));
		hamon::visit<void>(f, hamon::move(cv));
	}
	return true;
}

struct F2
{
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR F2&        operator()(Args&&...) &       { return *this; }

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR F2 const&  operator()(Args&&...) const&  { return *this; }

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR F2&&       operator()(Args&&...) &&      { return hamon::move(*this); }

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR F2 const&& operator()(Args&&...) const&& { return hamon::move(*this); }

	HAMON_CXX11_CONSTEXPR operator int() const;
};

inline HAMON_CXX14_CONSTEXPR bool ReturnTypeTest()
{
	{
		F2 f;
		F2 const cf;
		static_assert(hamon::is_same<decltype(hamon::visit<int>(f)), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<int>(cf)), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<int>(hamon::move(f))), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<int>(hamon::move(cf))), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(f)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(cf)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(hamon::move(f))), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(hamon::move(cf))), void>::value, "");
	}
	{
		F2 f;
		F2 const cf;
		const hamon::variant<float> v(hamon::in_place_index_t<0>{}, 0.5f);
		static_assert(hamon::is_same<decltype(hamon::visit<int>(f, v)), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<int>(cf, v)), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<int>(hamon::move(f), v)), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<int>(hamon::move(cf), v)), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(f, v)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(cf, v)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(hamon::move(f), v)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(hamon::move(cf), v)), void>::value, "");
	}
	{
		F2 f;
		F2 const cf;
		const hamon::variant<int, const long> v(hamon::in_place_index_t<0>{}, 42);
		static_assert(hamon::is_same<decltype(hamon::visit<long>(f, v)), long>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<long>(cf, v)), long>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<long>(hamon::move(f), v)), long>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<long>(hamon::move(cf), v)), long>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(f, v)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(cf, v)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(hamon::move(f), v)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(hamon::move(cf), v)), void>::value, "");
	}
	{
		F2 f;
		F2 const cf;
		const hamon::variant<const int, float> v1(hamon::in_place_index_t<0>{}, 42);
		const hamon::variant<int, long, double> v2(hamon::in_place_index_t<1>{}, 42);
		static_assert(hamon::is_same<decltype(hamon::visit<long>(f, v1, v2)), long>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<long>(cf, v1, v2)), long>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<long>(hamon::move(f), v1, v2)), long>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<long>(hamon::move(cf), v1, v2)), long>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(f, v1, v2)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(cf, v1, v2)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(hamon::move(f), v1, v2)), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit<void>(hamon::move(cf), v1, v2)), void>::value, "");
	}
	return true;
}

struct ReturnArity
{
	template <typename... Args>
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(Args&&...) const { return sizeof...(Args); }
};

struct T1{int value;};
struct T2{int value;};
struct T3{int value;};

struct F3
{
	HAMON_CXX11_CONSTEXPR int operator()(T1, T1) const { return 0; }
	HAMON_CXX11_CONSTEXPR int operator()(T1, T2) const { return 1; }
	HAMON_CXX11_CONSTEXPR int operator()(T1, T3) const { return 2; }
	HAMON_CXX11_CONSTEXPR int operator()(T2, T1) const { return 3; }
	HAMON_CXX11_CONSTEXPR int operator()(T2, T2) const { return 4; }
	HAMON_CXX11_CONSTEXPR int operator()(T2, T3) const { return 5; }
	HAMON_CXX11_CONSTEXPR int operator()(T3, T1) const { return 6; }
	HAMON_CXX11_CONSTEXPR int operator()(T3, T2) const { return 7; }
	HAMON_CXX11_CONSTEXPR int operator()(T3, T3) const { return 8; }
};

inline void ConstexprTest()
{
	{
		HAMON_CXX11_CONSTEXPR ReturnArity f;
		HAMON_CXX11_CONSTEXPR hamon::variant<float> v(hamon::in_place_index_t<0>{}, 0.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<hamon::size_t>(f) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<hamon::size_t>(f, v) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<hamon::size_t>(f, v, v) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<hamon::size_t>(f, v, v, v) == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR ReturnArity f;
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long, double> v(hamon::in_place_index_t<0>{}, 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<hamon::size_t>(f) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<hamon::size_t>(f, v) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<hamon::size_t>(f, v, v) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<hamon::size_t>(f, v, v, v) == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR F3 f;
		HAMON_CXX11_CONSTEXPR hamon::variant<T1, T2, T3> v0(T1{42});
		HAMON_CXX11_CONSTEXPR hamon::variant<T1, T2, T3> v1(T2{42});
		HAMON_CXX11_CONSTEXPR hamon::variant<T1, T2, T3> v2(T3{42});
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<int>(f, v0, v0) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<int>(f, v0, v1) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<int>(f, v0, v2) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<int>(f, v1, v0) == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<int>(f, v1, v1) == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<int>(f, v1, v2) == 5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<int>(f, v2, v0) == 6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<int>(f, v2, v1) == 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit<int>(f, v2, v2) == 8);
	}
}

struct Doubling
{
	void operator()(int& n)
	{
		n *= 2;
	}

	void operator()(hamon::string& s)
	{
		s += s;
	}
};

inline void RuntimeTest()
{
	{
		hamon::variant<int, hamon::string> v = 2;
		EXPECT_EQ(2, hamon::adl_get<int>(v));
		hamon::visit<void>(Doubling{}, v);
		EXPECT_EQ(4, hamon::adl_get<int>(v));

		v = "Hello";
		EXPECT_EQ(hamon::string("Hello"), hamon::adl_get<hamon::string>(v));
		hamon::visit<void>(Doubling{}, v);
		EXPECT_EQ(hamon::string("HelloHello"), hamon::adl_get<hamon::string>(v));
	}
}

#if !defined(HAMON_NO_EXCEPTIONS)

struct MakeEmptyT
{
	int value;
	MakeEmptyT(int v) : value(v) {}
	MakeEmptyT(MakeEmptyT const&) = default;
	MakeEmptyT(MakeEmptyT &&) : value() { throw 42; }
	MakeEmptyT& operator=(MakeEmptyT const&) { throw 42; }
	MakeEmptyT& operator=(MakeEmptyT &&) { throw 42; }
};

template <typename Variant>
void MakeEmpty(Variant& v)
{
	Variant v2(hamon::in_place_type_t<MakeEmptyT>{}, 0);
	try
	{
		v = hamon::move(v2);
	}
	catch (...)
	{
	}
}

#endif

inline void ExceptionsTest()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	ReturnArity f;
	{
		hamon::variant<int, MakeEmptyT> v{};
		MakeEmpty(v);
		EXPECT_THROW(hamon::visit<hamon::size_t>(f, v), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, MakeEmptyT> v1{};
		hamon::variant<int, MakeEmptyT> v2{};
		MakeEmpty(v1);
		MakeEmpty(v2);
		EXPECT_THROW(hamon::visit<void>(f, v1, v2), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, MakeEmptyT> v1{};
		hamon::variant<int, MakeEmptyT> v2{};
		MakeEmpty(v1);
		EXPECT_THROW(hamon::visit<hamon::size_t>(f, v1, v2), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, MakeEmptyT> v1{};
		hamon::variant<int, MakeEmptyT> v2{};
		MakeEmpty(v2);
		EXPECT_THROW(hamon::visit<void>(f, v1, v2), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, MakeEmptyT> v1{};
		hamon::variant<int, MakeEmptyT> v2{};
		EXPECT_NO_THROW(hamon::visit<hamon::size_t>(f, v1, v2));
	}
	{
		hamon::variant<int, float, MakeEmptyT>   v1{};
		hamon::variant<char, void*, long>        v2{};
		hamon::variant<float, double, char, int> v3{};
		MakeEmpty(v1);
		EXPECT_THROW(hamon::visit<void>(f, v1, v2, v3), hamon::bad_variant_access);
		EXPECT_THROW(hamon::visit<void>(f, v3, v1, v2), hamon::bad_variant_access);
		EXPECT_THROW(hamon::visit<void>(f, v2, v3, v1), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, float, MakeEmptyT>   v1{};
		hamon::variant<char, void*, long>        v2{};
		hamon::variant<float, double, char, int> v3{};
		EXPECT_NO_THROW(hamon::visit<hamon::size_t>(f, v1, v2, v3));
		EXPECT_NO_THROW(hamon::visit<hamon::size_t>(f, v3, v1, v2));
		EXPECT_NO_THROW(hamon::visit<hamon::size_t>(f, v2, v3, v1));
	}
#endif
}

struct MyVariant : public hamon::variant<int, hamon::string>
{
	using hamon::variant<int, hamon::string>::variant;
	using hamon::variant<int, hamon::string>::operator=;
};

inline void DerivedFromVariantTest()
{
	{
		auto v = MyVariant(hamon::in_place_index_t<0>{}, 2);
		EXPECT_EQ(2, hamon::adl_get<int>(v));
		hamon::visit<void>(Doubling{}, v);
		EXPECT_EQ(4, hamon::adl_get<int>(v));

		v = "Hello";
		EXPECT_EQ(hamon::string("Hello"), hamon::adl_get<hamon::string>(v));
		hamon::visit<void>(Doubling{}, v);
		EXPECT_EQ(hamon::string("HelloHello"), hamon::adl_get<hamon::string>(v));
	}
}

struct AnyVisitor
{
	template <typename... Args>
	void operator()(Args const&...) const;
};

struct IdentityVisitor
{
	template <typename T>
	T operator()(T x) const;
};

struct F4
{
	HAMON_CXX11_CONSTEXPR int operator()(T1, T1) const;
	HAMON_CXX11_CONSTEXPR int operator()(T1, T2) const;
	HAMON_CXX11_CONSTEXPR int operator()(T1, T3) const;
	HAMON_CXX11_CONSTEXPR int operator()(T2, T1) const;
	HAMON_CXX11_CONSTEXPR int operator()(T2, T2) const;
//	HAMON_CXX11_CONSTEXPR int operator()(T2, T3) const;
	HAMON_CXX11_CONSTEXPR int operator()(T3, T1) const;
	HAMON_CXX11_CONSTEXPR int operator()(T3, T2) const;
	HAMON_CXX11_CONSTEXPR int operator()(T3, T3) const;
};

template <typename R, typename Visitor, typename... Args>
using invoke_visit = decltype(hamon::visit<R>(hamon::declval<Visitor&>(), hamon::declval<Args>()...));

inline void SfinaeTest()
{
#if !defined(HAMON_USE_STD_VARIANT)
	struct BadVariant : private hamon::variant<long, float> {};

	static_assert( hamon::is_detected<invoke_visit, void, AnyVisitor, hamon::variant<int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, AnyVisitor, hamon::variant<long, float>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, AnyVisitor, MyVariant>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, AnyVisitor, hamon::variant<int>, hamon::variant<long, float>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, AnyVisitor, hamon::variant<int>, MyVariant>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, AnyVisitor, hamon::variant<int>, hamon::variant<float>, hamon::variant<long>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void, AnyVisitor, int>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void, AnyVisitor, BadVariant>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void, AnyVisitor, hamon::variant<int>, int>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void, AnyVisitor, hamon::variant<int>, BadVariant>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void, AnyVisitor, hamon::variant<int>, hamon::variant<float>, BadVariant>::value, "");

	static_assert( hamon::is_detected<invoke_visit, int, IdentityVisitor, hamon::variant<int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, IdentityVisitor, hamon::variant<long>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int, IdentityVisitor, hamon::variant<int*>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, IdentityVisitor, hamon::variant<int, int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, IdentityVisitor, hamon::variant<long, long>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, IdentityVisitor, hamon::variant<int, long>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int, IdentityVisitor, hamon::variant<int, int*>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int, IdentityVisitor, hamon::variant<void*, int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, IdentityVisitor, hamon::variant<int, int, long>>::value, "");

	static_assert(!hamon::is_detected<invoke_visit, void*, IdentityVisitor, hamon::variant<int>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void*, IdentityVisitor, hamon::variant<long>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void*, IdentityVisitor, hamon::variant<int*>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void*, IdentityVisitor, hamon::variant<int, int>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void*, IdentityVisitor, hamon::variant<long, long>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void*, IdentityVisitor, hamon::variant<int, long>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void*, IdentityVisitor, hamon::variant<int, int*>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void*, IdentityVisitor, hamon::variant<void*, int>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void*, IdentityVisitor, hamon::variant<int, int, long>>::value, "");

	static_assert( hamon::is_detected<invoke_visit, void, IdentityVisitor, hamon::variant<int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, IdentityVisitor, hamon::variant<long>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, IdentityVisitor, hamon::variant<int*>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, IdentityVisitor, hamon::variant<int, int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, IdentityVisitor, hamon::variant<long, long>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, IdentityVisitor, hamon::variant<int, long>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, IdentityVisitor, hamon::variant<int, int*>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, IdentityVisitor, hamon::variant<void*, int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, IdentityVisitor, hamon::variant<int, int, long>>::value, "");

	// 引数の数チェック
	static_assert(!hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int, F4, hamon::variant<T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int, F4, hamon::variant<T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1, T2, T3>>::value, "");

	// 引数の型チェック
	static_assert( hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1>, hamon::variant<T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int, F4, hamon::variant<T2>, hamon::variant<T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, F4, hamon::variant<T3>, hamon::variant<T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1, T2>, hamon::variant<T1, T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1, T3>, hamon::variant<T1, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1, T3>, hamon::variant<T1, T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int, F4, hamon::variant<T2, T3>, hamon::variant<T2, T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1, T2, T3>, hamon::variant<T1, T2, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1, T2, T3>, hamon::variant<T1, T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1, T3>, hamon::variant<T1, T2, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, int, F4, hamon::variant<T1, T2, T1>, hamon::variant<T2, T1>>::value, "");

	// 戻り値の型はvoidでもOK
	static_assert( hamon::is_detected<invoke_visit, void, F4, hamon::variant<T1>, hamon::variant<T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void, F4, hamon::variant<T2>, hamon::variant<T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, F4, hamon::variant<T3>, hamon::variant<T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, F4, hamon::variant<T1, T2>, hamon::variant<T1, T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, F4, hamon::variant<T1, T3>, hamon::variant<T1, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, F4, hamon::variant<T1, T3>, hamon::variant<T1, T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void, F4, hamon::variant<T2, T3>, hamon::variant<T2, T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, void, F4, hamon::variant<T1, T2, T3>, hamon::variant<T1, T2, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, void, F4, hamon::variant<T1, T2, T1>, hamon::variant<T2, T1>>::value, "");

	// 戻り値の型チェック
	static_assert( hamon::is_detected<invoke_visit, long, F4, hamon::variant<T1>, hamon::variant<T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, long, F4, hamon::variant<T2>, hamon::variant<T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, long, F4, hamon::variant<T3>, hamon::variant<T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, long, F4, hamon::variant<T1, T2>, hamon::variant<T1, T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, long, F4, hamon::variant<T1, T3>, hamon::variant<T1, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, long, F4, hamon::variant<T1, T3>, hamon::variant<T1, T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, long, F4, hamon::variant<T2, T3>, hamon::variant<T2, T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, long, F4, hamon::variant<T1, T2, T3>, hamon::variant<T1, T2, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, long, F4, hamon::variant<T1, T2, T1>, hamon::variant<T2, T1>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int*, F4, hamon::variant<T1>, hamon::variant<T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int*, F4, hamon::variant<T2>, hamon::variant<T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int*, F4, hamon::variant<T3>, hamon::variant<T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int*, F4, hamon::variant<T1, T2>, hamon::variant<T1, T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int*, F4, hamon::variant<T1, T3>, hamon::variant<T1, T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int*, F4, hamon::variant<T1, T3>, hamon::variant<T1, T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int*, F4, hamon::variant<T2, T3>, hamon::variant<T2, T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int*, F4, hamon::variant<T1, T2, T3>, hamon::variant<T1, T2, T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, int*, F4, hamon::variant<T1, T2, T1>, hamon::variant<T2, T1>>::value, "");
#endif
}

GTEST_TEST(VariantTest, VisitRTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(VisitorForwardingTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ArgumentForwardingTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReturnTypeTest());
	ConstexprTest();
	RuntimeTest();
	ExceptionsTest();
	DerivedFromVariantTest();
	SfinaeTest();
}

#undef VERIFY

}	// namespace visit_r_test

}	// namespace hamon_variant_test
