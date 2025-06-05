/**
 *	@file	flat_map_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_FLAT_MAP_TEST_HELPER_HPP
#define HAMON_FLAT_MAP_TEST_HELPER_HPP

#include <hamon/vector.hpp>
#include <hamon/config.hpp>

namespace hamon_flat_map_test
{

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

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(const_iterator pos, Args&&... args)
	{
		return m_cont.emplace(pos, hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		return m_cont.erase(first, last);
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
};

template <typename T>
struct TestLess : public hamon::less<T>
{
	int id;

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

}	// namespace hamon_flat_map_test

#endif // HAMON_FLAT_MAP_TEST_HELPER_HPP
