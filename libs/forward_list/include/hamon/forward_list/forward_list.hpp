/**
 *	@file	forward_list.hpp
 *
 *	@brief	forward_list の定義
 */

#ifndef HAMON_FORWARD_LIST_FORWARD_LIST_HPP
#define HAMON_FORWARD_LIST_FORWARD_LIST_HPP

#include <hamon/forward_list/forward_list_fwd.hpp>
#include <hamon/forward_list/config.hpp>

#if !defined(HAMON_USE_STD_FORWARD_LIST)

#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/container/detail/forward_list_impl.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/cpp17_default_insertable.hpp>
#include <hamon/container/detail/cpp17_move_insertable.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/make_move_iterator.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

template <typename T, typename Allocator>
class forward_list
{
private:
	using AllocTraits     = hamon::allocator_traits<Allocator>;
	using Impl            = hamon::detail::forward_list_impl<T, Allocator>;

public:
	// types
	using value_type      = T;
	using allocator_type  = Allocator;
	using pointer         = typename hamon::allocator_traits<Allocator>::pointer;
	using const_pointer   = typename hamon::allocator_traits<Allocator>::const_pointer;
	using reference       = value_type&;
	using const_reference = value_type const&;
	using size_type       = typename Impl::size_type;
	using difference_type = typename Impl::difference_type;
	using iterator        = typename Impl::iterator;
	using const_iterator  = typename Impl::const_iterator;

	static_assert(hamon::is_same<typename allocator_type::value_type, value_type>::value, "[container.alloc.reqmts]/5");

private:
	HAMON_NO_UNIQUE_ADDRESS	Allocator	m_allocator;
	Impl	m_impl{};

public:
	// [forward.list.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	forward_list() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_default_constructible<Allocator>::value)
		: forward_list(Allocator())
	{}

	HAMON_CXX11_CONSTEXPR explicit
	forward_list(Allocator const& a) HAMON_NOEXCEPT	// noexcept as an extension
		: m_allocator(a)
	{
		// [forward.list.cons]/1
	}

	HAMON_CXX14_CONSTEXPR explicit
	forward_list(size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/3
		static_assert(hamon::detail::cpp17_default_insertable_t<value_type, allocator_type>::value, "");

		// [forward.list.cons]/4
		m_impl.insert_n_after(m_allocator, this->before_begin(), n);
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(size_type n, T const& value, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/7
		m_impl.insert_n_after(m_allocator, this->before_begin(), n, value);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	forward_list(InputIterator first, InputIterator last, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/9
		m_impl.insert_range_after(m_allocator, this->before_begin(), first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	forward_list(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [forward.list.cons]/11
		m_impl.insert_range_after(m_allocator, this->before_begin(), hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list const& x)
		: m_allocator(AllocTraits::select_on_container_copy_construction(x.m_allocator))
	{
		m_impl.insert_range_after(m_allocator, this->before_begin(), x);
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list&& x) HAMON_NOEXCEPT	// noexcept as an extension
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list const& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		m_impl.insert_range_after(m_allocator, this->before_begin(), x);
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(forward_list&& x, hamon::type_identity_t<Allocator> const& a)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			AllocTraits::is_always_equal::value)
		: m_allocator(a)
	{
		// [container.alloc.reqmts]/18
		static_assert(hamon::detail::cpp17_move_insertable_t<value_type, allocator_type>::value, "");

		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータが異なる場合は、
			// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
			m_impl.insert_range_after(m_allocator, this->before_begin(),
				hamon::make_move_iterator(hamon::ranges::begin(x)),
				hamon::make_move_iterator(hamon::ranges::end(x)));
			return;
		}

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR
	forward_list(std::initializer_list<T> il, Allocator const& a = Allocator())
		: forward_list(il.begin(), il.end(), a)
	{}

	HAMON_CXX20_CONSTEXPR
	~forward_list()
	{
		this->clear();
	}

	HAMON_CXX14_CONSTEXPR
	forward_list& operator=(forward_list const& x)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (AllocTraits::propagate_on_container_copy_assignment::value)
#else
		if           (AllocTraits::propagate_on_container_copy_assignment::value)
#endif
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させる場合は、
				// 今のアロケータで確保した要素を破棄しなければいけない
				this->clear();

				// アロケータを伝播
				hamon::detail::propagate_allocator_on_copy(m_allocator, x.m_allocator);
			}
		}

		// 要素をコピー代入
		m_impl.assign_range(m_allocator, x);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR
	forward_list& operator=(forward_list&& x)
		HAMON_NOEXCEPT_IF(AllocTraits::is_always_equal::value)
	{
		// [container.alloc.reqmts]/26
		static_assert(AllocTraits::propagate_on_container_move_assignment::value ||
			hamon::detail::cpp17_move_insertable_t<value_type, allocator_type>::value, "");

		if (hamon::addressof(x) == this)
		{
			return *this;
		}

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (!AllocTraits::propagate_on_container_move_assignment::value)
#else
		if           (!AllocTraits::propagate_on_container_move_assignment::value)
#endif
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させない場合は、
				// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
				m_impl.assign_range(m_allocator,
					hamon::make_move_iterator(hamon::ranges::begin(x)),
					hamon::make_move_iterator(hamon::ranges::end(x)));
				return *this;
			}
		}

		// 今の要素を破棄
		this->clear();

		// アロケータを伝播
		hamon::detail::propagate_allocator_on_move(m_allocator, x.m_allocator);

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR
	forward_list& operator=(std::initializer_list<T> il)
	{
		// [sequence.reqmts]/17
		this->assign(il.begin(), il.end());

		// [sequence.reqmts]/18
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	void assign(InputIterator first, InputIterator last)
	{
		// [sequence.reqmts]/58
		m_impl.assign_range(m_allocator, first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	void assign_range(R&& rg)
	{
		// [sequence.reqmts]/62
		m_impl.assign_range(m_allocator, hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	void assign(size_type n, T const& t)
	{
		// [sequence.reqmts]/66
		this->clear();
		this->insert_after(before_begin(), n, t);
	}

	HAMON_CXX14_CONSTEXPR
	void assign(std::initializer_list<T> il)
	{
		// [sequence.reqmts]/63
		this->assign(il.begin(), il.end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	allocator_type get_allocator() const HAMON_NOEXCEPT
	{
		return static_cast<allocator_type>(m_allocator);
	}

	// [forward.list.iter], iterators
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator before_begin() HAMON_NOEXCEPT
	{
		// [forward.list.iter]/2
		return m_impl.before_begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator before_begin() const HAMON_NOEXCEPT
	{
		// [forward.list.iter]/2
		return m_impl.before_begin();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator begin() HAMON_NOEXCEPT
	{
		return m_impl.begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator begin() const HAMON_NOEXCEPT
	{
		return m_impl.begin();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator end() HAMON_NOEXCEPT
	{
		return m_impl.end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator end() const HAMON_NOEXCEPT
	{
		return m_impl.end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cbegin() const HAMON_NOEXCEPT
	{
		return this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cbefore_begin() const HAMON_NOEXCEPT
	{
		// [forward.list.iter]/1
		return this->before_begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cend() const HAMON_NOEXCEPT
	{
		return this->end();
	}

	// capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool empty() const HAMON_NOEXCEPT
	{
		return this->begin() == this->end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type max_size() const HAMON_NOEXCEPT
	{
		return m_impl.max_size(m_allocator);
	}

	// [forward.list.access], element access
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference front() HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.access]/1
		return *this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference front() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.access]/1
		return *this->begin();
	}

	// [forward.list.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	reference emplace_front(Args&&... args)
	{
		// [forward.list.modifiers]/2
		m_impl.insert_after(m_allocator, this->before_begin(), hamon::forward<Args>(args)...);
		return front();
	}

	HAMON_CXX14_CONSTEXPR
	void push_front(T const& x)
	{
		// [forward.list.modifiers]/3
		m_impl.insert_after(m_allocator, this->before_begin(), x);
	}

	HAMON_CXX14_CONSTEXPR
	void push_front(T&& x)
	{
		// [sequence.reqmts]/94
		static_assert(hamon::detail::cpp17_move_insertable_t<value_type, allocator_type>::value, "");

		// [forward.list.modifiers]/3
		m_impl.insert_after(m_allocator, this->before_begin(), hamon::move(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	void prepend_range(R&& rg)
	{
		// [forward.list.modifiers]/4
		m_impl.insert_range_after(m_allocator, this->before_begin(), hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	void pop_front() HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.modifiers]/5
		this->erase_after(this->before_begin());
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	iterator emplace_after(const_iterator position, Args&&... args)
	{
		// [forward.list.modifiers]/23
		return m_impl.insert_after(m_allocator, position, hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, T const& x)
	{
		// [forward.list.modifiers]/7
		return m_impl.insert_after(m_allocator, position, x);
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, T&& x)
	{
		// [forward.list.modifiers]/9
		static_assert(hamon::detail::cpp17_move_insertable_t<value_type, allocator_type>::value, "");

		// [forward.list.modifiers]/10
		return m_impl.insert_after(m_allocator, position, hamon::move(x));
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, size_type n, T const& x)
	{
		// [forward.list.modifiers]/13
		return m_impl.insert_n_after(m_allocator, position, n, x);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, InputIterator first, InputIterator last)
	{
		// [forward.list.modifiers]/16
		return m_impl.insert_range_after(m_allocator, position, first, last);
	}

	HAMON_CXX14_CONSTEXPR
	iterator insert_after(const_iterator position, std::initializer_list<T> il)
	{
		// [forward.list.modifiers]/21
		return this->insert_after(position, il.begin(), il.end());
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	iterator insert_range_after(const_iterator position, R&& rg)
	{
		// [forward.list.modifiers]/19
		return m_impl.insert_range_after(m_allocator, position, hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	iterator erase_after(const_iterator position)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.modifiers]/26
		// [forward.list.modifiers]/27
		return m_impl.erase_after(m_allocator, position);
	}

	HAMON_CXX14_CONSTEXPR
	iterator erase_after(const_iterator position, const_iterator last)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.modifiers]/30
		// [forward.list.modifiers]/31
		return m_impl.erase_range_after(m_allocator, position, last);
	}

	HAMON_CXX14_CONSTEXPR
	void swap(forward_list& x)
		HAMON_NOEXCEPT_IF(AllocTraits::is_always_equal::value)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}
		hamon::swap(m_impl, x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR
	void resize(size_type sz)
	{
		// [forward.list.modifiers]/33
		static_assert(hamon::detail::cpp17_default_insertable_t<value_type, allocator_type>::value, "");

		// [forward.list.modifiers]/34
		m_impl.resize(m_allocator, sz);
	}

	HAMON_CXX14_CONSTEXPR
	void resize(size_type sz, value_type const& c)
	{
		// [forward.list.modifiers]/36
		m_impl.resize(m_allocator, sz, c);
	}

	HAMON_CXX14_CONSTEXPR
	void clear() HAMON_NOEXCEPT
	{
		// [forward.list.modifiers]/37
		m_impl.clear(m_allocator);
	}

	// [forward.list.ops], forward_list operations
	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list& x)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/3
		this->splice_after(position, x, x.before_begin(), x.end());
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list&& x)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/3
		this->splice_after(position, x, x.before_begin(), x.end());
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list& x, const_iterator i)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/6
		HAMON_ASSERT(hamon::detail::equals_allocator(m_allocator, x.m_allocator));
		// TODO
		// * position が before_begin() または [begin(), end()) の間接参照可能なイテレータであること
		// * i に続くイテレータが x 内の間接参照可能なイテレータであること

		// [forward.list.ops]/7
		m_impl.splice_after(position, i);
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list&& x, const_iterator i)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/7
		this->splice_after(position, x, i);
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list& x, const_iterator first, const_iterator last)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/10
		HAMON_ASSERT(hamon::detail::equals_allocator(m_allocator, x.m_allocator));
		// TODO
		// * position が before_begin() または [begin(), end()) の間接参照可能なイテレータであること
		// * (first, last) が x の有効な範囲で、全てのイテレータが間接参照可能であること
		// * position が (first, last) の範囲内のイテレータでないこと

		// [forward.list.ops]/11
		m_impl.splice_range_after(position, first, last);
	}

	HAMON_CXX14_CONSTEXPR
	void splice_after(const_iterator position, forward_list&& x, const_iterator first, const_iterator last)
		HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [forward.list.ops]/11
		this->splice_after(position, x, first, last);
	}

	HAMON_CXX14_CONSTEXPR
	size_type remove(T const& value)
	{
		// [forward.list.ops]/13
		// [forward.list.ops]/14
		return this->remove_if([&](T const& x) { return x == value; });
	}

	template <typename Predicate>
	HAMON_CXX14_CONSTEXPR
	size_type remove_if(Predicate pred)
	{
		// [forward.list.ops]/13
		// [forward.list.ops]/14
		return static_cast<size_type>(m_impl.remove_if(m_allocator, pred));
	}

	HAMON_CXX14_CONSTEXPR
	size_type unique()
	{
		// [forward.list.ops]/18
		return this->unique(hamon::equal_to<>{});
	}

	template <typename BinaryPredicate>
	HAMON_CXX14_CONSTEXPR
	size_type unique(BinaryPredicate binary_pred)
	{
		// [forward.list.ops]/20
		// [forward.list.ops]/21
		return static_cast<size_type>(m_impl.unique(m_allocator, binary_pred));
	}

	HAMON_CXX14_CONSTEXPR
	void merge(forward_list& x)
	{
		// [forward.list.ops]/24
		this->merge(x, hamon::less<>{});
	}

	HAMON_CXX14_CONSTEXPR
	void merge(forward_list&& x)
	{
		// [forward.list.ops]/24
		this->merge(hamon::move(x), hamon::less<>{});
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR
	void merge(forward_list& x, Compare comp)
	{
		// [forward.list.ops]/26
		if (hamon::addressof(x) == this)
		{
			return;
		}

		m_impl.merge(x.m_impl, comp);
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR
	void merge(forward_list&& x, Compare comp)
	{
		// [forward.list.ops]/26
		this->merge(x, comp);
	}

	HAMON_CXX14_CONSTEXPR
	void sort()
	{
		// [forward.list.ops]/29
		this->sort(hamon::less<>{});
	}

	template <typename Compare>
	HAMON_CXX14_CONSTEXPR
	void sort(Compare comp)
	{
		// [forward.list.ops]/29
		m_impl.sort(comp);
	}

	HAMON_CXX14_CONSTEXPR
	void reverse() HAMON_NOEXCEPT
	{
		// [forward.list.ops]/32
		m_impl.reverse();
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator = hamon::allocator<hamon::detail::iter_value_type<InputIterator>>>
forward_list(InputIterator, InputIterator, Allocator = Allocator())
	->forward_list<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator = hamon::allocator<ranges::range_value_t<R>>>
forward_list(hamon::from_range_t, R&&, Allocator = Allocator())
	->forward_list<ranges::range_value_t<R>, Allocator>;

#endif

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator==(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return hamon::equal(x.begin(), x.end(), y.begin(), y.end());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::detail::synth_three_way_result<T>
operator<=>(forward_list<T, Allocator> const&x, forward_list<T, Allocator> const&y)
{
	return hamon::lexicographical_compare_three_way(
		x.begin(), x.end(),
		y.begin(), y.end(),
		hamon::detail::synth_three_way);
}

#else

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator!=(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return !(x == y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator<(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return hamon::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end());
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator>(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return y < x;
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator<=(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return !(x > y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator>=(forward_list<T, Allocator> const& x, forward_list<T, Allocator> const& y)
{
	return !(x < y);
}

#endif

template <typename T, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(forward_list<T, Allocator>& x, forward_list<T, Allocator>& y)
	HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	x.swap(y);
}

}	// namespace hamon

#endif

#endif // HAMON_FORWARD_LIST_FORWARD_LIST_HPP
