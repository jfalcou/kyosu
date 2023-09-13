//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

//======================================================================================================================
//! @defgroup functions Cayley-Dickson Functions
//! @brief Functions performing computations over all caylet-dickson types complex, quaternions, octonions...
//======================================================================================================================
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/average.hpp>
#include <kyosu/functions/ceil.hpp>
#include <kyosu/functions/conj.hpp>
#include <kyosu/functions/cos.hpp>
#include <kyosu/functions/cosh.hpp>
#include <kyosu/functions/cospi.hpp>
#include <kyosu/functions/cot.hpp>
#include <kyosu/functions/cotpi.hpp>
#include <kyosu/functions/coth.hpp>
#include <kyosu/functions/convert.hpp>
#include <kyosu/functions/csc.hpp>
#include <kyosu/functions/cscpi.hpp>
#include <kyosu/functions/csch.hpp>
#include <kyosu/functions/dec.hpp>
#include <kyosu/functions/dist.hpp>
#include <kyosu/functions/dot.hpp>
#include <kyosu/functions/exp.hpp>
#include <kyosu/functions/exp10.hpp>
#include <kyosu/functions/exp2.hpp>
#include <kyosu/functions/exp_i.hpp>
#include <kyosu/functions/exp_ipi.hpp>
#include <kyosu/functions/expm1.hpp>
#include <kyosu/functions/expmx2.hpp>
#include <kyosu/functions/expx2.hpp>
#include <kyosu/functions/floor.hpp>
#include <kyosu/functions/frac.hpp>
#include <kyosu/functions/hypot.hpp>
#include <kyosu/functions/if_else.hpp>
#include <kyosu/functions/inc.hpp>
#include <kyosu/functions/ipart.hpp>
#include <kyosu/functions/is_denormal.hpp>
#include <kyosu/functions/is_equal.hpp>
#include <kyosu/functions/is_eqz.hpp>
#include <kyosu/functions/is_finite.hpp>
#include <kyosu/functions/is_infinite.hpp>
#include <kyosu/functions/is_nan.hpp>
#include <kyosu/functions/is_nez.hpp>
#include <kyosu/functions/is_not_denormal.hpp>
#include <kyosu/functions/is_not_equal.hpp>
#include <kyosu/functions/is_not_finite.hpp>
#include <kyosu/functions/is_not_infinite.hpp>
#include <kyosu/functions/is_not_nan.hpp>
#include <kyosu/functions/is_not_real.hpp>
#include <kyosu/functions/is_real.hpp>
#include <kyosu/functions/is_unitary.hpp>
#include <kyosu/functions/jpart.hpp>
#include <kyosu/functions/kpart.hpp>
#include <kyosu/functions/lerp.hpp>
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/log10.hpp>
#include <kyosu/functions/log1p.hpp>
#include <kyosu/functions/log_abs.hpp>
#include <kyosu/functions/log2.hpp>
#include <kyosu/functions/lpnorm.hpp>
#include <kyosu/functions/manhattan.hpp>
#include <kyosu/functions/minus.hpp>
#include <kyosu/functions/nearest.hpp>
#include <kyosu/functions/oneminus.hpp>
#include <kyosu/functions/pow.hpp>
#include <kyosu/functions/pow1p.hpp>
#include <kyosu/functions/pow_abs.hpp>
#include <kyosu/functions/powm1.hpp>
#include <kyosu/functions/pure.hpp>
#include <kyosu/functions/radinpi.hpp>
#include <kyosu/functions/real.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/reldist.hpp>
#include <kyosu/functions/sec.hpp>
#include <kyosu/functions/secpi.hpp>
#include <kyosu/functions/sech.hpp>
#include <kyosu/functions/sign.hpp>
#include <kyosu/functions/sin.hpp>
#include <kyosu/functions/sinc.hpp>
#include <kyosu/functions/sincos.hpp>
#include <kyosu/functions/sinpi.hpp>
#include <kyosu/functions/sinpicospi.hpp>
#include <kyosu/functions/sinh.hpp>
#include <kyosu/functions/sinhcosh.hpp>
#include <kyosu/functions/slerp.hpp>
#include <kyosu/functions/sqr.hpp>
#include <kyosu/functions/sqr_abs.hpp>
#include <kyosu/functions/sqrt.hpp>
#include <kyosu/functions/tan.hpp>
#include <kyosu/functions/tanpi.hpp>
#include <kyosu/functions/tanh.hpp>
#include <kyosu/functions/trunc.hpp>

//======================================================================================================================
//! @brief Functions performing computations over complex or real elements only.
//======================================================================================================================

#include <kyosu/complex/acos.hpp>
#include <kyosu/complex/acosh.hpp>
#include <kyosu/complex/acot.hpp>
#include <kyosu/complex/acospi.hpp>
#include <kyosu/complex/acoth.hpp>
#include <kyosu/complex/acotpi.hpp>
#include <kyosu/complex/acsc.hpp>
#include <kyosu/complex/acsch.hpp>
#include <kyosu/complex/acscpi.hpp>
#include <kyosu/complex/arg.hpp>
#include <kyosu/complex/asec.hpp>
#include <kyosu/complex/asech.hpp>
#include <kyosu/complex/asecpi.hpp>
#include <kyosu/complex/asin.hpp>
#include <kyosu/complex/asinh.hpp>
#include <kyosu/complex/asinpi.hpp>
#include <kyosu/complex/atan.hpp>
#include <kyosu/complex/atanh.hpp>
#include <kyosu/complex/atanpi.hpp>
#include <kyosu/complex/digamma.hpp>
#include <kyosu/complex/is_imag.hpp>
#include <kyosu/complex/log_abs_gamma.hpp>
#include <kyosu/complex/log_gamma.hpp>
#include <kyosu/complex/polar.hpp>
#include <kyosu/complex/tgamma.hpp>
#include <kyosu/functions/from_polar.hpp>
#include <kyosu/functions/to_polar.hpp>

//======================================================================================================================
//! @brief Functions performing computations over quaternion complex or real elements only.
//======================================================================================================================


#include <kyosu/functions/from_angle_axis.hpp>
#include <kyosu/functions/from_cylindrical.hpp>
#include <kyosu/functions/from_euler.hpp>
#include <kyosu/functions/from_multipolar.hpp>
#include <kyosu/functions/from_semipolar.hpp>
#include <kyosu/functions/from_spherical.hpp>
#include <kyosu/functions/rot_angle.hpp>
#include <kyosu/functions/rot_axis.hpp>
#include <kyosu/functions/rotate_vec.hpp>
#include <kyosu/functions/to_angle_axis.hpp>
#include <kyosu/functions/to_cylindrical.hpp>
#include <kyosu/functions/to_euler.hpp>
#include <kyosu/functions/to_multipolar.hpp>
#include <kyosu/functions/to_rotation_matrix.hpp>
#include <kyosu/functions/to_semipolar.hpp>
#include <kyosu/functions/to_spherical.hpp>
