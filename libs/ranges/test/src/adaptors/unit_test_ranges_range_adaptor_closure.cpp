/**
 *	@file	unit_test_ranges_range_adaptor_closure.cpp
 *
 *	@brief	ranges::range_adaptor_closure のテスト
 */

#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/array.hpp>
#include <hamon/concepts.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace range_adaptor_closure_test
{

//template <typename T>
//concept CanInstantiateRangeAdaptorClosure =
//	requires { typename hamon::ranges::range_adaptor_closure<T>; };

template <typename T, typename = void>
struct CanInstantiateRangeAdaptorClosure
	: hamon::false_type {};

template <typename T>
struct CanInstantiateRangeAdaptorClosure<T, hamon::void_t<hamon::ranges::range_adaptor_closure<T>>>
	: hamon::true_type {};

class EmptyTestType {};
class IncompleteTestType;

static_assert( CanInstantiateRangeAdaptorClosure<EmptyTestType>::value, "");
static_assert(!CanInstantiateRangeAdaptorClosure<EmptyTestType const>::value, "");
static_assert(!CanInstantiateRangeAdaptorClosure<EmptyTestType volatile>::value, "");
static_assert(!CanInstantiateRangeAdaptorClosure<EmptyTestType&>::value, "");
static_assert(!CanInstantiateRangeAdaptorClosure<int>::value, "");
static_assert( CanInstantiateRangeAdaptorClosure<IncompleteTestType>::value, "");

//template <typename LHS, typename RHS>
//concept CanPipe =
//	requires(LHS lhs, RHS rhs)
//	{
//		hamon::forward<LHS>(lhs) | hamon::forward<RHS>(rhs);
//	};

template <typename LHS, typename RHS, typename = void>
struct CanPipe
	: hamon::false_type {};

template <typename LHS, typename RHS>
struct CanPipe<LHS, RHS, hamon::void_t<decltype(hamon::declval<LHS>() | hamon::declval<RHS>())>>
	: hamon::true_type {};

//template <typename LHS, typename RHS, typename Ret>
//concept CanPipe_R =
//	requires(LHS lhs, RHS rhs)
//	{
//		{ hamon::forward<LHS>(lhs) | hamon::forward<RHS>(rhs) } -> hamon::same_as<Ret>;
//	};

template <typename LHS, typename RHS, typename Ret, typename = void>
struct CanPipe_R
	: hamon::false_type {};

template <typename LHS, typename RHS, typename Ret>
struct CanPipe_R<LHS, RHS, Ret, hamon::void_t<decltype(hamon::declval<LHS>() | hamon::declval<RHS>())>>
	: hamon::same_as_t<Ret, decltype(hamon::declval<LHS>() | hamon::declval<RHS>())> {};

using TestRange = hamon::array<int, 1>;

template <typename T>
HAMON_CXX11_CONSTEXPR bool is_range_adaptor_closure()
{
	return
		CanPipe<TestRange, T&>::value ||
		CanPipe<TestRange, T&&>::value ||
		CanPipe<TestRange, T const&>::value ||
		CanPipe<TestRange, T const&&>::value;
}

struct IdentityRangeAdaptorClosure
	: hamon::ranges::range_adaptor_closure<IdentityRangeAdaptorClosure>
{
#if 0
	template <typename T>
	HAMON_CXX11_CONSTEXPR decltype(auto) operator()(T&& range) const
	{
		return hamon::forward<T>(range);
	}
#else
	template <typename T>
	HAMON_CXX11_CONSTEXPR auto operator()(T&& range) const
	->decltype((hamon::forward<T>(range)))
	{
		return hamon::forward<T>(range);
	}
#endif
};
static_assert(is_range_adaptor_closure<IdentityRangeAdaptorClosure>(), "");

// Is not a range adaptor closure, because it is not a function object.
struct NotCallable : hamon::ranges::range_adaptor_closure<NotCallable> {};
static_assert(!is_range_adaptor_closure<NotCallable>(), "");

// Is not a range adaptor closure, because it does not accept a range as argument.
struct NotCallableWithRange
	: hamon::ranges::range_adaptor_closure<NotCallableWithRange>
{
	void operator()() {}
};
static_assert(!is_range_adaptor_closure<NotCallableWithRange>(), "");

// Is not a range adaptor closure, because it doesn't derive from range_adaptor_closure.
struct NotDerivedFrom
{
	void operator()(TestRange const&) {}
};
static_assert(!is_range_adaptor_closure<NotDerivedFrom>(), "");

// Is not a range adaptor closure, because it inherits privately from range_adaptor_closure.
struct DerivedPrivately
	: private hamon::ranges::range_adaptor_closure<DerivedPrivately>
{
	void operator()(TestRange const&) {}
};
static_assert(!is_range_adaptor_closure<DerivedPrivately>(), "");

// Is not a range adaptor closure, because it inherits from the wrong specialization of range_adaptor_closure.
struct DerivedFromWrongSpecialization
	: hamon::ranges::range_adaptor_closure<IdentityRangeAdaptorClosure>
{
	void operator()(TestRange const&) {}
};
static_assert(!is_range_adaptor_closure<DerivedFromWrongSpecialization>(), "");

// TODO
#if 0
// Is not a range adaptor closure, because it has two base classes which are specializations of
// range_adaptor_closure.
struct DerivedFromTwoSpecializations
	: hamon::ranges::range_adaptor_closure<DerivedFromTwoSpecializations>
	, hamon::ranges::range_adaptor_closure<IdentityRangeAdaptorClosure>
{
	void operator()(TestRange const&) {}
};
//static_assert(!is_range_adaptor_closure<DerivedFromTwoSpecializations>(), "");
#endif

// Is not a range adaptor closure, because it models ranges::range.
struct ModelsRange
	: hamon::ranges::range_adaptor_closure<ModelsRange>
{
	void operator()(TestRange const&) {}

	int* begin()       { return nullptr; }
	int* begin() const { return nullptr; }
	int* end()       { return nullptr; }
	int* end() const { return nullptr; }
};
static_assert(hamon::ranges::range_t<ModelsRange>::value, "");
static_assert(!is_range_adaptor_closure<ModelsRange>(), "");

struct RangeAdaptorClosureMemberRefQualTest
	: hamon::ranges::range_adaptor_closure<RangeAdaptorClosureMemberRefQualTest>
{
	template <typename T>
	HAMON_CXX14_CONSTEXPR hamon::ranges::empty_view<char>
	operator()(T const&) &
	{
		return hamon::ranges::empty_view<char>{};
	}

	template <typename T>
	HAMON_CXX14_CONSTEXPR hamon::ranges::empty_view<short>
	operator()(T const&) &&
	{
		return hamon::ranges::empty_view<short>{};
	}

	template <typename T>
	HAMON_CXX11_CONSTEXPR hamon::ranges::empty_view<float>
	operator()(T const&) const&
	{
		return hamon::ranges::empty_view<float>{};
	}

	template <typename T>
	HAMON_CXX11_CONSTEXPR hamon::ranges::empty_view<double>
	operator()(T const&) const&&
	{
		return hamon::ranges::empty_view<double>{};
	}
};
static_assert(is_range_adaptor_closure<RangeAdaptorClosureMemberRefQualTest>(), "");
static_assert(CanPipe_R<TestRange, RangeAdaptorClosureMemberRefQualTest&, hamon::ranges::empty_view<char>>::value, "");
static_assert(CanPipe_R<TestRange, RangeAdaptorClosureMemberRefQualTest&&, hamon::ranges::empty_view<short>>::value, "");
static_assert(CanPipe_R<TestRange, RangeAdaptorClosureMemberRefQualTest const&, hamon::ranges::empty_view<float>>::value, "");
static_assert(CanPipe_R<TestRange, RangeAdaptorClosureMemberRefQualTest const&&, hamon::ranges::empty_view<double>>::value, "");

using FirstIdentityThenMemberRefQualTest =
	decltype(IdentityRangeAdaptorClosure{} | RangeAdaptorClosureMemberRefQualTest{});
static_assert(is_range_adaptor_closure<FirstIdentityThenMemberRefQualTest>(), "");
static_assert(CanPipe_R<TestRange, FirstIdentityThenMemberRefQualTest&, hamon::ranges::empty_view<char>>::value, "");
static_assert(CanPipe_R<TestRange, FirstIdentityThenMemberRefQualTest&&, hamon::ranges::empty_view<short>>::value, "");
static_assert(CanPipe_R<TestRange, FirstIdentityThenMemberRefQualTest const&, hamon::ranges::empty_view<float>>::value, "");
static_assert(CanPipe_R<TestRange, FirstIdentityThenMemberRefQualTest const&&, hamon::ranges::empty_view<double>>::value, "");

#if 0	// TODO
using FirstTransformThenMemberRefQualTest =
decltype(hamon::views::transform([](auto x) { return x; }) | RangeAdaptorClosureMemberRefQualTest{});
static_assert(CanPipe_R<TestRange, FirstTransformThenMemberRefQualTest&, hamon::ranges::empty_view<char>>::value, "");
static_assert(CanPipe_R<TestRange, FirstTransformThenMemberRefQualTest&&, hamon::ranges::empty_view<short>>::value, "");
static_assert(CanPipe_R<TestRange, FirstTransformThenMemberRefQualTest const&, hamon::ranges::empty_view<float>>::value, "");
static_assert(CanPipe_R<TestRange, FirstTransformThenMemberRefQualTest const&&, hamon::ranges::empty_view<double>>::value, "");
#endif

#if 0	// TODO
using FirstMemberRefQualTestThenAll = decltype(RangeAdaptorClosureMemberRefQualTest{} | hamon::views::all);
static_assert(CanPipe_R<TestRange, FirstMemberRefQualTestThenAll&, hamon::ranges::empty_view<char>>::value, "");
static_assert(CanPipe_R<TestRange, FirstMemberRefQualTestThenAll&&, hamon::ranges::empty_view<short>>::value, "");
static_assert(CanPipe_R<TestRange, FirstMemberRefQualTestThenAll const&, hamon::ranges::empty_view<float>>::value, "");
static_assert(CanPipe_R<TestRange, FirstMemberRefQualTestThenAll const&&, hamon::ranges::empty_view<double>>::value, "");
#endif

struct RangeAdaptorClosureParameterRefQualTest
	: hamon::ranges::range_adaptor_closure<RangeAdaptorClosureParameterRefQualTest>
{
	HAMON_CXX14_CONSTEXPR char operator()(TestRange&)
	{
		return {};
	}

	HAMON_CXX14_CONSTEXPR short operator()(TestRange&&)
	{
		return {};
	}

	HAMON_CXX14_CONSTEXPR float operator()(TestRange const&)
	{
		return {};
	}

	HAMON_CXX14_CONSTEXPR double operator()(TestRange const&&)
	{
		return {};
	}
};
static_assert(is_range_adaptor_closure<RangeAdaptorClosureParameterRefQualTest>(), "");
static_assert(CanPipe_R<TestRange&, RangeAdaptorClosureParameterRefQualTest, char>::value, "");
static_assert(CanPipe_R<TestRange&&, RangeAdaptorClosureParameterRefQualTest, short>::value, "");
static_assert(CanPipe_R<TestRange const&, RangeAdaptorClosureParameterRefQualTest, float>::value, "");
static_assert(CanPipe_R<TestRange const&&, RangeAdaptorClosureParameterRefQualTest, double>::value, "");
static_assert(!CanPipe_R<TestRange&, RangeAdaptorClosureParameterRefQualTest const, char>::value, "");
static_assert(!CanPipe_R<TestRange&&, RangeAdaptorClosureParameterRefQualTest const, short>::value, "");
static_assert(!CanPipe_R<TestRange const&, RangeAdaptorClosureParameterRefQualTest const, float>::value, "");
static_assert(!CanPipe_R<TestRange const&&, RangeAdaptorClosureParameterRefQualTest const, double>::value, "");

struct MoveOnlyRangeAdaptorClosure
	: hamon::ranges::range_adaptor_closure<MoveOnlyRangeAdaptorClosure>
{
	MoveOnlyRangeAdaptorClosure()                                   = default;
	MoveOnlyRangeAdaptorClosure(MoveOnlyRangeAdaptorClosure const&) = delete;
	MoveOnlyRangeAdaptorClosure(MoveOnlyRangeAdaptorClosure&&)      = default;

	void operator()(TestRange const&) {}
};
static_assert(is_range_adaptor_closure<MoveOnlyRangeAdaptorClosure>(), "");
static_assert(CanPipe<TestRange, MoveOnlyRangeAdaptorClosure>::value, "");
static_assert(CanPipe<TestRange, MoveOnlyRangeAdaptorClosure&>::value, "");
static_assert(CanPipe<MoveOnlyRangeAdaptorClosure, IdentityRangeAdaptorClosure>::value, "");
static_assert(CanPipe<IdentityRangeAdaptorClosure, MoveOnlyRangeAdaptorClosure>::value, "");
static_assert(!CanPipe<MoveOnlyRangeAdaptorClosure&, IdentityRangeAdaptorClosure>::value, "");
static_assert(!CanPipe<IdentityRangeAdaptorClosure, MoveOnlyRangeAdaptorClosure&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Slice : hamon::ranges::range_adaptor_closure<Slice>
{
	using size_type = typename hamon::string_view::size_type;

	size_type start;
	size_type end;

	HAMON_CXX11_CONSTEXPR Slice(size_type s, size_type e = hamon::string_view::npos)
		: start(s), end(e)
	{}

	HAMON_CXX11_CONSTEXPR hamon::string_view operator()(hamon::string_view sv) const
	{
		return sv.substr(start, end - start);
	}
};

struct RemovePrefix : hamon::ranges::range_adaptor_closure<RemovePrefix>
{
	using size_type = typename hamon::string_view::size_type;

	size_type n;

	HAMON_CXX11_CONSTEXPR RemovePrefix(size_type n_)
		: n(n_)
	{}

	HAMON_CXX14_CONSTEXPR hamon::string_view operator()(hamon::string_view sv) const
	{
		sv.remove_prefix(n);
		return sv;
	}
};

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		hamon::string_view str = "01234567";

		Slice slicer{1, 6};

		auto sv1 = slicer(str);
		auto sv2 = str | slicer;
		auto sv3 = str | slicer | slicer;
		auto sv4 = str | (slicer | slicer);
		VERIFY(sv1 == "12345");
		VERIFY(sv2 == "12345");
		VERIFY(sv3 == "2345");
		VERIFY(sv4 == "2345");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		hamon::string_view str = "ABCDEFGHIJK";

		RemovePrefix a{2};

		auto sv1 = a(str);
		auto sv2 = str | a;
		auto sv3 = str | RemovePrefix(1) | RemovePrefix(3);
		auto sv4 = str | (RemovePrefix(1) | RemovePrefix(3));
		VERIFY(sv1 == "CDEFGHIJK");
		VERIFY(sv2 == "CDEFGHIJK");
		VERIFY(sv3 == "EFGHIJK");
		VERIFY(sv4 == "EFGHIJK");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		hamon::string_view str = "0123456789";

		auto sv1 = str | RemovePrefix(2) | Slice(1, 5);
		auto sv2 = str | Slice(1, 5) | RemovePrefix(2);
		VERIFY(sv1 == "3456");
		VERIFY(sv2 == "34");

		auto a1 = RemovePrefix(2) | Slice(1, 5);
		auto sv3 = a1(str);
		auto sv4 = str | a1;
		VERIFY(sv3 == "3456");
		VERIFY(sv4 == "3456");

		auto a2 = Slice(1, 5) | RemovePrefix(2);
		auto sv5 = a2(str);
		auto sv6 = str | a2;
		VERIFY(sv5 == "34");
		VERIFY(sv6 == "34");

		auto sv7 = str | RemovePrefix(1) | a2;
		auto sv8 = str | a2 | RemovePrefix(1);
		VERIFY(sv7 == "45");
		VERIFY(sv8 == "4");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, RangeAdaptorClosureTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace range_adaptor_closure_test
}	// namespace hamon_ranges_test
