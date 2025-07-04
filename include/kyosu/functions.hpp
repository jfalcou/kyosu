//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/module/bessel.hpp>

//======================================================================================================================
//! @defgroup functions Cayley-Dickson Functions
//! @brief Functions performing computations over all Cayley-Dickson types complex, quaternions, octonions...
//======================================================================================================================

//======================================================================================================================
// Fundamental functions
//=================================)=====================================================================================
#include <kyosu/functions/parts.hpp>
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/conj.hpp>
#include <kyosu/functions/convert.hpp>
#include <kyosu/functions/pure.hpp>
#include <kyosu/functions/if_else.hpp>
#include <kyosu/functions/arg.hpp>

//======================================================================================================================
// Arithmetic and math
//======================================================================================================================
#include <kyosu/functions/acos.hpp>
#include <kyosu/functions/acosh.hpp>
#include <kyosu/functions/acospi.hpp>
#include <kyosu/functions/acot.hpp>
#include <kyosu/functions/acoth.hpp>
#include <kyosu/functions/acotpi.hpp>
#include <kyosu/functions/add.hpp>
#include <kyosu/functions/agd.hpp>
#include <kyosu/functions/am.hpp>
#include <kyosu/functions/atanpi.hpp>
#include <kyosu/functions/acsc.hpp>
#include <kyosu/functions/acscpi.hpp>
#include <kyosu/functions/acsch.hpp>
#include <kyosu/functions/asec.hpp>
#include <kyosu/functions/asecpi.hpp>
#include <kyosu/functions/asech.hpp>
#include <kyosu/functions/asin.hpp>
#include <kyosu/functions/asinpi.hpp>
#include <kyosu/functions/asinh.hpp>
#include <kyosu/functions/associator.hpp>
#include <kyosu/functions/atan.hpp>
#include <kyosu/functions/atanh.hpp>
#include <kyosu/functions/atanpi.hpp>
#include <kyosu/functions/average.hpp>

#include <kyosu/functions/beta.hpp>
#include <kyosu/functions/ceil.hpp>
#include <kyosu/functions/chi.hpp>
#include <kyosu/functions/commutator.hpp>
#include <kyosu/functions/cos.hpp>
#include <kyosu/functions/cosh.hpp>
#include <kyosu/functions/cospi.hpp>
#include <kyosu/functions/cot.hpp>
#include <kyosu/functions/cotpi.hpp>
#include <kyosu/functions/coth.hpp>
#include <kyosu/functions/csc.hpp>
#include <kyosu/functions/cscpi.hpp>
#include <kyosu/functions/csch.hpp>
#include <kyosu/functions/dec.hpp>
#include <kyosu/functions/deta.hpp>
#include <kyosu/functions/digamma.hpp>
#include <kyosu/functions/dist.hpp>
#include <kyosu/functions/div.hpp>
#include <kyosu/functions/dot.hpp>
#include <kyosu/functions/ellint_fe.hpp>
#include <kyosu/functions/ellint_rc.hpp>
#include <kyosu/functions/ellint_rd.hpp>
#include <kyosu/functions/ellint_rf.hpp>
#include <kyosu/functions/ellint_rg.hpp>
#include <kyosu/functions/ellint_rj.hpp>
#include <kyosu/functions/erf.hpp>
#include <kyosu/functions/erfcx.hpp>
#include <kyosu/functions/erfi.hpp>
#include <kyosu/functions/eta.hpp>
#include <kyosu/functions/exp.hpp>
#include <kyosu/functions/exp10.hpp>
#include <kyosu/functions/exp2.hpp>
#include <kyosu/functions/exp_i.hpp>
#include <kyosu/functions/exp_int.hpp>
#include <kyosu/functions/exp_ipi.hpp>
#include <kyosu/functions/expm1.hpp>
#include <kyosu/functions/expmx2.hpp>
#include <kyosu/functions/expx2.hpp>
#include <kyosu/functions/faddeeva.hpp>
#include <kyosu/functions/fam.hpp>
#include <kyosu/functions/floor.hpp>
#include <kyosu/functions/fma.hpp>
#include <kyosu/functions/fms.hpp>
#include <kyosu/functions/fnma.hpp>
#include <kyosu/functions/fnms.hpp>
#include <kyosu/functions/frac.hpp>
#include <kyosu/functions/from_polar.hpp>
#include <kyosu/functions/fsm.hpp>
#include <kyosu/functions/gd.hpp>
#include <kyosu/functions/gegenbauer.hpp>
#include <kyosu/functions/hypergeometric.hpp>
#include <kyosu/functions/hypot.hpp>
#include <kyosu/functions/horner.hpp>
#include <kyosu/functions/inc.hpp>
#include <kyosu/functions/is_cinf.hpp>
#include <kyosu/functions/is_denormal.hpp>
#include <kyosu/functions/is_equal.hpp>
#include <kyosu/functions/is_eqz.hpp>
#include <kyosu/functions/is_finite.hpp>
#include <kyosu/functions/is_flint.hpp>
#include <kyosu/functions/is_fnan.hpp>
#include <kyosu/functions/is_infinite.hpp>
#include <kyosu/functions/is_imag.hpp>
#include <kyosu/functions/is_nan.hpp>
#include <kyosu/functions/is_nez.hpp>
#include <kyosu/functions/is_not_cinf.hpp>
#include <kyosu/functions/is_not_denormal.hpp>
#include <kyosu/functions/is_not_equal.hpp>
#include <kyosu/functions/is_not_finite.hpp>
#include <kyosu/functions/is_not_flint.hpp>
#include <kyosu/functions/is_not_fnan.hpp>
#include <kyosu/functions/is_not_infinite.hpp>
#include <kyosu/functions/is_not_nan.hpp>
#include <kyosu/functions/is_not_real.hpp>
#include <kyosu/functions/is_pure.hpp>
#include <kyosu/functions/is_real.hpp>
#include <kyosu/functions/is_unitary.hpp>
#include <kyosu/functions/jacobi_elliptic.hpp>
#include <kyosu/functions/kummer.hpp>
#include <kyosu/functions/lambda.hpp>
#include <kyosu/functions/lbeta.hpp>
#include <kyosu/functions/ldiv.hpp>
#include <kyosu/functions/legendre.hpp>
#include <kyosu/functions/lerp.hpp>
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/log10.hpp>
#include <kyosu/functions/log1p.hpp>
#include <kyosu/functions/log_abs.hpp>
#include <kyosu/functions/log_abs_gamma.hpp>
#include <kyosu/functions/log_gamma.hpp>
#include <kyosu/functions/log2.hpp>
#include <kyosu/functions/lpnorm.hpp>
#include <kyosu/functions/lrising_factorial.hpp>
#include <kyosu/functions/rising_factorial.hpp>
#include <kyosu/functions/manhattan.hpp>
#include <kyosu/functions/maxabs.hpp>
#include <kyosu/functions/maxmag.hpp>
#include <kyosu/functions/minabs.hpp>
#include <kyosu/functions/minmag.hpp>
#include <kyosu/functions/minus.hpp>
#include <kyosu/functions/mul.hpp>
#include <kyosu/functions/muli.hpp>
#include <kyosu/functions/mulmi.hpp>
#include <kyosu/functions/nearest.hpp>
#include <kyosu/functions/negmaxabs.hpp>
#include <kyosu/functions/negminabs.hpp>
#include <kyosu/functions/oneminus.hpp>
#include <kyosu/functions/pow.hpp>
#include <kyosu/functions/pow1p.hpp>
#include <kyosu/functions/pow_abs.hpp>
#include <kyosu/functions/powm1.hpp>
#include <kyosu/functions/proj.hpp>
#include <kyosu/functions/radinpi.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/reldist.hpp>
#include <kyosu/functions/reverse_horner.hpp>
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
#include <kyosu/functions/sinhc.hpp>
#include <kyosu/functions/sinhcosh.hpp>
#include <kyosu/functions/slerp.hpp>
#include <kyosu/functions/sqr.hpp>
#include <kyosu/functions/sqr_abs.hpp>
#include <kyosu/functions/sqrt.hpp>
#include <kyosu/functions/sub.hpp>
#include <kyosu/functions/tan.hpp>
#include <kyosu/functions/tanpi.hpp>
#include <kyosu/functions/tanh.hpp>
#include <kyosu/functions/tchebytchev.hpp>
#include <kyosu/functions/tgamma.hpp>
#include <kyosu/functions/tgamma_inv.hpp>
#include <kyosu/functions/to_cylindrical.hpp>
#include <kyosu/functions/to_polar.hpp>
#include <kyosu/functions/tricomi.hpp>
#include <kyosu/functions/trunc.hpp>
#include <kyosu/functions/zeta.hpp>

#include <kyosu/functions/bessel_j.hpp>
#include <kyosu/functions/bessel_y.hpp>
#include <kyosu/functions/bessel_h.hpp>
#include <kyosu/functions/bessel_i.hpp>
#include <kyosu/functions/bessel_k.hpp>

#include <kyosu/functions/airy.hpp>
#include <kyosu/functions/airy_ai.hpp>
#include <kyosu/functions/airy_bi.hpp>

//======================================================================================================================
// Functions performing computations over quaternion complex or real elements only.
//======================================================================================================================

#include <kyosu/functions/align.hpp>
#include <kyosu/functions/from_angle_axis.hpp>
#include <kyosu/functions/from_cylindrical.hpp>
#include <kyosu/functions/from_cylindrospherical.hpp>
#include <kyosu/functions/from_euler.hpp>
#include <kyosu/functions/from_multipolar.hpp>
#include <kyosu/functions/from_rotation_matrix.hpp>
#include <kyosu/functions/from_semipolar.hpp>
#include <kyosu/functions/from_spherical.hpp>
#include <kyosu/functions/rot_angle.hpp>
#include <kyosu/functions/rot_axis.hpp>
#include <kyosu/functions/rotate_vec.hpp>
#include <kyosu/functions/to_angle_axis.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/to_cylindrical.hpp>
#include <kyosu/functions/to_cylindrospherical.hpp>
#include <kyosu/functions/to_euler.hpp>
#include <kyosu/functions/to_multipolar.hpp>
#include <kyosu/functions/to_quaternion.hpp>
#include <kyosu/functions/to_rotation_matrix.hpp>
#include <kyosu/functions/to_semipolar.hpp>
#include <kyosu/functions/to_spherical.hpp>
