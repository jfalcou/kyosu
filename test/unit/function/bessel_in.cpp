//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL ( "Check kyosu::cyl_bessel_jn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  auto constexpr N = 11;
  using a_t  = std::array<T, 16 >;
  using aN_t = std::array<a_t, N >;
  a_t re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
  a_t im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};
  aN_t reresN16;
  aN_t imresN16;
  //res are taken from octave 9.2.0 besseli outputs
  int i=0;
  reresN16[i] = a_t{9.1105158918418851e+00,1.3520681783686308e+01,5.1996157906116176e+00,-9.3955732595530583e-01,-2.1592215730366595e+00,-1.0203442510225200e+00,1.7928053786055054e-01,7.9145564123437862e-01,1.0226268793515969e+00,9.3760847680602921e-01,9.6892664556561592e-02,-1.8654535569280768e+00,-3.7136415921698247e+00,-1.3637442303665379e+00,9.5845168576745756e+00,2.3992713926047784e+01,};
  imresN16[i] = a_t{-2.4327050976845694e+01,2.8653583146189998e+00,5.3090647906716306e+00,-3.9446445638917211e+00,7.3190429239585508e-01,8.0207883753193920e-01,-7.2760910016154035e-01,1.7951149535253691e-01,0.0000000000000000e+00,4.9652994760912211e-01,-1.3484619725848805e+00,1.3085405635612335e+00,1.4854842997435447e+00,-7.0649726353849376e+00,9.1307990856050161e+00,5.8349474258307366e+00,};
  ++i; //1 1.000e+00
  reresN16[i] = a_t{-7.7663478926916039e+00,-1.2939941854695570e+01,-5.3302796682714355e+00,5.9719589151668284e-01,1.9477234840183313e+00,1.0345853150807232e+00,9.1715728120041307e-02,-1.3252601532703701e-01,1.5169384000359271e-01,3.6502802882708790e-01,-1.9309671470909062e-01,-1.8559797097918986e+00,-3.3591287128841567e+00,-8.2478634016454500e-01,9.7166059866485099e+00,2.2909280737884778e+01,};
  imresN16[i] = a_t{2.4051496578757863e+01,-3.4696927580512948e+00,-4.8039150011847722e+00,3.8527686802723053e+00,-8.9103272670310230e-01,-6.8185707326573963e-01,8.3915572064640787e-01,-4.6635055250513691e-01,0.0000000000000000e+00,6.1416033492290367e-01,-1.2763519411438635e+00,1.0376469905065817e+00,1.7026334985345826e+00,-6.8299943890080241e+00,8.2452497177525110e+00,6.7817932616967287e+00,};
  ++i; //2 2.000e+00
  reresN16[i] = a_t{4.0377910257037932e+00,1.1131526087051226e+01,5.5134372825409299e+00,2.6219467485144321e-01,-1.4011595850044585e+00,-1.0502981158349249e+00,-4.2625656016661650e-01,-1.0399428744829654e-01,1.1334612660978446e-02,-4.1579886943962120e-02,-5.4880819677356119e-01,-1.6836906393155004e+00,-2.3685550631515331e+00,5.2693325633049048e-01,9.7888465062646848e+00,1.9610788290359256e+01,};
  imresN16[i] = a_t{-2.2907957726202113e+01,4.9924679581718241e+00,3.3283209314937663e+00,-3.4144016399820751e+00,1.2319772918848950e+00,9.4382975257347401e-02,-3.0284796812655723e-01,8.6383554533540505e-02,0.0000000000000000e+00,2.4739764151330637e-01,-6.0651952574518542e-01,2.1663109112336176e-01,2.1226065961964480e+00,-5.9579722815610143e+00,5.7386831869462647e+00,9.1253114501434780e+00,};
  ++i; //3 3.000e+00
  reresN16[i] = a_t{1.1233884194311896e+00,-8.0281804118427527e+00,-5.2105780621049034e+00,-1.2453676999005441e+00,4.3207258423393058e-01,5.0929522268502936e-01,1.9675505254985781e-01,2.1907914170279676e-02,5.6567119054670495e-04,-4.6607480311600599e-02,-3.5568894517371541e-01,-9.3701920545934714e-01,-8.8619672060683563e-01,1.9934200527106283e+00,9.0326799310742185e+00,1.4184752633683175e+01,};
  imresN16[i] = a_t{2.0180941784828413e+01,-6.6028358596344319e+00,-1.2060961901657319e+00,2.4637722418841257e+00,-1.3449104993423109e+00,4.0336635907674406e-01,-7.1129028123224192e-02,1.1400169086975935e-02,0.0000000000000000e+00,3.6205278008366759e-02,-4.0532151701810043e-02,-4.7210545844804447e-01,2.1546662676711930e+00,-4.2666109253585001e+00,2.2322965885901072e+00,1.1506879978780825e+01,};
  ++i; //4 4.000e+00
  reresN16[i] = a_t{-6.0931836070886050e+00,4.0206810831814126e+00,3.9803760873195198e+00,1.6810967014812204e+00,3.4081528006180806e-01,-7.7341559999806742e-03,-1.3179461451117138e-02,2.9882335388177364e-04,2.1188850044340972e-05,-1.0373280034260593e-02,-9.2837018203143828e-02,-1.9378719685754689e-01,2.9428169699668177e-01,2.6199441731396353e+00,6.8818299560467286e+00,7.4349171530669196e+00,};
  imresN16[i] = a_t{-1.5353645717403756e+01,7.2009244514940214e+00,-8.8576735371722126e-01,-1.0118631030583647e+00,7.9135187756937464e-01,-2.9866909421174481e-01,6.0224785229491408e-02,-3.3466861672661399e-03,0.0000000000000000e+00,-1.0406334465956882e-03,7.2971807991105947e-02,-4.6548456582896919e-01,1.3882031879918353e+00,-1.9751799215333103e+00,-1.1137343314644861e+00,1.2238738005597600e+01,};
  ++i; //5 5.000e+00
  reresN16[i] = a_t{8.9883285972277314e+00,-1.7166910704313232e-01,-1.9552652930598802e+00,-1.1726789531472908e+00,-3.9970065086646656e-01,-8.5429459298761556e-02,-1.0457197822828099e-02,-3.4833980015778159e-04,6.3518936427802918e-07,-9.5182638817546271e-04,-2.9846816874380209e-03,7.1947173914647819e-02,5.6340561950331836e-01,1.9772155394724815e+00,3.6779221296879525e+00,1.1039809098398150e+00,};
  imresN16[i] = a_t{8.8772353099495991e+00,-6.0350496686877255e+00,1.9851186263810294e+00,-1.7946168256374539e-01,-1.4342166728094663e-01,6.7155965886418131e-02,-9.8801362227155052e-03,1.0708066774676126e-04,0.0000000000000000e+00,-1.1253083422928653e-03,3.1017297147429464e-02,-1.8169821323564050e-01,4.4266106009246053e-01,-8.7015678396073937e-02,-2.9274083350991624e+00,1.0286783444573661e+01,};
  ++i; //6 6.000e+00
  reresN16[i] = a_t{-8.6319761919827087e+00,-2.1131595059309745e+00,1.6544806521061284e-01,3.6160718306746958e-01,1.4955013037983969e-01,3.1232241811688852e-02,2.6695881464262497e-03,2.0760833913227061e-05,1.5871235073313834e-08,1.2393618081046237e-05,4.5629138193577128e-03,5.8530839939042859e-02,3.0368693710193584e-01,8.2523305295326099e-01,8.1692336152392664e-01,-2.7897257773884530e+00,};
  imresN16[i] = a_t{-2.4362848833767474e+00,3.4153565029960720e+00,-1.6648396277795654e+00,4.8902151145141681e-01,-8.8359031045561170e-02,9.4756088044619796e-03,-7.7818116329791812e-04,2.5486826324258143e-05,0.0000000000000000e+00,-1.7322367600867587e-04,5.1052742091697847e-03,-2.3806223342871222e-02,-2.7599921848032366e-02,6.1527070607000789e-01,-2.6949246017189732e+00,6.2204045570304878e+00,};
  ++i; //7 7.000e+00
  reresN16[i] = a_t{5.5665636172523536e+00,2.2548351906233490e+00,5.3665860172600954e-01,5.3967088761785909e-02,-7.4427901212023861e-03,-2.4443007944224167e-03,-1.0884629653700958e-04,1.2239228375527663e-06,3.3996134547701461e-10,1.3153959390315560e-05,1.2886331318910631e-03,1.5804616333274527e-02,7.0553206036017335e-02,8.7081929460585156e-02,-5.5582778757530293e-01,-3.4782796672448959e+00,};
  imresN16[i] = a_t{-1.8038096787907758e+00,-8.1793054862522441e-01,6.9626422519142706e-01,-2.6226545510386384e-01,6.0067560892782007e-02,-7.9819062577338520e-03,4.4579931638189776e-04,-2.2238500138294700e-06,0.0000000000000000e+00,-1.1604577754531845e-05,7.4966348534454322e-06,7.5111004554323200e-03,-8.6439130776189310e-02,4.5704210508271137e-01,-1.3859426201995746e+00,2.1004313975019571e+00,};
  ++i; //8 8.000e+00
  reresN16[i] = a_t{-1.9530131729286142e+00,-1.1859332728797818e+00,-4.0445303343886463e-01,-9.0744016726584414e-02,-1.3338906215121064e-02,-1.1890361984636744e-03,-4.7996081090656087e-05,-1.7014221032212802e-07,6.3722843864318098e-12,1.5479466305602426e-06,1.4207742413117184e-04,1.1798014616592736e-03,-4.8878565501436384e-03,-1.0341060838276658e-01,-6.3022382922309939e-01,-2.1666789228351044e+00,};
  imresN16[i] = a_t{2.8803884466915348e+00,-4.8499378224555761e-01,-4.2200509630049454e-02,4.8408895050221903e-02,-1.2603148597918959e-02,1.4295790390084237e-03,-4.5433913922684944e-05,-2.0483850900239631e-08,0.0000000000000000e+00,8.6084005255864629e-08,-1.5744677812510365e-04,4.0678220971697284e-03,-3.5390677893731494e-02,1.5333092594426539e-01,-3.1263270431633028e-01,-2.7331997121967028e-01,};
  ++i; //9 9.000e+00
  reresN16[i] = a_t{-2.3542615623947888e-01,2.3653427136088589e-01,1.2293822753931929e-01,3.2020946526161942e-02,4.8289070321446380e-03,3.6415928373530518e-04,8.0738989198756685e-06,2.6713199101344913e-09,1.0617820065123293e-13,8.1714303786711880e-08,-3.5008066243495196e-06,-4.9347559029343918e-04,-8.4224167797457786e-03,-6.4518199491469197e-02,-2.8270110153627298e-01,-7.0500871568671930e-01,};
  imresN16[i] = a_t{-1.8660177997096641e+00,5.6646204244180176e-01,-1.1335895409086341e-01,1.4069867390407241e-02,-9.5787468854415035e-04,4.4696180967048848e-05,-2.4754398446377702e-06,9.9247442675241405e-09,0.0000000000000000e+00,9.0323247903168339e-08,-3.0808910457829212e-05,7.6490137876074674e-04,-5.6815968933983628e-03,1.0912060254296946e-02,8.9809243199417521e-02,-7.9183343353506441e-01,};
  ++i; //10 1.000e+01
  reresN16[i] = a_t{7.2096780060754961e-01,1.1052133111606181e-01,3.1437370175592463e-03,-2.4723202156997602e-03,-4.7293794448343297e-04,-2.7896119603828976e-05,-2.0739912894830789e-07,4.4304844373647224e-10,1.5923473578552213e-15,-3.9133464867901946e-10,-3.3501656767750857e-06,-1.7429941587485191e-04,-2.5100400727858961e-03,-1.6418736619841605e-02,-5.0700496067984643e-02,1.3224133631162732e-02,};
  imresN16[i] = a_t{5.7916720018499834e-01,-2.4126888311913855e-01,6.1676272191232950e-02,-1.0372626676994788e-02,1.0857028775833849e-03,-5.8692616087497892e-05,9.4740127725668645e-07,-3.3350577631464458e-10,0.0000000000000000e+00,8.6035082077564487e-09,-2.3260671692032776e-06,2.3687853381792524e-05,6.6738984517224101e-04,-1.2820769685200642e-02,1.0082810042615270e-01,-4.6684296961057775e-01,};
  using eve::spherical;
  auto h =  eve::half(eve::as<T>());
  using c_t = kyosu::complex_t<T>;
  std::array<c_t, 5> is;
  for(int j=0; j <= 15; ++j)
  {
    auto c = kyosu::complex(re[j], im[j]);
    auto iN = kyosu::bessel_i(N-1, c, std::span(is));
    TTS_RELATIVE_EQUAL(iN, kyosu::bessel_i(N-1, c), tts::prec<T>());
    auto fac = kyosu::sqrt(eve::pio_2(eve::as(kyosu::real(c)))*kyosu::rec(c));
    for(int i=0; i < N; ++i)
    {
      // std::cout<< "j " << j  << " c[" << i << "] = " << c << std::endl;
      auto res = kyosu::complex(reresN16[i][j], imresN16[i][j]);
      TTS_RELATIVE_EQUAL(kyosu::bessel_i(i, c), res, tts::prec<T>());
      TTS_RELATIVE_EQUAL(kyosu::bessel_i(-i, c), res, tts::prec<T>());
      TTS_RELATIVE_EQUAL(kyosu::bessel_i[spherical](i, c), kyosu::bessel_i(i+h, c)*fac, tts::prec<T>());
      TTS_RELATIVE_EQUAL(kyosu::bessel_i[spherical](-i, c), kyosu::bessel_i(-i+h, c)*fac, tts::prec<T>());
      if (i < 5) TTS_RELATIVE_EQUAL(kyosu::bessel_i(i, c), is[i], tts::prec<T>()) << i << " -- " <<  j <<  " -- "<< c << '\n';
    }
  }
};
