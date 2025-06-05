/**
 *	@file	flat_multimap_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_FLAT_MULTIMAP_TEST_HELPER_HPP
#define HAMON_FLAT_MULTIMAP_TEST_HELPER_HPP

#include <hamon/algorithm.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon_flat_multimap_test
{

template <typename FlatMultimap>
HAMON_CXX14_CONSTEXPR bool
check_invariant(FlatMultimap const& m)
{
	if (m.keys().size() != m.values().size())
	{
		return false;
	}

	if (!hamon::is_sorted(m.keys().begin(), m.keys().end(), m.key_comp()))
	{
		return false;
	}

	return true;
}

template <typename T>
struct MinSequenceContainer
{
private:
	using Container = hamon::vector<T>;

	Container m_cont;

public:
	using value_type = T;
	using size_type = typename Container::size_type;
	using iterator = typename Container::iterator;
	using const_iterator = typename Container::const_iterator;

	HAMON_CXX14_CONSTEXPR iterator       begin()       { return m_cont.begin(); }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const { return m_cont.begin(); }
	HAMON_CXX14_CONSTEXPR iterator       end()         { return m_cont.end(); }
	HAMON_CXX11_CONSTEXPR const_iterator end() const   { return m_cont.end(); }

	HAMON_CXX11_CONSTEXPR bool empty() const noexcept { return m_cont.empty(); }
	HAMON_CXX11_CONSTEXPR size_type size() const noexcept { return m_cont.size(); }
	HAMON_CXX11_CONSTEXPR size_type max_size() const noexcept { return m_cont.max_size(); }

	MinSequenceContainer() = default;

	HAMON_CXX14_CONSTEXPR
	MinSequenceContainer(std::initializer_list<T> il)
		: m_cont(il)
	{}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(const_iterator pos, Args&&... args)
	{
		return m_cont.emplace(pos, hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator pos)
	{
		return m_cont.erase(pos);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		return m_cont.erase(first, last);
	}

	HAMON_CXX14_CONSTEXPR void
	clear()
	{
		return m_cont.clear();
	}
};

template <typename T>
struct UseAllocContainer
{
private:
	using Container = hamon::vector<T>;

	Container m_cont;

public:
	using value_type = T;
	using allocator_type = typename Container::allocator_type;
	using size_type = typename Container::size_type;
	using iterator = typename Container::iterator;
	using const_iterator = typename Container::const_iterator;

	HAMON_CXX14_CONSTEXPR iterator       begin()       { return m_cont.begin(); }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const { return m_cont.begin(); }
	HAMON_CXX14_CONSTEXPR iterator       end()         { return m_cont.end(); }
	HAMON_CXX11_CONSTEXPR const_iterator end() const   { return m_cont.end(); }

	HAMON_CXX11_CONSTEXPR bool empty() const noexcept { return m_cont.empty(); }
	HAMON_CXX11_CONSTEXPR size_type size() const noexcept { return m_cont.size(); }
	HAMON_CXX11_CONSTEXPR size_type max_size() const noexcept { return m_cont.max_size(); }

	UseAllocContainer() = default;

	HAMON_CXX14_CONSTEXPR
	UseAllocContainer(std::initializer_list<T> il)
		: m_cont(il)
	{}

	HAMON_CXX14_CONSTEXPR
	UseAllocContainer(allocator_type const& a)
		: m_cont(a)
	{}

	HAMON_CXX14_CONSTEXPR
	UseAllocContainer(UseAllocContainer const& c, allocator_type const& a)
		: m_cont(c.m_cont, a)
	{}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(const_iterator pos, Args&&... args)
	{
		return m_cont.emplace(pos, hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator pos)
	{
		return m_cont.erase(pos);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		return m_cont.erase(first, last);
	}

	HAMON_CXX14_CONSTEXPR void
	clear()
	{
		return m_cont.clear();
	}
};

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

	friend HAMON_CXX11_CONSTEXPR bool
	operator<(TransparentKey const& lhs, TransparentKey const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator<(TransparentKey const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator<(int lhs, TransparentKey const& rhs)
	{
		return lhs < rhs.value;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator>(TransparentKey const& lhs, TransparentKey const& rhs)
	{
		return lhs.value > rhs.value;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator>(TransparentKey const& lhs, int rhs)
	{
		return lhs.value > rhs;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator>(int lhs, TransparentKey const& rhs)
	{
		return lhs > rhs.value;
	}
};

template <typename T>
struct TestLess : public hamon::less<T>
{
	int id;

	HAMON_CXX11_CONSTEXPR
	TestLess() : id(0) {}

	explicit HAMON_CXX11_CONSTEXPR
	TestLess(int i) : id(i) {}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestLess const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestLess const& rhs) const
	{
		return id != rhs.id;
	}
};

// is_always_equal == true_type なアロケータ
template <typename T>
struct TestAllocator1
{
	using value_type = T;

	HAMON_CXX11_CONSTEXPR
	TestAllocator1() {}

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

	HAMON_CXX11_CONSTEXPR
	TestAllocator2() : id(0) {}

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

	HAMON_CXX11_CONSTEXPR
	TestAllocator3() : id(0) {}

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

	HAMON_CXX11_CONSTEXPR
	TestAllocator4() : id(0) {}

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

	HAMON_CXX11_CONSTEXPR
	TestAllocator5() : id(0) {}

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

	HAMON_CXX11_CONSTEXPR
	TestAllocator6() : id(0) {}

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

#if !defined(HAMON_NO_EXCEPTIONS)

template <typename T>
struct ThrowAllocator
{
	using value_type = T;

	int* throw_after;

	HAMON_CXX11_CONSTEXPR
	ThrowAllocator() : throw_after(nullptr) {}

	explicit HAMON_CXX11_CONSTEXPR
	ThrowAllocator(int* x) : throw_after(x) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	ThrowAllocator(ThrowAllocator<U> const& x) : throw_after(x.throw_after) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		if (throw_after != nullptr)
		{
			--(*throw_after);
			if (*throw_after <= 0)
			{
				throw std::bad_alloc();
			}
		}

		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(ThrowAllocator const& rhs) const
	{
		return throw_after == rhs.throw_after;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(ThrowAllocator const& rhs) const
	{
		return !(*this == rhs);
	}
};

template <typename T>
struct EmplaceUnsafeContainer : hamon::vector<T>
{
	using hamon::vector<T>::vector;

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR auto emplace(Args&&... args)
		-> decltype(hamon::declval<hamon::vector<T>>().emplace(hamon::forward<Args>(args)...))
	{
		if (this->size() > 1)
		{
			auto it1 = this->begin();
			auto it2 = it1 + 1;
			// messing up the container
			hamon::iter_swap(it1, it2);
		}

		throw 42;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR auto insert(Args&&... args)
		-> decltype(hamon::declval<hamon::vector<T>>().insert(hamon::forward<Args>(args)...))
	{
		if (this->size() > 1)
		{
			auto it1 = this->begin();
			auto it2 = it1 + 1;
			// messing up the container
			hamon::iter_swap(it1, it2);
		}

		throw 42;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR auto insert_range(Args&&... args)
		-> decltype(hamon::declval<hamon::vector<T>>().insert_range(hamon::forward<Args>(args)...))
	{
		if (this->size() > 1)
		{
			auto it1 = this->begin();
			auto it2 = it1 + 1;
			// messing up the container
			hamon::iter_swap(it1, it2);
		}

		throw 42;
	}
};

template <typename T>
struct ThrowOnEraseContainer : hamon::vector<T>
{
	using hamon::vector<T>::vector;

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR auto erase(Args&&... args)
		-> decltype(hamon::declval<hamon::vector<T>>().erase(hamon::forward<Args>(args)...))
	{
		throw 42;
	}
};

template <typename T>
struct ThrowOnMoveContainer : hamon::vector<T>
{
	using hamon::vector<T>::vector;

	ThrowOnMoveContainer() = default;

	HAMON_CXX14_CONSTEXPR ThrowOnMoveContainer(ThrowOnMoveContainer&&) { throw 42; }

	HAMON_CXX14_CONSTEXPR ThrowOnMoveContainer& operator=(ThrowOnMoveContainer&&) { throw 42; }
};

#endif

}	// namespace hamon_flat_multimap_test

#endif // HAMON_FLAT_MULTIMAP_TEST_HELPER_HPP
