//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check behavior of if_else on scalar cayley-dickson"
              , tts::bunch<kyosu::scalar_real_types>
              , tts::generate(tts::randoms(-100,+100))
              )
<typename T>(T const& a0 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    auto m = eve::is_odd(e);
    TTS_EQUAL ( kyosu::if_else( m, kyosu::complex_t<e_t>(0,-e), kyosu::complex_t<e_t>(0, e))
              , kyosu::complex_t<e_t>(0,m ? -e : e)
              );

    TTS_EQUAL ( kyosu::if_else(m, kyosu::quaternion_t<e_t>(0,-e,1,-2), kyosu::quaternion_t<e_t>(0,e,-1, 2))
              , kyosu::quaternion_t<e_t>(0,m ? -e : e,m ? 1 : -1,m ? -2 : 2)
              );

    TTS_EQUAL ( kyosu::if_else( eve::is_odd(e)
                              , kyosu::complex_t<e_t>(0,-e)
                              , kyosu::quaternion_t<e_t>(0, e,-1,  2)
                              )
              , kyosu::quaternion_t<e_t>(0,m ? -e : e,m ? 0 : -1,m ? 0 : 2)
              );
    TTS_EQUAL ( kyosu::if_else( eve::is_odd(e)
                              , kyosu::quaternion_t<e_t>(0,-e, 1, -2)
                              , kyosu::complex_t<e_t>(0, e)
                              )
              , kyosu::quaternion_t<e_t>(0,m ? -e : e,m ? 1 : 0,m ? -2 : 0)
              );
  }
};

TTS_CASE_WITH ( "Check behavior of if_else on SIMD cayley-dickson"
              , tts::bunch<kyosu::scalar_real_types>
              , tts::generate(tts::randoms(-100,+100))
              )
<typename T>(T const& a0 )
{
  using e_t   = typename T::value_type;
  using c_t   = kyosu::complex_t<e_t>;
  using q_t   = kyosu::quaternion_t<e_t>;
  using wc_t  = eve::wide<c_t>;
  using wq_t  = eve::wide<q_t>;

  for(auto e : a0)
  {
    auto m = eve::is_odd(e);
    TTS_EQUAL(kyosu::if_else(m, wc_t(c_t(0,-e))     , wc_t(c_t(0,e)))     , wc_t(c_t(0,m ? -e : e)));
    TTS_EQUAL(kyosu::if_else(m, wq_t(q_t(0,-e,1,-2)), wq_t(q_t(0,e,-1,2))), wq_t(q_t(0,m ? -e : e,m ? 1 : -1,m ? -2 : 2)));
    TTS_EQUAL(kyosu::if_else(m, wc_t(c_t(0,-e))     , wq_t(q_t(0,e,-1,2))), wq_t(q_t(0,m ? -e : e,m ? 0 : -1,m ? 0 : 2)));
    TTS_EQUAL(kyosu::if_else(m, wq_t(q_t(0,-e,1,-2)), wc_t(c_t(0, e)))    , wq_t(q_t(0,m ? -e : e,m ? 1 : 0,m ? -2 : 0)));
  }
};
