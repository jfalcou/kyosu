//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_j over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};
    std::array<T, 16> reres2_3{-2.4479154036643860e+02, -2.8872235660821971e+01, 1.7858689849510746e+01, 1.4623389079462152e+01, 6.1504223321168556e+00, 1.6678589902262093e+00, 2.2949273079731994e-01, -1.5679246690912356e-02, 4.7136244726909650e-03, -1.4161521303466679e-02, 6.2368957399474179e-02, 1.1718092183868052e+00, 5.6839576199159945e+00, 1.6848129489914882e+01, 3.1444252061317524e+01, 1.3380246970620504e+01};
    std::array<T, 16> imres2_3{1.8484337522053480e+02, -1.1307037886162173e+02, 4.0559222645050831e+01, -8.1127083417081263e+00, -7.1604085289604757e-01, 1.3764522757547775e+00, -5.8422524476846360e-01, 9.4354760762079409e-02, 0.0000000000000000e+00, 1.6777982416879342e-01, -7.7628934704675578e-01, 2.0566484873623425e+00, -3.0172359706556837e+00, -2.3116674849406200e+00, 3.1658466827290766e+01, -1.1613111974080600e+02};
    std::array<T, 16> reres2_5{-2.8049431495810552e+02, -6.2553886222065564e+01, 2.5314724988644741e+00, 1.0049330193568066e+01, 5.4536915453121964e+00, 1.8106065159284395e+00, 3.5849716184926256e-01, 1.4987835482274801e-02, 2.6053018556586637e-03, -3.1361058355225617e-02, -7.8997782111187353e-02, 6.0551659158336801e-01, 4.3969031579482527e+00, 1.5830582921915545e+01, 3.6799808327604701e+01, 4.2822757682615944e+01};
    std::array<T, 16> imres2_5{8.7654998859698608e+01, -9.1771974928543131e+01, 4.1718091696208361e+01, -1.1882468425425639e+01, 1.4368335199546438e+00, 5.6548672084036988e-01, -3.6797517016358028e-01, 6.6319634847538445e-02, 0.0000000000000000e+00, 1.2286070035872497e-01, -6.5342738359033214e-01, 2.0314875005753552e+00, -3.9916982408915409e+00, 2.0164707092474652e+00, 2.0901220839866554e+01, -1.0317934754576970e+02};
    std::array<T, 16> reres3_3{-1.0918413942748916e+02, -7.8797147882867463e+01, -3.0909487239084530e+01, -7.7110299412270855e+00, -7.5921716748249157e-01, 2.9975541266731082e-01, 1.4239220265897637e-01, 1.5066450073465406e-02, 2.1459626326408355e-04, -2.8328757861205110e-02, -2.3433875386613734e-01, -6.8629822748353597e-01, -4.9039626796495428e-01, 4.8595510269314701e+00, 2.8045979092239701e+01, 8.9252884063426592e+01};
    std::array<T, 16> imres3_3{-2.1234273422730070e+02, 3.7740925787368155e+01, 5.8004666452451303e+00, -7.8068987376840697e+00, 3.5097368382935086e+00, -9.7447451427817566e-01, 1.4895188392447734e-01, -3.0886644326671847e-03, 0.0000000000000000e+00, 2.2260930150816184e-02, -1.8652976751721981e-01, 1.0332828428652927e+00, -3.9745542628760084e+00, 1.0638609029329768e+01, -1.6838439553526808e+01, -8.0823729240188555e+00};
    std::array<T, 16> reres3_5{-2.6802047026639684e+01, -5.6271869281869350e+01, -2.8443432115858691e+01, -9.0658838598773546e+00, -1.7811536143855298e+00, -8.5691680119444225e-02, 5.6108564412438416e-02, 8.5753218028732561e-03, 1.1181567593280482e-04, -2.2409200978551334e-02, -2.1236060287348266e-01, -7.5944760007298773e-01, -1.2328516630725352e+00, 1.9415440635532528e+00, 2.1178989079442957e+01, 8.2707928047873310e+01};
    std::array<T, 16> imres3_5{-2.2303501611661392e+02, 5.8843279367966588e+01, -5.2595094023262909e+00, -3.9836876803417556e+00, 2.5953839919941273e+00, -8.4915907970234206e-01, 1.4969691495299720e-01, -5.7471868274262053e-03, 0.0000000000000000e+00, 1.2352553082238980e-02, -1.1115743060650482e-01, 7.4073118474663702e-01, -3.3443291603533210e+00, 1.0490564746532662e+01, -2.1695295136346079e+01, 1.4603369286233004e+01};



    T v1 = 5.3;
    T v2 = 5.5;
      auto n = int(v1);
    std::vector<kyosu::complex_t<T>> jsa(n+1), ysa(n+1);
    std::vector<kyosu::complex_t<T>> jsb(n+1), ysb(n+1);
    for (int k = 0; k < 16; ++k)
    {
      auto c = kyosu::complex(re[k], im[k]);
      kyosu::cyl_bessel_jy(v1, c, jsa, ysa);
      kyosu::cyl_bessel_jy(v2, c, jsb, ysb);
      auto ref2_3=  kyosu::complex_t<T>(reres2_3[k], imres2_3[k]);
      auto ref2_5=  kyosu::complex_t<T>(reres2_5[k], imres2_5[k]);
      auto ref3_3=  kyosu::complex_t<T>(reres3_3[k], imres3_3[k]);
      auto ref3_5=  kyosu::complex_t<T>(reres3_5[k], imres3_5[k]);
      TTS_RELATIVE_EQUAL(ref2_3, jsa[2], 1.e-6) << "k " << k  << " c "<< c << '\n';
      TTS_RELATIVE_EQUAL(ref2_5, jsb[2], 1.e-6) << "k " << k  << " c "<< c << '\n';
      TTS_RELATIVE_EQUAL(ref3_3, jsa[3], 1.e-6) << "k " << k  << " c "<< c << '\n';
      TTS_RELATIVE_EQUAL(ref3_5, jsb[3], 1.e-6) << "k " << k  << " c "<< c << '\n';
    }
  }
};



TTS_CASE_WITH ( "Check kyosu::cyl_bessel_y over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};
    std::array<T, 16> reres2_3{-1.8484326865730344e+02, -1.1307014892933245e+02, -4.0559107572608077e+01, -8.1143546783931484e+00, 7.0633087288169860e-01, 1.3407841677059855e+00, 4.8877301616299679e-01, 2.2216544132094485e-01, -2.9681108437337542e+01, -2.4768799812528658e-01, -8.3639026725231835e-01, -2.0849521349780398e+00, -3.0267053789450706e+00, 2.3094783207028629e+00, 3.1658297750782335e+01, 1.1613126597756914e+02};
    std::array<T, 16> imres2_3{-2.4479153111110480e+02, 2.8872011802354219e+01, 1.7859666206505757e+01, -1.4626023538430497e+01, 6.1539074899810009e+00, -1.6563862289466802e+00, 9.4579141615307158e-02, 1.3332222909221194e+00, 0.0000000000000000e+00, 7.5954671034312571e-01, -1.8050823318641987e-01, 1.1889018428934341e+00, -5.6832311664239743e+00, 1.6846188856186565e+01, -3.1443328799583625e+01, 1.3379974578893540e+01};
    std::array<T, 16> reres2_5{-8.7654890991263287e+01, -9.1771669314189324e+01, -4.1717627703885285e+01, -1.1883151237067642e+01, -1.4453741876757213e+00, 5.2384061340744781e-01, 2.0613862369503433e-01, -4.1620643416178454e-01, -4.9302216969951630e+01, -3.8688922030869238e-02, -6.8911084080985185e-01, -2.0568676772290106e+00, -4.0017265312328689e+00, -2.0192640420463226e+00, 2.0900781668534790e+01, 1.0317941425982525e+02};
    std::array<T, 16> imres2_5{-2.8049434280044375e+02, 6.2553746160092665e+01, 2.5324009446864300e+00, -1.0052574585964901e+01, 5.4609192262232265e+00, -1.8129144119062477e+00, 2.5301316433891041e-01, 1.6542434472998313e+00, 0.0000000000000000e+00, 9.2883679082057158e-01, -6.7774302064112446e-02, 6.3146613171915755e-01, -4.3988243107870826e+00, 1.5829229872251211e+01, -3.6798924723120059e+01, 4.2822441814660202e+01};
    std::array<T, 16> reres3_3{2.1234272627043438e+02, 3.7741166652500659e+01, -5.7991786932755796e+00, -7.8026294000848422e+00, -3.5004933875497719e+00, -9.7559453898841753e-01, -3.7968711500276059e-01, -5.8490882994878817e+00, -4.5154962496132447e+02, 1.8877397415951571e+00, -1.6759842547747747e-02, -1.0221082627373854e+00, -3.9795691917737503e+00, -1.0641982953961264e+01, -1.6839696018946302e+01, 8.0820595351012692e+00};
    std::array<T, 16> imres3_3{-1.0918427479348105e+02, 7.8797493017829169e+01, -3.0909888177765485e+01, 7.7094897213255917e+00, -7.4550400829345764e-01, -3.6948307759316718e-01, 4.7422846714803280e-01, -1.4337366846187500e+00, 0.0000000000000000e+00, 1.7968080730357263e+00, 8.1126863938282140e-03, -6.3045657087350815e-01, 4.7679943976112987e-01, 4.8619363191323641e+00, -2.8045959615751542e+01, 8.9252638723682622e+01};
    std::array<T, 16> reres3_5{2.2303495914583851e+02, 5.8843393240988448e+01, 5.2606600172919311e+00, -3.9787131602438528e+00, -2.5801402820432502e+00, -8.2017197341107251e-01, -2.5670790136429888e-01, -6.9043394249229149e+00, -8.1663422761794823e+02, 2.9111931831265583e+00, 1.4481876717491965e-01, -7.1358410680502704e-01, -3.3460060585171023e+00, -1.0493446102766375e+01, -2.1696601638720377e+01, -1.4603760504563096e+01};
    std::array<T, 16> imres3_5{-2.6802178885661171e+01, 5.6272304131655567e+01, -2.8444325156170606e+01, 9.0659750768594716e+00, -1.7706092148284680e+00, 1.0101460672152084e-02, 5.4387090969453589e-01, -4.9599685771513116e+00, 0.0000000000000000e+00, 1.9340464780401485e+00, -1.0451441918509025e-02, -7.0042674192193743e-01, 1.2168812704902807e+00, 1.9449922562939730e+00, -2.1179324864154136e+01, 8.2707766661737594e+01};

    T v1 = 5.3;
    T v2 = 5.5;
    auto n = int(v1);
    std::vector<kyosu::complex_t<T>> jsa(n+1), ysa(n+1);
    std::vector<kyosu::complex_t<T>> jsb(n+1), ysb(n+1);
    for (int k = 0; k < 16; ++k)
    {
      auto c = kyosu::complex(re[k], im[k]);
      kyosu::cyl_bessel_jy(v1, c, jsa, ysa);
      kyosu::cyl_bessel_jy(v2, c, jsb, ysb);
      auto ref2_3=  kyosu::complex_t<T>(reres2_3[k], imres2_3[k]);
      auto ref2_5=  kyosu::complex_t<T>(reres2_5[k], imres2_5[k]);
      auto ref3_3=  kyosu::complex_t<T>(reres3_3[k], imres3_3[k]);
      auto ref3_5=  kyosu::complex_t<T>(reres3_5[k], imres3_5[k]);
      TTS_RELATIVE_EQUAL(ref2_3, ysa[2], 1.e-6) << "k " << k  << " c "<< c << '\n';
      TTS_RELATIVE_EQUAL(ref2_5, ysb[2], 1.e-6) << "k " << k  << " c "<< c << '\n';
      TTS_RELATIVE_EQUAL(ref3_3, ysa[3], 1.e-6) << "k " << k  << " c "<< c << '\n';
      TTS_RELATIVE_EQUAL(ref3_5, ysb[3], 1.e-6) << "k " << k  << " c "<< c << '\n';
    }
  }
};
