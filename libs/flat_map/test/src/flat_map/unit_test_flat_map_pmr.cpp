/**
 *	@file	unit_test_flat_map_pmr.cpp
 *
 *	@brief	pmr::flat_map のテスト
 */

#include <hamon/flat_map.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/memory_resource.hpp>
#include <hamon/utility.hpp>
#include <hamon/pair.hpp>
#include <hamon/ranges.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

GTEST_TEST(FlatMapTest, PmrTest)
{
	{
		// flat_map(const Allocator& a);
		using M = hamon::flat_map<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::polymorphic_allocator<int> pa = &mr;
		auto m1                                 = M(pa);
		EXPECT_TRUE(m1.empty());
		EXPECT_TRUE(m1.keys().get_allocator() == pa);
		EXPECT_TRUE(m1.values().get_allocator() == pa);
		auto m2 = M(&mr);
		EXPECT_TRUE(m2.empty());
		EXPECT_TRUE(m2.keys().get_allocator() == pa);
		EXPECT_TRUE(m2.values().get_allocator() == pa);
	}
	{
		// flat_map(const key_compare& comp, const Alloc& a);
		using M = hamon::flat_map<int, int, std::function<bool(int, int)>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		M m(hamon::greater<int>(), &mr);
		EXPECT_TRUE(m.key_comp()(2, 1) == true);
		EXPECT_TRUE(m.value_comp()({2, 0}, {1, 0}) == true);
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
	}
	{
		// flat_map(const key_container_type& key_cont, const mapped_container_type& mapped_cont,
		//          const Allocator& a);
		using M = hamon::flat_map<int, int, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<int> ks = {1, 1, 1, 2, 2, 3, 2, 3, 3};
		hamon::pmr::vector<int> vs = {1, 1, 1, 2, 2, 3, 2, 3, 3};
		EXPECT_TRUE(ks.get_allocator().resource() != &mr);
		EXPECT_TRUE(vs.get_allocator().resource() != &mr);
		M m(ks, vs, &mr);
		EXPECT_TRUE(ks.size() == 9); // ks' value is unchanged, since it was an lvalue above
		EXPECT_TRUE(vs.size() == 9); // vs' value is unchanged, since it was an lvalue above
		EXPECT_TRUE((m == M {{1, 1}, {2, 2}, {3, 3}}));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
	}
	{
		// flat_map(const flat_map&, const allocator_type&);
		using C = TestLess<int>;
		using M = hamon::flat_map<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({1, 2, 3}, {2, 2, 1}, C(5), &mr1);
		M m  = {mo, &mr2}; // also test the implicitness of this constructor

		EXPECT_TRUE(m.key_comp() == C(5));
		EXPECT_TRUE((m.keys() == hamon::pmr::vector<int>{1, 2, 3}));
		EXPECT_TRUE((m.values() == hamon::pmr::vector<int>{2, 2, 1}));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr2);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr2);

		// mo is unchanged
		EXPECT_TRUE(mo.key_comp() == C(5));
		EXPECT_TRUE((mo.keys() == hamon::pmr::vector<int>{1, 2, 3}));
		EXPECT_TRUE((mo.values() == hamon::pmr::vector<int>{2, 2, 1}));
		EXPECT_TRUE(mo.keys().get_allocator().resource() == &mr1);
		EXPECT_TRUE(mo.values().get_allocator().resource() == &mr1);
	}
	{
		// flat_map(const flat_map&, const allocator_type&);
		using M = hamon::flat_map<int, int, hamon::less<>, hamon::pmr::vector<int>, hamon::pmr::deque<int>>;
		hamon::pmr::vector<M> vs;
		M m = {{1, 2}, {2, 2}, {3, 1}};
		vs.push_back(m);
		EXPECT_TRUE(vs[0] == m);
	}
	{
		// flat_map& operator=(const flat_map& m);
		// pmr allocator is not propagated
		using M = hamon::flat_map<int, int, hamon::less<>, hamon::pmr::deque<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({{1, 1}, {2, 2}, {3, 3}}, &mr1);
		M m  = M({{4, 4}, {5, 5}}, &mr2);
		m    = mo;
		EXPECT_TRUE((m == M {{1, 1}, {2, 2}, {3, 3}}));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr2);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr2);

		// mo is unchanged
		EXPECT_TRUE((mo == M {{1, 1}, {2, 2}, {3, 3}}));
		EXPECT_TRUE(mo.keys().get_allocator().resource() == &mr1);
	}
	{
		// flat_map(const flat_map& m);
		using C = TestLess<int>;
		hamon::pmr::monotonic_buffer_resource mr;
		using M = hamon::flat_map<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		auto mo = M({{1, 1}, {2, 2}, {3, 3}}, C(5), &mr);
		auto m  = mo;

		EXPECT_TRUE(m.key_comp() == C(5));
		EXPECT_TRUE((m == M {{1, 1}, {2, 2}, {3, 3}}));
		auto [ks, vs] = hamon::move(m).extract();
		EXPECT_TRUE(ks.get_allocator().resource() == hamon::pmr::get_default_resource());
		EXPECT_TRUE(vs.get_allocator().resource() == hamon::pmr::get_default_resource());

		// mo is unchanged
		EXPECT_TRUE(mo.key_comp() == C(5));
		EXPECT_TRUE((mo == M {{1, 1}, {2, 2}, {3, 3}}));
		auto [kso, vso] = hamon::move(mo).extract();
		EXPECT_TRUE(kso.get_allocator().resource() == &mr);
		EXPECT_TRUE(vso.get_allocator().resource() == &mr);
	}
	{
		//  flat_map(initializer_list<value_type> il, const Alloc& a);
		using M = hamon::flat_map<int, int, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		std::initializer_list<M::value_type> il = {{3, 3}, {1, 1}, {4, 4}, {1, 1}, {5, 5}};
		M m(il, &mr);
		EXPECT_TRUE((m == M {{1, 1}, {3, 3}, {4, 4}, {5, 5}}));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
	}
	{
		//  flat_map(initializer_list<value_type> il, const key_compare& comp, const Alloc& a);
		using C = TestLess<int>;
		using M = hamon::flat_map<int, int, C, hamon::pmr::vector<int>, hamon::pmr::deque<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		std::initializer_list<M::value_type> il = {{3, 3}, {1, 1}, {4, 4}, {1, 1}, {5, 5}};
		M m(il, C(5), &mr);
		EXPECT_TRUE((m == M {{1, 1}, {3, 3}, {4, 4}, {5, 5}}));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.key_comp() == C(5));
	}
	{
		// flat_map(InputIterator first, InputIterator last, const Allocator& a);
		using P      = hamon::pair<int, short>;
		P ar[]       = {{1, 1}, {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {2, 7}, {3, 8}, {3, 9}};
		P expected[] = {{1, 1}, {2, 4}, {3, 6}};
		{
			//  cpp17 iterator
			using M = hamon::flat_map<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
			hamon::pmr::monotonic_buffer_resource mr;
			M m(cpp17_input_iterator_wrapper<P>(ar), cpp17_input_iterator_wrapper<P>(ar + 9), &mr);
			EXPECT_TRUE(hamon::ranges::equal(m.keys(), expected | hamon::views::elements<0>));
			EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
			EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
		}
		{
			using M = hamon::flat_map<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
			hamon::pmr::monotonic_buffer_resource mr;
			M m(ar, ar, &mr);
			EXPECT_TRUE(m.empty());
			EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
			EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
		}
	}
	{
		// flat_map(flat_map&&, const allocator_type&);
		hamon::pair<int, int> expected[] = {{1, 1}, {2, 2}, {3, 1}};
		using C                        = TestLess<int>;
		using M                        = hamon::flat_map<int, int, C, hamon::pmr::vector<int>, hamon::pmr::deque<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({{1, 1}, {3, 1}, {1, 1}, {2, 2}}, C(5), &mr1);
		M m  = {hamon::move(mo), &mr2}; // also test the implicitness of this constructor

		EXPECT_TRUE(m.key_comp() == C(5));
		EXPECT_TRUE(m.size() == 3);
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr2);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr2);
		EXPECT_TRUE(hamon::equal(m.begin(), m.end(), expected, expected + 3));

		// The original flat_map is moved-from.
		EXPECT_TRUE(hamon::is_sorted(mo.begin(), mo.end(), mo.value_comp()));
		EXPECT_TRUE(mo.key_comp() == C(5));
		EXPECT_TRUE(mo.keys().get_allocator().resource() == &mr1);
		EXPECT_TRUE(mo.values().get_allocator().resource() == &mr1);
	}
	{
		// flat_map(flat_map&&, const allocator_type&);
		using M = hamon::flat_map<int, int, hamon::less<>, hamon::pmr::deque<int>, hamon::pmr::vector<int>>;
		hamon::pmr::vector<M> vs;
		M m = {{1, 1}, {3, 1}, {1, 1}, {2, 2}};
		vs.push_back(hamon::move(m));
		EXPECT_TRUE((vs[0].keys() == hamon::pmr::deque<int>{1, 2, 3}));
		EXPECT_TRUE((vs[0].values() == hamon::pmr::vector<int>{1, 2, 1}));
	}
	{
		//// flat_map& operator=(flat_map&&);
		//using M =
		//	hamon::flat_map<hamon::pmr::string, int, hamon::less<>, hamon::pmr::vector<hamon::pmr::string>, hamon::pmr::vector<int>>;
		//hamon::pmr::monotonic_buffer_resource mr1;
		//hamon::pmr::monotonic_buffer_resource mr2;
		//M mo = M({{"short", 1},
		//		  {"very long string that definitely won't fit in the SSO buffer and therefore becomes empty on move", 2}},
		//		 &mr1);
		//M m  = M({{"don't care", 3}}, &mr2);
		//m    = hamon::move(mo);
		//EXPECT_TRUE(m.size() == 2);
		//EXPECT_TRUE(hamon::is_sorted(m.begin(), m.end(), m.value_comp()));
		//EXPECT_TRUE(m.begin()->first.get_allocator().resource() == &mr2);

		//EXPECT_TRUE(hamon::is_sorted(mo.begin(), mo.end(), mo.value_comp()));
		//mo.insert({"foo", 1});
		//EXPECT_TRUE(mo.begin()->first.get_allocator().resource() == &mr1);
	}
	{
		//  flat_map(from_range_t, R&&, const Alloc&);
		using P      = hamon::pair<int, short>;
		P ar[]       = {{1, 1}, {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {2, 7}, {3, 8}, {3, 9}};
		P expected[] = {{1, 1}, {2, 4}, {3, 6}};
		{
		  // input_range
			using M    = hamon::flat_map<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
			using Iter = input_iterator_wrapper<P>;
			using Sent = test_sentinel<Iter>;
			using R    = hamon::ranges::subrange<Iter, Sent>;
			hamon::pmr::monotonic_buffer_resource mr;
			M m(hamon::from_range, R(Iter(ar), Sent(Iter(ar + 9))), &mr);
			EXPECT_TRUE(hamon::ranges::equal(m.keys(), expected | hamon::views::elements<0>));
			EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
			EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
		}
		{
			using M = hamon::flat_map<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
			using R = hamon::ranges::subrange<const P*>;
			hamon::pmr::monotonic_buffer_resource mr;
			M m(hamon::from_range, R(ar, ar), &mr);
			EXPECT_TRUE(m.empty());
			EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
			EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
		}
	}
	{
		// flat_map(sorted_unique_t, const key_container_type& key_cont,
		//          const mapped_container_type& mapped_cont, const Alloc& a);
		using M = hamon::flat_map<int, int, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<int> ks = {1, 2, 4, 10};
		hamon::pmr::vector<int> vs = {4, 3, 2, 1};
		M m(hamon::sorted_unique, ks, vs, &mr);
		EXPECT_TRUE(!ks.empty()); // it was an lvalue above
		EXPECT_TRUE(!vs.empty()); // it was an lvalue above
		EXPECT_TRUE((m == M {{1, 4}, {2, 3}, {4, 2}, {10, 1}}));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
	}
	{
		// flat_map(sorted_unique_t, const key_container_type& key_cont,
		//          const mapped_container_type& mapped_cont, const Alloc& a);
		using M = hamon::flat_map<int, int, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<int> ks({1, 2, 4, 10}, &mr);
		hamon::pmr::vector<int> vs({4, 3, 2, 1}, &mr);
		M m(hamon::sorted_unique, ks, vs, &mr);
		EXPECT_TRUE((m == M {{1, 4}, {2, 3}, {4, 2}, {10, 1}}));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
	}
	{
		// flat_map(sorted_unique_t, initializer_list<value_type> il, const Alloc& a);
		// cpp_17
		using C = TestLess<int>;
		using M = hamon::flat_map<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		using P = hamon::pair<int, int>;
		P ar[]  = {{1, 1}, {2, 2}, {4, 4}, {5, 5}};
		M m(hamon::sorted_unique, cpp17_input_iterator_wrapper<P>(ar), cpp17_input_iterator_wrapper<P>(ar + 4), C(3), &mr);
		EXPECT_TRUE((m == M {{1, 1}, {2, 2}, {4, 4}, {5, 5}}));
		EXPECT_TRUE(m.key_comp() == C(3));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
	}
	{
		// flat_map(sorted_unique_t, initializer_list<value_type> il, const Alloc& a);
		using C = TestLess<int>;
		using M = hamon::flat_map<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pair<int, int> ar[1] = {{42, 42}};
		M m(hamon::sorted_unique, ar, ar, C(4), &mr);
		EXPECT_TRUE(m == M {});
		EXPECT_TRUE(m.key_comp() == C(4));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
	}
	{
		// flat_map(InputIterator first, InputIterator last, const Alloc& a);
		// cpp_17
		using C = TestLess<int>;
		using M = hamon::flat_map<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		using P = hamon::pair<int, int>;
		P ar[]  = {{1, 1}, {2, 2}, {4, 4}, {5, 5}};
		M m(hamon::sorted_unique, cpp17_input_iterator_wrapper<P>(ar), cpp17_input_iterator_wrapper<P>(ar + 4), C(3), &mr);
		EXPECT_TRUE((m == M {{1, 1}, {2, 2}, {4, 4}, {5, 5}}));
		EXPECT_TRUE(m.key_comp() == C(3));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
	}
	{
		// flat_map(InputIterator first, InputIterator last, const Alloc& a);
		using C = TestLess<int>;
		using M = hamon::flat_map<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pair<int, int> ar[1] = {{42, 42}};
		M m(hamon::sorted_unique, ar, ar, C(4), &mr);
		EXPECT_TRUE(m == M {});
		EXPECT_TRUE(m.key_comp() == C(4));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr);
	}
}

}	// namespace hamon_flat_map_test
