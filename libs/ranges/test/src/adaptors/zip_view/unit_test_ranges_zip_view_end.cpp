/**
 *	@file	unit_test_ranges_zip_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end() requires (!(simple-view<Views> && ...));
 *	constexpr auto end() const requires (range<const Views> && ...);
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace end_test
{

template <typename T, typename Iterator, typename Sentinel, typename ConstIterator, typename ConstSentinel>
struct TestView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	HAMON_CXX11_CONSTEXPR TestView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR TestView(T (&arr)[N]) : TestView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR TestView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR Iterator      begin()       noexcept { return Iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR ConstIterator begin() const noexcept { return ConstIterator{m_first}; }
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{m_last}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{m_last}; }
};

template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// (simple-view<Views> && ...) && (range<const Views> && ...)
	{
		// !zip_is_common<Views...> 
		{
			using V1 = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>
			>;

			using V2 = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>
			>;

			static_assert( hamon::ranges::detail::simple_view_t<V1>::value, "");
			static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
			static_assert( hamon::ranges::range_t<V1 const>::value, "");
			static_assert( hamon::ranges::range_t<V2 const>::value, "");
			//static_assert(!hamon::ranges::detail::zip_is_common<V1, V2>, "");

			using ZV = hamon::ranges::zip_view<V1, V2>;
			static_assert(has_end<ZV&>::value, "");
			static_assert(has_end<ZV const&>::value, "");

			using I  = decltype(hamon::declval<ZV&>().begin());
			using S  = decltype(hamon::declval<ZV&>().end());
			using CS = decltype(hamon::declval<ZV const&>().end());
			//static_assert( hamon::is_same<S,  ZV::sentinel<true>>::value, "");
			//static_assert( hamon::is_same<CS, ZV::sentinel<true>>::value, "");
			static_assert(!hamon::is_same<S, I>::value, "");
			static_assert( hamon::is_same<S, CS>::value, "");

			int a1[] = { 1,2,3 };
			int a2[] = { 4,5,6 };
			V1 v1(a1);
			V2 v2(a2);
			{
				ZV zv(v1, v2);
				auto sent = zv.end();
				VERIFY(sent != zv.begin());
				//VERIFY(sent != zv.cbegin());
			}
			{
				ZV const zv(v1, v2);
				auto sent = zv.end();
				VERIFY(sent != zv.begin());
				//VERIFY(sent != zv.cbegin());
			}
		}

		// zip_is_common<Views...> &&
		// (random_access_range<Views> && ...)
		{
			using V1 = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;

			using V2 = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;

			static_assert( hamon::ranges::detail::simple_view_t<V1>::value, "");
			static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
			static_assert( hamon::ranges::range_t<V1 const>::value, "");
			static_assert( hamon::ranges::range_t<V2 const>::value, "");
			//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
			static_assert( hamon::ranges::random_access_range_t<V1>::value, "");
			static_assert( hamon::ranges::random_access_range_t<V2>::value, "");

			using ZV = hamon::ranges::zip_view<V1, V2>;
			static_assert(has_end<ZV&>::value, "");
			static_assert(has_end<ZV const&>::value, "");

			using I  = decltype(hamon::declval<ZV&>().begin());
			using S  = decltype(hamon::declval<ZV&>().end());
			using CS = decltype(hamon::declval<ZV const&>().end());
			//static_assert( hamon::is_same<S,  ZV::iterator<true>>::value, "");
			//static_assert( hamon::is_same<CS, ZV::iterator<true>>::value, "");
			static_assert( hamon::is_same<S, I>::value, "");
			static_assert( hamon::is_same<S, CS>::value, "");

			int a1[] = { 1,2,3 };
			int a2[] = { 4,5,6,7 };
			V1 v1(a1);
			V2 v2(a2);
			{
				ZV zv(v1, v2);
				auto it = zv.end();
				VERIFY(it != zv.begin());
				//VERIFY(it != zv.cbegin());
				--it;
				VERIFY(hamon::adl_get<0>(*it) == 3);
				VERIFY(hamon::adl_get<1>(*it) == 6);
			}
			{
				ZV const zv(v1, v2);
				auto it = zv.end();
				VERIFY(it != zv.begin());
				//VERIFY(it != zv.cbegin());
				--it;
				VERIFY(hamon::adl_get<0>(*it) == 3);
				VERIFY(hamon::adl_get<1>(*it) == 6);
			}
		}

		// zip_is_common<Views...> &&
		// !(random_access_range<Views> && ...)
		{
			using V1 = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>
			>;

			using V2 = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;

			static_assert( hamon::ranges::detail::simple_view_t<V1>::value, "");
			static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
			static_assert( hamon::ranges::range_t<V1 const>::value, "");
			static_assert( hamon::ranges::range_t<V2 const>::value, "");
			//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
			static_assert(!hamon::ranges::random_access_range_t<V1>::value, "");
			static_assert( hamon::ranges::random_access_range_t<V2>::value, "");

			using ZV = hamon::ranges::zip_view<V1, V2>;
			static_assert(has_end<ZV&>::value, "");
			static_assert(has_end<ZV const&>::value, "");

			using I  = decltype(hamon::declval<ZV&>().begin());
			using S  = decltype(hamon::declval<ZV&>().end());
			using CS = decltype(hamon::declval<ZV const&>().end());
			//static_assert( hamon::is_same<S,  ZV::iterator<true>>::value, "");
			//static_assert( hamon::is_same<CS, ZV::iterator<true>>::value, "");
			static_assert( hamon::is_same<S, I>::value, "");
			static_assert( hamon::is_same<S, CS>::value, "");

			int a1[] = { 1,2,3 };
			int a2[] = { 4,5,6,7 };
			V1 v1(a1);
			V2 v2(a2);
			{
				ZV zv(v1, v2);
				auto sent = zv.end();
				VERIFY(sent != zv.begin());
				//VERIFY(sent != zv.cbegin());
			}
			{
				ZV const zv(v1, v2);
				auto sent = zv.end();
				VERIFY(sent != zv.begin());
				//VERIFY(sent != zv.cbegin());
			}
		}
	}

	// !(simple-view<Views> && ...) && (range<const Views> && ...)
	{
		// !zip_is_common<Views...>
		{
			// !zip_is_common<const Views...>
			{
				using V1 = TestView<int,
					forward_iterator_wrapper<int>,
					test_sentinel<forward_iterator_wrapper<int>>,
					forward_iterator_wrapper<int const>,
					test_sentinel<forward_iterator_wrapper<int const>>
				>;

				using V2 = TestView<int,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>
				>;

				static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
				static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
				static_assert( hamon::ranges::range_t<V1 const>::value, "");
				static_assert( hamon::ranges::range_t<V2 const>::value, "");
				//static_assert(!hamon::ranges::detail::zip_is_common<V1, V2>, "");
				//static_assert(!hamon::ranges::detail::zip_is_common<V1 const, V2 const>, "");

				using ZV = hamon::ranges::zip_view<V1, V2>;
				static_assert(has_end<ZV&>::value, "");
				static_assert(has_end<ZV const&>::value, "");

				using S  = decltype(hamon::declval<ZV&>().end());
				using CS = decltype(hamon::declval<ZV const&>().end());
				//static_assert( hamon::is_same<S,  ZV::sentinel<false>>::value, "");
				//static_assert( hamon::is_same<CS, ZV::sentinel<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				using I  = decltype(hamon::declval<ZV&>().begin());
				using CI = decltype(hamon::declval<ZV const&>().begin());
				static_assert(!hamon::is_same<S, I>::value, "");
				static_assert(!hamon::is_same<CS, CI>::value, "");

				int a1[] = { 1,2,3 };
				int a2[] = { 4,5,6 };
				V1 v1(a1);
				V2 v2(a2);
				{
					ZV zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
				{
					ZV const zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
			}

			// zip_is_common<const Views...> &&
			// (random_access_range<const Views> && ...)
			{
				using V1 = TestView<int,
					forward_iterator_wrapper<int>,
					test_sentinel<forward_iterator_wrapper<int>>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				using V2 = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
				static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
				static_assert( hamon::ranges::range_t<V1 const>::value, "");
				static_assert( hamon::ranges::range_t<V2 const>::value, "");
				//static_assert(!hamon::ranges::detail::zip_is_common<V1, V2>, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1 const, V2 const>, "");
				static_assert( hamon::ranges::random_access_range_t<V1 const>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2 const>::value, "");

				using ZV = hamon::ranges::zip_view<V1, V2>;
				static_assert(has_end<ZV&>::value, "");
				static_assert(has_end<ZV const&>::value, "");

				using S  = decltype(hamon::declval<ZV&>().end());
				using CS = decltype(hamon::declval<ZV const&>().end());
				//static_assert( hamon::is_same<S,  ZV::sentinel<false>>::value, "");
				//static_assert( hamon::is_same<CS, ZV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				using I  = decltype(hamon::declval<ZV&>().begin());
				using CI = decltype(hamon::declval<ZV const&>().begin());
				static_assert(!hamon::is_same<S, I>::value, "");
				static_assert( hamon::is_same<CS, CI>::value, "");

				int a1[] = { 1,2,3 };
				int a2[] = { 4,5,6 };
				V1 v1(a1);
				V2 v2(a2);
				{
					ZV zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
				{
					ZV const zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
			}

			// zip_is_common<const Views...> &&
			// !(random_access_range<const Views> && ...)
			{
				using V1 = TestView<int,
					forward_iterator_wrapper<int>,
					test_sentinel<forward_iterator_wrapper<int>>,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>
				>;

				using V2 = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
				static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
				static_assert( hamon::ranges::range_t<V1 const>::value, "");
				static_assert( hamon::ranges::range_t<V2 const>::value, "");
				//static_assert(!hamon::ranges::detail::zip_is_common<V1, V2>, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1 const, V2 const>, "");
				static_assert(!hamon::ranges::random_access_range_t<V1 const>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2 const>::value, "");

				using ZV = hamon::ranges::zip_view<V1, V2>;
				static_assert(has_end<ZV&>::value, "");
				static_assert(has_end<ZV const&>::value, "");

				using S  = decltype(hamon::declval<ZV&>().end());
				using CS = decltype(hamon::declval<ZV const&>().end());
				//static_assert( hamon::is_same<S,  ZV::sentinel<false>>::value, "");
				//static_assert( hamon::is_same<CS, ZV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				using I  = decltype(hamon::declval<ZV&>().begin());
				using CI = decltype(hamon::declval<ZV const&>().begin());
				static_assert(!hamon::is_same<S, I>::value, "");
				static_assert( hamon::is_same<CS, CI>::value, "");

				int a1[] = { 1,2,3 };
				int a2[] = { 4,5,6 };
				V1 v1(a1);
				V2 v2(a2);
				{
					ZV zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
				{
					ZV const zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
			}
		}

		// zip_is_common<Views...> &&
		// (random_access_range<Views> && ...)
		{
			// !zip_is_common<const Views...>
			{
				using V1 = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					forward_iterator_wrapper<int>,
					test_sentinel<forward_iterator_wrapper<int>>
				>;

				using V2 = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
				static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
				static_assert( hamon::ranges::range_t<V1 const>::value, "");
				static_assert( hamon::ranges::range_t<V2 const>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
				static_assert( hamon::ranges::random_access_range_t<V1>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2>::value, "");
				//static_assert(!hamon::ranges::detail::zip_is_common<V1 const, V2 const>, "");

				using ZV = hamon::ranges::zip_view<V1, V2>;
				static_assert(has_end<ZV&>::value, "");
				static_assert(has_end<ZV const&>::value, "");

				using S  = decltype(hamon::declval<ZV&>().end());
				using CS = decltype(hamon::declval<ZV const&>().end());
				//static_assert( hamon::is_same<S,  ZV::iterator<false>>::value, "");
				//static_assert( hamon::is_same<CS, ZV::sentinel<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				using I  = decltype(hamon::declval<ZV&>().begin());
				using CI = decltype(hamon::declval<ZV const&>().begin());
				static_assert( hamon::is_same<S, I>::value, "");
				static_assert(!hamon::is_same<CS, CI>::value, "");

				int a1[] = { 1,2,3 };
				int a2[] = { 4,5,6 };
				V1 v1(a1);
				V2 v2(a2);
				{
					ZV zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
				{
					ZV const zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
			}

			// zip_is_common<const Views...> &&
			// (random_access_range<const Views> && ...)
			{
				using V1 = TestView<int,
					random_access_iterator_wrapper<int>,
					test_sentinel<random_access_iterator_wrapper<int>>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				using V2 = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
				static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
				static_assert( hamon::ranges::range_t<V1 const>::value, "");
				static_assert( hamon::ranges::range_t<V2 const>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
				static_assert( hamon::ranges::random_access_range_t<V1>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1 const, V2 const>, "");
				static_assert( hamon::ranges::random_access_range_t<V1 const>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2 const>::value, "");

				using ZV = hamon::ranges::zip_view<V1, V2>;
				static_assert(has_end<ZV&>::value, "");
				static_assert(has_end<ZV const&>::value, "");

				using S  = decltype(hamon::declval<ZV&>().end());
				using CS = decltype(hamon::declval<ZV const&>().end());
				//static_assert( hamon::is_same<S,  ZV::iterator<false>>::value, "");
				//static_assert( hamon::is_same<CS, ZV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				using I  = decltype(hamon::declval<ZV&>().begin());
				using CI = decltype(hamon::declval<ZV const&>().begin());
				static_assert( hamon::is_same<S, I>::value, "");
				static_assert( hamon::is_same<CS, CI>::value, "");

				int a1[] = { 1,2,3 };
				int a2[] = { 4,5,6 };
				V1 v1(a1);
				V2 v2(a2);
				{
					ZV zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
				{
					ZV const zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
			}

			// zip_is_common<const Views...> &&
			// !(random_access_range<const Views> && ...)
			{
				using V1 = TestView<int,
					random_access_iterator_wrapper<int>,
					test_sentinel<random_access_iterator_wrapper<int>>,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>
				>;

				using V2 = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
				static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
				static_assert( hamon::ranges::range_t<V1 const>::value, "");
				static_assert( hamon::ranges::range_t<V2 const>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
				static_assert( hamon::ranges::random_access_range_t<V1>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1 const, V2 const>, "");
				static_assert(!hamon::ranges::random_access_range_t<V1 const>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2 const>::value, "");

				using ZV = hamon::ranges::zip_view<V1, V2>;
				static_assert(has_end<ZV&>::value, "");
				static_assert(has_end<ZV const&>::value, "");

				using S  = decltype(hamon::declval<ZV&>().end());
				using CS = decltype(hamon::declval<ZV const&>().end());
				//static_assert( hamon::is_same<S,  ZV::iterator<false>>::value, "");
				//static_assert( hamon::is_same<CS, ZV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				using I  = decltype(hamon::declval<ZV&>().begin());
				using CI = decltype(hamon::declval<ZV const&>().begin());
				static_assert( hamon::is_same<S, I>::value, "");
				static_assert( hamon::is_same<CS, CI>::value, "");

				int a1[] = { 1,2,3 };
				int a2[] = { 4,5,6 };
				V1 v1(a1);
				V2 v2(a2);
				{
					ZV zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
				{
					ZV const zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
			}
		}

		// zip_is_common<Views...> &&
		// !(random_access_range<Views> && ...)
		{
			// !zip_is_common<const Views...>
			{
				using V1 = TestView<int,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>,
					test_sentinel<forward_iterator_wrapper<int>>
				>;

				using V2 = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
				static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
				static_assert( hamon::ranges::range_t<V1 const>::value, "");
				static_assert( hamon::ranges::range_t<V2 const>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
				static_assert(!hamon::ranges::random_access_range_t<V1>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2>::value, "");
				//static_assert(!hamon::ranges::detail::zip_is_common<V1 const, V2 const>, "");

				using ZV = hamon::ranges::zip_view<V1, V2>;
				static_assert(has_end<ZV&>::value, "");
				static_assert(has_end<ZV const&>::value, "");

				using S  = decltype(hamon::declval<ZV&>().end());
				using CS = decltype(hamon::declval<ZV const&>().end());
				//static_assert( hamon::is_same<S,  ZV::iterator<false>>::value, "");
				//static_assert( hamon::is_same<CS, ZV::sentinel<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				using I  = decltype(hamon::declval<ZV&>().begin());
				using CI = decltype(hamon::declval<ZV const&>().begin());
				static_assert( hamon::is_same<S, I>::value, "");
				static_assert(!hamon::is_same<CS, CI>::value, "");

				int a1[] = { 1,2,3 };
				int a2[] = { 4,5,6 };
				V1 v1(a1);
				V2 v2(a2);
				{
					ZV zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
				{
					ZV const zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
			}

			// zip_is_common<const Views...> &&
			// (random_access_range<const Views> && ...)
			{
				using V1 = TestView<int,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				using V2 = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
				static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
				static_assert( hamon::ranges::range_t<V1 const>::value, "");
				static_assert( hamon::ranges::range_t<V2 const>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
				static_assert(!hamon::ranges::random_access_range_t<V1>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1 const, V2 const>, "");
				static_assert( hamon::ranges::random_access_range_t<V1 const>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2 const>::value, "");

				using ZV = hamon::ranges::zip_view<V1, V2>;
				static_assert(has_end<ZV&>::value, "");
				static_assert(has_end<ZV const&>::value, "");

				using S  = decltype(hamon::declval<ZV&>().end());
				using CS = decltype(hamon::declval<ZV const&>().end());
				//static_assert( hamon::is_same<S,  ZV::iterator<false>>::value, "");
				//static_assert( hamon::is_same<CS, ZV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				using I  = decltype(hamon::declval<ZV&>().begin());
				using CI = decltype(hamon::declval<ZV const&>().begin());
				static_assert( hamon::is_same<S, I>::value, "");
				static_assert( hamon::is_same<CS, CI>::value, "");

				int a1[] = { 1,2,3 };
				int a2[] = { 4,5,6 };
				V1 v1(a1);
				V2 v2(a2);
				{
					ZV zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
				{
					ZV const zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
			}

			// zip_is_common<const Views...> &&
			// !(random_access_range<const Views> && ...)
			{
				using V1 = TestView<int,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>
				>;

				using V2 = TestView<int,
					random_access_iterator_wrapper<int>,
					random_access_iterator_wrapper<int>,
					forward_iterator_wrapper<int>,
					forward_iterator_wrapper<int>
				>;

				static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
				static_assert(!hamon::ranges::detail::simple_view_t<V2>::value, "");
				static_assert( hamon::ranges::range_t<V1 const>::value, "");
				static_assert( hamon::ranges::range_t<V2 const>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
				static_assert(!hamon::ranges::random_access_range_t<V1>::value, "");
				static_assert( hamon::ranges::random_access_range_t<V2>::value, "");
				//static_assert( hamon::ranges::detail::zip_is_common<V1 const, V2 const>, "");
				static_assert( hamon::ranges::random_access_range_t<V1 const>::value, "");
				static_assert(!hamon::ranges::random_access_range_t<V2 const>::value, "");

				using ZV = hamon::ranges::zip_view<V1, V2>;
				static_assert(has_end<ZV&>::value, "");
				static_assert(has_end<ZV const&>::value, "");

				using S  = decltype(hamon::declval<ZV&>().end());
				using CS = decltype(hamon::declval<ZV const&>().end());
				//static_assert( hamon::is_same<S,  ZV::iterator<false>>::value, "");
				//static_assert( hamon::is_same<CS, ZV::iterator<true>>::value, "");
				static_assert(!hamon::is_same<S, CS>::value, "");

				using I  = decltype(hamon::declval<ZV&>().begin());
				using CI = decltype(hamon::declval<ZV const&>().begin());
				static_assert( hamon::is_same<S, I>::value, "");
				static_assert( hamon::is_same<CS, CI>::value, "");

				int a1[] = { 1,2,3 };
				int a2[] = { 4,5,6 };
				V1 v1(a1);
				V2 v2(a2);
				{
					ZV zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
				{
					ZV const zv(v1, v2);
					auto sent = zv.end();
					VERIFY(sent != zv.begin());
					//VERIFY(sent != zv.cbegin());
				}
			}
		}
	}

	// (simple-view<Views> && ...) && !(range<const Views> && ...)
	{
		// simple_view<V> && !range<V const> ということは、
		// range<V> も false になってしまうのでインスタンス化できない
	}

	// !(simple-view<Views> && ...) && !(range<const Views> && ...)
	{
		// !zip_is_common<Views...> 
		{
			using V1 = TestView<int,
				forward_iterator_wrapper<int>,
				test_sentinel<forward_iterator_wrapper<int>>,
				forward_iterator_wrapper<int const>,
				forward_iterator_wrapper<int>
			>;

			using V2 = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>
			>;

			static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
			static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
			static_assert(!hamon::ranges::range_t<V1 const>::value, "");
			static_assert( hamon::ranges::range_t<V2 const>::value, "");
			//static_assert(!hamon::ranges::detail::zip_is_common<V1, V2>, "");

			using ZV = hamon::ranges::zip_view<V1, V2>;
			static_assert(has_end<ZV&>::value, "");
			static_assert(!has_end<ZV const&>::value, "");

			using I  = decltype(hamon::declval<ZV&>().begin());
			using S  = decltype(hamon::declval<ZV&>().end());
			//static_assert( hamon::is_same<S, ZV::sentinel<false>>::value, "");
			static_assert(!hamon::is_same<S, I>::value, "");

			int a1[] = { 1,2,3 };
			int a2[] = { 4,5,6 };
			V1 v1(a1);
			V2 v2(a2);
			{
				ZV zv(v1, v2);
				auto sent = zv.end();
				VERIFY(sent != zv.begin());
				//VERIFY(sent != zv.cbegin());
			}
		}

		// zip_is_common<Views...> &&
		// (random_access_range<Views> && ...)
		{
			using V1 = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int const>,
				random_access_iterator_wrapper<int>
			>;

			using V2 = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;

			static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
			static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
			static_assert(!hamon::ranges::range_t<V1 const>::value, "");
			static_assert( hamon::ranges::range_t<V2 const>::value, "");
			//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
			static_assert( hamon::ranges::random_access_range_t<V1>::value, "");
			static_assert( hamon::ranges::random_access_range_t<V2>::value, "");

			using ZV = hamon::ranges::zip_view<V1, V2>;
			static_assert(has_end<ZV&>::value, "");
			static_assert(!has_end<ZV const&>::value, "");

			using I  = decltype(hamon::declval<ZV&>().begin());
			using S  = decltype(hamon::declval<ZV&>().end());
			//static_assert( hamon::is_same<S, ZV::iterator<false>>::value, "");
			static_assert( hamon::is_same<S, I>::value, "");

			int a1[] = { 1,2,3 };
			int a2[] = { 4,5,6 };
			V1 v1(a1);
			V2 v2(a2);
			{
				ZV zv(v1, v2);
				auto sent = zv.end();
				VERIFY(sent != zv.begin());
				//VERIFY(sent != zv.cbegin());
			}
		}

		// zip_is_common<Views...> &&
		// !(random_access_range<Views> && ...)
		{
			using V1 = TestView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>,
				forward_iterator_wrapper<int>
			>;

			using V2 = TestView<int,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>,
				random_access_iterator_wrapper<int>
			>;

			static_assert(!hamon::ranges::detail::simple_view_t<V1>::value, "");
			static_assert( hamon::ranges::detail::simple_view_t<V2>::value, "");
			static_assert(!hamon::ranges::range_t<V1 const>::value, "");
			static_assert( hamon::ranges::range_t<V2 const>::value, "");
			//static_assert( hamon::ranges::detail::zip_is_common<V1, V2>, "");
			static_assert(!hamon::ranges::random_access_range_t<V1>::value, "");
			static_assert( hamon::ranges::random_access_range_t<V2>::value, "");

			using ZV = hamon::ranges::zip_view<V1, V2>;
			static_assert(has_end<ZV&>::value, "");
			static_assert(!has_end<ZV const&>::value, "");

			using I  = decltype(hamon::declval<ZV&>().begin());
			using S  = decltype(hamon::declval<ZV&>().end());
			//static_assert( hamon::is_same<S, ZV::iterator<false>>::value, "");
			static_assert( hamon::is_same<S, I>::value, "");

			int a1[] = { 1,2,3 };
			int a2[] = { 4,5,6 };
			V1 v1(a1);
			V2 v2(a2);
			{
				ZV zv(v1, v2);
				auto sent = zv.end();
				VERIFY(sent != zv.begin());
				//VERIFY(sent != zv.cbegin());
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace end_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
