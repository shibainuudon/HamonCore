/**
 *	@file	quaternion.hpp
 *
 *	@brief	quaternion の定義
 */

#ifndef HAMON_QVM_QUATERNION_QUATERNION_HPP
#define HAMON_QVM_QUATERNION_QUATERNION_HPP

#include <hamon/qvm/quaternion/quaternion_fwd.hpp>
#include <hamon/qvm/quaternion/detail/matrix_to_quaternion.hpp>
#include <hamon/qvm/quaternion/detail/quaternion_to_matrix.hpp>
#include <hamon/qvm/quaternion/detail/make_look_at_quaternion.hpp>
#include <hamon/qvm/detail/vector_xyzw.hpp>
#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/matrix/matrix.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/cmath/ranges/sin.hpp>
#include <hamon/cmath/ranges/cos.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

template <typename T, std::size_t N>
class quaternion : public hamon::qvm::detail::vector_xyzw<T, N>
{
private:
	using base_type = hamon::qvm::detail::vector_xyzw<T, N>;

public:
	using value_type             = typename base_type::value_type;
	using pointer                = typename base_type::pointer;
	using const_pointer          = typename base_type::const_pointer;
	using reference              = typename base_type::reference;
	using const_reference        = typename base_type::const_reference;
	using size_type              = typename base_type::size_type;
	using difference_type        = typename base_type::difference_type;
	using iterator               = typename base_type::iterator;
	using const_iterator         = typename base_type::const_iterator;
	using reverse_iterator       = typename base_type::reverse_iterator;
	using const_reverse_iterator = typename base_type::const_reverse_iterator;

	using real_type = value_type;
	using imag_type = hamon::qvm::vector<T, 3>;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	HAMON_CONSTEXPR
	quaternion() HAMON_NOEXCEPT
		: base_type{}
	{}

	/**
	 *	@brief	引数4つのコンストラクタ
	 */
	HAMON_CONSTEXPR
	quaternion(T x, T y, T z, T w) HAMON_NOEXCEPT
		: base_type{x, y, z, w}
	{}

	/**
	 *	@brief	虚部と実部のコンストラクタ
	 */
	HAMON_CONSTEXPR
	quaternion(imag_type const& imag, real_type const& real) HAMON_NOEXCEPT
		: base_type{ imag.x(), imag.y(), imag.z(), real }
	{}

	/**
	 *	@brief	quaternion<U, N>からのコンストラクタ
	 */
	template <
		typename U,
		typename = hamon::enable_if_t<
			hamon::is_implicitly_constructible<T, U>::value
		>
	>
	HAMON_CONSTEXPR
	quaternion(quaternion<U> const& rhs) HAMON_NOEXCEPT
		: base_type{ rhs }
	{}

	/**
	 *	@brief	Matrix3x3 からのコンストラクタ
	 */
	explicit HAMON_CXX14_CONSTEXPR
	quaternion(matrix<T, 3, 3> const& q) HAMON_NOEXCEPT
		: base_type(detail::matrix_to_quaternion(q))
	{}

	/**
	 *	@brief	Matrix3x3 への変換
	 */
	explicit HAMON_CONSTEXPR
	operator matrix<T, 3, 3>() const HAMON_NOEXCEPT
	{
		return detail::quaternion_to_matrix(*this);
	}

	/**
	 *	@brief	実部を取得します
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR real_type
	real() const HAMON_NOEXCEPT
	{
		return this->w();
	}

	/**
	 *	@brief	虚部を取得します
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR imag_type
	imag() const HAMON_NOEXCEPT
	{
		return this->xyz();
	}

public:
	/**
	 *	@brief	単位クォータニオンを作成します
	 */
	HAMON_NODISCARD static HAMON_CONSTEXPR quaternion
	identity() HAMON_NOEXCEPT
	{
		return {0, 0, 0, 1};
	}

	/**
	 *	@brief	X軸で回転するクォータニオンを作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR quaternion
	rotation_x(AngleType const& angle) HAMON_NOEXCEPT
	{
		return
		{
			T(hamon::ranges::sin(angle * 0.5)),
			0,
			0,
			T(hamon::ranges::cos(angle * 0.5))
		};
	}

	/**
	 *	@brief	Y軸で回転するクォータニオンを作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR quaternion
	rotation_y(AngleType const& angle) HAMON_NOEXCEPT
	{
		return
		{
			0,
			T(hamon::ranges::sin(angle * 0.5)),
			0,
			T(hamon::ranges::cos(angle * 0.5))
		};
	}

	/**
	 *	@brief	Z軸で回転するクォータニオンを作成します。
	 *
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR quaternion
	rotation_z(AngleType const& angle) HAMON_NOEXCEPT
	{
		return
		{
			0,
			0,
			T(hamon::ranges::sin(angle * 0.5)),
			T(hamon::ranges::cos(angle * 0.5))
		};
	}

	/**
	 *	@brief	任意のベクトルを回転軸にして回転するクォータニオンを作成します。
	 *
	 *	@param	axis	回転軸(正規化していなくてもかまいません)
	 *	@param	angle	回転角度(ラジアン・時計回り)
	 */
	template <typename T2, typename AngleType>
	HAMON_NODISCARD static HAMON_CONSTEXPR quaternion
	rotation(vector<T2, 3> const& axis, AngleType const& angle) HAMON_NOEXCEPT
	{
		return
		{
			normalize(axis) * hamon::ranges::sin(angle * 0.5f),
			static_cast<T>(hamon::ranges::cos(angle * 0.5f))
		};
	}

	/**
	 *	任意の方向を向くクォータニオンを取得します
	 *
	 *	@param	eye		視点位置
	 *	@param	lookat	注視点
	 *	@param	up		上方向(正規化していなくても可)
	 */
	HAMON_NODISCARD static HAMON_CONSTEXPR quaternion
	look_at(
		vector<T, 3> const& eye,
		vector<T, 3> const& lookat,
		vector<T, 3> const& up) HAMON_NOEXCEPT
	{
		return detail::make_look_at_quaternion<quaternion>(eye, lookat, up);
	}
};

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_QUATERNION_QUATERNION_HPP
