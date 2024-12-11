//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_h1n integral positive order"
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
  int i=0;
  reresN16[i] = a_t{5.4897235878702522e-05,-1.2268421138042991e+02,6.2791919542924018e-04,-4.8089232666858855e+01,-2.4084160260729008e-03,6.1781027538348077e-01,-6.6559203024245964e-02,2.5605247393843049e+00,9.7762624653829611e-01,2.2744989480229472e-01,9.8407508041674696e-01,8.0887252704128568e-03,-1.8273514210562674e+01,-1.7457419869508024e-03,-6.1802005844609923e+01,-1.6987525206133878e-04,};
  imresN16[i] = a_t{-6.5539561898233831e-05,2.8056814033312583e+02,3.7023665194116904e-04,-1.1742199634170285e+01,6.1311336939828889e-03,-8.8084554422437513e+00,-1.6219886131682522e-02,-6.6297629083583021e-01,-8.0727357780451992e-01,-5.1055458673089568e-02,3.6321658845974136e+00,1.8052231450423499e-02,7.4948386100868873e+00,1.1896731293522277e-03,-1.0185845035564768e+02,-1.7463870535747248e-04,};
  ++i; //1   1.000e+00
  reresN16[i] = a_t{-6.9868644506618311e-05,2.7064676972685243e+02,3.6886164009504170e-04,-8.5309491355821621e+00,6.7926396008222457e-03,-7.7947066285489113e+00,-1.3037972953166450e-02,-2.6465006046269030e-01,1.4831881627310406e-01,-1.5640669069980788e-02,3.2658114168417036e+00,2.0448522418679817e-02,5.6969763924510062e+00,1.1844646693963893e-03,-9.9003239995999664e+01,-1.8815491376888570e-04,};
  imresN16[i] = a_t{-5.5439750416853029e-05,1.0676239189527861e+02,-6.7744869054317850e-04,4.5195192232412410e+01,2.2998038589222207e-03,2.9120943115132863e-01,8.0073592652737891e-02,-8.4023335956971990e-01,-2.2931051383885306e+00,-2.9266650676425737e-01,-3.2109920594551683e-01,-7.5444920068123474e-03,1.7334275515362012e+01,1.9088885170084806e-03,5.4155975118041177e+01,1.7188222826493554e-04,};
  ++i; //2   2.000e+00
  reresN16[i] = a_t{-5.6487293158531979e-05,6.5890828141819014e+01,-8.4284801947258066e-04,3.6813584316790795e+01,1.7088759302197115e-03,1.5320007765665287e+00,1.3354152761309773e-01,-9.2932925015189749e-01,1.1165861949063943e-02,-5.3575707063653277e-01,8.1391557866073649e-01,-4.5056659500341961e-03,1.4237866007138228e+01,2.4579837886114860e-03,3.4408212753401202e+01,1.7578714175771814e-04,};
  imresN16[i] = a_t{8.4060135972775416e-05,-2.4056185796796944e+02,-3.5348679634467821e-04,1.1134050358938667e+00,-9.0902409344857694e-03,4.9018709877144806e+00,-7.5824194390195195e-03,7.8615436560341267e-01,-1.4480094011452358e+01,-2.2597037902118694e-01,-1.8946465279715725e+00,-2.8818132273240451e-02,-1.5187230562074436e+00,-1.1221552278486639e-03,8.9402715175387669e+01,2.3278894163732160e-04,};
  ++i; //3   3.000e+00
  reresN16[i] = a_t{1.1208229382890835e-04,-1.9192184405276925e+02,-2.7777111106750833e-04,-5.4725122711374690e+00,-1.4097476196506266e-02,2.0877738308485188e+00,-1.1138469058038176e-01,-1.1643936138223201e+00,5.5934304776041695e-04,-1.5078142302454585e+00,-2.6264767828356361e-01,-4.6808412689629257e-02,2.1456283474097195e+00,-8.0621291914483473e-04,7.1868709602255961e+01,3.2195900259589173e-04,};
  imresN16[i] = a_t{5.5716854320101858e-05,-1.7376967514127351e+01,1.1801385263236690e-03,-2.4706540079280316e+01,5.5684308316057988e-04,-1.6727014076828581e+00,-2.7872418293548179e-01,-3.4487011107518746e+00,-1.9077481501430970e+02,9.1223988999494887e-01,-6.0375881450742841e-01,-7.5358656099016067e-03,-9.1744281816158395e+00,-3.5878042177064882e-03,-1.0866268820465949e+01,-1.7293470042642709e-04,};
  ++i; //4   4.000e+00
  reresN16[i] = a_t{4.6824920084426248e-05,2.0011046593782176e+01,1.7993961730877297e-03,-1.2799156451176460e+01,8.3956803369015457e-03,-9.1429914542866508e-01,-6.3441508565441440e-01,2.1176528679190525e+01,2.0999005910771326e-05,-1.2509659501149950e+00,-1.5120157929980915e-01,-5.0351158149484113e-02,-4.0818736752131617e+00,-5.6531100839384858e-03,7.0431799007798768e+00,-1.3920292998652033e-04,};
  imresN16[i] = a_t{-1.6172053418286162e-04,1.3250722360613375e+02,9.5016075623396965e-06,7.6888140727343410e+00,2.3921107562294385e-02,-3.5570234733472150e-01,6.1721694810288918e-01,3.2636372307812445e-01,-3.8010162062747440e+03,7.4861327397424073e+00,5.4339659366409299e-01,7.8549498372884330e-02,-3.1337284799199030e+00,-3.3868525362605421e-04,-4.8622550063767491e+01,-4.8157695797519608e-04,};
  ++i; //5   5.000e+00
  reresN16[i] = a_t{-2.4603267714178506e-04,7.5661709551704888e+01,-8.0961579456312728e-04,6.0430526298418910e+00,4.0954187893377701e-02,-3.1467219439377231e-01,3.0784334282780925e+00,-5.9504400832759345e+01,6.3044940002188614e-07,2.6448481388755098e+01,-1.2976842487270159e+00,1.0903373277629110e-01,-2.1827683625541732e+00,-3.8946480518686579e-03,-2.5869831744675270e+01,-7.5277372555815120e-04,};
  imresN16[i] = a_t{-1.3799645459747282e-05,-3.6152781907963863e+01,-2.8725319351140619e-03,4.5930355869688029e+00,-3.4133648567508321e-02,2.9843133507926495e-01,1.1845077198193978e+00,1.4859341276564339e+02,-1.0116965735231226e+05,3.4036154869434654e+01,1.3252346352671844e+00,1.9158587674452207e-01,1.0394643429264685e+00,9.0601260140378108e-03,-1.4241983038346410e+01,1.1989969067628880e-05,};
  ++i; //6   6.000e+00
  reresN16[i] = a_t{8.2784812261483496e-05,-3.3547875354058021e+01,-4.5484080871451742e-03,7.9491514858336609e-01,-1.1577548438340833e-01,6.4560302179385731e-01,-1.3181018653381145e+00,-1.0969666358562558e+03,1.5767594796476312e-08,3.0367414724106374e+02,-6.8974667710199240e+00,6.1704396905508363e-01,-1.8381913838457831e-01,1.3386621106526761e-02,-1.2547596722283924e+01,-3.6454425431502923e-04,};
  imresN16[i] = a_t{3.8339493293092778e-04,-3.3314697431879431e+01,3.1267157941802120e-03,-3.2854232467101374e+00,-5.9194199766671923e-02,-8.5442264149207103e-01,-1.4935499766447458e+01,-1.0256864149214980e+03,-3.3685208955374686e+06,3.0452234663655361e+01,-1.0404497395274004e+00,1.1358974430624866e-02,9.8271950407271658e-01,1.4005449734530460e-02,9.6344764387700668e+00,1.1827558004342605e-03,};
  ++i; //7   7.000e+00
  reresN16[i] = a_t{5.8853240025546420e-04,-9.3806761448936786e+00,9.3624186779720214e-03,-1.3154518041606473e+00,-1.2552257884299201e-02,1.6883805132636445e+00,-6.8539671388407811e+01,1.5209225807012073e+04,8.5048885023285613e-09,1.9783098100395591e+03,-1.5500215371033335e+01,1.1226593152107620e+00,7.3880891121265224e-02,4.0678545276246141e-02,1.4920090496570182e+00,1.7601898981938694e-03,};
  imresN16[i] = a_t{-3.3728363949529034e-04,2.2198246111197474e+01,6.4100262351886317e-03,3.4042529806727062e-01,3.6370889546205926e-01,3.1082057434180879e+00,4.2727784350280636e+01,-7.2523044805689824e+03,-1.3463966616414651e+08,-1.6733676303338843e+03,-2.8431820584590429e+01,-1.6744073145752145e+00,4.3466032280297238e-02,-1.3232254779175149e-02,7.4301566150422431e+00,1.3613093380018119e-03,};
  ++i; //8   8.000e+00
  reresN16[i] = a_t{-9.6718997810389825e-04,1.1151744009043766e+01,5.0806116399390155e-03,2.0118218290607925e-01,1.0509227730047923e+00,-1.4787092413771274e+01,4.3354245909937623e+02,1.5200930608871846e+04,-3.6068825022539437e-09,1.8309211106986577e+03,6.8898315905698965e+01,-2.8259704067974569e+00,2.1397661073781071e-01,1.7998794059650575e-02,3.1229463127700372e+00,3.8041831248133355e-03,};
  imresN16[i] = a_t{-8.2740821100739023e-04,-1.6411259891729366e-01,-2.5318291685430927e-02,2.3966048721356814e-01,-4.8133995302664601e-01,2.4863806820263143e-01,2.5698980300658104e+02,2.1959643330229673e+05,-6.2798159000979691e+09,-2.5592194317277754e+04,-1.6016177962218310e+02,-7.0175769289414118e+00,-7.4750842622204283e-01,-1.0405246098172488e-01,9.1536581756506086e-01,-2.1479752930232566e-03,};
  ++i; //9   9.000e+00
  reresN16[i] = a_t{-8.4795840596439426e-04,-2.0558653030379705e+00,-6.3015731861599519e-02,4.7909065938548479e-01,-3.2612755135268041e+00,3.2129726859521206e+01,1.8242190095876677e+02,-3.1279927505772938e+06,2.0307278554816495e-05,-1.9206849546267229e+05,1.0313508888898828e+03,-3.1296165833517691e+01,2.2085782721277067e+00,-2.2399168421415783e-01,9.4313790204425718e-01,-7.6157333893736286e-04,};
  imresN16[i] = a_t{2.4435333244852532e-03,-4.2239870420239409e+00,1.4916329627665193e-02,-2.3191344542392103e-01,-2.5212576303492895e+00,-6.1681834193193993e+01,-3.5737026834089879e+03,-9.9464621568559564e+05,-3.3478887500572778e+11,-2.1771155579347737e+05,-2.8385472466083957e+02,-7.3925557304838820e+00,-9.5646544084700669e-01,-1.8368187180451956e-01,-9.2865999476476913e-01,-9.3147556078417449e-03,};
  ++i; //10   1.000e+01
  reresN16[i] = a_t{5.6665496333854664e-03,-1.1396571449251707e+00,1.1276098133940345e-01,-3.9197139665327130e-01,-2.6137610326201903e+00,2.0186355452030639e+02,-2.5820346728141052e+04,3.4834091902578406e+07,-1.1554052326231523e-05,-3.6898513824160448e+06,5.9946876474935216e+03,-1.1581849933941487e+02,7.2871627616054351e+00,-8.2561541836632280e-01,1.8199456122050553e-02,-2.0176388163116819e-02,};
  imresN16[i] = a_t{-3.7801114719676209e-04,1.4569731875261576e+00,1.3776845183365691e-01,1.3629607897759746e+00,1.6133853676156892e+01,3.0477560035284563e+02,1.2063955436337446e+04,-4.2583748810418658e+07,-2.0081052684443582e+13,-2.0519534865996765e+05,4.2882717107417893e+03,9.9878996133077734e+01,4.8727276372307102e+00,2.9663388967962223e-01,-4.4181143810135504e-01,-8.0559027210203946e-03,};
  using kyosu::kind_1;
  using eve::spherical;
  auto h =  eve::half(eve::as<T>());
  for(int j=0; j <= 15; ++j)
  {
    auto c = kyosu::complex(re[j], im[j]);
    auto fac = kyosu::sqrt(eve::pio_2(eve::as(kyosu::real(c)))*kyosu::rec(c));
    for(int i=0; i < N; ++i)
    {
      // std::cout<< "j " << j  << " c[" << i << "] = " << c << std::endl;
      auto res = kyosu::complex(reresN16[i][j], imresN16[i][j]);
      if( ((i < 7) || (sizeof(T) == 8 ) || kyosu::is_not_real(c)) ) // The limitation of these tests with float is due to some overflow pbs when z is real
      {
        TTS_RELATIVE_EQUAL(kyosu::bessel_h[kind_1](i, c), res, tts::prec<T>());
        TTS_RELATIVE_EQUAL(kyosu::bessel_h[kind_1](-i, c), eve::sign_alternate(i)*res, tts::prec<T>());
        TTS_RELATIVE_EQUAL(kyosu::bessel_h[kind_1][spherical](i, c), kyosu::bessel_h[kind_1](i+h, c)*fac, tts::prec<T>());
        TTS_RELATIVE_EQUAL(kyosu::bessel_h[kind_1][spherical](-i, c), kyosu::bessel_h[kind_1](-i+h, c)*fac, tts::prec<T>());
      }
    }
  }
};


TTS_CASE_WITH ( "Check kyosu::cyl_bessel_h2n integral negative order"
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
  int i=0;
  reresN16[i] = a_t{2.1988399563106543e+02,2.4475379403286627e-04,-1.0949275587116509e+02,7.0926149688609519e-04,-1.2134577316119763e+01,-1.8269104646258683e-02,2.9718238932026955e+00,-1.3938490578596488e-01,9.7762624653829611e-01,1.6477670588097639e+00,5.7801144894856459e-02,-3.7706880470084005e+00,-1.7305844653144060e-03,-4.5587245103257374e+01,-7.0927339073308311e-04,4.7382830132773599e+01,};
  imresN16[i] = a_t{-7.4457014389297478e+02,4.2222247912422257e-05,-5.4163840901549179e+01,-2.0501433281152636e-03,1.6547181744548173e+01,-9.6142660041630447e-03,2.9905093588667149e+00,2.1994852133809409e-01,8.0727357780451992e-01,-9.4200443654515464e-01,-2.8437721740099727e-02,-7.4893412346961954e+00,-6.1357907332358014e-03,1.5088797239958149e+01,7.1380035703526274e-05,2.9602274269542443e+02,};
  ++i; //1   1.000e+00
  reresN16[i] = a_t{7.0523479832421106e+02,-5.1966173198415601e-05,5.5399150676183154e+01,2.1622410773788087e-03,-1.4293275067061980e+01,1.1965620368655849e-02,-2.7447717452290470e+00,-2.8456976487589863e-01,1.4831881627310406e-01,1.2439613389157882e+00,3.8795396026071904e-02,6.3858212297139350e+00,6.5083649941374815e-03,-1.6483172127684213e+01,-1.0216956600761109e-04,-2.8058303011863615e+02,};
  imresN16[i] = a_t{2.3270002447946945e+02,2.5546359367357779e-04,-1.0077752102748380e+02,8.4599647402696764e-04,-1.2068202214419697e+01,-1.9783141801227117e-02,1.7182840689151211e+00,-2.2214378917556191e-01,2.2931051383885306e+00,1.0227225644184332e+00,6.2808764715385101e-02,-4.0730198843794367e+00,-2.2101999076038947e-03,-4.1893920025793783e+01,-7.4389305617771583e-04,5.5828974027738006e+01,};
  ++i; //2   2.000e+00
  reresN16[i] = a_t{-2.6062987977228732e+02,-2.8891573129062945e-04,7.7439570407309688e+01,-1.3420171051577766e-03,1.1007420355218741e+01,2.4447423067843786e-02,-4.9358318011931945e-01,7.1864644910651909e-01,1.1165861949063943e-02,6.1891684452445705e-01,-7.5120551625320317e-02,4.1916787378180382e+00,3.9966314088709671e-03,3.1788783936210265e+01,8.5162344548977812e-04,-7.5479330354308104e+01,};
  imresN16[i] = a_t{5.9525559255548148e+02,-8.6090427595642526e-05,5.6532027894327456e+01,2.5100761697729114e-03,-8.6960711104540440e+00,2.1298337302884680e-02,-1.6087700058335248e+00,-5.5738343376166943e-01,1.4480094011452358e+01,7.2076566204779957e-01,8.1954613487065897e-02,3.5689196342012823e+00,7.6337868490482077e-03,-1.8982358875840266e+01,-2.1219909877358444e-04,-2.3672784854038261e+02,};
  ++i; //3   3.000e+00
  reresN16[i] = a_t{-4.3839222678606467e+02,1.6209418671645398e-04,-5.2495198887278107e+01,-3.0993496031858090e-03,3.0927653448394108e+00,-4.7227180313352872e-02,6.9133718589254267e-01,1.2153451239071451e+00,5.5934304776041695e-04,1.4354036742287248e+00,-2.0809244376898994e-01,-7.5796543747351741e-01,-9.3425063496537404e-03,1.9108484965249893e+01,4.6522735070773610e-04,1.7276675144293495e+02,};
  imresN16[i] = a_t{-2.7916828823734778e+02,-3.4818845981351228e-04,4.7263572093155709e+01,-2.5193596146696694e-03,8.0611004355900597e+00,3.1222769924867302e-02,3.9827129895859570e-01,3.4690397292141371e+00,1.9077481501430970e+02,-8.1902492937174798e-01,-6.9147377384545392e-02,2.9863995344143857e+00,8.4032908669999604e-03,1.8458130633375493e+01,1.0393486813124739e-03,-9.2790020841511421e+01,};
  ++i; //4   4.000e+00
  reresN16[i] = a_t{2.6650234123828983e+02,4.3358670846841432e-04,-2.0226599321273508e+01,5.1753968106418189e-03,-4.3973111290807525e+00,-2.8692219739690231e-02,5.3512447774165406e-01,-2.1176462546228901e+01,2.0999005910771326e-05,1.2302193900464740e+00,-1.1250998506976712e-01,-1.2892065616770967e+00,-1.8656904697100511e-02,-6.7021364664089909e+00,-1.2934974731900481e-03,9.5115597709332960e+01,};
  imresN16[i] = a_t{-2.7035192818715944e+02,3.2009780121229029e-04,-4.1225260212972884e+01,-3.7759326820860960e-03,-7.4395173141316620e-02,-1.1829957593269830e-01,-4.8808926553638732e-01,-3.3367226164442110e-01,3.8010162062747440e+03,-7.4840514728492158e+00,-5.4674598860321133e-01,2.6898898165850565e-01,-1.0285834575150924e-02,1.5118028994589356e+01,1.0088319702565229e-03,1.0322900305302829e+02,};
  ++i; //5   5.000e+00
  reresN16[i] = a_t{1.2780234001788479e+02,-6.4501134377925205e-04,2.6177241625044850e+01,3.6256591642247803e-03,7.5287856711982182e-01,3.1294268575749501e-01,-3.0941248351648563e+00,5.9503670601168622e+01,6.3044940002188614e-07,-2.6450732005439693e+01,1.2556686441612321e+00,-4.8167077014139514e-01,4.1279600754146510e-03,-8.9417453302412504e+00,-2.1539356815015996e-03,-4.4707400631811439e+01,};
  imresN16[i] = a_t{2.1843174698297722e+02,5.2637056627900434e-04,-3.1881007776727484e+00,1.1136832630761524e-02,-1.6700056224030755e+00,5.1693947369110642e-02,-1.2172360028254385e+00,-1.4859313380901500e+02,1.0116965735231226e+05,-3.4038058522211003e+01,-1.2713323332279289e+00,-5.4022433603405806e-01,-4.1675826898665704e-02,-7.9901645145370355e-03,-1.4974807308038073e-03,7.9216284061965538e+01,};
  ++i; //6   6.000e+00
  reresN16[i] = a_t{-1.5030062837380635e+02,-5.3585891236927969e-04,-3.4445287794317085e+00,-2.4269117718509849e-02,5.4912285608666045e-01,-5.5821846365150518e-01,1.3248857200135578e+00,1.0969666829647417e+03,1.5767594796476312e-08,-3.0367417202829989e+02,6.9010460685675215e+00,-5.9201488577650951e-01,8.8746707051043608e-02,-1.9232649224067928e+00,1.1676617075128300e-03,-5.2764794822912776e+01,};
  imresN16[i] = a_t{3.3615368392083155e+01,-1.3087500263175051e-03,1.2982757436689853e+01,-1.1927303704998785e-03,5.9731642596306966e-01,8.0929545175629813e-01,1.4935707832595298e+01,1.0256864664407362e+03,3.3685208955374686e+06,-3.0452581111007380e+01,1.0548335384362815e+00,-1.6839690581673980e-01,-3.3713862060618327e-02,-3.7898433896068466e+00,-4.5043479485012746e-03,-7.9006914348141208e+00,};
  ++i; //7   7.000e+00
  reresN16[i] = a_t{1.1042217808307697e+01,2.6335292196836800e-03,-4.7759043409387463e+00,2.4850445904469057e-02,-2.0467619572083159e-01,-1.7081320197733632e+00,6.8539133756106921e+01,-1.5209225804669784e+04,8.5048885023285613e-09,-1.9783097868304035e+03,1.5502725387233061e+01,-1.0842043870243303e+00,1.8797055149071196e-01,9.5261034448667103e-01,9.0404562947955479e-03,-7.3202332118779596e+00,};
  imresN16[i] = a_t{-8.4965323982120196e+01,-1.3824552617486017e-04,-3.8337108981328054e+00,-5.1158007911221118e-02,-3.1998942798127467e-01,-3.1216814023846520e+00,-4.2726833223774065e+01,7.2523044757584657e+03,1.3463966616414651e+08,1.6733676040259661e+03,2.8432973817947914e+01,1.6555837534075162e+00,1.5903960158804847e-01,-1.4479166108826389e+00,-1.3320863141409939e-03,-2.7411449506570069e+01,};
  ++i; //8   8.000e+00
  reresN16[i] = a_t{3.8068585292321998e+01,-1.6883603034587237e-03,2.2481347464713464e+00,9.4296375870191587e-02,-1.0325269512202457e+00,1.4786612728230278e+01,-4.3354254217101555e+02,-1.5200930609229943e+04,-3.6068825022539437e-09,-1.8309211076027646e+03,-6.8897911480235834e+01,2.8349180185067393e+00,-1.1796559632218066e-01,6.3839442455958673e-01,1.0946898238442063e-02,1.0428721315961420e+01,};
  imresN16[i] = a_t{2.1414478984861770e+01,5.1141786952836072e-03,-1.0613245197418786e+00,1.1559142412008958e-01,4.2117781851833203e-01,-2.4354165195139638e-01,-2.5698993307729251e+02,-2.1959643330232380e+05,6.2798159000979691e+09,2.5592194317105586e+04,1.6016157977211319e+02,7.0223398847811316e+00,7.1425543146324133e-01,1.4603284668029054e-01,1.6512826010224715e-02,-8.9084967465938387e+00,};
  ++i; //9   9.000e+00
  reresN16[i] = a_t{-1.6332289724113984e+01,-9.0264125654248746e-03,4.6930271908627953e-02,-4.2426271531879883e-01,3.2723821927537791e+00,-3.2128832627233578e+01,-1.8242188159938584e+02,3.1279927505773003e+06,2.0307278554816495e-05,1.9206849546285294e+05,-1.0313508741492124e+03,3.1296478532021162e+01,-2.2013809845726184e+00,3.2773977588975173e-01,-2.3210316273706559e-02,5.6095280286780662e+00,};
  imresN16[i] = a_t{1.2332826041697865e+01,-7.9219013660750074e-03,9.1251805241212591e-01,9.7282558270663344e-02,2.5327809847166654e+00,6.1681437164741979e+01,3.5737026819057019e+03,9.9464621568561555e+05,3.3478887500572778e+11,2.1771155579364079e+05,2.8385466078784765e+02,7.3946727972206592e+00,9.2949109876170588e-01,3.7812054377804272e-01,4.1151209934169743e-02,2.3035626482812028e+00,};
  ++i; //10   1.000e+01
  reresN16[i] = a_t{-1.8645741110323140e+00,2.6567871884739094e-02,-3.8800108951911211e-01,3.5071219842047568e-01,2.6101913209137191e+00,-2.0186369032412077e+02,2.5820346727252228e+04,-3.4834091902578406e+07,-1.1554052326231523e-05,3.6898513824160453e+06,-5.9946876527183713e+03,1.1581821230894789e+02,-7.2916563501828930e+00,7.9284922683196646e-01,-1.2338007674618542e-01,2.9327654263534830e-01,};
  imresN16[i] = a_t{-8.6519845132097135e+00,-1.1975560538677621e-02,-2.8855317300295752e-01,-1.3581317117217391e+00,-1.6132937916968761e+01,-3.0477570066898443e+02,-1.2063955434322903e+04,4.2583748810418658e+07,2.0081052684443582e+13,2.0519534865998483e+05,-4.2882717175462076e+03,-9.9878706814944479e+01,-4.8780128534985954e+00,-2.3815086482581632e-01,-1.8188909505369088e-03,2.4489087963792731e+00,};
  auto pr2 = tts::prec<T>()*2;
  using kyosu::kind_2;
  using eve::spherical;
  auto h =  eve::half(eve::as<T>());
  for(int j=0; j <= 15; ++j)
  {
    auto c = kyosu::complex(re[j], im[j]);
    auto fac = kyosu::sqrt(eve::pio_2(eve::as(kyosu::real(c)))*kyosu::rec(c));
    for(int i=0; i < N; ++i)
    {
      // std::cout<< "j " << j  << " c[" << i << "] = " << c << std::endl;
      auto res = kyosu::complex(reresN16[i][j], imresN16[i][j]);
      if( ((i < 7) || (sizeof(T) == 8 ) || kyosu::is_not_real(c)) ) // The limitation of these tests with float is due to some overflow pbs when z is real
      {
        TTS_RELATIVE_EQUAL(kyosu::bessel_h[kind_2](i, c), res, pr2);
        TTS_RELATIVE_EQUAL(kyosu::bessel_h[kind_2](-i, c), eve::sign_alternate(i)*res, pr2);
        TTS_RELATIVE_EQUAL(kyosu::bessel_h[kind_2][spherical](i, c), kyosu::bessel_h[kind_2](i+h, c)*fac, tts::prec<T>());
        TTS_RELATIVE_EQUAL(kyosu::bessel_h[kind_2][spherical](-i, c), kyosu::bessel_h[kind_2](-i+h, c)*fac, tts::prec<T>());
      }
    }
  }
};
