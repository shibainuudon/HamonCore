/**
 *	@file	inplace_vector.hpp
 *
 *	@brief	inplace_vector の定義
 */

#ifndef HAMON_INPLACE_VECTOR_INPLACE_VECTOR_HPP
#define HAMON_INPLACE_VECTOR_INPLACE_VECTOR_HPP

#include <hamon/inplace_vector/inplace_vector_fwd.hpp>
#include <hamon/inplace_vector/config.hpp>

#if !defined(HAMON_USE_STD_INPLACE_VECTOR)

#include <hamon/inplace_vector/detail/inplace_vector_iterator.hpp>
#include <hamon/inplace_vector/detail/inplace_vector_base.hpp>

#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/ranges/move.hpp>
#include <hamon/algorithm/ranges/rotate.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/new/bad_alloc.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/detail/container_compatible_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

// 23.3.14 Class template inplace_vector[inplace.vector]

template <typename T, hamon::size_t N>
class inplace_vector : private hamon::detail::inplace_vector_base<T, N>
{
public:
	// types:
	using value_type             = T;
	using pointer                = T*;
	using const_pointer          = T const*;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = hamon::size_t;
	using difference_type        = hamon::ptrdiff_t;
	using iterator               = hamon::detail::inplace_vector_iterator_t<T, N, false>;
	using const_iterator         = hamon::detail::inplace_vector_iterator_t<T, N, true>;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

public:
	// [inplace.vector.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	inplace_vector() HAMON_NOEXCEPT
	{}

	HAMON_CXX14_CONSTEXPR explicit
	inplace_vector(size_type n)
	{
		// [inplace.vector.cons]/2
		this->AppendN(n);
	}

	HAMON_CXX14_CONSTEXPR
	inplace_vector(size_type n, T const& value)
	{
		// [inplace.vector.cons]/5
		this->AppendN(n, value);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	inplace_vector(InputIterator first, InputIterator last)
	{
		// [inplace.vector.cons]/7
		this->AppendRange(first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	inplace_vector(hamon::from_range_t, R&& rg)
	{
		// [inplace.vector.cons]/9
		this->AppendRange(hamon::forward<R>(rg));
	}

	// defined in base-class
//	constexpr inplace_vector(inplace_vector const&);

	// defined in base-class
//	constexpr inplace_vector(inplace_vector&&)
//		noexcept(N == 0 || hamon::is_nothrow_move_constructible<T>::value);

	HAMON_CXX11_CONSTEXPR
	inplace_vector(std::initializer_list<T> il)
		: inplace_vector(il.begin(), il.end())
	{}

	// defined in base-class
//	constexpr ~inplace_vector();

	// defined in base-class
//	constexpr inplace_vector& operator=(inplace_vector const& other);

	// defined in base-class
//	constexpr inplace_vector& operator=(inplace_vector&& other)
//		noexcept(N == 0 || (
//			hamon::is_nothrow_move_assignable<T>::value &&
//			hamon::is_nothrow_move_constructible<T>::value));

	HAMON_CXX14_CONSTEXPR inplace_vector&
	operator=(std::initializer_list<T> il)
	{
		this->assign(il.begin(), il.end());
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	assign(InputIterator first, InputIterator last)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(first, last));
		if (n > this->capacity())
		{
			hamon::detail::throw_bad_alloc();
		}

		this->UncheckedAssignN(n, first);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	assign_range(R&& rg)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(rg));
		if (n > this->capacity())
		{
			hamon::detail::throw_bad_alloc();
		}

		this->UncheckedAssignN(n, hamon::ranges::begin(rg));
	}

	HAMON_CXX14_CONSTEXPR void
	assign(size_type n, T const& u)
	{
		if (n > this->capacity())
		{
			hamon::detail::throw_bad_alloc();
		}

		this->UncheckedAssignN(n, u);
	}

	HAMON_CXX14_CONSTEXPR void
	assign(std::initializer_list<T> il)
	{
		this->assign(il.begin(), il.end());
	}

	// iterators
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator begin() HAMON_NOEXCEPT
	{
		return MakeIterator(this->Begin());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator begin() const HAMON_NOEXCEPT
	{
		return MakeConstIterator(this->Begin());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator end() HAMON_NOEXCEPT
	{
		return MakeIterator(this->End());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator end() const HAMON_NOEXCEPT
	{
		return MakeConstIterator(this->End());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reverse_iterator rbegin() HAMON_NOEXCEPT
	{
		return reverse_iterator{this->end()};
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator rbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator{this->end()};
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reverse_iterator rend() HAMON_NOEXCEPT
	{
		return reverse_iterator{this->begin()};
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator rend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator{this->begin()};
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cbegin() const HAMON_NOEXCEPT
	{
		return this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cend() const HAMON_NOEXCEPT
	{
		return this->end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator crbegin() const HAMON_NOEXCEPT
	{
		return this->rbegin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator crend() const HAMON_NOEXCEPT
	{
		return this->rend();
	}

	// [inplace.vector.capacity], size/capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool empty() const HAMON_NOEXCEPT
	{
		return this->size() == 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type size() const HAMON_NOEXCEPT
	{
		return this->Size();
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type max_size() HAMON_NOEXCEPT
	{
		// [inplace.vector.capacity]/1
		return N;
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type capacity() HAMON_NOEXCEPT
	{
		// [inplace.vector.capacity]/1
		return N;
	}

	HAMON_CXX14_CONSTEXPR
	void resize(size_type sz)
	{
		this->Resize(sz);
	}

	HAMON_CXX14_CONSTEXPR
	void resize(size_type sz, T const& c)
	{
		this->Resize(sz, c);
	}

	static HAMON_CXX14_CONSTEXPR
	void reserve(size_type n)
	{
		// [inplace.vector.modifiers]/25
		if (n > capacity())
		{
			hamon::detail::throw_bad_alloc();
		}

		// [inplace.vector.modifiers]/24
		// Do nothing.
	}

	static HAMON_CXX14_CONSTEXPR
	void shrink_to_fit() HAMON_NOEXCEPT
	{
		// [inplace.vector.modifiers]/26
		// Do nothing.
	}

	// element access
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference operator[](size_type n) HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(n < this->size()),
			this->data()[n];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference operator[](size_type n) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(n < this->size()),
			this->data()[n];
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference at(size_type n)
	{
		return
			n < this->size() ?
			this->data()[n] :
			(hamon::detail::throw_out_of_range("inplace_vector::at"), this->data()[n]);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference at(size_type n) const
	{
		return
			n < this->size() ?
			this->data()[n] :
			(hamon::detail::throw_out_of_range("inplace_vector::at"), this->data()[n]);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference front() HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[0];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference front() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[0];
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference back() HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[this->size() - 1];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference back() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[this->size() - 1];
	}

	// [inplace.vector.data], data access
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	T* data() HAMON_NOEXCEPT
	{
		// [inplace.vector.data]/1
		return this->Begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	T const* data() const HAMON_NOEXCEPT
	{
		// [inplace.vector.data]/1
		return this->Begin();
	}

	// [inplace.vector.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	reference emplace_back(Args&&... args)
	{
		this->EmplaceBack(hamon::forward<Args>(args)...);

		// [inplace.vector.modifiers]/4
		return this->back();
	}

	HAMON_CXX14_CONSTEXPR
	reference push_back(T const& x)
	{
		return this->emplace_back(x);
	}

	HAMON_CXX14_CONSTEXPR
	reference push_back(T&& x)
	{
		return this->emplace_back(hamon::move(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	void append_range(R&& rg)
	{
		this->AppendRange(hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR
	void pop_back() HAMON_NOEXCEPT	// noexcept as an extension
	{
		HAMON_ASSERT(!this->empty());
		this->PopBackN(1);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR pointer
	try_emplace_back(Args&&... args)
	{
		// [inplace.vector.modifiers]/11
		if (size() == capacity())
		{
			return nullptr;
		}

		// [inplace.vector.modifiers]/10
		this->UncheckedEmplaceBack(hamon::forward<Args>(args)...);	// may throw

		// [inplace.vector.modifiers]/11
		return hamon::addressof(this->back());
	}

	HAMON_CXX14_CONSTEXPR pointer
	try_push_back(T const& x)
	{
		return this->try_emplace_back(x);
	}

	HAMON_CXX14_CONSTEXPR pointer
	try_push_back(T&& x)
	{
		return this->try_emplace_back(hamon::move(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR ranges::borrowed_iterator_t<R>
	try_append_range(R&& rg)
	{
		auto first = hamon::ranges::begin(rg);
		auto last = hamon::ranges::end(rg);
		for (; first != last; ++first)
		{
			if (this->size() == capacity())
			{
				break;
			}

			this->UncheckedEmplaceBack(*first);	// may throw
		}
		return first;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR reference
	unchecked_emplace_back(Args&&... args)
	{
		// [inplace.vector.modifiers]/20
		HAMON_ASSERT(size() < capacity());

		// [inplace.vector.modifiers]/21
		return *this->try_emplace_back(hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR reference
	unchecked_push_back(T const& x)
	{
		return this->unchecked_emplace_back(x);
	}

	HAMON_CXX14_CONSTEXPR reference
	unchecked_push_back(T&& x)
	{
		return this->unchecked_emplace_back(hamon::move(x));
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(const_iterator position, Args&&... args)
	{
		auto const mid = this->end();
		this->EmplaceBack(hamon::forward<Args>(args)...);	// may throw
		iterator const pos = begin() + (position - begin());
		hamon::ranges::rotate(pos, mid, this->end());	// may throw
		return pos;
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, T const& x)
	{
		return this->emplace(position, x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, T&& x)
	{
		return this->emplace(position, hamon::move(x));
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, size_type n, T const& x)
	{
		auto const mid = this->end();
		this->AppendN(n, x);	// may throw
		iterator const pos = begin() + (position - begin());
		hamon::ranges::rotate(pos, mid, this->end());	// may throw
		return pos;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, InputIterator first, InputIterator last)
	{
		auto const mid = this->end();
		this->AppendRange(first, last);	// may throw
		iterator const pos = begin() + (position - begin());
		hamon::ranges::rotate(pos, mid, this->end());	// may throw
		return pos;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR iterator
	insert_range(const_iterator position, R&& rg)
	{
		auto const mid = this->end();
		this->AppendRange(hamon::forward<R>(rg));	// may throw
		iterator const pos = begin() + (position - begin());
		hamon::ranges::rotate(pos, mid, this->end());	// may throw
		return pos;
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, std::initializer_list<T> il)
	{
		return this->insert(position, il.begin(), il.end());
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position)
	{
		return this->erase(position, position + 1);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		// [inplace.vector.modifiers]/27
		auto const n = hamon::ranges::distance(first, last);
		iterator const pos = begin() + (first - begin());
		hamon::ranges::move(pos + n, this->end(), pos);	// may throw
		this->PopBackN(static_cast<size_type>(n));
		return pos;
	}

	HAMON_CXX14_CONSTEXPR
	void swap(inplace_vector& x)
		HAMON_NOEXCEPT_IF(N == 0 || (
			hamon::is_nothrow_swappable<T>::value &&
			hamon::is_nothrow_move_constructible<T>::value))
	{
		auto tmp = hamon::move(x);
		x = hamon::move(*this);
		*this = tmp;
	}

	HAMON_CXX14_CONSTEXPR
	void clear() HAMON_NOEXCEPT
	{
		this->PopBackN(this->Size());
	}

private:
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	friend bool operator==(inplace_vector const& x, inplace_vector const& y)
	{
		return x.size() == y.size() &&
			hamon::equal(x.begin(), x.end(), y.begin());
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

	template <typename U = T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	friend hamon::detail::synth_three_way_result<U>
	operator<=>(inplace_vector const& x, inplace_vector const& y)
	{
		return hamon::lexicographical_compare_three_way(
			x.begin(), x.end(),
			y.begin(), y.end(),
			hamon::detail::synth_three_way);
	}

#else

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	friend bool operator!=(inplace_vector const& x, inplace_vector const& y)
	{
		return !(x == y);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	friend bool operator<(inplace_vector const& x, inplace_vector const& y)
	{
		return hamon::lexicographical_compare(
			x.begin(), x.end(),
			y.begin(), y.end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	friend bool operator>(inplace_vector const& x, inplace_vector const& y)
	{
		return y < x;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	friend bool operator<=(inplace_vector const& x, inplace_vector const& y)
	{
		return !(x > y);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	friend bool operator>=(inplace_vector const& x, inplace_vector const& y)
	{
		return !(x < y);
	}

#endif

	HAMON_CXX14_CONSTEXPR friend
	void swap(inplace_vector& x, inplace_vector& y)
		HAMON_NOEXCEPT_IF(N == 0 || (
			hamon::is_nothrow_swappable<T>::value &&
			hamon::is_nothrow_move_constructible<T>::value))
	{
		x.swap(y);
	}

private:
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void EmplaceBack(Args&&... args)
	{
		if (this->size() == this->capacity())
		{
			hamon::detail::throw_bad_alloc();
		}

		this->UncheckedEmplaceBack(hamon::forward<Args>(args)...);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void AppendN(size_type n, Args&&... args)
	{
		if (this->size() + n > this->capacity())
		{
			hamon::detail::throw_bad_alloc();
		}

		this->UncheckedAppendN(n, hamon::forward<Args>(args)...);
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void AppendRange(Iterator first, Sentinel last)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(first, last));
		if (this->size() + n > this->capacity())
		{
			hamon::detail::throw_bad_alloc();
		}

		this->UncheckedAppendN(n, first);
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR void AppendRange(Range&& rg)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(rg));
		if (this->size() + n > this->capacity())
		{
			hamon::detail::throw_bad_alloc();
		}

		this->UncheckedAppendN(n, hamon::ranges::begin(rg));
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void Resize(size_type sz, Args&&... args)
	{
		if (sz > this->capacity())
		{
			hamon::detail::throw_bad_alloc();
		}

		this->UncheckedResize(sz, hamon::forward<Args>(args)...);
	}

	HAMON_CXX14_CONSTEXPR iterator
	MakeIterator(T* ptr) HAMON_NOEXCEPT
	{
#if defined(HAMON_INPLACE_VECTOR_ITERATOR_DEBUG)
		return iterator{this->Begin(), ptr - this->Begin()};
#else
		return ptr;
#endif
	}

	HAMON_CXX11_CONSTEXPR const_iterator
	MakeConstIterator(T const* ptr) const HAMON_NOEXCEPT
	{
#if defined(HAMON_INPLACE_VECTOR_ITERATOR_DEBUG)
		return const_iterator{this->Begin(), ptr - this->Begin()};
#else
		return ptr;
#endif
	}
};

}	// namespace hamon

HAMON_WARNING_POP()

#endif	// !defined(HAMON_USE_STD_INPLACE_VECTOR)

#endif // HAMON_INPLACE_VECTOR_INPLACE_VECTOR_HPP
