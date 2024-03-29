﻿/**
 *	@file	make_translation_matrix.hpp
 *
 *	@brief	make_translation_matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_DETAIL_MAKE_TRANSLATION_MATRIX_HPP
#define HAMON_QVM_MATRIX_DETAIL_MAKE_TRANSLATION_MATRIX_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename Matrix>
struct make_translation_matrix;

template <
	template <typename, hamon::size_t, hamon::size_t> class Matrix,
	typename T, hamon::size_t N
>
struct make_translation_matrix<Matrix<T, N, N>>
{
private:
	static const hamon::size_t M = N - 1;

	template <template <typename, hamon::size_t> class Vector, hamon::size_t... Js>
	HAMON_NODISCARD static HAMON_CONSTEXPR Vector<T, N>
	impl(Vector<T, M> const& v, hamon::size_t i, hamon::index_sequence<Js...>) HAMON_NOEXCEPT
	{
		return i == M ?
			Vector<T, N>{ v, 1 } :
			Vector<T, N>{ (i == Js ? 1 : 0)... };
	}

	template <template <typename, hamon::size_t> class Vector, hamon::size_t... Is>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, N, N>
	impl(Vector<T, M> const& v, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
	{
		return { impl(v, Is, hamon::make_index_sequence<N>{})... };
	}

public:
	template <template <typename, hamon::size_t> class Vector>
	HAMON_NODISCARD static HAMON_CONSTEXPR Matrix<T, N, N>
	invoke(Vector<T, M> const& v) HAMON_NOEXCEPT
	{
		return impl(v, hamon::make_index_sequence<N>{});
	}
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_DETAIL_MAKE_TRANSLATION_MATRIX_HPP
