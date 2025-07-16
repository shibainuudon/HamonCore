/**
 *	@file	deque_impl.hpp
 *
 *	@brief	deque_impl の定義
 */

#ifndef HAMON_DEQUE_DETAIL_DEQUE_IMPL_HPP
#define HAMON_DEQUE_DETAIL_DEQUE_IMPL_HPP

#include <hamon/deque/detail/deque_iterator.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/algorithm/move.hpp>
#include <hamon/algorithm/move_backward.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/limits.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

template <typename T, typename Allocator>
struct deque_impl
{
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;
	using MapAllocator = typename AllocTraits::template rebind_alloc<typename AllocTraits::pointer>;
	using MapAllocTraits = hamon::allocator_traits<MapAllocator>;

public:
	using size_type              = typename AllocTraits::size_type;
	using difference_type        = typename AllocTraits::difference_type;
	using iterator               = hamon::detail::deque_iterator<deque_impl, T, false>;
	using const_iterator         = hamon::detail::deque_iterator<deque_impl, T, true>;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

private:
	static const size_type BlockSize = 8;

	T**             m_map{};
	size_type       m_map_size{};
	difference_type m_start{};
	difference_type m_end{};

public:
	HAMON_CXX11_CONSTEXPR
	deque_impl() HAMON_NOEXCEPT {}

	// コピー禁止
	deque_impl(deque_impl const&) = delete;
	deque_impl& operator=(deque_impl const&) = delete;

	HAMON_CXX14_CONSTEXPR
	deque_impl(deque_impl&& x) HAMON_NOEXCEPT
	{
		m_map      = hamon::exchange(x.m_map,      nullptr);
		m_map_size = hamon::exchange(x.m_map_size, size_type{0});
		m_start    = hamon::exchange(x.m_start,    difference_type{0});
		m_end      = hamon::exchange(x.m_end,      difference_type{0});
	}

	HAMON_CXX14_CONSTEXPR
	deque_impl& operator=(deque_impl&& x) HAMON_NOEXCEPT
	{
		deque_impl(hamon::move(x)).Swap(*this);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR void
	Swap(deque_impl& x) HAMON_NOEXCEPT
	{
		hamon::swap(m_map,      x.m_map);
		hamon::swap(m_map_size, x.m_map_size);
		hamon::swap(m_start,    x.m_start);
		hamon::swap(m_end,      x.m_end);
	}

	HAMON_CXX14_CONSTEXPR iterator Begin() HAMON_NOEXCEPT
	{
		return iterator(this, m_start);
	}

	HAMON_CXX11_CONSTEXPR const_iterator Begin() const HAMON_NOEXCEPT
	{
		return const_iterator(this, m_start);
	}

	HAMON_CXX14_CONSTEXPR iterator End() HAMON_NOEXCEPT
	{
		return iterator(this, m_end);
	}

	HAMON_CXX11_CONSTEXPR const_iterator End() const HAMON_NOEXCEPT
	{
		return const_iterator(this, m_end);
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator RBegin() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->End());
	}

	HAMON_CXX11_CONSTEXPR const_reverse_iterator RBegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->End());
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator REnd() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->Begin());
	}

	HAMON_CXX11_CONSTEXPR const_reverse_iterator REnd() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->Begin());
	}

	HAMON_CXX14_CONSTEXPR T& Subscript(difference_type n) HAMON_NOEXCEPT
	{
		return m_map[static_cast<size_type>(n) / BlockSize][static_cast<size_type>(n) % BlockSize];
	}

	HAMON_CXX11_CONSTEXPR T const& Subscript(difference_type n) const HAMON_NOEXCEPT
	{
		return m_map[static_cast<size_type>(n) / BlockSize][static_cast<size_type>(n) % BlockSize];
	}
private:
	HAMON_CXX14_CONSTEXPR T* GetPtr(difference_type n) HAMON_NOEXCEPT
	{
		return &m_map[static_cast<size_type>(n) / BlockSize][static_cast<size_type>(n) % BlockSize];
	}
public:
	HAMON_CXX11_CONSTEXPR size_type
	MaxSize(Allocator const& allocator) const HAMON_NOEXCEPT
	{
		return hamon::min(
			static_cast<size_type>(hamon::numeric_limits<difference_type>::max()),
			static_cast<size_type>(AllocTraits::max_size(allocator)));
	}

	HAMON_CXX11_CONSTEXPR size_type Size() const HAMON_NOEXCEPT
	{
		return static_cast<size_type>(m_end - m_start);
	}
private:
	HAMON_CXX11_CONSTEXPR size_type Capacity() const HAMON_NOEXCEPT
	{
		return m_map_size * BlockSize;
	}
public:
	HAMON_CXX14_CONSTEXPR void Clear(Allocator& allocator)
	{
		for (difference_type i = m_start; i < m_end; ++i)
		{
			AllocTraits::destroy(allocator, GetPtr(i));
		}

		for (size_type i = 0; i < m_map_size; ++i)
		{
			AllocTraits::deallocate(allocator, m_map[i], BlockSize);
		}

		if (m_map != nullptr)
		{
			MapAllocator map_allocator(allocator);
			MapAllocTraits::deallocate(map_allocator, m_map, m_map_size);
			m_map = nullptr;
		}
		m_map_size = 0;
		m_start = 0;
		m_end = 0;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void EmplaceBack(Allocator& allocator, Args&&... args)
	{
		if (m_end == static_cast<difference_type>(this->Capacity()))
		{
			auto const new_map_size = m_map_size + 1;
			MapAllocator map_allocator(allocator);
			auto new_map = MapAllocTraits::allocate(map_allocator, new_map_size);
			hamon::detail::uninitialized_value_construct_n_impl(new_map, new_map_size);
			for (size_type i = 0; i < new_map_size; ++i)
			{
				if (i < m_map_size)
				{
					new_map[i] = m_map[i];
				}
				else
				{
					new_map[i] = AllocTraits::allocate(allocator, BlockSize);
				}
			}

			if (m_map != nullptr)
			{
				MapAllocTraits::deallocate(map_allocator, m_map, m_map_size);
			}
			m_map = new_map;
			m_map_size = new_map_size;
		}

		AllocTraits::construct(allocator, GetPtr(m_end), hamon::forward<Args>(args)...);
		++m_end;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void EmplaceFront(Allocator& allocator, Args&&... args)
	{
		if (m_start == 0)
		{
			auto const new_map_size = m_map_size + 1;
			MapAllocator map_allocator(allocator);
			auto new_map = MapAllocTraits::allocate(map_allocator, new_map_size);
			hamon::detail::uninitialized_value_construct_n_impl(new_map, new_map_size);
			for (size_type i = 0; i < m_map_size; ++i)
			{
				new_map[i + 1] = m_map[i];
			}
			new_map[0] = AllocTraits::allocate(allocator, BlockSize);

			if (m_map != nullptr)
			{
				MapAllocTraits::deallocate(map_allocator, m_map, m_map_size);
			}
			m_map = new_map;
			m_map_size = new_map_size;

			m_start += BlockSize;
			m_end += BlockSize;
		}

		AllocTraits::construct(allocator, GetPtr(m_start - 1), hamon::forward<Args>(args)...);
		--m_start;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void Emplace(Allocator& allocator, difference_type pos, Args&&... args)
	{
		auto const sz = static_cast<difference_type>(this->Size());

		if (pos == 0)
		{
			this->EmplaceFront(allocator, hamon::forward<Args>(args)...);
		}
		else if (pos == sz)
		{
			this->EmplaceBack(allocator, hamon::forward<Args>(args)...);
		}
		else
		{
			// 移動する要素数が少なくなるように、前方または後方に移動する
			if (pos <= (sz / 2))
			{
				this->EmplaceFront(allocator, hamon::move(*this->Begin()));
				auto dst = this->Begin() + 1;
				auto first = dst + 1;
				auto last = dst + pos;
				dst = hamon::move(first, last, dst);
				AllocTraits::construct(allocator, hamon::to_address(dst), hamon::forward<Args>(args)...);
			}
			else
			{
				this->EmplaceBack(allocator, hamon::move(*this->RBegin()));
				auto dst = this->RBegin() + 1;
				auto first = dst + 1;
				auto last = dst + (sz - pos);
				dst = hamon::move(first, last, dst);
				AllocTraits::construct(allocator, hamon::to_address(dst), hamon::forward<Args>(args)...);
			}
		}
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void AppendIter(Allocator& allocator, Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			this->EmplaceBack(allocator, *first);
		}
	}

	HAMON_CXX14_CONSTEXPR void AppendFillN(Allocator& allocator, size_type n, T const& t)
	{
		for (; n > 0; --n)
		{
			this->EmplaceBack(allocator, t);
		}
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void InsertIter(Allocator& allocator, difference_type pos, Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			this->Emplace(allocator, pos, *first);
			++pos;
		}
	}

	HAMON_CXX14_CONSTEXPR void InsertFillN(Allocator& allocator, difference_type pos, size_type n, T const& t)
	{
		for (; n > 0; --n)
		{
			this->Emplace(allocator, pos, t);
			++pos;
		}
	}

	HAMON_CXX14_CONSTEXPR void PopBackN(Allocator& allocator, size_type n)
	{
		HAMON_ASSERT(n <= this->Size());

		for (; n > 0; --n)
		{
			AllocTraits::destroy(allocator, GetPtr(m_end - 1));
			--m_end;
		}
	}

	HAMON_CXX14_CONSTEXPR void PopFrontN(Allocator& allocator, size_type n)
	{
		HAMON_ASSERT(n <= this->Size());

		for (; n > 0; --n)
		{
			AllocTraits::destroy(allocator, GetPtr(m_start));
			++m_start;
		}
	}

	HAMON_CXX14_CONSTEXPR void DestroyN(Allocator& allocator, difference_type pos, size_type n)
	{
		HAMON_ASSERT(n <= this->Size());

		auto const first = this->Begin() + pos;
		auto const last  = first + static_cast<difference_type>(n);

		if (first - this->Begin() < this->End() - last)
		{
			hamon::move_backward(this->Begin(), first, last);
			PopFrontN(allocator, n);
		}
		else
		{
			hamon::move(last, this->End(), first);
			PopBackN(allocator, n);
		}
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void AssignIter(Allocator& allocator, Iterator first, Sentinel last)
	{
		auto dst_first = this->Begin();
		auto dst_last = this->End();
		for (; first != last && dst_first != dst_last;)
		{
			*dst_first = *first;
			++dst_first;
			++first;
		}
		this->PopBackN(allocator, static_cast<size_type>(dst_last - dst_first));
		this->AppendIter(allocator, first, last);
	}

	HAMON_CXX14_CONSTEXPR void AssignFillN(Allocator& allocator, size_type n, T const& t)
	{
		auto dst_first = this->Begin();
		auto dst_last = this->End();
		for (; n > 0 && dst_first != dst_last;)
		{
			*dst_first = t;
			++dst_first;
			--n;
		}
		this->PopBackN(allocator, static_cast<size_type>(dst_last - dst_first));
		this->AppendFillN(allocator, n, t);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void Resize(Allocator& allocator, size_type sz, Args&&... args)
	{
		if (sz < this->Size())
		{
			this->PopBackN(allocator, this->Size() - sz);
		}

		while (this->Size() < sz)
		{
			this->EmplaceBack(allocator, hamon::forward<Args>(args)...);
		}
	}
};

HAMON_WARNING_POP()

}	// namespace detail

}	// namespace hamon

#endif // HAMON_DEQUE_DETAIL_DEQUE_IMPL_HPP
