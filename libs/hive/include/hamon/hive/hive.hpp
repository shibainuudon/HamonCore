/**
 *	@file	hive.hpp
 *
 *	@brief	hive の定義
 */

#ifndef HAMON_HIVE_HIVE_HPP
#define HAMON_HIVE_HIVE_HPP

#include <hamon/hive/hive_fwd.hpp>
#include <hamon/hive/hive_limits.hpp>
#include <hamon/hive/config.hpp>

#if !defined(HAMON_USE_STD_HIVE)

#include <hamon/hive/detail/hive_impl.hpp>
#include <hamon/hive/detail/hive_traits.hpp>

#include <hamon/algorithm/ranges/sort.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/cpp17_copy_assignable.hpp>
#include <hamon/concepts/detail/cpp17_move_assignable.hpp>
#include <hamon/concepts/detail/cpp17_swappable.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/container/detail/cpp17_copy_insertable.hpp>
#include <hamon/container/detail/cpp17_default_insertable.hpp>
#include <hamon/container/detail/cpp17_emplace_constructible.hpp>
#include <hamon/container/detail/cpp17_move_insertable.hpp>
#include <hamon/functional/cref.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/ranges/adaptors/as_rvalue_view.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/factories/repeat_view.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/stdexcept/length_error.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

// 23.3.9 Class template hive[hive]

template <typename T, typename Allocator/* = hamon::allocator<T>*/>
class hive
{
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;
	using Impl = hamon::detail::hive_impl<T, Allocator>;

public:
	// types
	using value_type             = T;
	using allocator_type         = Allocator;
	using pointer                = typename AllocTraits::pointer;
	using const_pointer          = typename AllocTraits::const_pointer;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = typename AllocTraits::size_type;
	using difference_type        = typename AllocTraits::difference_type;
	using iterator               = typename Impl::iterator;
	using const_iterator         = typename Impl::const_iterator;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

private:
	HAMON_NO_UNIQUE_ADDRESS	allocator_type m_allocator;
	Impl	m_impl;

public:
	// [hive.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	hive() HAMON_NOEXCEPT_IF_EXPR(Allocator())
		: hive(Allocator())
	{}

	HAMON_CXX11_CONSTEXPR explicit
	hive(Allocator const& a) HAMON_NOEXCEPT
		: m_allocator(a)
	{}

	HAMON_CXX11_CONSTEXPR explicit
	hive(hive_limits block_limits)
		: hive(block_limits, Allocator())
	{}

	HAMON_CXX11_CONSTEXPR
	hive(hive_limits block_limits, Allocator const& a)
		: m_allocator(a)
		, m_impl(block_limits)
	{}

	HAMON_CXX14_CONSTEXPR explicit
	hive(size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [hive.cons]/5
		static_assert(hamon::detail::cpp17_default_insertable_t<T, allocator_type>::value, "");

		// [hive.cons]/6
		m_impl.Reserve(m_allocator, n);
		for (size_type i = 0; i < n; ++i)
		{
			m_impl.Emplace(m_allocator);
		}
	}

	HAMON_CXX14_CONSTEXPR
	hive(size_type n, hive_limits block_limits, Allocator const& a = Allocator())
		: m_allocator(a)
		, m_impl(block_limits)
	{
		// [hive.cons]/5
		static_assert(hamon::detail::cpp17_default_insertable_t<T, allocator_type>::value, "");

		// [hive.cons]/6
		m_impl.Reserve(m_allocator, n);
		for (size_type i = 0; i < n; ++i)
		{
			m_impl.Emplace(m_allocator);
		}
	}

	HAMON_CXX14_CONSTEXPR
	hive(size_type n, T const& value, hamon::type_identity_t<Allocator> const& a = Allocator())
		: m_allocator(a)
	{
		// [hive.cons]/8
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");

		// [hive.cons]/9
		m_impl.InsertRange(m_allocator, hamon::views::repeat(hamon::cref(value), n));
	}

	HAMON_CXX14_CONSTEXPR
	hive(size_type n, T const& value, hive_limits block_limits, Allocator const& a = Allocator())
		: m_allocator(a)
		, m_impl(block_limits)
	{
		// [hive.cons]/8
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");

		// [hive.cons]/9
		m_impl.InsertRange(m_allocator, hamon::views::repeat(hamon::cref(value), n));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	hive(InputIterator first, InputIterator last, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [sequence.reqmts]/8
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			T, allocator_type, decltype(*first)>::value, "");

		m_impl.InsertRange(m_allocator, hamon::ranges::make_subrange(first, last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	hive(InputIterator first, InputIterator last, hive_limits block_limits, Allocator const& a = Allocator())
		: m_allocator(a)
		, m_impl(block_limits)
	{
		// [sequence.reqmts]/8
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			T, allocator_type, decltype(*first)>::value, "");

		m_impl.InsertRange(m_allocator, hamon::ranges::make_subrange(first, last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	hive(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [sequence.reqmts]/11
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			T, allocator_type, decltype(*hamon::ranges::begin(rg))>::value, "");

		m_impl.InsertRange(m_allocator, hamon::forward<R>(rg));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	hive(hamon::from_range_t, R&& rg, hive_limits block_limits, Allocator const& a = Allocator())
		: m_allocator(a)
		, m_impl(block_limits)
	{
		// [sequence.reqmts]/11
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			T, allocator_type, decltype(*hamon::ranges::begin(rg))>::value, "");

		m_impl.InsertRange(m_allocator, hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	hive(hive const& x)
		: m_allocator(AllocTraits::select_on_container_copy_construction(x.m_allocator))
		, m_impl(x.block_capacity_limits())
	{
		// [hive.cons]/15
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");

		m_impl.InsertRange(m_allocator, x);	// may throw
	}

	HAMON_CXX11_CONSTEXPR
	hive(hive&& x) HAMON_NOEXCEPT
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	hive(hive const& x, hamon::type_identity_t<Allocator> const& alloc)
		: m_allocator(alloc)
		, m_impl(x.block_capacity_limits())
	{
		// [hive.cons]/15
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");

		m_impl.InsertRange(m_allocator, x);	// may throw
	}

private:
	HAMON_CXX14_CONSTEXPR
	hive(hive&& x, Allocator const& alloc, hamon::true_type) HAMON_NOEXCEPT
		: m_allocator(alloc)
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	hive(hive&& x, Allocator const& alloc, hamon::false_type)
		: m_allocator(alloc)
	{
		// [hive.cons]/18
		static_assert(hamon::detail::cpp17_move_insertable_t<T, allocator_type>::value, "");

		if (hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// 要素をsteal
			m_impl = hamon::move(x.m_impl);
		}
		else
		{
			// アロケータが異なる場合は、
			// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
			m_impl.InsertRange(m_allocator, hamon::views::as_rvalue(x));	// may throw
			// current-limitsは変化しない
		}
	}

public:
	HAMON_CXX14_CONSTEXPR
	hive(hive&& x, hamon::type_identity_t<Allocator> const& alloc)
		HAMON_NOEXCEPT_IF(AllocTraits::is_always_equal::value)	// noexcept as an extension
		: hive(hamon::move(x), alloc, hamon::bool_constant<AllocTraits::is_always_equal::value>{})
	{}

	HAMON_CXX14_CONSTEXPR
	hive(std::initializer_list<T> il, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [hive.cons]/22
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");

		m_impl.InsertRange(m_allocator, il);
	}

	HAMON_CXX14_CONSTEXPR
	hive(std::initializer_list<T> il, hive_limits block_limits, Allocator const& a = Allocator())
		: m_allocator(a)
		, m_impl(block_limits)
	{
		// [hive.cons]/22
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");

		m_impl.InsertRange(m_allocator, il);
	}

	HAMON_CXX20_CONSTEXPR
	~hive()
	{
		m_impl.Destroy(m_allocator);
	}

private:
	HAMON_CXX14_CONSTEXPR void
	op_assign_copy(hive const& x, hamon::true_type)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータを伝播させる場合は、
			// 今のアロケータで確保した要素を破棄しなければいけない
			m_impl.Destroy(m_allocator);

			// アロケータを伝播
			hamon::detail::propagate_allocator_on_copy(m_allocator, x.m_allocator);
		}

		this->op_assign_copy(x, hamon::false_type{});
	}

	HAMON_CXX14_CONSTEXPR void
	op_assign_copy(hive const& x, hamon::false_type)
	{
		// 要素をコピー代入
		m_impl.AssignRange(m_allocator, x);	// may throw
	}

public:
	HAMON_CXX14_CONSTEXPR hive&
	operator=(hive const& x)
	{
		// [hive.cons]/25
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");
		static_assert(hamon::detail::cpp17_copy_assignable_t<T>::value, "");

		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		this->op_assign_copy(x, hamon::bool_constant<
			AllocTraits::propagate_on_container_copy_assignment::value>{});

		// [hive.cons]/26
		// [Note 1: current-limits is unchanged. — end note]

		return *this;
	}

private:
	HAMON_CXX14_CONSTEXPR void
	op_assign_move(hive&& x, hamon::true_type) HAMON_NOEXCEPT
	{
		// 今の要素を破棄
		m_impl.Destroy(m_allocator);

		// アロケータを伝播
		hamon::detail::propagate_allocator_on_move(m_allocator, x.m_allocator);

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR void
	op_assign_move(hive&& x, hamon::false_type)
	{
		// [hive.cons]/28
		static_assert(hamon::detail::cpp17_move_insertable_t<T, allocator_type>::value, "");
		static_assert(hamon::detail::cpp17_move_assignable_t<T>::value, "");

		if (hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			this->op_assign_move(hamon::move(x), hamon::true_type{});
		}
		else
		{
			// アロケータを伝播させない場合は、
			// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
			m_impl.AssignRange(m_allocator, hamon::views::as_rvalue(x));	// may throw
			// current-limitsは変化しない
		}
	}

public:
	HAMON_CXX14_CONSTEXPR hive&
	operator=(hive&& x) HAMON_NOEXCEPT_IF(
		AllocTraits::propagate_on_container_move_assignment::value ||
		AllocTraits::is_always_equal::value)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		this->op_assign_move(hamon::move(x), hamon::bool_constant<
			AllocTraits::propagate_on_container_move_assignment::value ||
			AllocTraits::is_always_equal::value>{});

		return *this;
	}

	HAMON_CXX14_CONSTEXPR hive&
	operator=(std::initializer_list<T> il)
	{
		// [sequence.reqmts]/17
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");
		static_assert(hamon::detail::cpp17_copy_assignable_t<T>::value, "");

		// [sequence.reqmts]/18
		m_impl.AssignRange(m_allocator, il);

		// [sequence.reqmts]/19
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	assign(InputIterator first, InputIterator last)
	{
		// [sequence.reqmts]/58
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			T, allocator_type, decltype(*first)>::value, "");

		m_impl.AssignRange(m_allocator, hamon::ranges::make_subrange(first, last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	assign_range(R&& rg)
	{
		// [sequence.reqmts]/61
		static_assert(hamon::assignable_from_t<T&, hamon::ranges::range_reference_t<R>>::value, "");

		// [sequence.reqmts]/62
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			T, allocator_type, decltype(*hamon::ranges::begin(rg))>::value, "");

		m_impl.AssignRange(m_allocator, hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR void
	assign(size_type n, T const& t)
	{
		// [sequence.reqmts]/67
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");
		static_assert(hamon::detail::cpp17_copy_assignable_t<T>::value, "");

		m_impl.AssignRange(m_allocator, hamon::views::repeat(hamon::cref(t), n));
	}

	HAMON_CXX14_CONSTEXPR void
	assign(std::initializer_list<T> il)
	{
		// [sequence.reqmts]/65
		m_impl.AssignRange(m_allocator, il);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR allocator_type
	get_allocator() const HAMON_NOEXCEPT
	{
		return m_allocator;
	}

	// iterators
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	begin() HAMON_NOEXCEPT
	{
		return m_impl.Begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator
	begin() const HAMON_NOEXCEPT
	{
		return const_iterator(m_impl.Begin());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	end() HAMON_NOEXCEPT
	{
		return m_impl.End();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator
	end() const HAMON_NOEXCEPT
	{
		return const_iterator(m_impl.End());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reverse_iterator
	rbegin() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator
	rbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reverse_iterator
	rend() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator
	rend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator
	cbegin() const HAMON_NOEXCEPT
	{
		return this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator
	cend() const HAMON_NOEXCEPT
	{
		return this->end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator
	crbegin() const HAMON_NOEXCEPT
	{
		return this->rbegin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator
	crend() const HAMON_NOEXCEPT
	{
		return this->rend();
	}

	// [hive.capacity], capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		return this->size() == 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		return m_impl.Size();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type
	max_size() const HAMON_NOEXCEPT
	{
		return m_impl.MaxSize(m_allocator);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type
	capacity() const HAMON_NOEXCEPT
	{
		return m_impl.Capacity();
	}

	HAMON_CXX14_CONSTEXPR void
	reserve(size_type n)
	{
		// [hive.capacity]/3
		if (n <= this->capacity())
		{
			return;
		}

		// [hive.capacity]/5
		if (n > this->max_size())
		{
			hamon::detail::throw_length_error("hive::reserve");
		}

		m_impl.Reserve(m_allocator, n);	// may throw
	}

	HAMON_CXX14_CONSTEXPR void
	shrink_to_fit()
	{
		// [hive.capacity]/8
		static_assert(hamon::detail::cpp17_move_insertable_t<T, allocator_type>::value, "");

		// [hive.capacity]/9
		if (this->capacity() == this->size())
		{
			return;
		}

		hive tmp{this->block_capacity_limits(), this->get_allocator()};
		tmp.reserve(this->size());	// may throw
		tmp.insert_range(hamon::views::as_rvalue(*this));	// may throw
		tmp.swap(*this);
	}

	HAMON_CXX14_CONSTEXPR void
	trim_capacity() HAMON_NOEXCEPT
	{
		// [hive.capacity]/12
		m_impl.TrimCapacity(m_allocator, 0);
	}

	HAMON_CXX14_CONSTEXPR void
	trim_capacity(size_type n) HAMON_NOEXCEPT
	{
		// [hive.capacity]/12
		m_impl.TrimCapacity(m_allocator, n);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hive_limits
	block_capacity_limits() const HAMON_NOEXCEPT
	{
		// [hive.capacity]/15
		return m_impl.CurrentLimits();
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR hive_limits
	block_capacity_default_limits() HAMON_NOEXCEPT
	{
		// [hive.capacity]/17
		return hamon::detail::hive_traits<T>::default_limits();
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR hive_limits
	block_capacity_hard_limits() HAMON_NOEXCEPT
	{
		// [hive.capacity]/19
		return hamon::detail::hive_traits<T>::hard_limits();
	}

	HAMON_CXX14_CONSTEXPR void
	reshape(hive_limits block_limits)
	{
		// [hive.capacity]/21
		static_assert(hamon::detail::cpp17_move_insertable_t<T, allocator_type>::value, "");

		m_impl.Reshape(m_allocator, block_limits);
	}

	// [hive.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(Args&&... args)
	{
		// [hive.modifiers]/1
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			T, allocator_type, Args&&...>::value, "");

		return m_impl.Emplace(m_allocator, hamon::forward<Args>(args)...);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator hint, Args&&... args)
	{
		(void)hint;	// The hint parameter is ignored.
		return this->emplace(hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(T const& x)
	{
		// [hive.modifiers]/6
		return this->emplace(x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(T&& x)
	{
		// [hive.modifiers]/6
		return this->emplace(hamon::move(x));
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, T const& x)
	{
		// [hive.modifiers]/6
		(void)hint;	// [Note 2: The hint parameter is ignored. — end note]
		return this->emplace(x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, T&& x)
	{
		// [hive.modifiers]/6
		(void)hint;	// [Note 2: The hint parameter is ignored. — end note]
		return this->emplace(hamon::move(x));
	}

	HAMON_CXX14_CONSTEXPR void
	insert(std::initializer_list<T> il)
	{
		m_impl.InsertRange(m_allocator, il);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	insert_range(R&& rg)
	{
		// [hive.modifiers]/7
		static_assert(hamon::detail::cpp17_emplace_constructible_t<
			T, allocator_type, decltype(*hamon::ranges::begin(rg))>::value, "");

		m_impl.InsertRange(m_allocator, hamon::forward<R>(rg));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(InputIterator first, InputIterator last)
	{
		// [hive.modifiers]/15
		m_impl.InsertRange(m_allocator, hamon::ranges::make_subrange(first, last));
	}

	HAMON_CXX14_CONSTEXPR void
	insert(size_type n, T const& x)
	{
		// [hive.modifiers]/11
		static_assert(hamon::detail::cpp17_copy_insertable_t<T, allocator_type>::value, "");

		m_impl.InsertRange(m_allocator, hamon::views::repeat(hamon::cref(x), n));
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position)
	{
		return m_impl.Erase(m_allocator, position);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		return m_impl.Erase(m_allocator, first, last);
	}

	HAMON_CXX14_CONSTEXPR void
	swap(hive& x) HAMON_NOEXCEPT_IF(
		AllocTraits::propagate_on_container_swap::value ||
		AllocTraits::is_always_equal::value)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}

		// [hive.modifiers]/18
		m_impl.Swap(x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR void
	clear() HAMON_NOEXCEPT
	{
		m_impl.Clear(m_allocator);
	}

	// [hive.operations], hive operations
	HAMON_CXX14_CONSTEXPR void
	splice(hive& x)
	{
		// [hive.operations]/2
		HAMON_ASSERT(hamon::detail::equals_allocator(get_allocator(), x.get_allocator()));

		// [hive.operations]/3
		if (hamon::addressof(x) == this)
		{
			return;
		}

		// [hive.operations]/4
		if (!x.m_impl.AreActiveBlocksWithinLimits(m_impl.CurrentLimits()))
		{
			hamon::detail::throw_length_error("hive::splice");
		}

		m_impl.Splice(x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR void
	splice(hive&& x)
	{
		this->splice(x);
	}

	template <typename BinaryPredicate = hamon::equal_to<T>>
	HAMON_CXX14_CONSTEXPR size_type
	unique(BinaryPredicate binary_pred = BinaryPredicate())
	{
		// [hive.operations]/8
		auto it = this->begin();
		if (it == this->end())
		{
			return 0;
		}

		size_type result = 0;

		auto prev = it++;
		while (it != this->end())
		{
			if (binary_pred(*it, *prev))
			{
				it = this->erase(it);
				++result;
			}
			else
			{
				prev = it++;
			}
		}

		// [hive.operations]/9
		return result;
	}

	template <typename Compare = hamon::less<T>>
	HAMON_CXX14_CONSTEXPR void
	sort(Compare comp = Compare())
	{
		// [hive.operations]/13
		static_assert(hamon::detail::cpp17_move_insertable_t<T, allocator_type>::value, "");
		static_assert(hamon::detail::cpp17_move_assignable_t<T>::value, "");
		static_assert(hamon::detail::cpp17_swappable_t<T>::value, "");

		// vectorにムーブしてソート後、thisに挿入し直す
		// TODO: Tをムーブするコストが高い場合、vectorにポインタを渡したほうが効率的かもしれない
		hamon::vector<T, Allocator> tmp(hamon::from_range, hamon::views::as_rvalue(*this), m_allocator);	// may throw
		this->clear();
		hamon::ranges::sort(tmp, comp);
		this->insert_range(hamon::views::as_rvalue(tmp));
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	get_iterator(const_pointer p) HAMON_NOEXCEPT
	{
		// [hive.operations]/18
		return m_impl.GetIterator(p);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator
	get_iterator(const_pointer p) const HAMON_NOEXCEPT
	{
		// [hive.operations]/18
		return const_iterator{m_impl.GetIterator(p)};
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<hamon::detail::iter_value_type<InputIterator>>)>
hive(InputIterator, InputIterator, Allocator = Allocator())
->hive<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<hamon::detail::iter_value_type<InputIterator>>)>
hive(InputIterator, InputIterator, hamon::hive_limits, Allocator = Allocator())
->hive<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<hamon::ranges::range_value_t<R>>)>
hive(hamon::from_range_t, R&&, Allocator = Allocator())
->hive<hamon::ranges::range_value_t<R>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<hamon::ranges::range_value_t<R>>)>
hive(hamon::from_range_t, R&&, hive_limits, Allocator = Allocator())
->hive<hamon::ranges::range_value_t<R>, Allocator>;

#endif

template <typename T, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(hive<T, Allocator>& x, hive<T, Allocator>& y)
HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	x.swap(y);
}

}	// namespace hamon

#endif

#endif // HAMON_HIVE_HIVE_HPP
