/**
 *	@file	matrix.hpp
 *
 *	@brief	matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_MATRIX_HPP
#define HAMON_QVM_MATRIX_MATRIX_HPP

#include <hamon/qvm/vector.hpp>
#include <hamon/qvm/detail/vector_base.hpp>
#include <hamon/qvm/detail/rebind.hpp>
#include <hamon/qvm/matrix/detail/make_diagonal_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_rotation_x_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_rotation_y_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_rotation_z_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_rotation_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_translation_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_frustum_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_perspective_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_orthographic_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_look_to_matrix.hpp>
#include <hamon/qvm/matrix/detail/make_viewport_matrix.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

template <typename T, std::size_t Row, std::size_t Col>
class matrix : public hamon::qvm::detail::vector_base<qvm::vector<T, Col>, Row>
{
private:
	using base_type = hamon::qvm::detail::vector_base<qvm::vector<T, Col>, Row>;
	using row_type = qvm::vector<T, Col>;

public:
	using value_type             = typename base_type::value_type;
	using pointer                = T*;
	using const_pointer          = T const*;
	using reference              = typename base_type::reference;
	using const_reference        = typename base_type::const_reference;
	using size_type              = typename base_type::size_type;
	using difference_type        = typename base_type::difference_type;
	using iterator               = typename base_type::iterator;
	using const_iterator         = typename base_type::const_iterator;
	using reverse_iterator       = typename base_type::reverse_iterator;
	using const_reverse_iterator = typename base_type::const_reverse_iterator;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	HAMON_CONSTEXPR
	matrix() HAMON_NOEXCEPT
		: base_type{}
	{}
	
	/**
	 *	@brief	スカラー型1つのコンストラクタ
	 *
	 *	対角成分に引数がコピーされ、それ以外は0となる
	 */
	explicit HAMON_CONSTEXPR
	matrix(T const& v) HAMON_NOEXCEPT
		: matrix{ scalar(v) }
	{}

private:
	template <std::size_t Col2, std::size_t N, std::size_t... Js>
	static HAMON_CONSTEXPR
	qvm::vector<T, Col2>
	vector_chunk_impl_helper(qvm::vector<T, N> const& v, std::size_t i, hamon::index_sequence<Js...>) HAMON_NOEXCEPT
	{
		return
		{
			v[i * Col2 + Js]...
		};
	}

	template <std::size_t Row2, std::size_t Col2, std::size_t N, std::size_t... Is>
	static HAMON_CONSTEXPR
	qvm::vector<qvm::vector<T, Col2>, Row2>
	vector_chunk_impl(qvm::vector<T, N> const& v, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
	{
		return
		{
			vector_chunk_impl_helper<Col2>(v, Is, hamon::make_index_sequence<Col2>{})...
		};
	}

	template <std::size_t Row2, std::size_t Col2, std::size_t N>
	static HAMON_CONSTEXPR
	qvm::vector<qvm::vector<T, Col2>, Row2>
	vector_chunk(qvm::vector<T, N> const& v) HAMON_NOEXCEPT
	{
		return vector_chunk_impl<Row2, Col2>(v, hamon::make_index_sequence<Row2>{});
	}

public:
	/**
	 *	@brief	スカラー型を Row * Col 個受け取るコンストラクタ
	 */
	template <typename... Args,
		hamon::enable_if_t<
			(sizeof...(Args) != 1) &&
			(sizeof...(Args) == Row * Col) &&
			hamon::conjunction<
				hamon::is_implicitly_constructible<T, Args>...
			>::value
		>* = nullptr
	>
	HAMON_CONSTEXPR
	matrix(Args const&... args) HAMON_NOEXCEPT
		: base_type{ vector_chunk<Row, Col>(qvm::vector<T, Row * Col>{args...}) }
	{}

	/**
	 *	@brief	ベクトル型をRow個受け取るコンストラクタ
	 */
	template <typename... Vecs,
		hamon::enable_if_t<
			(sizeof...(Vecs) == Row) &&
			hamon::conjunction<
				hamon::is_implicitly_constructible<row_type, Vecs>...
			>::value
		>* = nullptr
	>
	HAMON_CONSTEXPR
	matrix(Vecs const&... vecs) HAMON_NOEXCEPT
		: base_type{vecs...}
	{}

	/**
	 *	@brief	matrix<U, Row, Col>からのコンストラクタ
	 */
	template <
		typename U,
		typename = hamon::enable_if_t<
			hamon::is_implicitly_constructible<T, U>::value
		>
	>
	HAMON_CONSTEXPR
	matrix(matrix<U, Row, Col> const& rhs) HAMON_NOEXCEPT
		: base_type{rhs}
	{}

	/**
	 *	@brief	data
	 */
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR pointer
	data(void) HAMON_NOEXCEPT
	{
		return &(*this)[0][0];
	}

	/**
	 *	@brief	data
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_pointer
	data(void) const HAMON_NOEXCEPT
	{
		return &(*this)[0][0];
	}

public:
	/**
	 *	@brief	対角行列を作成します
	 */
	template <typename U, std::size_t N,
		typename = hamon::enable_if_t<
			((N == Row) && (N == Col)) &&
			hamon::is_implicitly_constructible<T, U>::value
		>
	>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	diagonal(qvm::vector<U, N> const& vec) HAMON_NOEXCEPT
	{
		return detail::make_diagonal_matrix<matrix>(vec);
	}

	template <typename... Args>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	diagonal(Args const&... args) HAMON_NOEXCEPT
	->decltype(diagonal(qvm::vector<T, sizeof...(Args)>{args...}))
	{
		return diagonal(qvm::vector<T, sizeof...(Args)>{args...});
	}

	/**
	 *	@brief	スカラー行列を作成します
	 */
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	scalar(T const& v) HAMON_NOEXCEPT
	{
		return detail::make_diagonal_matrix<matrix>(row_type{v});
	}

	/**
	 *	@brief	単位行列を作成します
	 */
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	identity() HAMON_NOEXCEPT
	{
		return scalar(T{1});
	}

	/**
	 *	@brief	X軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	rotation_x(AngleType const& angle) HAMON_NOEXCEPT
	{
		return detail::make_rotation_x_matrix<matrix>(angle);
	}

	/**
	 *	@brief	Y軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	rotation_y(AngleType const& angle) HAMON_NOEXCEPT
	{
		return detail::make_rotation_y_matrix<matrix>(angle);
	}

	/**
	 *	@brief	Z軸で回転する行列を作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	rotation_z(AngleType const& angle) HAMON_NOEXCEPT
	{
		return detail::make_rotation_z_matrix<matrix>(angle);
	}

	/**
	 *	@brief	任意のベクトルを回転軸にして回転する行列を作成します。
	 *
	 *	@param	axis	回転軸(正規化していなくてもかまいません)
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename Vector3, typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	rotation(Vector3 const& axis, AngleType const& angle) HAMON_NOEXCEPT
	{
		return detail::make_rotation_matrix<matrix>(axis, angle);
	}

	/**
	 *	@brief	平行移動行列を作成します
	 */
	template <typename U, std::size_t N,
		typename = hamon::enable_if_t<
			((N+1 == Row) && (N+1 == Col)) &&
			hamon::is_implicitly_constructible<T, U>::value
		>
	>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	translation(qvm::vector<U, N> const& vec) HAMON_NOEXCEPT
	{
		return detail::make_translation_matrix<matrix>(vec);
	}

	template <typename... Args>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	translation(Args const&... args) HAMON_NOEXCEPT
	->decltype(translation(qvm::vector<T, sizeof...(Args)>{args...}))
	{
		return translation(qvm::vector<T, sizeof...(Args)>{args...});
	}

	/**
	 *	@brief	スケーリング行列を作成します
	 */
	template <typename U, std::size_t N,
		typename = hamon::enable_if_t<
			((N+1 == Row) && (N+1 == Col)) &&
			hamon::is_implicitly_constructible<T, U>::value
		>
	>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	scaling(qvm::vector<U, N> const& vec) HAMON_NOEXCEPT
	{
		return diagonal(qvm::vector<U, N+1>{vec, 1});
	}

	template <typename... Args>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	scaling(Args const&... args) HAMON_NOEXCEPT
	->decltype(scaling(qvm::vector<T, sizeof...(Args)>{args...}))
	{
		return scaling(qvm::vector<T, sizeof...(Args)>{args...});
	}

	/**
	 *	@brief	左手座標系透視射影行列を計算します
	 *
	 *	@param	left	ビューボリュームの最小X値
	 *	@param	right	ビューボリュームの最大X値
	 *	@param	bottom	ビューボリュームの最小Y値
	 *	@param	top		ビューボリュームの最大Y値
	 *	@param	near_z	ビューボリュームの最小Z値
	 *	@param	far_z	ビューボリュームの最大Z値
	 */
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	frustum_lh(T1 left, T2 right, T3 bottom, T4 top, T5 near_z, T6 far_z) HAMON_NOEXCEPT
	->decltype(detail::make_frustum_matrix_lh<matrix>(left, right, bottom, top, near_z, far_z))
	{
		return detail::make_frustum_matrix_lh<matrix>(left, right, bottom, top, near_z, far_z);
	}

	/**
	 *	@brief	右手座標系透視射影行列を計算します
	 *
	 *	@param	left	ビューボリュームの最小X値
	 *	@param	right	ビューボリュームの最大X値
	 *	@param	bottom	ビューボリュームの最小Y値
	 *	@param	top		ビューボリュームの最大Y値
	 *	@param	near_z	ビューボリュームの最小Z値
	 *	@param	far_z	ビューボリュームの最大Z値
	 */
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	frustum_rh(T1 left, T2 right, T3 bottom, T4 top, T5 near_z, T6 far_z) HAMON_NOEXCEPT
	->decltype(detail::make_frustum_matrix_rh<matrix>(left, right, bottom, top, near_z, far_z))
	{
		return detail::make_frustum_matrix_rh<matrix>(left, right, bottom, top, near_z, far_z);
	}

	/**
	 *	@brief	左手座標系透視射影行列を計算します
	 *
	 *	@param	fovy	Y軸方向の視野角
	 *	@param	aspect	アスペクト比。(ビュー空間の 横幅/高さ)
	 *	@param	near_z	視点に近いほうのビュー平面のZ値
	 *	@param	far_z	視点から遠いほうのビュー平面のZ値
	 */
	template <typename T1, typename T2, typename T3, typename T4>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	perspective_lh(T1 const& fovy, T2 const& aspect, T3 const& near_z, T4 const& far_z) HAMON_NOEXCEPT
	->decltype(detail::make_perspective_matrix_lh<matrix>(fovy, aspect, near_z, far_z))
	{
		return detail::make_perspective_matrix_lh<matrix>(fovy, aspect, near_z, far_z);
	}

	/**
	 *	@brief	右手座標系透視射影行列を計算します
	 *
	 *	@param	fovy	Y軸方向の視野角
	 *	@param	aspect	アスペクト比。(ビュー空間の 横幅/高さ)
	 *	@param	near_z	視点に近いほうのビュー平面のZ値
	 *	@param	far_z	視点から遠いほうのビュー平面のZ値
	 */
	template <typename T1, typename T2, typename T3, typename T4>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	perspective_rh(T1 const& fovy, T2 const& aspect, T3 const& near_z, T4 const& far_z) HAMON_NOEXCEPT
	->decltype(detail::make_perspective_matrix_rh<matrix>(fovy, aspect, near_z, far_z))
	{
		return detail::make_perspective_matrix_rh<matrix>(fovy, aspect, near_z, far_z);
	}

	/**
	 *	@brief	左手座標系正射影行列を計算します
	 *
	 *	@param	left	ビューボリュームの最小X値
	 *	@param	right	ビューボリュームの最大X値
	 *	@param	bottom	ビューボリュームの最小Y値
	 *	@param	top		ビューボリュームの最大Y値
	 *	@param	near_z	ビューボリュームの最小Z値
	 *	@param	far_z	ビューボリュームの最大Z値
	 */
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	orthographic_lh(T1 left, T2 right, T3 bottom, T4 top, T5 near_z, T6 far_z) HAMON_NOEXCEPT
	->decltype(detail::make_orthographic_matrix_lh<matrix>(left, right, bottom, top, near_z, far_z))
	{
		return detail::make_orthographic_matrix_lh<matrix>(left, right, bottom, top, near_z, far_z);
	}

	/**
	 *	@brief	右手座標系正射影行列を計算します
	 *
	 *	@param	left	ビューボリュームの最小X値
	 *	@param	right	ビューボリュームの最大X値
	 *	@param	bottom	ビューボリュームの最小Y値
	 *	@param	top		ビューボリュームの最大Y値
	 *	@param	near_z	ビューボリュームの最小Z値
	 *	@param	far_z	ビューボリュームの最大Z値
	 */
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	orthographic_rh(T1 left, T2 right, T3 bottom, T4 top, T5 near_z, T6 far_z) HAMON_NOEXCEPT
	->decltype(detail::make_orthographic_matrix_rh<matrix>(left, right, bottom, top, near_z, far_z))
	{
		return detail::make_orthographic_matrix_rh<matrix>(left, right, bottom, top, near_z, far_z);
	}

	/**
	 *	@brief	視点と向きから左手座標系ビュー行列を作成します。
	 *
	 *	@param	eye		視点
	 *	@param	dir		視点の向き(正規化していなくても可)
	 *	@param	up		上方を定義するベクトル(正規化していなくても可)
	 */
	template <typename Vector3>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	look_to_lh(Vector3 const& eye, Vector3 const& dir, Vector3 const& up) HAMON_NOEXCEPT
	->decltype(detail::make_look_to_matrix<matrix>(eye, dir, up))
	{
		return detail::make_look_to_matrix<matrix>(eye, dir, up);
	}

	/**
	 *	@brief	視点と向きから右手座標系ビュー行列を作成します。
	 *
	 *	@param	eye		視点
	 *	@param	dir		視点の向き(正規化していなくても可)
	 *	@param	up		上方を定義するベクトル(正規化していなくても可)
	 */
	template <typename Vector3>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	look_to_rh(Vector3 const& eye, Vector3 const& dir, Vector3 const& up) HAMON_NOEXCEPT
	->decltype(detail::make_look_to_matrix<matrix>(eye, -dir, up))
	{
		return detail::make_look_to_matrix<matrix>(eye, -dir, up);
	}

	/**
	 *	@brief	視点と注視点から左手座標系ビュー行列を作成します。
	 *
	 *	@param	eye		視点
	 *	@param	at		注視点
	 *	@param	up		上方を定義するベクトル(正規化していなくても可)
	 */
	template <typename Vector3>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	look_at_lh(Vector3 const& eye, Vector3 const& at, Vector3 const& up) HAMON_NOEXCEPT
	->decltype(look_to_lh(eye, at - eye, up))
	{
		return look_to_lh(eye, at - eye, up);
	}

	/**
	 *	@brief	視点と注視点から右手座標系ビュー行列を作成します。
	 *
	 *	@param	eye		視点
	 *	@param	at		注視点
	 *	@param	up		上方を定義するベクトル(正規化していなくても可)
	 */
	template <typename Vector3>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	look_at_rh(Vector3 const& eye, Vector3 const& at, Vector3 const& up) HAMON_NOEXCEPT
	->decltype(look_to_rh(eye, at - eye, up))
	{
		return look_to_rh(eye, at - eye, up);
	}

	/**
	 *	@brief	ビューポート行列を作成します
	 *
	 *	@param	x
	 *	@param	y
	 *	@param	width
	 *	@param	height
	 *	@param	min_depth
	 *	@param	max_depth
	 */
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	HAMON_NODISCARD static HAMON_CONSTEXPR auto
	viewport(T1 x, T2 y, T3 width, T4 height, T5 min_depth, T6 max_depth) HAMON_NOEXCEPT
	->decltype(detail::make_viewport_matrix<matrix>(x, y, width, height, min_depth, max_depth))
	{
		return detail::make_viewport_matrix<matrix>(x, y, width, height, min_depth, max_depth);
	}
};

namespace detail
{

template <typename T, std::size_t R, std::size_t C>
struct vector_size<hamon::qvm::matrix<T, R, C>>
	: public std::integral_constant<std::size_t, R> {};

template <typename T, std::size_t R, std::size_t C>
struct vector_element<hamon::qvm::matrix<T, R, C>>
{
	using type = T;
};

template <typename T, std::size_t R, std::size_t C>
struct vector_rank<hamon::qvm::matrix<T, R, C>>
	: public std::integral_constant<std::size_t, vector_rank<T>::value + 2> {};

template <typename T, std::size_t R, std::size_t C, typename U>
struct rebind<hamon::qvm::matrix<T, R, C>, U>
{
	using type = hamon::qvm::matrix<U, R, C>;
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_MATRIX_HPP
