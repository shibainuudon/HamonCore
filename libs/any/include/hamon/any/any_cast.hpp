/**
 *	@file	any_cast.hpp
 *
 *	@brief	any_cast の定義
 */

#ifndef HAMON_ANY_ANY_CAST_HPP
#define HAMON_ANY_ANY_CAST_HPP

#include <hamon/any/config.hpp>

#if defined(HAMON_USE_STD_ANY)

#include <any>

namespace hamon
{

using std::any_cast;

}	// namespace hamon

#else

#include <hamon/any/any.hpp>
#include <hamon/any/bad_any_cast.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace any_detail
{

struct any_caster
{
	template <typename T>
	static T* get(hamon::any* operand) HAMON_NOEXCEPT
	{
		if (operand == nullptr)
		{
			return nullptr;
		}

		// RTTIがOffのときはm_vtblのアドレスを見て型が同じかどうか判定したいが、
		// MSVCで最適化がOnだと、違う型でも同じアドレスになる場合があるもよう。
		// (例えばintとlongなど)
		// 幸い、MSVCではRTTIがOffでもtypeid演算子自体は使えるようなので、
		// MSVCのときはtypeidで判断する。

#if !defined(HAMON_NO_RTTI) || defined(HAMON_MSVC)
		if (operand->type() == typeid(T))
#else
		if (operand->m_vtbl == &hamon::any::Impl<T>::vtbl)
#endif
		{
			return operand->get<T>();
		}

		return nullptr;
	}
};

}	// namespace any_detail

template <typename T>
HAMON_NODISCARD inline T*
any_cast(hamon::any* operand) HAMON_NOEXCEPT
{
	// [any.nonmembers]/9
	return any_detail::any_caster::get<T>(operand);
}

template <typename T>
HAMON_NODISCARD inline T const*
any_cast(hamon::any const* operand) HAMON_NOEXCEPT
{
	// [any.nonmembers]/9
	return hamon::any_cast<T>(const_cast<hamon::any*>(operand));
}

template <typename T>
HAMON_NODISCARD inline T
any_cast(hamon::any const& operand)
{
	// [any.nonmembers]/4
	using U = hamon::remove_cvref_t<T>;

	// [any.nonmembers]/5
	static_assert(hamon::is_constructible<T, const U&>::value, "");

	auto ptr = hamon::any_cast<U>(&operand);

	// [any.nonmembers]/7
	if (ptr == nullptr)
	{
		hamon::detail::throw_bad_any_cast();
	}

	// [any.nonmembers]/6
	return static_cast<T>(*ptr);
}

template <typename T>
HAMON_NODISCARD inline T
any_cast(any& operand)
{
	// [any.nonmembers]/4
	using U = hamon::remove_cvref_t<T>;

	// [any.nonmembers]/5
	static_assert(hamon::is_constructible<T, U&>::value, "");

	auto ptr = hamon::any_cast<U>(&operand);

	// [any.nonmembers]/7
	if (ptr == nullptr)
	{
		hamon::detail::throw_bad_any_cast();
	}

	// [any.nonmembers]/6
	return static_cast<T>(*ptr);
}

template <typename T>
HAMON_NODISCARD inline T
any_cast(any&& operand)
{
	// [any.nonmembers]/4
	using U = hamon::remove_cvref_t<T>;

	// [any.nonmembers]/5
	static_assert(hamon::is_constructible<T, U>::value, "");

	auto ptr = hamon::any_cast<U>(&operand);

	// [any.nonmembers]/7
	if (ptr == nullptr)
	{
		hamon::detail::throw_bad_any_cast();
	}

	// [any.nonmembers]/6
	return static_cast<T>(hamon::move(*ptr));
}

}	// namespace hamon

#endif

#endif // HAMON_ANY_ANY_CAST_HPP
