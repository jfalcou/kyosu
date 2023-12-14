//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_i over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00
        , -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01
        , 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00
        , 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00
        , 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00
        , -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00
        , -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};

    constexpr int N = 2;
    T v1 = N+0.3;
    auto n = int(v1);
    using vc_t = std::array<T, 16>;
    using a_t = std::array<vc_t, N+1>;
    a_t reresi_03{
      vc_t{2.4946103002927494e+01, 1.0281055589440035e+01, -1.1955996056568359e+00, -3.7244789629988131e+00
          , -1.8681466325086200e+00, 5.3651059494096098e-02, 7.5861099866223158e-01, 7.1910702637099910e-01
          , 6.4164623507421747e-01, 8.4603281117851570e-01, 8.8728399491446633e-02, -1.8512237177059714e+00
          , -3.6785403913549906e+00, -1.3149090187159249e+00, 9.5974950027834574e+00, 2.3895446262106674e+01},
      vc_t{-2.3314234836654144e+01, -1.0487582208749537e+01, 4.2957770293599618e-01, 3.2669735099338491e+00
            , 1.8637006674095131e+00, 1.8329466319739901e-01, -4.3951295857717176e-01, -2.6887642660785366e-01
          , 7.3484756949980357e-02, 1.7975463328408453e-01, -3.5042129823656992e-01, -1.8533518623157652e+00
          , -3.1285557845058007e+00, -4.7892306409120167e-01, 9.7762598159581202e+00, 2.2155802276551285e+01},
      vc_t{1.9548998482144881e+01, 1.0535312492927069e+01, 1.0187567542575802e+00, -2.2495401999216877e+00
          , -1.7450918942284412e+00, -6.4192601829985618e-01, -1.1911991238263646e-01, -2.3752735967216422e-02
          , 4.7783415077204501e-03, -6.3552438346782397e-02, -5.3468271578196114e-01, -1.5104323124570009e+00
          , -1.9530537659802314e+00, 9.9546617249995384e-01, 9.6846390655315062e+00, 1.8188390761309609e+01}
    };
    a_t imresi_03{
      vc_t{-7.0149276052284684e+00, -9.1782628874200327e+00, 7.3091253003252543e+00, -1.5804772907430746e+00
          , -1.2814322501402557e+00, 1.2680402389274552e+00, -3.0657941540593403e-01, -3.2113352636255493e-01
          , 0.0000000000000000e+00, 5.9814531708188334e-01, -1.3735420325973586e+00, 1.2830632485422924e+00
          , 1.5124117680691991e+00, -7.0476634635465096e+00, 9.0502640456466512e+00, 5.9241573333129605e+00},
      vc_t{8.4494807341237461e+00, 7.8719861299613019e+00, -6.9898250822721870e+00, 1.9073555698606222e+00
          , 9.0154677032960695e-01, -1.2014977507643358e+00, 6.3768672788713165e-01, -2.2387916947698525e-01
          , 0.0000000000000000e+00, 5.1992632788922155e-01, -1.1238778312383464e+00, 8.3779929222764138e-01
          , 1.8243800819933460e+00, -6.6453413591025576e+00, 7.6464162420697885e+00, 7.3856073352545026e+00},
      vc_t{-1.1016472182122605e+01, -5.1157921018787036e+00, 6.0559440043198070e+00, -2.3353427075393176e+00
          , -1.4693602774918135e-01, 6.9183861748000253e-01, -3.9519426048158079e-01, 8.0801277882578668e-02
          , 0.0000000000000000e+00, 1.5592211409520523e-01, -3.8809489690744248e-01, -5.0541907932195318e-02
          , 2.2087208933325315e+00, -5.5408183115498604e+00, 4.7485267450037423e+00, 9.9139283782970526e+00}
    };

    std::vector<kyosu::complex_t<T>> is_03(N+2);
    for (int k = 0; k < 16; ++k)
    {
      for (n = 0; n <= N; ++n)
      {
        std::cout << "n = "<< n << " k = "<< k << std::endl;
        auto c = kyosu::complex(re[k], im[k]);
        kyosu::cyl_bessel_i(v1, c, is_03);
        auto refi_03=  kyosu::complex_t<T>(reresi_03[n][k], imresi_03[n][k]);
        TTS_RELATIVE_EQUAL(refi_03, is_03[n], 1.e-6) << "n " << n  << " k " << k  << " c "<< c << " arg(c) "<< kyosu::arg(kyosu::conj(c)) << " < 1.57" << '\n';
      }
    }
  }
};

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_k over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00
        , -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01
        , 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00
        , 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00
        , 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00
        , -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00
        , -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};

    constexpr int N = 2;
    T v1 = N+0.3;
    auto n = int(v1);
    using vc_t = std::array<T, 16>;
    using a_t = std::array<vc_t, N+1>;
    a_t reresi_03{
      vc_t{-7.6356085800614579e+01, -9.1777541957610591e+00, 1.6542613518775354e+01, 1.2381215528291099e+01
          , 2.3387662997005862e+00, -2.5690360792159450e+00, -2.4930621764042549e+00, -5.9179800603848065e-01
          , 1.4823411623387830e+00, 7.6222886510162097e-02, -1.0353447894367163e-01, -5.4817788296649773e-02
          , -6.5755373416543517e-03, 7.4754253132452942e-03, 4.9759020245597188e-03, 8.9580881413898973e-04},
      vc_t{-7.4858670276675767e+01, -1.2123306468557997e+01, 1.3991108787767311e+01, 1.1826801567594778e+01
          , 3.1163376758999819e+00, -1.6392538522424551e+00, -2.2158615052476724e+00, -1.6399139926251056e+00
          , 5.0252049759614961e+00, -3.0710975110808281e-02, -1.4448722663392172e-01, -5.9358498236853956e-02
          , -4.2856644566998800e-03, 8.8712819627955915e-03, 5.2227131524972374e-03, 7.8878939645721496e-04},
      vc_t{-7.0028359986020078e+01, -1.7325314484522657e+01, 8.6039335006386377e+00, 1.0034374609472982e+01
           , 4.1203503622633431e+00, 1.8737546605673755e-01, -7.8661759114041829e-01, -1.1787359554492010e+00
          , 4.5034117620671751e+01, -6.6359059112780450e-01, -2.6202186702526037e-01, -6.5475381627126655e-02
          , 3.0805234748470314e-03, 1.2366476238369981e-02, 5.6902500521605311e-03, 4.7783649284957982e-04}
    };
    a_t imresi_03{
      vc_t{-2.8233953538916463e+01, 4.2311180773416339e+01, -1.6375448345023578e+01, -2.8400823313968524e+00
          , 6.6879086265570535e+00, -3.1842556027568345e+00, -3.5061121052017286e-01, 1.6999326061984978e+00
          , 0.0000000000000000e+00, -3.6592454260706442e-01, 9.2115150427228051e-02, 1.6505655277180269e-02
          , -2.3966513298980401e-02, 8.2061105972084727e-03, 8.6732273722515746e-04, -2.1491225231985342e-03},
      vc_t{-2.1578471449355344e+01, 3.9375141495795027e+01, -1.6966023116719221e+01, -1.2074088510183536e+00
          , 5.7592731043626317e+00, -3.3418934981593567e+00, 4.9100238158007220e-01, 9.1783022063328734e-01
          , 0.0000000000000000e+00, -5.3837631537993569e-01, 8.7181646569271742e-02, 2.7319352748734618e-02
          , -2.7099439714577039e-02, 8.0965217457305613e-03, 1.3412607263892384e-03, -2.3322553819202355e-03},
      vc_t{-8.0970040511656194e+00, 3.2454127323908530e+01, -1.7278120141267198e+01, 1.8078762957088461e+00
          , 3.5487990981203326e+00, -2.9510953475366790e+00, 1.5914642244066768e+00, -2.7986189543910651e+00
          , 0.0000000000000000e+00, -1.0258894849569298e+00, 3.8996035672480382e-02, 5.9423612418072189e-02
          , -3.4235642328623889e-02, 7.3102426796495309e-03, 2.5947374159400196e-03, -2.7525951662690611e-03}
    };

    std::vector<kyosu::complex_t<T>> is_03(N+2);
    for (int k = 0; k < 16; ++k)
    {
      for (n = 0; n <= N; ++n)
      {
        std::cout << "n = "<< n << " k = "<< k << std::endl;
        auto c = kyosu::complex(re[k], im[k]);
        kyosu::cyl_bessel_k(v1, c, is_03);
        auto refi_03=  kyosu::complex_t<T>(reresi_03[n][k], imresi_03[n][k]);
        TTS_RELATIVE_EQUAL(refi_03, is_03[n], 1.e-6) << "n " << n  << " k " << k  << " c "<< c << " arg(c) "<< kyosu::arg(kyosu::conj(c)) << " < 1.57" << '\n';
      }
    }
  }
};