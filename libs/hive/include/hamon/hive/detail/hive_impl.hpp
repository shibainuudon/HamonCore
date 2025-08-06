/**
 *	@file	hive_impl.hpp
 *
 *	@brief	hive_impl の定義
 */

#ifndef HAMON_HIVE_DETAIL_HIVE_IMPL_HPP
#define HAMON_HIVE_DETAIL_HIVE_IMPL_HPP

#include <hamon/hive/hive_limits.hpp>
#include <hamon/hive/detail/hive_block.hpp>
#include <hamon/hive/detail/hive_iterator.hpp>
#include <hamon/hive/detail/hive_traits.hpp>
#include <hamon/algorithm/clamp.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/iterator/make_move_iterator.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/limits.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

/**
 *	Elementは
 *
 *	Element Blockは
 *	・Active:   少なくとも1つのElementがactive
 *	・Open:     少なくとも1つのElementが非active
 *	・Reserved: 全てのElementが非active
 */



template <typename T, typename Allocator>
struct hive_impl
{
private:
	using Block = hive_block<T>;
	using AllocTraits = hamon::allocator_traits<Allocator>;
	using BlockAllocator   = typename AllocTraits::template rebind_alloc<Block>;
	using BlockAllocTraits = typename AllocTraits::template rebind_traits<Block>;

public:
	using value_type      = T;
	using pointer         = typename AllocTraits::pointer;
	using const_pointer   = typename AllocTraits::const_pointer;
	using reference       = value_type&;
	using const_reference = value_type const&;
	using size_type       = typename AllocTraits::size_type;
	using difference_type = typename AllocTraits::difference_type;
	using iterator        = hamon::detail::hive_iterator<hive_impl, false>;
	using const_iterator  = hamon::detail::hive_iterator<hive_impl, true>;

private:
	hamon::hive_limits  m_current_limits;
	size_type           m_total_size     = 0;
	size_type           m_total_capacity = 0;
	Block*              m_head           = nullptr;		// TODO ポインタじゃなくしたい

public:
	HAMON_CXX11_CONSTEXPR
	hive_impl()
		: hive_impl(hamon::detail::hive_traits<T>::default_limits())
	{}

	explicit HAMON_CXX14_CONSTEXPR
	hive_impl(hamon::hive_limits block_limits)
		: m_current_limits(block_limits)
	{
		// [hive.overview]/5.4
		HAMON_ASSERT(block_limits.min <= block_limits.max);
		HAMON_ASSERT(block_limits.min >= hamon::detail::hive_traits<T>::hard_limits().min);
		HAMON_ASSERT(block_limits.max <= hamon::detail::hive_traits<T>::hard_limits().max);
	}

	// コピー禁止
	hive_impl(hive_impl const&) = delete;
	hive_impl& operator=(hive_impl const&) = delete;

	HAMON_CXX14_CONSTEXPR
	hive_impl(hive_impl&& x) HAMON_NOEXCEPT
		: m_current_limits(hamon::exchange(x.m_current_limits, hamon::hive_limits{0, 0}))
		, m_total_size    (hamon::exchange(x.m_total_size,     size_type{0}))
		, m_total_capacity(hamon::exchange(x.m_total_capacity, size_type{0}))
		, m_head          (hamon::exchange(x.m_head,           nullptr))
	{}

	HAMON_CXX14_CONSTEXPR
	hive_impl& operator=(hive_impl&& x) HAMON_NOEXCEPT
	{
		hive_impl(hamon::move(x)).Swap(*this);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR void
	Swap(hive_impl& x) HAMON_NOEXCEPT
	{
		hamon::swap(m_current_limits, x.m_current_limits);
		hamon::swap(m_total_size,     x.m_total_size);
		hamon::swap(m_total_capacity, x.m_total_capacity);
		hamon::swap(m_head,           x.m_head);
	}

	HAMON_CXX11_CONSTEXPR hive_limits
	CurrentLimits() const HAMON_NOEXCEPT
	{
		return m_current_limits;
	}

	HAMON_CXX11_CONSTEXPR size_type
	MaxSize(Allocator const& allocator) const HAMON_NOEXCEPT
	{
		return hamon::min(
			static_cast<size_type>(hamon::numeric_limits<difference_type>::max()),
			static_cast<size_type>(AllocTraits::max_size(allocator)));
	}

	HAMON_CXX11_CONSTEXPR
	size_type Size() const HAMON_NOEXCEPT
	{
		return m_total_size;
	}

	HAMON_CXX11_CONSTEXPR
	size_type Capacity() const HAMON_NOEXCEPT
	{
		return m_total_capacity;
	}

private:
	// Active Blocks

	HAMON_CXX11_CONSTEXPR Block*
	ActiveBlocks_Begin() const HAMON_NOEXCEPT
	{
		return m_head ? m_head->m_active_next : nullptr;
	}

	HAMON_CXX11_CONSTEXPR Block*
	ActiveBlocks_End() const HAMON_NOEXCEPT
	{
		return m_head;
	}

	HAMON_CXX11_CONSTEXPR Block*
	ActiveBlocks_Back() const HAMON_NOEXCEPT
	{
		return m_head ? m_head->m_active_prev : nullptr;
	}

	HAMON_CXX14_CONSTEXPR void
	ActiveBlocks_Append(Block* block) HAMON_NOEXCEPT
	{
		auto prev = m_head->m_active_prev;
		auto next = prev->m_active_next;
		prev->m_active_next = block;
		next->m_active_prev = block;
		block->m_active_prev = prev;
		block->m_active_next = next;

		block->m_index = prev->m_index + 1;
	}

	HAMON_CXX14_CONSTEXPR void
	ActiveBlocks_Remove(Block* block) HAMON_NOEXCEPT
	{
		auto prev = block->m_active_prev;
		auto next = block->m_active_next;
		prev->m_active_next = next;
		next->m_active_prev = prev;
	}

	// Open Blocks

	HAMON_CXX11_CONSTEXPR Block*
	OpenBlocks_Begin() const HAMON_NOEXCEPT
	{
		return m_head ? m_head->m_open_next : nullptr;
	}

	HAMON_CXX11_CONSTEXPR Block*
	OpenBlocks_End() const HAMON_NOEXCEPT
	{
		return m_head;
	}

	HAMON_CXX11_CONSTEXPR Block*
	OpenBlocks_Back() const HAMON_NOEXCEPT
	{
		return m_head ? m_head->m_open_prev : nullptr;
	}

	HAMON_CXX14_CONSTEXPR void
	OpenBlocks_Append(Block* block) HAMON_NOEXCEPT
	{
		auto prev = m_head->m_open_prev;
		auto next = prev->m_open_next;
		prev->m_open_next = block;
		next->m_open_prev = block;
		block->m_open_prev = prev;
		block->m_open_next = next;
	}

	HAMON_CXX14_CONSTEXPR void
	OpenBlocks_Prepend(Block* block) HAMON_NOEXCEPT
	{
		auto prev = m_head;
		auto next = prev->m_open_next;
		prev->m_open_next = block;
		next->m_open_prev = block;
		block->m_open_prev = prev;
		block->m_open_next = next;
	}

	HAMON_CXX14_CONSTEXPR void
	OpenBlocks_Remove(Block* block) HAMON_NOEXCEPT
	{
		auto prev = block->m_open_prev;
		auto next = block->m_open_next;
		prev->m_open_next = next;
		next->m_open_prev = prev;
	}

	// Reserved Blocks
	HAMON_CXX11_CONSTEXPR Block*
	ReservedBlocks_Next(Block* block) const HAMON_NOEXCEPT
	{
		return block->m_reserved_next;
	}

	HAMON_CXX11_CONSTEXPR Block*
	ReservedBlocks_Begin() const HAMON_NOEXCEPT
	{
		return m_head ? ReservedBlocks_Next(m_head) : nullptr;
	}

	HAMON_CXX11_CONSTEXPR Block*
	ReservedBlocks_End() const HAMON_NOEXCEPT
	{
		return m_head;
	}

	//HAMON_CXX11_CONSTEXPR Block*
	//ReservedBlocks_Back() const HAMON_NOEXCEPT
	//{
	//	return m_head ? m_head->m_reserved_prev : nullptr;
	//}

	HAMON_CXX14_CONSTEXPR void
	ReservedBlocks_Append(Block* block) HAMON_NOEXCEPT
	{
		auto prev = m_head->m_reserved_prev;
		auto next = prev->m_reserved_next;
		prev->m_reserved_next = block;
		next->m_reserved_prev = block;
		block->m_reserved_prev = prev;
		block->m_reserved_next = next;
	}

	HAMON_CXX14_CONSTEXPR void
	ReservedBlocks_Prepend(Block* block) HAMON_NOEXCEPT
	{
		auto prev = m_head;
		auto next = prev->m_reserved_next;
		prev->m_reserved_next = block;
		next->m_reserved_prev = block;
		block->m_reserved_prev = prev;
		block->m_reserved_next = next;
	}

	HAMON_CXX14_CONSTEXPR void
	ReservedBlocks_Remove(Block* block) HAMON_NOEXCEPT
	{
		auto prev = block->m_reserved_prev;
		auto next = block->m_reserved_next;
		prev->m_reserved_next = next;
		next->m_reserved_prev = prev;
	}

public:
	HAMON_CXX11_CONSTEXPR iterator
	Begin() const HAMON_NOEXCEPT
	{
		return iterator{this->ActiveBlocks_Begin()};
	}

	HAMON_CXX11_CONSTEXPR iterator
	End() const HAMON_NOEXCEPT
	{
		return iterator{this->ActiveBlocks_End()};
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	Emplace(Allocator& allocator, Args&&... args)
	{
		if (m_total_size == m_total_capacity)
		{
			this->Grow(allocator);
		}

		auto block = this->OpenBlocks_Begin();
		bool const was_empty = block->IsEmpty();

		auto index = block->Emplace(allocator, hamon::forward<Args>(args)...);	// may throw
		++m_total_size;

		if (was_empty)
		{
			this->ActiveBlocks_Append(block);	// 末尾に追加
			this->ReservedBlocks_Remove(block);
		}

		if (block->IsFull())
		{
			this->OpenBlocks_Remove(block);
		}

		return iterator{block, index};
	}

	template <typename R>
	HAMON_CXX14_CONSTEXPR void
	InsertRange(Allocator& allocator, R&& rg)
	{
		// TODO
		// [sequence.reqmts]/13
		// Recommended practice:
		// If R models ranges​::​approximately_sized_range and ranges​::​distance(rg) <= ranges​::​reserve_hint(rg) is true,
		// an implementation should not perform more than a single reallocation.

		auto first = hamon::ranges::begin(rg);
		auto last = hamon::ranges::end(rg);
		for (auto it = first; it != last; ++it)
		{
			this->Emplace(allocator, *it);
		}
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	Insert(Allocator& allocator, Iterator first, Sentinel last)
	{
		this->InsertRange(allocator, hamon::ranges::make_subrange(first, last));
	}

private:
	HAMON_CXX14_CONSTEXPR void
	EraseImpl(Allocator& allocator, const_iterator position)
	{
		auto block = position.m_block;
		auto index = position.m_index;

		if (block->IsFull())
		{
			this->OpenBlocks_Prepend(block);		// 先頭に追加
		}

		block->Erase(allocator, index);

		if (block->IsEmpty())
		{
			this->ActiveBlocks_Remove(block);
			this->ReservedBlocks_Prepend(block);	// 先頭に追加
		}

		--m_total_size;
	}

public:
	HAMON_CXX14_CONSTEXPR iterator
	Erase(Allocator& allocator, const_iterator position)
	{
		auto ret = hamon::next(position);
		this->EraseImpl(allocator, position);
		return iterator{ret.m_block, ret.m_index};
	}

	HAMON_CXX14_CONSTEXPR iterator
	Erase(Allocator& allocator, const_iterator first, const_iterator last)
	{
		while (first != last)
		{
			first = this->Erase(allocator, first);
		}
		return iterator{first.m_block, first.m_index};
	}

	HAMON_CXX14_CONSTEXPR void
	Clear(Allocator& allocator)
	{
		this->Erase(allocator, this->Begin(), this->End());
	}

	template <typename R>
	HAMON_CXX14_CONSTEXPR void
	AssignRange(Allocator& allocator, R&& rg)
	{
		auto src_first = hamon::ranges::begin(rg);
		auto src_last = hamon::ranges::end(rg);
		auto dst_first = this->Begin();
		auto dst_last = this->End();
		for (; src_first != src_last && dst_first != dst_last; ++src_first, ++dst_first)
		{
			*dst_first = *src_first;
		}

		this->Erase(allocator, dst_first, dst_last);
		this->Insert(allocator, src_first, src_last);
	}

private:
	HAMON_CXX14_CONSTEXPR void
	AllocateHead(Allocator& allocator)
	{
		HAMON_ASSERT(m_head == nullptr);

		BlockAllocator block_allocator(allocator);
		auto head = BlockAllocTraits::allocate(block_allocator, 1);	// may throw
		BlockAllocTraits::construct(block_allocator, head);	// nothrow
		head->InitializeAsHead();
		m_head = head;
	}

	HAMON_CXX14_CONSTEXPR void
	AllocateBlock(Allocator& allocator, size_type request_size)
	{
		auto const new_block_capacity = hamon::clamp(request_size, m_current_limits.min, m_current_limits.max);

		if (m_head == nullptr)
		{
			this->AllocateHead(allocator);
		}

		BlockAllocator block_allocator(allocator);
		auto block = BlockAllocTraits::allocate(block_allocator, 1);	// may throw
		BlockAllocTraits::construct(block_allocator, block, allocator, new_block_capacity);	// may throw

		this->OpenBlocks_Append(block);		// 末尾に追加
		this->ReservedBlocks_Append(block);	// 末尾に追加

		m_total_capacity += new_block_capacity;
	}

	HAMON_CXX14_CONSTEXPR void
	DeallocateBlock(Allocator& allocator, Block* block)
	{
		m_total_capacity -= block->m_capacity;

		block->Deallocate(allocator);
		BlockAllocator block_allocator(allocator);
		BlockAllocTraits::deallocate(block_allocator, block, 1);
	}

	HAMON_CXX14_CONSTEXPR void
	DestroyBlock(Allocator& allocator, Block* block)
	{
		this->ReservedBlocks_Remove(block);
		this->OpenBlocks_Remove(block);
		this->DeallocateBlock(allocator, block);
	}

public:
	HAMON_CXX14_CONSTEXPR void
	Reserve(Allocator& allocator, size_type n)
	{
		while (m_total_capacity < n)
		{
			this->AllocateBlock(allocator, hamon::max(m_total_capacity, n - m_total_capacity));
		}
	}

	HAMON_CXX14_CONSTEXPR void
	TrimCapacity(Allocator& allocator, size_type n)
	{
		auto block = this->ReservedBlocks_Begin();
		while (block != this->ReservedBlocks_End())
		{
			auto next = this->ReservedBlocks_Next(block);

			if (m_total_capacity - block->m_capacity >= n)
			{
				this->DestroyBlock(allocator, block);
			}

			block = next;
		}
	}

	HAMON_CXX14_CONSTEXPR void
	Reshape(Allocator& allocator, hive_limits block_limits)
	{
		hive_impl tmp;
		tmp.AllocateHead(allocator);

		// block_limitsの境界外にあるActiveブロックをリストアップする
		{
			auto block = this->ActiveBlocks_Begin();
			while (block != this->ActiveBlocks_End())
			{
				auto next = block->m_active_next;

				if (!block->IsWithinLimits(block_limits))
				{
					this->ExtractBlock(block);
					tmp.SpliceBlock(block);
				}

				block = next;
			}
		}

		// block_limitsの境界外にあるEmptyブロックを削除する
		{
			auto block = this->ReservedBlocks_Begin();
			while (block != this->ReservedBlocks_End())
			{
				auto next = this->ReservedBlocks_Next(block);

				if (!block->IsWithinLimits(block_limits))
				{
					this->DestroyBlock(allocator, block);
				}

				block = next;
			}
		}

		// current-limits を更新
		m_current_limits = block_limits;

		// リストアップしたブロックを挿入
		this->Insert(allocator,
			hamon::make_move_iterator(tmp.Begin()),
			hamon::make_move_iterator(tmp.End()));

		// 後始末
		tmp.Destroy(allocator);
	}

	HAMON_CXX14_CONSTEXPR bool
	AreActiveBlocksWithinLimits(hive_limits block_limits) const
	{
		auto block = this->ActiveBlocks_Begin();
		while (block != this->ActiveBlocks_End())
		{
			if (!block->IsWithinLimits(block_limits))
			{
				return false;
			}

			block = block->m_active_next;
		}

		return true;
	}

	HAMON_CXX14_CONSTEXPR void
	ExtractBlock(Block* block)
	{
		this->ActiveBlocks_Remove(block);
		if (block->IsOpen())
		{
			this->OpenBlocks_Remove(block);
		}
		this->m_total_size -= block->m_count;
		this->m_total_capacity -= block->m_capacity;
	}

	HAMON_CXX14_CONSTEXPR void
	SpliceBlock(Block* block)
	{
		this->ActiveBlocks_Append(block);	// 末尾に追加
		if (block->IsOpen())
		{
			this->OpenBlocks_Append(block);		// 末尾に追加
		}
		this->m_total_size += block->m_count;
		this->m_total_capacity += block->m_capacity;
	}

	HAMON_CXX14_CONSTEXPR void
	Splice(hive_impl& x)
	{
		auto block = x.ActiveBlocks_Begin();
		while (block != x.ActiveBlocks_End())
		{
			auto next = block->m_active_next;

			x.ExtractBlock(block);
			this->SpliceBlock(block);

			block = next;
		}
	}

	HAMON_CXX14_CONSTEXPR iterator
	GetIterator(const_pointer p) const HAMON_NOEXCEPT
	{
		// 仕様では active blocks の数に対して線形なオーダーとなっているが、
		// そのためにはブロック内のポインタとの大小比較が必要となる。
		// ポインタの大小比較は、同一配列中の要素へのポインタ以外の場合は未規定となるため、
		// 厳密に考えると言語仕様上、実装することは不可能なように思える。
		//
		// 提案文書 : P0447R28 では
		// According to Jens Maurer, these difficulties can be bypassed via hidden
		// channels between the library implementation and the compiler.
		// と書かれているが、コンパイラマジックを使わなければ実現できないということか？
		//
		// 現実的には主要なコンパイラにおいて、
		// * ポインタの大小比較をしても、期待通りの動作をしている
		// * ただし、constexprにしようとするとコンパイルエラーになる
		// という状態である。
		//
		// ここで2つの選択肢がある:
		// 1. get_iterator関数はconstexprにしない
		// 2. constexprのときは、size() に対して線形なオーダーとなるようにする
		//
		// 他の関数を全てconstexpr対応した以上、1は避けたいところである。
		// 2は仕様には合致しなくなってしまうが、ランタイムの動作は仕様通りなので大きな問題はなさそうだと判断し、
		// 2の方法を選択した

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			for (auto it = this->Begin(); it != this->End(); ++it)
			{
				if (hamon::to_address(it) == p)
				{
					return it;
				}
			}
		}
		else
#endif
		{
			auto block = this->ActiveBlocks_Begin();
			while (block != this->ActiveBlocks_End())
			{
				if (block->Includes(p))
				{
					return iterator{block, block->GetIndex(p)};
				}

				block = block->m_active_next;
			}
		}
		return iterator{};
	}

private:
	HAMON_CXX14_CONSTEXPR void
	Deallocate(Allocator& allocator) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(m_total_size == 0u);

		this->TrimCapacity(allocator, 0);

		if (m_head != nullptr)
		{
			this->DeallocateBlock(allocator, m_head);
			m_head = nullptr;
		}

		HAMON_ASSERT(m_total_capacity == 0u);
	}

public:
	HAMON_CXX14_CONSTEXPR void
	Destroy(Allocator& allocator) HAMON_NOEXCEPT
	{
		this->Clear(allocator);
		this->Deallocate(allocator);
	}

private:
	HAMON_CXX14_CONSTEXPR void
	Grow(Allocator& allocator)
	{
		this->AllocateBlock(allocator, m_total_capacity);
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_HIVE_DETAIL_HIVE_IMPL_HPP
