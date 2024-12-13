//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::bessel_ir over real positive order"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
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
    reresN16[i] = a_t{2.5523730989266411e+01,9.2706996673506659e+00,-1.9424053248776310e+00,-3.8645026908977691e+00,-1.7250579462058564e+00,1.8516492230190784e-01,7.9156940293440248e-01,6.8699028142461271e-01,6.0509651841527701e-01,8.2869927413521360e-01,8.2888817031661149e-02,-1.8501627752689938e+00,-3.6706471143016657e+00,-1.3032130424320045e+00,9.6006795849188240e+00,2.3872654664245289e+01,};
    imresN16[i] = a_t{-4.3912042088879399e+00,-1.0185465229373808e+01,7.1412934310600882e+00,-1.1882255098703263e+00,-1.4630737641610567e+00,1.2530201530165290e+00,-2.3322404790968038e-01,-3.6611508946269294e-01,0.0000000000000000e+00,6.0729940314610720e-01,-1.3752664985824743e+00,1.2776234478643902e+00,1.5176982557040111e+00,-7.0432016118123233e+00,9.0314213649766231e+00,5.9448945743437376e+00,};
    ++i; //1  2  1.333e+00
    reresN16[i] = a_t{-2.3987283008015975e+01,-9.6225318263107482e+00,1.1157998661680351e+00,3.4246355951092582e+00,1.7609404576181622e+00,7.3807535920572154e-02,-4.8133135007169442e-01,-2.7213427339733920e-01,6.7585974638665919e-02,1.6239480312767646e-01,-3.6639278152620930e-01,-1.8514304264477448e+00,-3.0994760670741535e+00,-4.3651510803776761e-01,9.7819127902801029e+00,2.2059631030702967e+01,};
    imresN16[i] = a_t{6.0485521943444454e+00,8.8560421790361339e+00,-6.8914036877080349e+00,1.5727034543694813e+00,1.0726675403809822e+00,-1.2090572240062278e+00,5.9400100681677692e-01,-1.9756460571119283e-01,0.0000000000000000e+00,5.0737690338645069e-01,-1.1031170678326632e+00,8.1221861703124698e-01,1.8388368275740232e+00,-6.6210058160373944e+00,7.5710793404065591e+00,7.4596060108646753e+00,};
    ++i; //2  2  2.333e+00
    reresN16[i] = a_t{2.0441137367165098e+01,9.9445365678532731e+00,4.3734038126328123e-01,-2.4401855379505868e+00,-1.7116729595366160e+00,-5.7612442570715849e-01,-8.7492144711108527e-02,-1.7419638276831802e-02,4.3322994049129118e-03,-6.4329667883622321e-02,-5.2992837003007898e-01,-1.4876014071785060e+00,-1.9042826089546945e+00,1.0472796209033919e+00,9.6674229798191540e+00,1.8018636658434033e+01,};
    imresN16[i] = a_t{-9.0197469369178549e+00,-6.0769317133060987e+00,6.0903697736987326e+00,-2.1031348493757340e+00,-2.9747907575055688e-01,7.3063984561501061e-01,-3.9151533013357465e-01,7.7812338382966612e-02,0.0000000000000000e+00,1.4732326946774132e-01,-3.6584818087839599e-01,-7.8043392283439428e-02,2.2150831421095458e+00,-5.4896352452975670e+00,4.6338470231213273e+00,9.9998644483898413e+00,};
    ++i; //3  2  3.333e+00
    reresN16[i] = a_t{-1.4840636431918472e+01,-9.4092628835810252e+00,-2.0587902280434967e+00,9.9803938288368599e-01,1.1130044974421271e+00,5.1412719790341332e-01,1.3383501046503110e-01,1.2872267697854857e-02,1.9465056224268713e-04,-3.1256933901934902e-02,-2.5180419216380989e-01,-6.4860229281851478e-01,-4.0924411097929303e-01,2.3403543251837444e+00,8.4793676182124624e+00,1.2013412090337379e+01,};
    imresN16[i] = a_t{1.1912895635192870e+01,2.3664992961658768e+00,-4.4877664965990958e+00,2.2971883806323268e+00,-5.1932427063504627e-01,-4.8671875716480850e-02,5.1511170862323513e-02,-2.2703439812331375e-03,0.0000000000000000e+00,1.3520049566601352e-02,3.5982161279483553e-02,-5.3956550945415527e-01,1.9755701053809829e+00,-3.5331240672792172e+00,1.0288814573757326e+00,1.2009124951263397e+01,};
    ++i; //4  2  4.333e+00
    reresN16[i] = a_t{7.8477657979964786e+00,7.4058522091197467e+00,2.8974480542731000e+00,3.3689882231983215e-01,-2.5555061462410522e-01,-1.5160736193989205e-01,-3.0939144344010482e-02,-8.7617219689609734e-04,6.7313550754176053e-06,-5.2067200991772079e-03,-4.6105003569078706e-02,-5.3390914347921259e-02,4.8304972621639541e-01,2.5300845398854475e+00,5.8767426197952437e+00,5.1715721723216292e+00,};
    imresN16[i] = a_t{-1.3043835298942369e+01,1.2159927400795234e+00,2.2037550884162336e+00,-1.6565200359809142e+00,6.4745195441600289e-01,-1.5715480035443735e-01,2.3497221214625042e-02,-1.3853931707581619e-03,0.0000000000000000e+00,-1.9333420940461155e-03,6.2249264842453515e-02,-3.7201342650456448e-01,1.0469741006507727e+00,-1.2422310732928756e+00,-1.9446622826523616e+00,1.1897675678075268e+01,};
    ++i; //5  2  5.333e+00
    reresN16[i] = a_t{-1.1057398845411814e+00,-4.1496153973343688e+00,-2.3841470013927162e+00,-7.7378830024636536e-01,-1.4461038210590235e-01,-1.2923427544109325e-02,-9.5161982282534379e-04,-9.6816580142701798e-05,1.8919339728992067e-07,-3.1666439796724372e-04,3.3870477762408565e-03,8.1945139942692730e-02,5.0122704006377561e-01,1.5925322070920549e+00,2.6070938249691160e+00,-5.4389779528239268e-01,};
    imresN16[i] = a_t{1.1315272953718258e+01,-3.3463112813060265e+00,-9.1081848860952164e-02,5.7926070474138514e-01,-2.8700796926974936e-01,7.3074572396915671e-02,-8.4258079700672908e-03,1.3551468066733439e-04,0.0000000000000000e+00,-6.6458845563332949e-04,1.8857956129780935e-02,-1.0936798247251751e-01,2.2334722318708006e-01,2.8401099210588032e-01,-3.0555414262848961e+00,9.0837364876773918e+00,};
    ++i; //6  2  6.333e+00
    reresN16[i] = a_t{-3.3161078059781066e+00,9.4254399218621798e-01,1.0745369640400197e+00,4.6408186066067414e-01,1.2150091343665817e-01,1.9165228571088412e-02,1.4188014218791036e-03,1.3832847795889500e-05,4.4787273315451215e-09,2.6628453359182453e-05,3.3702646108185403e-03,4.1594170786741831e-02,2.0798428555024290e-01,5.0934692055367981e-01,1.7549542191522893e-01,-3.3513647911394653e+00,};
    imresN16[i] = a_t{-7.1220888823641157e+00,3.2918993744136729e+00,-8.4983626096375908e-01,7.5625482416137840e-02,2.6167063762273193e-02,-8.7412814465715610e-03,6.2504532165061680e-04,3.3190353074508136e-06,0.0000000000000000e+00,-7.7747119826991428e-05,2.1310320829229061e-03,-4.6648608228157078e-03,-7.6455623003028245e-02,6.1941037781136477e-01,-2.3035603508541125e+00,4.7375544362167146e+00,};
    ++i; //7  2  7.333e+00
    reresN16[i] = a_t{4.3137805415445341e+00,7.9338119820054320e-01,-8.6359814186649952e-02,-1.0408345806509253e-01,-3.1274156119130606e-02,-4.3614572458171054e-03,-1.9650434047731349e-04,-1.5490537814666462e-07,9.1576624682134710e-11,7.0871563288801999e-06,6.8938664625842975e-04,8.2867333945927726e-03,3.1074709798521345e-02,-2.3742869920374582e-02,-6.8310752105898376e-01,-3.1651488793806197e+00,};
    imresN16[i] = a_t{2.4743366453044713e+00,-1.8036121710533846e+00,6.8382340353959048e-01,-1.6780224326964177e-01,2.6909782037936026e-02,-2.7080993909268034e-03,1.4462085320895372e-04,-1.0367215081108146e-06,0.0000000000000000e+00,-3.5431587875605972e-06,-1.9404111158476313e-04,7.3251244996903504e-03,-7.0901625099792129e-02,3.4598746564575605e-01,-9.5838075191819394e-01,1.0721470126663479e+00,};
    ++i; //8  2  8.333e+00
    reresN16[i] = a_t{-2.8274296174631370e+00,-9.3379672507264133e-01,-1.9701626546515882e-01,-2.3729758852059267e-02,-9.9015490463190501e-04,2.3166112726384137e-05,-3.9397912680433148e-06,-5.8554793839554282e-08,1.6479026407537482e-12,6.3913805617203115e-07,4.9425764200749063e-05,-4.6431343992068544e-06,-9.6035894215355383e-03,-1.0041841574939139e-01,-5.2232519637645880e-01,-1.6243580240823912e+00,};
    imresN16[i] = a_t{4.6275947724305633e-01,3.9655296398524925e-01,-2.3442842979720008e-01,6.8737522918925778e-02,-1.1947924294566137e-02,1.0961609468504391e-03,-3.3478841285418811e-05,3.4419817710257102e-08,0.0000000000000000e+00,2.0852436024108422e-07,-1.0175697001379113e-04,2.5690068582805859e-03,-2.1765622494478210e-02,8.6342970454594437e-02,-1.1037650232448629e-01,-6.1126676029076821e-01,};
    ++i; //9  2  9.333e+00
    reresN16[i] = a_t{9.3168100295914469e-01,4.3239816241624890e-01,1.2134933880074776e-01,2.2549339072648611e-02,2.6706453165882731e-03,1.7310408786863130e-04,3.8280721138251344e-06,3.1104289572910388e-09,2.6477973592895964e-14,2.3302858770895777e-08,-6.1569898539450982e-06,-4.0328134375824964e-04,-6.2097902477839632e-03,-4.4924780174466938e-02,-1.8289881891166365e-01,-3.7593069437619875e-01,};
    imresN16[i] = a_t{-1.1755007800977046e+00,1.8249594131855376e-01,1.5450500278875595e-03,-7.6580569279545724e-03,1.5686357046453242e-03,-1.1606321697304217e-04,1.6064323834660513e-06,2.3980453900062410e-09,0.0000000000000000e+00,4.5288678530638989e-08,-1.4710389228821028e-05,3.4731751790283822e-04,-1.9911816408408221e-03,-4.8388386453343882e-03,1.1736604473929274e-01,-7.2338144057424025e-01,};
    ++i; //10  2  1.033e+01
    reresN16[i] = a_t{7.9680351632479302e-02,-6.4715692977910896e-02,-2.7885504645572171e-02,-5.7900537632269702e-03,-6.5283735434268591e-04,-3.2654377314821181e-05,-3.6405132796452412e-07,5.5594230465793899e-11,3.8428386243994239e-16,-1.0496253089611917e-09,-1.9248966377795324e-06,-9.8327199588188705e-05,-1.3777024051753557e-03,-8.1697000477348510e-03,-1.5507457720804953e-02,9.8579653050043847e-02,};
    imresN16[i] = a_t{7.1072146295521510e-01,-1.8539840993868739e-01,3.3167851939061709e-02,-3.9652650287765635e-03,3.0426371391506285e-04,-1.4423449467994037e-05,2.8317480990589453e-07,-1.9736759783455983e-10,0.0000000000000000e+00,3.3233758168138750e-09,-6.4366966422078066e-07,-1.5246532810827176e-05,8.3833622416789016e-04,-1.1267184930154210e-02,7.8528741408949193e-02,-3.3385205180510785e-01,};
    auto v0 = T(1.0/3.0);
    auto h =  eve::half(eve::as(v0));
    using eve::spherical;
    using c_t = kyosu::complex_t<T>;
    std::array<c_t, 5> is;
    for(int j=0; j <= 15; ++j)
    {
      auto c = kyosu::complex(re[j], im[j]);
      auto jv = kyosu::bessel_i(v0+N-1, c, std::span(is));
      TTS_RELATIVE_EQUAL(jv, kyosu::bessel_i(v0+(N-1), c), tts::prec<T>());
      auto fac = kyosu::sqrt(eve::pio_2(eve::as(kyosu::real(c)))*kyosu::rec(c));
      for(int i=0; i < N; ++i)
      {
        auto res = kyosu::complex(reresN16[i][j], imresN16[i][j]);
        auto v = v0+i;
        //       std::cout<< "j " << j  << " c[" << j << "] = " << c << " i " << i << " v " << v << std::endl;
        TTS_RELATIVE_EQUAL(kyosu::bessel_i(v, c), res, tts::prec<T>());
        TTS_RELATIVE_EQUAL(kyosu::bessel_i[spherical](v, c), kyosu::bessel_i(v+h, c)*fac, tts::prec<T>());
        if (i < 5) TTS_RELATIVE_EQUAL(kyosu::bessel_i(v, c), is[i], tts::prec<T>()) << i << " -- " <<  j <<  " -- "<< c << '\n';
      }
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::bessel_ir over real negative order"
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
  int i=0; //0  -3.333e-01
  reresN16[i] = a_t{-1.6564313796793620e+01,4.1878807688831481e+00,7.1592122208913569e+00,2.9582453704487550e+00,-4.2922769480958989e-01,-1.2243787743936891e+00,-5.8196426681248958e-01,3.5209833836852678e-01,1.4371140801918962e+00,8.7019408352292482e-01,2.5534409995330368e-02,-1.8804210392625627e+00,-3.6742576763069326e+00,-1.2990818329665390e+00,9.6034248054750826e+00,2.3873147835157724e+01,};
  imresN16[i] = a_t{-1.9907582174184576e+01,1.3121018588254959e+01,-1.8923489778022429e+00,-2.7415697568391373e+00,2.2176745577064310e+00,-5.0452218290950945e-01,-4.1995005277922859e-01,5.6815110579191819e-01,0.0000000000000000e+00,4.0442726082624725e-01,-1.3244906917435351e+00,1.2867951159871540e+00,1.5044623205495895e+00,-7.0386776874849355e+00,9.0319028157758598e+00,5.9437083809445355e+00,};
  ++i; //-1  2 -1.333e+00
  reresN16[i] = a_t{1.7232236145140686e+01,-2.8558339391524061e+00,-6.5219674106273278e+00,-3.0762994505726891e+00,2.2605035412005980e-02,9.5007658231587344e-01,7.2756092399921313e-01,6.5672857813610064e-01,-2.8766224494585382e+00,1.8383416516860518e-01,-2.8538185426760199e-01,-1.8185804402442167e+00,-3.0971914574210149e+00,-4.4144991824842333e-01,9.7790262149820855e+00,2.2059199677109095e+01,};
  imresN16[i] = a_t{1.7750416423178635e+01,-1.2761968235554022e+01,2.4756032683511560e+00,2.1917430766820232e+00,-2.0735317233832924e+00,6.3463276802218527e-01,3.0038432332395959e-01,-6.6816206656238597e-01,0.0000000000000000e+00,8.0996249751877680e-01,-1.1509047533796222e+00,7.9679739271033323e-01,1.8538733100028264e+00,-6.6254642201586220e+00,7.5703247328540249e+00,7.4608974384267661e+00,};
  ++i; //-2  2 -2.333e+00
  reresN16[i] = a_t{-1.8031645894124019e+01,2.9314060282539245e-01,5.0612213330932114e+00,3.0425856762813339e+00,5.7159801090584939e-01,-4.3700706366707659e-01,-4.7982818504603142e-01,-5.8001806463824368e-01,2.7007091408712302e+01,-4.5486813339358501e-01,-6.7757554820663257e-01,-1.5237451804630822e+00,-1.9023678668037223e+00,1.0541859689359045e+00,9.6705693591796020e+00,1.8018891465178609e+01,};
  imresN16[i] = a_t{-1.3191395944656236e+01,1.1649554646427454e+01,-3.4273070832344867e+00,-1.0468989208008508e+00,1.6072285152422849e+00,-8.7661167408764251e-01,4.9395633424817131e-01,-1.5559716637737289e+00,0.0000000000000000e+00,-4.3041051564064925e-01,-3.4633808824841061e-01,-4.4380143857012076e-02,2.1960420231319464e+00,-5.4856341144382403e+00,4.6353105271720967e+00,9.9983368592873259e+00,};
  ++i; //-3  2 -3.333e+00
  reresN16[i] = a_t{1.7737134326114035e+01,2.6579184846971184e+00,-2.8492701524187338e+00,-2.4801500574460924e+00,-1.0260671214698416e+00,-3.5249063762126664e-01,-6.3009303688739493e-01,-6.5362899433599786e+00,-4.2298693325165010e+02,2.2494843462484839e+00,2.5640476470780327e-02,-6.2025604761652664e-01,-4.2191983546773654e-01,2.3299470937807074e+00,8.4760348944140400e+00,1.2013555670116476e+01,};
  imresN16[i] = a_t{6.8974612733780818e+00,-9.3340722827174734e+00,4.0248555318102950e+00,-2.6646794291286557e-01,-7.5124727927531598e-01,5.3288120176424103e-01,-7.2505096629146615e-02,-8.3861850684901651e-01,0.0000000000000000e+00,7.5289472276192693e-01,1.6573587797489742e-01,-6.1481337390786395e-01,1.9999669809267115e+00,-3.5352955866763089e+00,1.0260142772514884e+00,1.2011013343351314e+01,};
  ++i; //-4  2 -4.333e+00
  reresN16[i] = a_t{-1.5220836052926662e+01,-4.7536173741239995e+00,4.7080451537599455e-01,1.2891199368958211e+00,7.0337967785016686e-01,8.8134797756912381e-02,-1.1811617068858775e+00,-2.0425618548506026e+01,9.4267167192231391e+03,-1.0462798363428256e+01,-3.9902407655741284e-01,-1.8300448754288670e-02,5.2059696819740520e-01,2.5455110157605905e+00,5.8796275682042767e+00,5.1706025919483070e+00,};
  imresN16[i] = a_t{-2.7261219268783954e-01,5.8017627523396342e+00,-3.6093918766279867e+00,1.1377497492538740e+00,-1.8524689571431507e-01,2.2178597081400980e-01,-1.2206203516978946e+00,3.4081054431745564e+01,0.0000000000000000e+00,4.5582215626478604e+00,-6.6857509405284665e-01,-2.1837113097115204e-01,1.0214440017856332e+00,-1.2456309538105326e+00,-1.9392996789453389e+00,1.1895375286903361e+01,};
  ++i; //-5  2 -5.333e+00
  reresN16[i] = a_t{1.0350418895505474e+01,4.9735217865812871e+00,1.1265464889474814e+00,-6.6583597431562835e-02,-5.2503732487819463e-02,2.3095201647776115e-01,1.2695252274347042e+00,1.8705019922931859e+02,-2.7275035882192029e+05,2.7835983816296853e+01,-8.0305041404254296e-01,-2.0980220348785852e-01,4.1460314447493019e-01,1.5729790041781262e+00,2.6067182994784779e+00,-5.4134426258483037e-01,};
  imresN16[i] = a_t{-4.6980788111809115e+00,-1.9269590782781481e+00,2.1206256815764575e+00,-9.5625996578965133e-01,1.6426490461961119e-01,6.2833515625924474e-01,-6.2356625385117717e+00,2.5361800458260805e+02,0.0000000000000000e+00,-6.4338191623567894e+01,2.5992274666600097e+00,-3.3931826167287454e-01,2.2370157371009897e-01,3.0162775921075824e-01,-3.0647936528419155e+00,9.0862146976615783e+00,};
  ++i; //-6  2 -6.333e+00
  reresN16[i] = a_t{-4.5134149781083979e+00,-3.3261013467082812e+00,-1.2643196728817292e+00,-2.2260684047209678e-01,3.2545898286384817e-01,2.0931187615370468e+00,2.7211012987321084e+01,2.9996946966177966e+03,9.7072172526097260e+06,1.8421564327535054e+02,9.7623934556223144e+00,1.0812334796211289e+00,3.5796738994645355e-01,5.2104610381179484e-01,1.6817384097139787e-01,-3.3566304739033370e+00,};
  imresN16[i] = a_t{6.4342798725856909e+00,-8.3885515205390560e-01,-4.7881184057605586e-01,3.1228961959240720e-01,-8.9056414648722451e-02,6.0361362382782835e-01,-1.0065515220526644e+01,-7.5307294461446372e+02,0.0000000000000000e+00,4.9615382390859310e+02,-5.0228444548453854e+00,-8.4707378449870835e-02,4.1873539663639534e-02,5.7146425535505208e-01,-2.2898752492601959e+00,4.7359537521414472e+00,};
  ++i; //-7  2 -7.333e+00
  reresN16[i] = a_t{-1.9953775638992255e-02,1.1511254265900939e+00,6.1751130135565979e-01,2.3861916383546719e-01,6.1349144951474810e-01,6.0038625939697665e+00,1.2298414452558222e+02,5.0659546513100431e+03,-4.1013303435789949e+08,-4.2811706416820107e+03,-4.9781608507968542e+01,-2.2186516207905163e+00,-5.1409877870762767e-02,1.9418609419141593e-02,-6.5757375170631505e-01,-3.1561676731859407e+00,};
  imresN16[i] = a_t{-4.9739472985526634e+00,1.5798400363426253e+00,-2.1762075590584185e-01,-1.9699286938277324e-01,7.7863802827019180e-01,-4.7455310459575282e+00,9.9157712433873883e+01,-3.5790953038410516e+04,0.0000000000000000e+00,-2.0399466689674362e+03,-1.7597490039110852e+01,2.6188102295519879e+00,-5.4870173546910017e-01,4.4090532218381018e-01,-9.7160827872627220e-01,1.0698716874851963e+00,};
  ++i; //-8  2 -8.333e+00
  reresN16[i] = a_t{1.8071273486426582e+00,9.2648736603022419e-02,-2.0061584633890645e-01,-3.1474506404546260e-01,-7.1658196888043912e-01,-2.0164722140617131e+00,-1.5023275535194352e+02,-4.2390867651804030e+05,2.0060655563638931e+10,4.6539075921371528e+04,1.1499147874610598e+02,-1.4344245859927918e+00,-8.0771265822470140e-01,-3.2619833817027499e-01,-5.8030013085605925e-01,-1.6355596169880646e+00,};
  imresN16[i] = a_t{2.2103386591082108e+00,-1.0041298006380623e+00,3.3925274215161011e-01,-4.4662839074525229e-01,2.8116878284122135e+00,-3.1214358087605977e+01,9.8941228388700938e+02,-2.4581708964969311e+05,0.0000000000000000e+00,-1.5939488642665056e+04,2.7059756210668098e+02,-1.2943975088139114e+01,1.1337784625224154e+00,-1.5480266255175998e-02,-1.2111726621859985e-01,-5.9845921225395193e-01,};
  ++i; //-9  2 -9.333e+00
  reresN16[i] = a_t{-1.4868040172612629e+00,-4.1736669049768876e-01,-2.9960067339908214e-01,-1.2938846947871898e+00,-9.1529551690994460e+00,-1.2644810397483339e+02,-6.7358789350046673e+03,-5.9630455432927888e+06,-1.1148909976809661e+12,-2.5927773129756929e+05,7.8647772953020740e+02,4.5516831973157146e+01,4.5294980295783054e+00,5.7594118223985080e-01,-9.9159828286840612e-02,-3.7383282878037399e-01,};
  imresN16[i] = a_t{-2.3731037047225900e-01,3.2852441510628744e-01,-1.7876421214555938e-01,-1.2864512541639656e-01,3.8969089612355710e+00,-7.3014087575785453e+01,2.6195927782426511e+03,4.6421090564179532e+06,0.0000000000000000e+00,5.1861475803133735e+05,-1.6866802502557769e+03,3.2838171626972382e+01,-7.3343595447253795e-01,-2.2346531637337627e-01,2.2152608664265561e-01,-7.5744056378519176e-01,};
  ++i; //-10  2 -1.033e+01
  reresN16[i] = a_t{5.9465988438098982e-01,1.9369354489578172e-01,-2.3555701531274970e-01,-2.8486532405726548e+00,-3.2991058837654755e+01,-6.8318029556360159e+02,-4.5468501057300949e+04,3.5893874941196464e+07,6.9391056066823641e+13,-2.3739398402604586e+06,-1.2646540590916315e+04,-2.6417776357704196e+02,-1.3180620529325054e+01,-8.3321317079447055e-01,8.8615985674436425e-03,1.4322707749133157e-01,};
  imresN16[i] = a_t{-4.5561101942804594e-01,1.7524891471006365e-01,-5.7012648192364601e-01,2.7621732368161771e+00,-1.9730554917734498e+01,3.4687555041274288e+02,-3.6953743543417797e+04,1.2559147983223459e+08,0.0000000000000000e+00,-7.2762693890457768e+06,3.7774410123711477e+03,6.0077197107554362e+01,-1.0414875408740194e+01,1.7493688746458751e+00,-2.5449131972716643e-01,-2.7396235405501640e-01,};
  using eve::spherical;
  auto v0 = T(-1.0/3.0);
  auto h =  eve::half(eve::as(v0));
  using c_t = kyosu::complex_t<T>;
  std::array<c_t, 5> is;
  for(int j=0; j <= 15; ++j)
  {
    auto c = kyosu::complex(re[j], im[j]);
    auto iv = kyosu::bessel_i(v0-(N-1), c, std::span(is));
    TTS_RELATIVE_EQUAL(iv, kyosu::bessel_i(v0-(N-1), c), tts::prec<T>());
    auto fac = kyosu::sqrt(eve::pio_2(eve::as(kyosu::real(c)))*kyosu::rec(c));

    for(int i=0; i < N; ++i)
    {
      auto res = kyosu::complex(reresN16[i][j], imresN16[i][j]);
      auto v = v0-i;
      // std::cout<< "j " << j  << " c[" << j << "] = " << c << " i " << i << " v " << v << std::endl;
      if( ((i < 7) || (sizeof(T) == 8 ) || kyosu::is_not_real(c)) ) // The limitation of these tests with float is due to some overflow pbs when z is real
        TTS_RELATIVE_EQUAL(kyosu::bessel_i(v, c), res, tts::prec<T>()) << i << " -- " <<  j <<  " -- "<< c << " v " << v << '\n';
      TTS_RELATIVE_EQUAL(kyosu::bessel_i[spherical](v, c), kyosu::bessel_i(v+h, c)*fac, tts::prec<T>());
      if(i < 5)
        if (j!= 8) TTS_RELATIVE_EQUAL(kyosu::bessel_i(v, c), is[i], tts::prec<T>()) << i << " -- " <<  j <<  " -- "<< c << " v " << v << '\n';
    }
  }
};