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

//======================================================================================================================
//! @defgroup functions Cayley-Dickson Functions
//! @brief Functions performing computations over all Cayley-Dickson types complex, quaternions, octonions...
//======================================================================================================================

//======================================================================================================================
// Fundamental functions
//======================================================================================================================
#include <kyosu/functions/parts.hpp>
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/conj.hpp>
#include <kyosu/functions/convert.hpp>
#include <kyosu/functions/pure.hpp>
#include <kyosu/functions/if_else.hpp>
#include <kyosu/functions/arg.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/to_quaternion.hpp>


//======================================================================================================================
// core functions
//======================================================================================================================
#include <kyosu/functions/average.hpp>
#include <kyosu/functions/ceil.hpp>
#include <kyosu/functions/commutator.hpp>
#include <kyosu/functions/dec.hpp>
#include <kyosu/functions/dist.hpp>
#include <kyosu/functions/dot.hpp>
#include <kyosu/functions/fam.hpp>
#include <kyosu/functions/floor.hpp>
#include <kyosu/functions/fma.hpp>
#include <kyosu/functions/fms.hpp>
#include <kyosu/functions/fnma.hpp>
#include <kyosu/functions/fnms.hpp>
#include <kyosu/functions/frac.hpp>
#include <kyosu/functions/from_polar.hpp>
#include <kyosu/functions/fsm.hpp>
#include <kyosu/functions/hypot.hpp>
#include <kyosu/functions/horner.hpp>
#include <kyosu/functions/inc.hpp>
#include <kyosu/functions/is_denormal.hpp>
#include <kyosu/functions/is_equal.hpp>
#include <kyosu/functions/is_eqz.hpp>
#include <kyosu/functions/is_finite.hpp>
#include <kyosu/functions/is_infinite.hpp>
#include <kyosu/functions/is_imag.hpp>
#include <kyosu/functions/is_nan.hpp>
#include <kyosu/functions/is_nez.hpp>
#include <kyosu/functions/is_not_denormal.hpp>
#include <kyosu/functions/is_not_equal.hpp>
#include <kyosu/functions/is_not_finite.hpp>
#include <kyosu/functions/is_not_infinite.hpp>
#include <kyosu/functions/is_not_nan.hpp>
#include <kyosu/functions/is_not_real.hpp>
#include <kyosu/functions/is_pure.hpp>
#include <kyosu/functions/is_real.hpp>
#include <kyosu/functions/is_unitary.hpp>
#include <kyosu/functions/ldiv.hpp>
#include <kyosu/functions/lerp.hpp>
#include <kyosu/functions/manhattan.hpp>
#include <kyosu/functions/maxabs.hpp>
#include <kyosu/functions/maxmag.hpp>
#include <kyosu/functions/minabs.hpp>
#include <kyosu/functions/minmag.hpp>
#include <kyosu/functions/minus.hpp>
#include <kyosu/functions/muli.hpp>
#include <kyosu/functions/mulmi.hpp>
#include <kyosu/functions/nearest.hpp>
#include <kyosu/functions/negmaxabs.hpp>
#include <kyosu/functions/negminabs.hpp>
#include <kyosu/functions/oneminus.hpp>
#include <kyosu/functions/proj.hpp>
#include <kyosu/functions/rec.hpp>
#include <kyosu/functions/reldist.hpp>
#include <kyosu/functions/sign.hpp>
#include <kyosu/functions/slerp.hpp>
#include <kyosu/functions/sqr.hpp>
#include <kyosu/functions/sqr_abs.hpp>
#include <kyosu/functions/sqrt.hpp>
#include <kyosu/functions/to_polar.hpp>
#include <kyosu/functions/trunc.hpp>
