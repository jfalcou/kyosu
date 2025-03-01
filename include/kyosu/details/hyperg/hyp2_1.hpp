//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/functions/expm1.hpp>
#include <kyosu/functions/abs.hpp>
#include <kyosu/functions/linfnorm.hpp>
#include <kyosu/functions/log.hpp>
#include <kyosu/functions/log1p.hpp>
#include <kyosu/functions/oneminus.hpp>
#include <kyosu/functions/reverse_horner.hpp>
#include <kyosu/functions/sinpicospi.hpp>
#include <kyosu/functions/cotpi.hpp>
#include <kyosu/functions/log_gamma.hpp>
#include <kyosu/functions/sqr_abs.hpp>
#include <kyosu/functions/tgamma_inv.hpp>
#include <kyosu/constants/wrapped.hpp>
#include <eve/module/core.hpp>

#include <kyosu/details/hyperg/hyp2_1/is_negint.hpp>
#include <kyosu/details/hyperg/hyp2_1/gamma_ratio_diff_small_eps.hpp>
#include <kyosu/details/hyperg/hyp2_1/gamma_inv_diff_eps.hpp>
#include <kyosu/details/hyperg/hyp2_1/a_sum_init.hpp>
#include <kyosu/details/hyperg/hyp2_1/b_sum_init_ps_one.hpp>
#include <kyosu/details/hyperg/hyp2_1/b_sum_init_ps_infinity.hpp>
#include <kyosu/details/hyperg/hyp2_1/max_index_estimation.hpp>
#include <kyosu/details/hyperg/hyp2_1/hyp_ps_zero.hpp>
#include <kyosu/details/hyperg/hyp2_1/hyp_ps_one.hpp>
#include <kyosu/details/hyperg/hyp2_1/hyp_ps_infinity.hpp>
#include <kyosu/details/hyperg/hyp2_1/hyp_ps_cp_rest.hpp>
#include <kyosu/details/hyperg/hyp2_1/hyp2_1_base.hpp>
