/**
 *	@file	matrix.hpp
 *
 *	@brief	matrix の定義
 */

#ifndef HAMON_QVM_MATRIX_MATRIX_HPP
#define HAMON_QVM_MATRIX_MATRIX_HPP

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/operators.hpp>
#include <hamon/qvm/vector/normalize.hpp>
#include <hamon/qvm/vector/cross.hpp>
#include <hamon/qvm/detail/vector_base.hpp>
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
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace qvm
{

template <typename T, hamon::size_t Row, hamon::size_t Col>
class matrix : public hamon::qvm::detail::vector_base<qvm::vector<T, Col>, Row>
{
private:
	using base_type = hamon::qvm::detail::vector_base<qvm::vector<T, Col>, Row>;
	using row_type = qvm::vector<T, Col>;

	template <typename>
	struct is_square_matrix
	{
		static const bool value = (Row == Col);
	};

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
	template <typename Dummy = void, typename = hamon::enable_if_t<is_square_matrix<Dummy>::value>>
	explicit HAMON_CONSTEXPR
	matrix(T const& v) HAMON_NOEXCEPT
		: matrix{ scalar(v) }
	{}

private:
	template <hamon::size_t Col2, hamon::size_t N, hamon::size_t... Js>
	static HAMON_CONSTEXPR
	qvm::vector<T, Col2>
	vector_chunk_impl_helper(qvm::vector<T, N> const& v, hamon::size_t i, hamon::index_sequence<Js...>) HAMON_NOEXCEPT
	{
		return
		{
			v[i * Col2 + Js]...
		};
	}

	template <hamon::size_t Row2, hamon::size_t Col2, hamon::size_t N, hamon::size_t... Is>
	static HAMON_CONSTEXPR
	qvm::vector<qvm::vector<T, Col2>, Row2>
	vector_chunk_impl(qvm::vector<T, N> const& v, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
	{
		return
		{
			vector_chunk_impl_helper<Col2>(v, Is, hamon::make_index_sequence<Col2>{})...
		};
	}

	template <hamon::size_t Row2, hamon::size_t Col2, hamon::size_t N>
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
	template <typename U, hamon::size_t N,
		typename = hamon::enable_if_t<
			((N == Row) && (N == Col)) &&
			hamon::is_implicitly_constructible<T, U>::value
		>
	>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	diagonal(qvm::vector<U, N> const& vec) HAMON_NOEXCEPT
	{
		return detail::make_diagonal_matrix<matrix>::invoke(vec);
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
	template <typename Dummy = void, typename = hamon::enable_if_t<is_square_matrix<Dummy>::value>>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	scalar(T const& v) HAMON_NOEXCEPT
	{
		return detail::make_diagonal_matrix<matrix>::invoke(row_type{v});
	}

	/**
	 *	@brief	単位行列を作成します
	 */
	template <typename Dummy = void, typename = hamon::enable_if_t<is_square_matrix<Dummy>::value>>
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
		return detail::make_rotation_x_matrix<matrix>::invoke(angle);
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
		return detail::make_rotation_y_matrix<matrix>::invoke(angle);
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
		return detail::make_rotation_z_matrix<matrix>::invoke(angle);
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
		return detail::make_rotation_matrix<matrix>::invoke(axis, angle);
	}

	/**
	 *	@brief	平行移動行列を作成します
	 */
	template <typename U, hamon::size_t N,
		typename = hamon::enable_if_t<
			((N+1 == Row) && (N+1 == Col)) &&
			hamon::is_implicitly_constructible<T, U>::value
		>
	>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	translation(qvm::vector<U, N> const& vec) HAMON_NOEXCEPT
	{
		return detail::make_translation_matrix<matrix>::invoke(vec);
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
	template <typename U, hamon::size_t N,
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
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	frustum_lh(T left, T right, T bottom, T top, T near_z, T far_z) HAMON_NOEXCEPT
	{
		return detail::make_frustum_matrix_lh<matrix>::invoke(
			left, right, bottom, top, near_z, far_z);
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
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	frustum_rh(T left, T right, T bottom, T top, T near_z, T far_z) HAMON_NOEXCEPT
	{
		return detail::make_frustum_matrix_rh<matrix>::invoke(
			left, right, bottom, top, near_z, far_z);
	}

	/**
	 *	@brief	左手座標系透視射影行列を計算します
	 *
	 *	@param	fovy	Y軸方向の視野角
	 *	@param	aspect	アスペクト比。(ビュー空間の 横幅/高さ)
	 *	@param	near_z	視点に近いほうのビュー平面のZ値
	 *	@param	far_z	視点から遠いほうのビュー平面のZ値
	 */
	template <typename Angle>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	perspective_lh(Angle const& fovy, T const& aspect, T const& near_z, T const& far_z) HAMON_NOEXCEPT
	{
		return detail::make_perspective_matrix_lh<matrix>::invoke(
			fovy, aspect, near_z, far_z);
	}

	/**
	 *	@brief	右手座標系透視射影行列を計算します
	 *
	 *	@param	fovy	Y軸方向の視野角
	 *	@param	aspect	アスペクト比。(ビュー空間の 横幅/高さ)
	 *	@param	near_z	視点に近いほうのビュー平面のZ値
	 *	@param	far_z	視点から遠いほうのビュー平面のZ値
	 */
	template <typename Angle>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	perspective_rh(Angle const& fovy, T const& aspect, T const& near_z, T const& far_z) HAMON_NOEXCEPT
	{
		return detail::make_perspective_matrix_rh<matrix>::invoke(
			fovy, aspect, near_z, far_z);
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
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	orthographic_lh(T left, T right, T bottom, T top, T near_z, T far_z) HAMON_NOEXCEPT
	{
		return detail::make_orthographic_matrix_lh<matrix>::invoke(
			left, right, bottom, top, near_z, far_z);
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
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	orthographic_rh(T left, T right, T bottom, T top, T near_z, T far_z) HAMON_NOEXCEPT
	{
		return detail::make_orthographic_matrix_rh<matrix>::invoke(
			left, right, bottom, top, near_z, far_z);
	}

	/**
	 *	@brief	視点と向きから左手座標系ビュー行列を作成します。
	 *
	 *	@param	eye		視点
	 *	@param	dir		視点の向き(正規化していなくても可)
	 *	@param	up		上方を定義するベクトル(正規化していなくても可)
	 */
	template <template <typename, hamon::size_t> class Vector>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	look_to_lh(
		Vector<T, 3> const& eye,
		Vector<T, 3> const& dir,
		Vector<T, 3> const& up) HAMON_NOEXCEPT
	{
		return detail::make_look_to_matrix<matrix>::invoke(eye, dir, up);
	}

	/**
	 *	@brief	視点と向きから右手座標系ビュー行列を作成します。
	 *
	 *	@param	eye		視点
	 *	@param	dir		視点の向き(正規化していなくても可)
	 *	@param	up		上方を定義するベクトル(正規化していなくても可)
	 */
	template <template <typename, hamon::size_t> class Vector>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	look_to_rh(
		Vector<T, 3> const& eye,
		Vector<T, 3> const& dir,
		Vector<T, 3> const& up) HAMON_NOEXCEPT
	{
		return detail::make_look_to_matrix<matrix>::invoke(eye, -dir, up);
	}

	/**
	 *	@brief	視点と注視点から左手座標系ビュー行列を作成します。
	 *
	 *	@param	eye		視点
	 *	@param	at		注視点
	 *	@param	up		上方を定義するベクトル(正規化していなくても可)
	 */
	template <template <typename, hamon::size_t> class Vector>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	look_at_lh(
		Vector<T, 3> const& eye,
		Vector<T, 3> const& at,
		Vector<T, 3> const& up) HAMON_NOEXCEPT
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
	template <template <typename, hamon::size_t> class Vector>
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	look_at_rh(
		Vector<T, 3> const& eye,
		Vector<T, 3> const& at,
		Vector<T, 3> const& up) HAMON_NOEXCEPT
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
	HAMON_NODISCARD static HAMON_CONSTEXPR matrix
	viewport(T x, T y, T width, T height, T min_depth, T max_depth) HAMON_NOEXCEPT
	{
		return detail::make_viewport_matrix<matrix>::invoke(
			x, y, width, height, min_depth, max_depth);
	}
};

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_MATRIX_MATRIX_HPP
