/**
 *	@file	optional_constraint.hpp
 *
 *	@brief	optional_constraint の定義
 */

#ifndef HAMON_OPTIONAL_DETAIL_OPTIONAL_CONSTRAINT_HPP
#define HAMON_OPTIONAL_DETAIL_OPTIONAL_CONSTRAINT_HPP

#include <hamon/optional/optional_fwd.hpp>
#include <hamon/optional/detail/is_specialization_of_optional.hpp>
#include <hamon/optional/detail/converts_from_any_cvref.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/in_place.hpp>

namespace hamon
{

namespace optional_detail
{

template <typename T>
struct optional_constraint
{
	template <typename U>
	struct UTypeCtor
	{
		using V = hamon::remove_cvref_t<U>;

		// [optional.ctor]/23
		static const bool constructible = hamon::conjunction<
			hamon::is_constructible<T, U>,							// [optional.ctor]/23.1
			hamon::negation<hamon::is_same<V, hamon::in_place_t>>,	// [optional.ctor]/23.2
			hamon::negation<hamon::is_same<V, hamon::optional<T>>>,	// [optional.ctor]/23.3
			hamon::negation<hamon::conjunction<						// [optional.ctor]/23.4
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				optional_detail::is_specialization_of_optional<V>
			>>
		>::value;

		// [optional.ctor]/27
		static const bool implicitly = hamon::is_convertible<U, T>::value;

		static const bool nothrow = hamon::is_nothrow_constructible<T, U>::value;
	};

	template <typename UOptional>
	struct UOptionalCtor;

	template <typename U>
	struct UOptionalCtor<hamon::optional<U> const&>
	{
		// [optional.ctor]/28
		static const bool constructible = hamon::conjunction<
			hamon::is_constructible<T, U const&>,		// [optional.ctor]/28.1
			hamon::negation<hamon::conjunction<			// [optional.ctor]/28.2
				hamon::negation<hamon::is_same<hamon::remove_cv_t<T>, bool>>,
				optional_detail::converts_from_any_cvref<T, hamon::optional<U>>
			>>
		>::value;

		// [optional.ctor]/32
		static const bool implicitly = hamon::is_convertible<U const&, T>::value;

		static const bool nothrow = hamon::is_nothrow_constructible<T, U const&>::value;
	};

	template <typename U>
	struct UOptionalCtor<hamon::optional<U>&&>
	{
		// [optional.ctor]/33
		static const bool constructible = hamon::conjunction<
			hamon::is_constructible<T, U>,				// [optional.ctor]/33.1
			hamon::negation<hamon::conjunction<			// [optional.ctor]/33.2
				hamon::negation<hamon::is_same<hamon::remove_cv_t<T>, bool>>,
				optional_detail::converts_from_any_cvref<T, hamon::optional<U>>
			>>
		>::value;

		// [optional.ctor]/37
		static const bool implicitly = hamon::is_convertible<U, T>::value;

		static const bool nothrow = hamon::is_nothrow_constructible<T, U>::value;
	};
};

}	// namespace optional_detail

}	// namespace hamon

#endif // HAMON_OPTIONAL_DETAIL_OPTIONAL_CONSTRAINT_HPP
