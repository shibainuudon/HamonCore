/**
 *	@file	basic_string.hpp
 *
 *	@brief	basic_string の定義
 */

#ifndef HAMON_STRING_BASIC_STRING_HPP
#define HAMON_STRING_BASIC_STRING_HPP

#include <hamon/string/config.hpp>
#include <hamon/ranges/from_range_t.hpp>

#if defined(HAMON_USE_STD_STRING)

#include <string>

namespace hamon
{

using std::basic_string;

}	// namespace hamon

#else

#include <hamon/string/char_traits.hpp>
#include <hamon/string_view.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/concepts/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/detail/is_integer_like.hpp>
#include <hamon/ranges/detail/container_compatible_range.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/stdexcept/length_error.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/assert.hpp>
#include <initializer_list>
#include <ios>		// ios_base, streamsize
#include <istream>	// basic_istream
#include <ostream>	// basic_ostream
#include <memory>	// allocator, allocator_traits
#include <cctype>	// isspace

namespace hamon
{

namespace detail
{

template <typename Alloc, typename = void, typename = void>
struct is_allocator : hamon::false_type {};

template <typename A>
struct is_allocator<A,
	hamon::void_t<typename A::value_type>,	// [container.reqmts]/69.1
	hamon::void_t<decltype(hamon::declval<A&>().allocate(hamon::size_t{}))>>// [container.reqmts]/69.2
	: hamon::true_type {};

}	// namespace detail

template <typename CharT, typename Traits = hamon::char_traits<CharT>, typename Allocator = std::allocator<CharT>>
class basic_string
{
private:
	static_assert(hamon::is_same<CharT, typename Allocator::value_type>::value, "[string.require]/3 Note 1");
	static_assert(hamon::is_same<CharT, typename Traits::char_type>::value, "[string.require]/3 Note 2");

	using AllocTraits = std::allocator_traits<Allocator>;
	using StringView = hamon::basic_string_view<CharT, Traits>;

public:
	// types
	using traits_type            = Traits;
	using value_type             = CharT;
	using allocator_type         = Allocator;
	using size_type              = typename AllocTraits::size_type;
	using difference_type        = typename AllocTraits::difference_type;
	using pointer                = typename AllocTraits::pointer;
	using const_pointer          = typename AllocTraits::const_pointer;
	using reference              = value_type&;
	using const_reference        = value_type const&;

	using iterator               = CharT*;//implementation-defined; // see [container.requirements]
	using const_iterator         = CharT const*;//implementation-defined; // see [container.requirements]
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

	static constexpr size_type npos = size_type(-1);

private:
	struct Rep
	{
		using small_size_type = hamon::make_unsigned_t<value_type>;

		static const hamon::size_t kLargeSizeBits = hamon::bitsof<size_type>() - 1;
		static const hamon::size_t kSmallSizeBits = hamon::bitsof<small_size_type>() - 1;

		static const size_type kLargeSizeMask = (1ULL << kLargeSizeBits) - 1;
		static const size_type kSmallSizeMask = (1ULL << kSmallSizeBits) - 1;

#if !defined(HAMON_MSVC)
#define HAMON_HAS_BUILTIN_CONSTANT_P
#endif

#if HAMON_CXX_STANDARD < 20 || defined(HAMON_HAS_BUILTIN_CONSTANT_P)
#define HAMON_BASIC_STRING_CONPACT_LAYOUT
#endif

		struct Large
		{
#if defined(HAMON_BASIC_STRING_CONPACT_LAYOUT)
			size_type	is_large : 1;
#endif
			size_type	size : kLargeSizeBits;
			size_type	capacity;
			pointer		data;
		};

		static const hamon::size_t kSmallBufferSize = (sizeof(Large) / sizeof(small_size_type)) - 1;

		struct Small
		{
#if defined(HAMON_BASIC_STRING_CONPACT_LAYOUT)
			small_size_type	is_large : 1;
#endif
			small_size_type	size : kSmallSizeBits;
			value_type	    data[kSmallBufferSize];
		};

#if !defined(HAMON_BASIC_STRING_CONPACT_LAYOUT)
		bool	m_is_large;
#endif
		union
		{
			Small	m_small;
			Large	m_large;
		};

		HAMON_CXX11_CONSTEXPR bool IsLarge() const HAMON_NOEXCEPT
		{
#if defined(HAMON_BASIC_STRING_CONPACT_LAYOUT)
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
			if (hamon::is_constant_evaluated() && __builtin_constant_p(m_large.is_large))
			{
				return m_large.is_large;
			}
#endif
			return m_small.is_large;
#else
			return m_is_large;
#endif
		}

		HAMON_CXX14_CONSTEXPR void IsLarge(bool is_large) HAMON_NOEXCEPT
		{
#if defined(HAMON_BASIC_STRING_CONPACT_LAYOUT)
			if (is_large)
			{
				m_large.is_large = true;
			}
			else
			{
				m_small.is_large = false;
			}
#else
			m_is_large = is_large;
#endif
		}

		HAMON_CXX11_CONSTEXPR size_type GetMaxSize(allocator_type const& alloc) const HAMON_NOEXCEPT
		{
			return (AllocTraits::max_size(alloc) - 1) / 2;	// TODO
		}

		HAMON_CXX11_CONSTEXPR size_type GetSize() const HAMON_NOEXCEPT
		{
			return IsLarge() ? m_large.size : m_small.size;
		}

		HAMON_CXX11_CONSTEXPR size_type GetCapacity() const HAMON_NOEXCEPT
		{
			return IsLarge() ? m_large.capacity : kSmallBufferSize;
		}
		
		HAMON_CXX14_CONSTEXPR pointer GetData() HAMON_NOEXCEPT
		{
			return IsLarge() ? m_large.data : m_small.data;
		}

	private:
		HAMON_CXX14_CONSTEXPR void BeginLifetime(pointer p, size_type n)
		{
			for (size_type i = 0; i < n; ++i)
			{
				hamon::construct_at(hamon::addressof(p[i]));
			}
		}

	public:

		HAMON_CXX14_CONSTEXPR void Allocate(allocator_type& alloc, size_type size)
		{
			if (size >= GetMaxSize(alloc))
			{
				hamon::detail::throw_length_error("basic_string");
			}

			if (size <= kSmallBufferSize)
			{
				IsLarge(false);
				m_small.size = 0;
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
				if (hamon::is_constant_evaluated())
				{
					for (hamon::size_t i = 0; i < kSmallBufferSize; ++i)
					{
						m_small.data[i] = {};
					}
				}
#endif
			}
			else
			{
				auto p = AllocTraits::allocate(alloc, size);
				BeginLifetime(p, size);
				IsLarge(true);
				m_large.size = 0;
				m_large.data = p;
				m_large.capacity = size;
			}
		}

		HAMON_CXX14_CONSTEXPR void Deallocate(allocator_type& alloc) HAMON_NOEXCEPT
		{
			if (IsLarge())
			{
				AllocTraits::deallocate(alloc, this->GetData(), this->GetCapacity());
				m_large.data = nullptr;
			}
		}

		HAMON_CXX14_CONSTEXPR void SetSize(size_type size) HAMON_NOEXCEPT
		{
			if (IsLarge())
			{
				m_large.size = size & kLargeSizeMask;
			}
			else
			{
				m_small.size = size & kSmallSizeMask;
			}
		}

		HAMON_CXX14_CONSTEXPR void NullTerminate() HAMON_NOEXCEPT
		{
			Traits::assign(GetData()[GetSize()], CharT{});
		}
	};

	// [[msvc::no_unique_address]]	TODO
	HAMON_NO_UNIQUE_ADDRESS	allocator_type m_allocator;
	Rep	m_rep;

public:
	// 23.4.3.3		[string.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	basic_string() HAMON_NOEXCEPT_IF_EXPR(Allocator())
		: basic_string(Allocator())
	{}

	HAMON_CXX11_CONSTEXPR explicit
	basic_string(Allocator const& a) HAMON_NOEXCEPT
		: m_allocator(a)
		, m_rep{}
	{}

	HAMON_CXX11_CONSTEXPR
	basic_string(basic_string const& str)
		: basic_string(str, AllocTraits::select_on_container_copy_construction(str.m_allocator))
	{
		// [string.cons]/2
	}

	HAMON_CXX14_CONSTEXPR
	basic_string(basic_string&& str) HAMON_NOEXCEPT
		: m_rep(hamon::move(str.m_rep))
	{
		// [string.cons]/3
		str.m_rep = Rep{};
	}

	HAMON_CXX14_CONSTEXPR
	basic_string(basic_string const& str, Allocator const& a)
		: m_allocator(a)
	{
		if (str.m_rep.IsLarge())
		{
			auto const size = str.size();
			m_rep.Allocate(m_allocator, size + 1);
			Traits::copy(this->data(), str.data(), size);
			m_rep.SetSize(size);
			m_rep.NullTerminate();
		}
		else
		{
			m_rep = str.m_rep;
		}
	}

	HAMON_CXX14_CONSTEXPR
	basic_string(basic_string const& str, size_type pos, Allocator const& a = Allocator())
		: basic_string(str, pos, npos, a)
	{}

	HAMON_CXX14_CONSTEXPR
	basic_string(basic_string const& str, size_type pos, size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [string.cons]/6
		if (pos > str.size())
		{
			hamon::detail::throw_out_of_range("basic_string::basic_string");
		}

		// [string.cons]/4.2
		// [string.cons]/5

		auto const size = hamon::min(n, str.size() - pos);
		m_rep.Allocate(m_allocator, size + 1);
		Traits::copy(this->data(), str.data() + pos, size);
		m_rep.SetSize(size);
		m_rep.NullTerminate();
	}

	HAMON_CXX14_CONSTEXPR
	basic_string(basic_string&& str, Allocator const& a)
		: m_allocator(a)
	{
		if (str.m_rep.IsLarge() && a != str.m_allocator)
		{
			auto const size = str.size();
			m_rep.Allocate(m_allocator, size + 1);
			Traits::copy(this->data(), str.data(), size);
			m_rep.SetSize(size);
			m_rep.NullTerminate();
		}
		else
		{
			m_rep = str.m_rep;
			str.m_rep = Rep{};
		}
	}

	HAMON_CXX14_CONSTEXPR
	basic_string(basic_string&& str, size_type pos, Allocator const& a = Allocator())
		: basic_string(hamon::move(str), pos, npos, a)
	{}

	HAMON_CXX14_CONSTEXPR
	basic_string(basic_string&& str, size_type pos, size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [string.cons]/6
		if (pos > str.size())
		{
			hamon::detail::throw_out_of_range("basic_string::basic_string");
		}

		// [string.cons]/4.2
		// [string.cons]/5

		auto const size = hamon::min(n, str.size() - pos);
		if (str.m_rep.IsLarge() && a != str.m_allocator)
		{
			m_rep.Allocate(m_allocator, size + 1);
			Traits::copy(this->data(), str.data() + pos, size);
			m_rep.SetSize(size);
			m_rep.NullTerminate();
		}
		else
		{
			m_rep = str.m_rep;
			str.m_rep = Rep{};
			Traits::move(this->data(), this->data() + pos, size);
			m_rep.SetSize(size);
			m_rep.NullTerminate();
		}
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value	// [string.cons]/9
		>
	>
	HAMON_CXX14_CONSTEXPR
	basic_string(T const& t, size_type pos, size_type n, Allocator const& a = Allocator())
		: basic_string(StringView(t).substr(pos, n), a)			// [string.cons]/10
	{}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.cons]/11.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.cons]/11.2
		>
	>
	HAMON_CXX14_CONSTEXPR explicit
	basic_string(T const& t, Allocator const& a = Allocator())
		: basic_string(StringView(t).data(), StringView(t).size(), a)	// [string.cons]/12
	{}

	HAMON_CXX14_CONSTEXPR
	basic_string(CharT const* s, size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [string.cons]/14

		m_rep.Allocate(m_allocator, n + 1);
		Traits::copy(this->data(), s, n);
		m_rep.SetSize(n);
		m_rep.NullTerminate();
	}

	template <
		typename = hamon::enable_if_t<
			hamon::detail::is_allocator<Allocator>::value	// [string.cons]/16
		>
	>
	HAMON_CXX14_CONSTEXPR
	basic_string(CharT const* s, Allocator const& a = Allocator())
		: basic_string(s, Traits::length(s), a)	// [string.cons]/17
	{}

	basic_string(hamon::nullptr_t) = delete;

	template <
		typename = hamon::enable_if_t<
			hamon::detail::is_allocator<Allocator>::value	// [string.cons]/18
		>
	>
	HAMON_CXX14_CONSTEXPR
	basic_string(size_type n, CharT c, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		m_rep.Allocate(m_allocator, n + 1);
		Traits::assign(this->data(), n, c);
		m_rep.SetSize(n);
		m_rep.NullTerminate();
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>	// [string.cons]/20
	HAMON_CXX14_CONSTEXPR
	basic_string(InputIterator begin, InputIterator end, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		auto const size = static_cast<size_type>(hamon::ranges::distance(begin, end));
		m_rep.Allocate(m_allocator, size + 1);

		//Traits::copy(this->data(), begin, size);
		auto p = m_rep.GetData();
		for (auto it = begin; it != end; ++it, (void)++p)
		{
			Traits::assign(*p, static_cast<CharT>(*it));
		}

		m_rep.SetSize(size);
		m_rep.NullTerminate();
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, CharT, R)>
	HAMON_CXX14_CONSTEXPR
	basic_string(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: basic_string(hamon::ranges::begin(rg), hamon::ranges::end(rg), a)	// [string.cons]/22
	{}

	HAMON_CXX14_CONSTEXPR
	basic_string(std::initializer_list<CharT> il, Allocator const& a = Allocator())
		: basic_string(il.begin(), il.end(), a)	// [string.cons]/23
	{}

	HAMON_CXX20_CONSTEXPR
	~basic_string()
	{
		m_rep.Deallocate(m_allocator);
	}

private:
	HAMON_CXX14_CONSTEXPR void PropagateOnCopyAssign(basic_string const& str)
	{
		(void)str;
		if (AllocTraits::propagate_on_container_copy_assignment::value)
		{
			// TODO
		}
	}

	HAMON_CXX14_CONSTEXPR void CopyAssign(CharT const* s, size_type n)
	{
		if (n + 1 > m_rep.GetCapacity())
		{
			m_rep.Deallocate(m_allocator);
			m_rep.Allocate(m_allocator, n + 1);
		}

		Traits::copy(this->data(), s, n);
		m_rep.SetSize(n);
		m_rep.NullTerminate();
	}

	HAMON_CXX14_CONSTEXPR void PropagateOnMoveAssign(basic_string& str)
	{
		if (AllocTraits::propagate_on_container_move_assignment::value)
		{
			m_allocator = hamon::move(str.m_allocator);
		}
	}

	HAMON_CXX14_CONSTEXPR void MoveAssign(basic_string& str)
	{
		PropagateOnMoveAssign(str);

		m_rep.Deallocate(m_allocator);
		m_rep = str.m_rep;
		str.m_rep = Rep{};
	}

public:
	HAMON_CXX14_CONSTEXPR basic_string&
	operator=(basic_string const& str)
	{
		// [string.cons]/28
		if (this != hamon::addressof(str))
		{
			PropagateOnCopyAssign(str);
			CopyAssign(str.data(), str.size());
		}

		// [string.cons]/29
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	operator=(basic_string&& str)
		HAMON_NOEXCEPT(
			AllocTraits::propagate_on_container_move_assignment::value ||
			AllocTraits::is_always_equal::value)
	{
		// [string.cons]/30
		MoveAssign(str);

		// [string.cons]/31
		return *this;
	}
	
	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.cons]/32.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.cons]/32.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	operator=(T const& t)
	{
		// [string.cons]/33
		StringView sv = t;
		return assign(sv);
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	operator=(CharT const* s)
	{
		// [string.cons]/34
		return *this = StringView(s);
	}

	basic_string& operator=(hamon::nullptr_t) = delete;

	HAMON_CXX14_CONSTEXPR basic_string&
	operator=(CharT c)
	{
		// [string.cons]/35
		return *this = StringView(hamon::addressof(c), 1);
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	operator=(std::initializer_list<CharT> il)
	{
		// [string.cons]/36
		return *this = StringView(il.begin(), il.size());
	}

	// 23.4.3.4		[string.iterators], iterators
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
	begin() HAMON_NOEXCEPT
	{
		// [string.iterators]/1
		return iterator(this->data());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator	// nodiscard as an extension
	begin() const HAMON_NOEXCEPT
	{
		// [string.iterators]/1
		return const_iterator(this->data());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
	end() HAMON_NOEXCEPT
	{
		// [string.iterators]/2
		return iterator(this->data() + this->size());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator	// nodiscard as an extension
	end() const HAMON_NOEXCEPT
	{
		// [string.iterators]/2
		return const_iterator(this->data() + this->size());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reverse_iterator	// nodiscard as an extension
	rbegin() HAMON_NOEXCEPT
	{
		// [string.iterators]/3
		return reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator	// nodiscard as an extension
	rbegin() const HAMON_NOEXCEPT
	{
		// [string.iterators]/3
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reverse_iterator	// nodiscard as an extension
	rend() HAMON_NOEXCEPT
	{
		// [string.iterators]/4
		return reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator	// nodiscard as an extension
	rend() const HAMON_NOEXCEPT
	{
		// [string.iterators]/4
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator	// nodiscard as an extension
	cbegin() const HAMON_NOEXCEPT
	{
		// [string.iterators]/1
		return const_iterator(this->data());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator	// nodiscard as an extension
	cend() const HAMON_NOEXCEPT
	{
		// [string.iterators]/2
		return const_iterator(this->data() + this->size());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator	// nodiscard as an extension
	crbegin() const HAMON_NOEXCEPT
	{
		// [string.iterators]/3
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator	// nodiscard as an extension
	crend() const HAMON_NOEXCEPT
	{
		// [string.iterators]/4
		return const_reverse_iterator(this->begin());
	}

	// 23.4.3.5		[string.capacity], capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	size() const HAMON_NOEXCEPT
	{
		// [string.capacity]/1
		return m_rep.GetSize();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	length() const HAMON_NOEXCEPT
	{
		// [string.capacity]/1
		return this->size();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	max_size() const HAMON_NOEXCEPT
	{
		// [string.capacity]/3
		return m_rep.GetMaxSize(m_allocator);
	}

	HAMON_CXX14_CONSTEXPR void
	resize(size_type n, CharT c)
	{
		// [string.capacity]/5
		if (n <= size())
		{
			this->erase(this->begin() + n, this->end());
		}
		else
		{
			this->append(n - size(), c);
		}
	}

	HAMON_CXX14_CONSTEXPR void
	resize(size_type n)
	{
		// [string.capacity]/6
		resize(n, CharT());
	}

	template <typename Operation>
	HAMON_CXX14_CONSTEXPR void
	resize_and_overwrite(size_type n, Operation op)
	{
		reserve(n + 1);
		auto p = data();
		size_type const m = n;			// [string.capacity]/7.4
		auto r = hamon::move(op)(p, m);	// [string.capacity]/7.5, 7.6
		static_assert(hamon::ranges::detail::is_integer_like_t<decltype(r)>::value, "[string.capacity]/8");
		auto const rr = static_cast<size_type>(r);
		HAMON_ASSERT(rr >= 0u);	// [string.capacity]/9.2
		HAMON_ASSERT(rr <= m);	// [string.capacity]/9.3
		m_rep.SetSize(rr);
		m_rep.NullTerminate();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	capacity() const HAMON_NOEXCEPT
	{
		return m_rep.GetCapacity();
	}

	HAMON_CXX14_CONSTEXPR void
	reserve(size_type res_arg)
	{
		// [string.capacity]/15
		if (res_arg > max_size())
		{
			hamon::detail::throw_length_error("basic_string::reserve");
		}

		// [string.capacity]/14
		if (res_arg <= capacity())
		{
			return;
		}

		Rep new_one{};
		new_one.Allocate(m_allocator, res_arg);
		Traits::copy(new_one.GetData(), m_rep.GetData(), m_rep.GetSize());
		new_one.SetSize(m_rep.GetSize());
		new_one.NullTerminate();
		hamon::swap(new_one, m_rep);
		new_one.Deallocate(m_allocator);
	}

	HAMON_CXX14_CONSTEXPR void
	shrink_to_fit()
	{
		// TODO
	}

	HAMON_CXX14_CONSTEXPR void
	clear() HAMON_NOEXCEPT
	{
		// [string.capacity]/19
		erase(begin(), end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		// [string.capacity]/20
		return this->size() == 0;
	}

	// 23.4.3.6	[string.access], element access
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reference	// nodiscard as an extension
	operator[](size_type pos) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(pos <= this->size()),	// [string.access]/1
			this->data()[pos];					// [string.access]/2
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reference	// nodiscard as an extension
	operator[](size_type pos) HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(pos <= this->size()),	// [string.access]/1
			this->data()[pos];					// [string.access]/2
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reference	// nodiscard as an extension
	at(size_type pos) const
	{
		return pos >= this->size() ?		// [string.access]/6
			(hamon::detail::throw_out_of_range("basic_string::at"), operator[](0)) :
			operator[](pos);				// [string.access]/5
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reference	// nodiscard as an extension
	at(size_type pos)
	{
		return pos >= this->size() ?		// [string.access]/6
			(hamon::detail::throw_out_of_range("basic_string::at"), operator[](0)) :
			operator[](pos);				// [string.access]/5
	}

HAMON_WARNING_POP()

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR CharT const&	// nodiscard as an extension
	front() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(!this->empty()),	// [string.access]/7
			operator[](0);					// [string.access]/8
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR CharT&	// nodiscard as an extension
	front() HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(!this->empty()),	// [string.access]/7
			operator[](0);					// [string.access]/8
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR CharT const&	// nodiscard as an extension
	back() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(!this->empty()),	// [string.access]/9
			operator[](this->size() - 1);	// [string.access]/10
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR CharT&	// nodiscard as an extension
	back() HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT(!this->empty()),	// [string.access]/9
			operator[](this->size() - 1);	// [string.access]/10
	}

	// 23.4.3.7		[string.modifiers], modifiers

	// 23.4.3.7.1	[string.op.append]
	HAMON_CXX14_CONSTEXPR basic_string&
	operator+=(basic_string const& str)
	{
		// [string.op.append]/1
		return append(str);
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.op.append]/2.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.op.append]/2.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	operator+=(T const& t)
	{
		// [string.op.append]/3
		StringView sv = t;
		return append(sv);
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	operator+=(CharT const* s)
	{
		// [string.op.append]/4
		return append(s);
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	operator+=(CharT c)
	{
		// [string.op.append]/5
		return append(size_type{1}, c);
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	operator+=(std::initializer_list<CharT> il)
	{
		// [string.op.append]/6
		return append(il);
	}

	// 23.4.3.7.2	[string.append]
	HAMON_CXX14_CONSTEXPR basic_string&
	append(basic_string const& str)
	{
		// [string.append]/1
		return append(str.data(), str.size());
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	append(basic_string const& str, size_type pos, size_type n = npos)
	{
		// [string.append]/2
		return append(StringView(str).substr(pos, n));
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.append]/3.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.append]/3.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	append(T const& t)
	{
		// [string.append]/4
		StringView sv = t;
		return append(sv.data(), sv.size());
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.append]/5.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.append]/5.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	append(T const& t, size_type pos, size_type n = npos)
	{
		// [string.append]/6
		StringView sv = t;
		return append(sv.substr(pos, n));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	append(CharT const* s, size_type n)
	{
		// [string.append]/8
		if (n != 0)
		{
			auto const cur_size = this->size();
			auto const new_size = cur_size + n;
			auto const new_capacity = new_size + 1;
			if (new_capacity > m_rep.GetCapacity())
			{
				Rep new_one{};
				new_one.Allocate(m_allocator, new_capacity);
				Traits::copy(new_one.GetData(), m_rep.GetData(), m_rep.GetSize());
				Traits::copy(new_one.GetData() + cur_size, s, n);
				hamon::swap(new_one, m_rep);
				new_one.Deallocate(m_allocator);
			}
			else
			{
				Traits::copy(m_rep.GetData() + cur_size, s, n);
			}
			m_rep.SetSize(new_size);
			m_rep.NullTerminate();
		}

		// [string.append]/9
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	append(CharT const* s)
	{
		// [string.append]/10
		return append(s, Traits::length(s));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	append(size_type n, CharT c)
	{
		// [string.append]/11
		if (n != 0)
		{
			auto const cur_size = this->size();
			auto const new_size = cur_size + n;
			auto const new_capacity = new_size + 1;
			if (new_capacity > m_rep.GetCapacity())
			{
				Rep new_one{};
				new_one.Allocate(m_allocator, new_capacity);
				Traits::copy(new_one.GetData(), m_rep.GetData(), m_rep.GetSize());
				Traits::assign(new_one.GetData() + cur_size, n, c);
				hamon::swap(new_one, m_rep);
				new_one.Deallocate(m_allocator);
			}
			else
			{
				Traits::assign(m_rep.GetData() + cur_size, n, c);
			}
			m_rep.SetSize(new_size);
			m_rep.NullTerminate();
		}

		// [string.append]/12
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>	// [string.append]/13
	HAMON_CXX14_CONSTEXPR basic_string&
	append(InputIterator first, InputIterator last)
	{
		// [string.append]/14
		return append(basic_string(first, last, get_allocator()));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	append(std::initializer_list<CharT> il)
	{
		// [string.append]/16
		return append(il.begin(), il.size());
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, CharT, R)>
	HAMON_CXX14_CONSTEXPR basic_string&
	append_range(R&& rg)
	{
		// [string.append]/15
		return append(basic_string(hamon::from_range, hamon::forward<R>(rg), get_allocator()));
	}

	HAMON_CXX14_CONSTEXPR void
	push_back(CharT c)
	{
		// [string.append]/17
		append(size_type{1}, c);
	}

	// 23.4.3.7.3	[string.assign]
	HAMON_CXX14_CONSTEXPR basic_string&
	assign(basic_string const& str)
	{
		// [string.assign]/1
		return *this = str;
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	assign(basic_string&& str)
		HAMON_NOEXCEPT_IF(
			AllocTraits::propagate_on_container_move_assignment::value ||
			AllocTraits::is_always_equal::value)
	{
		// [string.assign]/2
		return *this = hamon::move(str);
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	assign(basic_string const& str, size_type pos, size_type n = npos)
	{
		// [string.assign]/3
		return assign(StringView(str).substr(pos, n));
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.assign]/4.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.assign]/4.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	assign(T const& t)
	{
		// [string.assign]/5
		StringView sv = t;
		return assign(sv.data(), sv.size());
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.assign]/6.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.assign]/6.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	assign(T const& t, size_type pos, size_type n = npos)
	{
		// [string.assign]/7
		StringView sv = t;
		return assign(sv.substr(pos, n));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	assign(CharT const* s, size_type n)
	{
		CopyAssign(s, n);
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	assign(CharT const* s)
	{
		// [string.assign]/11
		return assign(s, Traits::length(s));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	assign(std::initializer_list<CharT> il)
	{
		// [string.assign]/12
		return assign(il.begin(), il.size());
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	assign(size_type n, CharT c)
	{
		// [string.assign]/13
		clear();
		resize(n, c);
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>	// [string.assign]/14
	HAMON_CXX14_CONSTEXPR basic_string&
	assign(InputIterator first, InputIterator last)
	{
		// [string.assign]/15
		return assign(basic_string(first, last, get_allocator()));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, CharT, R)>
	HAMON_CXX14_CONSTEXPR basic_string&
	assign_range(R&& rg)
	{
		// [string.assign]/16
		return assign(basic_string(hamon::from_range, hamon::forward<R>(rg), get_allocator()));
	}

	// 23.4.3.7.4	[string.insert]
	HAMON_CXX14_CONSTEXPR basic_string&
	insert(size_type pos, basic_string const& str)
	{
		// [string.insert]/1
		return insert(pos, str.data(), str.size());
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	insert(size_type pos1, basic_string const& str, size_type pos2, size_type n = npos)
	{
		// [string.insert]/2
		return insert(pos1, StringView(str), pos2, n);
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.insert]/3.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.insert]/3.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	insert(size_type pos, T const& t)
	{
		// [string.insert]/4
		StringView sv = t;
		return insert(pos, sv.data(), sv.size());
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.insert]/5.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.insert]/5.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	insert(size_type pos1, T const& t, size_type pos2, size_type n = npos)
	{
		// [string.insert]/6
		StringView sv = t;
		return insert(pos1, sv.substr(pos2, n));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	insert(size_type pos, CharT const* s, size_type n)
	{
		// [string.insert]/10.1
		if (pos > size())
		{
			hamon::detail::throw_out_of_range("basic_string::insert");
		}

		// [string.insert]/10.2
		if (n > max_size() - size())
		{
			hamon::detail::throw_length_error("basic_string::insert");
		}

		// [string.insert]/8
		if (n != 0)
		{
			auto const new_size = this->size() + n;
			auto const new_capacity = new_size + 1;
			//if (new_capacity > m_rep.GetCapacity())
			{
				Rep new_one{};
				new_one.Allocate(m_allocator, new_capacity);
				Traits::copy(new_one.GetData(), m_rep.GetData(), pos);
				Traits::copy(new_one.GetData() + pos, s, n);
				Traits::copy(new_one.GetData() + pos + n, m_rep.GetData() + pos, m_rep.GetSize() - pos);
				hamon::swap(new_one, m_rep);
				new_one.Deallocate(m_allocator);
			}
			// TODO
			/*else
			{
				auto p = m_rep.GetData();
				Traits::move(p + pos + n, p + pos, m_rep.GetSize() - pos);
				Traits::move(p + pos, s, n);
			}*/
			m_rep.SetSize(new_size);
			m_rep.NullTerminate();
		}

		// [string.insert]/9
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	insert(size_type pos, CharT const* s)
	{
		// [string.insert]/11
		return insert(pos, s, Traits::length(s));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	insert(size_type pos, size_type n, CharT c)
	{
		// [string.insert]/14.1
		if (pos > size())
		{
			hamon::detail::throw_out_of_range("basic_string::insert");
		}

		// [string.insert]/14.2
		if (n > max_size() - size())
		{
			hamon::detail::throw_length_error("basic_string::insert");
		}

		// [string.insert]/12
		if (n != 0)
		{
			auto const new_size = this->size() + n;
			auto const new_capacity = new_size + 1;
			if (new_capacity > m_rep.GetCapacity())
			{
				Rep new_one{};
				new_one.Allocate(m_allocator, new_capacity);
				Traits::copy(new_one.GetData(), m_rep.GetData(), pos);
				Traits::assign(new_one.GetData() + pos, n, c);
				Traits::copy(new_one.GetData() + pos + n, m_rep.GetData() + pos, m_rep.GetSize() - pos);
				hamon::swap(new_one, m_rep);
				new_one.Deallocate(m_allocator);
			}
			else
			{
				Traits::move(m_rep.GetData() + pos + n, m_rep.GetData() + pos, m_rep.GetSize() - pos);
				Traits::assign(m_rep.GetData() + pos, n, c);
			}
			m_rep.SetSize(new_size);
			m_rep.NullTerminate();
		}

		// [string.insert]/13
		return *this;
	}
	
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator p, CharT c)
	{
		// [string.insert]/16
		// [string.insert]/17
		return insert(p, 1, c);
	}
	
	template <typename Iterator,
		typename = hamon::enable_if_t<	// insert(size_type, size_type, CharT) と曖昧にならないようにするため
			hamon::is_same<Iterator, const_iterator>::value ||
			hamon::is_same<Iterator, iterator>::value
		>
	>
	HAMON_CXX14_CONSTEXPR iterator
	insert(Iterator p, size_type n, CharT c)
	{
		// [string.insert]/18
		auto pos = p - begin();
		insert(static_cast<size_type>(pos), n, c);

		// [string.insert]/19
		return begin() + pos;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>	// [string.insert]/21
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator p, InputIterator first, InputIterator last)
	{
		// [string.insert]/23
		auto pos = p - begin();
		insert(static_cast<size_type>(pos), basic_string(first, last, get_allocator()));

		// [string.insert]/24
		return begin() + pos;
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator p, std::initializer_list<CharT> il)
	{
		// [string.insert]/28
		return insert(p, il.begin(), il.end());
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, CharT, R)>
	HAMON_CXX14_CONSTEXPR iterator
	insert_range(const_iterator p, R&& rg)
	{
		// [string.insert]/26
		auto pos = p - begin();
		insert(static_cast<size_type>(pos), basic_string(hamon::from_range, hamon::forward<R>(rg), get_allocator()));

		// [string.insert]/27
		return begin() + pos;
	}

	// 23.4.3.7.5	[string.erase]
	HAMON_CXX14_CONSTEXPR basic_string&
	erase(size_type pos = 0, size_type n = npos)
	{
		// [string.erase]/3
		if (pos > size())
		{
			hamon::detail::throw_out_of_range("basic_string::erase");
		}

		// [string.erase]/1
		auto const xlen = hamon::min(n, size() - pos);
		erase(begin() + pos, begin() + pos + xlen);

		// [string.erase]/2
		return *this;
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator p)
	{
		return erase(p, p + 1);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		auto const n = static_cast<size_type>(last - first);
		auto const n_move = static_cast<size_type>(this->end() - last);
		Traits::move(const_cast<iterator>(first), last, n_move);
		m_rep.SetSize(this->size() - n);
		m_rep.NullTerminate();
		return const_cast<iterator>(first);
	}

	HAMON_CXX14_CONSTEXPR void
	pop_back()
	{
		HAMON_ASSERT(!this->empty());	// [string.erase]/12
		this->erase(this->end() - 1);	// [string.erase]/13
	}

	// 23.4.3.7.6	[string.replace]
	HAMON_CXX14_CONSTEXPR basic_string&
	replace(size_type pos1, size_type n1, basic_string const& str)
	{
		// [string.replace]/1
		return replace(pos1, n1, str.data(), str.size());
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	replace(size_type pos1, size_type n1, basic_string const& str, size_type pos2, size_type n2 = npos)
	{
		// [string.replace]/2
		return replace(pos1, n1, StringView(str).substr(pos2, n2));
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.replace]/3.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.replace]/3.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	replace(size_type pos1, size_type n1, T const& t)
	{
		// [string.replace]/4
		StringView sv = t;
		return replace(pos1, n1, sv.data(), sv.size());
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.replace]/5.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.replace]/5.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	replace(size_type pos1, size_type n1, T const& t, size_type pos2, size_type n2 = npos)
	{
		// [string.replace]/6
		StringView sv = t;
		return replace(pos1, n1, sv.substr(pos2, n2));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	replace(size_type pos1, size_type n1, CharT const* s, size_type n2)
	{
		// [string.replace]/10.1
		if (pos1 > size())
		{
			hamon::detail::throw_out_of_range("basic_string::replace");
		}

		auto const xlen = hamon::min(n1, size() - pos1);

		// [string.replace]/10.2
		if (size() - xlen >= max_size() - n2)
		{
			hamon::detail::throw_length_error("basic_string::replace");
		}

		// [string.replace]/8
		auto const new_size = this->size() - xlen + n2;
		auto const new_capacity = new_size + 1;
		//if (new_capacity > m_rep.GetCapacity())
		{
			Rep new_one{};
			new_one.Allocate(m_allocator, new_capacity);
			Traits::copy(new_one.GetData(), m_rep.GetData(), pos1);
			Traits::copy(new_one.GetData() + pos1, s, n2);
			Traits::copy(new_one.GetData() + pos1 + n2, m_rep.GetData() + pos1 + xlen, m_rep.GetSize() - pos1 - xlen);
			hamon::swap(new_one, m_rep);
			new_one.Deallocate(m_allocator);
		}
		// TODO
		//else
		//{
		//	Traits::move(m_rep.GetData() + pos1 + n2, m_rep.GetData() + pos1 + xlen, m_rep.GetSize() - pos1 - xlen);
		//	Traits::move(m_rep.GetData() + pos1, s, n2);
		//}
		m_rep.SetSize(new_size);
		m_rep.NullTerminate();

		// [string.replace]/9
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	replace(size_type pos, size_type n, CharT const* s)
	{
		// [string.replace]/11
		return replace(pos, n, s, Traits::length(s));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	replace(size_type pos1, size_type n1, size_type n2, CharT c)
	{
		// [string.replace]/14.1
		if (pos1 > size())
		{
			hamon::detail::throw_out_of_range("basic_string::replace");
		}

		auto const xlen = hamon::min(n1, size() - pos1);

		// [string.replace]/14.2
		if (size() - xlen >= max_size() - n2)
		{
			hamon::detail::throw_length_error("basic_string::replace");
		}

		// [string.replace]/12
		auto const new_size = this->size() - xlen + n2;
		auto const new_capacity = new_size + 1;
		if (new_capacity > m_rep.GetCapacity())
		{
			Rep new_one{};
			new_one.Allocate(m_allocator, new_capacity);
			Traits::copy(new_one.GetData(), m_rep.GetData(), pos1);
			Traits::assign(new_one.GetData() + pos1, n2, c);
			Traits::copy(new_one.GetData() + pos1 + n2, m_rep.GetData() + pos1 + xlen, m_rep.GetSize() - pos1 - xlen);
			hamon::swap(new_one, m_rep);
			new_one.Deallocate(m_allocator);
		}
		else
		{
			Traits::move(m_rep.GetData() + pos1 + n2, m_rep.GetData() + pos1 + xlen, m_rep.GetSize() - pos1 - xlen);
			Traits::assign(m_rep.GetData() + pos1, n2, c);
		}
		m_rep.SetSize(new_size);
		m_rep.NullTerminate();

		// [string.replace]/13
		return *this;
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	replace(const_iterator i1, const_iterator i2, basic_string const& str)
	{
		return replace(i1, i2, StringView(str));
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.replace]/16.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.replace]/16.2
		>
	>
	HAMON_CXX14_CONSTEXPR basic_string&
	replace(const_iterator i1, const_iterator i2, T const& t)
	{
		// [string.replace]/18
		StringView sv = t;
		return replace(static_cast<size_type>(i1 - begin()), static_cast<size_type>(i2 - i1), sv.data(), sv.size());
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	replace(const_iterator i1, const_iterator i2, CharT const* s, size_type n)
	{
		// [string.replace]/19
		return replace(i1, i2, StringView(s, n));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	replace(const_iterator i1, const_iterator i2, CharT const* s)
	{
		// [string.replace]/20
		return replace(i1, i2, StringView(s));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	replace(const_iterator i1, const_iterator i2, size_type n, CharT c)
	{
		// [string.replace]/22
		return replace(static_cast<size_type>(i1 - begin()), static_cast<size_type>(i2 - i1), n, c);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>	// [string.replace]/23
	HAMON_CXX14_CONSTEXPR basic_string&
	replace(const_iterator i1, const_iterator i2, InputIterator j1, InputIterator j2)
	{
		// [string.replace]/24
		return replace(i1, i2, basic_string(j1, j2, get_allocator()));
	}

	HAMON_CXX14_CONSTEXPR basic_string&
	replace(const_iterator i1, const_iterator i2, std::initializer_list<CharT> il)
	{
		// [string.replace]/26
		return replace(i1, i2, il.begin(), il.size());
	}

#if 0
	// TODO
	template <container-compatible-range<CharT> R>
	HAMON_CXX14_CONSTEXPR basic_string&
	replace_with_range(const_iterator i1, const_iterator i2, R&& rg)
	{
		// [string.replace]/25
		return replace(i1, i2, basic_string(hamon::from_range, hamon::forward<R>(rg), get_allocator()));
	}
#endif

	// 23.4.3.7.7	[string.copy]
	HAMON_CXX11_CONSTEXPR size_type
	copy(CharT* s, size_type n, size_type pos = 0) const
	{
		// [string.copy]/1
		return StringView(*this).copy(s, n, pos);
	}

	// 23.4.3.7.8	[string.swap]
	HAMON_CXX14_CONSTEXPR void
	swap(basic_string& str)
		HAMON_NOEXCEPT_IF(
			AllocTraits::propagate_on_container_swap::value ||
			AllocTraits::is_always_equal::value)
	{
		// [string.swap]/1
		HAMON_ASSERT(
			AllocTraits::propagate_on_container_swap::value ||
			get_allocator() == str.get_allocator());

		if (AllocTraits::propagate_on_container_swap::value)
		{
			hamon::swap(m_allocator, str.m_allocator);
		}
		hamon::swap(m_rep, str.m_rep);
	}

	// 23.4.3.8		[string.ops], string operations

	// 23.4.3.8.1	[string.accessors]
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR CharT const*	// nodiscard as an extension
	c_str() const HAMON_NOEXCEPT
	{
		// [string.accessors]/1
		return data();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR CharT const*	// nodiscard as an extension
	data() const HAMON_NOEXCEPT
	{
		// [string.accessors]/1
		return const_cast<basic_string*>(this)->data();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR CharT*	// nodiscard as an extension
	data() HAMON_NOEXCEPT
	{
		// [string.accessors]/4
		return m_rep.GetData();
	}

#if defined(HAMON_HAS_STD_STRING_VIEW)
	template <typename Traits2>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	operator std::basic_string_view<CharT, Traits2>() const HAMON_NOEXCEPT
	{
		// [string.accessors]/7
		return std::basic_string_view<CharT, Traits2>(data(), size());
	}
#endif

#if !defined(HAMON_USE_STD_STRING_VIEW)
	template <typename Traits2>	// extension
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	operator hamon::basic_string_view<CharT, Traits2>() const HAMON_NOEXCEPT
	{
		// [string.accessors]/7
		return hamon::basic_string_view<CharT, Traits2>(data(), size());
	}
#endif

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR allocator_type	// nodiscard as an extension
	get_allocator() const HAMON_NOEXCEPT
	{
		// [string.accessors]/8
		return m_allocator;
	}

	// 23.4.3.8.2	[string.find]
	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.find]/2.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.find]/2.2
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find(T const& t, size_type pos = 0) const
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_convertible<T const&, StringView>::value)	// [string.find]/4
	{
		// [string.find]/3
		return StringView(*this).find(StringView(t), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find(basic_string const& str, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.find]/1.1
		return find(StringView(str), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find(CharT const* s, size_type pos, size_type n) const
	{
		// [string.find]/1.3
		return find(StringView(s, n), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find(CharT const* s, size_type pos = 0) const
	{
		// [string.find]/1.2
		return find(StringView(s), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find(CharT c, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.find]/1.4
		return find(StringView(hamon::addressof(c), 1), pos);
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.find]/2.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.find]/2.2
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	rfind(T const& t, size_type pos = npos) const
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_convertible<T const&, StringView>::value)	// [string.find]/4
	{
		// [string.find]/3
		return StringView(*this).rfind(StringView(t), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	rfind(basic_string const& str, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.find]/1.1
		return rfind(StringView(str), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	rfind(CharT const* s, size_type pos, size_type n) const
	{
		// [string.find]/1.3
		return rfind(StringView(s, n), pos);
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	rfind(CharT const* s, size_type pos = npos) const
	{
		// [string.find]/1.2
		return rfind(StringView(s), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	rfind(CharT c, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.find]/1.4
		return rfind(StringView(hamon::addressof(c), 1), pos);
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.find]/2.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.find]/2.2
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_of(T const& t, size_type pos = 0) const
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_convertible<T const&, StringView>::value)	// [string.find]/4
	{
		// [string.find]/3
		return StringView(*this).find_first_of(StringView(t), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_of(basic_string const& str, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.find]/1.1
		return find_first_of(StringView(str), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_of(CharT const* s, size_type pos, size_type n) const
	{
		// [string.find]/1.3
		return find_first_of(StringView(s, n), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_of(CharT const* s, size_type pos = 0) const
	{
		// [string.find]/1.2
		return find_first_of(StringView(s), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_of(CharT c, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.find]/1.4
		return find_first_of(StringView(hamon::addressof(c), 1), pos);
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.find]/2.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.find]/2.2
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_of(T const& t, size_type pos = npos) const
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_convertible<T const&, StringView>::value)	// [string.find]/4
	{
		// [string.find]/3
		return StringView(*this).find_last_of(StringView(t), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_of(basic_string const& str, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.find]/1.1
		return find_last_of(StringView(str), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_of(CharT const* s, size_type pos, size_type n) const
	{
		// [string.find]/1.3
		return find_last_of(StringView(s, n), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_of(CharT const* s, size_type pos = npos) const
	{
		// [string.find]/1.2
		return find_last_of(StringView(s), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_of(CharT c, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.find]/1.4
		return find_last_of(StringView(hamon::addressof(c), 1), pos);
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.find]/2.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.find]/2.2
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_not_of(T const& t, size_type pos = 0) const
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_convertible<T const&, StringView>::value)	// [string.find]/4
	{
		// [string.find]/3
		return StringView(*this).find_first_not_of(StringView(t), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_not_of(basic_string const& str, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.find]/1.1
		return find_first_not_of(StringView(str), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_not_of(CharT const* s, size_type pos, size_type n) const
	{
		// [string.find]/1.3
		return find_first_not_of(StringView(s, n), pos);
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_not_of(CharT const* s, size_type pos = 0) const
	{
		// [string.find]/1.2
		return find_first_not_of(StringView(s), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_first_not_of(CharT c, size_type pos = 0) const HAMON_NOEXCEPT
	{
		// [string.find]/1.4
		return find_first_not_of(StringView(hamon::addressof(c), 1), pos);
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.find]/2.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.find]/2.2
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_not_of(T const& t, size_type pos = npos) const
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_convertible<T const&, StringView>::value)	// [string.find]/4
	{
		// [string.find]/3
		return StringView(*this).find_last_not_of(StringView(t), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_not_of(basic_string const& str, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.find]/1.1
		return find_last_not_of(StringView(str), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_not_of(CharT const* s, size_type pos, size_type n) const
	{
		// [string.find]/1.3
		return find_last_not_of(StringView(s, n), pos);
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_not_of(CharT const* s, size_type pos = npos) const
	{
		// [string.find]/1.2
		return find_last_not_of(StringView(s), pos);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	find_last_not_of(CharT c, size_type pos = npos) const HAMON_NOEXCEPT
	{
		// [string.find]/1.4
		return find_last_not_of(StringView(hamon::addressof(c), 1), pos);
	}

	// 23.4.3.8.3	[string.substr]
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR basic_string	// nodiscard as an extension
	substr(size_type pos = 0, size_type n = npos) const &
	{
		// [string.substr]/1
		return basic_string(*this, pos, n);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR basic_string	// nodiscard as an extension
	substr(size_type pos = 0, size_type n = npos) &&
	{
		// [string.substr]/2
		return basic_string(hamon::move(*this), pos, n);
	}

	// 23.4.3.8.4	[string.compare]
	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.compare]/1.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.compare]/1.2
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int	// nodiscard as an extension
	compare(T const& t) const
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_convertible<T const&, StringView>::value)	// [string.compare]/3
	{
		// [string.compare]/2
		return StringView(*this).compare(t);
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.compare]/4.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.compare]/4.2
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int	// nodiscard as an extension
	compare(size_type pos1, size_type n1, T const& t) const
	{
		// [string.compare]/5
		return StringView(*this).substr(pos1, n1).compare(t);
	}

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::is_convertible<T const&, StringView>::value &&	// [string.compare]/6.1
			!hamon::is_convertible<T const&, CharT const*>::value	// [string.compare]/6.2
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int	// nodiscard as an extension
	compare(size_type pos1, size_type n1, T const& t, size_type pos2, size_type n2 = npos) const
	{
		// [string.compare]/7
		return StringView(*this).substr(pos1, n1).compare(StringView(t).substr(pos2, n2));
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int	// nodiscard as an extension
	compare(basic_string const& str) const HAMON_NOEXCEPT
	{
		// [string.compare]/8
		return compare(StringView(str));
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int	// nodiscard as an extension
	compare(size_type pos1, size_type n1, basic_string const& str) const
	{
		// [string.compare]/9
		return compare(pos1, n1, StringView(str));
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int	// nodiscard as an extension
	compare(size_type pos1, size_type n1, basic_string const& str, size_type pos2, size_type n2 = npos) const
	{
		// [string.compare]/10
		return compare(pos1, n1, StringView(str), pos2, n2);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int	// nodiscard as an extension
	compare(CharT const* s) const
	{
		// [string.compare]/11
		return compare(StringView(s));
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int	// nodiscard as an extension
	compare(size_type pos1, size_type n1, CharT const* s) const
	{
		// [string.compare]/12
		return compare(pos1, n1, StringView(s));
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int	// nodiscard as an extension
	compare(size_type pos1, size_type n1, CharT const* s, size_type n2) const
	{
		// [string.compare]/13
		return compare(pos1, n1, StringView(s, n2));
	}

	// 23.4.3.8.5	[string.starts.with]
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	starts_with(basic_string_view<CharT, Traits> x) const HAMON_NOEXCEPT
	{
		// [string.starts.with]/1
		return StringView(data(), size()).starts_with(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	starts_with(CharT x) const HAMON_NOEXCEPT
	{
		// [string.starts.with]/1
		return StringView(data(), size()).starts_with(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	starts_with(CharT const* x) const
	{
		// [string.starts.with]/1
		return StringView(data(), size()).starts_with(x);
	}

	// 23.4.3.8.6	[string.ends.with]
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	ends_with(basic_string_view<CharT, Traits> x) const HAMON_NOEXCEPT
	{
		// [string.ends.with]/1
		return StringView(data(), size()).ends_with(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	ends_with(CharT x) const HAMON_NOEXCEPT
	{
		// [string.ends.with]/1
		return StringView(data(), size()).ends_with(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	ends_with(CharT const* x) const
	{
		// [string.ends.with]/1
		return StringView(data(), size()).ends_with(x);
	}

	// 23.4.3.8.7	[string.contains]
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	contains(basic_string_view<CharT, Traits> x) const HAMON_NOEXCEPT
	{
		// [string.contains]/1
		return StringView(data(), size()).contains(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	contains(CharT x) const HAMON_NOEXCEPT
	{
		// [string.contains]/1
		return StringView(data(), size()).contains(x);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	contains(CharT const* x) const
	{
		// [string.contains]/1
		return StringView(data(), size()).contains(x);
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),	// [string.cons]/26
	typename CharT = typename hamon::iterator_traits<InputIterator>::value_type,
	typename Allocator = std::allocator<CharT>,
	typename = hamon::enable_if_t<
		hamon::detail::is_allocator<Allocator>::value	// [string.cons]/26
	>
>
basic_string(InputIterator, InputIterator, Allocator = Allocator())
	-> basic_string<CharT, hamon::char_traits<CharT>, Allocator>;

// TODO
#if 0
template <
	ranges::input_range R,
	typename Allocator = std::allocator<ranges::range_value_t<R>>,
	typename = hamon::enable_if_t<
		hamon::detail::is_allocator<Allocator>::value
	>
>
basic_string(hamon::from_range_t, R&&, Allocator = Allocator())
	-> basic_string<ranges::range_value_t<R>, hamon::char_traits<ranges::range_value_t<R>>, Allocator>;
#endif

template <
	typename CharT,
	typename Traits,
	typename Allocator = std::allocator<CharT>,
	typename = hamon::enable_if_t<
		hamon::detail::is_allocator<Allocator>::value	// [string.cons]/27
	>
>
explicit basic_string(basic_string_view<CharT, Traits>, Allocator const& = Allocator())
	-> basic_string<CharT, Traits, Allocator>;

template <
	typename CharT,
	typename Traits,
	typename Allocator = std::allocator<CharT>,
	typename = hamon::enable_if_t<
		hamon::detail::is_allocator<Allocator>::value	// [string.cons]/27
	>,
	typename SizeType = typename  std::allocator_traits<Allocator>::size_type
>
basic_string(basic_string_view<CharT, Traits>, SizeType, SizeType, Allocator const& = Allocator())
	-> basic_string<CharT, Traits, Allocator>;

#endif

// 23.4.4 [string.nonmembers], Non-member functions

// 23.4.4.1 [string.op.plus], operator+
template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	// [string.op.plus]/1
	basic_string<CharT, Traits, Allocator> r = lhs;
	r.append(rhs);
	return r;
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	basic_string<CharT, Traits, Allocator>&& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	// [string.op.plus]/2
	lhs.append(rhs);
	return hamon::move(lhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator>&& rhs)
{
	// [string.op.plus]/4
	rhs.insert(0, lhs);
	return hamon::move(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	basic_string<CharT, Traits, Allocator>&& lhs,
	basic_string<CharT, Traits, Allocator>&& rhs)
{
	// [string.op.plus]/3
	lhs.append(rhs);
	return hamon::move(lhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	// [string.op.plus]/5
	basic_string<CharT, Traits, Allocator> r = rhs;
	r.insert(0, lhs);
	return r;
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator>&& rhs)
{
	// [string.op.plus]/4
	rhs.insert(0, lhs);
	return hamon::move(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	CharT lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	// [string.op.plus]/6
	basic_string<CharT, Traits, Allocator> r = rhs;
	r.insert(r.begin(), lhs);
	return r;
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	CharT lhs,
	basic_string<CharT, Traits, Allocator>&& rhs)
{
	// [string.op.plus]/7
	rhs.insert(rhs.begin(), lhs);
	return hamon::move(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	// [string.op.plus]/1
	basic_string<CharT, Traits, Allocator> r = lhs;
	r.append(rhs);
	return r;
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	basic_string<CharT, Traits, Allocator>&& lhs,
	CharT const* rhs)
{
	// [string.op.plus]/2
	lhs.append(rhs);
	return hamon::move(lhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT rhs)
{
	// [string.op.plus]/8
	basic_string<CharT, Traits, Allocator> r = lhs;
	r.push_back(rhs);
	return r;
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
basic_string<CharT, Traits, Allocator>
operator+(
	basic_string<CharT, Traits, Allocator>&& lhs,
	CharT rhs)
{
	// [string.op.plus]/9
	lhs.push_back(rhs);
	return hamon::move(lhs);
}

// 23.4.4.2	[string.cmp], Non-member comparison operator functions
template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) HAMON_NOEXCEPT
{
	// [string.cmp]/1
	return
		basic_string_view<CharT, Traits>(lhs) ==
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	// [string.cmp]/1
	return
		basic_string_view<CharT, Traits>(lhs) ==
		basic_string_view<CharT, Traits>(rhs);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
operator<=>(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) HAMON_NOEXCEPT
{
	// [string.cmp]/1
	return
		basic_string_view<CharT, Traits>(lhs) <=>
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
operator<=>(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	// [string.cmp]/1
	return
		basic_string_view<CharT, Traits>(lhs) <=>
		basic_string_view<CharT, Traits>(rhs);
}

#else

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) ==
		basic_string_view<CharT, Traits>(rhs);
}


template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) HAMON_NOEXCEPT
{
	return
		basic_string_view<CharT, Traits>(lhs) !=
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) !=
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) HAMON_NOEXCEPT
{
	return
		basic_string_view<CharT, Traits>(lhs) !=
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) HAMON_NOEXCEPT
{
	return
		basic_string_view<CharT, Traits>(lhs) <
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) <
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) <
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) HAMON_NOEXCEPT
{
	return
		basic_string_view<CharT, Traits>(lhs) >
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) >
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) >
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) HAMON_NOEXCEPT
{
	return
		basic_string_view<CharT, Traits>(lhs) <=
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) <=
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) <=
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) HAMON_NOEXCEPT
{
	return
		basic_string_view<CharT, Traits>(lhs) >=
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) >=
		basic_string_view<CharT, Traits>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return
		basic_string_view<CharT, Traits>(lhs) >=
		basic_string_view<CharT, Traits>(rhs);
}

#endif

// 23.4.4.3	[string.special], swap
template <typename CharT, typename Traits, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(
	basic_string<CharT, Traits, Allocator>& lhs,
	basic_string<CharT, Traits, Allocator>& rhs)
	HAMON_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	// [string.special]/1
	lhs.swap(rhs);
}

// [string.io], inserters and extractors
template <typename CharT, typename Traits, typename Traits2, typename Allocator>
std::basic_istream<CharT, Traits>&
operator>>(
	std::basic_istream<CharT, Traits>& is,
	basic_string<CharT, Traits2, Allocator>& str)
{
	// 31.7.5.4 [istream.unformatted], Unformatted input functions
	std::ios_base::iostate state = std::ios_base::goodbit;
	typename std::basic_istream<CharT, Traits>::sentry sen(is);
	if (sen)
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		try
		{
#endif
			// [string.io]/1
			str.erase();

			std::streamsize const n =
				is.width() > 0 ? is.width() :
				static_cast<std::streamsize>(str.max_size());
			std::streamsize extracted = 0;
			while (true)
			{
				// [string.io]/1.1
				if (extracted >= n)
				{
					break;
				}

				typename Traits::int_type const i = is.rdbuf()->sgetc();

				// [string.io]/1.2
				if (Traits::eq_int_type(i, Traits::eof()))
				{
					state |= std::ios_base::eofbit;
					break;
				}
				
				// [string.io]/1.3
				CharT const c = Traits::to_char_type(i);
				if (std::isspace(c, is.getloc()))
				{
					break;
				}

				str.append(1, c);
				++extracted;
				is.rdbuf()->sbumpc();
			}

			// [string.io]/2
			is.width(0);

			// [string.io]/3
			if (extracted == 0)
			{
				state |= std::ios_base::failbit;
			}
#if !defined(HAMON_NO_EXCEPTIONS)
		}
		catch (...)
		{
			state |= std::ios_base::badbit;
			is.setstate(state);	// TODO nothrow
			if (is.exceptions() & std::ios_base::badbit)
			{
				throw;
			}
		}
#endif
		is.setstate(state);
	}

	// [string.io]/4
	return is;
}

template <typename CharT, typename Traits, typename Traits2, typename Allocator>
std::basic_ostream<CharT, Traits>&
operator<<(
	std::basic_ostream<CharT, Traits>& os,
	basic_string<CharT, Traits2, Allocator> const& str)
{
	// [string.io]/5
	return os << hamon::basic_string_view<CharT, Traits>(str);
}

}	// namespace hamon

#endif

#endif // HAMON_STRING_BASIC_STRING_HPP
