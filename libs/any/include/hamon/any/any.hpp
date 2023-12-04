/**
 *	@file	any.hpp
 *
 *	@brief	any の定義
 */

#ifndef HAMON_ANY_ANY_HPP
#define HAMON_ANY_ANY_HPP

#include <hamon/any/config.hpp>

#if defined(HAMON_USE_STD_ANY)

#include <any>

namespace hamon
{

using std::any;

}	// namespace hamon

#else

#include <hamon/cstddef/byte.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy_at.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_type_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <initializer_list>
#include <typeinfo>

namespace hamon
{

namespace any_detail
{
struct any_caster;
}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

// [any.class], class any
class any
{
private:
	friend struct any_detail::any_caster;

	enum class Action
	{
		Copy,
		Move,
		Destroy,
		Type,
		Get,
	};

	union Storage
	{
		void* m_ptr;
		alignas(void*) hamon::byte m_buf[sizeof(void*) * 2];
	};

	// [any.class.general]/3
	template <typename T>
	struct IsSmallObject
		: public hamon::bool_constant<
			(sizeof(T) <= sizeof(Storage)) &&
			hamon::is_nothrow_move_constructible<T>::value
		>
	{};

	template <typename T>
	static void* GetTypeId()
	{
#if !defined(HAMON_NO_RTTI) || defined(HAMON_MSVC)
		return (void*)(&typeid(T));
#else
		return nullptr;
#endif
	}

	template <typename T, bool = IsSmallObject<T>::value>
	struct Impl
	{
	public:
		static void* vtbl(Action action, any* lhs, any* rhs)
		{
			switch (action)
			{
			case Action::Copy:
				{
					construct(lhs, *rhs->get<T>());
				}
				break;
			case Action::Move:
				{
					lhs->m_storage.m_ptr = rhs->get<T>();
					rhs->m_vtbl = nullptr;
				}
				break;
			case Action::Destroy:
				{
					auto ptr = lhs->get<T const>();
					delete ptr;
				}
				break;
			case Action::Type:
				return GetTypeId<T>();
			case Action::Get:
				return lhs->m_storage.m_ptr;
			}

			return nullptr;
		}

		template <typename... Args>
		static void construct(any* lhs, Args&&... args)
		{
			lhs->m_storage.m_ptr = new T(hamon::forward<Args>(args)...);
			lhs->m_vtbl = Impl::vtbl;
		}
	};

	template <typename T>
	struct Impl<T, true>
	{
	public:
		static void* vtbl(Action action, any* lhs, any* rhs)
		{
			switch (action)
			{
			case Action::Copy:
				{
					construct(lhs, *rhs->get<T>());
				}
				break;
			case Action::Move:
				{
					construct(lhs, hamon::move(*rhs->get<T>()));
					rhs->reset();
				}
				break;
			case Action::Destroy:
				{
					auto ptr = lhs->get<T>();
					hamon::destroy_at(ptr);
				}
				break;
			case Action::Type:
				return GetTypeId<T>();
			case Action::Get:
				return lhs->m_storage.m_buf;
			}

			return nullptr;
		}

		template <typename... Args>
		static void construct(any* lhs, Args&&... args)
		{
			auto ptr = static_cast<T*>(static_cast<void*>(lhs->m_storage.m_buf));
			hamon::construct_at<T>(ptr, hamon::forward<Args>(args)...);
			lhs->m_vtbl = Impl::vtbl;
		}
	};

	using VTblType = void*(*)(Action, any*, any*);

	Storage		m_storage {};
	VTblType	m_vtbl {};

private:
	template <typename T>
	T* get()
	{
		return static_cast<T*>(m_vtbl(any::Action::Get, this, nullptr));
	}

	static void copy(any* lhs, any* rhs)
	{
		lhs->m_vtbl = rhs->m_vtbl;
		lhs->m_vtbl(Action::Copy, lhs, rhs);
	}

	static void move(any* lhs, any* rhs)
	{
		lhs->m_vtbl = rhs->m_vtbl;
		lhs->m_vtbl(Action::Move, lhs, rhs);
	}

public:
	// [any.cons], construction and destruction
	HAMON_CXX11_CONSTEXPR any() HAMON_NOEXCEPT
	{
	}

	any(any const& other)
	{
		// [any.cons]/2
		if (other.has_value())
		{
			copy(this, const_cast<any*>(&other));
		}
	}

	any(any&& other) HAMON_NOEXCEPT
	{
		// [any.cons]/4
		if (other.has_value())
		{
			move(this, &other);
		}
	}

	template <typename T,
		typename VT = hamon::decay_t<T>,	// [any.cons]/5
		typename = hamon::enable_if_t<		// [any.cons]/6
			!hamon::is_same<VT, any>::value &&
			!hamon::is_in_place_type<VT>::value &&
			hamon::is_copy_constructible<VT>::value
		>
	>
	any(T&& value)
	{
		// [any.cons]/8
		Impl<VT>::construct(this, hamon::forward<T>(value));
	}

	template <typename T, typename... Args,
		typename VT = hamon::decay_t<T>,	// [any.cons]/10
		typename = hamon::enable_if_t<		// [any.cons]/11
			hamon::is_copy_constructible<VT>::value &&
			hamon::is_constructible<VT, Args...>::value
		>
	>
	explicit any(hamon::in_place_type_t<T>, Args&&... args)
	{
		// [any.cons]/13
		Impl<VT>::construct(this, hamon::forward<Args>(args)...);
	}

	template <typename T, typename U, typename... Args,
		typename VT = hamon::decay_t<T>,	// [any.cons]/16
		typename = hamon::enable_if_t<		// [any.cons]/17
			hamon::is_copy_constructible<VT>::value &&
			hamon::is_constructible<VT, std::initializer_list<U>&, Args...>::value
		>
	>
	explicit any(hamon::in_place_type_t<T>, std::initializer_list<U> il, Args&&... args)
	{
		// [any.cons]/19
		Impl<VT>::construct(this, il, hamon::forward<Args>(args)...);
	}

	~any()
	{
		// [any.cons]/22
		this->reset();
	}

	// [any.assign], assignments
	any& operator=(any const& rhs)
	{
		// [any.assign]/1
		any(rhs).swap(*this);
		// [any.assign]/2
		return *this;
	}

	any& operator=(any&& rhs) HAMON_NOEXCEPT
	{
		// [any.assign]/4
		any(hamon::move(rhs)).swap(*this);
		// [any.assign]/6
		return *this;
	}

	template <typename T,
		typename VT = hamon::decay_t<T>,	// [any.assign]/7
		typename = hamon::enable_if_t<		// [any.assign]/8
			!hamon::is_same<VT, any>::value &&
			hamon::is_copy_constructible<VT>::value
		>
	>
	any& operator=(T&& rhs)
	{
		// [any.assign]/10
		hamon::any tmp{hamon::forward<T>(rhs)};
		tmp.swap(*this);
		
		// [any.assign]/11
		return *this;
	}

	// [any.modifiers], modifiers
	template <typename T, typename... Args,
		typename VT = hamon::decay_t<T>,	// [any.modifiers]/1
		typename = hamon::enable_if_t<		// [any.modifiers]/2
			hamon::is_copy_constructible<VT>::value &&
			hamon::is_constructible<VT, Args...>::value
		>
	>
	hamon::decay_t<T>& emplace(Args&&... args)
	{
		// [any.modifiers]/4
		this->reset();
		Impl<VT>::construct(this, hamon::forward<Args>(args)...);
		// [any.modifiers]/6
		return *this->get<T>();
	}

	template <typename T, typename U, typename... Args,
		typename VT = hamon::decay_t<T>,	// [any.modifiers]/9
		typename = hamon::enable_if_t<		// [any.modifiers]/10
			hamon::is_copy_constructible<VT>::value &&
			hamon::is_constructible<VT, std::initializer_list<U>&, Args...>::value
		>
	>
	hamon::decay_t<T>& emplace(std::initializer_list<U> il, Args&&... args)
	{
		// [any.modifiers]/12
		this->reset();
		Impl<VT>::construct(this, il, hamon::forward<Args>(args)...);
		// [any.modifiers]/14
		return *this->get<T>();
	}

	void reset() HAMON_NOEXCEPT
	{
		if (this->has_value())
		{
			m_vtbl(Action::Destroy, this, nullptr);
			m_vtbl = nullptr;
		}
	}

	void swap(any& rhs) HAMON_NOEXCEPT
	{
		if (this == &rhs)
		{
			return;
		}

		if (this->has_value() && rhs.has_value())
		{
			any tmp{hamon::move(rhs)};
			move(&rhs, this);
			move(this, &tmp);
		}
		else if (this->has_value())
		{
			move(&rhs, this);
		}
		else if (rhs.has_value())
		{
			move(this, &rhs);
		}
	}

	// [any.observers], observers
	HAMON_NODISCARD bool has_value() const HAMON_NOEXCEPT
	{
		return m_vtbl != nullptr;
	}

#if !defined(HAMON_NO_RTTI) || defined(HAMON_MSVC)
	HAMON_NODISCARD std::type_info const& type() const HAMON_NOEXCEPT
	{
		if (this->has_value())
		{
			return *static_cast<std::type_info const*>(m_vtbl(Action::Type, nullptr, nullptr));
		}
		else
		{
			return typeid(void);
		}
	}
#endif
};

HAMON_WARNING_POP()

// [any.nonmembers], non-member functions
inline void swap(any& x, any& y) HAMON_NOEXCEPT
{
	// [any.nonmembers]/1
	x.swap(y);
}

}	// namespace hamon

#endif

#endif // HAMON_ANY_ANY_HPP
