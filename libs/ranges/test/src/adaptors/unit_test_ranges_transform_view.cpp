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
#include <hamon/iterator/concepts/detail/has_iterator_category.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

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
static_assert(hamon::regular_invocable_t<Double&, int&>::value, "");
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
static_assert(hamon::regular_invocable_t<NonMovable&, int&>::value, "");
//static_assert(hamon::detail::can_reference<hamon::invoke_result_t<NonMovable&, int&>>, "");

struct VoidFunc
{
	HAMON_CXX14_CONSTEXPR void operator()(int& x) const HAMON_NOEXCEPT
	{
		x *= 2;
	}
};
static_assert(hamon::regular_invocable_t<VoidFunc&, int&>::value, "");
//static_assert(!hamon::detail::can_reference<hamon::invoke_result_t<VoidFunc&, int&>>, "");

struct NonConstFunc
{
	HAMON_CXX14_CONSTEXPR int operator()(int x) HAMON_NOEXCEPT
	{
		return x * 2;
	}
};

struct Empty{};
static_assert(!hamon::regular_invocable_t<Empty&, int&>::value, "");

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

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_size
	: public hamon::false_type {};

template <typename T>
struct has_size<T, hamon::void_t<decltype(hamon::declval<T>().size())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_pre_increment
	: public hamon::false_type {};

template <typename T>
struct has_pre_increment<T, hamon::void_t<decltype(++hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_post_increment
	: public hamon::false_type {};

template <typename T>
struct has_post_increment<T, hamon::void_t<decltype(hamon::declval<T>()++)>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_pre_decrement
	: public hamon::false_type {};

template <typename T>
struct has_pre_decrement<T, hamon::void_t<decltype(--hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_post_decrement
	: public hamon::false_type {};

template <typename T>
struct has_post_decrement<T, hamon::void_t<decltype(hamon::declval<T>()--)>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_advance_forward
	: public hamon::false_type {};

template <typename T>
struct has_advance_forward<T, hamon::void_t<decltype(hamon::declval<T>() += hamon::declval<hamon::ptrdiff_t>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_advance_backward
	: public hamon::false_type {};

template <typename T>
struct has_advance_backward<T, hamon::void_t<decltype(hamon::declval<T>() -= hamon::declval<hamon::ptrdiff_t>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_index_access
	: public hamon::false_type {};

template <typename T>
struct has_index_access<T, hamon::void_t<decltype(hamon::declval<T>().operator[](hamon::declval<hamon::ptrdiff_t>()))>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_op_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_op_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_op_not_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_op_not_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_op_less
	: public hamon::false_type {};

template <typename T, typename U>
struct has_op_less<T, U, hamon::void_t<decltype(hamon::declval<T>() < hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_op_less_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_op_less_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() <= hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_op_greater
	: public hamon::false_type {};

template <typename T, typename U>
struct has_op_greater<T, U, hamon::void_t<decltype(hamon::declval<T>() > hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_op_greater_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_op_greater_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() >= hamon::declval<U>())>>
	: public hamon::true_type {};

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename U = T, typename = void>
struct has_op_three_way
	: public hamon::false_type {};

template <typename T, typename U>
struct has_op_three_way<T, U, hamon::void_t<decltype(hamon::declval<T>() <=> hamon::declval<U>())>>
	: public hamon::true_type {};
#endif

template <typename T, typename = void>
struct has_op_plus_n
	: public hamon::false_type {};

template <typename T>
struct has_op_plus_n<T, hamon::void_t<decltype(hamon::declval<T>() + hamon::declval<hamon::ptrdiff_t>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_op_n_plus
	: public hamon::false_type {};

template <typename T>
struct has_op_n_plus<T, hamon::void_t<decltype(hamon::declval<hamon::ptrdiff_t>() + hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_op_minus_n
	: public hamon::false_type {};

template <typename T>
struct has_op_minus_n<T, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<hamon::ptrdiff_t>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_op_minus
	: public hamon::false_type {};

template <typename T, typename U>
struct has_op_minus<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View, typename F>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = View<T>;
	using RV = hamon::ranges::transform_view<V, F>;

	static_assert(hamon::ranges::range_t<RV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::sized_range_t<RV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(hamon::ranges::output_range_t<RV, T>::value == false, "");
	static_assert(hamon::ranges::input_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::forward_range_t<RV>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<RV>::value == hamon::ranges::bidirectional_range_t<V>::value, "");
	static_assert(hamon::ranges::random_access_range_t<RV>::value == hamon::ranges::random_access_range_t<V>::value, "");
	static_assert(hamon::ranges::contiguous_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::common_range_t<RV>::value == hamon::ranges::common_range_t<V>::value, "");
	static_assert(hamon::ranges::viewable_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::view_t<RV>::value == true, "");
	static_assert(hamon::is_default_constructible<RV>::value ==
		(hamon::is_default_constructible<V>::value && hamon::is_default_constructible<F>::value), "");
	static_assert(hamon::is_nothrow_default_constructible<RV>::value ==
		(hamon::is_nothrow_default_constructible<V>::value && hamon::is_nothrow_default_constructible<F>::value), "");

	static_assert(has_base<RV&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV&&>::value, "");
	static_assert(has_base<RV const&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV const&&>::value == hamon::copy_constructible_t<V>::value, "");

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&&>().base()), V>::value, "");
#if !defined(HAMON_USE_STD_RANGES)
	//static_assert(noexcept(hamon::declval<RV&&>().base()) == hamon::is_nothrow_move_constructible<V>::value, "");
#endif

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::copy_constructible_t<V>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&&>().base()), V>::value, "");
#if !defined(HAMON_USE_STD_RANGES)
		//static_assert(noexcept(hamon::declval<RV&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
		//static_assert(noexcept(hamon::declval<RV const&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
		//static_assert(noexcept(hamon::declval<RV const&&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
#endif
	}
#endif

	static_assert(has_begin<RV>::value, "");
	static_assert(has_end<RV>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::ranges::range_t<V const>::value)
	{
		static_assert(has_begin<RV const>::value == hamon::regular_invocable_t<F const&, hamon::ranges::range_reference_t<V const>>::value, "");
		static_assert(has_end<RV const>::value   == hamon::regular_invocable_t<F const&, hamon::ranges::range_reference_t<V const>>::value, "");
	}
	else
	{
		static_assert(has_begin<RV const>::value == false, "");
		static_assert(has_end<RV const>::value   == false, "");
	}
#endif

	static_assert(has_size<RV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(has_size<RV const>::value == hamon::ranges::sized_range_t<V const>::value, "");

	using I = decltype(hamon::declval<RV&>().begin());
	using S = decltype(hamon::declval<RV&>().end());
	using BI = decltype(hamon::declval<V&>().begin());
	static_assert(hamon::same_as_t<I, S>::value == hamon::ranges::common_range_t<V>::value, "");
	static_assert(hamon::detail::has_iterator_category<I>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::same_as_t<typename I::value_type, T>::value, "");
	static_assert(hamon::same_as_t<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	static_assert(hamon::is_default_constructible<I>::value == hamon::is_default_constructible<BI>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<I>::value == hamon::is_nothrow_default_constructible<BI>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using R = test_random_access_view<int>;
	hamon::ranges::transform_view<R, Double> rv{};
	VERIFY(rv.empty());
	VERIFY(rv.begin() == rv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3, 4};
	using R = test_input_view<int>;
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::transform_view rv{r, Double{}};
	static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::transform_view<R, Double>>::value, "");
#else
	hamon::ranges::transform_view<R, Double> rv{r, Double{}};
#endif

	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	{
		auto it = rv.begin();
		VERIFY(it.base() == r.begin());
		VERIFY(hamon::move(it).base() == r.begin());
		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 8);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it == rv.end());
	}
	{
		auto const& crv = rv;
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
		auto const& crv = rv;
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

	using I = decltype(rv.begin());
	static_assert(!hamon::detail::has_iterator_category<I>::value, "");
	static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int const a[] = {1, 2, 3, 4};
	using R = test_random_access_common_view<int const>;
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::transform_view rv{r, Double{}};
	static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::transform_view<R, Double>>::value, "");
#else
	hamon::ranges::transform_view<R, Double> rv{r, Double{}};
#endif

	VERIFY(rv.size() == 4);
	VERIFY(hamon::as_const(rv).size() == 4);

	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	{
		auto it = rv.begin();
		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 8);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it == rv.end());

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
		auto it1 = rv.begin() + 1;
		auto it2 = 1 + rv.begin();
		auto it3 = rv.begin() + 2;

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
		auto const& crv = rv;
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

		it = rv.begin();
		sent = rv.end();
		VERIFY(it == crv.begin());
		VERIFY(sent == crv.end());
	}

	using I = decltype(rv.begin());
	static_assert(hamon::detail::has_iterator_category<I>::value, "");
	static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[] = {1, 2, 3, 4};
	using R = test_random_access_view<int>;
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::transform_view rv{r, Double{}};
	static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::transform_view<R, Double>>::value, "");
#else
	hamon::ranges::transform_view<R, Double> rv{r, Double{}};
#endif
	
	VERIFY(rv.end().base() == r.end());

	{
		auto it = rv.begin();
		VERIFY(it - rv.end() == -4);
		VERIFY(rv.end() - it == 4);
	}
	{
		auto const& crv = rv;
		auto it = crv.begin();
		auto sent = crv.end();
		it = rv.begin();
		sent = rv.end();
		VERIFY(it == crv.begin());
		VERIFY(it != sent);
	}

	{
		using I = decltype(rv.begin());
		using BI = decltype(r.begin());
		I i{};
		BI bi{};
		VERIFY(i.base() == bi);
	}
	{
		using S = decltype(rv.end());
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
	static_assert(hamon::same_as_t<decltype(r), hamon::ranges::transform_view<hamon::ranges::ref_view<int[4]>, Double>>::value, "");
	VERIFY(r[0] == 2);
	VERIFY(r[1] == 4);
	VERIFY(r[2] == 6);
	VERIFY(r[3] == 8);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_eq(r.begin() <=> r.begin()));
	VERIFY(hamon::is_neq(r.begin() <=> r.end()));
#endif

	auto r2 = hamon::views::transform(a, Double{});
	static_assert(hamon::same_as_t<decltype(r), decltype(r2)>::value, "");

	using I = decltype(r.begin());
	static_assert(hamon::detail::has_iterator_category<I>::value, "");
	static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test06()
{
	int a[] = {1, 2, 3, 4};

	{
		auto rv = test_input_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(rv.begin());
		static_assert(!hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), void>::value, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert(!has_pre_decrement<I>::value, "");
		static_assert(!has_post_decrement<I>::value, "");
		static_assert(!has_advance_forward<I>::value, "");
		static_assert(!has_advance_backward<I>::value, "");
		static_assert(!has_index_access<I>::value, "");
		static_assert( has_op_equal<I>::value, "");
		static_assert( has_op_not_equal<I>::value, "");
		static_assert(!has_op_less<I>::value, "");
		static_assert(!has_op_less_equal<I>::value, "");
		static_assert(!has_op_greater<I>::value, "");
		static_assert(!has_op_greater_equal<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_op_three_way<I>::value, "");
#endif
		static_assert(!has_op_plus_n<I>::value, "");
		static_assert(!has_op_n_plus<I>::value, "");
		static_assert(!has_op_minus_n<I>::value, "");
		static_assert(!has_op_minus<I>::value, "");

		using S = decltype(rv.end());
		static_assert(!hamon::same_as_t<I, S>::value, "");
		static_assert( has_op_equal<S, I>::value, "");
		static_assert( has_op_equal<I, S>::value, "");
		static_assert( has_op_not_equal<S, I>::value, "");
		static_assert( has_op_not_equal<I, S>::value, "");
		static_assert(!has_op_minus<I, S>::value, "");
		static_assert(!has_op_minus<S, I>::value, "");
	}
	{
		auto rv = test_forward_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert(!has_pre_decrement<I>::value, "");
		static_assert(!has_post_decrement<I>::value, "");
		static_assert(!has_advance_forward<I>::value, "");
		static_assert(!has_advance_backward<I>::value, "");
		static_assert(!has_index_access<I>::value, "");
		static_assert( has_op_equal<I>::value, "");
		static_assert( has_op_not_equal<I>::value, "");
		static_assert(!has_op_less<I>::value, "");
		static_assert(!has_op_less_equal<I>::value, "");
		static_assert(!has_op_greater<I>::value, "");
		static_assert(!has_op_greater_equal<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_op_three_way<I>::value, "");
#endif
		static_assert(!has_op_plus_n<I>::value, "");
		static_assert(!has_op_n_plus<I>::value, "");
		static_assert(!has_op_minus_n<I>::value, "");
		static_assert(!has_op_minus<I>::value, "");

		using S = decltype(rv.end());
		static_assert(!hamon::same_as_t<I, S>::value, "");
		static_assert( has_op_equal<S, I>::value, "");
		static_assert( has_op_equal<I, S>::value, "");
		static_assert( has_op_not_equal<S, I>::value, "");
		static_assert( has_op_not_equal<I, S>::value, "");
		static_assert(!has_op_minus<I, S>::value, "");
		static_assert(!has_op_minus<S, I>::value, "");
	}
	{
		auto rv = test_bidirectional_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert( has_pre_decrement<I>::value, "");
		static_assert( has_post_decrement<I>::value, "");
		static_assert(!has_advance_forward<I>::value, "");
		static_assert(!has_advance_backward<I>::value, "");
		static_assert(!has_index_access<I>::value, "");
		static_assert( has_op_equal<I>::value, "");
		static_assert( has_op_not_equal<I>::value, "");
		static_assert(!has_op_less<I>::value, "");
		static_assert(!has_op_less_equal<I>::value, "");
		static_assert(!has_op_greater<I>::value, "");
		static_assert(!has_op_greater_equal<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_op_three_way<I>::value, "");
#endif
		static_assert(!has_op_plus_n<I>::value, "");
		static_assert(!has_op_n_plus<I>::value, "");
		static_assert(!has_op_minus_n<I>::value, "");
		static_assert(!has_op_minus<I>::value, "");

		using S = decltype(rv.end());
		static_assert(!hamon::same_as_t<I, S>::value, "");
		static_assert( has_op_equal<S, I>::value, "");
		static_assert( has_op_equal<I, S>::value, "");
		static_assert( has_op_not_equal<S, I>::value, "");
		static_assert( has_op_not_equal<I, S>::value, "");
		static_assert(!has_op_minus<I, S>::value, "");
		static_assert(!has_op_minus<S, I>::value, "");
	}
	{
		auto rv = test_random_access_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()[hamon::declval<int>()]), int>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<int>() + hamon::declval<I>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>::value, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert( has_pre_decrement<I>::value, "");
		static_assert( has_post_decrement<I>::value, "");
		static_assert( has_advance_forward<I>::value, "");
		static_assert( has_advance_backward<I>::value, "");
		static_assert( has_index_access<I>::value, "");
		static_assert( has_op_equal<I>::value, "");
		static_assert( has_op_not_equal<I>::value, "");
		static_assert( has_op_less<I>::value, "");
		static_assert( has_op_less_equal<I>::value, "");
		static_assert( has_op_greater<I>::value, "");
		static_assert( has_op_greater_equal<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_op_three_way<I>::value, "");
#endif
		static_assert( has_op_plus_n<I>::value, "");
		static_assert( has_op_n_plus<I>::value, "");
		static_assert( has_op_minus_n<I>::value, "");
		static_assert( has_op_minus<I>::value, "");

		using S = decltype(rv.end());
		static_assert(!hamon::same_as_t<I, S>::value, "");
		static_assert( has_op_equal<S, I>::value, "");
		static_assert( has_op_equal<I, S>::value, "");
		static_assert( has_op_not_equal<S, I>::value, "");
		static_assert( has_op_not_equal<I, S>::value, "");
		static_assert( has_op_minus<I, S>::value, "");
		static_assert( has_op_minus<S, I>::value, "");
	}
	{
		auto rv = test_contiguous_view<int>(a) | hamon::views::transform(Double{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()[hamon::declval<int>()]), int>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<int>() + hamon::declval<I>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>::value, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert( has_pre_decrement<I>::value, "");
		static_assert( has_post_decrement<I>::value, "");
		static_assert( has_advance_forward<I>::value, "");
		static_assert( has_advance_backward<I>::value, "");
		static_assert( has_index_access<I>::value, "");
		static_assert( has_op_equal<I>::value, "");
		static_assert( has_op_not_equal<I>::value, "");
		static_assert( has_op_less<I>::value, "");
		static_assert( has_op_less_equal<I>::value, "");
		static_assert( has_op_greater<I>::value, "");
		static_assert( has_op_greater_equal<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_op_three_way<I>::value, "");
#endif
		static_assert( has_op_plus_n<I>::value, "");
		static_assert( has_op_n_plus<I>::value, "");
		static_assert( has_op_minus_n<I>::value, "");
		static_assert( has_op_minus<I>::value, "");

		using S = decltype(rv.end());
		static_assert(!hamon::same_as_t<I, S>::value, "");
		static_assert( has_op_equal<S, I>::value, "");
		static_assert( has_op_equal<I, S>::value, "");
		static_assert( has_op_not_equal<S, I>::value, "");
		static_assert( has_op_not_equal<I, S>::value, "");
		static_assert( has_op_minus<I, S>::value, "");
		static_assert( has_op_minus<S, I>::value, "");
	}
	{
		auto rv = a | hamon::views::transform(Double{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()[hamon::declval<int>()]), int>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<int>() + hamon::declval<I>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>::value, "");
		static_assert( has_pre_increment<I>::value, "");
		static_assert( has_post_increment<I>::value, "");
		static_assert( has_pre_decrement<I>::value, "");
		static_assert( has_post_decrement<I>::value, "");
		static_assert( has_advance_forward<I>::value, "");
		static_assert( has_advance_backward<I>::value, "");
		static_assert( has_index_access<I>::value, "");
		static_assert( has_op_equal<I>::value, "");
		static_assert( has_op_not_equal<I>::value, "");
		static_assert( has_op_less<I>::value, "");
		static_assert( has_op_less_equal<I>::value, "");
		static_assert( has_op_greater<I>::value, "");
		static_assert( has_op_greater_equal<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( has_op_three_way<I>::value, "");
#endif
		static_assert( has_op_plus_n<I>::value, "");
		static_assert( has_op_n_plus<I>::value, "");
		static_assert( has_op_minus_n<I>::value, "");
		static_assert( has_op_minus<I>::value, "");

		using S = decltype(rv.end());
		static_assert( hamon::same_as_t<I, S>::value, "");
	}

	{
		auto rv = test_input_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(rv.begin());
		static_assert(!hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int&>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), void>::value, "");
	}
	{
		auto rv = test_forward_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int&>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
	}
	{
		auto rv = test_bidirectional_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int&>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
	}
	{
		auto rv = test_random_access_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int&>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()[hamon::declval<int>()]), int&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<int>() + hamon::declval<I>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>::value, "");
	}
	{
		auto rv = test_contiguous_view<int>(a) | hamon::views::transform(Ref{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, int>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), int&>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()[hamon::declval<int>()]), int&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<int>() + hamon::declval<I>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>::value, "");
	}

	{
		auto rv = test_input_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(rv.begin());
		static_assert(!hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, float>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), float>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), void>::value, "");
	}
	{
		auto rv = test_forward_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, float>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), float>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
	}
	{
		auto rv = test_bidirectional_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, float>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), float>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
	}
	{
		auto rv = test_random_access_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, float>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), float>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()[hamon::declval<int>()]), float>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<int>() + hamon::declval<I>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>::value, "");
	}
	{
		auto rv = test_contiguous_view<int>(a) | hamon::views::transform(ToFloat{});
		using I = decltype(rv.begin());
		static_assert(hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::same_as_t<typename I::value_type, float>::value, "");
		static_assert(hamon::same_as_t<decltype(*hamon::declval<I>()), float>::value, "");
		static_assert(hamon::same_as_t<decltype(++hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()++), I>::value, "");
		static_assert(hamon::same_as_t<decltype(--hamon::declval<I>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()--), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() += hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() -= hamon::declval<int>()), I&>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>()[hamon::declval<int>()]), float>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<int>() + hamon::declval<I>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<I>() - hamon::declval<I>()), hamon::ptrdiff_t>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test07()
{
	int a[] = {1, 2, 3, 4, 5};
	auto rv = a | hamon::views::transform(Ref{});
	auto it = rv.begin();
	*it = 0;
	it[1] = 42;
	VERIFY(a[0] == 0);
	VERIFY(a[1] == 42);
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
}

}	// namespace transform_view_test
}	// namespace hamon_ranges_test
