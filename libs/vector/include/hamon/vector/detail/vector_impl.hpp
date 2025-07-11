/**
 *	@file	vector_impl.hpp
 *
 *	@brief	vector_impl の定義
 */

#ifndef HAMON_VECTOR_DETAIL_VECTOR_IMPL_HPP
#define HAMON_VECTOR_DETAIL_VECTOR_IMPL_HPP

#include <hamon/memory.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename Allocator>
struct vector_impl
{
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;

	using size_type       = typename AllocTraits::size_type;
	using difference_type = typename AllocTraits::difference_type;

private:
	size_type	m_size{};
	size_type	m_capacity{};
	T*			m_data{};

public:
	HAMON_CXX11_CONSTEXPR
	vector_impl() HAMON_NOEXCEPT {}

	// コピー禁止
	vector_impl(vector_impl const&) = delete;
	vector_impl& operator=(vector_impl const&) = delete;

	HAMON_CXX14_CONSTEXPR
	vector_impl(vector_impl&& x) HAMON_NOEXCEPT
	{
		m_size     = hamon::exchange(x.m_size,     size_type{0});
		m_capacity = hamon::exchange(x.m_capacity, size_type{0});
		m_data     = hamon::exchange(x.m_data,     nullptr);
	}

	HAMON_CXX14_CONSTEXPR
	vector_impl& operator=(vector_impl&& x) HAMON_NOEXCEPT
	{
		vector_impl(hamon::move(x)).swap(*this);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR void
	swap(vector_impl& x) HAMON_NOEXCEPT
	{
		hamon::swap(m_size,     x.m_size);
		hamon::swap(m_capacity, x.m_capacity);
		hamon::swap(m_data,     x.m_data);
	}

	HAMON_CXX11_CONSTEXPR T*
	begin() const HAMON_NOEXCEPT
	{
		return m_data;
	}

	HAMON_CXX11_CONSTEXPR T*
	end() const HAMON_NOEXCEPT
	{
		return m_data + m_size;
	}

	HAMON_CXX11_CONSTEXPR
	size_type size() const HAMON_NOEXCEPT
	{
		return m_size;
	}

	HAMON_CXX11_CONSTEXPR
	size_type capacity() const HAMON_NOEXCEPT
	{
		return m_capacity;
	}

	HAMON_CXX14_CONSTEXPR void
	assign_n(Allocator& allocator, size_type n, T const& value);

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	assign_range(Allocator& allocator, Iterator first, Sentinel last);

	template <typename Range>
	HAMON_CXX14_CONSTEXPR void
	assign_range(Allocator& allocator, Range&& rg);

	HAMON_CXX14_CONSTEXPR void
	resize(Allocator& allocator, size_type n);

	HAMON_CXX14_CONSTEXPR void
	resize(Allocator& allocator, size_type n, T const& value);

	HAMON_CXX14_CONSTEXPR void
	reserve(Allocator& allocator, size_type n);

	HAMON_CXX14_CONSTEXPR void
	shrink_to_fit(Allocator& allocator);

	HAMON_CXX14_CONSTEXPR void
	pop_back(Allocator& allocator);

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void
	emplace(Allocator& allocator, difference_type pos, Args&&... args);

	HAMON_CXX14_CONSTEXPR void
	insert_n(Allocator& allocator, difference_type pos, size_type n, T const& value);

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	insert_range(Allocator& allocator, difference_type pos, Iterator first, Sentinel last);

	template <typename Range>
	HAMON_CXX14_CONSTEXPR void
	insert_range(Allocator& allocator, difference_type pos, Range&& rg);

	HAMON_CXX14_CONSTEXPR void
	erase_n(Allocator& allocator, difference_type pos, size_type n);

	HAMON_CXX14_CONSTEXPR void
	clear(Allocator& allocator);
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_VECTOR_DETAIL_VECTOR_IMPL_HPP
