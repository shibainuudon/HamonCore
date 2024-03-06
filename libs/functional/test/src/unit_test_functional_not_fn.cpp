/**
 *	@file	unit_test_functional_not_fn.cpp
 *
 *	@brief	not_fn のテスト
 */

#include <hamon/functional/not_fn.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
//#include "tuple_test_utility.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunneeded-internal-declaration")
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon_functional_not_fn_test
{

HAMON_CXX11_CONSTEXPR bool returns_true() { return true; }

template <typename Ret = bool>
struct MoveOnlyCallable
{
	MoveOnlyCallable(MoveOnlyCallable const&) = delete;
	
	HAMON_CXX14_CONSTEXPR
	MoveOnlyCallable(MoveOnlyCallable&& other) noexcept
		: value(other.value)
	{
		other.value = !other.value;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR Ret
	operator()(Args&&...) { return Ret{value}; }

	HAMON_CXX14_CONSTEXPR explicit
	MoveOnlyCallable(bool x) : value(x) {}

	Ret value;
};

template <typename Ret = bool>
struct CopyCallable
{
	HAMON_CXX14_CONSTEXPR
	CopyCallable(CopyCallable const& other)
		: value(other.value) {}

	HAMON_CXX14_CONSTEXPR
	CopyCallable(CopyCallable&& other) noexcept
		: value(other.value)
	{
		other.value = !other.value;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR Ret
	operator()(Args&&...) { return Ret{value}; }

	HAMON_CXX14_CONSTEXPR explicit
	CopyCallable(bool x) : value(x) {}

	Ret value;
};

template <typename Ret = bool>
struct ConstCallable
{
	HAMON_CXX14_CONSTEXPR
	ConstCallable(ConstCallable const& other)
		: value(other.value) {}

	HAMON_CXX14_CONSTEXPR
	ConstCallable(ConstCallable&& other)
		: value(other.value)
	{
		other.value = !other.value;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR Ret
	operator()(Args&&...) const { return Ret{value}; }

	HAMON_CXX14_CONSTEXPR explicit
	ConstCallable(bool x) : value(x) {}

	Ret value;
};

template <typename Ret = bool>
struct NoExceptCallable
{
	HAMON_CXX14_CONSTEXPR
	NoExceptCallable(NoExceptCallable const& other)
		: value(other.value) {}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR Ret
	operator()(Args&&...) noexcept { return Ret{value}; }

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR Ret
	operator()(Args&&...) const noexcept { return Ret{value}; }

	HAMON_CXX14_CONSTEXPR explicit
	NoExceptCallable(bool x) : value(x) {}

	Ret value;
};

struct CopyAssignableWrapper
{
	CopyAssignableWrapper(CopyAssignableWrapper const&) = default;
	CopyAssignableWrapper(CopyAssignableWrapper&&) = default;
	CopyAssignableWrapper& operator=(CopyAssignableWrapper const&) = default;
	CopyAssignableWrapper& operator=(CopyAssignableWrapper &&) = default;

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR bool
	operator()(Args&&...) { return value; }

	HAMON_CXX14_CONSTEXPR explicit
	CopyAssignableWrapper(bool x) : value(x) {}

	bool value;
};

struct MoveAssignableWrapper
{
	MoveAssignableWrapper(MoveAssignableWrapper const&) = delete;
	MoveAssignableWrapper(MoveAssignableWrapper&&) = default;
	MoveAssignableWrapper& operator=(MoveAssignableWrapper const&) = delete;
	MoveAssignableWrapper& operator=(MoveAssignableWrapper &&) = default;

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR bool
	operator()(Args&&...) { return value; }

	HAMON_CXX14_CONSTEXPR explicit
	MoveAssignableWrapper(bool x) : value(x) {}

	bool value;
};

struct MemFunCallable
{
	HAMON_CXX14_CONSTEXPR explicit
	MemFunCallable(bool x) : value(x) {}

	HAMON_CXX14_CONSTEXPR bool return_value() const { return value; }
	HAMON_CXX14_CONSTEXPR bool return_value_nc() { return value; }

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

	friend EvilBool
	operator!(EvilBool const& other)
	{
		++bang_called;
		return EvilBool{!other.value};
	}

private:
	friend struct MoveOnlyCallable<EvilBool>;
	friend struct CopyCallable<EvilBool>;
	friend struct NoExceptCallable<EvilBool>;

	explicit
	EvilBool(bool x) : value(x) {}
	
	EvilBool& operator=(EvilBool const& other) = default;

public:
	bool value;
};

int EvilBool::bang_called = 0;

struct ExplicitBool
{
	ExplicitBool(ExplicitBool const&) = default;
	ExplicitBool(ExplicitBool&&) = default;

	HAMON_CXX14_CONSTEXPR explicit
	operator bool() const { return value; }

private:
	friend struct MoveOnlyCallable<ExplicitBool>;
	friend struct CopyCallable<ExplicitBool>;

	HAMON_CXX14_CONSTEXPR explicit
	ExplicitBool(bool x) : value(x) {}
	
	HAMON_CXX14_CONSTEXPR ExplicitBool&
	operator=(bool x)
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool constructor_tests()
{
	{
		using T = MoveOnlyCallable<bool>;
		T value(true);
		using RetT = decltype(hamon::not_fn(hamon::move(value)));
		static_assert( hamon::is_move_constructible<RetT>::value, "");
		static_assert(!hamon::is_copy_constructible<RetT>::value, "");
		static_assert(!hamon::is_move_assignable<RetT>::value, "");
		static_assert(!hamon::is_copy_assignable<RetT>::value, "");
		auto ret = hamon::not_fn(hamon::move(value));
		// test it was moved from
		VERIFY(!value.value);
		// test that ret() negates the original value 'true'
		VERIFY(!ret());
		VERIFY(!ret(0, 0.0, "blah"));
		// Move ret and test that it was moved from and that ret2 got the
		// original value.
		auto ret2 = hamon::move(ret);
		VERIFY(ret());
		VERIFY(!ret2());
		VERIFY(!ret2(42));
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
		VERIFY(!value.value);
		// test 'ret' has the original value
		VERIFY(ret());
		VERIFY(ret(42, 100));
		// move from 'ret' and check that 'ret2' has the original value.
		auto ret2 = hamon::move(ret);
		VERIFY(!ret());
		VERIFY(ret2());
		VERIFY(ret2("abc"));
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
		VERIFY(!ret());
		auto ret2 = hamon::not_fn(value2);
		VERIFY(ret2());
#if 0
		ret = ret2;
		VERIFY(ret());
		VERIFY(ret2());
#endif
	}
	{
		using T = MoveAssignableWrapper;
		T value(true);
		T value2(false);
		using RetT = decltype(hamon::not_fn(hamon::move(value)));
		static_assert( hamon::is_move_constructible<RetT>::value, "");
		static_assert(!hamon::is_copy_constructible<RetT>::value, "");
//		static_assert( hamon::is_move_assignable<RetT>::value, "");
//		static_assert(!hamon::is_copy_assignable<RetT>::value, "");
		auto ret = hamon::not_fn(hamon::move(value));
		VERIFY(!ret());
		auto ret2 = hamon::not_fn(hamon::move(value2));
		VERIFY(ret2());
#if 0
		ret = hamon::move(ret2);
		VERIFY(ret());
#endif
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool return_type_tests_1()
{
	{
		using T = CopyCallable<bool>;
		auto ret = hamon::not_fn(T{false});
		static_assert(hamon::is_same<decltype(ret()), bool>::value, "");
		static_assert(hamon::is_same<decltype(ret("abc")), bool>::value, "");
		VERIFY(ret());
	}
	{
		using T = CopyCallable<ExplicitBool>;
		auto ret = hamon::not_fn(T{true});
		static_assert(hamon::is_same<decltype(ret()), bool>::value, "");
		static_assert(hamon::is_same<decltype(ret(hamon::string("abc"))), bool>::value, "");
		VERIFY(!ret());
	}
	return true;
}

bool return_type_tests_2()
{
	{
		using T = CopyCallable<EvilBool>;
		auto ret = hamon::not_fn(T{false});
		static_assert(hamon::is_same<decltype(ret()), EvilBool>::value, "");
		EvilBool::bang_called = 0;
		auto value_ret = ret();
		VERIFY(EvilBool::bang_called == 1);
		VERIFY(value_ret.value);
		ret();
		VERIFY(EvilBool::bang_called == 2);
	}

	return true;
}

// Other tests only test using objects with call operators. Test various
// other callable types here.
HAMON_CXX14_CONSTEXPR bool other_callable_types_test_1()
{
	{ // test with function pointer
		auto ret = hamon::not_fn(returns_true);
		VERIFY(!ret());
	}
	{ // test with pointer to member function
		MemFunCallable mt(true);
		const MemFunCallable mf(false);
		auto ret = hamon::not_fn(&MemFunCallable::return_value);
		VERIFY(!ret(mt));
		VERIFY(ret(mf));
		VERIFY(!ret(&mt));
		VERIFY(ret(&mf));
	}
	{ // test with pointer to member function
		MemFunCallable mt(true);
		MemFunCallable mf(false);
		auto ret = hamon::not_fn(&MemFunCallable::return_value_nc);
		VERIFY(!ret(mt));
		VERIFY(ret(mf));
		VERIFY(!ret(&mt));
		VERIFY(ret(&mf));
	}
	{ // test with pointer to member data
		MemFunCallable mt(true);
		const MemFunCallable mf(false);
		auto ret = hamon::not_fn(&MemFunCallable::value);
		VERIFY(!ret(mt));
		VERIFY(ret(mf));
		VERIFY(!ret(&mt));
		VERIFY(ret(&mf));
	}
	return true;
}

HAMON_CXX17_CONSTEXPR bool other_callable_types_test_2()
{
	{ // test with lambda
		auto returns_value = [](bool value) { return value; };
		auto ret = hamon::not_fn(returns_value);
		VERIFY(!ret(true));
		VERIFY(ret(false));
	}
	return true;
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
		static_assert(!hamon::is_invocable<T, hamon::string>::value, "");
	}
#endif
}

void call_operator_forwarding_test()
{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(26478)	// 定数変数の hamon::move は使用しないでください。(es.56)。
	using Fn = ForwardingCallObject;
	auto obj = hamon::not_fn(Fn{});
	const auto& c_obj = obj;
	{ // test zero args
		obj();
		EXPECT_TRUE(Fn::check_call<>(CallType::NonConst | CallType::LValue));
		hamon::move(obj)();
		EXPECT_TRUE(Fn::check_call<>(CallType::NonConst | CallType::RValue));
		c_obj();
		EXPECT_TRUE(Fn::check_call<>(CallType::Const | CallType::LValue));
		hamon::move(c_obj)();
		EXPECT_TRUE(Fn::check_call<>(CallType::Const | CallType::RValue));
	}
	{ // test value categories
		int x = 42;
		const int cx = 42;
		obj(x);
		EXPECT_TRUE(Fn::check_call<int&>(CallType::NonConst | CallType::LValue));
		obj(cx);
		EXPECT_TRUE(Fn::check_call<const int&>(CallType::NonConst | CallType::LValue));
		obj(hamon::move(x));
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::NonConst | CallType::LValue));
		obj(hamon::move(cx));
		EXPECT_TRUE(Fn::check_call<const int&&>(CallType::NonConst | CallType::LValue));
		obj(42);
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::NonConst | CallType::LValue));
	}
	{ // test value categories - rvalue
		int x = 42;
		const int cx = 42;
		hamon::move(obj)(x);
		EXPECT_TRUE(Fn::check_call<int&>(CallType::NonConst | CallType::RValue));
		hamon::move(obj)(cx);
		EXPECT_TRUE(Fn::check_call<const int&>(CallType::NonConst | CallType::RValue));
		hamon::move(obj)(hamon::move(x));
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::NonConst | CallType::RValue));
		hamon::move(obj)(hamon::move(cx));
		EXPECT_TRUE(Fn::check_call<const int&&>(CallType::NonConst | CallType::RValue));
		hamon::move(obj)(42);
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::NonConst | CallType::RValue));
	}
	{ // test value categories - const call
		int x = 42;
		const int cx = 42;
		c_obj(x);
		EXPECT_TRUE(Fn::check_call<int&>(CallType::Const | CallType::LValue));
		c_obj(cx);
		EXPECT_TRUE(Fn::check_call<const int&>(CallType::Const | CallType::LValue));
		c_obj(hamon::move(x));
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::Const | CallType::LValue));
		c_obj(hamon::move(cx));
		EXPECT_TRUE(Fn::check_call<const int&&>(CallType::Const | CallType::LValue));
		c_obj(42);
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::Const | CallType::LValue));
	}
	{ // test value categories - const call rvalue
		int x = 42;
		const int cx = 42;
		hamon::move(c_obj)(x);
		EXPECT_TRUE(Fn::check_call<int&>(CallType::Const | CallType::RValue));
		hamon::move(c_obj)(cx);
		EXPECT_TRUE(Fn::check_call<const int&>(CallType::Const | CallType::RValue));
		hamon::move(c_obj)(hamon::move(x));
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::Const | CallType::RValue));
		hamon::move(c_obj)(hamon::move(cx));
		EXPECT_TRUE(Fn::check_call<const int&&>(CallType::Const | CallType::RValue));
		hamon::move(c_obj)(42);
		EXPECT_TRUE(Fn::check_call<int&&>(CallType::Const | CallType::RValue));
	}
	{ // test multi arg
		const double y = 3.14;
		hamon::string s = "abc";
		obj(42, hamon::move(y), s, hamon::string{"foo"});
		EXPECT_TRUE((Fn::check_call<int&&, const double&&, hamon::string&, hamon::string&&>(CallType::NonConst | CallType::LValue)));
		hamon::move(obj)(42, hamon::move(y), s, hamon::string{"foo"});
		EXPECT_TRUE((Fn::check_call<int&&, const double&&, hamon::string&, hamon::string&&>(CallType::NonConst | CallType::RValue)));
		c_obj(42, hamon::move(y), s, hamon::string{"foo"});
		EXPECT_TRUE((Fn::check_call<int&&, const double&&, hamon::string&, hamon::string&&>(CallType::Const  | CallType::LValue)));
		hamon::move(c_obj)(42, hamon::move(y), s, hamon::string{"foo"});
		EXPECT_TRUE((Fn::check_call<int&&, const double&&, hamon::string&, hamon::string&&>(CallType::Const  | CallType::RValue)));
	}
HAMON_WARNING_POP()
}

HAMON_CXX14_CONSTEXPR bool call_operator_forwarding_test_2()
{
	{
		auto fn = hamon::not_fn(returns_true);
		VERIFY(!fn());
		VERIFY(!hamon::move(fn)());
	}
	{
		auto const fn = hamon::not_fn(returns_true);
		VERIFY(!fn());
		VERIFY(!hamon::move(fn)());
	}
	{
		auto fn = hamon::not_fn(hamon::ranges::less{});
		VERIFY(!fn(1, 2));
		VERIFY( fn(2, 1));
		VERIFY(!hamon::move(fn)(1, 2));
	}
	{
		auto const fn = hamon::not_fn(hamon::ranges::less{});
		VERIFY(!fn(1, 2));
		VERIFY( fn(2, 1));
		VERIFY(!hamon::move(fn)(1, 2));
	}
	return true;
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
		bool b = hamon::not_fn(F{})(hamon::move(a));
		EXPECT_TRUE(b);
	}
}

#undef VERIFY

GTEST_TEST(FunctionalTest, NotFnTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constructor_tests());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(return_type_tests_1());
	                      EXPECT_TRUE(return_type_tests_2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(other_callable_types_test_1());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(other_callable_types_test_2());
	throws_in_constructor_test();
	call_operator_sfinae_test(); // somewhat of an extension
	call_operator_forwarding_test();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(call_operator_forwarding_test_2());
	call_operator_noexcept_test();
	test_lwg2767();
}

}	// namespace hamon_functional_not_fn_test

HAMON_WARNING_POP()
