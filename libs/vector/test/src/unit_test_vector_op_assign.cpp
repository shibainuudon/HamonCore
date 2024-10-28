/**
 *	@file	unit_test_vector_op_assign.cpp
 *
 *	@brief	代入演算子のテスト
 *
 *	constexpr vector& operator=(const vector& x);
 *  constexpr vector& operator=(vector&& x)
 *    noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
 *             allocator_traits<Allocator>::is_always_equal::value);
 *  constexpr vector& operator=(initializer_list<T>);
 */

#include <hamon/vector.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/cstddef.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace op_assign_test
{

template <typename T>
struct MyAllocator1
{
	using value_type = T;
	using propagate_on_container_copy_assignment = hamon::true_type;
	using propagate_on_container_move_assignment = hamon::false_type;
	using is_always_equal = hamon::false_type;

	int id;

	MyAllocator1() : id(13) {}

	MyAllocator1(int i) : id(i) {}

	template <typename U>
	MyAllocator1(MyAllocator1<U> const& a) : id(a.id) {}

	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	bool operator==(MyAllocator1 const& rhs) const
	{
		return id == rhs.id;
	}

	bool operator!=(MyAllocator1 const& rhs) const
	{
		return id != rhs.id;
	}
};

template <typename T>
struct MyAllocator2
{
	using value_type = T;
	using propagate_on_container_copy_assignment = hamon::false_type;
	using propagate_on_container_move_assignment = hamon::true_type;
	using is_always_equal = hamon::false_type;

	int id;

	MyAllocator2() : id(13) {}

	MyAllocator2(int i) : id(i) {}

	template <typename U>
	MyAllocator2(MyAllocator2<U> const& a) : id(a.id) {}

	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	bool operator==(MyAllocator2 const& rhs) const
	{
		return id == rhs.id;
	}

	bool operator!=(MyAllocator2 const& rhs) const
	{
		return id != rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Vector = hamon::vector<T>;

	{
		Vector v1;
		VERIFY(v1.empty());

		{
			Vector const v2{1,2,3};
			auto& r = (v1 = v2);
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
			VERIFY(v1.size() == 3);
			VERIFY(v2.size() == 3);
			{
				auto it = v1.begin();
				VERIFY(*it++ == 1);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 3);
				VERIFY(it == v1.end());
			}
			{
				auto it = v1.rbegin();
				VERIFY(*it++ == 3);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 1);
				VERIFY(it == v1.rend());
			}
		}
		{
			auto& r = (v1 = v1);
			VERIFY(&r == &v1);
			VERIFY(v1.size() == 3);
			{
				auto it = v1.begin();
				VERIFY(*it++ == 1);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 3);
				VERIFY(it == v1.end());
			}
			{
				auto it = v1.rbegin();
				VERIFY(*it++ == 3);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 1);
				VERIFY(it == v1.rend());
			}
		}
		{
			Vector const v2{1,2,3,4,5};
			auto& r = (v1 = v2);
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
			VERIFY(v1.size() == 5);
			VERIFY(v2.size() == 5);
			{
				auto it = v1.begin();
				VERIFY(*it++ == 1);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 3);
				VERIFY(*it++ == 4);
				VERIFY(*it++ == 5);
				VERIFY(it == v1.end());
			}
			{
				auto it = v1.rbegin();
				VERIFY(*it++ == 5);
				VERIFY(*it++ == 4);
				VERIFY(*it++ == 3);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 1);
				VERIFY(it == v1.rend());
			}
		}
	}
	{
		Vector v1;
		VERIFY(v1.empty());

		{
			Vector v2{1,2,3};
			auto& r = (v1 = hamon::move(v2));
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
			VERIFY(v1.size() == 3);
			{
				auto it = v1.begin();
				VERIFY(*it++ == 1);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 3);
				VERIFY(it == v1.end());
			}
			{
				auto it = v1.rbegin();
				VERIFY(*it++ == 3);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 1);
				VERIFY(it == v1.rend());
			}
		}
		//{
		//	auto& r = (v1 = hamon::move(v1));
		//	VERIFY(&r == &v1);

		//	auto it = v1.begin();
		//	VERIFY(*it++ == 1);
		//	VERIFY(*it++ == 2);
		//	VERIFY(*it++ == 3);
		//	VERIFY(it == v1.end());
		//}
		{
			Vector v2{4};
			auto& r = (v1 = hamon::move(v2));
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
			VERIFY(v1.size() == 1);
			{
				auto it = v1.begin();
				VERIFY(*it++ == 4);
				VERIFY(it == v1.end());
			}
			{
				auto it = v1.rbegin();
				VERIFY(*it++ == 4);
				VERIFY(it == v1.rend());
			}
		}
	}

	{
		Vector v1;
		VERIFY(v1.empty());

		{
			auto& r = (v1 = {1,2,3});
			VERIFY(&r == &v1);
			VERIFY(v1.size() == 3);
			{
				auto it = v1.begin();
				VERIFY(*it++ == 1);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 3);
				VERIFY(it == v1.end());
			}
			{
				auto it = v1.rbegin();
				VERIFY(*it++ == 3);
				VERIFY(*it++ == 2);
				VERIFY(*it++ == 1);
				VERIFY(it == v1.rend());
			}
		}
		{
			auto& r = (v1 = {4,5});
			VERIFY(&r == &v1);
			VERIFY(v1.size() == 2);
			{
				auto it = v1.begin();
				VERIFY(*it++ == 4);
				VERIFY(*it++ == 5);
				VERIFY(it == v1.end());
			}
			{
				auto it = v1.rbegin();
				VERIFY(*it++ == 5);
				VERIFY(*it++ == 4);
				VERIFY(it == v1.rend());
			}
		}
	}

	return true;
}

HAMON_WARNING_POP()

template <typename T>
bool test2()
{
	using Allocator = MyAllocator1<T>;
	using Vector = hamon::vector<T, Allocator>;

	{
		Vector v1{Allocator{10}};
		VERIFY(v1.empty());

		Vector const v2{{1,2,3}, Allocator{20}};
		v1 = v2;

		// コピー代入のときはアロケータを伝播する
		VERIFY(v1.get_allocator().id == 20);

		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 3);
		VERIFY(it == v1.end());

		Vector v3{{4,5,6,7,8,9}, Allocator{30}};
		v1 = hamon::move(v3);

		// ムーブ代入のときはアロケータを伝播しない
		VERIFY(v1.get_allocator().id == 20);

		it = v1.begin();
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 7);
		VERIFY(*it++ == 8);
		VERIFY(*it++ == 9);
		VERIFY(it == v1.end());
	}
	return true;
}

template <typename T>
bool test3()
{
	using Allocator = MyAllocator2<T>;
	using Vector = hamon::vector<T, Allocator>;

	{
		Vector v1{Allocator{10}};
		VERIFY(v1.empty());

		Vector const v2{{1,2,3}, Allocator{20}};
		v1 = v2;

		// コピー代入のときはアロケータを伝播しない
		VERIFY(v1.get_allocator().id == 10);

		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 3);
		VERIFY(it == v1.end());

		Vector v3{{4,5,6,7,8,9}, Allocator{30}};
		v1 = hamon::move(v3);

		// ムーブ代入のときはアロケータを伝播する
		VERIFY(v1.get_allocator().id == 30);

		it = v1.begin();
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 7);
		VERIFY(*it++ == 8);
		VERIFY(*it++ == 9);
		VERIFY(it == v1.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, OpAssignTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());

	EXPECT_TRUE(test3<int>());
	EXPECT_TRUE(test3<char>());
	EXPECT_TRUE(test3<float>());
}

}	// namespace op_assign_test

}	// namespace hamon_vector_test
