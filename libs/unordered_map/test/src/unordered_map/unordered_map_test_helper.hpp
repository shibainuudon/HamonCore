/**
 *	@file	unordered_map_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_UNORDERED_MAP_TEST_HELPER_HPP
#define HAMON_UNORDERED_MAP_TEST_HELPER_HPP

#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/functional/ranges/hash.hpp>
#include <hamon/type_traits/remove_const.hpp>
#include <hamon/utility/adl_swap.hpp>

namespace hamon_unordered_map_test
{

template <typename T = void>
struct NoThrowHash
{
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(T v) const HAMON_NOEXCEPT
	{
		return hamon::hash<T>{}(v);
	}
};

template <>
struct NoThrowHash<void>
{
	using is_transparent = void;

	template <typename T>
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(T v) const HAMON_NOEXCEPT
	{
		return hamon::hash<T>{}(v);
	}
};

template <typename T = void>
struct ThrowHash
{
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(T v) const
	{
		return hamon::hash<T>{}(v);
	}
};

template <>
struct ThrowHash<void>
{
	using is_transparent = void;

	template <typename T>
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(T v) const
	{
		return hamon::hash<T>{}(v);
	}
};

template <typename T = void>
struct NoThrowEqualTo
{
	HAMON_CXX11_CONSTEXPR bool
	operator()(T const& lhs, T const& rhs) const HAMON_NOEXCEPT
	{
		return lhs == rhs;
	}
};

template <>
struct NoThrowEqualTo<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CXX11_CONSTEXPR bool
	operator()(T const& lhs, U const& rhs) const HAMON_NOEXCEPT
	{
		return lhs == rhs;
	}
};

template <typename T = void>
struct ThrowEqualTo
{
	HAMON_CXX11_CONSTEXPR bool
	operator()(T const& lhs, T const& rhs) const
	{
		return lhs == rhs;
	}
};

template <>
struct ThrowEqualTo<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CXX11_CONSTEXPR bool
	operator()(T const& lhs, U const& rhs) const
	{
		return lhs == rhs;
	}
};

using TransparentHash =	hamon::remove_const_t<decltype(hamon::ranges::hash)>;

struct TransparentKey
{
	int value;

	explicit HAMON_CXX11_CONSTEXPR
	TransparentKey(int v) HAMON_NOEXCEPT : value(v) {}

	friend HAMON_CXX11_CONSTEXPR bool
	operator==(TransparentKey const& lhs, TransparentKey const& rhs) HAMON_NOEXCEPT
	{
		return lhs.value == rhs.value;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator==(TransparentKey const& lhs, int rhs) HAMON_NOEXCEPT
	{
		return lhs.value == rhs;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator==(int lhs, TransparentKey const& rhs) HAMON_NOEXCEPT
	{
		return lhs == rhs.value;
	}

	HAMON_CXX11_CONSTEXPR hamon::size_t
	hash() const HAMON_NOEXCEPT { return hamon::hash<int>{}(value); }
};

// is_always_equal == true_type なアロケータ
template <typename T>
struct TestAllocator1
{
	using value_type = T;

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator1(int) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator1(TestAllocator1<U> const&) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator1 const&) const
	{
		return true;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator1 const&) const
	{
		return false;
	}
};

// is_always_equal == false_type なアロケータ
template <typename T>
struct TestAllocator2
{
	using value_type = T;
	using is_always_equal = std::false_type;
	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;

	int id;

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator2(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator2(TestAllocator2<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator2 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator2 const& rhs) const
	{
		return id != rhs.id;
	}
};

// is_always_equal == false_type かつ、
// select_on_container_copy_construction で伝播しないアロケータ
template <typename T>
struct TestAllocator3
{
	using value_type = T;
	using is_always_equal = std::false_type;

	int id;

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator3(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator3(TestAllocator3<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator3 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator3 const& rhs) const
	{
		return id != rhs.id;
	}

	HAMON_CXX11_CONSTEXPR TestAllocator3
	select_on_container_copy_construction() const noexcept
	{
		// don't propagate on copy
		return TestAllocator3{0};
	}
};

// is_always_equal == false_type
// propagate_on_container_copy_assignment == true_type
// propagate_on_container_move_assignment == false_type なアロケータ
template <typename T>
struct TestAllocator4
{
	using value_type = T;
	using is_always_equal = std::false_type;
	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::false_type;

	int id;

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator4(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator4(TestAllocator4<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator4 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator4 const& rhs) const
	{
		return id != rhs.id;
	}
};

// is_always_equal == false_type
// propagate_on_container_copy_assignment == false_type
// propagate_on_container_move_assignment == true_type なアロケータ
template <typename T>
struct TestAllocator5
{
	using value_type = T;
	using is_always_equal = std::false_type;
	using propagate_on_container_copy_assignment = std::false_type;
	using propagate_on_container_move_assignment = std::true_type;

	int id;

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator5(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator5(TestAllocator5<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator5 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator5 const& rhs) const
	{
		return id != rhs.id;
	}
};

// is_always_equal == false_type
// propagate_on_container_swap == false_type なアロケータ
template <typename T>
struct TestAllocator6
{
	using value_type = T;
	using is_always_equal = std::false_type;
	using propagate_on_container_swap = std::false_type;

	int id;

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator6(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator6(TestAllocator6<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator6 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator6 const& rhs) const
	{
		return id != rhs.id;
	}
};

template <typename T>
struct TestHash : public hamon::hash<T>
{
	int id;

	explicit HAMON_CXX11_CONSTEXPR
	TestHash(int i) : id(i) {}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestHash const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestHash const& rhs) const
	{
		return id != rhs.id;
	}
};

template <typename T>
HAMON_CXX14_CONSTEXPR
void swap(TestHash<T>& x, TestHash<T>& y)
{
	hamon::adl_swap(x.id, y.id);
}

template <typename T>
struct WorstHash
{
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(T) const HAMON_NOEXCEPT
	{
		return 0;
	}
};

template <typename T>
struct TestEqualTo : public hamon::equal_to<T>
{
	int id;

	explicit HAMON_CXX11_CONSTEXPR
	TestEqualTo(int i) : id(i) {}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestEqualTo const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestEqualTo const& rhs) const
	{
		return id != rhs.id;
	}
};

template <typename T>
HAMON_CXX14_CONSTEXPR
void swap(TestEqualTo<T>& x, TestEqualTo<T>& y)
{
	hamon::adl_swap(x.id, y.id);
}

struct NonCopyableMovable
{
	int value;

	explicit HAMON_CXX11_CONSTEXPR
	NonCopyableMovable(int v) : value(v) {}

	NonCopyableMovable(NonCopyableMovable&&)                 = delete;
	NonCopyableMovable(NonCopyableMovable const&)            = delete;
	NonCopyableMovable& operator=(NonCopyableMovable&&)      = delete;
	NonCopyableMovable& operator=(NonCopyableMovable const&) = delete;

	HAMON_CXX11_CONSTEXPR
	bool operator==(NonCopyableMovable const& rhs) const
	{
		return value == rhs.value;
	}
};

#if !defined(HAMON_NO_EXCEPTIONS)

struct ThrowIfNegative
{
	struct Exception{};

	int value;

	ThrowIfNegative(int v) : value(v)
	{
		if (v < 0)
		{
			throw Exception{};
		}
	}
};

struct ThrowOnCopy
{
	struct Exception{};

	int value;

	ThrowOnCopy(int v) : value(v)
	{}

	ThrowOnCopy(ThrowOnCopy const&)
	{
		throw Exception{};
	}

	ThrowOnCopy(ThrowOnCopy&&)                 = default;
	ThrowOnCopy& operator=(ThrowOnCopy&&)      = delete;
	ThrowOnCopy& operator=(ThrowOnCopy const&) = delete;
};

struct ThrowOnMove
{
	struct Exception{};

	int value;

	ThrowOnMove(int v) : value(v)
	{}

	ThrowOnMove(ThrowOnMove&&)
	{
		throw Exception{};
	}

	ThrowOnMove(ThrowOnMove const&)            = default;
	ThrowOnMove& operator=(ThrowOnMove&&)      = delete;
	ThrowOnMove& operator=(ThrowOnMove const&) = delete;
};

struct ThrowOnCopyIfNegative
{
	struct Exception{};

	int value;

	ThrowOnCopyIfNegative(int v) : value(v)
	{}

	ThrowOnCopyIfNegative(ThrowOnCopyIfNegative const& x)
		: value(x.value)
	{
		if (x.value < 0)
		{
			throw Exception{};
		}
	}

	ThrowOnCopyIfNegative(ThrowOnCopyIfNegative&&)                 = default;
	ThrowOnCopyIfNegative& operator=(ThrowOnCopyIfNegative&&)      = delete;
	ThrowOnCopyIfNegative& operator=(ThrowOnCopyIfNegative const&) = delete;
};

#endif

}	// namespace hamon_unordered_map_test

#endif // HAMON_UNORDERED_MAP_TEST_HELPER_HPP
