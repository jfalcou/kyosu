//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL ( "Check kyosu::bessel_yr over real positive order"
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
    //res are taken from octave 9.2.0 besselj outputs
    int i=0;
    reresN16[i] = a_t{2.6513657493935034e+02,1.5122843619345218e+02,5.0648789106855794e+01,7.0207071123160771e+00,-4.0157239964866642e+00,-3.8818208974565880e+00,-1.9700774006295092e+00,-8.8015136866517407e-01,-1.2133448538831417e+00,-4.7036021607109069e-02,1.3293987996432377e+00,4.1474049533381976e+00,7.7005870282777540e+00,4.6857906393290154e+00,-2.8742001471989823e+01,-1.3952369860713620e+02,};
    imresN16[i] = a_t{2.8090371647178273e+02,-1.7536301901048642e+01,-3.3401195686627879e+01,2.3525800606543957e+01,-9.3284782480155641e+00,1.9546375587054139e+00,5.0096629910926505e-01,-9.8992537961477600e-01,0.0000000000000000e+00,8.4240922212198033e-01,-1.2574860466731328e+00,1.8207337449423835e-01,6.0487612323155489e+00,-2.3373344181702222e+01,5.1769001839281714e+01,-5.2626238180368290e+01,};
    ++i; //1   1.333e+00
    reresN16[i] = a_t{-2.7341624336594754e+02,-2.4492590819747971e+01,2.6834829208655936e+01,2.0180308717562898e+01,8.3159948289824452e+00,2.0870574869377925e+00,1.5875901804361703e-01,2.6219422251017110e-01,-3.7648698799182263e+00,-7.0929009222227590e-01,-7.3302686894198221e-01,4.1783434159729838e-01,6.0593389866595722e+00,2.1283861339833010e+01,4.5200094848540786e+01,4.0490326809936846e+01,};
    imresN16[i] = a_t{2.3218020651347828e+02,-1.3762546766746826e+02,4.7847145978408072e+01,-8.0137287884077182e+00,-2.5136202055984631e+00,2.8463982601995266e+00,-1.4042283946981760e+00,2.1848931073183459e-01,0.0000000000000000e+00,5.1146239824658346e-01,-1.2892829386112927e+00,3.4594908691251631e+00,-6.0609779957998171e+00,2.2646223823910492e+00,2.9701618940993288e+01,-1.3184192400111763e+02,};
    ++i; //2   2.333e+00
    reresN16[i] = a_t{-1.6938827821665609e+02,-1.1032975920967719e+02,-4.1149236053067320e+01,-8.8752923528883674e+00,3.1900874317130989e-01,1.2029759612721256e+00,4.4322303889216835e-01,1.3677895547918964e-01,-3.2252165189834493e+01,-2.1673423702714734e-01,-8.1370641453586212e-01,-2.0911673693799302e+00,-3.2202681068310364e+00,1.5482719031537946e+00,2.9936227874240455e+01,1.1454232850030996e+02,};
    imresN16[i] = a_t{-2.5319821526191888e+02,3.5082064559053933e+01,1.5299895442262720e+01,-1.3949903844476678e+01,6.0949287286826914e+00,-1.7067823098046875e+00,1.2712490912144936e-01,1.3917610077008402e+00,0.0000000000000000e+00,7.8526076516983290e-01,-1.5822163925744692e-01,1.0915083890303339e+00,-5.4814490719970470e+00,1.6759838999411549e+01,-3.2575740597173763e+01,1.8643762554369022e+01,};
    ++i; //3   3.333e+00
    reresN16[i] = a_t{2.1626349472997933e+02,4.1915596170925937e+01,-3.8449216017591885e+00,-7.1827078234769655e+00,-3.3699168844845420e+00,-9.6042723672699748e-01,-3.6772493893541591e-01,-6.0813368255260407e+00,-4.9793547751750742e+02,2.0358519912218762e+00,1.0433411431338413e-02,-9.6932194936359006e-01,-3.8830860620810541e+00,-1.0672326559520391e+01,-1.7808423344897893e+01,4.0729304456773292e+00,};
    imresN16[i] = a_t{-9.5506681582433202e+01,7.5521698377505160e+01,-3.0785624548283039e+01,8.0485871645935969e+00,-9.4985537674592535e-01,-2.9912417031639221e-01,4.8497256044027054e-01,-1.9078445597019658e+00,0.0000000000000000e+00,1.8265259402130365e+00,4.8390769116596344e-03,-6.4775393630275346e-01,6.1740252128192852e-01,4.3550902743696653e+00,-2.6961639777649573e+01,8.8584505628891179e+01,};
    ++i; //4   4.333e+00
    reresN16[i] = a_t{3.1099649358773853e+01,4.1775632354033405e+01,1.9054781448779423e+01,5.6103905769062026e+00,1.0668701195186356e+00,2.2738435302949467e-01,1.3155006382792942e+00,2.4807929607235593e+01,-1.1032980668532542e+04,1.3091327341810164e+01,8.2150384618555350e-01,1.6269650787094408e-01,-5.5616736826436464e-01,-4.7226109082804220e+00,-2.0261332038524046e+01,-5.8320096541712665e+01,};
    imresN16[i] = a_t{1.6459485293861624e+02,-4.0212303949023656e+01,3.3336351635901722e+00,2.2834229432121367e+00,-1.3445748770563453e+00,4.3071575010344182e-01,1.3132686488563211e-01,-3.1956123086121796e+01,0.0000000000000000e+00,-1.4830142685326191e+00,1.8637186045967039e-01,-4.8023630187397814e-01,1.9363764617275567e+00,-4.9425678972806049e+00,5.5324316704999195e+00,1.9242342666610543e+01,};
    ++i; //5   5.333e+00
    reresN16[i] = a_t{-1.0785433800071735e+02,-3.0882368837307823e+01,-5.3466930137857078e+00,-4.0423831991945880e-02,2.3609898212396449e-01,-2.4429542748456951e-01,-1.6024811570808952e+00,1.7069534036688120e+02,-3.1823261716897838e+05,4.8266837992980811e+01,1.2773814534694170e+00,3.5265145579937834e-01,6.7847533838232088e-01,1.2983594839238364e+00,-1.3538592572076291e+00,-2.3285497020797653e+01,};
    imresN16[i] = a_t{-1.0005671556040932e+01,-1.6549080358038690e+01,9.2366008445947099e+00,-2.9467144241229399e+00,5.9693964009761336e-01,2.3317870276354796e-01,-5.1018619735082389e+00,2.8275550257228588e+02,0.0000000000000000e+00,-6.4982006251698408e+01,2.4603682880600961e+00,-3.1559459239801096e-01,6.6114149167846847e-01,-3.2934463441369788e+00,1.2066983229138389e+01,-3.0650864128288603e+01,};
    ++i; //6   6.333e+00
    reresN16[i] = a_t{2.5839735324960081e+01,-2.5658324060460540e+00,-3.1679452170366620e+00,-1.1115851639697099e+00,-2.0514194929276416e-01,-4.5379336289304051e-01,-1.8597127610466096e+01,-3.2527034580581621e+03,-1.1303904518672930e+07,-1.0223889138830403e+02,-5.0776247638009302e+00,-2.3526762496256098e-01,3.3071692745584763e-01,1.6033504128715463e+00,5.3764934427760842e+00,1.1237419577845513e+01,};
    imresN16[i] = a_t{-5.8511411290633554e+01,1.8919896162755798e+01,-4.1548466897150398e+00,5.0957501281773232e-01,1.7639748500127458e-01,-1.4351671204111502e+00,1.7920134140915223e+01,5.6154820895248236e+02,0.0000000000000000e+00,-6.0251082170308973e+02,1.0244032004683625e+01,-8.3169243464154929e-01,4.7615198918562113e-02,-1.9790364493432597e-01,3.2243363746086029e+00,-1.8735383427124965e+01,};
    ++i; //7   7.333e+00
    reresN16[i] = a_t{2.4632881719544720e+01,9.1026991550758165e+00,2.2365220570051583e+00,4.0316979778221856e-01,4.5754750331433292e-01,5.5451809870911903e+00,1.3847325075573985e+02,7.9046669074175361e+03,-4.7695773594902158e+08,-4.5116816875718068e+03,-5.4812020645414037e+01,-2.9784270869132481e+00,-2.6560349380756620e-01,3.4060355766785794e-01,2.4456025775273238e+00,1.1173021643658572e+01,};
    imresN16[i] = a_t{2.4226972077797676e+01,-2.4062088345590062e+00,-5.2710537560995374e-01,3.6285609350544934e-01,-3.8085252073612907e-01,1.0313362118964764e+00,4.7604746893864373e+01,-3.8253521072195224e+04,0.0000000000000000e+00,-3.1034068857419443e+03,1.0885784854353616e+01,-7.9167371820671573e-01,6.6153099052972952e-02,4.7723720980541584e-01,-1.5354156735175408e+00,1.3186469929791218e+00,};
    ++i; //8   8.333e+00
    reresN16[i] = a_t{-1.5764424381364634e+01,-2.6663701212399840e+00,-2.3596680628634031e-01,-1.8045653200962541e-01,-1.5530643280725624e+00,-1.5213818678173384e+01,-1.4217623194921231e+02,4.4694028667818569e+05,-2.3306629852989143e+10,-5.5741743979579362e+04,-2.3961943432957560e+02,-9.2277592761513851e+00,-9.5379726051162317e-01,-2.3467984999749802e-01,-1.0491389812991619e-01,1.7493006830111866e+00,};
    imresN16[i] = a_t{6.6762346380030486e+00,-3.2858786414801169e+00,9.0033558775126077e-01,-1.5385029141666443e-01,-7.5519274046716545e-01,1.9144373610439366e+01,-9.4496529192518722e+02,2.9284859972122370e+05,0.0000000000000000e+00,1.0929859368455514e+04,-2.0420634984168402e+02,7.8224700053262879e+00,-5.3860741809474633e-01,2.3898950355955056e-01,-1.1998813991375332e+00,4.9725207484766374e+00,};
    ++i; //9   9.333e+00
    reresN16[i] = a_t{1.5470403447523570e-01,-7.2507347851148529e-01,-1.7888875913873770e-01,2.3375432230580967e-01,1.8806287744427852e-01,-4.6460550282578716e+01,-5.6840162088691141e+03,-6.7841218277191725e+06,-1.2943358118745601e+12,-3.6892069007179351e+05,5.7375303962031694e+01,4.4698315056300011e+00,-2.5655050541607349e-01,-2.1249162062962595e-01,-4.5236528767823331e-01,-1.5500142810869957e+00,};
    imresN16[i] = a_t{-7.8061968453247825e+00,1.5630054190631415e+00,-1.5489291720782256e-01,-5.5674643001452884e-01,6.4484473997310099e+00,-1.1010177266793004e+02,4.1872458129785955e+03,4.7767714347172547e+06,0.0000000000000000e+00,5.5870010145269916e+05,-2.0098931950866086e+03,5.3250126565132263e+01,-3.6356390017864162e+00,4.0239402900196908e-01,-2.5093978867458966e-01,1.6648711358566404e+00,};
    ++i; //10   1.033e+01
    reresN16[i] = a_t{2.9396792257641189e+00,6.4280875575065766e-01,1.5151249927645868e-01,1.2587787590893371e+00,2.2798358930283008e+01,6.4648618460127216e+02,5.2548249777690740e+04,-3.3646615977269173e+07,-8.0513143886786344e+13,1.8270162502013647e+06,1.1394441243080695e+04,2.2482772804983915e+02,1.0973919200638228e+01,8.0476192615171493e-01,-7.0969263353062736e-02,-8.6702237947239325e-01,};
    imresN16[i] = a_t{1.4591829471400704e+00,2.2580468127932633e-02,-2.8889748198543175e-01,1.7166593200227021e+00,-1.3400743147321002e+01,7.0531177518485521e+01,2.5172442791212405e+04,-1.4020965966004884e+08,0.0000000000000000e+00,8.6468641948601417e+06,-8.7418893506178028e+03,1.3684522008970387e+02,-8.4242227774450473e+00,9.8757492466825803e-01,-7.5564902526958286e-02,-1.8374259247297453e-01,};

    auto v0 = T(1.0/3.0);
    auto h =  eve::half(eve::as(v0));
    using eve::spherical;
    using c_t = kyosu::complex_t<T>;
    std::array<c_t, 5> ys;
    for(int j=0; j <= 15; ++j)
    {
      auto c = kyosu::complex(re[j], im[j]);
      auto yv = kyosu::bessel_y(v0+(N-1), c, std::span(ys));
      TTS_RELATIVE_EQUAL(yv, kyosu::bessel_y(v0+(N-1), c), tts::prec<T>());
      auto fac = kyosu::sqrt(eve::pio_2(eve::as(kyosu::real(c)))*kyosu::rec(c));
      for(int i=0; i < N; ++i)
      {
        auto res = kyosu::complex(reresN16[i][j], imresN16[i][j]);
        auto v = v0+i;
        //       std::cout<< "j " << j  << " c[" << j << "] = " << c << " i " << i << " v " << v << std::endl;
        TTS_RELATIVE_EQUAL(kyosu::bessel_y(v, c), res, tts::prec<T>());
        TTS_RELATIVE_EQUAL(kyosu::bessel_y[spherical](v, c), kyosu::bessel_y(v+h, c)*fac, tts::prec<T>());
        if (i < 5) TTS_RELATIVE_EQUAL(kyosu::bessel_y(v, c), ys[i], tts::prec<T>()) << i << " -- " <<  j <<  " -- "<< c << '\n';
      }
    }
 }
};


TTS_CASE_TPL ( "Check kyosu::bessel_yr over real negative order"
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
  //res are taken from octave 9.2.0 besselj outputs
  int i=0; //0  -3.333e-01
  reresN16[i] = a_t{3.7583805458938821e+02,9.0801266745274788e+01,-3.6012541742235697e+00,-1.6862151475581715e+01,-1.0085674143682983e+01,-3.6432335856963327e+00,-6.0906440868768552e-01,2.0873153295804381e-01,-1.0003474349638408e-01,8.6097480021168360e-01,1.8102650205095943e+00,2.2453391061314565e+00,-1.3867486242808820e+00,-1.7899822024160851e+01,-5.9204838602123715e+01,-1.1533771231556815e+02,};
  imresN16[i] = a_t{-8.9163224441390696e+01,1.2219965550991174e+02,-6.0563732479780832e+01,1.7841777572774447e+01,-1.1808300271084744e+00,-2.3998139242391443e+00,1.9741006840075483e+00,-1.1510312786004779e+00,0.0000000000000000e+00,3.2456737045081957e-01,5.2569711539964548e-01,-3.4904700264222477e+00,9.6878805608040661e+00,-1.5743030177502007e+01,9.9294471444101262e-01,9.4517889913758978e+01,};
  ++i; //-1  -1.333e+00
  reresN16[i] = a_t{-6.4365756223188953e+01,-1.0694069643885213e+02,-5.4854222620856866e+01,-1.7031518837618616e+01,-1.9875922496399472e+00,1.4019111602329308e+00,1.1040124764744512e+00,1.8184927791552408e-01,1.8250217738076471e+00,4.4431381046870499e-02,-7.5734466470992046e-01,-3.2187380543211570e+00,-8.2848656305405033e+00,-1.2604917207425061e+01,3.1220711799762526e+00,9.3933366404745584e+01,};
  imresN16[i] = a_t{-3.5287550574020077e+02,9.0023767742338606e+01,-6.8323205462091607e-01,-1.3471491597814282e+01,8.4602113354090616e+00,-3.2209846484337490e+00,7.6651927320185809e-01,4.4399377244116897e-02,-0.0000000000000000e+00,-5.9722794528212364e-01,1.2087465045406005e+00,-1.3529391838467266e+00,-2.2180312587312692e+00,1.7299030530509278e+01,-5.3994605935481687e+01,1.0098639748763406e+02,};
  ++i; //-2  -2.333e+00
  reresN16[i] = a_t{-3.0397022853694108e+02,-8.5547022329552618e+01,-7.3253656731300190e+00,7.6409393477382856e+00,5.4343092339318328e+00,2.0877839436740886e+00,4.4598068647050371e-01,6.0553727755350381e-02,-1.6122381023682710e+01,-1.2391271456467906e-01,-3.7631090765501235e-01,-1.1637995854139815e-01,3.1372063537876396e+00,1.5290189349087752e+01,4.3180331062080654e+01,7.3417379588297777e+01,};
  imresN16[i] = a_t{2.0095537607248048e+01,-7.8007553393350634e+01,4.3286380882402035e+01,-1.4659876621197661e+01,2.7628715959429750e+00,2.2040088548542858e-01,-4.1238800148883037e-01,7.7381397511110506e-01,0.0000000000000000e+00,5.3097839798783864e-01,-7.3476522504616504e-01,2.3325368517643739e+00,-5.5212415474781338e+00,7.0370868338197443e+00,9.6378487494907397e+00,-8.9874568928399668e+01,};
  ++i; //-3  -3.333e+00
  reresN16[i] = a_t{-2.5420652614009327e+01,4.4445597281822764e+01,2.8583175560551776e+01,1.0562759088231937e+01,2.5191280371276972e+00,2.8297425836662049e-01,7.4168368908339694e-02,3.0286382298389114e+00,2.4896757192792356e+02,-9.9425130903424330e-01,1.9531144269234244e-01,1.0946147217305340e+00,2.4883762069669175e+00,1.5667651474280153e+00,-1.4445221176739876e+01,-7.8753099348130291e+01,};
  imresN16[i] = a_t{2.3504303494829605e+02,-7.4060627540113316e+01,1.2061906009162515e+01,2.1999419669844160e+00,-2.4523937630017656e+00,9.8425198721151197e-01,-3.7389713639788236e-01,9.5721156299935650e-01,-0.0000000000000000e+00,-9.3085131734041826e-01,1.4704051870270393e-01,-5.2739497329016594e-01,3.0502364825818935e+00,-1.1417182703625144e+01,2.8902266495880575e+01,-4.0764707948616582e+01,};
  ++i; //-4  -4.333e+00
  reresN16[i] = a_t{1.5809309830632461e+02,5.5712867513474251e+01,1.2415901197594899e+01,8.3438015987888403e-01,-6.0812342274792441e-01,-2.0210331911283841e-01,6.1528544097023774e-01,1.2403048886813172e+01,-5.5164903284857428e+03,6.5409214691468929e+00,3.3959255722291448e-01,-3.5556693047521520e-01,-1.9691783207978846e+00,-6.6471525069817226e+00,-1.4923490259637642e+01,-1.2496016073429061e+01,};
  imresN16[i] = a_t{5.5364183992194341e+01,1.6073111388667900e+01,-1.4836145017135518e+01,6.0004023217633824e+00,-1.5806909993867779e+00,2.8217580399216569e-01,7.5919527757555699e-02,-1.5979294461543137e+01,0.0000000000000000e+00,-7.4231170363391830e-01,1.1493768060564084e-01,-2.7761720357646974e-01,4.6872614363288245e-01,1.6206413627515039e+00,-1.4780233599389758e+01,6.0127487207892329e+01,};
  ++i; //-5  -5.333e+00
  reresN16[i] = a_t{6.2592544879673994e+01,1.1101098036442121e+00,-5.3233239423179093e+00,-2.5276405569118165e+00,-6.4850868944818474e-01,5.8836127714752787e-02,7.9911046463970248e-01,-8.5347588683075813e+01,1.5911630858432699e+05,-2.4133057674855312e+01,-6.3233280881520215e-01,-1.0451719822967674e-01,2.1191393482833087e-01,2.2031409591650855e+00,1.1128669584874952e+01,3.8187864828102185e+01,};
  imresN16[i] = a_t{-8.8401890409113491e+01,3.5019399084356756e+01,-9.2467300533774477e+00,1.4962749492704039e+00,-3.4344078585097249e-02,-1.9531172257004475e-01,2.5598306888174895e+00,-1.4137788209667499e+02,-0.0000000000000000e+00,3.2491528399390596e+01,-1.2471401054642366e+00,2.9227963738467611e-01,-8.7640831407779363e-01,2.7605803325342602e+00,-4.8587002047275405e+00,-4.8407242619353905e+00,};
  ++i; //-6  -6.333e+00
  reresN16[i] = a_t{-3.7752201515772754e+01,-1.7667668169154876e+01,-5.1841017948272468e+00,-1.0181334813365588e+00,-1.0325714799308074e-01,-2.1622359838047683e-01,-9.2973376309255666e+00,-1.6263517161962873e+03,-5.6519522593364799e+06,-5.1119432000001780e+01,-2.5368863138830089e+00,-9.6825218686702658e-02,2.3545286801995352e-01,6.4990103774612373e-01,-1.0109557461231544e-01,-1.0606467149097131e+01,};
  imresN16[i] = a_t{-5.1633301609702997e+01,7.2364237177603261e+00,6.7178839677136404e-01,-7.2570459275108146e-01,2.9594735090475899e-01,-7.4236707525172074e-01,8.9611316547962936e+00,2.8077410682389484e+02,0.0000000000000000e+00,-3.0125548069234429e+02,5.1252036595698520e+00,-4.5591322056969297e-01,3.0980725606112136e-01,-1.4785184331517105e+00,6.2643714908550878e+00,-1.9098299768470383e+01,};
  ++i; //-7  -7.333e+00
  reresN16[i] = a_t{-3.3297904476904691e+01,-6.6375693582053348e+00,-6.7453871769165241e-01,5.2338779071946367e-02,-1.7236661237752371e-01,-2.7663399596298075e+00,-6.9236392533558899e+01,-3.9523334535225517e+03,2.3847886797451162e+08,2.2558408380597139e+03,2.7405353321836539e+01,1.4777007368288702e+00,3.9997493891446245e-02,-6.2206597227964910e-01,-2.5623641438458238e+00,-6.7307999189547614e+00,};
  imresN16[i] = a_t{9.2198720756386230e+00,-6.6816634379309585e+00,2.2011258821928101e+00,-5.0119660103530572e-01,2.2041017358140952e-01,-5.1624649452808602e-01,-2.3802463880107183e+01,1.9126760537034061e+04,-0.0000000000000000e+00,1.5517034466521120e+03,-5.4429806760115138e+00,3.9744960348415581e-01,-6.4423791909899830e-02,8.7452619788850133e-02,-1.3526048851960817e+00,9.0161747817929641e+00,};
  ++i; //-8  -8.333e+00
  reresN16[i] = a_t{-2.1018046906156940e+00,1.5074801371162101e+00,6.4821637625801909e-01,4.4864921608623778e-02,-7.6194911285868694e-01,-7.6061800530461960e+00,-7.1088111964392866e+01,2.2347014333904066e+05,-1.1653314926494545e+10,-2.7870871989219970e+04,-1.1980964140563195e+02,-4.6120398551397672e+00,-4.5404255359766277e-01,6.6544653697505618e-02,9.9152763855131076e-01,5.1839929629870660e+00,};
  imresN16[i] = a_t{1.6990422513776199e+01,-3.9486876740030650e+00,6.2766470427458243e-01,-5.0714370752505580e-02,-3.8720434992331876e-01,9.5732535759191499e+00,-4.7248267962346824e+02,1.4642429986064491e+05,0.0000000000000000e+00,5.4649296843481061e+03,-1.0210324612478266e+02,3.9131358748940679e+00,-2.8705772734036261e-01,1.9829030662856306e-01,-6.6863874274176260e-01,9.6754768574066419e-01,};
  ++i; //-9  -9.333e+00
  reresN16[i] = a_t{6.6821038162322370e+00,1.7187160022362993e+00,2.7164072958996044e-01,-1.0436493524624360e-01,-9.4341539272996863e-02,2.3230169796604628e+01,2.8420081010623635e+03,3.3920609138595765e+06,6.4716790593727869e+11,1.8446034503587251e+05,-2.8687650999608778e+01,-2.2348280768771573e+00,1.2875234783138662e-01,9.6237195575222950e-02,5.1636194236467231e-02,-6.6215054740473089e-01,};
  imresN16[i] = a_t{4.0343360899402541e+00,-1.3996433198253944e-01,-1.3864114476553230e-01,3.1835012238834126e-01,-3.2285055490443648e+00,5.5051100246969654e+01,-2.0936229088473438e+03,-2.3883857173586241e+06,-0.0000000000000000e+00,-2.7935005072638608e+05,1.0049466120823845e+03,-2.6625595115188172e+01,1.8254866378983008e+00,-2.6526697775919050e-01,4.8140740698275730e-01,-2.1652404544521939e+00,};
  ++i; //-10  -1.033e+01
  reresN16[i] = a_t{2.7383770450678435e+00,3.3533259586989628e-01,4.1165645376207913e-02,6.2138401778419916e-01,1.1398315067730941e+01,3.2324305252005945e+02,2.6274124888442104e+04,-1.6823307988634657e+07,-4.0256571943393344e+13,9.1350812510068552e+05,5.6972206200408809e+03,1.1241377591846260e+02,5.4853792619888306e+00,3.8811625362303392e-01,-1.1010205159654510e-01,-6.1800796583856066e-01,};
  imresN16[i] = a_t{-1.8205761273921781e+00,5.7643622590665566e-01,-2.3065852627917557e-01,8.6674278354989098e-01,-6.7007848884791592e+00,3.5265591169858915e+01,1.2586221395809618e+04,-7.0104829830024719e+07,0.0000000000000000e+00,4.3234320974300923e+06,-4.3709446763854930e+03,6.8422656052972840e+01,-4.2130725115425953e+00,5.0653751308254713e-01,-1.5307638509887631e-01,6.5859209049037148e-01,};
  using eve::spherical;
  auto v0 = T(-1.0/3.0);
  auto h =  eve::half(eve::as(v0));
  using c_t = kyosu::complex_t<T>;
  std::array<c_t, 5> ys;
  for(int j=0; j <= 15; ++j)
  {
    auto c = kyosu::complex(re[j], im[j]);
    auto yv = kyosu::bessel_y(v0-(N-1), c, std::span(ys));
    TTS_RELATIVE_EQUAL(yv, kyosu::bessel_y(v0-(N-1), c), tts::prec<T>());
    auto fac = kyosu::sqrt(eve::pio_2(eve::as(kyosu::real(c)))*kyosu::rec(c));

    for(int i=0; i < N; ++i)
    {
      auto res = kyosu::complex(reresN16[i][j], imresN16[i][j]);
      auto v = v0-i;
      // std::cout<< "j " << j  << " c[" << j << "] = " << c << " i " << i << " v " << v << std::endl;
      if( ((i < 7) || (sizeof(T) == 8 ) || kyosu::is_not_real(c)) ) // The limitation of these tests with float is due to some overflow pbs when z is real
        TTS_RELATIVE_EQUAL(kyosu::bessel_y(v, c), res, tts::prec<T>());
      TTS_RELATIVE_EQUAL(kyosu::bessel_y[spherical](v, c), kyosu::bessel_y(v+h, c)*fac, tts::prec<T>());
      if(i < 5)
        if (j!= 8) TTS_RELATIVE_EQUAL(kyosu::bessel_y(v, c), ys[i], tts::prec<T>()) << i << " -- " <<  j <<  " -- "<< c << " v " << v << '\n';
    }
  }
};
