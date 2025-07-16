/**
 *	@file	vector.hpp
 *
 *	@brief	vector の定義
 */

#ifndef HAMON_VECTOR_VECTOR_HPP
#define HAMON_VECTOR_VECTOR_HPP

#include <hamon/vector/vector_fwd.hpp>
#include <hamon/vector/config.hpp>

#if !defined(HAMON_USE_STD_VECTOR)

#include <hamon/vector/detail/vector_iterator.hpp>
#include <hamon/vector/detail/vector_impl.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/functional/cref.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/make_move_iterator.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/factories/repeat_view.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

#if 0

// [vector.bool], specialization of vector for bool
// [vector.bool.pspc], partial class template specialization vector<bool, Allocator>
template <typename Allocator>
class vector<bool, Allocator>;

template <typename T>
constexpr bool is_vector_bool_reference = see below;          // exposition only

// hash support
template <typename T>
struct hash;

template <typename Allocator>
struct hash<vector<bool, Allocator>>;

// [vector.bool.fmt], formatter specialization for vector<bool>
template <typename T, typename charT>
requires is_vector_bool_reference<T>
struct formatter<T, charT>;

#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

// TODO:
// * vector<bool>の特殊化

// 24.3.11 Class template vector[vector]

template <typename T, typename Allocator>
class vector
{
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;

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
	using iterator               = hamon::detail::vector_iterator<T, Allocator, false>;
	using const_iterator         = hamon::detail::vector_iterator<T, Allocator, true>;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

	static_assert(hamon::is_same<typename allocator_type::value_type, value_type>::value, "[container.alloc.reqmts]/5");

private:
	using Impl = hamon::detail::vector_impl<T, Allocator>;

	HAMON_NO_UNIQUE_ADDRESS	allocator_type m_allocator;
	Impl	m_impl;

public:
	// [vector.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	vector() HAMON_NOEXCEPT_IF_EXPR(Allocator())
		: vector(Allocator())
	{}

	HAMON_CXX11_CONSTEXPR explicit
	vector(Allocator const& a) HAMON_NOEXCEPT
		: m_allocator(a)
	{
		// [vector.cons]/1
	}

	HAMON_CXX14_CONSTEXPR explicit
	vector(size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// TODO
		// [vector.cons]/3
		// Preconditions: T is Cpp17DefaultInsertable into *this.

		// [vector.cons]/4
		this->resize(n);
	}

	HAMON_CXX14_CONSTEXPR
	vector(size_type n, T const& value, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// TODO
		// [vector.cons]/6
		// Preconditions: T is Cpp17CopyInsertable into *this.

		// [vector.cons]/7
		this->resize(n, value);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	vector(InputIterator first, InputIterator last, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [vector.cons]/9,10
		this->insert(this->cend(), hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	vector(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [vector.cons]/11,12
		this->append_range(hamon::forward<R>(rg));
	}

	HAMON_CXX11_CONSTEXPR
	vector(vector const& x)
		: vector(x, AllocTraits::select_on_container_copy_construction(x.m_allocator))
	{}

	HAMON_CXX11_CONSTEXPR
	vector(vector&& x) HAMON_NOEXCEPT
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	vector(vector const& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		this->append_range(x);
	}

	HAMON_CXX14_CONSTEXPR
	vector(vector&& x, hamon::type_identity_t<Allocator> const& a)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::allocator_traits<Allocator>::is_always_equal::value)
		: m_allocator(a)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			// アロケータが異なる場合は、
			// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
			m_impl.Reserve(m_allocator, x.size());
			m_impl.AppendMoveIfNoexceptN(m_allocator, x.begin(), x.size());
			return;
		}

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);
	}

	HAMON_CXX11_CONSTEXPR
	vector(std::initializer_list<T> il, Allocator const& a = Allocator())
		: vector(il.begin(), il.end(), a)
	{}

	HAMON_CXX20_CONSTEXPR
	~vector()
	{
		m_impl.Destroy(m_allocator);
	}

	HAMON_CXX14_CONSTEXPR vector&
	operator=(vector const& x)
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
				m_impl.Destroy(m_allocator);

				// アロケータを伝播
				hamon::detail::propagate_allocator_on_copy(m_allocator, x.m_allocator);
			}
		}

		// 要素をコピー代入
		m_impl.AssignIter(m_allocator, x.begin(), x.end());

		return *this;
	}

	HAMON_CXX14_CONSTEXPR vector&
	operator=(vector&& x) HAMON_NOEXCEPT_IF(
		AllocTraits::propagate_on_container_move_assignment::value ||
		AllocTraits::is_always_equal::value)
	{
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
				m_impl.AssignIter(m_allocator,
					hamon::make_move_iterator(hamon::ranges::begin(x)),
					hamon::make_move_iterator(hamon::ranges::end(x)));	// may throw
				return *this;
			}
		}

		// 今の要素を破棄
		m_impl.Destroy(m_allocator);

		// アロケータを伝播
		hamon::detail::propagate_allocator_on_move(m_allocator, x.m_allocator);

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR vector&
	operator=(std::initializer_list<T> il)
	{
		this->assign(il);
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	assign(InputIterator first, InputIterator last)
	{
		m_impl.AssignIter(m_allocator, hamon::move(first), hamon::move(last));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	assign_range(R&& rg)
	{
		m_impl.AssignRange(m_allocator, hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR void
	assign(size_type n, T const& u)
	{
		m_impl.AssignRange(m_allocator, hamon::views::repeat(hamon::cref(u), n));
	}

	HAMON_CXX14_CONSTEXPR void
	assign(std::initializer_list<T> il)
	{
		this->assign(il.begin(), il.end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR allocator_type
	get_allocator() const HAMON_NOEXCEPT
	{
		return m_allocator;
	}

	// iterators
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator begin() HAMON_NOEXCEPT
	{
		return iterator(m_impl.Begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator begin() const HAMON_NOEXCEPT
	{
		return const_iterator(m_impl.Begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator end() HAMON_NOEXCEPT
	{
		return iterator(m_impl.End());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator end() const HAMON_NOEXCEPT
	{
		return const_iterator(m_impl.End());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator rbegin() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator rbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator rend() HAMON_NOEXCEPT
	{
		return reverse_iterator(this->begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator rend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator cbegin() const HAMON_NOEXCEPT
	{
		return this->begin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator cend() const HAMON_NOEXCEPT
	{
		return this->end();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator crbegin() const HAMON_NOEXCEPT
	{
		return this->rbegin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator crend() const HAMON_NOEXCEPT
	{
		return this->rend();
	}

	// [vector.capacity], capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool empty() const HAMON_NOEXCEPT
	{
		return this->size() == 0;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type size() const HAMON_NOEXCEPT
	{
		return m_impl.Size();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type max_size() const HAMON_NOEXCEPT
	{
		return m_impl.MaxSize(m_allocator);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type capacity() const HAMON_NOEXCEPT
	{
		// [vector.capacity]/1
		return m_impl.Capacity();
	}

	HAMON_CXX14_CONSTEXPR void resize(size_type sz)
	{
		m_impl.Resize(m_allocator, sz);
	}

	HAMON_CXX14_CONSTEXPR void resize(size_type sz, T const& c)
	{
		m_impl.Resize(m_allocator, sz, c);
	}

	HAMON_CXX14_CONSTEXPR void reserve(size_type n)
	{
		m_impl.Reserve(m_allocator, n);
	}

	HAMON_CXX14_CONSTEXPR void shrink_to_fit()
	{
		if (this->size() < this->capacity())
		{
			m_impl.Reallocate(m_allocator, this->size());
		}
	}

	// element access
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference operator[](size_type n)
	{
		return
			HAMON_ASSERT(n < this->size()),
			this->data()[n];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference operator[](size_type n) const
	{
		return
			HAMON_ASSERT(n < this->size()),
			this->data()[n];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference at(size_type n)
	{
		return
			n < this->size() ?
			this->data()[n] :
			(hamon::detail::throw_out_of_range("vector::at"), this->data()[n]);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference at(size_type n) const
	{
		return
			n < this->size() ?
			this->data()[n] :
			(hamon::detail::throw_out_of_range("vector::at"), this->data()[n]);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference front()
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[0];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference front() const
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[0];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference back()
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[this->size() - 1];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference back() const
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[this->size() - 1];
	}

	// [vector.data], data access
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR T* data() HAMON_NOEXCEPT
	{
		return m_impl.Begin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR T const* data() const HAMON_NOEXCEPT
	{
		return m_impl.Begin();
	}

	// [vector.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR reference emplace_back(Args&&... args)
	{
		auto it = this->emplace(this->cend(), hamon::forward<Args>(args)...);
		return *it;
	}

	HAMON_CXX14_CONSTEXPR void push_back(T const& x)
	{
		this->emplace_back(x);
	}

	HAMON_CXX14_CONSTEXPR void push_back(T&& x)
	{
		this->emplace_back(hamon::move(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void append_range(R&& rg)
	{
		this->insert_range(this->cend(), hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR void pop_back()
	{
		m_impl.PopBackN(m_allocator, 1);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(const_iterator position, Args&&... args)
	{
		auto const pos_offset = position - this->begin();
		m_impl.Emplace(m_allocator, pos_offset, hamon::forward<Args>(args)...);
		return this->begin() + pos_offset;
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
		auto const pos_offset = position - this->begin();
		m_impl.InsertRange(m_allocator, pos_offset, hamon::views::repeat(hamon::cref(x), n));
		return this->begin() + pos_offset;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, InputIterator first, InputIterator last)
	{
		auto const pos_offset = position - this->begin();
		m_impl.InsertIter(m_allocator, pos_offset, hamon::move(first), hamon::move(last));
		return this->begin() + pos_offset;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR iterator
	insert_range(const_iterator position, R&& rg)
	{
		auto const pos_offset = position - this->begin();
		m_impl.InsertRange(m_allocator, pos_offset, hamon::forward<R>(rg));
		return this->begin() + pos_offset;
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
		auto const pos_offset = first - this->begin();
		m_impl.EraseN(m_allocator, pos_offset, static_cast<size_type>(last - first));
		return this->begin() + pos_offset;
	}

	HAMON_CXX14_CONSTEXPR void
	swap(vector& x) HAMON_NOEXCEPT_IF(
		AllocTraits::propagate_on_container_swap::value ||
		AllocTraits::is_always_equal::value)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}
		m_impl.Swap(x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR void clear() HAMON_NOEXCEPT
	{
		m_impl.Clear(m_allocator);
	}
};

HAMON_WARNING_POP()

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator = hamon::allocator<hamon::detail::iter_value_type<InputIterator>>>
vector(InputIterator, InputIterator, Allocator = Allocator())
	->vector<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator = hamon::allocator<hamon::ranges::range_value_t<R>>>
vector(hamon::from_range_t, R&&, Allocator = Allocator())
	->vector<hamon::ranges::range_value_t<R>, Allocator>;

#endif

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator==(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return x.size() == y.size() &&
		hamon::equal(x.begin(), x.end(), y.begin());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR hamon::detail::synth_three_way_result<T>
operator<=>(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return hamon::lexicographical_compare_three_way(
		x.begin(), x.end(),
		y.begin(), y.end(),
		hamon::detail::synth_three_way);
}

#else

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator!=(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return !(x == y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return hamon::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end());
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return y < x;
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<=(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return !(x > y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>=(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return !(x < y);
}

#endif

template <typename T, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(vector<T, Allocator>& x, vector<T, Allocator>& y)
HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	x.swap(y);
}

}	// namespace hamon

#include <hamon/serialization/detail/save_vector.hpp>
#include <hamon/serialization/detail/load_vector.hpp>

namespace hamon
{

template <typename Archive, typename T>
void save_value(Archive& oa, hamon::vector<T> const& t)
{
	hamon::serialization::detail::save_vector(oa, t);
}

template <typename Archive, typename T>
void load_value(Archive& ia, hamon::vector<T>& t)
{
	t.clear();
	hamon::serialization::detail::load_vector(ia, t);
}

}	// namespace hamon

#endif

#endif // HAMON_VECTOR_VECTOR_HPP
