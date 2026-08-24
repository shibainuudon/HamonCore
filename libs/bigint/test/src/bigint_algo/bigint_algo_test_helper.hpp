/**
 *	@file	bigint_algo_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_BIGINT_ALGO_TEST_HELPER_HPP
#define HAMON_BIGINT_ALGO_TEST_HELPER_HPP

#include <hamon/algorithm/equal.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/initializer_list.hpp>

namespace hamon_bigint_test
{

template <typename T, hamon::size_t N>
struct MyVector
{
private:
	using value_type = T;
	using size_type = hamon::size_t;

	size_type  m_size;
	value_type m_data[N];

public:
	HAMON_CXX14_CONSTEXPR
	MyVector(hamon::initializer_list<T> il)
		: m_size(il.size())
		, m_data{}
	{
		auto p = m_data;
		for (auto it = il.begin(); it != il.end(); ++it)
		{
			*p++ = *it;
		}
	}

	//HAMON_CXX14_CONSTEXPR
	//MyVector(MyVector const& rhs)
	//	: m_size(rhs.size())
	//	, m_data{}
	//{
	//	auto dst = m_data;
	//	auto src = rhs.data();
	//	for (size_type i = 0; i < m_size; ++i)
	//	{
	//		*dst++ = *src++;
	//	}
	//}

	HAMON_CXX11_CONSTEXPR size_type size() const
	{
		return m_size;
	}

	HAMON_CXX11_CONSTEXPR size_type max_size() const
	{
		return N;
	}

	HAMON_CXX14_CONSTEXPR value_type* data()
	{
		return m_data;
	}

	HAMON_CXX11_CONSTEXPR value_type const* data() const
	{
		return m_data;
	}

	HAMON_CXX14_CONSTEXPR void resize(size_type new_size)
	{
		for (size_type i = m_size; i < new_size; ++i)
		{
			m_data[i] = 0;
		}

		m_size = new_size;
	}

	HAMON_CXX11_CONSTEXPR bool operator==(MyVector const& rhs) const
	{
		return m_size == rhs.m_size &&
			hamon::equal(data(), data() + size(), rhs.data());
	}
};

}	// namespace hamon_bigint_test

#endif // HAMON_BIGINT_ALGO_TEST_HELPER_HPP
