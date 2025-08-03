//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <complex>


// TTS_CASE_WITH ( "Check kyosu::omega over real"
//               , kyosu::scalar_real_types
//               , tts::generate ( tts::randoms(-10,10))
//               )
//   <typename T>(T const& a0)
// {

// //  TTS_RELATIVE_EQUAL(eve::detail::map([](auto v){return kyosu::omega(v); }, a0),  eve::detail::map([](auto v){return kyosu::complex(eve::omega(v)); }, a0), tts::prec<T>());
//   if constexpr( sizeof(eve::element_type_t<T>) == 8)
//    {
// //     TTS_RELATIVE_EQUAL(kyosu::omega(a0),  kyosu::complex(eve::omega(a0)), tts::prec<T>()) << a0 << '\n';
//      TTS_RELATIVE_EQUAL(kyosu::omega(5.8148731e-15), kyosu::complex(eve::omega(5.8148731e-15)), tts::prec<T>()) << a0 << '\n';
//      std::cout << kyosu::omega(5.8148731e-15) << std::endl;
//    }
// };


TTS_CASE_TPL( "Check peculiar values", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  if constexpr( sizeof(T) == 8)
  {
    auto tcx = kyosu::complex;
    using c_t = decltype(tcx(e_t(0)));
    using eve::as;
    const int N = 15;
    std::array<c_t, N> inputs =
      {
        tcx(eve::zero(as<e_t>()),eve::zero(as<e_t>())),//0*
        tcx(eve::minf(as<e_t>()),eve::zero(as<e_t>())),//1*
        tcx(eve::inf(as<e_t>()),eve::zero(as<e_t>())), //2*
        tcx(eve::nan(as<e_t>()),eve::zero(as<e_t>())), //3*
        tcx(eve::zero(as<e_t>()),eve::inf(as<e_t>())), //4*
        tcx(eve::inf(as<e_t>()),eve::inf(as<e_t>())),  //5*
        tcx(eve::minf(as<e_t>()),eve::inf(as<e_t>())), //6*
        tcx(1+eve::euler(as<e_t>()),eve::zero(as<e_t>())),//7*
        tcx(eve::zero(as<e_t>()),eve::pi(as<e_t>())),  //8*
        tcx(eve::mone(as<e_t>()),eve::pi(as<e_t>())),  //9*
        tcx(eve::mone(as<e_t>()),-eve::pi(as<e_t>())), //10*
        tcx( -2+eve::log_2(as<e_t>()), -eve::pi(as<e_t>())), //11*
        tcx( -2+eve::log_2(as<e_t>()), eve::pi(as<e_t>())),//12*
        tcx(eve::one(as<e_t>()),eve::one(as<e_t>())),  //13*
        tcx( eve::zero(as<e_t>())    , 1+eve::pio_2(as<e_t>())),//14*
      };
    std::array<c_t, N> expected =
      {
        tcx( eve::omega(eve::zero(as<e_t>()))),                 //0*
        tcx( eve::zero(as<e_t>())   , eve::zero(as<e_t>())),    //1*
        tcx( eve::inf(as<e_t>())    , eve::zero(as<e_t>())),    //2*
        tcx( eve::nan(as<e_t>())    , eve::nan(as<e_t>())),     //3*
        tcx( eve::zero(as<e_t>())   , eve::inf(as<e_t>())),     //4*
        tcx( eve::inf(as<e_t>())    , eve::inf(as<e_t>())),     //5*
        tcx( eve::minf(as<e_t>())   , eve::inf(as<e_t>())) ,    //6*
        tcx( eve::euler(as<e_t>())  , eve::zero(as<e_t>())),    //7*
        tcx( e_t(-0.3181315052047641353) , e_t(1.337235701430689408901)), //8
        tcx( eve::mone(as<e_t>())   ,  eve::zero(as<e_t>())),   //9*
        tcx(eve::mone(as<e_t>())    , eve::zero(as<e_t>())) ,   //10*
        tcx(e_t(-0.406375739959959907))  ,                      //11*
        tcx(e_t(-2))                ,                           //12*
        tcx(e_t(0.937208208373369753), e_t(0.50542131601315120396215)),   //13*
        tcx( eve::zero(as<e_t>())    , eve::one(as<e_t>())),    //14*
      };


    for(int i=0; i < N; ++i)
    {
      TTS_RELATIVE_EQUAL(kyosu::omega(inputs[i]), expected[i], tts::prec<T>()) << i << " < - "<< inputs[i] << '\n';
   TTS_IEEE_EQUAL(kyosu::acos(kyosu::conj(inputs[i])), kyosu::conj(expected[i]));
    }
  }
};
