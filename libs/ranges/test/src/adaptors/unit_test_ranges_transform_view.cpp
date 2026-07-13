/**
 *	@file	unit_test_ranges_transform_view.cpp
 *
 *	@brief	ranges::transform_view のテスト
 */

#include <hamon/ranges/adaptors/transform_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/compare.hpp>
#include <hamon/concepts.hpp>
#include <hamon/iterator.hpp>
#include <hamon/iterator/detail/can_reference.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace transform_view_test
{

struct Double
{
	HAMON_CXX11_CONSTEXPR int operator()(int x) const HAMON_NOEXCEPT
	{
		return x * 2;
	}
};
static_assert(hamon::regular_invocable<Double&, int&>, "");
//static_assert(hamon::detail::can_reference<hamon::invoke_result_t<Double&, int&>>, "");

struct NonMovable
{
	HAMON_CXX11_CONSTEXPR int operator()(int x) const HAMON_NOEXCEPT
	{
		return x * 2;
	}

	NonMovable() = default;
	NonMovable(NonMovable const&) = default;
	NonMovable(NonMovable &&) = delete;
	NonMovable& operator=(NonMovable const&) = default;
	NonMovable& operator=(NonMovable &&) = default;
};
static_assert(hamon::regular_invocable<NonMovable&, int&>, "");
//static_assert(hamon::detail::can_reference<hamon::invoke_result_t<NonMovable&, int&>>, "");

struct VoidFunc
{
	HAMON_CXX14_CONSTEXPR void operator()(int& x) const HAMON_NOEXCEPT
	{
		x *= 2;
	}
};
static_assert(hamon::regular_invocable<VoidFunc&, int&>, "");
//static_assert(!hamon::detail::can_reference<hamon::invoke_result_t<VoidFunc&, int&>>, "");

struct NonConstFunc
{
	HAMON_CXX14_CONSTEXPR int operator()(int x) HAMON_NOEXCEPT
	{
		return x * 2;
	}
};

struct Empty{};
static_assert(!hamon::regular_invocable<Empty&, int&>, "");

struct Ref
{
	HAMON_CXX11_CONSTEXPR int& operator()(int& x) const HAMON_NOEXCEPT
	{
		return x;
	}
};

struct ToFloat
{
	HAMON_CXX11_CONSTEXPR float operator()(int x) const HAMON_NOEXCEPT
	{
		return static_cast<float>(x);
	}
};

struct NoDefaultCtorFunc
{
	HAMON_CXX11_CONSTEXPR int operator()(int x) const HAMON_NOEXCEPT
	{
		return x * 2;
	}

	NoDefaultCtorFunc() = delete;
	NoDefaultCtorFunc(NoDefaultCtorFunc const&) = default;
	NoDefaultCtorFunc(NoDefaultCtorFunc &&) = default;
	NoDefaultCtorFunc& operator=(NoDefaultCtorFunc const&) = default;
	NoDefaultCtorFunc& operator=(NoDefaultCtorFunc &&) = default;
};

struct ThrowDefaultCtorFunc
{
	HAMON_CXX11_CONSTEXPR int operator()(int x) const HAMON_NOEXCEPT
	{
		return x * 2;
	}

	HAMON_CXX11_CONSTEXPR ThrowDefaultCtorFunc() noexcept(false) {}
	ThrowDefaultCtorFunc(ThrowDefaultCtorFunc const&) = default;
	ThrowDefaultCtorFunc(ThrowDefaultCtorFunc &&) = default;
	ThrowDefaultCtorFunc& operator=(ThrowDefaultCtorFunc const&) = default; 
	ThrowDefaultCtorFunc& operator=(ThrowDefaultCtorFunc &&) = default;
};

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct NoDefaultCtorView : public test_range<T, Iterator, Sentinel>, hamon::ranges::view_base
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::test_range;

	NoDefaultCtorView() = delete;
};
template <typename T> using NoDefaultCtorContiguousView    = NoDefaultCtorView<T, contiguous_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorRandomAccessView  = NoDefaultCtorView<T, random_access_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorBidirectionalView = NoDefaultCtorView<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorForwardView       = NoDefaultCtorView<T, forward_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorInputView         = NoDefaultCtorView<T, input_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorOutputView        = NoDefaultCtorView<T, output_iterator_wrapper<T>>;

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct NoThrowDefaultCtorView : public test_range<T, Iterator, Sentinel>, hamon::ranges::view_base
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::test_range;

	NoThrowDefaultCtorView() noexcept {}
};
template <typename T> using NoThrowDefaultCtorContiguousView    = NoThrowDefaultCtorView<T, contiguous_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorRandomAccessView  = NoThrowDefaultCtorView<T, random_access_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorBidirectionalView = NoThrowDefaultCtorView<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorForwardView       = NoThrowDefaultCtorView<T, forward_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorInputView         = NoThrowDefaultCtorView<T, input_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorOutputView        = NoThrowDefaultCtorView<T, output_iterator_wrapper<T>>;

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct ThrowDefaultCtorView : public test_range<T, Iterator, Sentinel>, hamon::ranges::view_base
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::test_range;

	ThrowDefaultCtorView() noexcept(false) {}
};
template <typename T> using ThrowDefaultCtorContiguousView    = ThrowDefaultCtorView<T, contiguous_iterator_wrapper<T>>;
template <typename T> using ThrowDefaultCtorRandomAccessView  = ThrowDefaultCtorView<T, random_access_iterator_wrapper<T>>;
template <typename T> using ThrowDefaultCtorBidirectionalView = ThrowDefaultCtorView<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using ThrowDefaultCtorForwardView       = ThrowDefaultCtorView<T, forward_iterator_wrapper<T>>;
template <typename T> using ThrowDefaultCtorInputView         = ThrowDefaultCtorView<T, input_iterator_wrapper<T>>;
template <typename T> using ThrowDefaultCtorOutputView        = ThrowDefaultCtorView<T, output_iterator_wrapper<T>>;

template <typename T>
struct ConstNotView : hamon::ranges::view_base
{
	using iterator = T*;
	using sentinel = T*;

	HAMON_CXX14_CONSTEXPR iterator begin() noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR sentinel end()   noexcept { return nullptr; }
};

template <typename V, typename F, typename = void>
struct CanInstantiateTransformView
	: hamon::false_type {};

template <typename V, typename F>
struct CanInstantiateTransformView<V, F, hamon::void_t<hamon::ranges::transform_view<V, F>>>
	: hamon::true_type {};

static_assert( CanInstantiateTransformView<test_input_view<int>, Double>::value, "");
static_assert( CanInstantiateTransformView<test_input_view<int>, NonConstFunc>::value, "");
static_assert(!CanInstantiateTransformView<test_output_view<int>, Double>::value, "");
static_assert(!CanInstantiateTransformView<test_input_range<int>, Double>::value, "");
static_assert(!CanInstantiateTransformView<test_input_view<int>, Empty>::value, "");
static_assert(!CanInstantiateTransformView<test_input_view<int>, NonMovable>::value, "");
static_assert(!CanInstantiateTransformView<test_input_view<int>, VoidFunc>::value, "");

static_assert(!hamon::ranges::output_range_t<hamon::ranges::transform_view<test_input_view<int>, Double>, int>::value, "");
static_assert(!hamon::ranges::output_range_t<hamon::ranges::transform_view<test_input_view<int>, Ref>, int>::value, "");
static_assert(!hamon::ranges::output_range_t<hamon::ranges::transform_view<test_forward_view<int>, Double>, int>::value, "");
static_assert( hamon::ranges::output_range_t<hamon::ranges::transform_view<test_forward_view<int>, Ref>, int>::value, "");
static_assert(!hamon::ranges::output_range_t<hamon::ranges::transform_view<test_bidirectional_view<int>, Double>, int>::value, "");
static_assert( hamon::ranges::output_range_t<hamon::ranges::transform_view<test_bidirectional_view<int>, Ref>, int>::value, "");
static_assert(!hamon::ranges::output_range_t<hamon::ranges::transform_view<test_random_access_view<int>, Double>, int>::value, "");
static_assert( hamon::ranges::output_range_t<hamon::ranges::transform_view<test_random_access_view<int>, Ref>, int>::value, "");
static_assert(!hamon::ranges::output_range_t<hamon::ranges::transform_view<test_contiguous_view<int>, Double>, int>::value, "");
static_assert( hamon::ranges::output_range_t<hamon::ranges::transform_view<test_contiguous_view<int>, Ref>, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View, typename F>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = View<T>;
	using TV = hamon::ranges::transform_view<V, F>;

	static_assert(hamon::ranges::range_t<TV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range<TV> == false, "");
	static_assert(hamon::ranges::sized_range_t<TV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(hamon::ranges::approximately_sized_range<TV> == hamon::ranges::approximately_sized_range<V>, "");
	static_assert(hamon::ranges::output_range_t<TV, T>::value == false, "");
	static_assert(hamon::ranges::input_range<TV> == true, "");
	static_assert(hamon::ranges::forward_range<TV> == hamon::ranges::forward_range<V>, "");
	static_assert(hamon::ranges::bidirectional_range<TV> == hamon::ranges::bidirectional_range<V>, "");
	static_assert(hamon::ranges::random_access_range_t<TV>::value == hamon::ranges::random_access_range_t<V>::value, "");
	static_assert(hamon::ranges::contiguous_range<TV> == false, "");
	static_assert(hamon::ranges::common_range<TV> == hamon::ranges::common_range<V>, "");
	static_assert(hamon::ranges::viewable_range_t<TV>::value == true, "");
	static_assert(hamon::ranges::view_t<TV>::value == true, "");
	static_assert(hamon::ranges::constant_range<TV> == true, "");

	static_assert(hamon::is_default_constructible<TV>::value ==
		(hamon::is_default_constructible<V>::value && hamon::is_default_constructible<F>::value), "");
	static_assert(hamon::is_nothrow_default_constructible<TV>::value ==
		(hamon::is_nothrow_default_constructible<V>::value && hamon::is_nothrow_default_constructible<F>::value), "");

	static_assert(has_base<TV&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<TV&&>::value, "");
	static_assert(has_base<TV const&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<TV const&&>::value == hamon::copy_constructible<V>, "");

	static_assert(hamon::same_as<decltype(hamon::declval<TV&&>().base()), V>, "");
#if !defined(HAMON_USE_STD_RANGES)
	//static_assert(noexcept(hamon::declval<TV&&>().base()) == hamon::is_nothrow_move_constructible<V>::value, "");
#endif

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::copy_constructible<V>)
	{
		static_assert(hamon::same_as<decltype(hamon::declval<TV&>().base()), V>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<TV const&>().base()), V>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<TV const&&>().base()), V>, "");
#if !defined(HAMON_USE_STD_RANGES)
		//static_assert(noexcept(hamon::declval<TV&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
		//static_assert(noexcept(hamon::declval<TV const&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
		//static_assert(noexcept(hamon::declval<TV const&&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
#endif
	}
#endif

	static_assert(has_begin<TV>::value, "");
	static_assert(has_end<TV>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::ranges::range_t<V const>::value)
	{
		static_assert(has_begin<TV const>::value == hamon::regular_invocable<F const&, hamon::ranges::range_reference_t<V const>>, "");
		static_assert(has_end<TV const>::value   == hamon::regular_invocable<F const&, hamon::ranges::range_reference_t<V const>>, "");
	}
	else
	{
		static_assert(has_begin<TV const>::value == false, "");
		static_assert(has_end<TV const>::value   == false, "");
	}
#endif

	static_assert(has_size<TV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(has_size<TV const>::value == hamon::ranges::sized_range_t<V const>::value, "");

	static_assert(has_reserve_hint<TV>::value == hamon::ranges::approximately_sized_range<V>, "");
	static_assert(has_reserve_hint<TV const>::value == hamon::ranges::approximately_sized_range<V const>, "");

	using I = decltype(hamon::declval<TV&>().begin());
	using S = decltype(hamon::declval<TV&>().end());
	using BI = decltype(hamon::declval<V&>().begin());
	static_assert(hamon::same_as<I, S> == hamon::ranges::common_range<V>, "");
	static_assert(has_iterator_category<I>::value == hamon::ranges::forward_range<V>, "");
	static_assert(hamon::same_as<typename I::value_type, T>, "");
	static_assert(hamon::same_as<typename I::difference_type, hamon::ranges::range_difference_t<V>>, "");
	static_assert(hamon::is_default_constructible<I>::value == hamon::is_default_constructible<BI>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<I>::value == hamon::is_nothrow_default_constructible<BI>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using R = test_random_access_view<int>;
	using TV = hamon::ranges::transform_view<R, Double>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert( has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert( has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert( has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert( has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	TV tv{};
	VERIFY(tv.empty());
	VERIFY(tv.begin() == tv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using R = test_input_view<int>;
	using TV = hamon::ranges::transform_view<R, Double>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert(!has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert(!has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert(!has_size<TV&>::value, "");
	static_assert(!has_reserve_hint<TV&>::value, "");
	static_assert(!has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert(!has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert(!has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert(!has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert(!has_size<TV const&>::value, "");
	static_assert(!has_reserve_hint<TV const&>::value, "");
	static_assert(!has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert(!has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int a[] = {1, 2, 3, 4};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::transform_view tv{r, Double{}};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, Double{}};
#endif

	VERIFY(tv.base().begin() == r.begin());
	VERIFY(hamon::move(tv).base().begin() == r.begin());

	{
		auto it = tv.begin();
		VERIFY(it.base() == r.begin());
		VERIFY(hamon::move(it).base() == r.begin());
		VERIFY(it == tv.begin());
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != tv.begin());
		VERIFY(it != tv.end());
		VERIFY(*it == 4);
		it++;
		VERIFY(it != tv.begin());
		VERIFY(it != tv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it != tv.begin());
		VERIFY(it != tv.end());
		VERIFY(*it == 8);
		it++;
		VERIFY(it != tv.begin());
		VERIFY(it == tv.end());
	}
	{
		auto const& crv = tv;
		auto it = crv.begin();
		VERIFY(it == crv.begin());
		VERIFY(it != crv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != crv.begin());
		VERIFY(it != crv.end());
		VERIFY(*it == 4);
		it++;
		VERIFY(it != crv.begin());
		VERIFY(it != crv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it != crv.begin());
		VERIFY(it != crv.end());
		VERIFY(*it == 8);
		it++;
		VERIFY(it != crv.begin());
		VERIFY(it == crv.end());
	}
	{
		auto const& crv = tv;
		auto it = crv.begin();
		auto sent = crv.end();

		VERIFY(!(it == sent));
		VERIFY( (it != sent));
		VERIFY(!(sent == it));
		VERIFY( (sent != it));
	}

	VERIFY(a[0] == 1);
	VERIFY(a[1] == 2);
	VERIFY(a[2] == 3);
	VERIFY(a[3] == 4);

	using I = decltype(tv.begin());
	static_assert(!has_iterator_category<I>::value, "");
	static_assert(hamon::same_as<typename I::iterator_concept, hamon::input_iterator_tag>, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using R = test_random_access_common_view<int const>;
	using TV = hamon::ranges::transform_view<R, Double>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert( has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert( has_back<TV&>::value, "");
	static_assert( has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert( has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert( has_back<TV const&>::value, "");
	static_assert( has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int const a[] = {1, 2, 3, 4};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::transform_view tv{r, Double{}};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, Double{}};
#endif

	VERIFY(tv.size() == 4);
	VERIFY(hamon::as_const(tv).size() == 4);

	VERIFY(tv.reserve_hint() == 4);
	VERIFY(hamon::as_const(tv).reserve_hint() == 4);

	VERIFY(tv.base().begin() == r.begin());
	VERIFY(hamon::move(tv).base().begin() == r.begin());

	{
		auto it = tv.begin();
		VERIFY(it == tv.begin());
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != tv.begin());
		VERIFY(it != tv.end());
		VERIFY(*it == 4);
		it++;
		VERIFY(it != tv.begin());
		VERIFY(it != tv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it != tv.begin());
		VERIFY(it != tv.end());
		VERIFY(*it == 8);
		it++;
		VERIFY(it != tv.begin());
		VERIFY(it == tv.end());

		VERIFY(*--it == 8);
		VERIFY(*it-- == 8);
		VERIFY(*it == 6);

		it -= 2;
		VERIFY(*it == 2);

		it += 3;
		VERIFY(*it == 8);

		it = it - 3;
		VERIFY(it[0] == 2);
		VERIFY(it[1] == 4);
		VERIFY(it[2] == 6);
		VERIFY(it[3] == 8);
	}
	{
		auto it1 = tv.begin() + 1;
		auto it2 = 1 + tv.begin();
		auto it3 = tv.begin() + 2;

		VERIFY( (it1 == it2));
		VERIFY(!(it1 == it3));
		VERIFY(!(it1 != it2));
		VERIFY( (it1 != it3));
		VERIFY(!(it1 <  it2));
		VERIFY( (it1 <  it3));
		VERIFY( (it1 <= it2));
		VERIFY( (it1 <= it3));
		VERIFY(!(it1 >  it2));
		VERIFY(!(it1 >  it3));
		VERIFY( (it1 >= it2));
		VERIFY(!(it1 >= it3));

		VERIFY(!(it3 == it2));
		VERIFY( (it3 == it3));
		VERIFY( (it3 != it2));
		VERIFY(!(it3 != it3));
		VERIFY(!(it3 <  it2));
		VERIFY(!(it3 <  it3));
		VERIFY(!(it3 <= it2));
		VERIFY( (it3 <= it3));
		VERIFY( (it3 >  it2));
		VERIFY(!(it3 >  it3));
		VERIFY( (it3 >= it2));
		VERIFY( (it3 >= it3));

		VERIFY(it3 - it1 == 1);
		VERIFY(it2 - it3 == -1);
	}
	{
		auto const& crv = tv;
		auto it = crv.begin();
		auto sent = crv.end();
		VERIFY(it == crv.begin());
		VERIFY(it != sent);
		VERIFY(*it == 2);
		++it;
		VERIFY(it != crv.begin());
		VERIFY(it != sent);
		VERIFY(*it == 4);
		it++;
		VERIFY(it != crv.begin());
		VERIFY(it != sent);
		VERIFY(*it == 6);
		++it;
		VERIFY(it != crv.begin());
		VERIFY(it != sent);
		VERIFY(*it == 8);
		it++;
		VERIFY(it != crv.begin());
		VERIFY(it == sent);

		it = tv.begin();
		sent = tv.end();
		VERIFY(it == crv.begin());
		VERIFY(sent == crv.end());
	}

	using I = decltype(tv.begin());
	static_assert(has_iterator_category<I>::value, "");
	static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
	static_assert(hamon::same_as<typename I::iterator_concept, hamon::random_access_iterator_tag>, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	using R = test_random_access_view<int>;
	using TV = hamon::ranges::transform_view<R, Double>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert( has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert( has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert( has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert( has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int a[] = {1, 2, 3, 4};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::transform_view tv{r, Double{}};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, Double{}};
#endif
	
	VERIFY(tv.end().base() == r.end());

	{
		auto it = tv.begin();
		VERIFY(it - tv.end() == -4);
		VERIFY(tv.end() - it == 4);
	}
	{
		auto const& crv = tv;
		auto it = crv.begin();
		auto sent = crv.end();
		it = tv.begin();
		sent = tv.end();
		VERIFY(it == crv.begin());
		VERIFY(it != sent);
	}

	{
		using I = decltype(tv.begin());
		using BI = decltype(r.begin());
		I i{};
		BI bi{};
		VERIFY(i.base() == bi);
	}
	{
		using S = decltype(tv.end());
		using BS = decltype(r.end());
		S s{};
		BS bs{};
		VERIFY(s.base() == bs);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	int a[] = {1, 2, 3, 4};
	auto r = a | hamon::views::transform(Double{});
	static_assert(hamon::same_as<decltype(r), hamon::ranges::transform_view<hamon::ranges::ref_view<int[4]>, Double>>, "");
	VERIFY(r[0] == 2);
	VERIFY(r[1] == 4);
	VERIFY(r[2] == 6);
	VERIFY(r[3] == 8);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_eq(r.begin() <=> r.begin()));
	VERIFY(hamon::is_neq(r.begin() <=> r.end()));
#endif

	auto r2 = hamon::views::transform(a, Double{});
	static_assert(hamon::same_as<decltype(r), decltype(r2)>, "");

	using I = decltype(r.begin());
	static_assert(has_iterator_category<I>::value, "");
	static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
	static_assert(hamon::same_as<typename I::iterator_concept, hamon::random_access_iterator_tag>, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test06()
{
	int a[] = {1, 2, 3, 4};

	{
		auto tv = test_input_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(tv.begin());
		static_assert(!has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), void>, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert(!has_pre_decrement<I>::value, "");
		static_assert(!has_post_decrement<I>::value, "");
		static_assert(!has_plus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_minus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_subscript<I>::value, "");
		static_assert( has_eq<I>::value, "");
		static_assert( has_neq<I>::value, "");
		static_assert(!has_lt<I>::value, "");
		static_assert(!has_lteq<I>::value, "");
		static_assert(!has_gt<I>::value, "");
		static_assert(!has_gteq<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I>::value, "");
#endif
		static_assert(!has_plus<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_plus<hamon::ptrdiff_t, I>::value, "");
		static_assert(!has_minus<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_minus<I, I>::value, "");

		using S = decltype(tv.end());
		static_assert(!hamon::same_as<I, S>, "");
		static_assert( has_eq<S, I>::value, "");
		static_assert( has_eq<I, S>::value, "");
		static_assert( has_neq<S, I>::value, "");
		static_assert( has_neq<I, S>::value, "");
		static_assert(!has_minus<I, S>::value, "");
		static_assert(!has_minus<S, I>::value, "");
	}
	{
		auto tv = test_forward_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::forward_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert(!has_pre_decrement<I>::value, "");
		static_assert(!has_post_decrement<I>::value, "");
		static_assert(!has_plus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_minus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_subscript<I>::value, "");
		static_assert( has_eq<I>::value, "");
		static_assert( has_neq<I>::value, "");
		static_assert(!has_lt<I>::value, "");
		static_assert(!has_lteq<I>::value, "");
		static_assert(!has_gt<I>::value, "");
		static_assert(!has_gteq<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I>::value, "");
#endif
		static_assert(!has_plus<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_plus<hamon::ptrdiff_t, I>::value, "");
		static_assert(!has_minus<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_minus<I, I>::value, "");

		using S = decltype(tv.end());
		static_assert(!hamon::same_as<I, S>, "");
		static_assert( has_eq<S, I>::value, "");
		static_assert( has_eq<I, S>::value, "");
		static_assert( has_neq<S, I>::value, "");
		static_assert( has_neq<I, S>::value, "");
		static_assert(!has_minus<I, S>::value, "");
		static_assert(!has_minus<S, I>::value, "");
	}
	{
		auto tv = test_bidirectional_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::bidirectional_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert( has_pre_decrement<I>::value, "");
		static_assert( has_post_decrement<I>::value, "");
		static_assert(!has_plus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_minus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_subscript<I>::value, "");
		static_assert( has_eq<I>::value, "");
		static_assert( has_neq<I>::value, "");
		static_assert(!has_lt<I>::value, "");
		static_assert(!has_lteq<I>::value, "");
		static_assert(!has_gt<I>::value, "");
		static_assert(!has_gteq<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I>::value, "");
#endif
		static_assert(!has_plus<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_plus<hamon::ptrdiff_t, I>::value, "");
		static_assert(!has_minus<I, hamon::ptrdiff_t>::value, "");
		static_assert(!has_minus<I, I>::value, "");

		using S = decltype(tv.end());
		static_assert(!hamon::same_as<I, S>, "");
		static_assert( has_eq<S, I>::value, "");
		static_assert( has_eq<I, S>::value, "");
		static_assert( has_neq<S, I>::value, "");
		static_assert( has_neq<I, S>::value, "");
		static_assert(!has_minus<I, S>::value, "");
		static_assert(!has_minus<S, I>::value, "");
	}
	{
		auto tv = test_random_access_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::random_access_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()[hamon::declval<int>()]), int>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() + hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<int>() + hamon::declval<I>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert( has_pre_decrement<I>::value, "");
		static_assert( has_post_decrement<I>::value, "");
		static_assert( has_plus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_minus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_subscript<I>::value, "");
		static_assert( has_eq<I>::value, "");
		static_assert( has_neq<I>::value, "");
		static_assert( has_lt<I>::value, "");
		static_assert( has_lteq<I>::value, "");
		static_assert( has_gt<I>::value, "");
		static_assert( has_gteq<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I>::value, "");
#endif
		static_assert( has_plus<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_plus<hamon::ptrdiff_t, I>::value, "");
		static_assert( has_minus<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_minus<I, I>::value, "");

		using S = decltype(tv.end());
		static_assert(!hamon::same_as<I, S>, "");
		static_assert( has_eq<S, I>::value, "");
		static_assert( has_eq<I, S>::value, "");
		static_assert( has_neq<S, I>::value, "");
		static_assert( has_neq<I, S>::value, "");
		static_assert( has_minus<I, S>::value, "");
		static_assert( has_minus<S, I>::value, "");
	}
	{
		auto tv = test_contiguous_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::random_access_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()[hamon::declval<int>()]), int>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() + hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<int>() + hamon::declval<I>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert( has_pre_decrement<I>::value, "");
		static_assert( has_post_decrement<I>::value, "");
		static_assert( has_plus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_minus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_subscript<I>::value, "");
		static_assert( has_eq<I>::value, "");
		static_assert( has_neq<I>::value, "");
		static_assert( has_lt<I>::value, "");
		static_assert( has_lteq<I>::value, "");
		static_assert( has_gt<I>::value, "");
		static_assert( has_gteq<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I>::value, "");
#endif
		static_assert( has_plus<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_plus<hamon::ptrdiff_t, I>::value, "");
		static_assert( has_minus<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_minus<I, I>::value, "");

		using S = decltype(tv.end());
		static_assert(!hamon::same_as<I, S>, "");
		static_assert( has_eq<S, I>::value, "");
		static_assert( has_eq<I, S>::value, "");
		static_assert( has_neq<S, I>::value, "");
		static_assert( has_neq<I, S>::value, "");
		static_assert( has_minus<I, S>::value, "");
		static_assert( has_minus<S, I>::value, "");
	}
	{
		auto tv = a | hamon::views::transform(Double{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::random_access_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()[hamon::declval<int>()]), int>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() + hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<int>() + hamon::declval<I>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert( has_pre_decrement<I>::value, "");
		static_assert( has_post_decrement<I>::value, "");
		static_assert( has_plus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_minus_equal<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_subscript<I>::value, "");
		static_assert( has_eq<I>::value, "");
		static_assert( has_neq<I>::value, "");
		static_assert( has_lt<I>::value, "");
		static_assert( has_lteq<I>::value, "");
		static_assert( has_gt<I>::value, "");
		static_assert( has_gteq<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( has_compare_three_way<I>::value, "");
#endif
		static_assert( has_plus<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_plus<hamon::ptrdiff_t, I>::value, "");
		static_assert( has_minus<I, hamon::ptrdiff_t>::value, "");
		static_assert( has_minus<I, I>::value, "");

		using S = decltype(tv.end());
		static_assert( hamon::same_as<I, S>, "");
	}

	{
		auto tv = test_input_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(tv.begin());
		static_assert(!has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int&>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), void>, "");
	}
	{
		auto tv = test_forward_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::forward_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::forward_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int&>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
	}
	{
		auto tv = test_bidirectional_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::bidirectional_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::bidirectional_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int&>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
	}
	{
		auto tv = test_random_access_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::random_access_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::random_access_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int&>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()[hamon::declval<int>()]), int&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() + hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<int>() + hamon::declval<I>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>, "");
	}
	{
		auto tv = test_contiguous_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::random_access_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::random_access_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, int>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), int&>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()[hamon::declval<int>()]), int&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() + hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<int>() + hamon::declval<I>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>, "");
	}

	{
		auto tv = test_input_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(tv.begin());
		static_assert(!has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, float>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), float>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), void>, "");
	}
	{
		auto tv = test_forward_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::forward_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, float>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), float>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
	}
	{
		auto tv = test_bidirectional_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::bidirectional_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, float>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), float>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
	}
	{
		auto tv = test_random_access_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::random_access_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, float>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), float>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()[hamon::declval<int>()]), float>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() + hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<int>() + hamon::declval<I>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>, "");
	}
	{
		auto tv = test_contiguous_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(tv.begin());
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::input_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::random_access_iterator_tag>, "");
		static_assert(hamon::same_as<typename I::value_type, float>, "");
		static_assert(hamon::same_as<decltype(*hamon::declval<I>()), float>, "");
		static_assert(hamon::same_as<decltype(++hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()++), I>, "");
		static_assert(hamon::same_as<decltype(--hamon::declval<I>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()--), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>()[hamon::declval<int>()]), float>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() + hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<int>() + hamon::declval<I>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<int>()), I>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test07()
{
	int a[] = {1, 2, 3, 4, 5};
	auto tv = a | hamon::views::transform(Ref{});
	auto it = tv.begin();
	*it = 0;
	it[1] = 42;
	VERIFY(a[0] == 0);
	VERIFY(a[1] == 42);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test08()
{
	using R = test_input_approximately_sized_view<int const>;
	using TV = hamon::ranges::transform_view<R, Double>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert(!has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert(!has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert(!has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert(!has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert(!has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert(!has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert(!has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert(!has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert(!has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert(!has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int const a[] = {1, 2, 3, 4};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::transform_view tv{r, Double{}};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, Double{}};
#endif

	static_assert(!has_size<TV>::value, "");
	static_assert( has_reserve_hint<TV>::value, "");

	VERIFY(tv.reserve_hint() == 4);
	VERIFY(hamon::as_const(tv).reserve_hint() == 4);

	return true;
}

#undef VERIFY

GTEST_TEST(ViewsTest, TransformViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_input_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_forward_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_bidirectional_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_random_access_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_contiguous_view, Double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_input_view, NonConstFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_forward_view, NonConstFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_bidirectional_view, NonConstFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_random_access_view, NonConstFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_contiguous_view, NonConstFunc>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_input_common_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_forward_common_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_bidirectional_common_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_random_access_common_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_contiguous_common_view, Double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_input_borrowed_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_forward_borrowed_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_bidirectional_borrowed_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_random_access_borrowed_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_contiguous_borrowed_view, Double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_input_sized_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_forward_sized_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_bidirectional_sized_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_random_access_sized_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_contiguous_sized_view, Double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_input_approximately_sized_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_forward_approximately_sized_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_bidirectional_approximately_sized_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_random_access_approximately_sized_view, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_contiguous_approximately_sized_view, Double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorInputView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorForwardView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorBidirectionalView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorRandomAccessView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorContiguousView, Double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorInputView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorForwardView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorBidirectionalView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorRandomAccessView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorContiguousView, NoDefaultCtorFunc>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorInputView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorForwardView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorBidirectionalView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorRandomAccessView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoDefaultCtorContiguousView, ThrowDefaultCtorFunc>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorInputView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorForwardView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorBidirectionalView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorRandomAccessView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorContiguousView, Double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorInputView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorForwardView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorBidirectionalView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorRandomAccessView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorContiguousView, NoDefaultCtorFunc>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorInputView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorForwardView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorBidirectionalView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorRandomAccessView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NoThrowDefaultCtorContiguousView, ThrowDefaultCtorFunc>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorInputView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorForwardView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorBidirectionalView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorRandomAccessView, Double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorContiguousView, Double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorInputView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorForwardView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorBidirectionalView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorRandomAccessView, NoDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorContiguousView, NoDefaultCtorFunc>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorInputView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorForwardView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorBidirectionalView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorRandomAccessView, ThrowDefaultCtorFunc>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ThrowDefaultCtorContiguousView, ThrowDefaultCtorFunc>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ConstNotView, Double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test08());
}

}	// namespace transform_view_test
}	// namespace hamon_ranges_test
