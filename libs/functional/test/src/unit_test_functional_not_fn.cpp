﻿/**
 *	@file	unit_test_functional_not_fn.cpp
 *
 *	@brief	not_fn のテスト
 */

#include <hamon/functional/not_fn.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <string>
#include "constexpr_test.hpp"
//#include "tuple_test_utility.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunneeded-internal-declaration")
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon_functional_not_fn_test
{

bool returns_true() { return true; }

template <typename Ret = bool>
struct MoveOnlyCallable
{
	MoveOnlyCallable(MoveOnlyCallable const&) = delete;
	MoveOnlyCallable(MoveOnlyCallable&& other) noexcept
		: value(other.value)
	{
		other.value = !other.value;
	}

	template <typename... Args>
	Ret operator()(Args&&...) { return Ret{value}; }

	explicit MoveOnlyCallable(bool x) : value(x) {}

	Ret value;
};

template <typename Ret = bool>
struct CopyCallable
{
	CopyCallable(CopyCallable const& other)
		: value(other.value) {}

	CopyCallable(CopyCallable&& other) noexcept
		: value(other.value)
	{
		other.value = !other.value;
	}

	template <typename... Args>
	Ret operator()(Args&&...) { return Ret{value}; }

	explicit CopyCallable(bool x) : value(x) {}

	Ret value;
};

template <typename Ret = bool>
struct ConstCallable
{
	ConstCallable(ConstCallable const& other)
		: value(other.value) {}

	ConstCallable(ConstCallable&& other)
		: value(other.value)
	{
		other.value = !other.value;
	}

	template <typename... Args>
	Ret operator()(Args&&...) const { return Ret{value}; }

	explicit ConstCallable(bool x) : value(x) {}

	Ret value;
};

template <typename Ret = bool>
struct NoExceptCallable
{
	NoExceptCallable(NoExceptCallable const& other)
		: value(other.value) {}

	template <typename... Args>
	Ret operator()(Args&&...) noexcept { return Ret{value}; }

	template <typename... Args>
	Ret operator()(Args&&...) const noexcept { return Ret{value}; }

	explicit NoExceptCallable(bool x) : value(x) {}

	Ret value;
};

struct CopyAssignableWrapper
{
	CopyAssignableWrapper(CopyAssignableWrapper const&) = default;
	CopyAssignableWrapper(CopyAssignableWrapper&&) = default;
	CopyAssignableWrapper& operator=(CopyAssignableWrapper const&) = default;
	CopyAssignableWrapper& operator=(CopyAssignableWrapper &&) = default;

	template <typename... Args>
	bool operator()(Args&&...) { return value; }

	explicit CopyAssignableWrapper(bool x) : value(x) {}

	bool value;
};

struct MoveAssignableWrapper
{
	MoveAssignableWrapper(MoveAssignableWrapper const&) = delete;
	MoveAssignableWrapper(MoveAssignableWrapper&&) = default;
	MoveAssignableWrapper& operator=(MoveAssignableWrapper const&) = delete;
	MoveAssignableWrapper& operator=(MoveAssignableWrapper &&) = default;

	template <typename... Args>
	bool operator()(Args&&...) { return value; }

	explicit MoveAssignableWrapper(bool x) : value(x) {}

	bool value;
};

struct MemFunCallable
{
	explicit MemFunCallable(bool x) : value(x) {}

	bool return_value() const { return value; }
	bool return_value_nc() { return value; }
	bool value;
};

enum class CallType : unsigned
{
	None     = 0,
	NonConst = 1,
	Const    = 2,
	LValue   = 4,
	RValue   = 8,
};

inline constexpr CallType operator|(CallType LHS, CallType RHS)
{
	return static_cast<CallType>(static_cast<unsigned>(LHS) | static_cast<unsigned>(RHS));
}

// TypeID - Represent a unique identifier for a type. TypeID allows equality
// comparisons between different types.
struct TypeID
{
	friend bool operator==(TypeID const& LHS, TypeID const& RHS)
	{
		return LHS.m_id == RHS.m_id;
	}
	friend bool operator!=(TypeID const& LHS, TypeID const& RHS)
	{
		return LHS.m_id != RHS.m_id;
	}
private:
	explicit constexpr TypeID(const int* xid) : m_id(xid) {}
	const int* const m_id;
	template <typename T> friend class TypeInfo;
};

// TypeInfo - Represent information for the specified type 'T', including a
// unique TypeID.
template <typename T>
class TypeInfo
{
public:
	typedef T value_type;
	typedef TypeID ID;
	static  ID const& GetID()
	{
		static ID id(&dummy_addr);
		return id;
	}

private:
	static const int dummy_addr;
};

template <typename L, typename R>
inline bool operator==(TypeInfo<L> const&, TypeInfo<R> const&)
{
	return hamon::is_same<L, R>::value;
}

template <typename L, typename R>
inline bool operator!=(TypeInfo<L> const& lhs, TypeInfo<R> const& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
const int TypeInfo<T>::dummy_addr = 42;

// makeTypeID - Return the TypeID for the specified type 'T'.
template <typename T>
inline constexpr TypeID const& makeTypeID()
{
	return TypeInfo<T>::GetID();
}

template <typename... Args>
struct ArgumentListID {};

// makeArgumentID - Create and return a unique identifier for a given set
// of arguments.
template <typename... Args>
inline constexpr TypeID const& makeArgumentID()
{
	return makeTypeID<ArgumentListID<Args...>>();
}

struct ForwardingCallObject
{
	template <typename... Args>
	bool operator()(Args&&...) &
	{
		set_call<Args&&...>(CallType::NonConst | CallType::LValue);
		return true;
	}

	template <typename... Args>
	bool operator()(Args&&...) const &
	{
		set_call<Args&&...>(CallType::Const | CallType::LValue);
		return true;
	}

	// Don't allow the call operator to be invoked as an rvalue.
	template <typename... Args>
	bool operator()(Args&&...) &&
	{
		set_call<Args&&...>(CallType::NonConst | CallType::RValue);
		return true;
	}

	template <typename... Args>
	bool operator()(Args&&...) const &&
	{
		set_call<Args&&...>(CallType::Const | CallType::RValue);
		return true;
	}

	template <typename... Args>
	static void set_call(CallType type)
	{
		assert(last_call_type == CallType::None);
		assert(last_call_args == nullptr);
		last_call_type = type;
		last_call_args = &makeArgumentID<Args...>();
	}

	template <typename... Args>
	static bool check_call(CallType type)
	{
		bool result =
			last_call_type == type
			&& last_call_args
			&& *last_call_args == makeArgumentID<Args...>();
		last_call_type = CallType::None;
		last_call_args = nullptr;
		return result;
	}

	static CallType      last_call_type;
	static TypeID const* last_call_args;
};

CallType ForwardingCallObject::last_call_type = CallType::None;
TypeID const* ForwardingCallObject::last_call_args = nullptr;



///////////////////////////////////////////////////////////////////////////////
//                        BOOL TEST TYPES
///////////////////////////////////////////////////////////////////////////////

struct EvilBool
{
	static int bang_called;

	EvilBool(EvilBool const&) = default;
	EvilBool(EvilBool&&) = default;

	friend EvilBool operator!(EvilBool const& other)
	{
		++bang_called;
		return EvilBool{!other.value};
	}

private:
	friend struct MoveOnlyCallable<EvilBool>;
	friend struct CopyCallable<EvilBool>;
	friend struct NoExceptCallable<EvilBool>;

	explicit EvilBool(bool x) : value(x) {}
	EvilBool& operator=(EvilBool const& other) = default;

public:
	bool value;
};

int EvilBool::bang_called = 0;

struct ExplicitBool
{
	ExplicitBool(ExplicitBool const&) = default;
	ExplicitBool(ExplicitBool&&) = default;

	explicit operator bool() const { return value; }

private:
	friend struct MoveOnlyCallable<ExplicitBool>;
	friend struct CopyCallable<ExplicitBool>;

	explicit ExplicitBool(bool x) : value(x) {}
	ExplicitBool& operator=(bool x)
	{
		value = x;
		return *this;
	}

	bool value;
};

struct NoExceptEvilBool
{
	NoExceptEvilBool(NoExceptEvilBool const&) = default;
	NoExceptEvilBool(NoExceptEvilBool&&) = default;
	NoExceptEvilBool& operator=(NoExceptEvilBool const& other) = default;

	explicit NoExceptEvilBool(bool x) : value(x) {}

	friend NoExceptEvilBool operator!(NoExceptEvilBool const& other) noexcept
	{
		return NoExceptEvilBool{!other.value};
	}

	bool value;
};

void constructor_tests()
{
	{
		using T = MoveOnlyCallable<bool>;
		T value(true);
		using RetT = decltype(hamon::not_fn(std::move(value)));
		static_assert( hamon::is_move_constructible<RetT>::value, "");
		static_assert(!hamon::is_copy_constructible<RetT>::value, "");
		static_assert(!hamon::is_move_assignable<RetT>::value, "");
		static_assert(!hamon::is_copy_assignable<RetT>::value, "");
		auto ret = hamon::not_fn(std::move(value));
		// test it was moved from
		EXPECT_FALSE(value.value);
		// test that ret() negates the original value 'true'
		EXPECT_FALSE(ret());
		EXPECT_FALSE(ret(0, 0.0, "blah"));
		// Move ret and test that it was moved from and that ret2 got the
		// original value.
		auto ret2 = std::move(ret);
		EXPECT_TRUE (ret());
		EXPECT_FALSE(ret2());
		EXPECT_FALSE(ret2(42));
	}
	{
		using T = CopyCallable<bool>;
		T value(false);
		using RetT = decltype(hamon::not_fn(value));
		static_assert( hamon::is_move_constructible<RetT>::value, "");
		static_assert( hamon::is_copy_constructible<RetT>::value, "");
		static_assert(!hamon::is_move_assignable<RetT>::value, "");
		static_assert(!hamon::is_copy_assignable<RetT>::value, "");
		auto ret = hamon::not_fn(value);
		// test that value is unchanged (copied not moved)
		EXPECT_FALSE(value.value);
		// test 'ret' has the original value
		EXPECT_TRUE(ret());
		EXPECT_TRUE(ret(42, 100));
		// move from 'ret' and check that 'ret2' has the original value.
		auto ret2 = std::move(ret);
		EXPECT_FALSE(ret());
		EXPECT_TRUE(ret2());
		EXPECT_TRUE(ret2("abc"));
	}
	{
		using T = CopyAssignableWrapper;
		T value(true);
		T value2(false);
		using RetT = decltype(hamon::not_fn(value));
		static_assert(hamon::is_move_constructible<RetT>::value, "");
		static_assert(hamon::is_copy_constructible<RetT>::value, "");
//		static_assert(hamon::is_move_assignable<RetT>::value, "");
//		static_assert(hamon::is_copy_assignable<RetT>::value, "");
		auto ret = hamon::not_fn(value);
		EXPECT_FALSE(ret());
		auto ret2 = hamon::not_fn(value2);
		EXPECT_TRUE(ret2());
#if 0
		ret = ret2;
		EXPECT_TRUE(ret());
		EXPECT_TRUE(ret2());
#endif
	}
	{
		using T = MoveAssignableWrapper;
		T value(true);
		T value2(false);
		using RetT = decltype(hamon::not_fn(std::move(value)));
		static_assert( hamon::is_move_constructible<RetT>::value, "");
		static_assert(!hamon::is_copy_constructible<RetT>::value, "");
//		static_assert( hamon::is_move_assignable<RetT>::value, "");
//		static_assert(!hamon::is_copy_assignable<RetT>::value, "");
		auto ret = hamon::not_fn(std::move(value));
		EXPECT_FALSE(ret());
		auto ret2 = hamon::not_fn(std::move(value2));
		EXPECT_TRUE(ret2());
#if 0
		ret = std::move(ret2);
		EXPECT_TRUE(ret());
#endif
	}
}

void return_type_tests()
{
	{
		using T = CopyCallable<bool>;
		auto ret = hamon::not_fn(T{false});
		static_assert(hamon::is_same<decltype(ret()), bool>::value, "");
		static_assert(hamon::is_same<decltype(ret("abc")), bool>::value, "");
		EXPECT_TRUE(ret());
	}
	{
		using T = CopyCallable<ExplicitBool>;
		auto ret = hamon::not_fn(T{true});
		static_assert(hamon::is_same<decltype(ret()), bool>::value, "");
		static_assert(hamon::is_same<decltype(ret(std::string("abc"))), bool>::value, "");
		EXPECT_FALSE(ret());
	}
	{
		using T = CopyCallable<EvilBool>;
		auto ret = hamon::not_fn(T{false});
		static_assert(hamon::is_same<decltype(ret()), EvilBool>::value, "");
		EvilBool::bang_called = 0;
		auto value_ret = ret();
		EXPECT_EQ(EvilBool::bang_called, 1);
		EXPECT_TRUE(value_ret.value);
		ret();
		EXPECT_EQ(EvilBool::bang_called, 2);
	}
}

// Other tests only test using objects with call operators. Test various
// other callable types here.
void other_callable_types_test()
{
	{ // test with function pointer
		auto ret = hamon::not_fn(returns_true);
		EXPECT_FALSE(ret());
	}
	{ // test with lambda
		auto returns_value = [](bool value) { return value; };
		auto ret = hamon::not_fn(returns_value);
		EXPECT_FALSE(ret(true));
		EXPECT_TRUE (ret(false));
	}
	{ // test with pointer to member function
		MemFunCallable mt(true);
		const MemFunCallable mf(false);
		auto ret = hamon::not_fn(&MemFunCallable::return_value);
		EXPECT_FALSE(ret(mt));
		EXPECT_TRUE (ret(mf));
		EXPECT_FALSE(ret(&mt));
		EXPECT_TRUE (ret(&mf));
	}
	{ // test with pointer to member function
		MemFunCallable mt(true);
		MemFunCallable mf(false);
		auto ret = hamon::not_fn(&MemFunCallable::return_value_nc);
		EXPECT_FALSE(ret(mt));
		EXPECT_TRUE (ret(mf));
		EXPECT_FALSE(ret(&mt));
		EXPECT_TRUE (ret(&mf));
	}
	{ // test with pointer to member data
		MemFunCallable mt(true);
		const MemFunCallable mf(false);
		auto ret = hamon::not_fn(&MemFunCallable::value);
		EXPECT_FALSE(ret(mt));
		EXPECT_TRUE (ret(mf));
		EXPECT_FALSE(ret(&mt));
		EXPECT_TRUE (ret(&mf));
	}
}

void throws_in_constructor_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	struct ThrowsOnCopy
	{
		ThrowsOnCopy(ThrowsOnCopy const&)
		{
			throw 42;
		}

		ThrowsOnCopy() = default;

		bool operator()() const
		{
			EXPECT_TRUE(false);
			return false;
		}
	};
	{
		ThrowsOnCopy cp;
		try
		{
			(void)hamon::not_fn(cp);
			GTEST_FAIL();
		}
		catch (int const& value)
		{
			EXPECT_EQ(value, 42);
		}
	}
#endif
}

void call_operator_sfinae_test()
{
	{ // wrong number of arguments
		using T = decltype(hamon::not_fn(returns_true));
		static_assert( hamon::is_invocable<T>::value, ""); // callable only with no args
		static_assert(!hamon::is_invocable<T, bool>::value, "");
	}
	{ // violates const correctness (member function pointer)
		using T = decltype(hamon::not_fn(&MemFunCallable::return_value_nc));
		static_assert( hamon::is_invocable<T, MemFunCallable&>::value, "");
		static_assert(!hamon::is_invocable<T, const MemFunCallable&>::value, "");
	}
	{ // violates const correctness (call object)
		using Obj = CopyCallable<bool>;
		using NCT = decltype(hamon::not_fn(Obj{true}));
		using CT = const NCT;
		static_assert( hamon::is_invocable<NCT>::value, "");
		static_assert(!hamon::is_invocable<CT>::value, "");
	}
#if defined(HAMON_HAS_CXX14_GENERIC_LAMBDAS)
	{ // returns bad type with no operator!
		auto fn = [](auto x) { return x; };
		using T = decltype(hamon::not_fn(fn));
		static_assert( hamon::is_invocable<T, bool>::value, "");
		static_assert(!hamon::is_invocable<T, std::string>::value, "");
	}
#endif
}

void call_operator_forwarding_test()
{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(26478)	// 定数変数の std::move は使用しないでください。(es.56)。
	using Fn = ForwardingCallObject;
	auto obj = hamon::not_fn(Fn{});
	const auto& c_obj = obj;
	{ // test zero args
		obj();
		EXPECT_TRUE(Fn::check_call<>(CallType::NonConst | CallType::LValue));
		std::move(obj)();
		EXPECT_TRUE(Fn::check_call<>(CallType::NonConst | CallType::RValue));
		c_obj();
		EXPECT_TRUE(Fn::check_call<>(CallType::Const | CallType::LValue));
		std::move(c_obj)();
		EXPECT_TRUE(Fn::check_call<>(CallType::Const | CallType::RValue));
	}
	{ // test value categories
		int x = 42;
		const int cx = 42;
		obj(x);
		EXPECT_TRUE(Fn::check_call<int&>(CallType::NonConst | CallType::LValue));
		obj(cx);
		EXPECT_TRUE(Fn::check_call<const int&>(CallType::NonConst | CallType::LValue));
		obj(std::move(x));
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::NonConst | CallType::LValue));
		obj(std::move(cx));
		EXPECT_TRUE(Fn::check_call<const int&&>(CallType::NonConst | CallType::LValue));
		obj(42);
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::NonConst | CallType::LValue));
	}
	{ // test value categories - rvalue
		int x = 42;
		const int cx = 42;
		std::move(obj)(x);
		EXPECT_TRUE(Fn::check_call<int&>(CallType::NonConst | CallType::RValue));
		std::move(obj)(cx);
		EXPECT_TRUE(Fn::check_call<const int&>(CallType::NonConst | CallType::RValue));
		std::move(obj)(std::move(x));
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::NonConst | CallType::RValue));
		std::move(obj)(std::move(cx));
		EXPECT_TRUE(Fn::check_call<const int&&>(CallType::NonConst | CallType::RValue));
		std::move(obj)(42);
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::NonConst | CallType::RValue));
	}
	{ // test value categories - const call
		int x = 42;
		const int cx = 42;
		c_obj(x);
		EXPECT_TRUE(Fn::check_call<int&>(CallType::Const | CallType::LValue));
		c_obj(cx);
		EXPECT_TRUE(Fn::check_call<const int&>(CallType::Const | CallType::LValue));
		c_obj(std::move(x));
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::Const | CallType::LValue));
		c_obj(std::move(cx));
		EXPECT_TRUE(Fn::check_call<const int&&>(CallType::Const | CallType::LValue));
		c_obj(42);
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::Const | CallType::LValue));
	}
	{ // test value categories - const call rvalue
		int x = 42;
		const int cx = 42;
		std::move(c_obj)(x);
		EXPECT_TRUE(Fn::check_call<int&>(CallType::Const | CallType::RValue));
		std::move(c_obj)(cx);
		EXPECT_TRUE(Fn::check_call<const int&>(CallType::Const | CallType::RValue));
		std::move(c_obj)(std::move(x));
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::Const | CallType::RValue));
		std::move(c_obj)(std::move(cx));
		EXPECT_TRUE(Fn::check_call<const int&&>(CallType::Const | CallType::RValue));
		std::move(c_obj)(42);
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::Const | CallType::RValue));
	}
	{ // test multi arg
		const double y = 3.14;
		std::string s = "abc";
		obj(42, std::move(y), s, std::string{"foo"});
		Fn::check_call<int&&, const double&&, std::string&, std::string&&>(CallType::NonConst | CallType::LValue);
		std::move(obj)(42, std::move(y), s, std::string{"foo"});
		Fn::check_call<int&&, const double&&, std::string&, std::string&&>(CallType::NonConst | CallType::RValue);
		c_obj(42, std::move(y), s, std::string{"foo"});
		Fn::check_call<int&&, const double&&, std::string&, std::string&&>(CallType::Const  | CallType::LValue);
		std::move(c_obj)(42, std::move(y), s, std::string{"foo"});
		Fn::check_call<int&&, const double&&, std::string&, std::string&&>(CallType::Const  | CallType::RValue);
	}
HAMON_WARNING_POP()
}

void call_operator_noexcept_test()
{
#if 0
	{
		using T = ConstCallable<bool>;
		T value(true);
		auto ret = hamon::not_fn(value);
		static_assert(!noexcept(ret()), "call should not be noexcept");
		auto const& cret = ret;
		static_assert(!noexcept(cret()), "call should not be noexcept");
	}
#endif
	{
		using T = NoExceptCallable<bool>;
		T value(true);
		auto ret = hamon::not_fn(value);
		static_assert(noexcept(!hamon::invoke(value)), "");
		static_assert(noexcept(ret()), "call should be noexcept");
		auto const& cret = ret;
		static_assert(noexcept(cret()), "call should be noexcept");
	}
	{
		using T = NoExceptCallable<NoExceptEvilBool>;
		T value(true);
		auto ret = hamon::not_fn(value);
		static_assert(noexcept(ret()), "call should not be noexcept");
		auto const& cret = ret;
		static_assert(noexcept(cret()), "call should not be noexcept");
	}
	{
		using T = NoExceptCallable<EvilBool>;
		T value(true);
		auto ret = hamon::not_fn(value);
		static_assert(!noexcept(ret()), "call should not be noexcept");
		auto const& cret = ret;
		static_assert(!noexcept(cret()), "call should not be noexcept");
	}
}

void test_lwg2767()
{
	// See https://cplusplus.github.io/LWG/lwg-defects.html#2767
	struct Abstract { virtual void f() const = 0; };
	struct Derived : public Abstract { void f() const {} };
	struct F { bool operator()(Abstract&&) { return false; } };
	{
		Derived d;
		Abstract &a = d;
		bool b = hamon::not_fn(F{})(std::move(a));
		EXPECT_TRUE(b);
	}
}

GTEST_TEST(FunctionalTest, NotFnTest)
{
	constructor_tests();
	return_type_tests();
	other_callable_types_test();
	throws_in_constructor_test();
	call_operator_sfinae_test(); // somewhat of an extension
	call_operator_forwarding_test();
	call_operator_noexcept_test();
	test_lwg2767();
}

}	// namespace hamon_functional_not_fn_test

HAMON_WARNING_POP()
