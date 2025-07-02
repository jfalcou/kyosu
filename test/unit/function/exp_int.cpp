//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <iomanip>
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <eve/wide.hpp>
#include <iostream>

TTS_CASE_TPL ( "Check exp_int "
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  if constexpr(sizeof(T) == 8)
  {
    auto pr = tts::prec<T>(4.0e-3, 1.0e-8);
    using r_t = kyosu::cayley_dickson<T, 2>;
    r_t I = r_t(0.0, 1.0);
    auto cinf = kyosu::cinf(eve::as<r_t>());
    r_t res[] = {r_t(-0.2685678950039737734, -0.01944069178788886870),
                 r_t(-0.187165853583267096, 0.32843702230303777488610),
                 r_t(-0.210405792206054376, -0.0646082262867762182142),
                 r_t(-0.0019147781533606244, -0.0020421342605292576),
                 r_t(0.00296509191308227717, 0.0),
                 r_t(4.4195931497672e18, -1.1367863689312e19),
                 r_t(-0.454219904863173, -3.141592653589793238)
    };
    r_t r(cinf);
    r = kyosu::exp_int(0.4+2*I);
    TTS_RELATIVE_EQUAL(r, res[0], pr);
    r = kyosu::exp_int(0.4-1.2*I);
    TTS_RELATIVE_EQUAL(r, res[1], pr);
    r = kyosu::exp_int(r_t(2.0), 0.4+2*I);
    TTS_RELATIVE_EQUAL(r, res[2], pr);
//     r = kyosu::exp_int(r_t(2.5), 4+2*I);
//     TTS_RELATIVE_EQUAL(r, res[3], pr);
//     r = kyosu::exp_int(r_t(2.5), r_t(4.0));
//     TTS_RELATIVE_EQUAL(r, res[4], pr);

    TTS_RELATIVE_EQUAL(kyosu::exp_int(r_t(0.0)), cinf, pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(1.0),kyosu::real(kyosu::exp_int(r_t(1.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0),kyosu::real(kyosu::exp_int(r_t(2.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 1.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(1.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 9.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(9.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 15.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(15.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 18.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(18.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 18.99), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(18.99))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 20.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(20.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 25.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(25.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 49.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(49.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 51.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(51.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 500.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(500.0))), pr);
    TTS_RELATIVE_EQUAL(kyosu::exp_int(2.0, 1000.0), kyosu::real(kyosu::exp_int(r_t(2.0),r_t(1000.0))), pr);
  }
};
