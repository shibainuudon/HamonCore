/**
 *	@file	unit_test_flat_multiset_pmr.cpp
 *
 *	@brief	flat_multiset のテスト
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/is_sorted.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/deque.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/memory_resource.hpp>
#include <hamon/ranges.hpp>
#include <hamon/string.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

GTEST_TEST(FlatMultisetTest, PmrTest)
{
	{
		// flat_multiset(const Allocator& a);
		using M = hamon::flat_multiset<int, hamon::less<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::polymorphic_allocator<int> pa = &mr;
		auto m1 = M(pa);
		EXPECT_TRUE(m1.empty());
		EXPECT_TRUE(hamon::move(m1).extract().get_allocator() == pa);
		auto m2 = M(&mr);
		EXPECT_TRUE(m2.empty());
		EXPECT_TRUE(hamon::move(m2).extract().get_allocator() == pa);
	}
	{
		// flat_multiset(const key_compare& comp, const Alloc& a);
		using M = hamon::flat_multiset<int, std::function<bool(int, int)>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		vm.emplace_back(hamon::greater<int>());
		EXPECT_TRUE(vm[0] == M {});
		EXPECT_TRUE(vm[0].key_comp()(2, 1) == true);
		EXPECT_TRUE(vm[0].value_comp()(2, 1) == true);
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
	}
	{
		// flat_multiset(const container_type& key_cont, const Allocator& a);
		using M = hamon::flat_multiset<int, hamon::less<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		hamon::pmr::vector<int> ks = {1, 1, 1, 2, 2, 3, 2, 3, 3};
		EXPECT_TRUE(ks.get_allocator().resource() != &mr);
		vm.emplace_back(ks);
		EXPECT_TRUE(ks.size() == 9); // ks' value is unchanged, since it was an lvalue above
		EXPECT_TRUE((vm[0] == M {1, 1, 1, 2, 2, 2, 3, 3, 3}));
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
	}
	{
		// flat_multiset(const flat_multiset&, const allocator_type&);
		using C = TestLess<int>;
		using M = hamon::flat_multiset<int, C, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({1, 2, 3}, C(5), &mr1);
		M m = {mo, &mr2}; // also test the implicitness of this constructor

		EXPECT_TRUE(m.key_comp() == C(5));
		auto keys = hamon::move(m).extract();
		EXPECT_TRUE((keys == hamon::pmr::vector<int>{1, 2, 3}));
		EXPECT_TRUE(keys.get_allocator().resource() == &mr2);

		// mo is unchanged
		EXPECT_TRUE(mo.key_comp() == C(5));
		auto keys2 = hamon::move(mo).extract();
		EXPECT_TRUE((keys2 == hamon::pmr::vector<int>{1, 2, 3}));
		EXPECT_TRUE(keys2.get_allocator().resource() == &mr1);
	}
	{
		// flat_multiset(const flat_multiset&, const allocator_type&);
		using M = hamon::flat_multiset<int, hamon::less<>, hamon::pmr::vector<int>>;
		hamon::pmr::vector<M> vs;
		M m = {1, 2, 3};
		vs.push_back(m);
		EXPECT_TRUE(vs[0] == m);
	}
	{
		// flat_multiset& operator=(const flat_multiset& m);
		// pmr allocator is not propagated
		using M = hamon::flat_multiset<int, hamon::less<>, hamon::pmr::deque<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({1, 2, 3}, &mr1);
		M m = M({4, 5}, &mr2);
		m = mo;
		EXPECT_TRUE((m == M {1, 2, 3}));
		EXPECT_TRUE(hamon::move(m).extract().get_allocator().resource() == &mr2);

		// mo is unchanged
		EXPECT_TRUE((mo == M {1, 2, 3}));
		EXPECT_TRUE(hamon::move(mo).extract().get_allocator().resource() == &mr1);
	}
	{
		// flat_multiset(const flat_multiset& m);
		using C = TestLess<int>;
		hamon::pmr::monotonic_buffer_resource mr;
		using M = hamon::flat_multiset<int, C, hamon::pmr::vector<int>>;
		auto mo = M({1, 2, 3}, C(5), &mr);
		auto m = mo;

		EXPECT_TRUE(m.key_comp() == C(5));
		EXPECT_TRUE((m == M {1, 2, 3}));
		auto ks = hamon::move(m).extract();
		EXPECT_TRUE(ks.get_allocator().resource() == hamon::pmr::get_default_resource());

		// mo is unchanged
		EXPECT_TRUE(mo.key_comp() == C(5));
		EXPECT_TRUE((mo == M {1, 2, 3}));
		auto kso = hamon::move(mo).extract();
		EXPECT_TRUE(kso.get_allocator().resource() == &mr);
	}
	{
		// flat_multiset(initializer_list<value_type> il, const Alloc& a);
		using M = hamon::flat_multiset<int, hamon::less<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		std::initializer_list<M::value_type> il = {3, 1, 4, 1, 5};
		vm.emplace_back(il);
		EXPECT_TRUE((vm[0] == M {1, 1, 3, 4, 5}));
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
	}
	{
		// flat_multiset(initializer_list<value_type> il, const key_compare& comp, const Alloc& a);
		using C = TestLess<int>;
		using M = hamon::flat_multiset<int, C, hamon::pmr::deque<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		std::initializer_list<M::value_type> il = {3, 1, 4, 1, 5};
		vm.emplace_back(il, C(5));
		EXPECT_TRUE((vm[0] == M {1, 1, 3, 4, 5}));
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
		EXPECT_TRUE(vm[0].key_comp() == C(5));
	}
	{
		// flat_multiset(InputIterator first, InputIterator last, const Allocator& a);
		int ar[]       = {1, 1, 1, 2, 2, 3, 2, 3, 3};
		int expected[] = {1, 1, 1, 2, 2, 2, 3, 3, 3};
		{
			// cpp17 iterator
			using M = hamon::flat_multiset<int, hamon::less<int>, hamon::pmr::vector<int>>;
			hamon::pmr::monotonic_buffer_resource mr;
			hamon::pmr::vector<M> vm(&mr);
			using Iter = cpp17_input_iterator_wrapper<int>;
			vm.emplace_back(Iter{ar}, Iter{ar + 9});
			EXPECT_TRUE(hamon::ranges::equal(vm[0], expected));
			EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
		}
		{
			using M = hamon::flat_multiset<int, hamon::less<int>, hamon::pmr::vector<int>>;
			hamon::pmr::monotonic_buffer_resource mr;
			hamon::pmr::vector<M> vm(&mr);
			vm.emplace_back(&ar[0], &ar[0]);
			EXPECT_TRUE(vm[0].empty());
			EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
		}
	}
	{
		// flat_multiset(flat_multiset&&, const allocator_type&);
		int expected[] = {1, 1, 2, 3};
		using C = TestLess<int>;
		using M = hamon::flat_multiset<int, C, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({1, 3, 1, 2}, C(5), &mr1);
		M m  = {hamon::move(mo), &mr2}; // also test the implicitness of this constructor

		EXPECT_TRUE(m.key_comp() == C(5));
		EXPECT_TRUE(m.size() == 4);
		EXPECT_TRUE(hamon::ranges::equal(m, expected));
		EXPECT_TRUE(hamon::move(m).extract().get_allocator().resource() == &mr2);

		// The original flat_multiset is moved-from.
		EXPECT_TRUE(hamon::is_sorted(mo.begin(), mo.end(), mo.value_comp()));
		EXPECT_TRUE(mo.key_comp() == C(5));
		EXPECT_TRUE(hamon::move(mo).extract().get_allocator().resource() == &mr1);
	}
	{
		// flat_multiset(flat_multiset&&, const allocator_type&);
		using M = hamon::flat_multiset<int, hamon::less<>, hamon::pmr::deque<int>>;
		hamon::pmr::vector<M> vs;
		M m = {1, 3, 1, 2};
		vs.push_back(hamon::move(m));
		EXPECT_TRUE((hamon::move(vs[0]).extract() == hamon::pmr::deque<int>{1, 1, 2, 3}));
	}
	{
		// flat_multiset& operator=(flat_multiset&&);
		using M = hamon::flat_multiset<hamon::pmr::string, hamon::less<>, hamon::pmr::vector<hamon::pmr::string>>;
		hamon::pmr::monotonic_buffer_resource mr1;
		hamon::pmr::monotonic_buffer_resource mr2;
		M mo = M({"short", "very long string that definitely won't fit in the SSO buffer and therefore becomes empty on move"},
			  &mr1);
		M m = M({"don't care"}, &mr2);
		m = hamon::move(mo);
		EXPECT_TRUE(m.size() == 2);
		check_invariant(m);
		EXPECT_TRUE(m.begin()->get_allocator().resource() == &mr2);

		check_invariant(mo);
		mo.insert((const char*)"foo");
		EXPECT_TRUE(mo.begin()->get_allocator().resource() == &mr1);
	}
	{
		// flat_multiset(from_range_t, R&&, const Alloc&);
		int ar[]       = {1, 1, 1, 2, 2, 3, 2, 3, 3};
		int expected[] = {1, 1, 1, 2, 2, 2, 3, 3, 3};
		{
			// input_range
			using M    = hamon::flat_multiset<int, hamon::less<int>, hamon::pmr::vector<int>>;
			using Iter = input_iterator_wrapper<int>;
			using Sent = test_sentinel<Iter>;
			using R    = hamon::ranges::subrange<Iter, Sent>;
			hamon::pmr::monotonic_buffer_resource mr;
			hamon::pmr::vector<M> vm(&mr);
			vm.emplace_back(hamon::from_range, R(Iter{ar}, Sent{Iter{ar + 9}}));
			EXPECT_TRUE(hamon::ranges::equal(vm[0], expected));
			EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
		}
		{
			using M = hamon::flat_multiset<int, hamon::less<int>, hamon::pmr::vector<int>>;
			using R = hamon::ranges::subrange<const int*>;
			hamon::pmr::monotonic_buffer_resource mr;
			hamon::pmr::vector<M> vm(&mr);
			vm.emplace_back(hamon::from_range, R(ar, ar));
			EXPECT_TRUE(vm[0].empty());
			EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
		}
	}
	{
		// flat_multiset(sorted_equivalent_t, const container_type& key_cont, const Alloc& a);
		using M = hamon::flat_multiset<int, hamon::less<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		hamon::pmr::vector<int> ks = {1, 1, 2, 4, 10};
		vm.emplace_back(hamon::sorted_equivalent, ks);
		EXPECT_TRUE(!ks.empty()); // it was an lvalue above
		EXPECT_TRUE((vm[0] == M {1, 1, 2, 4, 10}));
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
	}
	{
		// flat_multiset(sorted_equivalent_t, const container_type& key_cont,const Alloc& a);
		using M = hamon::flat_multiset<int, hamon::less<int>, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		hamon::pmr::vector<int> ks({1, 1, 2, 4, 10}, &mr);
		vm.emplace_back(hamon::sorted_equivalent, ks);
		EXPECT_TRUE((vm[0] == M {1, 1, 2, 4, 10}));
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
	}
	{
		// flat_multiset(sorted_equivalent_t, initializer_list<value_type> il, const Alloc& a);
		// cpp_17
		using C = TestLess<int>;
		using M = hamon::flat_multiset<int, C, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		int ar[] = {1, 1, 2, 4, 5};
		using Iter = cpp17_input_iterator_wrapper<int>;
		vm.emplace_back(hamon::sorted_equivalent, Iter{ar}, Iter{ar + 5}, C(3));
		EXPECT_TRUE((vm[0] == M {1, 1, 2, 4, 5}));
		EXPECT_TRUE(vm[0].key_comp() == C(3));
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
	}
	{
		// flat_multiset(sorted_equivalent_t, initializer_list<value_type> il, const Alloc& a);
		using C = TestLess<int>;
		using M = hamon::flat_multiset<int, C, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		int ar[1] = {42};
		vm.emplace_back(hamon::sorted_equivalent, &ar[0], &ar[0], C(4));
		EXPECT_TRUE(vm[0] == M {});
		EXPECT_TRUE(vm[0].key_comp() == C(4));
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
	}
	{
		// flat_multiset(InputIterator first, InputIterator last, const Alloc& a);
		// cpp_17
		using C = TestLess<int>;
		using M = hamon::flat_multiset<int, C, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		int ar[] = {1, 1, 2, 4, 5};
		using Iter = cpp17_input_iterator_wrapper<int>;
		vm.emplace_back(hamon::sorted_equivalent, Iter{ar}, Iter{ar + 5}, C(3));
		EXPECT_TRUE((vm[0] == M {1, 1, 2, 4, 5}));
		EXPECT_TRUE(vm[0].key_comp() == C(3));
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
	}
	{
		// flat_multiset(InputIterator first, InputIterator last, const Alloc& a);
		using C = TestLess<int>;
		using M = hamon::flat_multiset<int, C, hamon::pmr::vector<int>>;
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::vector<M> vm(&mr);
		int ar[1] = {42};
		vm.emplace_back(hamon::sorted_equivalent, &ar[0], &ar[0], C(4));
		EXPECT_TRUE(vm[0] == M {});
		EXPECT_TRUE(vm[0].key_comp() == C(4));
		EXPECT_TRUE(hamon::move(vm[0]).extract().get_allocator().resource() == &mr);
	}
}

}	// namespace hamon_flat_multiset_test
