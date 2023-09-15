/**
 *	@file	unit_test_variant_visit.cpp
 *
 *	@brief	visit() のテスト
 *
 *	template<class Visitor, class... Variants>
 *	constexpr see below visit(Visitor&& vis, Variants&&... vars);
 */

#include <hamon/variant/visit.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/variant/get.hpp>
#include <hamon/variant/bad_variant_access.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace visit_test
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
		VERIFY(hamon::visit(f) == 1);
		VERIFY(hamon::visit(cf) == 2);
		VERIFY(hamon::visit(hamon::move(f)) == 3);
		VERIFY(hamon::visit(hamon::move(cf)) == 4);
	}
	{
		const hamon::variant<float> v(hamon::in_place_index_t<0>{}, 0.5f);
		VERIFY(hamon::visit(f, v) == 1);
		VERIFY(hamon::visit(cf, v) == 2);
		VERIFY(hamon::visit(hamon::move(f), v) == 3);
		VERIFY(hamon::visit(hamon::move(cf), v) == 4);
	}
	{
		const hamon::variant<int, const long> v(hamon::in_place_index_t<0>{}, 42);
		VERIFY(hamon::visit(f, v) == 1);
		VERIFY(hamon::visit(cf, v) == 2);
		VERIFY(hamon::visit(hamon::move(f), v) == 3);
		VERIFY(hamon::visit(hamon::move(cf), v) == 4);
	}
	{
		const hamon::variant<const int, float> v1(hamon::in_place_index_t<0>{}, 42);
		const hamon::variant<int, long, double> v2(hamon::in_place_index_t<1>{}, 42);
		VERIFY(hamon::visit(f, v1, v2) == 1);
		VERIFY(hamon::visit(cf, v1, v2) == 2);
		VERIFY(hamon::visit(hamon::move(f), v1, v2) == 3);
		VERIFY(hamon::visit(hamon::move(cf), v1, v2) == 4);
	}
	{
		const hamon::variant<const int, float> v1(hamon::in_place_index_t<1>{}, 1.0f);
		const hamon::variant<const int, float> v2(hamon::in_place_index_t<0>{}, 2);
		const hamon::variant<int, long, double> v3(hamon::in_place_index_t<0>{}, 3);
		const hamon::variant<int, long, double> v4(hamon::in_place_index_t<2>{}, 4);
		const hamon::variant<int, long, double> v5(hamon::in_place_index_t<1>{}, 5);
		VERIFY(hamon::visit(f, v1, v2, v3, v4, v5) == 1);
		VERIFY(hamon::visit(cf, v1, v2, v3, v4, v5) == 2);
		VERIFY(hamon::visit(hamon::move(f), v1, v2, v3, v4, v5) == 3);
		VERIFY(hamon::visit(hamon::move(cf), v1, v2, v3, v4, v5) == 4);
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
		VERIFY(hamon::visit(f, v) == 1);
		VERIFY(hamon::visit(f, cv) == 2);
		VERIFY(hamon::visit(f, hamon::move(v)) == 3);
		VERIFY(hamon::visit(f, hamon::move(cv)) == 4);
	}
	{
		hamon::variant<const float> v(hamon::in_place_index_t<0>{}, 0.5f);
		const auto& cv = v;
		VERIFY(hamon::visit(f, v) == 2);
		VERIFY(hamon::visit(f, cv) == 2);
		VERIFY(hamon::visit(f, hamon::move(v)) == 4);
		VERIFY(hamon::visit(f, hamon::move(cv)) == 4);
	}
	{
		hamon::variant<int, const long> v(hamon::in_place_index_t<0>{}, 42);
		const auto& cv = v;
		VERIFY(hamon::visit(f, v) == 1);
		VERIFY(hamon::visit(f, cv) == 2);
		VERIFY(hamon::visit(f, hamon::move(v)) == 3);
		VERIFY(hamon::visit(f, hamon::move(cv)) == 4);
	}
	{
		hamon::variant<int, const long> v(hamon::in_place_index_t<1>{}, 42);
		const auto& cv = v;
		VERIFY(hamon::visit(f, v) == 2);
		VERIFY(hamon::visit(f, cv) == 2);
		VERIFY(hamon::visit(f, hamon::move(v)) == 4);
		VERIFY(hamon::visit(f, hamon::move(cv)) == 4);
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
};

inline HAMON_CXX14_CONSTEXPR bool ReturnTypeTest()
{
	{
		F2 f;
		F2 const cf;
		static_assert(hamon::is_same<decltype(hamon::visit(f)), F2&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(cf)), F2 const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(hamon::move(f))), F2&&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(hamon::move(cf))), F2 const&&>::value, "");
	}
	{
		F2 f;
		F2 const cf;
		const hamon::variant<float> v(hamon::in_place_index_t<0>{}, 0.5f);
		static_assert(hamon::is_same<decltype(hamon::visit(f, v)), F2&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(cf, v)), F2 const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(hamon::move(f), v)), F2&&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(hamon::move(cf), v)), F2 const&&>::value, "");
	}
	{
		F2 f;
		F2 const cf;
		const hamon::variant<int, const long> v(hamon::in_place_index_t<0>{}, 42);
		static_assert(hamon::is_same<decltype(hamon::visit(f, v)), F2&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(cf, v)), F2 const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(hamon::move(f), v)), F2&&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(hamon::move(cf), v)), F2 const&&>::value, "");
	}
	{
		F2 f;
		F2 const cf;
		const hamon::variant<const int, float> v1(hamon::in_place_index_t<0>{}, 42);
		const hamon::variant<int, long, double> v2(hamon::in_place_index_t<1>{}, 42);
		static_assert(hamon::is_same<decltype(hamon::visit(f, v1, v2)), F2&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(cf, v1, v2)), F2 const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(hamon::move(f), v1, v2)), F2&&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::visit(hamon::move(cf), v1, v2)), F2 const&&>::value, "");
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
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v, v) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v, v, v) == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR ReturnArity f;
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long, double> v(hamon::in_place_index_t<0>{}, 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v, v) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v, v, v) == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR F3 f;
		HAMON_CXX11_CONSTEXPR hamon::variant<T1, T2, T3> v0(T1{42});
		HAMON_CXX11_CONSTEXPR hamon::variant<T1, T2, T3> v1(T2{42});
		HAMON_CXX11_CONSTEXPR hamon::variant<T1, T2, T3> v2(T3{42});
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v0, v0) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v0, v1) == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v0, v2) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v1, v0) == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v1, v1) == 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v1, v2) == 5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v2, v0) == 6);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v2, v1) == 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::visit(f, v2, v2) == 8);
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
		hamon::visit(Doubling{}, v);
		EXPECT_EQ(4, hamon::adl_get<int>(v));

		v = "Hello";
		EXPECT_EQ(hamon::string("Hello"), hamon::adl_get<hamon::string>(v));
		hamon::visit(Doubling{}, v);
		EXPECT_EQ(hamon::string("HelloHello"), hamon::adl_get<hamon::string>(v));
	}
#if defined(HAMON_HAS_CXX14_GENERIC_LAMBDAS)
	{
		using var_t = hamon::variant<int, long, double, hamon::string>;
		hamon::vector<var_t> vec = { "hello", 15l, 10, 1.5 };

		std::stringstream ss;
		for (auto& v : vec)
		{
			hamon::visit([&](auto&& arg) { ss << arg << ", "; }, v);
		}
		EXPECT_EQ("hello, 15, 10, 1.5, ", ss.str());
	}
#endif
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
		EXPECT_THROW(hamon::visit(f, v), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, MakeEmptyT> v1{};
		hamon::variant<int, MakeEmptyT> v2{};
		MakeEmpty(v1);
		MakeEmpty(v2);
		EXPECT_THROW(hamon::visit(f, v1, v2), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, MakeEmptyT> v1{};
		hamon::variant<int, MakeEmptyT> v2{};
		MakeEmpty(v1);
		EXPECT_THROW(hamon::visit(f, v1, v2), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, MakeEmptyT> v1{};
		hamon::variant<int, MakeEmptyT> v2{};
		MakeEmpty(v2);
		EXPECT_THROW(hamon::visit(f, v1, v2), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, MakeEmptyT> v1{};
		hamon::variant<int, MakeEmptyT> v2{};
		EXPECT_NO_THROW(hamon::visit(f, v1, v2));
	}
	{
		hamon::variant<int, float, MakeEmptyT>   v1{};
		hamon::variant<char, void*, long>        v2{};
		hamon::variant<float, double, char, int> v3{};
		MakeEmpty(v1);
		EXPECT_THROW(hamon::visit(f, v1, v2, v3), hamon::bad_variant_access);
		EXPECT_THROW(hamon::visit(f, v3, v1, v2), hamon::bad_variant_access);
		EXPECT_THROW(hamon::visit(f, v2, v3, v1), hamon::bad_variant_access);
	}
	{
		hamon::variant<int, float, MakeEmptyT>   v1{};
		hamon::variant<char, void*, long>        v2{};
		hamon::variant<float, double, char, int> v3{};
		EXPECT_NO_THROW(hamon::visit(f, v1, v2, v3));
		EXPECT_NO_THROW(hamon::visit(f, v3, v1, v2));
		EXPECT_NO_THROW(hamon::visit(f, v2, v3, v1));
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
		hamon::visit(Doubling{}, v);
		EXPECT_EQ(4, hamon::adl_get<int>(v));

		v = "Hello";
		EXPECT_EQ(hamon::string("Hello"), hamon::adl_get<hamon::string>(v));
		hamon::visit(Doubling{}, v);
		EXPECT_EQ(hamon::string("HelloHello"), hamon::adl_get<hamon::string>(v));
	}
}

struct AnyVisitor
{
	template <typename... Args>
	void operator()(Args const&...) const {}
};

struct IdentityVisitor
{
	template <typename T>
	T operator()(T x) const;
};

struct F4
{
	int   operator()(T1, T1) const;
	int   operator()(T1, T2) const;
	int   operator()(T1, T3) const;
	int   operator()(T2, T1) const;
	int   operator()(T2, T2) const;
	void* operator()(T2, T3) const;
	int   operator()(T3, T1) const;
	int   operator()(T3, T2) const;
	int   operator()(T3, T3) const;
};

template <typename Visitor, typename... Args>
using invoke_visit = decltype(hamon::visit(hamon::declval<Visitor&>(), hamon::declval<Args>()...));

inline void SfinaeTest()
{
	struct BadVariant : private hamon::variant<long, float> {};

	static_assert( hamon::is_detected<invoke_visit, AnyVisitor, hamon::variant<int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, AnyVisitor, hamon::variant<long, float>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, AnyVisitor, MyVariant>::value, "");
	static_assert( hamon::is_detected<invoke_visit, AnyVisitor, hamon::variant<int>, hamon::variant<long, float>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, AnyVisitor, hamon::variant<int>, MyVariant>::value, "");
	static_assert( hamon::is_detected<invoke_visit, AnyVisitor, hamon::variant<int>, hamon::variant<float>, hamon::variant<long>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, AnyVisitor, int>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, AnyVisitor, BadVariant>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, AnyVisitor, hamon::variant<int>, int>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, AnyVisitor, hamon::variant<int>, BadVariant>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, AnyVisitor, hamon::variant<int>, hamon::variant<float>, BadVariant>::value, "");

#if !defined(HAMON_USE_STD_VARIANT)
	static_assert( hamon::is_detected<invoke_visit, IdentityVisitor, hamon::variant<int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, IdentityVisitor, hamon::variant<long>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, IdentityVisitor, hamon::variant<int*>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, IdentityVisitor, hamon::variant<int, int>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, IdentityVisitor, hamon::variant<long, long>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, IdentityVisitor, hamon::variant<int, long>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, IdentityVisitor, hamon::variant<int, int*>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, IdentityVisitor, hamon::variant<void*, int>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, IdentityVisitor, hamon::variant<int, int, long>>::value, "");

	static_assert(!hamon::is_detected<invoke_visit, F4, hamon::variant<T1>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, F4, hamon::variant<T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, F4, hamon::variant<T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, F4, hamon::variant<T1, T2, T3>>::value, "");

	static_assert( hamon::is_detected<invoke_visit, F4, hamon::variant<T1>, hamon::variant<T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, F4, hamon::variant<T2>, hamon::variant<T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, F4, hamon::variant<T3>, hamon::variant<T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, F4, hamon::variant<T1, T2>, hamon::variant<T1, T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, F4, hamon::variant<T1, T3>, hamon::variant<T1, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, F4, hamon::variant<T1, T3>, hamon::variant<T1, T2>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, F4, hamon::variant<T2, T3>, hamon::variant<T2, T3>>::value, "");
	static_assert(!hamon::is_detected<invoke_visit, F4, hamon::variant<T1, T2, T3>, hamon::variant<T1, T2, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, F4, hamon::variant<T1, T2, T3>, hamon::variant<T1, T2>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, F4, hamon::variant<T1, T3>, hamon::variant<T1, T2, T3>>::value, "");
	static_assert( hamon::is_detected<invoke_visit, F4, hamon::variant<T1, T2, T1>, hamon::variant<T2, T1>>::value, "");
#endif
}

GTEST_TEST(VariantTest, VisitTest)
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

}	// namespace visit_test

}	// namespace hamon_variant_test
