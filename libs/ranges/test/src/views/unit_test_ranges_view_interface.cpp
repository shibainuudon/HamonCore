/**
 *	@file	unit_test_ranges_view_interface.cpp
 *
 *	@brief	ranges::view_interface のテスト
 */

#include <hamon/ranges/views/view_interface.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/is_detected.hpp>
//#include <hamon/type_traits/common_type.hpp>
//#include <hamon/type_traits/make_signed.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include "iterator_test.hpp"
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{
namespace view_interface_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

#if 0
template <typename T>
concept ValidViewInterfaceType = requires { typename hamon::ranges::view_interface<T>; };
#else
template <typename T>
using ValidViewInterfaceType = hamon::is_detected<hamon::ranges::view_interface, T>;
#endif

struct Empty { };

static_assert(!ValidViewInterfaceType<void>::value, "");
static_assert(!ValidViewInterfaceType<void*>::value, "");
static_assert(!ValidViewInterfaceType<Empty*>::value, "");
static_assert(!ValidViewInterfaceType<Empty const>::value, "");
static_assert(!ValidViewInterfaceType<Empty&>::value, "");
static_assert( ValidViewInterfaceType<Empty>::value, "");

using InputIter = input_iterator_wrapper<const int>;

struct InputRange : hamon::ranges::view_interface<InputRange>
{
	int buff[8] ={ 0, 1, 2, 3, 4, 5, 6, 7 };
	HAMON_CXX11_CONSTEXPR InputIter begin() const noexcept { return InputIter{ buff }; }
	HAMON_CXX11_CONSTEXPR InputIter end()   const noexcept { return InputIter{ buff + 8 }; }
};

struct NotSizedSentinel
{
	using value_type = int;
	using difference_type = hamon::ptrdiff_t;
	using iterator_concept = hamon::forward_iterator_tag;

	explicit NotSizedSentinel() = default;
	explicit NotSizedSentinel(int*);
	int& operator*() const;
	NotSizedSentinel& operator++();
	NotSizedSentinel operator++(int);
	bool operator==(NotSizedSentinel const&) const;
};
//static_assert(hamon::forward_iterator_t<NotSizedSentinel>::value, "");

using ForwardIter = forward_iterator_wrapper<int>;
using ConstForwardIter = forward_iterator_wrapper<int const>;

struct ForwardRange : hamon::ranges::view_interface<ForwardRange>
{
	int buff[8] ={ 0, 1, 2, 3, 4, 5, 6, 7 };
	HAMON_CXX14_CONSTEXPR ForwardIter      begin()       noexcept { return ForwardIter     { buff }; }
	HAMON_CXX11_CONSTEXPR ConstForwardIter begin() const noexcept { return ConstForwardIter{ buff }; }
	HAMON_CXX14_CONSTEXPR ForwardIter      end()         noexcept { return ForwardIter     { buff + 8 }; }
	HAMON_CXX11_CONSTEXPR ConstForwardIter end()   const noexcept { return ConstForwardIter{ buff + 8 }; }
};
static_assert(hamon::ranges::view_t<ForwardRange>::value, "");

struct MoveOnlyForwardRange : hamon::ranges::view_interface<MoveOnlyForwardRange>
{
	int buff[8] ={ 0, 1, 2, 3, 4, 5, 6, 7 };
	MoveOnlyForwardRange(MoveOnlyForwardRange const&) = delete;
	MoveOnlyForwardRange(MoveOnlyForwardRange &&) = default;
	MoveOnlyForwardRange& operator=(MoveOnlyForwardRange &&) = default;
	MoveOnlyForwardRange() = default;
	HAMON_CXX14_CONSTEXPR ForwardIter      begin()       noexcept { return ForwardIter     { buff }; }
	HAMON_CXX11_CONSTEXPR ConstForwardIter begin() const noexcept { return ConstForwardIter{ buff }; }
	HAMON_CXX14_CONSTEXPR ForwardIter      end()         noexcept { return ForwardIter     { buff + 8 }; }
	HAMON_CXX11_CONSTEXPR ConstForwardIter end()   const noexcept { return ConstForwardIter{ buff + 8 }; }
};
static_assert(hamon::ranges::view_t<MoveOnlyForwardRange>::value, "");

struct MI
	: hamon::ranges::view_interface<InputRange>
	, hamon::ranges::view_interface<MoveOnlyForwardRange>
{};
static_assert(!hamon::ranges::view_t<MI>::value, "");

struct EmptyIsTrue : hamon::ranges::view_interface<EmptyIsTrue>
{
	using base_type = hamon::ranges::view_interface<EmptyIsTrue>;
	int buff[8] ={ 0, 1, 2, 3, 4, 5, 6, 7 };
	HAMON_CXX14_CONSTEXPR ForwardIter      begin()       noexcept { return ForwardIter     { buff }; }
	HAMON_CXX11_CONSTEXPR ConstForwardIter begin() const noexcept { return ConstForwardIter{ buff }; }
	HAMON_CXX14_CONSTEXPR ForwardIter      end()         noexcept { return ForwardIter     { buff + 8 }; }
	HAMON_CXX11_CONSTEXPR ConstForwardIter end()   const noexcept { return ConstForwardIter{ buff + 8 }; }
	HAMON_CXX11_CONSTEXPR bool empty() const noexcept { return true; }
};
static_assert(hamon::ranges::view_t<EmptyIsTrue>::value, "");

using RAIter = random_access_iterator_wrapper<int>;
using ConstRAIter = random_access_iterator_wrapper<int const>;

struct SizeIsTen : hamon::ranges::view_interface<SizeIsTen>
{
	using base_type = hamon::ranges::view_interface<SizeIsTen>;
	int buff[8] ={ 0, 1, 2, 3, 4, 5, 6, 7 };
	HAMON_CXX14_CONSTEXPR RAIter      begin()       noexcept { return RAIter     { buff }; }
	HAMON_CXX11_CONSTEXPR ConstRAIter begin() const noexcept { return ConstRAIter{ buff }; }
	HAMON_CXX14_CONSTEXPR RAIter      end()         noexcept { return RAIter     { buff + 8 }; }
	HAMON_CXX11_CONSTEXPR ConstRAIter end()   const noexcept { return ConstRAIter{ buff + 8 }; }
	HAMON_CXX11_CONSTEXPR hamon::size_t size()  const noexcept { return 10; }
};
static_assert(hamon::ranges::view_t<SizeIsTen>::value, "");

struct RARange : hamon::ranges::view_interface<RARange>
{
	int buff[8] ={ 0, 1, 2, 3, 4, 5, 6, 7 };
	HAMON_CXX14_CONSTEXPR RAIter      begin()       noexcept { return RAIter     { buff }; }
	HAMON_CXX11_CONSTEXPR ConstRAIter begin() const noexcept { return ConstRAIter{ buff }; }
	HAMON_CXX14_CONSTEXPR RAIter      end()         noexcept { return RAIter     { buff + 8 }; }
	HAMON_CXX11_CONSTEXPR ConstRAIter end()   const noexcept { return ConstRAIter{ buff + 8 }; }
};
static_assert(hamon::ranges::view_t<RARange>::value, "");

using ContIter = contiguous_iterator_wrapper<int>;
using ConstContIter = contiguous_iterator_wrapper<int const>;

struct ContRange : hamon::ranges::view_interface<ContRange>
{
	int buff[8] ={ 0, 1, 2, 3, 4, 5, 6, 7 };
	HAMON_CXX14_CONSTEXPR ContIter      begin()       noexcept { return ContIter     { buff }; }
	HAMON_CXX11_CONSTEXPR ConstContIter begin() const noexcept { return ConstContIter{ buff }; }
	HAMON_CXX14_CONSTEXPR ContIter      end()         noexcept { return ContIter     { buff + 8 }; }
	HAMON_CXX11_CONSTEXPR ConstContIter end()   const noexcept { return ConstContIter{ buff + 8 }; }
};
static_assert(hamon::ranges::view_t<ContRange>::value, "");

struct DataIsNull : hamon::ranges::view_interface<DataIsNull>
{
	using base_type = hamon::ranges::view_interface<DataIsNull>;
	int buff[8] ={ 0, 1, 2, 3, 4, 5, 6, 7 };
	HAMON_CXX14_CONSTEXPR ContIter      begin()       noexcept { return ContIter     { buff }; }
	HAMON_CXX11_CONSTEXPR ConstContIter begin() const noexcept { return ConstContIter{ buff }; }
	HAMON_CXX14_CONSTEXPR ContIter      end()         noexcept { return ContIter     { buff + 8 }; }
	HAMON_CXX11_CONSTEXPR ConstContIter end()   const noexcept { return ConstContIter{ buff + 8 }; }
	HAMON_CXX14_CONSTEXPR int*       data()       noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR int const* data() const noexcept { return nullptr; }
};
static_assert(hamon::ranges::view_t<DataIsNull>::value, "");

struct BoolConvertibleComparison : hamon::ranges::view_interface<BoolConvertibleComparison>
{
	struct ResultType
	{
		bool value;
		HAMON_CXX11_CONSTEXPR operator bool() const noexcept { return value; }
	};

	struct SentinelType
	{
		int* base_;
		explicit SentinelType() = default;
		constexpr explicit SentinelType(int* base) : base_(base) {}
		friend constexpr ResultType operator==(ForwardIter const& iter, SentinelType const& sent) noexcept { return { iter.m_ptr == sent.base_ }; }
		friend constexpr ResultType operator==(SentinelType const& sent, ForwardIter const& iter) noexcept { return { iter.m_ptr == sent.base_ }; }
		friend constexpr ResultType operator!=(ForwardIter const& iter, SentinelType const& sent) noexcept { return { iter.m_ptr != sent.base_ }; }
		friend constexpr ResultType operator!=(SentinelType const& sent, ForwardIter const& iter) noexcept { return { iter.m_ptr != sent.base_ }; }
	};

	int buff[8] ={ 0, 1, 2, 3, 4, 5, 6, 7 };
	HAMON_CXX11_CONSTEXPR ForwardIter begin() const noexcept { return ForwardIter{ const_cast<int*>(buff) }; }
	HAMON_CXX11_CONSTEXPR SentinelType end()  const noexcept { return SentinelType{ const_cast<int*>(buff) + 8 }; }
};
static_assert(hamon::ranges::view_t<BoolConvertibleComparison>::value, "");

#if 0
template <typename T>
concept EmptyInvocable = requires (T const& obj) { obj.empty(); };
#else
template <typename T>
using EmptyInvocableImpl = decltype(hamon::declval<T const&>().empty());
template <typename T>
using EmptyInvocable = hamon::is_detected<EmptyInvocableImpl, T>;
#endif

#if 0
template <typename T>
concept BoolOpInvocable = requires (T const& obj) { bool(obj); };
#else
template <typename T>
using BoolOpInvocableImpl = decltype(bool(hamon::declval<T const&>()));
template <typename T>
using BoolOpInvocable = hamon::is_detected<BoolOpInvocableImpl, T>;
#endif

HAMON_CXX14_CONSTEXPR bool EmptyTest()
{
	static_assert(!EmptyInvocable<InputRange>::value, "");
	static_assert( EmptyInvocable<ForwardRange>::value, "");
	static_assert( EmptyInvocable<EmptyIsTrue>::value, "");
	static_assert( EmptyInvocable<MoveOnlyForwardRange>::value, "");
	static_assert( EmptyInvocable<BoolConvertibleComparison>::value, "");

	static_assert(!BoolOpInvocable<InputRange>::value, "");
	static_assert( BoolOpInvocable<ForwardRange>::value, "");
	static_assert( BoolOpInvocable<EmptyIsTrue>::value, "");
	static_assert( BoolOpInvocable<MoveOnlyForwardRange>::value, "");
	static_assert( BoolOpInvocable<BoolConvertibleComparison>::value, "");

	ForwardRange forwardRange;
	static_assert(!noexcept(forwardRange.empty()), "");
	VERIFY(!forwardRange.empty());
	static_assert(!noexcept(!forwardRange), "");
	VERIFY(forwardRange);
	VERIFY(!hamon::ranges::empty(forwardRange));

	EmptyIsTrue emptyTrue;
	static_assert(noexcept(emptyTrue.empty()), "");
	VERIFY(emptyTrue.empty());
	VERIFY(!emptyTrue.base_type::empty());

	//static_assert(noexcept(!emptyTrue), "");
	VERIFY(!emptyTrue);
	VERIFY(!emptyTrue.base_type::operator bool());
	VERIFY(hamon::ranges::empty(emptyTrue));

	// Try calling empty on an rvalue.
	MoveOnlyForwardRange moveOnly;
	static_assert(!noexcept(moveOnly.empty()), "");
	VERIFY(!hamon::move(moveOnly).empty());

	BoolConvertibleComparison boolConv;
	//static_assert(noexcept(boolConv.empty()), "");
	VERIFY(!boolConv.empty());
	VERIFY(boolConv);
	VERIFY(!hamon::ranges::empty(boolConv));

	return true;
}

GTEST_TEST(RangesViewInterfaceTest, EmptyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest());

	{
		HAMON_CXX11_CONSTEXPR ForwardRange const forwardRange;
		static_assert(!noexcept(forwardRange.empty()), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!forwardRange.empty());
		static_assert(!noexcept(!forwardRange), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(forwardRange);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::ranges::empty(forwardRange));
	}
	{
		HAMON_CXX11_CONSTEXPR EmptyIsTrue const emptyTrue;
		static_assert(noexcept(emptyTrue.empty()), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(emptyTrue.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!emptyTrue.base_type::empty());
		//static_assert(noexcept(!emptyTrue), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!emptyTrue);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!emptyTrue.base_type::operator bool());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::empty(emptyTrue));
	}
	{
		// Try calling empty on an rvalue.
		HAMON_CXX11_CONSTEXPR MoveOnlyForwardRange const moveOnly;
		static_assert(!noexcept(moveOnly.empty()), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::move(moveOnly).empty());
	}
	{
		HAMON_CXX11_CONSTEXPR BoolConvertibleComparison const boolConv;
		//static_assert(noexcept(boolConv.empty()), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!boolConv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(boolConv);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!hamon::ranges::empty(boolConv));
	}
}

HAMON_CXX14_CONSTEXPR bool CBeginCEndTest()
{
	{
		InputRange rng;
		VERIFY(rng.cbegin() != rng.cend());
	}
	{
		ForwardRange rng;
		VERIFY(rng.cbegin() != rng.cend());
	}
	return true;
}

GTEST_TEST(RangesViewInterfaceTest, CBeginCEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CBeginCEndTest());

	{
		HAMON_CXX11_CONSTEXPR InputRange const rng;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(rng.cbegin() != rng.cend());
	}
	{
		HAMON_CXX11_CONSTEXPR ForwardRange const rng;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(rng.cbegin() != rng.cend());
	}
}

#if 0
template <typename T>
concept DataInvocable = requires (T const& obj) { obj.data(); };
#else
template <typename T>
using DataInvocableImpl = decltype(hamon::declval<T const&>().data());
template <typename T>
using DataInvocable = hamon::is_detected<DataInvocableImpl, T>;
#endif

HAMON_CXX14_CONSTEXPR bool DataTest()
{
	static_assert(!DataInvocable<ForwardRange>::value, "");
	static_assert( DataInvocable<ContRange>::value, "");
	static_assert( DataInvocable<DataIsNull>::value, "");

	{
		ContRange contiguous;
		//static_assert(noexcept(contiguous.data()), "");
		VERIFY(contiguous.data() == contiguous.buff);
		VERIFY(hamon::ranges::data(contiguous) == contiguous.buff);
	}
	{
		DataIsNull dataNull;
		static_assert(noexcept(dataNull.data()), "");
		VERIFY(dataNull.data() == nullptr);
		VERIFY(dataNull.base_type::data() == dataNull.buff);
		VERIFY(hamon::ranges::data(dataNull) == nullptr);
	}

	return true;
}

GTEST_TEST(RangesViewInterfaceTest, DataTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest());

	{
		HAMON_CXX11_CONSTEXPR ContRange const contiguous;
		//static_assert(noexcept(contiguous.data()), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(contiguous.data() == contiguous.buff);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::data(contiguous) == contiguous.buff);
	}
	{
		HAMON_CXX11_CONSTEXPR DataIsNull const dataNull;
		static_assert(noexcept(dataNull.data()), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(dataNull.data() == nullptr);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(dataNull.base_type::data() == dataNull.buff);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::data(dataNull) == nullptr);
	}
}

#if 0
template <typename T>
concept SizeInvocable = requires (T const& obj) { obj.size(); };
#else
template <typename T>
using SizeInvocableImpl = decltype(hamon::declval<T const&>().size());
template <typename T>
using SizeInvocable = hamon::is_detected<SizeInvocableImpl, T>;
#endif

HAMON_CXX14_CONSTEXPR bool SizeTest()
{
	static_assert(!SizeInvocable<InputRange>::value, "");
	static_assert(!SizeInvocable<NotSizedSentinel>::value, "");
	static_assert( SizeInvocable<RARange>::value, "");
	static_assert( SizeInvocable<SizeIsTen>::value, "");

	//using SignedSize = hamon::common_type_t<hamon::ptrdiff_t, hamon::make_signed_t<hamon::size_t>>;
	RARange randomAccess;
	static_assert(!noexcept(randomAccess.size()), "");
	VERIFY(randomAccess.size() == 8);

	VERIFY(hamon::ranges::size(randomAccess) == 8);
	//static_assert(hamon::same_as<decltype(hamon::ranges::size(hamon::declval<RARange>())), hamon::size_t>);
	//static_assert(hamon::same_as<decltype(hamon::ranges::ssize(hamon::declval<RARange>())), SignedSize>);

	SizeIsTen sizeTen;
	static_assert(noexcept(sizeTen.size()), "");
	VERIFY(sizeTen.size() == 10);
	VERIFY(sizeTen.base_type::size() == 8);
	VERIFY(hamon::ranges::size(sizeTen) == 10);

	return true;
}

GTEST_TEST(RangesViewInterfaceTest, SizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest());

	HAMON_CXX11_CONSTEXPR RARange randomAccess;
	static_assert(!noexcept(randomAccess.size()), "");
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(randomAccess.size() == 8);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::size(randomAccess) == 8);

	HAMON_CXX11_CONSTEXPR SizeIsTen sizeTen;
	static_assert(noexcept(sizeTen.size()), "");
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sizeTen.size() == 10);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sizeTen.base_type::size() == 8);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::ranges::size(sizeTen) == 10);
}

#if 0
template <typename T>
concept SubscriptInvocable = requires (T const& obj, hamon::size_t n) { obj[n]; };
#else
template <typename T>
using SubscriptInvocableImpl = decltype(hamon::declval<T const&>()[hamon::declval<hamon::size_t>()]);
template <typename T>
using SubscriptInvocable = hamon::is_detected<SubscriptInvocableImpl, T>;
#endif

HAMON_CXX14_CONSTEXPR bool SubscriptTest()
{
	static_assert(!SubscriptInvocable<ForwardRange>::value, "");
	static_assert( SubscriptInvocable<RARange>::value, "");

	RARange randomAccess;
	static_assert(!noexcept(randomAccess[2]), "");
	VERIFY(randomAccess[2] == 2);
	randomAccess[2] = 3;
	VERIFY(randomAccess[2] == 3);

	return true;
}

GTEST_TEST(RangesViewInterfaceTest, SubscriptTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubscriptTest());

	HAMON_CXX11_CONSTEXPR RARange const randomAccess;
	static_assert(!noexcept(randomAccess[2]), "");
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(randomAccess[2] == 2);
}

#if 0
template <typename T>
concept FrontInvocable = requires (T const& obj) { obj.front(); };
#else
template <typename T>
using FrontInvocableImpl = decltype(hamon::declval<T const&>().front());
template <typename T>
using FrontInvocable = hamon::is_detected<FrontInvocableImpl, T>;
#endif

#if 0
template <typename T>
concept BackInvocable = requires (T const& obj) { obj.back(); };
#else
template <typename T>
using BackInvocableImpl = decltype(hamon::declval<T const&>().back());
template <typename T>
using BackInvocable = hamon::is_detected<BackInvocableImpl, T>;
#endif

HAMON_CXX14_CONSTEXPR bool FrontBackTest()
{
	static_assert(!FrontInvocable<InputRange>::value, "");
	static_assert( FrontInvocable<ForwardRange>::value, "");
	static_assert( FrontInvocable<RARange>::value, "");
	static_assert(!BackInvocable<InputRange>::value, "");
	static_assert(!BackInvocable<ForwardRange>::value, "");
	static_assert( BackInvocable<RARange>::value, "");

	ForwardRange forwardRange;
	static_assert(!noexcept(forwardRange.front()), "");
	VERIFY(forwardRange.front() == 0);
	forwardRange.front() = 2;
	VERIFY(forwardRange.front() == 2);

	RARange randomAccess;
	static_assert(!noexcept(randomAccess.front()), "");
	VERIFY(randomAccess.front() == 0);
	randomAccess.front() = 2;
	VERIFY(randomAccess.front() == 2);

	static_assert(!noexcept(randomAccess.back()), "");
	VERIFY(randomAccess.back() == 7);
	randomAccess.back() = 2;
	VERIFY(randomAccess.back() == 2);

	return true;
}

GTEST_TEST(RangesViewInterfaceTest, FrontBackTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrontBackTest());

	{
		HAMON_CXX11_CONSTEXPR ForwardRange const forwardRange;
		static_assert(!noexcept(forwardRange.front()), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(forwardRange.front() == 0);
	}
	{
		HAMON_CXX11_CONSTEXPR RARange const randomAccess;
		static_assert(!noexcept(randomAccess.front()), "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(randomAccess.front() == 0);

		static_assert(!noexcept(randomAccess.back()), "");
//		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(randomAccess.back() == 7);	// TODO
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(randomAccess.back() == 7);
	}
}

struct V1 : hamon::ranges::view_interface<V1> { };
struct V2 : hamon::ranges::view_interface<V2> { V1 base_; };
static_assert(sizeof(V2) == sizeof(V1), "");

#undef VERIFY

}	// namespace view_interface_test
}	// namespace hamon_ranges_test
