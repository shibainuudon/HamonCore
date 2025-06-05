/**
 *	@file	unit_test_flat_multimap_pmr.cpp
 *
 *	@brief	pmr::flat_multimap のテスト
 */

#include <hamon/flat_map/flat_multimap.hpp>
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
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

GTEST_TEST(FlatMultimapTest, PmrTest)
{
	{
		// flat_multimap(const Allocator& a);
		using M = hamon::flat_multimap<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::polymorphic_allocator<int> pa = &mr;
		auto m1 = M(pa);
		EXPECT_TRUE(m1.empty());
		EXPECT_TRUE(m1.keys().get_allocator() == pa);
		EXPECT_TRUE(m1.values().get_allocator() == pa);
		auto m2 = M(&mr);
		EXPECT_TRUE(m2.empty());
		EXPECT_TRUE(m2.keys().get_allocator() == pa);
		EXPECT_TRUE(m2.values().get_allocator() == pa);
	}
	{
		// flat_multimap(const key_compare& comp, const Alloc& a);
		using M = hamon::flat_multimap<int, int, std::function<bool(int, int)>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		vm.emplace_back(hamon::greater<int>());
		EXPECT_TRUE(vm[0] == M {});
		EXPECT_TRUE(vm[0].key_comp()(2, 1) == true);
		EXPECT_TRUE(vm[0].value_comp()({2, 0}, {1, 0}) == true);
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
	}
	{
		// flat_multimap(const key_container_type& key_cont, const mapped_container_type& mapped_cont, const Allocator& a);
		using M = hamon::flat_multimap<int, int, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		hamon::pmr::vector<int> ks = {1, 1, 1, 2, 2, 3, 2, 3, 3};
		hamon::pmr::vector<int> vs = {1, 1, 1, 2, 2, 3, 2, 3, 3};
		EXPECT_TRUE(ks.get_allocator().resource() != &mr);
		EXPECT_TRUE(vs.get_allocator().resource() != &mr);
		vm.emplace_back(ks, vs);
		EXPECT_TRUE(ks.size() == 9); // ks' value is unchanged, since it was an lvalue above
		EXPECT_TRUE(vs.size() == 9); // vs' value is unchanged, since it was an lvalue above
		EXPECT_TRUE((vm[0] == M {{1, 1}, {1, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {3, 3}, {3, 3}, {3, 3}}));
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
	}
	{
		// flat_multimap(const flat_multimap&, const allocator_type&);
		using C = TestLess<int>;
		using M = hamon::flat_multimap<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({1, 2, 1}, {2, 2, 1}, C(5), &mr1);
		M m  = {mo, &mr2}; // also test the implicitness of this constructor

		EXPECT_TRUE(m.key_comp() == C(5));
		EXPECT_TRUE((m.keys() == hamon::pmr::vector<int>{1, 1, 2}));
//		EXPECT_TRUE((m.values() == hamon::pmr::vector<int>{2, 1, 2}));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr2);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr2);

		// mo is unchanged
		EXPECT_TRUE(mo.key_comp() == C(5));
		EXPECT_TRUE((mo.keys() == hamon::pmr::vector<int>{1, 1, 2}));
//		EXPECT_TRUE((mo.values() == hamon::pmr::vector<int>{2, 1, 2}));
		EXPECT_TRUE(mo.keys().get_allocator().resource() == &mr1);
		EXPECT_TRUE(mo.values().get_allocator().resource() == &mr1);
	}
	{
		// flat_multimap(const flat_multimap&, const allocator_type&);
		using M = hamon::flat_multimap<int, int, hamon::less<>, hamon::pmr::vector<int>, hamon::pmr::deque<int>>;
		hamon::pmr::vector<M> vs;
		M m = {{1, 2}, {1, 2}, {3, 1}};
		vs.push_back(m);
		EXPECT_TRUE(vs[0] == m);
	}
	{
		// flat_multimap& operator=(const flat_multimap& m);
		// pmr allocator is not propagated
		using M = hamon::flat_multimap<int, int, hamon::less<>, hamon::pmr::deque<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({{1, 1}, {1, 2}, {3, 3}}, &mr1);
		M m  = M({{4, 4}, {4, 5}}, &mr2);
		m    = mo;
		EXPECT_TRUE((m == M {{1, 1}, {1, 2}, {3, 3}}));
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr2);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr2);

		// mo is unchanged
		EXPECT_TRUE((mo == M {{1, 1}, {1, 2}, {3, 3}}));
		EXPECT_TRUE(mo.keys().get_allocator().resource() == &mr1);
	}
	{
		// flat_multimap(const flat_multimap& m);
		using C = TestLess<int>;
		hamon::pmr::monotonic_buffer_resource mr;
		using M = hamon::flat_multimap<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		auto mo = M({{1, 1}, {1, 2}, {3, 3}}, C(5), &mr);
		auto m  = mo;

		EXPECT_TRUE(m.key_comp() == C(5));
		EXPECT_TRUE((m == M {{1, 1}, {1, 2}, {3, 3}}));
		auto c = hamon::move(m).extract();
		EXPECT_TRUE(c.keys.get_allocator().resource() == hamon::pmr::get_default_resource());
		EXPECT_TRUE(c.values.get_allocator().resource() == hamon::pmr::get_default_resource());

		// mo is unchanged
		EXPECT_TRUE(mo.key_comp() == C(5));
		EXPECT_TRUE((mo == M {{1, 1}, {1, 2}, {3, 3}}));
		auto co = hamon::move(mo).extract();
		EXPECT_TRUE(co.keys.get_allocator().resource() == &mr);
		EXPECT_TRUE(co.values.get_allocator().resource() == &mr);
	}
	{
		// flat_multimap(initializer_list<value_type> il, const Alloc& a);
		using M = hamon::flat_multimap<int, int, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		std::initializer_list<M::value_type> il = {{3, 3}, {1, 1}, {4, 4}, {1, 1}, {5, 5}};
		vm.emplace_back(il);
		EXPECT_TRUE((vm[0] == M {{1, 1}, {1, 1}, {3, 3}, {4, 4}, {5, 5}}));
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
	}
	{
		// flat_multimap(initializer_list<value_type> il, const key_compare& comp, const Alloc& a);
		using C = TestLess<int>;
		using M = hamon::flat_multimap<int, int, C, hamon::pmr::vector<int>, hamon::pmr::deque<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		std::initializer_list<M::value_type> il = {{3, 3}, {1, 1}, {4, 4}, {1, 1}, {5, 5}};
		vm.emplace_back(il, C(5));
		EXPECT_TRUE((vm[0] == M {{1, 1}, {1, 1}, {3, 3}, {4, 4}, {5, 5}}));
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].key_comp() == C(5));
	}
	{
		// flat_multimap(InputIterator first, InputIterator last, const Allocator& a);
		using P = hamon::pair<int, short>;
		P ar[] = {{1, 1}, {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {2, 7}, {3, 8}, {3, 9}};
		int expected[] = {1, 1, 1, 2, 2, 2, 3, 3, 3};
		{
			// cpp17 iterator
			using M = hamon::flat_multimap<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
			hamon::pmr::monotonic_buffer_resource mr;
			hamon::pmr::vector<M> vm(&mr);
			using Iter = cpp17_input_iterator_wrapper<P>;
			vm.emplace_back(Iter{ar}, Iter{ar + 9});
			EXPECT_TRUE(hamon::ranges::equal(vm[0].keys(), expected));
			EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
			EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
		}
		{
			using M = hamon::flat_multimap<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
			hamon::pmr::monotonic_buffer_resource mr;
			hamon::pmr::vector<M> vm(&mr);
			vm.emplace_back(&ar[0], &ar[0]);
			EXPECT_TRUE(vm[0].empty());
			EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
			EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
		}
	}
	{
		// flat_multimap(flat_multimap&&, const allocator_type&);
		hamon::pair<int, int> expected[] = {{1, 1}, {1, 1}, {2, 2}, {3, 1}};
		using C = TestLess<int>;
		using M = hamon::flat_multimap<int, int, C, hamon::pmr::vector<int>, hamon::pmr::deque<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({{1, 1}, {3, 1}, {1, 1}, {2, 2}}, C(5), &mr1);
		M m  = {hamon::move(mo), &mr2}; // also test the implicitness of this constructor

		EXPECT_TRUE(m.key_comp() == C(5));
		EXPECT_TRUE(m.size() == 4);
		EXPECT_TRUE(m.keys().get_allocator().resource() == &mr2);
		EXPECT_TRUE(m.values().get_allocator().resource() == &mr2);
		EXPECT_TRUE(hamon::ranges::equal(m, expected));

		// The original flat_multimap is moved-from.
		EXPECT_TRUE(hamon::is_sorted(mo.begin(), mo.end(), mo.value_comp()));
		EXPECT_TRUE(mo.key_comp() == C(5));
		EXPECT_TRUE(mo.keys().get_allocator().resource() == &mr1);
		EXPECT_TRUE(mo.values().get_allocator().resource() == &mr1);
	}
	{
		// flat_multimap(flat_multimap&&, const allocator_type&);
		using M = hamon::flat_multimap<int, int, hamon::less<>, hamon::pmr::deque<int>, hamon::pmr::vector<int>>;
		hamon::pmr::vector<M> vs;
		M m = {{1, 1}, {3, 1}, {1, 1}, {2, 2}};
		vs.push_back(hamon::move(m));
		EXPECT_TRUE((vs[0].keys() == hamon::pmr::deque<int>{1, 1, 2, 3}));
		EXPECT_TRUE((vs[0].values() == hamon::pmr::vector<int>{1, 1, 2, 1}));
	}
	{
		// flat_multimap& operator=(flat_multimap&&);
		using M = hamon::flat_multimap<hamon::pmr::string, int, hamon::less<>, hamon::pmr::vector<hamon::pmr::string>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({{"short", 1},
				  {"very long string that definitely won't fit in the SSO buffer and therefore becomes empty on move", 2}},
				 &mr1);
		M m  = M({{"don't care", 3}}, &mr2);
		m    = hamon::move(mo);
		EXPECT_TRUE(m.size() == 2);
		EXPECT_TRUE(hamon::is_sorted(m.begin(), m.end(), m.value_comp()));
		EXPECT_TRUE(m.begin()->first.get_allocator().resource() == &mr2);

		EXPECT_TRUE(hamon::is_sorted(mo.begin(), mo.end(), mo.value_comp()));
		mo.insert({"foo", 1});
		EXPECT_TRUE(mo.begin()->first.get_allocator().resource() == &mr1);
	}
	{
		// flat_multimap(from_range_t, R&&, const Alloc&);
		using P = hamon::pair<int, short>;
		P ar[] = {{1, 1}, {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {2, 7}, {3, 8}, {3, 9}};
		int expected[] = {1, 1, 1, 2, 2, 2, 3, 3, 3};
		{
		  // input_range
			using M    = hamon::flat_multimap<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
			using Iter = input_iterator_wrapper<P>;
			using Sent = test_sentinel<Iter>;
			using R    = hamon::ranges::subrange<Iter, Sent>;
			hamon::pmr::monotonic_buffer_resource mr;
			hamon::pmr::vector<M> vm(&mr);
			vm.emplace_back(hamon::from_range, R(Iter{ar}, Sent{Iter{ar + 9}}));
			EXPECT_TRUE(hamon::ranges::equal(vm[0].keys(), expected));
			EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
			EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
		}
		{
			using M = hamon::flat_multimap<int, short, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<short>>;
			using R = hamon::ranges::subrange<const P*>;
			hamon::pmr::monotonic_buffer_resource mr;
			hamon::pmr::vector<M> vm(&mr);
			vm.emplace_back(hamon::from_range, R(ar, ar));
			EXPECT_TRUE(vm[0].empty());
			EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
			EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
		}
	}
	{
		// flat_multimap(sorted_equivalent_t, const key_container_type& key_cont, const mapped_container_type& mapped_cont, const Alloc& a);
		using M = hamon::flat_multimap<int, int, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		hamon::pmr::vector<int> ks = {1, 1, 4, 10};
		hamon::pmr::vector<int> vs = {4, 3, 2, 1};
		vm.emplace_back(hamon::sorted_equivalent, ks, vs);
		EXPECT_TRUE(!ks.empty()); // it was an lvalue above
		EXPECT_TRUE(!vs.empty()); // it was an lvalue above
		EXPECT_TRUE((vm[0] == M {{1, 4}, {1, 3}, {4, 2}, {10, 1}}));
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
	}
	{
		// flat_multimap(sorted_equivalent_t, const key_container_type& key_cont, const mapped_container_type& mapped_cont, const Alloc& a);
		using M = hamon::flat_multimap<int, int, hamon::less<int>, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		hamon::pmr::vector<int> ks({1, 1, 4, 10}, &mr);
		hamon::pmr::vector<int> vs({4, 3, 2, 1}, &mr);
		vm.emplace_back(hamon::sorted_equivalent, ks, vs);
		EXPECT_TRUE((vm[0] == M {{1, 4}, {1, 3}, {4, 2}, {10, 1}}));
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
	}
	{
		// flat_multimap(sorted_equivalent_t, initializer_list<value_type> il, const Alloc& a);
		// cpp_17
		using C = TestLess<int>;
		using M = hamon::flat_multimap<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		using P = hamon::pair<int, int>;
		P ar[] = {{1, 1}, {1, 2}, {1, 4}, {5, 5}};
		using Iter = cpp17_input_iterator_wrapper<P>;
		vm.emplace_back(hamon::sorted_equivalent, Iter{ar}, Iter{ar + 4}, C(3));
		EXPECT_TRUE((vm[0] == M {{1, 1}, {1, 2}, {1, 4}, {5, 5}}));
		EXPECT_TRUE(vm[0].key_comp() == C(3));
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
	}
	{
		// flat_multimap(sorted_equivalent_t, initializer_list<value_type> il, const Alloc& a);
		using C = TestLess<int>;
		using M = hamon::flat_multimap<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		hamon::pair<int, int> ar[1] = {{42, 42}};
		vm.emplace_back(hamon::sorted_equivalent, &ar[0], &ar[0], C(4));
		EXPECT_TRUE(vm[0] == M {});
		EXPECT_TRUE(vm[0].key_comp() == C(4));
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
	}
	{
		// flat_multimap(InputIterator first, InputIterator last, const Alloc& a);
		// cpp_17
		using C = TestLess<int>;
		using M = hamon::flat_multimap<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		using P = hamon::pair<int, int>;
		P ar[] = {{1, 1}, {1, 2}, {1, 4}, {5, 5}};
		using Iter = cpp17_input_iterator_wrapper<P>;
		vm.emplace_back(hamon::sorted_equivalent, Iter{ar}, Iter{ar + 4}, C(3));
		EXPECT_TRUE((vm[0] == M {{1, 1}, {1, 2}, {1, 4}, {5, 5}}));
		EXPECT_TRUE(vm[0].key_comp() == C(3));
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
	}
	{
		// flat_multimap(InputIterator first, InputIterator last, const Alloc& a);
		using C = TestLess<int>;
		using M = hamon::flat_multimap<int, int, C, hamon::pmr::vector<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		hamon::pair<int, int> ar[1] = {{42, 42}};
		vm.emplace_back(hamon::sorted_equivalent, &ar[0], &ar[0], C(4));
		EXPECT_TRUE(vm[0] == M {});
		EXPECT_TRUE(vm[0].key_comp() == C(4));
		EXPECT_TRUE(vm[0].keys().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].values().get_allocator().resource() == &mr);
	}
}

}	// namespace hamon_flat_multimap_test
