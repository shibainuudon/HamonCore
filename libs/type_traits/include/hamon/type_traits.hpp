﻿/**
 *	@file	type_traits.hpp
 *
 *	@brief	TypeTraits library
 */

#ifndef HAMON_TYPE_TRAITS_HPP
#define HAMON_TYPE_TRAITS_HPP

#include <hamon/type_traits/accumulation.hpp>
#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/add_cv.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/add_rvalue_reference.hpp>
#include <hamon/type_traits/add_volatile.hpp>
//#include <hamon/type_traits/aligned_storage.hpp>	// deprecated in C++23
//#include <hamon/type_traits/aligned_union.hpp>	// deprecated in C++23
#include <hamon/type_traits/alignment_of.hpp>
#include <hamon/type_traits/arithmetic_promote.hpp>
#include <hamon/type_traits/basic_common_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/extent.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/has_unique_object_representations.hpp>
#include <hamon/type_traits/has_virtual_destructor.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/is_abstract.hpp>
#include <hamon/type_traits/is_aggregate.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_base_of.hpp>
#include <hamon/type_traits/is_bounded_array.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/type_traits/is_compound.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_corresponding_member.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/type_traits/is_empty.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_final.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/is_fundamental.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_move_constructible.hpp>
#include <hamon/type_traits/is_implicit_lifetime.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_invocable_r.hpp>
#include <hamon/type_traits/is_layout_compatible.hpp>
//#include <hamon/type_traits/is_literal_type.hpp>	// removed in C++20
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/is_member_function_pointer.hpp>
#include <hamon/type_traits/is_member_object_pointer.hpp>
#include <hamon/type_traits/is_member_pointer.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable_r.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_nothrow_swappable_with.hpp>
#include <hamon/type_traits/is_null_pointer.hpp>
#include <hamon/type_traits/is_object.hpp>
//#include <hamon/type_traits/is_pod.hpp>		// deprecated in C++20
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_pointer_interconvertible_base_of.hpp>
#include <hamon/type_traits/is_pointer_interconvertible_with_class.hpp>
#include <hamon/type_traits/is_polymorphic.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_rvalue_reference.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_scalar.hpp>
#include <hamon/type_traits/is_scoped_enum.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_standard_layout.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/is_swappable_with.hpp>
#include <hamon/type_traits/is_trivial.hpp>		// deprecated in C++26
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/is_union.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
//#include <hamon/type_traits/is_virtual_base_of.hpp> // since C++26
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/is_volatile.hpp>
//#include <hamon/type_traits/is_within_lifetime.hpp> // since C++26
#include <hamon/type_traits/make_int_fast_n.hpp>
#include <hamon/type_traits/make_int_least_n.hpp>
#include <hamon/type_traits/make_int_n.hpp>
#include <hamon/type_traits/make_signed.hpp>
#include <hamon/type_traits/make_uint_fast_n.hpp>
#include <hamon/type_traits/make_uint_least_n.hpp>
#include <hamon/type_traits/make_uint_n.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/type_traits/rank.hpp>
#include <hamon/type_traits/reference_constructs_from_temporary.hpp>
#include <hamon/type_traits/reference_converts_from_temporary.hpp>
#include <hamon/type_traits/remove_all_extents.hpp>
#include <hamon/type_traits/remove_const.hpp>
//#include <hamon/type_traits/remove_constref.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/remove_extent.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/remove_volatile.hpp>
//#include <hamon/type_traits/result_of.hpp>	// removed in C++20
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/type_traits/unwrap_ref_decay.hpp>
#include <hamon/type_traits/unwrap_reference.hpp>
#include <hamon/type_traits/void_t.hpp>

#endif // HAMON_TYPE_TRAITS_HPP
