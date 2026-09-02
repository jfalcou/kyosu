<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.16.1" doxygen_gitid="669aeeefca743c148e2d935b3d3c69535c7491e6">
  <compound kind="struct">
    <name>kyosu::as_cayley_dickson_like</name>
    <filename>structkyosu_1_1as__cayley__dickson__like.html</filename>
    <templarg>typename... Ts</templarg>
  </compound>
  <compound kind="struct">
    <name>kyosu::as_real</name>
    <filename>structkyosu_1_1as__real.html</filename>
    <templarg>typename T</templarg>
    <base>eve::as&lt; typename T &gt;</base>
  </compound>
  <compound kind="struct">
    <name>kyosu::cayley_dickson</name>
    <filename>structkyosu_1_1cayley__dickson.html</filename>
    <templarg>eve::floating_scalar_value Type</templarg>
    <templarg>unsigned int N</templarg>
    <member kind="function">
      <type>constexpr</type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a855e307f5821528acf3b6d850194192f</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ab8e1d853182bea96fea1595877d240f4</anchor>
      <arglist>(cayley_dickson&lt; Type, M &gt; const &amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>aa793ea3b391b5e590eb6022b75d3be84</anchor>
      <arglist>(cayley_dickson&lt; Type, M &gt; const &amp;a, cayley_dickson&lt; Type, M &gt; const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ae438e3f20e692a6de77419c39e890ba8</anchor>
      <arglist>(eve::sized_product_type&lt; N &gt; auto const &amp;vs)</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>af70b4a76c4af0caf051ff4eae883d552</anchor>
      <arglist>(T v) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a5899e8aaa41998c60dc9ce3e2bb82c6f</anchor>
      <arglist>(T0 v0, Ts... vs) noexcept</arglist>
    </member>
    <member kind="function">
      <type>KYOSU_FORCEINLINE auto &amp;</type>
      <name>operator++</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a5212a7e8767444e76d7c054347716619</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>KYOSU_FORCEINLINE auto</type>
      <name>operator++</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a2375cc6d41964418f819e04a5aee14cf</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>KYOSU_FORCEINLINE auto &amp;</type>
      <name>operator--</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a348e923f3719df8b571cbbd1719177f2</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>KYOSU_FORCEINLINE auto</type>
      <name>operator--</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>abb849412f206b0f7ba1e48f4de76ca39</anchor>
      <arglist>(int) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr cayley_dickson &amp;</type>
      <name>operator=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>aba6f0b33ec930c1b7d025aa4ae76fd14</anchor>
      <arglist>(T const &amp;a) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>aa0be302941e24075875f2ff22e1bc866</anchor>
      <arglist>(Tuple const &amp;) -&gt; cayley_dickson&lt; kumi::element_t&lt; 0, Tuple &gt;, kumi::size_v&lt; Tuple &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>aa72548959abb0145c1eef8e8cf2928b4</anchor>
      <arglist>(T0, Ts...) -&gt; cayley_dickson&lt; T0, 1+sizeof...(Ts)&gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator+=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ae63ee48e9508d712beb22e125d596276</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator+=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a127b8375b7ef7d42f5044ebc5770da1a</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator-=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ab15d8bbe6f7602cf1f7b7c0ac4744bb2</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator-=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a715044a74f36e890e0fa86f68e60c2d1</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator*=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a5f0dd77597800b916c4cebc5e0634cde</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr Self &amp;</type>
      <name>operator*=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a7fb7201475d4bac42ec931f542a0c24f</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator/=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a30f4c360cf0019deefa476acf571c387</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr Self &amp;</type>
      <name>operator/=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a29ff75dcd5392b350f8775c8d0fc331a</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a1d50add5f2f5370f64b20919751ccdcf</anchor>
      <arglist>(std::basic_ostream&lt; C, Ct &gt; &amp;os, CD const &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::complex_t&lt; double &gt;</type>
      <name>operator&quot;&quot;_i</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a1a8dfb5ebec66f24fce04469de86120b</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::complex_t&lt; float &gt;</type>
      <name>operator&quot;&quot;_if</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a9f6fc5aa16208b342059eabb36dbf8a5</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; double &gt;</type>
      <name>operator&quot;&quot;_j</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>abc2491a56ef3c5cb615ddf96eb265510</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; float &gt;</type>
      <name>operator&quot;&quot;_jf</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a032f8a8437b972416acb47c33b144556</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; double &gt;</type>
      <name>operator&quot;&quot;_k</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ab81a5e9b87e5ca0c50cf8e6eb56217c5</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; float &gt;</type>
      <name>operator&quot;&quot;_kf</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a810e99156f3dfbd5d36030c0b585a9f7</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator+</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a18cec006320794126c85b238a68fc91c</anchor>
      <arglist>(Z const &amp;z) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator-</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a3032325260646fe3f0832b076a2b146a</anchor>
      <arglist>(Z const &amp;z) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator+</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a3ee8e2fe476ebb1011c476e093227822</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator-</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a36ef300ed76ad52be7293d1a1fac8331</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator*</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a2fb59110f4a618933f413b3c409ae8e6</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator/</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>abccb6441a9eaf55aec6a7aea780bd145</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator==</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a561363de989d2101775d8b85655ea08e</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator==</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a561363de989d2101775d8b85655ea08e</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator!=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ac345e6a953c0ec69ee85d43be131c6c6</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator!=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ac345e6a953c0ec69ee85d43be131c6c6</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>aa0be302941e24075875f2ff22e1bc866</anchor>
      <arglist>(Tuple const &amp;) -&gt; cayley_dickson&lt; kumi::element_t&lt; 0, Tuple &gt;, kumi::size_v&lt; Tuple &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>aa72548959abb0145c1eef8e8cf2928b4</anchor>
      <arglist>(T0, Ts...) -&gt; cayley_dickson&lt; T0, 1+sizeof...(Ts)&gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator+=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ae63ee48e9508d712beb22e125d596276</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator+=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a127b8375b7ef7d42f5044ebc5770da1a</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator-=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ab15d8bbe6f7602cf1f7b7c0ac4744bb2</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator-=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a715044a74f36e890e0fa86f68e60c2d1</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator*=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a5f0dd77597800b916c4cebc5e0634cde</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr Self &amp;</type>
      <name>operator*=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a7fb7201475d4bac42ec931f542a0c24f</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator/=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a30f4c360cf0019deefa476acf571c387</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr Self &amp;</type>
      <name>operator/=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a29ff75dcd5392b350f8775c8d0fc331a</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a1d50add5f2f5370f64b20919751ccdcf</anchor>
      <arglist>(std::basic_ostream&lt; C, Ct &gt; &amp;os, CD const &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::complex_t&lt; double &gt;</type>
      <name>operator&quot;&quot;_i</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a1a8dfb5ebec66f24fce04469de86120b</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::complex_t&lt; float &gt;</type>
      <name>operator&quot;&quot;_if</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a9f6fc5aa16208b342059eabb36dbf8a5</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; double &gt;</type>
      <name>operator&quot;&quot;_j</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>abc2491a56ef3c5cb615ddf96eb265510</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; float &gt;</type>
      <name>operator&quot;&quot;_jf</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a032f8a8437b972416acb47c33b144556</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; double &gt;</type>
      <name>operator&quot;&quot;_k</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ab81a5e9b87e5ca0c50cf8e6eb56217c5</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; float &gt;</type>
      <name>operator&quot;&quot;_kf</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a810e99156f3dfbd5d36030c0b585a9f7</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator+</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a18cec006320794126c85b238a68fc91c</anchor>
      <arglist>(Z const &amp;z) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator-</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a3032325260646fe3f0832b076a2b146a</anchor>
      <arglist>(Z const &amp;z) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator+</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a3ee8e2fe476ebb1011c476e093227822</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator-</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a36ef300ed76ad52be7293d1a1fac8331</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator*</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a2fb59110f4a618933f413b3c409ae8e6</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator/</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>abccb6441a9eaf55aec6a7aea780bd145</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator==</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a561363de989d2101775d8b85655ea08e</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator==</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a561363de989d2101775d8b85655ea08e</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator!=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ac345e6a953c0ec69ee85d43be131c6c6</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator!=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ac345e6a953c0ec69ee85d43be131c6c6</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>kyosu::complexify</name>
    <filename>structkyosu_1_1complexify.html</filename>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>kyosu::complexify_if</name>
    <filename>structkyosu_1_1complexify__if.html</filename>
    <templarg>typename O</templarg>
    <templarg>typename T</templarg>
  </compound>
  <compound kind="struct">
    <name>kyosu::promoting_elementwise_callable</name>
    <filename>structkyosu_1_1promoting__elementwise__callable.html</filename>
    <templarg>template&lt; typename &gt; class Func</templarg>
    <templarg>typename OptionsValues</templarg>
    <templarg>typename... Options</templarg>
  </compound>
  <compound kind="struct">
    <name>kyosu::promoting_strict_elementwise_callable</name>
    <filename>structkyosu_1_1promoting__strict__elementwise__callable.html</filename>
    <templarg>template&lt; typename &gt; class Func</templarg>
    <templarg>typename OptionsValues</templarg>
    <templarg>typename... Options</templarg>
  </compound>
  <compound kind="concept">
    <name>kyosu::concepts::cayley_dickson</name>
    <filename>conceptkyosu_1_1concepts_1_1cayley__dickson.html</filename>
  </compound>
  <compound kind="concept">
    <name>kyosu::concepts::complex</name>
    <filename>conceptkyosu_1_1concepts_1_1complex.html</filename>
  </compound>
  <compound kind="concept">
    <name>kyosu::concepts::octonion</name>
    <filename>conceptkyosu_1_1concepts_1_1octonion.html</filename>
  </compound>
  <compound kind="concept">
    <name>kyosu::concepts::quaternion</name>
    <filename>conceptkyosu_1_1concepts_1_1quaternion.html</filename>
  </compound>
  <compound kind="concept">
    <name>kyosu::concepts::real</name>
    <filename>conceptkyosu_1_1concepts_1_1real.html</filename>
  </compound>
  <compound kind="namespace">
    <name>kyosu</name>
    <filename>namespacekyosu.html</filename>
    <class kind="struct">kyosu::as_cayley_dickson_like</class>
    <class kind="struct">kyosu::as_real</class>
    <class kind="struct">kyosu::cayley_dickson</class>
    <class kind="struct">kyosu::complexify</class>
    <class kind="struct">kyosu::complexify_if</class>
    <class kind="struct">kyosu::promoting_elementwise_callable</class>
    <class kind="struct">kyosu::promoting_strict_elementwise_callable</class>
    <member kind="typedef">
      <type>typename as_cayley_dickson_n&lt; Dim, Ts... &gt;::type</type>
      <name>as_cayley_dickson_n_t</name>
      <anchorfile>group__kyosu__traits.html</anchorfile>
      <anchor>ga8f185ca9780dc6cec632805d9cd71463</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename as_cayley_dickson&lt; Ts... &gt;::type</type>
      <name>as_cayley_dickson_t</name>
      <anchorfile>group__kyosu__traits.html</anchorfile>
      <anchor>ga15c8de6cae864e2052c544b275ee2fb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename as_real_type&lt; T &gt;::type</type>
      <name>as_real_type_t</name>
      <anchorfile>group__kyosu__traits.html</anchorfile>
      <anchor>ga6637bd6d8f6205889825bef54cef64e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>as_cayley_dickson_n_t&lt; 2, T &gt;</type>
      <name>complex_t</name>
      <anchorfile>group__types.html</anchorfile>
      <anchor>ga10a5d4f4bdbbbc385c544fb41c7d628e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>as_cayley_dickson_n_t&lt; 8, T &gt;</type>
      <name>octonion_t</name>
      <anchorfile>group__types.html</anchorfile>
      <anchor>ga403b1334a805ef696b3ab5640d550cff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>as_cayley_dickson_n_t&lt; 4, T &gt;</type>
      <name>quaternion_t</name>
      <anchorfile>group__types.html</anchorfile>
      <anchor>ga43659263f005aec8e7e223b889004a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>abs</name>
      <anchorfile>group__abs.html</anchorfile>
      <anchor>gac70344c81b5cf55a5257cf54c6e6cb18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acos</name>
      <anchorfile>group__acos.html</anchorfile>
      <anchor>gaa6527f2975e878d560e025dba9def6cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acosh</name>
      <anchorfile>group__acosh.html</anchorfile>
      <anchor>ga010d55184f68d5a6276939926b22c689</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acot</name>
      <anchorfile>group__acot.html</anchorfile>
      <anchor>ga7d65b07b38591673afce19e11ad7738c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acoth</name>
      <anchorfile>group__acoth.html</anchorfile>
      <anchor>gaed04ae9c136243a0b242183b8bf7b0a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acsc</name>
      <anchorfile>group__acsc.html</anchorfile>
      <anchor>gabe9720e52e71443cb2d0cc9c62fad1a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>acsch</name>
      <anchorfile>group__acsch.html</anchorfile>
      <anchor>gaceca829cfb9fe916d2a1c769b10018ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>add</name>
      <anchorfile>group__add.html</anchorfile>
      <anchor>gadcd7dc3600f2f5da8fb31efc6b02d244</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>agd</name>
      <anchorfile>group__agd.html</anchorfile>
      <anchor>ga302a7795299874023f6c615a9908e2ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>align</name>
      <anchorfile>group__align.html</anchorfile>
      <anchor>ga75d48d720e22794a606131a0b0d7ce7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>am</name>
      <anchorfile>group__am.html</anchorfile>
      <anchor>gaabbe680517187a5e2b72489ec5921211</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>arg</name>
      <anchorfile>group__arg.html</anchorfile>
      <anchor>gae6b016425d0a624d4391512f4afb64fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>asec</name>
      <anchorfile>group__asec.html</anchorfile>
      <anchor>gaa0e50a4af9f77cf0b053e27ede376ca5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>asech</name>
      <anchorfile>group__asech.html</anchorfile>
      <anchor>ga73d1420e184c7752eb998291672c038d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>asin</name>
      <anchorfile>group__asin.html</anchorfile>
      <anchor>ga1b0ab1f5f9386bcfe84bc3356ad103e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>asinh</name>
      <anchorfile>group__asinh.html</anchorfile>
      <anchor>ga472ea5acadc02ca6a04f9b8c29b60a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>associator</name>
      <anchorfile>group__associator.html</anchorfile>
      <anchor>gac1477076e48284b3ea6b0304e24188c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>atan</name>
      <anchorfile>group__atan.html</anchorfile>
      <anchor>ga4c75b3c9fa3f13d411c888143c0660a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>atanh</name>
      <anchorfile>group__atanh.html</anchorfile>
      <anchor>gad32eb35a5b7923acacd701fd74ae6834</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>average</name>
      <anchorfile>group__average.html</anchorfile>
      <anchor>ga215f5e846e2b272e4e669c36a4d2afc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>beta</name>
      <anchorfile>group__beta.html</anchorfile>
      <anchor>gace5ed207bcf440be909fff9d63c23409</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cbrt</name>
      <anchorfile>group__cbrt.html</anchorfile>
      <anchor>ga81b0d6fb1ff90f938f3593cc201fcb1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ceil</name>
      <anchorfile>group__ceil.html</anchorfile>
      <anchor>ga8c89c82b3d1c4471c8c52c832c78d792</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>chi</name>
      <anchorfile>group__chi.html</anchorfile>
      <anchor>ga05dfb6e5aebe98bf4ea725063cbce033</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cinf</name>
      <anchorfile>group__cinf.html</anchorfile>
      <anchor>ga0c9ef916832ff4cbfbf575bc77f4fb4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>commutator</name>
      <anchorfile>group__commutator.html</anchorfile>
      <anchor>gacdb90f1b3fb7481bdb308a74224e8b38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>complex</name>
      <anchorfile>group__to__complex.html</anchorfile>
      <anchor>gad34d6e0109b4b00e61a647cac6197786</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>conj</name>
      <anchorfile>group__conj.html</anchorfile>
      <anchor>ga7e324b44c677cab7cf646a1cb87e9405</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>convert</name>
      <anchorfile>group__convert.html</anchorfile>
      <anchor>ga081e21d8e2b4876702601c74562eeabb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cos</name>
      <anchorfile>group__cos.html</anchorfile>
      <anchor>gaff78cbf53496580d8216966a5f96a5f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cosh</name>
      <anchorfile>group__cosh.html</anchorfile>
      <anchor>gaacd4903b331413b4b0c8da2a1521093a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>cot</name>
      <anchorfile>group__cot.html</anchorfile>
      <anchor>gafb2eb2745644a8b663b71b6ad8d5f6b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>coth</name>
      <anchorfile>group__coth.html</anchorfile>
      <anchor>gaf77965146c145973900d9edec9742caa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>csc</name>
      <anchorfile>group__csc.html</anchorfile>
      <anchor>ga627c035548638b22d13890b8b03e5ca9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>csch</name>
      <anchorfile>group__csch.html</anchorfile>
      <anchor>gaac742f86aaadd71a3fcca9b9e7a23d52</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>dec</name>
      <anchorfile>group__dec.html</anchorfile>
      <anchor>ga8b430b0a36d45bf0bec840d6e4cf2063</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>deta</name>
      <anchorfile>group__deta.html</anchorfile>
      <anchor>ga39f6e6a20461bbbd304313e231746d47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>digamma</name>
      <anchorfile>group__digamma.html</anchorfile>
      <anchor>gab9af9dd4c0b41ba6ce2171fd8192e7de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr unsigned int</type>
      <name>dimension_v</name>
      <anchorfile>group__kyosu__traits.html</anchorfile>
      <anchor>gab76e6a5196c280967c692c2139d8301e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>dist</name>
      <anchorfile>group__dist.html</anchorfile>
      <anchor>ga05d99d8cf767a2ec1d7806916bc22f00</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>div</name>
      <anchorfile>group__div.html</anchorfile>
      <anchor>ga435faee7fb66f5162ffb64397a878db9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>dot</name>
      <anchorfile>group__dot.html</anchorfile>
      <anchor>gab77f480117e453861b459a5dcfa0fb08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_fe</name>
      <anchorfile>group__ellint__fe.html</anchorfile>
      <anchor>ga858bbc0cd82011e1911907d0d6cdf2cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rc</name>
      <anchorfile>group__ellint__rc.html</anchorfile>
      <anchor>ga59830d1553989ba7ee7722d0b2731039</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rd</name>
      <anchorfile>group__ellint__rd.html</anchorfile>
      <anchor>ga81e0756cf62ec6b36813e4eb930992c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rf</name>
      <anchorfile>group__ellint__rf.html</anchorfile>
      <anchor>gac8903dbfbdb109a6d1c70209d3e20386</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rg</name>
      <anchorfile>group__ellint__rg.html</anchorfile>
      <anchor>gabe721a515ca959098143128eeb2c62c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ellint_rj</name>
      <anchorfile>group__ellint__rj.html</anchorfile>
      <anchor>gaea54d1c027a77c63a592fc8e933fc384</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>erf</name>
      <anchorfile>group__erf.html</anchorfile>
      <anchor>ga4836ce9e292b5071b85a14560ecfcba5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>erfcx</name>
      <anchorfile>group__erfcx.html</anchorfile>
      <anchor>ga39a3490b9804d064f6e763b6b2ee6545</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>erfi</name>
      <anchorfile>group__erfi.html</anchorfile>
      <anchor>ga1cfc9aee0b7545c21db6531760e294a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>eta</name>
      <anchorfile>group__eta.html</anchorfile>
      <anchor>ga5c1b5d98ef3091b5c757ab13d061fef2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp</name>
      <anchorfile>group__exp.html</anchorfile>
      <anchor>ga43bd0f5793b846caaf808a7f998734c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp10</name>
      <anchorfile>group__exp10.html</anchorfile>
      <anchor>ga37e090c4b1d41d1c37db13d21e293693</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp2</name>
      <anchorfile>group__exp2.html</anchorfile>
      <anchor>ga7646bef9d3128713a8284a545c10b1e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp_i</name>
      <anchorfile>group__exp__i.html</anchorfile>
      <anchor>gae60807f50d322f3b5a2289f14cb115bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>exp_int</name>
      <anchorfile>group__exp__int.html</anchorfile>
      <anchor>gac080f79509178fd061575a3875a29b53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>expm1</name>
      <anchorfile>group__expm1.html</anchorfile>
      <anchor>ga20b941e423fc7750665a8c15da666169</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>expmx2</name>
      <anchorfile>group__expmx2.html</anchorfile>
      <anchor>ga17336c4e1b6666dd1fb632c136b1f19d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>expx2</name>
      <anchorfile>group__expx2.html</anchorfile>
      <anchor>gae725cf6ea34c98c328ae87ef2d9271f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>faddeeva</name>
      <anchorfile>group__faddeeva.html</anchorfile>
      <anchor>ga595600555226cba8dbd29be5512575a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fam</name>
      <anchorfile>group__fam.html</anchorfile>
      <anchor>ga4a11cd36bff3274fc96bc9798f371b90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>floor</name>
      <anchorfile>group__floor.html</anchorfile>
      <anchor>ga44f8bdc4f61d63ad54b285482837ed6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fma</name>
      <anchorfile>group__fma.html</anchorfile>
      <anchor>gab0bdf8bce326915395666800b2d5b175</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fms</name>
      <anchorfile>group__fms.html</anchorfile>
      <anchor>gae2d27aa05efe337cd4d65778bbf08d7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fnan</name>
      <anchorfile>group__fnan.html</anchorfile>
      <anchor>ga0cf87abcd108df159683cdcd153e9f12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fnma</name>
      <anchorfile>group__fnma.html</anchorfile>
      <anchor>ga5b9920085c94d467ae761243033279fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fnms</name>
      <anchorfile>group__fnms.html</anchorfile>
      <anchor>ga5a79e77dd6087f110bca457d25d6caef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>frac</name>
      <anchorfile>group__frac.html</anchorfile>
      <anchor>ga7284c6f970f48919150521ccb059d373</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>from_angle_axis</name>
      <anchorfile>group__from__angle__axis.html</anchorfile>
      <anchor>ga2e2e427d078f717745ed2821f6cd06f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>from_cylindrical</name>
      <anchorfile>group__from__cylindrical.html</anchorfile>
      <anchor>ga505ff6cf7441aa432d2549a840868527</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>from_cylindrospherical</name>
      <anchorfile>group__from__cylindrospherical.html</anchorfile>
      <anchor>ga730bd78358cd0568b81be9cdcd247455</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>from_euler</name>
      <anchorfile>group__from__euler.html</anchorfile>
      <anchor>ga4e7d9b2067dc764269c1539b6e4b9271</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>from_multipolar</name>
      <anchorfile>group__from__multipolar.html</anchorfile>
      <anchor>ga2b89a4fbe7aa7dcd69bef6b423d7dac2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>from_polar</name>
      <anchorfile>group__from__polar.html</anchorfile>
      <anchor>gaf64b08ee90565c95c04b029767cba95e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>from_rotation_matrix</name>
      <anchorfile>group__from__rotation__matrix.html</anchorfile>
      <anchor>gad4d2929cc9f93e1308c26a2e0160007d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>from_semipolar</name>
      <anchorfile>group__from__semipolar.html</anchorfile>
      <anchor>gab01fdca022335c40f7f5e9a7445bedcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>from_spherical</name>
      <anchorfile>group__from__spherical.html</anchorfile>
      <anchor>gaed1e70b2f6b903ef24ce33d7937d8958</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>fsm</name>
      <anchorfile>group__fsm.html</anchorfile>
      <anchor>ga35571a35abfd2cc96d0ff2edd24d1d3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>gd</name>
      <anchorfile>group__gd.html</anchorfile>
      <anchor>gad3eacdb5f403d7a4f3a4fcc412f57b0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>gegenbauer</name>
      <anchorfile>group__gegenbauer.html</anchorfile>
      <anchor>gafacfbe5287142d18a3e08d15f9867b2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>harmmean</name>
      <anchorfile>group__harmmean.html</anchorfile>
      <anchor>ga2142b1d05423b76c401df4d5bf13003a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>horner</name>
      <anchorfile>group__horner.html</anchorfile>
      <anchor>gaeed0a0dd100ddf05147ded0ba505a5af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>hypergeometric</name>
      <anchorfile>group__hypergeometric.html</anchorfile>
      <anchor>gad56c4489b7eb531f721190906ce04ee9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>hypot</name>
      <anchorfile>group__hypot.html</anchorfile>
      <anchor>gafb18085cfb37fc835a36abdbf981101e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>i</name>
      <anchorfile>group__i.html</anchorfile>
      <anchor>gaa17b17c2202168c33700e95ccce7322d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>if_else</name>
      <anchorfile>group__if__else.html</anchorfile>
      <anchor>ga653d166a9a5d389a6d5aa1a1220b4643</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>imag</name>
      <anchorfile>group__ipart.html</anchorfile>
      <anchor>gaff94a2685c6d030458b388a4a4079efe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>inc</name>
      <anchorfile>group__inc.html</anchorfile>
      <anchor>gae5c7264a43adea8149beb99e71fb0e4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>inject</name>
      <anchorfile>group__inject.html</anchorfile>
      <anchor>ga5c2b44e7d8e27d43b129c6e0739bf6d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ipart</name>
      <anchorfile>group__ipart.html</anchorfile>
      <anchor>gac538e6a794844977cba0f5043a990c99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_cinf</name>
      <anchorfile>group__is__cinf.html</anchorfile>
      <anchor>ga193150c1f7fbf9cd161c8e9af90ebc9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_denormal</name>
      <anchorfile>group__is__denormal.html</anchorfile>
      <anchor>ga21e602517052b438e7702aaeea4427ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_equal</name>
      <anchorfile>group__is__equal.html</anchorfile>
      <anchor>ga2d35f43723bf977e2924344dfe248938</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_eqz</name>
      <anchorfile>group__is__eqz.html</anchorfile>
      <anchor>ga8cade15af2145e2b456fb57adcfbce78</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_finite</name>
      <anchorfile>group__is__finite.html</anchorfile>
      <anchor>gaeb6f14e6a7023df6a604d7f0215422ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_flint</name>
      <anchorfile>group__is__flint.html</anchorfile>
      <anchor>ga9bdf18bc3243b941872b67110a284f08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_fnan</name>
      <anchorfile>group__is__fnan.html</anchorfile>
      <anchor>gac0ac349906b1997e8d679a22d22fb592</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_imag</name>
      <anchorfile>group__is__imag.html</anchorfile>
      <anchor>ga08071c945a2f66b655b93b2a51800d03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_infinite</name>
      <anchorfile>group__is__infinite.html</anchorfile>
      <anchor>gafceb7f6cf53d556c2eeb87fe2501a3d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_nan</name>
      <anchorfile>group__is__nan.html</anchorfile>
      <anchor>gada27b99a22e5835b9e06f7aa6b0ded24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_nez</name>
      <anchorfile>group__is__nez.html</anchorfile>
      <anchor>ga97f0d66eadb5d6822404be13ea888c08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_cinf</name>
      <anchorfile>group__is__not__cinf.html</anchorfile>
      <anchor>ga0048da32d060c9d35691c34efc9f8306</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_denormal</name>
      <anchorfile>group__is__not__denormal.html</anchorfile>
      <anchor>gada3eef5a9850543278aeb28785ebbc99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_equal</name>
      <anchorfile>group__is__not__equal.html</anchorfile>
      <anchor>gaf8fe0f16bad6131ea9afa6f9c626db8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_finite</name>
      <anchorfile>group__is__not__finite.html</anchorfile>
      <anchor>ga750ee4ee1ef911781bd44700f444caa6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_flint</name>
      <anchorfile>group__is__not__flint.html</anchorfile>
      <anchor>gad08e1cfd306a50ccd92564086765d3a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_fnan</name>
      <anchorfile>group__is__not__fnan.html</anchorfile>
      <anchor>ga6101a780e32ca49e21b7efa011629fc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_infinite</name>
      <anchorfile>group__is__not__infinite.html</anchorfile>
      <anchor>ga42e5f2dc30e3fffca6bc19ff0b9e746e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_nan</name>
      <anchorfile>group__is__not__nan.html</anchorfile>
      <anchor>ga1c69997f67ae996aa06a61c3d8ad9765</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_not_real</name>
      <anchorfile>group__is__not__real.html</anchorfile>
      <anchor>ga9968f11970b837778ffe48677be73c82</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_pure</name>
      <anchorfile>group__is__pure.html</anchorfile>
      <anchor>ga5d01b83f2f41b991e96a16caa279388a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_real</name>
      <anchorfile>group__is__real.html</anchorfile>
      <anchor>ga83642115085d0145bddbd31b40a09738</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>is_unitary</name>
      <anchorfile>group__is__unitary.html</anchorfile>
      <anchor>gae2445553e9488629a8e57c9e5014b94b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>j</name>
      <anchorfile>group__j.html</anchorfile>
      <anchor>gad984a2daa62e2ee33ee4577d87cb0533</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>jacobi_elliptic</name>
      <anchorfile>group__jacobi__elliptic.html</anchorfile>
      <anchor>ga9ebb9efdd6da680620540b07dd9c34fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>jpart</name>
      <anchorfile>group__jpart.html</anchorfile>
      <anchor>ga66085e00476f789b11deaf0acb0f24ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>k</name>
      <anchorfile>group__k.html</anchorfile>
      <anchor>gabb75241dcb99709608d07d0a94af3813</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kolmmean</name>
      <anchorfile>group__kolmmean.html</anchorfile>
      <anchor>ga7445b35c94d90ede9a863a6c611fb5c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kpart</name>
      <anchorfile>group__kpart.html</anchorfile>
      <anchor>gab70ea330558b767effdc20d5d621a503</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kronecker</name>
      <anchorfile>group__kronecker.html</anchorfile>
      <anchor>ga386216ae903d30cecb1c34d69f1335a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kummer</name>
      <anchorfile>group__kummer.html</anchorfile>
      <anchor>gab4537c0d485cdbd2e836420db2f31ec7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lambda</name>
      <anchorfile>group__lambda.html</anchorfile>
      <anchor>gaf7906a8d9d35e9e55a84ddcfb03cf308</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lbeta</name>
      <anchorfile>group__lbeta.html</anchorfile>
      <anchor>gafe0c7a3f991d20592748394411b97f03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ldiv</name>
      <anchorfile>group__ldiv.html</anchorfile>
      <anchor>ga4842daf39053c0a08fa68cd1850558e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>legendre</name>
      <anchorfile>group__legendre.html</anchorfile>
      <anchor>ga1a1ccdfb045aafc00e85d17216d871f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lerp</name>
      <anchorfile>group__lerp.html</anchorfile>
      <anchor>ga82646e9c6fda08fd02c304d3b001abaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>linfnorm</name>
      <anchorfile>group__linfnorm.html</anchorfile>
      <anchor>ga2413388335ecd0df3e7d75d4e399fdd8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lipart</name>
      <anchorfile>group__lipart.html</anchorfile>
      <anchor>gadbcb03cb1614e1d7a30b6ab6d770792d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>ljpart</name>
      <anchorfile>group__ljpart.html</anchorfile>
      <anchor>gab9af5fb49098ddef5b3dba27f21628bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lkpart</name>
      <anchorfile>group__lkpart.html</anchorfile>
      <anchor>gaa2a8f6265c301b29d450fa2fa479b530</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log</name>
      <anchorfile>group__log.html</anchorfile>
      <anchor>gabc0fe7e42be704597604cc8dec55f4ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log10</name>
      <anchorfile>group__log10.html</anchorfile>
      <anchor>gae2f0c4d2d1293fe07161174e586a27a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log1p</name>
      <anchorfile>group__log1p.html</anchorfile>
      <anchor>gad73829174f8194f6843b625c3538a180</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log2</name>
      <anchorfile>group__log2.html</anchorfile>
      <anchor>ga5385bb9ae59cafa7a52c91df515c68b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log_abs</name>
      <anchorfile>group__log__abs.html</anchorfile>
      <anchor>gae2249b712f1cea3a5d99295d7c355785</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log_abs_gamma</name>
      <anchorfile>group__log__abs__gamma.html</anchorfile>
      <anchor>gad513c55f0b0115b4fe0e159d75a75d3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>log_gamma</name>
      <anchorfile>group__log__gamma.html</anchorfile>
      <anchor>ga7ba6f29f797e8ee39b4a6279b810d740</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lpart</name>
      <anchorfile>group__lpart.html</anchorfile>
      <anchor>ga8f1c7a32dcae0c94c2f79f0df7b60044</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lpnorm</name>
      <anchorfile>group__lpnorm.html</anchorfile>
      <anchor>gac6f87aa6b8c7e02f0c8bba937bfd335e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>lrising_factorial</name>
      <anchorfile>group__lrising__factorial.html</anchorfile>
      <anchor>gaf92a640dbc6c479e4b8b17c9c951eba9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>manhattan</name>
      <anchorfile>group__manhattan.html</anchorfile>
      <anchor>ga27fb46c71e5625bc16d551b2d042fa64</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxabs</name>
      <anchorfile>group__maxabs.html</anchorfile>
      <anchor>gae0175ca71d75db9471034684a10b37f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>maxmag</name>
      <anchorfile>group__maxmag.html</anchorfile>
      <anchor>ga3ca0ac25a6f4cb2c0a13290da3b09b77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>mi</name>
      <anchorfile>group__mi.html</anchorfile>
      <anchor>gada12ac0bbff1fc4e7476a12736e9a6c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minabs</name>
      <anchorfile>group__minabs.html</anchorfile>
      <anchor>gacf658d87e2919f4f6f6a830a2f94350b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minmag</name>
      <anchorfile>group__minmag.html</anchorfile>
      <anchor>gaef4a4b97d1e190629aa6e51150c38c6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>minus</name>
      <anchorfile>group__minus.html</anchorfile>
      <anchor>ga77f919fac06fc69976f93e549b57517d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>mul</name>
      <anchorfile>group__mul.html</anchorfile>
      <anchor>gafa0529f93372ed1d6f7288110d2cd663</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>muli</name>
      <anchorfile>group__muli.html</anchorfile>
      <anchor>ga5d7e27fded33a32379427adc16edec6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>mulmi</name>
      <anchorfile>group__mulmi.html</anchorfile>
      <anchor>gad0611b77939df02be326c41a6b6262bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>nearest</name>
      <anchorfile>group__nearest.html</anchorfile>
      <anchor>gafcbbc98213ecbc8a0bcb2b0a890d9542</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>negmaxabs</name>
      <anchorfile>group__negmaxabs.html</anchorfile>
      <anchor>ga242ce91e6c5d5abcbee8fc893f6c87e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>negminabs</name>
      <anchorfile>group__negminabs.html</anchorfile>
      <anchor>gac38ca831b02fb724d5865857a2cb3a2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>nthroot</name>
      <anchorfile>group__nthroot.html</anchorfile>
      <anchor>gaf2ae4980beda0e505d92440065e57f7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>omega</name>
      <anchorfile>group__omega.html</anchorfile>
      <anchor>gaf07c2f937a97dc2ef47bd760183dca54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>oneminus</name>
      <anchorfile>group__oneminus.html</anchorfile>
      <anchor>gab3954d5d5676a222f8a1299d1e81ef40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pow</name>
      <anchorfile>group__pow.html</anchorfile>
      <anchor>ga7dbdb37a871fee43869ef23d10d6123f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pow1p</name>
      <anchorfile>group__pow1p.html</anchorfile>
      <anchor>ga216a8b0ad2c118df71788014b7587f8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pow_abs</name>
      <anchorfile>group__pow__abs.html</anchorfile>
      <anchor>ga58e709793c8f3b413516867b44f3010b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>powm1</name>
      <anchorfile>group__powm1.html</anchorfile>
      <anchor>gab8e3f77af87791f809ac6cb9e95b38f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>proj</name>
      <anchorfile>group__proj.html</anchorfile>
      <anchor>gada630e85053aac1a1b0b53e89e5369f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>pure</name>
      <anchorfile>group__pure.html</anchorfile>
      <anchor>gab1c81e9ddeb944ba56779a613452909b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>quaternion</name>
      <anchorfile>group__to__quaternion.html</anchorfile>
      <anchor>ga74ebf9f07f4d05907402cdf7844990d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>radinpi</name>
      <anchorfile>group__radinpi.html</anchorfile>
      <anchor>gac3d481a9f480c463b7d66d720cba129d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>real</name>
      <anchorfile>group__real.html</anchorfile>
      <anchor>ga4121e4e64916c81e31b622b9b45c93fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rec</name>
      <anchorfile>group__rec.html</anchorfile>
      <anchor>ga8eac9efc63807af3af63afdc1df00785</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>reldist</name>
      <anchorfile>group__reldist.html</anchorfile>
      <anchor>ga46d7f251fffedca76fef7a5c414fe700</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>reverse_horner</name>
      <anchorfile>group__reverse__horner.html</anchorfile>
      <anchor>ga5db28dd284ecca661abaf0e79fe57126</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rising_factorial</name>
      <anchorfile>group__rising__factorial.html</anchorfile>
      <anchor>gaaae6b536a41451b5fe9ddc49def87bc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rot_angle</name>
      <anchorfile>group__rot__angle.html</anchorfile>
      <anchor>ga5a036cb7181db5317fee9c8359fe901b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rot_axis</name>
      <anchorfile>group__rot__axis.html</anchorfile>
      <anchor>gadb3618e47c65a49d20d4a926b6d63233</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rotate_vec</name>
      <anchorfile>group__rotate__vec.html</anchorfile>
      <anchor>gafc749b146c3a5d756fc81c80e9b77d74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>rsqrt</name>
      <anchorfile>group__rsqrt.html</anchorfile>
      <anchor>ga82c0404434b20d982247a9918ea7169b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sec</name>
      <anchorfile>group__sec.html</anchorfile>
      <anchor>gaf6e629a6211e4830fa9be0b06e57cef2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sech</name>
      <anchorfile>group__sech.html</anchorfile>
      <anchor>ga3eee368746f4dd2ba15c916dd177810d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sign</name>
      <anchorfile>group__sign.html</anchorfile>
      <anchor>ga67b994823617f74ac451898540a4dec7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>signnz</name>
      <anchorfile>group__signnz.html</anchorfile>
      <anchor>ga97b7c90af61b1ac3e294eb76a15488f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sin</name>
      <anchorfile>group__sin.html</anchorfile>
      <anchor>ga02b482e44325ab868b423995a9cf9df2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sinc</name>
      <anchorfile>group__sinc.html</anchorfile>
      <anchor>ga1ebadf9b1b77b65b5442b382a3e4a467</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sincos</name>
      <anchorfile>group__sincos.html</anchorfile>
      <anchor>ga958b55049cd0ec20b14095b4b158c362</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sinh</name>
      <anchorfile>group__sinh.html</anchorfile>
      <anchor>gaf9f5e943d59c79fd5f95be7df3ddbb3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sinhc</name>
      <anchorfile>group__sinhc.html</anchorfile>
      <anchor>ga7d61257b252a395e77340de641a0fcfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sinhcosh</name>
      <anchorfile>group__sinhcosh.html</anchorfile>
      <anchor>ga5ec18c46ae86e146614c7b573f146e37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>slerp</name>
      <anchorfile>group__slerp.html</anchorfile>
      <anchor>ga1bc2cb0004a3b7a58fd9514247031b7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqr</name>
      <anchorfile>group__sqr.html</anchorfile>
      <anchor>ga341e48919690498ce1a6cac915b3e58d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqr_abs</name>
      <anchorfile>group__sqr__abs.html</anchorfile>
      <anchor>ga3ec084980c244c7393b5c039d69c4aa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sqrt</name>
      <anchorfile>group__sqrt.html</anchorfile>
      <anchor>ga2281638c0373dd457ae6394e159a0010</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>sub</name>
      <anchorfile>group__sub.html</anchorfile>
      <anchor>gacc787c1065460b8a8dae30ebdcdceefa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tan</name>
      <anchorfile>group__tan.html</anchorfile>
      <anchor>ga922fad56b650ca766023b577bb08468a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tanh</name>
      <anchorfile>group__tanh.html</anchorfile>
      <anchor>ga78d8caa0d963138de3b8d7fa35bf9e6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tchebytchev</name>
      <anchorfile>group__tchebytchev.html</anchorfile>
      <anchor>ga232dd9d3384156fd6187ecf8f9d62e2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tgamma</name>
      <anchorfile>group__tgamma.html</anchorfile>
      <anchor>ga2592a73fafd38f5dcff68431ce527a41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tgamma_inv</name>
      <anchorfile>group__tgamma__inv.html</anchorfile>
      <anchor>ga870e7b641a8fd3301736f1c0a545a092</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>to_angle_axis</name>
      <anchorfile>group__to__angle__axis.html</anchorfile>
      <anchor>ga4ab51b43625e09149d9614a764c205c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>to_cylindrical</name>
      <anchorfile>group__to__cylindrical.html</anchorfile>
      <anchor>ga75b1e4452fa2f7e46268981fac1e63e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>to_cylindrospherical</name>
      <anchorfile>group__to__cylindrospherical.html</anchorfile>
      <anchor>ga42961187254bc61f724610896d63ddca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>to_euler</name>
      <anchorfile>group__to__euler.html</anchorfile>
      <anchor>gae7eecc3a7b0016fa20207efb5cd4b12a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>to_multipolar</name>
      <anchorfile>group__to__multipolar.html</anchorfile>
      <anchor>ga37dfba013d9e8f32d84fed33e7c27032</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>to_polar</name>
      <anchorfile>group__to__polar.html</anchorfile>
      <anchor>ga142fe18a19d74983fd0b09aeeb18ed8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>to_rotation_matrix</name>
      <anchorfile>group__to__rotation__matrix.html</anchorfile>
      <anchor>ga50cf8709672a806974dc93f77c0d6e5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>to_semipolar</name>
      <anchorfile>group__to__semipolar.html</anchorfile>
      <anchor>gafd4bfbd92bfffcca410f3b739923c49a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>to_spherical</name>
      <anchorfile>group__to__spherical.html</anchorfile>
      <anchor>gaff0907e49def12a25b3b86b06a10eb87</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>tricomi</name>
      <anchorfile>group__tricomi.html</anchorfile>
      <anchor>ga647fd208e837755628ead583aec3f21e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>trunc</name>
      <anchorfile>group__trunc.html</anchorfile>
      <anchor>ga963040c6c665a0d17451be2b2fcf68c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>xi</name>
      <anchorfile>group__xi.html</anchorfile>
      <anchor>gacb395fe97c9b0425cd25698db9dc2ef0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>zeta</name>
      <anchorfile>group__zeta.html</anchorfile>
      <anchor>ga9dc4aaaee99fe3a698b09d2c63850d66</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::complex_t&lt; double &gt;</type>
      <name>operator&quot;&quot;_i</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a1a8dfb5ebec66f24fce04469de86120b</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::complex_t&lt; float &gt;</type>
      <name>operator&quot;&quot;_if</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a9f6fc5aa16208b342059eabb36dbf8a5</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; double &gt;</type>
      <name>operator&quot;&quot;_j</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>abc2491a56ef3c5cb615ddf96eb265510</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; float &gt;</type>
      <name>operator&quot;&quot;_jf</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a032f8a8437b972416acb47c33b144556</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; double &gt;</type>
      <name>operator&quot;&quot;_k</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ab81a5e9b87e5ca0c50cf8e6eb56217c5</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr kyosu::quaternion_t&lt; float &gt;</type>
      <name>operator&quot;&quot;_kf</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a810e99156f3dfbd5d36030c0b585a9f7</anchor>
      <arglist>(long double d) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator*</name>
      <anchorfile>namespacekyosu.html</anchorfile>
      <anchor>a8e7d7d4929d7d4683837ab23d9323336</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator+</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a3ee8e2fe476ebb1011c476e093227822</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator-</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a36ef300ed76ad52be7293d1a1fac8331</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator*</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a2fb59110f4a618933f413b3c409ae8e6</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>as_cayley_dickson_t&lt; T1, T2 &gt;</type>
      <name>operator/</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>abccb6441a9eaf55aec6a7aea780bd145</anchor>
      <arglist>(T1 const &amp;a, T2 const &amp;b) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator==</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a561363de989d2101775d8b85655ea08e</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator==</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a561363de989d2101775d8b85655ea08e</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator!=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ac345e6a953c0ec69ee85d43be131c6c6</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator!=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ac345e6a953c0ec69ee85d43be131c6c6</anchor>
      <arglist>(T1 const &amp;a, T2 b)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>aa0be302941e24075875f2ff22e1bc866</anchor>
      <arglist>(Tuple const &amp;) -&gt; cayley_dickson&lt; kumi::element_t&lt; 0, Tuple &gt;, kumi::size_v&lt; Tuple &gt; &gt;</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>cayley_dickson</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>aa72548959abb0145c1eef8e8cf2928b4</anchor>
      <arglist>(T0, Ts...) -&gt; cayley_dickson&lt; T0, 1+sizeof...(Ts)&gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator+=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ae63ee48e9508d712beb22e125d596276</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator+=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a127b8375b7ef7d42f5044ebc5770da1a</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator-=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>ab15d8bbe6f7602cf1f7b7c0ac4744bb2</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator-=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a715044a74f36e890e0fa86f68e60c2d1</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator*=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a5f0dd77597800b916c4cebc5e0634cde</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr Self &amp;</type>
      <name>operator*=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a7fb7201475d4bac42ec931f542a0c24f</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto &amp;</type>
      <name>operator/=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a30f4c360cf0019deefa476acf571c387</anchor>
      <arglist>(concepts::cayley_dickson auto &amp;self, concepts::real auto other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr Self &amp;</type>
      <name>operator/=</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a29ff75dcd5392b350f8775c8d0fc331a</anchor>
      <arglist>(Self &amp;self, Other const &amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>auto &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a1d50add5f2f5370f64b20919751ccdcf</anchor>
      <arglist>(std::basic_ostream&lt; C, Ct &gt; &amp;os, CD const &amp;z)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator+</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a18cec006320794126c85b238a68fc91c</anchor>
      <arglist>(Z const &amp;z) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator-</name>
      <anchorfile>structkyosu_1_1cayley__dickson.html</anchorfile>
      <anchor>a3032325260646fe3f0832b076a2b146a</anchor>
      <arglist>(Z const &amp;z) noexcept</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>agnostic</name>
    <title>Algebra-agnostic functions</title>
    <filename>group__agnostic.html</filename>
    <subgroup>abs</subgroup>
    <subgroup>acos</subgroup>
    <subgroup>acosh</subgroup>
    <subgroup>acot</subgroup>
    <subgroup>acoth</subgroup>
    <subgroup>acsc</subgroup>
    <subgroup>acsch</subgroup>
    <subgroup>add</subgroup>
    <subgroup>agd</subgroup>
    <subgroup>am</subgroup>
    <subgroup>arg</subgroup>
    <subgroup>asec</subgroup>
    <subgroup>asech</subgroup>
    <subgroup>asin</subgroup>
    <subgroup>asinh</subgroup>
    <subgroup>associator</subgroup>
    <subgroup>atan</subgroup>
    <subgroup>atanh</subgroup>
    <subgroup>average</subgroup>
    <subgroup>beta</subgroup>
    <subgroup>cbrt</subgroup>
    <subgroup>ceil</subgroup>
    <subgroup>chi</subgroup>
    <subgroup>commutator</subgroup>
    <subgroup>conj</subgroup>
    <subgroup>convert</subgroup>
    <subgroup>cos</subgroup>
    <subgroup>cosh</subgroup>
    <subgroup>cot</subgroup>
    <subgroup>coth</subgroup>
    <subgroup>csc</subgroup>
    <subgroup>csch</subgroup>
    <subgroup>dec</subgroup>
    <subgroup>deta</subgroup>
    <subgroup>digamma</subgroup>
    <subgroup>dist</subgroup>
    <subgroup>div</subgroup>
    <subgroup>dot</subgroup>
    <subgroup>ellint_fe</subgroup>
    <subgroup>ellint_rc</subgroup>
    <subgroup>ellint_rd</subgroup>
    <subgroup>ellint_rf</subgroup>
    <subgroup>ellint_rg</subgroup>
    <subgroup>ellint_rj</subgroup>
    <subgroup>erf</subgroup>
    <subgroup>erfcx</subgroup>
    <subgroup>erfi</subgroup>
    <subgroup>eta</subgroup>
    <subgroup>exp</subgroup>
    <subgroup>exp10</subgroup>
    <subgroup>exp2</subgroup>
    <subgroup>exp_i</subgroup>
    <subgroup>exp_int</subgroup>
    <subgroup>expm1</subgroup>
    <subgroup>expmx2</subgroup>
    <subgroup>expx2</subgroup>
    <subgroup>faddeeva</subgroup>
    <subgroup>fam</subgroup>
    <subgroup>floor</subgroup>
    <subgroup>fma</subgroup>
    <subgroup>fms</subgroup>
    <subgroup>fnma</subgroup>
    <subgroup>fnms</subgroup>
    <subgroup>frac</subgroup>
    <subgroup>from_angle_axis</subgroup>
    <subgroup>fsm</subgroup>
    <subgroup>gd</subgroup>
    <subgroup>gegenbauer</subgroup>
    <subgroup>harmmean</subgroup>
    <subgroup>horner</subgroup>
    <subgroup>hypergeometric</subgroup>
    <subgroup>hypot</subgroup>
    <subgroup>if_else</subgroup>
    <subgroup>inc</subgroup>
    <subgroup>inject</subgroup>
    <subgroup>ipart</subgroup>
    <subgroup>is_cinf</subgroup>
    <subgroup>is_denormal</subgroup>
    <subgroup>is_equal</subgroup>
    <subgroup>is_eqz</subgroup>
    <subgroup>is_finite</subgroup>
    <subgroup>is_flint</subgroup>
    <subgroup>is_fnan</subgroup>
    <subgroup>is_imag</subgroup>
    <subgroup>is_infinite</subgroup>
    <subgroup>is_nan</subgroup>
    <subgroup>is_nez</subgroup>
    <subgroup>is_not_cinf</subgroup>
    <subgroup>is_not_denormal</subgroup>
    <subgroup>is_not_equal</subgroup>
    <subgroup>is_not_finite</subgroup>
    <subgroup>is_not_flint</subgroup>
    <subgroup>is_not_fnan</subgroup>
    <subgroup>is_not_infinite</subgroup>
    <subgroup>is_not_nan</subgroup>
    <subgroup>is_not_real</subgroup>
    <subgroup>is_pure</subgroup>
    <subgroup>is_real</subgroup>
    <subgroup>is_unitary</subgroup>
    <subgroup>jacobi_elliptic</subgroup>
    <subgroup>jpart</subgroup>
    <subgroup>kolmmean</subgroup>
    <subgroup>kpart</subgroup>
    <subgroup>kronecker</subgroup>
    <subgroup>kummer</subgroup>
    <subgroup>lambda</subgroup>
    <subgroup>lbeta</subgroup>
    <subgroup>ldiv</subgroup>
    <subgroup>legendre</subgroup>
    <subgroup>lerp</subgroup>
    <subgroup>linfnorm</subgroup>
    <subgroup>lipart</subgroup>
    <subgroup>ljpart</subgroup>
    <subgroup>lkpart</subgroup>
    <subgroup>log</subgroup>
    <subgroup>log10</subgroup>
    <subgroup>log1p</subgroup>
    <subgroup>log2</subgroup>
    <subgroup>log_abs</subgroup>
    <subgroup>log_abs_gamma</subgroup>
    <subgroup>log_gamma</subgroup>
    <subgroup>lpart</subgroup>
    <subgroup>lpnorm</subgroup>
    <subgroup>lrising_factorial</subgroup>
    <subgroup>manhattan</subgroup>
    <subgroup>maxabs</subgroup>
    <subgroup>maxmag</subgroup>
    <subgroup>minabs</subgroup>
    <subgroup>minmag</subgroup>
    <subgroup>minus</subgroup>
    <subgroup>mul</subgroup>
    <subgroup>muli</subgroup>
    <subgroup>mulmi</subgroup>
    <subgroup>nearest</subgroup>
    <subgroup>negmaxabs</subgroup>
    <subgroup>negminabs</subgroup>
    <subgroup>nthroot</subgroup>
    <subgroup>omega</subgroup>
    <subgroup>oneminus</subgroup>
    <subgroup>pow</subgroup>
    <subgroup>pow1p</subgroup>
    <subgroup>pow_abs</subgroup>
    <subgroup>powm1</subgroup>
    <subgroup>proj</subgroup>
    <subgroup>pure</subgroup>
    <subgroup>radinpi</subgroup>
    <subgroup>real</subgroup>
    <subgroup>rec</subgroup>
    <subgroup>reldist</subgroup>
    <subgroup>reverse_horner</subgroup>
    <subgroup>rising_factorial</subgroup>
    <subgroup>rsqrt</subgroup>
    <subgroup>sec</subgroup>
    <subgroup>sech</subgroup>
    <subgroup>sign</subgroup>
    <subgroup>signnz</subgroup>
    <subgroup>sin</subgroup>
    <subgroup>sinc</subgroup>
    <subgroup>sincos</subgroup>
    <subgroup>sinh</subgroup>
    <subgroup>sinhc</subgroup>
    <subgroup>sinhcosh</subgroup>
    <subgroup>slerp</subgroup>
    <subgroup>sqr</subgroup>
    <subgroup>sqr_abs</subgroup>
    <subgroup>sqrt</subgroup>
    <subgroup>sub</subgroup>
    <subgroup>tan</subgroup>
    <subgroup>tanh</subgroup>
    <subgroup>tchebytchev</subgroup>
    <subgroup>tgamma</subgroup>
    <subgroup>tgamma_inv</subgroup>
    <subgroup>to_complex</subgroup>
    <subgroup>to_polar</subgroup>
    <subgroup>to_quaternion</subgroup>
    <subgroup>tricomi</subgroup>
    <subgroup>trunc</subgroup>
    <subgroup>xi</subgroup>
    <subgroup>zeta</subgroup>
  </compound>
  <compound kind="group">
    <name>kyosu_functions</name>
    <title>Cayley-Dickson Functions</title>
    <filename>group__kyosu__functions.html</filename>
    <subgroup>agnostic</subgroup>
    <subgroup>complex</subgroup>
    <subgroup>quaternion</subgroup>
  </compound>
  <compound kind="group">
    <name>constants</name>
    <title>Cayley-Dickson constants</title>
    <filename>group__constants.html</filename>
    <subgroup>cinf</subgroup>
    <subgroup>fnan</subgroup>
    <subgroup>i</subgroup>
    <subgroup>j</subgroup>
    <subgroup>k</subgroup>
    <subgroup>mi</subgroup>
  </compound>
  <compound kind="group">
    <name>kyosu_traits</name>
    <title>Cayley-Dickson traits</title>
    <filename>group__kyosu__traits.html</filename>
    <class kind="struct">kyosu::as_real</class>
    <member kind="typedef">
      <type>typename as_cayley_dickson_n&lt; Dim, Ts... &gt;::type</type>
      <name>kyosu::as_cayley_dickson_n_t</name>
      <anchorfile>group__kyosu__traits.html</anchorfile>
      <anchor>ga8f185ca9780dc6cec632805d9cd71463</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename as_cayley_dickson&lt; Ts... &gt;::type</type>
      <name>kyosu::as_cayley_dickson_t</name>
      <anchorfile>group__kyosu__traits.html</anchorfile>
      <anchor>ga15c8de6cae864e2052c544b275ee2fb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename as_real_type&lt; T &gt;::type</type>
      <name>kyosu::as_real_type_t</name>
      <anchorfile>group__kyosu__traits.html</anchorfile>
      <anchor>ga6637bd6d8f6205889825bef54cef64e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr unsigned int</type>
      <name>kyosu::dimension_v</name>
      <anchorfile>group__kyosu__traits.html</anchorfile>
      <anchor>gab76e6a5196c280967c692c2139d8301e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>complex</name>
    <title>Complex-specific functions</title>
    <filename>group__complex.html</filename>
    <subgroup>from_polar</subgroup>
  </compound>
  <compound kind="group">
    <name>quaternion</name>
    <title>Quaternion-specific functions</title>
    <filename>group__quaternion.html</filename>
    <subgroup>align</subgroup>
    <subgroup>from_cylindrical</subgroup>
    <subgroup>from_cylindrospherical</subgroup>
    <subgroup>from_euler</subgroup>
    <subgroup>from_multipolar</subgroup>
    <subgroup>from_rotation_matrix</subgroup>
    <subgroup>from_semipolar</subgroup>
    <subgroup>from_spherical</subgroup>
    <subgroup>rot_angle</subgroup>
    <subgroup>rot_axis</subgroup>
    <subgroup>rotate_vec</subgroup>
    <subgroup>to_angle_axis</subgroup>
    <subgroup>to_cylindrical</subgroup>
    <subgroup>to_cylindrospherical</subgroup>
    <subgroup>to_euler</subgroup>
    <subgroup>to_multipolar</subgroup>
    <subgroup>to_rotation_matrix</subgroup>
    <subgroup>to_semipolar</subgroup>
    <subgroup>to_spherical</subgroup>
  </compound>
  <compound kind="group">
    <name>traits</name>
    <title>Traits</title>
    <filename>group__traits.html</filename>
    <class kind="struct">kyosu::promoting_elementwise_callable</class>
    <class kind="struct">kyosu::promoting_strict_elementwise_callable</class>
  </compound>
  <compound kind="group">
    <name>types</name>
    <title>Types</title>
    <filename>group__types.html</filename>
    <class kind="struct">kyosu::cayley_dickson</class>
    <member kind="typedef">
      <type>as_cayley_dickson_n_t&lt; 2, T &gt;</type>
      <name>kyosu::complex_t</name>
      <anchorfile>group__types.html</anchorfile>
      <anchor>ga10a5d4f4bdbbbc385c544fb41c7d628e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>as_cayley_dickson_n_t&lt; 8, T &gt;</type>
      <name>kyosu::octonion_t</name>
      <anchorfile>group__types.html</anchorfile>
      <anchor>ga403b1334a805ef696b3ab5640d550cff</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>as_cayley_dickson_n_t&lt; 4, T &gt;</type>
      <name>kyosu::quaternion_t</name>
      <anchorfile>group__types.html</anchorfile>
      <anchor>ga43659263f005aec8e7e223b889004a22</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>abs</name>
    <title>kyosu::abs</title>
    <filename>group__abs.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::abs</name>
      <anchorfile>group__abs.html</anchorfile>
      <anchor>gac70344c81b5cf55a5257cf54c6e6cb18</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>acos</name>
    <title>kyosu::acos</title>
    <filename>group__acos.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::acos</name>
      <anchorfile>group__acos.html</anchorfile>
      <anchor>gaa6527f2975e878d560e025dba9def6cd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>acosh</name>
    <title>kyosu::acosh</title>
    <filename>group__acosh.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::acosh</name>
      <anchorfile>group__acosh.html</anchorfile>
      <anchor>ga010d55184f68d5a6276939926b22c689</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>acot</name>
    <title>kyosu::acot</title>
    <filename>group__acot.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::acot</name>
      <anchorfile>group__acot.html</anchorfile>
      <anchor>ga7d65b07b38591673afce19e11ad7738c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>acoth</name>
    <title>kyosu::acoth</title>
    <filename>group__acoth.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::acoth</name>
      <anchorfile>group__acoth.html</anchorfile>
      <anchor>gaed04ae9c136243a0b242183b8bf7b0a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>acsc</name>
    <title>kyosu::acsc</title>
    <filename>group__acsc.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::acsc</name>
      <anchorfile>group__acsc.html</anchorfile>
      <anchor>gabe9720e52e71443cb2d0cc9c62fad1a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>acsch</name>
    <title>kyosu::acsch</title>
    <filename>group__acsch.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::acsch</name>
      <anchorfile>group__acsch.html</anchorfile>
      <anchor>gaceca829cfb9fe916d2a1c769b10018ef</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>add</name>
    <title>kyosu::add</title>
    <filename>group__add.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::add</name>
      <anchorfile>group__add.html</anchorfile>
      <anchor>gadcd7dc3600f2f5da8fb31efc6b02d244</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>agd</name>
    <title>kyosu::agd</title>
    <filename>group__agd.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::agd</name>
      <anchorfile>group__agd.html</anchorfile>
      <anchor>ga302a7795299874023f6c615a9908e2ba</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>align</name>
    <title>kyosu::align</title>
    <filename>group__align.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::align</name>
      <anchorfile>group__align.html</anchorfile>
      <anchor>ga75d48d720e22794a606131a0b0d7ce7d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>am</name>
    <title>kyosu::am</title>
    <filename>group__am.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::am</name>
      <anchorfile>group__am.html</anchorfile>
      <anchor>gaabbe680517187a5e2b72489ec5921211</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>arg</name>
    <title>kyosu::arg</title>
    <filename>group__arg.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::arg</name>
      <anchorfile>group__arg.html</anchorfile>
      <anchor>gae6b016425d0a624d4391512f4afb64fc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>asec</name>
    <title>kyosu::asec</title>
    <filename>group__asec.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::asec</name>
      <anchorfile>group__asec.html</anchorfile>
      <anchor>gaa0e50a4af9f77cf0b053e27ede376ca5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>asech</name>
    <title>kyosu::asech</title>
    <filename>group__asech.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::asech</name>
      <anchorfile>group__asech.html</anchorfile>
      <anchor>ga73d1420e184c7752eb998291672c038d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>asin</name>
    <title>kyosu::asin</title>
    <filename>group__asin.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::asin</name>
      <anchorfile>group__asin.html</anchorfile>
      <anchor>ga1b0ab1f5f9386bcfe84bc3356ad103e1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>asinh</name>
    <title>kyosu::asinh</title>
    <filename>group__asinh.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::asinh</name>
      <anchorfile>group__asinh.html</anchorfile>
      <anchor>ga472ea5acadc02ca6a04f9b8c29b60a27</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>associator</name>
    <title>kyosu::associator</title>
    <filename>group__associator.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::associator</name>
      <anchorfile>group__associator.html</anchorfile>
      <anchor>gac1477076e48284b3ea6b0304e24188c1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>atan</name>
    <title>kyosu::atan</title>
    <filename>group__atan.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::atan</name>
      <anchorfile>group__atan.html</anchorfile>
      <anchor>ga4c75b3c9fa3f13d411c888143c0660a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>atanh</name>
    <title>kyosu::atanh</title>
    <filename>group__atanh.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::atanh</name>
      <anchorfile>group__atanh.html</anchorfile>
      <anchor>gad32eb35a5b7923acacd701fd74ae6834</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>average</name>
    <title>kyosu::average</title>
    <filename>group__average.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::average</name>
      <anchorfile>group__average.html</anchorfile>
      <anchor>ga215f5e846e2b272e4e669c36a4d2afc1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>beta</name>
    <title>kyosu::beta</title>
    <filename>group__beta.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::beta</name>
      <anchorfile>group__beta.html</anchorfile>
      <anchor>gace5ed207bcf440be909fff9d63c23409</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>cbrt</name>
    <title>kyosu::cbrt</title>
    <filename>group__cbrt.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::cbrt</name>
      <anchorfile>group__cbrt.html</anchorfile>
      <anchor>ga81b0d6fb1ff90f938f3593cc201fcb1b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ceil</name>
    <title>kyosu::ceil</title>
    <filename>group__ceil.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ceil</name>
      <anchorfile>group__ceil.html</anchorfile>
      <anchor>ga8c89c82b3d1c4471c8c52c832c78d792</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>chi</name>
    <title>kyosu::chi</title>
    <filename>group__chi.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::chi</name>
      <anchorfile>group__chi.html</anchorfile>
      <anchor>ga05dfb6e5aebe98bf4ea725063cbce033</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>cinf</name>
    <title>kyosu::cinf</title>
    <filename>group__cinf.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::cinf</name>
      <anchorfile>group__cinf.html</anchorfile>
      <anchor>ga0c9ef916832ff4cbfbf575bc77f4fb4f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>commutator</name>
    <title>kyosu::commutator</title>
    <filename>group__commutator.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::commutator</name>
      <anchorfile>group__commutator.html</anchorfile>
      <anchor>gacdb90f1b3fb7481bdb308a74224e8b38</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>conj</name>
    <title>kyosu::conj</title>
    <filename>group__conj.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::conj</name>
      <anchorfile>group__conj.html</anchorfile>
      <anchor>ga7e324b44c677cab7cf646a1cb87e9405</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>convert</name>
    <title>kyosu::convert</title>
    <filename>group__convert.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::convert</name>
      <anchorfile>group__convert.html</anchorfile>
      <anchor>ga081e21d8e2b4876702601c74562eeabb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>cos</name>
    <title>kyosu::cos</title>
    <filename>group__cos.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::cos</name>
      <anchorfile>group__cos.html</anchorfile>
      <anchor>gaff78cbf53496580d8216966a5f96a5f9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>cosh</name>
    <title>kyosu::cosh</title>
    <filename>group__cosh.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::cosh</name>
      <anchorfile>group__cosh.html</anchorfile>
      <anchor>gaacd4903b331413b4b0c8da2a1521093a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>cot</name>
    <title>kyosu::cot</title>
    <filename>group__cot.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::cot</name>
      <anchorfile>group__cot.html</anchorfile>
      <anchor>gafb2eb2745644a8b663b71b6ad8d5f6b4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>coth</name>
    <title>kyosu::coth</title>
    <filename>group__coth.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::coth</name>
      <anchorfile>group__coth.html</anchorfile>
      <anchor>gaf77965146c145973900d9edec9742caa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>csc</name>
    <title>kyosu::csc</title>
    <filename>group__csc.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::csc</name>
      <anchorfile>group__csc.html</anchorfile>
      <anchor>ga627c035548638b22d13890b8b03e5ca9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>csch</name>
    <title>kyosu::csch</title>
    <filename>group__csch.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::csch</name>
      <anchorfile>group__csch.html</anchorfile>
      <anchor>gaac742f86aaadd71a3fcca9b9e7a23d52</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>dec</name>
    <title>kyosu::dec</title>
    <filename>group__dec.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::dec</name>
      <anchorfile>group__dec.html</anchorfile>
      <anchor>ga8b430b0a36d45bf0bec840d6e4cf2063</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>deta</name>
    <title>kyosu::deta</title>
    <filename>group__deta.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::deta</name>
      <anchorfile>group__deta.html</anchorfile>
      <anchor>ga39f6e6a20461bbbd304313e231746d47</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>digamma</name>
    <title>kyosu::digamma</title>
    <filename>group__digamma.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::digamma</name>
      <anchorfile>group__digamma.html</anchorfile>
      <anchor>gab9af9dd4c0b41ba6ce2171fd8192e7de</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>dist</name>
    <title>kyosu::dist</title>
    <filename>group__dist.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::dist</name>
      <anchorfile>group__dist.html</anchorfile>
      <anchor>ga05d99d8cf767a2ec1d7806916bc22f00</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>div</name>
    <title>kyosu::div</title>
    <filename>group__div.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::div</name>
      <anchorfile>group__div.html</anchorfile>
      <anchor>ga435faee7fb66f5162ffb64397a878db9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>dot</name>
    <title>kyosu::dot</title>
    <filename>group__dot.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::dot</name>
      <anchorfile>group__dot.html</anchorfile>
      <anchor>gab77f480117e453861b459a5dcfa0fb08</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ellint_fe</name>
    <title>kyosu::ellint_fe</title>
    <filename>group__ellint__fe.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ellint_fe</name>
      <anchorfile>group__ellint__fe.html</anchorfile>
      <anchor>ga858bbc0cd82011e1911907d0d6cdf2cb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ellint_rc</name>
    <title>kyosu::ellint_rc</title>
    <filename>group__ellint__rc.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ellint_rc</name>
      <anchorfile>group__ellint__rc.html</anchorfile>
      <anchor>ga59830d1553989ba7ee7722d0b2731039</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ellint_rd</name>
    <title>kyosu::ellint_rd</title>
    <filename>group__ellint__rd.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ellint_rd</name>
      <anchorfile>group__ellint__rd.html</anchorfile>
      <anchor>ga81e0756cf62ec6b36813e4eb930992c9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ellint_rf</name>
    <title>kyosu::ellint_rf</title>
    <filename>group__ellint__rf.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ellint_rf</name>
      <anchorfile>group__ellint__rf.html</anchorfile>
      <anchor>gac8903dbfbdb109a6d1c70209d3e20386</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ellint_rg</name>
    <title>kyosu::ellint_rg</title>
    <filename>group__ellint__rg.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ellint_rg</name>
      <anchorfile>group__ellint__rg.html</anchorfile>
      <anchor>gabe721a515ca959098143128eeb2c62c3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ellint_rj</name>
    <title>kyosu::ellint_rj</title>
    <filename>group__ellint__rj.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ellint_rj</name>
      <anchorfile>group__ellint__rj.html</anchorfile>
      <anchor>gaea54d1c027a77c63a592fc8e933fc384</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>erf</name>
    <title>kyosu::erf</title>
    <filename>group__erf.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::erf</name>
      <anchorfile>group__erf.html</anchorfile>
      <anchor>ga4836ce9e292b5071b85a14560ecfcba5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>erfcx</name>
    <title>kyosu::erfcx</title>
    <filename>group__erfcx.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::erfcx</name>
      <anchorfile>group__erfcx.html</anchorfile>
      <anchor>ga39a3490b9804d064f6e763b6b2ee6545</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>erfi</name>
    <title>kyosu::erfi</title>
    <filename>group__erfi.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::erfi</name>
      <anchorfile>group__erfi.html</anchorfile>
      <anchor>ga1cfc9aee0b7545c21db6531760e294a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>eta</name>
    <title>kyosu::eta</title>
    <filename>group__eta.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::eta</name>
      <anchorfile>group__eta.html</anchorfile>
      <anchor>ga5c1b5d98ef3091b5c757ab13d061fef2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>exp</name>
    <title>kyosu::exp</title>
    <filename>group__exp.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::exp</name>
      <anchorfile>group__exp.html</anchorfile>
      <anchor>ga43bd0f5793b846caaf808a7f998734c0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>exp10</name>
    <title>kyosu::exp10</title>
    <filename>group__exp10.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::exp10</name>
      <anchorfile>group__exp10.html</anchorfile>
      <anchor>ga37e090c4b1d41d1c37db13d21e293693</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>exp2</name>
    <title>kyosu::exp2</title>
    <filename>group__exp2.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::exp2</name>
      <anchorfile>group__exp2.html</anchorfile>
      <anchor>ga7646bef9d3128713a8284a545c10b1e5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>exp_i</name>
    <title>kyosu::exp_i</title>
    <filename>group__exp__i.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::exp_i</name>
      <anchorfile>group__exp__i.html</anchorfile>
      <anchor>gae60807f50d322f3b5a2289f14cb115bc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>exp_int</name>
    <title>kyosu::exp_int</title>
    <filename>group__exp__int.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::exp_int</name>
      <anchorfile>group__exp__int.html</anchorfile>
      <anchor>gac080f79509178fd061575a3875a29b53</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>expm1</name>
    <title>kyosu::expm1</title>
    <filename>group__expm1.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::expm1</name>
      <anchorfile>group__expm1.html</anchorfile>
      <anchor>ga20b941e423fc7750665a8c15da666169</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>expmx2</name>
    <title>kyosu::expmx2</title>
    <filename>group__expmx2.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::expmx2</name>
      <anchorfile>group__expmx2.html</anchorfile>
      <anchor>ga17336c4e1b6666dd1fb632c136b1f19d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>expx2</name>
    <title>kyosu::expx2</title>
    <filename>group__expx2.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::expx2</name>
      <anchorfile>group__expx2.html</anchorfile>
      <anchor>gae725cf6ea34c98c328ae87ef2d9271f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>faddeeva</name>
    <title>kyosu::faddeeva</title>
    <filename>group__faddeeva.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::faddeeva</name>
      <anchorfile>group__faddeeva.html</anchorfile>
      <anchor>ga595600555226cba8dbd29be5512575a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>fam</name>
    <title>kyosu::fam</title>
    <filename>group__fam.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::fam</name>
      <anchorfile>group__fam.html</anchorfile>
      <anchor>ga4a11cd36bff3274fc96bc9798f371b90</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>floor</name>
    <title>kyosu::floor</title>
    <filename>group__floor.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::floor</name>
      <anchorfile>group__floor.html</anchorfile>
      <anchor>ga44f8bdc4f61d63ad54b285482837ed6c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>fma</name>
    <title>kyosu::fma</title>
    <filename>group__fma.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::fma</name>
      <anchorfile>group__fma.html</anchorfile>
      <anchor>gab0bdf8bce326915395666800b2d5b175</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>fms</name>
    <title>kyosu::fms</title>
    <filename>group__fms.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::fms</name>
      <anchorfile>group__fms.html</anchorfile>
      <anchor>gae2d27aa05efe337cd4d65778bbf08d7f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>fnan</name>
    <title>kyosu::fnan</title>
    <filename>group__fnan.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::fnan</name>
      <anchorfile>group__fnan.html</anchorfile>
      <anchor>ga0cf87abcd108df159683cdcd153e9f12</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>fnma</name>
    <title>kyosu::fnma</title>
    <filename>group__fnma.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::fnma</name>
      <anchorfile>group__fnma.html</anchorfile>
      <anchor>ga5b9920085c94d467ae761243033279fb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>fnms</name>
    <title>kyosu::fnms</title>
    <filename>group__fnms.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::fnms</name>
      <anchorfile>group__fnms.html</anchorfile>
      <anchor>ga5a79e77dd6087f110bca457d25d6caef</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>frac</name>
    <title>kyosu::frac</title>
    <filename>group__frac.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::frac</name>
      <anchorfile>group__frac.html</anchorfile>
      <anchor>ga7284c6f970f48919150521ccb059d373</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>from_angle_axis</name>
    <title>kyosu::from_angle_axis</title>
    <filename>group__from__angle__axis.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::from_angle_axis</name>
      <anchorfile>group__from__angle__axis.html</anchorfile>
      <anchor>ga2e2e427d078f717745ed2821f6cd06f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>from_cylindrical</name>
    <title>kyosu::from_cylindrical</title>
    <filename>group__from__cylindrical.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::from_cylindrical</name>
      <anchorfile>group__from__cylindrical.html</anchorfile>
      <anchor>ga505ff6cf7441aa432d2549a840868527</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>from_cylindrospherical</name>
    <title>kyosu::from_cylindrospherical</title>
    <filename>group__from__cylindrospherical.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::from_cylindrospherical</name>
      <anchorfile>group__from__cylindrospherical.html</anchorfile>
      <anchor>ga730bd78358cd0568b81be9cdcd247455</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>from_euler</name>
    <title>kyosu::from_euler</title>
    <filename>group__from__euler.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::from_euler</name>
      <anchorfile>group__from__euler.html</anchorfile>
      <anchor>ga4e7d9b2067dc764269c1539b6e4b9271</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>from_multipolar</name>
    <title>kyosu::from_multipolar</title>
    <filename>group__from__multipolar.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::from_multipolar</name>
      <anchorfile>group__from__multipolar.html</anchorfile>
      <anchor>ga2b89a4fbe7aa7dcd69bef6b423d7dac2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>from_polar</name>
    <title>kyosu::from_polar</title>
    <filename>group__from__polar.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::from_polar</name>
      <anchorfile>group__from__polar.html</anchorfile>
      <anchor>gaf64b08ee90565c95c04b029767cba95e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>from_rotation_matrix</name>
    <title>kyosu::from_rotation_matrix</title>
    <filename>group__from__rotation__matrix.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::from_rotation_matrix</name>
      <anchorfile>group__from__rotation__matrix.html</anchorfile>
      <anchor>gad4d2929cc9f93e1308c26a2e0160007d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>from_semipolar</name>
    <title>kyosu::from_semipolar</title>
    <filename>group__from__semipolar.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::from_semipolar</name>
      <anchorfile>group__from__semipolar.html</anchorfile>
      <anchor>gab01fdca022335c40f7f5e9a7445bedcf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>from_spherical</name>
    <title>kyosu::from_spherical</title>
    <filename>group__from__spherical.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::from_spherical</name>
      <anchorfile>group__from__spherical.html</anchorfile>
      <anchor>gaed1e70b2f6b903ef24ce33d7937d8958</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>fsm</name>
    <title>kyosu::fsm</title>
    <filename>group__fsm.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::fsm</name>
      <anchorfile>group__fsm.html</anchorfile>
      <anchor>ga35571a35abfd2cc96d0ff2edd24d1d3a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>gd</name>
    <title>kyosu::gd</title>
    <filename>group__gd.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::gd</name>
      <anchorfile>group__gd.html</anchorfile>
      <anchor>gad3eacdb5f403d7a4f3a4fcc412f57b0e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>gegenbauer</name>
    <title>kyosu::gegenbauer</title>
    <filename>group__gegenbauer.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::gegenbauer</name>
      <anchorfile>group__gegenbauer.html</anchorfile>
      <anchor>gafacfbe5287142d18a3e08d15f9867b2e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>harmmean</name>
    <title>kyosu::harmmean</title>
    <filename>group__harmmean.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::harmmean</name>
      <anchorfile>group__harmmean.html</anchorfile>
      <anchor>ga2142b1d05423b76c401df4d5bf13003a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>horner</name>
    <title>kyosu::horner</title>
    <filename>group__horner.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::horner</name>
      <anchorfile>group__horner.html</anchorfile>
      <anchor>gaeed0a0dd100ddf05147ded0ba505a5af</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>hypergeometric</name>
    <title>kyosu::hypergeometric</title>
    <filename>group__hypergeometric.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::hypergeometric</name>
      <anchorfile>group__hypergeometric.html</anchorfile>
      <anchor>gad56c4489b7eb531f721190906ce04ee9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>hypot</name>
    <title>kyosu::hypot</title>
    <filename>group__hypot.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::hypot</name>
      <anchorfile>group__hypot.html</anchorfile>
      <anchor>gafb18085cfb37fc835a36abdbf981101e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>i</name>
    <title>kyosu::i</title>
    <filename>group__i.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::i</name>
      <anchorfile>group__i.html</anchorfile>
      <anchor>gaa17b17c2202168c33700e95ccce7322d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>if_else</name>
    <title>kyosu::if_else</title>
    <filename>group__if__else.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::if_else</name>
      <anchorfile>group__if__else.html</anchorfile>
      <anchor>ga653d166a9a5d389a6d5aa1a1220b4643</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>inc</name>
    <title>kyosu::inc</title>
    <filename>group__inc.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::inc</name>
      <anchorfile>group__inc.html</anchorfile>
      <anchor>gae5c7264a43adea8149beb99e71fb0e4d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>inject</name>
    <title>kyosu::inject</title>
    <filename>group__inject.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::inject</name>
      <anchorfile>group__inject.html</anchorfile>
      <anchor>ga5c2b44e7d8e27d43b129c6e0739bf6d3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ipart</name>
    <title>kyosu::ipart</title>
    <filename>group__ipart.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::imag</name>
      <anchorfile>group__ipart.html</anchorfile>
      <anchor>gaff94a2685c6d030458b388a4a4079efe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ipart</name>
      <anchorfile>group__ipart.html</anchorfile>
      <anchor>gac538e6a794844977cba0f5043a990c99</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_cinf</name>
    <title>kyosu::is_cinf</title>
    <filename>group__is__cinf.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_cinf</name>
      <anchorfile>group__is__cinf.html</anchorfile>
      <anchor>ga193150c1f7fbf9cd161c8e9af90ebc9f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_denormal</name>
    <title>kyosu::is_denormal</title>
    <filename>group__is__denormal.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_denormal</name>
      <anchorfile>group__is__denormal.html</anchorfile>
      <anchor>ga21e602517052b438e7702aaeea4427ad</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_equal</name>
    <title>kyosu::is_equal</title>
    <filename>group__is__equal.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_equal</name>
      <anchorfile>group__is__equal.html</anchorfile>
      <anchor>ga2d35f43723bf977e2924344dfe248938</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_eqz</name>
    <title>kyosu::is_eqz</title>
    <filename>group__is__eqz.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_eqz</name>
      <anchorfile>group__is__eqz.html</anchorfile>
      <anchor>ga8cade15af2145e2b456fb57adcfbce78</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_finite</name>
    <title>kyosu::is_finite</title>
    <filename>group__is__finite.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_finite</name>
      <anchorfile>group__is__finite.html</anchorfile>
      <anchor>gaeb6f14e6a7023df6a604d7f0215422ce</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_flint</name>
    <title>kyosu::is_flint</title>
    <filename>group__is__flint.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_flint</name>
      <anchorfile>group__is__flint.html</anchorfile>
      <anchor>ga9bdf18bc3243b941872b67110a284f08</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_fnan</name>
    <title>kyosu::is_fnan</title>
    <filename>group__is__fnan.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_fnan</name>
      <anchorfile>group__is__fnan.html</anchorfile>
      <anchor>gac0ac349906b1997e8d679a22d22fb592</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_imag</name>
    <title>kyosu::is_imag</title>
    <filename>group__is__imag.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_imag</name>
      <anchorfile>group__is__imag.html</anchorfile>
      <anchor>ga08071c945a2f66b655b93b2a51800d03</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_infinite</name>
    <title>kyosu::is_infinite</title>
    <filename>group__is__infinite.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_infinite</name>
      <anchorfile>group__is__infinite.html</anchorfile>
      <anchor>gafceb7f6cf53d556c2eeb87fe2501a3d1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_nan</name>
    <title>kyosu::is_nan</title>
    <filename>group__is__nan.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_nan</name>
      <anchorfile>group__is__nan.html</anchorfile>
      <anchor>gada27b99a22e5835b9e06f7aa6b0ded24</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_nez</name>
    <title>kyosu::is_nez</title>
    <filename>group__is__nez.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_nez</name>
      <anchorfile>group__is__nez.html</anchorfile>
      <anchor>ga97f0d66eadb5d6822404be13ea888c08</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_not_cinf</name>
    <title>kyosu::is_not_cinf</title>
    <filename>group__is__not__cinf.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_not_cinf</name>
      <anchorfile>group__is__not__cinf.html</anchorfile>
      <anchor>ga0048da32d060c9d35691c34efc9f8306</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_not_denormal</name>
    <title>kyosu::is_not_denormal</title>
    <filename>group__is__not__denormal.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_not_denormal</name>
      <anchorfile>group__is__not__denormal.html</anchorfile>
      <anchor>gada3eef5a9850543278aeb28785ebbc99</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_not_equal</name>
    <title>kyosu::is_not_equal</title>
    <filename>group__is__not__equal.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_not_equal</name>
      <anchorfile>group__is__not__equal.html</anchorfile>
      <anchor>gaf8fe0f16bad6131ea9afa6f9c626db8e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_not_finite</name>
    <title>kyosu::is_not_finite</title>
    <filename>group__is__not__finite.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_not_finite</name>
      <anchorfile>group__is__not__finite.html</anchorfile>
      <anchor>ga750ee4ee1ef911781bd44700f444caa6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_not_flint</name>
    <title>kyosu::is_not_flint</title>
    <filename>group__is__not__flint.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_not_flint</name>
      <anchorfile>group__is__not__flint.html</anchorfile>
      <anchor>gad08e1cfd306a50ccd92564086765d3a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_not_fnan</name>
    <title>kyosu::is_not_fnan</title>
    <filename>group__is__not__fnan.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_not_fnan</name>
      <anchorfile>group__is__not__fnan.html</anchorfile>
      <anchor>ga6101a780e32ca49e21b7efa011629fc6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_not_infinite</name>
    <title>kyosu::is_not_infinite</title>
    <filename>group__is__not__infinite.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_not_infinite</name>
      <anchorfile>group__is__not__infinite.html</anchorfile>
      <anchor>ga42e5f2dc30e3fffca6bc19ff0b9e746e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_not_nan</name>
    <title>kyosu::is_not_nan</title>
    <filename>group__is__not__nan.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_not_nan</name>
      <anchorfile>group__is__not__nan.html</anchorfile>
      <anchor>ga1c69997f67ae996aa06a61c3d8ad9765</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_not_real</name>
    <title>kyosu::is_not_real</title>
    <filename>group__is__not__real.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_not_real</name>
      <anchorfile>group__is__not__real.html</anchorfile>
      <anchor>ga9968f11970b837778ffe48677be73c82</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_pure</name>
    <title>kyosu::is_pure</title>
    <filename>group__is__pure.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_pure</name>
      <anchorfile>group__is__pure.html</anchorfile>
      <anchor>ga5d01b83f2f41b991e96a16caa279388a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_real</name>
    <title>kyosu::is_real</title>
    <filename>group__is__real.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_real</name>
      <anchorfile>group__is__real.html</anchorfile>
      <anchor>ga83642115085d0145bddbd31b40a09738</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>is_unitary</name>
    <title>kyosu::is_unitary</title>
    <filename>group__is__unitary.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::is_unitary</name>
      <anchorfile>group__is__unitary.html</anchorfile>
      <anchor>gae2445553e9488629a8e57c9e5014b94b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>j</name>
    <title>kyosu::j</title>
    <filename>group__j.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::j</name>
      <anchorfile>group__j.html</anchorfile>
      <anchor>gad984a2daa62e2ee33ee4577d87cb0533</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>jacobi_elliptic</name>
    <title>kyosu::jacobi_elliptic</title>
    <filename>group__jacobi__elliptic.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::jacobi_elliptic</name>
      <anchorfile>group__jacobi__elliptic.html</anchorfile>
      <anchor>ga9ebb9efdd6da680620540b07dd9c34fc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>jpart</name>
    <title>kyosu::jpart</title>
    <filename>group__jpart.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::jpart</name>
      <anchorfile>group__jpart.html</anchorfile>
      <anchor>ga66085e00476f789b11deaf0acb0f24ac</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>k</name>
    <title>kyosu::k</title>
    <filename>group__k.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::k</name>
      <anchorfile>group__k.html</anchorfile>
      <anchor>gabb75241dcb99709608d07d0a94af3813</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>kolmmean</name>
    <title>kyosu::kolmmean</title>
    <filename>group__kolmmean.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::kolmmean</name>
      <anchorfile>group__kolmmean.html</anchorfile>
      <anchor>ga7445b35c94d90ede9a863a6c611fb5c8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>kpart</name>
    <title>kyosu::kpart</title>
    <filename>group__kpart.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::kpart</name>
      <anchorfile>group__kpart.html</anchorfile>
      <anchor>gab70ea330558b767effdc20d5d621a503</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>kronecker</name>
    <title>kyosu::kronecker</title>
    <filename>group__kronecker.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::kronecker</name>
      <anchorfile>group__kronecker.html</anchorfile>
      <anchor>ga386216ae903d30cecb1c34d69f1335a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>kummer</name>
    <title>kyosu::kummer</title>
    <filename>group__kummer.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::kummer</name>
      <anchorfile>group__kummer.html</anchorfile>
      <anchor>gab4537c0d485cdbd2e836420db2f31ec7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>lambda</name>
    <title>kyosu::lambda</title>
    <filename>group__lambda.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::lambda</name>
      <anchorfile>group__lambda.html</anchorfile>
      <anchor>gaf7906a8d9d35e9e55a84ddcfb03cf308</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>lbeta</name>
    <title>kyosu::lbeta</title>
    <filename>group__lbeta.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::lbeta</name>
      <anchorfile>group__lbeta.html</anchorfile>
      <anchor>gafe0c7a3f991d20592748394411b97f03</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ldiv</name>
    <title>kyosu::ldiv</title>
    <filename>group__ldiv.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ldiv</name>
      <anchorfile>group__ldiv.html</anchorfile>
      <anchor>ga4842daf39053c0a08fa68cd1850558e1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>legendre</name>
    <title>kyosu::legendre</title>
    <filename>group__legendre.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::legendre</name>
      <anchorfile>group__legendre.html</anchorfile>
      <anchor>ga1a1ccdfb045aafc00e85d17216d871f0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>lerp</name>
    <title>kyosu::lerp</title>
    <filename>group__lerp.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::lerp</name>
      <anchorfile>group__lerp.html</anchorfile>
      <anchor>ga82646e9c6fda08fd02c304d3b001abaa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>linfnorm</name>
    <title>kyosu::linfnorm</title>
    <filename>group__linfnorm.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::linfnorm</name>
      <anchorfile>group__linfnorm.html</anchorfile>
      <anchor>ga2413388335ecd0df3e7d75d4e399fdd8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>lipart</name>
    <title>kyosu::lipart</title>
    <filename>group__lipart.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::lipart</name>
      <anchorfile>group__lipart.html</anchorfile>
      <anchor>gadbcb03cb1614e1d7a30b6ab6d770792d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ljpart</name>
    <title>kyosu::ljpart</title>
    <filename>group__ljpart.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::ljpart</name>
      <anchorfile>group__ljpart.html</anchorfile>
      <anchor>gab9af5fb49098ddef5b3dba27f21628bb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>lkpart</name>
    <title>kyosu::lkpart</title>
    <filename>group__lkpart.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::lkpart</name>
      <anchorfile>group__lkpart.html</anchorfile>
      <anchor>gaa2a8f6265c301b29d450fa2fa479b530</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>log</name>
    <title>kyosu::log</title>
    <filename>group__log.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::log</name>
      <anchorfile>group__log.html</anchorfile>
      <anchor>gabc0fe7e42be704597604cc8dec55f4ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>log10</name>
    <title>kyosu::log10</title>
    <filename>group__log10.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::log10</name>
      <anchorfile>group__log10.html</anchorfile>
      <anchor>gae2f0c4d2d1293fe07161174e586a27a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>log1p</name>
    <title>kyosu::log1p</title>
    <filename>group__log1p.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::log1p</name>
      <anchorfile>group__log1p.html</anchorfile>
      <anchor>gad73829174f8194f6843b625c3538a180</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>log2</name>
    <title>kyosu::log2</title>
    <filename>group__log2.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::log2</name>
      <anchorfile>group__log2.html</anchorfile>
      <anchor>ga5385bb9ae59cafa7a52c91df515c68b7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>log_abs</name>
    <title>kyosu::log_abs</title>
    <filename>group__log__abs.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::log_abs</name>
      <anchorfile>group__log__abs.html</anchorfile>
      <anchor>gae2249b712f1cea3a5d99295d7c355785</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>log_abs_gamma</name>
    <title>kyosu::log_abs_gamma</title>
    <filename>group__log__abs__gamma.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::log_abs_gamma</name>
      <anchorfile>group__log__abs__gamma.html</anchorfile>
      <anchor>gad513c55f0b0115b4fe0e159d75a75d3d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>log_gamma</name>
    <title>kyosu::log_gamma</title>
    <filename>group__log__gamma.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::log_gamma</name>
      <anchorfile>group__log__gamma.html</anchorfile>
      <anchor>ga7ba6f29f797e8ee39b4a6279b810d740</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>lpart</name>
    <title>kyosu::lpart</title>
    <filename>group__lpart.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::lpart</name>
      <anchorfile>group__lpart.html</anchorfile>
      <anchor>ga8f1c7a32dcae0c94c2f79f0df7b60044</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>lpnorm</name>
    <title>kyosu::lpnorm</title>
    <filename>group__lpnorm.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::lpnorm</name>
      <anchorfile>group__lpnorm.html</anchorfile>
      <anchor>gac6f87aa6b8c7e02f0c8bba937bfd335e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>lrising_factorial</name>
    <title>kyosu::lrising_factorial</title>
    <filename>group__lrising__factorial.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::lrising_factorial</name>
      <anchorfile>group__lrising__factorial.html</anchorfile>
      <anchor>gaf92a640dbc6c479e4b8b17c9c951eba9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>manhattan</name>
    <title>kyosu::manhattan</title>
    <filename>group__manhattan.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::manhattan</name>
      <anchorfile>group__manhattan.html</anchorfile>
      <anchor>ga27fb46c71e5625bc16d551b2d042fa64</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>maxabs</name>
    <title>kyosu::maxabs</title>
    <filename>group__maxabs.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::maxabs</name>
      <anchorfile>group__maxabs.html</anchorfile>
      <anchor>gae0175ca71d75db9471034684a10b37f7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>maxmag</name>
    <title>kyosu::maxmag</title>
    <filename>group__maxmag.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::maxmag</name>
      <anchorfile>group__maxmag.html</anchorfile>
      <anchor>ga3ca0ac25a6f4cb2c0a13290da3b09b77</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>mi</name>
    <title>kyosu::mi</title>
    <filename>group__mi.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::mi</name>
      <anchorfile>group__mi.html</anchorfile>
      <anchor>gada12ac0bbff1fc4e7476a12736e9a6c9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>minabs</name>
    <title>kyosu::minabs</title>
    <filename>group__minabs.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::minabs</name>
      <anchorfile>group__minabs.html</anchorfile>
      <anchor>gacf658d87e2919f4f6f6a830a2f94350b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>minmag</name>
    <title>kyosu::minmag</title>
    <filename>group__minmag.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::minmag</name>
      <anchorfile>group__minmag.html</anchorfile>
      <anchor>gaef4a4b97d1e190629aa6e51150c38c6c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>minus</name>
    <title>kyosu::minus</title>
    <filename>group__minus.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::minus</name>
      <anchorfile>group__minus.html</anchorfile>
      <anchor>ga77f919fac06fc69976f93e549b57517d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>mul</name>
    <title>kyosu::mul</title>
    <filename>group__mul.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::mul</name>
      <anchorfile>group__mul.html</anchorfile>
      <anchor>gafa0529f93372ed1d6f7288110d2cd663</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>muli</name>
    <title>kyosu::muli</title>
    <filename>group__muli.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::muli</name>
      <anchorfile>group__muli.html</anchorfile>
      <anchor>ga5d7e27fded33a32379427adc16edec6f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>mulmi</name>
    <title>kyosu::mulmi</title>
    <filename>group__mulmi.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::mulmi</name>
      <anchorfile>group__mulmi.html</anchorfile>
      <anchor>gad0611b77939df02be326c41a6b6262bb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>nearest</name>
    <title>kyosu::nearest</title>
    <filename>group__nearest.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::nearest</name>
      <anchorfile>group__nearest.html</anchorfile>
      <anchor>gafcbbc98213ecbc8a0bcb2b0a890d9542</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>negmaxabs</name>
    <title>kyosu::negmaxabs</title>
    <filename>group__negmaxabs.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::negmaxabs</name>
      <anchorfile>group__negmaxabs.html</anchorfile>
      <anchor>ga242ce91e6c5d5abcbee8fc893f6c87e2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>negminabs</name>
    <title>kyosu::negminabs</title>
    <filename>group__negminabs.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::negminabs</name>
      <anchorfile>group__negminabs.html</anchorfile>
      <anchor>gac38ca831b02fb724d5865857a2cb3a2c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>nthroot</name>
    <title>kyosu::nthroot</title>
    <filename>group__nthroot.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::nthroot</name>
      <anchorfile>group__nthroot.html</anchorfile>
      <anchor>gaf2ae4980beda0e505d92440065e57f7d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>omega</name>
    <title>kyosu::omega</title>
    <filename>group__omega.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::omega</name>
      <anchorfile>group__omega.html</anchorfile>
      <anchor>gaf07c2f937a97dc2ef47bd760183dca54</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>oneminus</name>
    <title>kyosu::oneminus</title>
    <filename>group__oneminus.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::oneminus</name>
      <anchorfile>group__oneminus.html</anchorfile>
      <anchor>gab3954d5d5676a222f8a1299d1e81ef40</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>pow</name>
    <title>kyosu::pow</title>
    <filename>group__pow.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::pow</name>
      <anchorfile>group__pow.html</anchorfile>
      <anchor>ga7dbdb37a871fee43869ef23d10d6123f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>pow1p</name>
    <title>kyosu::pow1p</title>
    <filename>group__pow1p.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::pow1p</name>
      <anchorfile>group__pow1p.html</anchorfile>
      <anchor>ga216a8b0ad2c118df71788014b7587f8c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>pow_abs</name>
    <title>kyosu::pow_abs</title>
    <filename>group__pow__abs.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::pow_abs</name>
      <anchorfile>group__pow__abs.html</anchorfile>
      <anchor>ga58e709793c8f3b413516867b44f3010b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>powm1</name>
    <title>kyosu::powm1</title>
    <filename>group__powm1.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::powm1</name>
      <anchorfile>group__powm1.html</anchorfile>
      <anchor>gab8e3f77af87791f809ac6cb9e95b38f9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>proj</name>
    <title>kyosu::proj</title>
    <filename>group__proj.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::proj</name>
      <anchorfile>group__proj.html</anchorfile>
      <anchor>gada630e85053aac1a1b0b53e89e5369f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>pure</name>
    <title>kyosu::pure</title>
    <filename>group__pure.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::pure</name>
      <anchorfile>group__pure.html</anchorfile>
      <anchor>gab1c81e9ddeb944ba56779a613452909b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>radinpi</name>
    <title>kyosu::radinpi</title>
    <filename>group__radinpi.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::radinpi</name>
      <anchorfile>group__radinpi.html</anchorfile>
      <anchor>gac3d481a9f480c463b7d66d720cba129d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>real</name>
    <title>kyosu::real</title>
    <filename>group__real.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::real</name>
      <anchorfile>group__real.html</anchorfile>
      <anchor>ga4121e4e64916c81e31b622b9b45c93fb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>rec</name>
    <title>kyosu::rec</title>
    <filename>group__rec.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::rec</name>
      <anchorfile>group__rec.html</anchorfile>
      <anchor>ga8eac9efc63807af3af63afdc1df00785</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>reldist</name>
    <title>kyosu::reldist</title>
    <filename>group__reldist.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::reldist</name>
      <anchorfile>group__reldist.html</anchorfile>
      <anchor>ga46d7f251fffedca76fef7a5c414fe700</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>reverse_horner</name>
    <title>kyosu::reverse_horner</title>
    <filename>group__reverse__horner.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::reverse_horner</name>
      <anchorfile>group__reverse__horner.html</anchorfile>
      <anchor>ga5db28dd284ecca661abaf0e79fe57126</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>rising_factorial</name>
    <title>kyosu::rising_factorial</title>
    <filename>group__rising__factorial.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::rising_factorial</name>
      <anchorfile>group__rising__factorial.html</anchorfile>
      <anchor>gaaae6b536a41451b5fe9ddc49def87bc2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>rot_angle</name>
    <title>kyosu::rot_angle</title>
    <filename>group__rot__angle.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::rot_angle</name>
      <anchorfile>group__rot__angle.html</anchorfile>
      <anchor>ga5a036cb7181db5317fee9c8359fe901b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>rot_axis</name>
    <title>kyosu::rot_axis</title>
    <filename>group__rot__axis.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::rot_axis</name>
      <anchorfile>group__rot__axis.html</anchorfile>
      <anchor>gadb3618e47c65a49d20d4a926b6d63233</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>rotate_vec</name>
    <title>kyosu::rotate_vec</title>
    <filename>group__rotate__vec.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::rotate_vec</name>
      <anchorfile>group__rotate__vec.html</anchorfile>
      <anchor>gafc749b146c3a5d756fc81c80e9b77d74</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>rsqrt</name>
    <title>kyosu::rsqrt</title>
    <filename>group__rsqrt.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::rsqrt</name>
      <anchorfile>group__rsqrt.html</anchorfile>
      <anchor>ga82c0404434b20d982247a9918ea7169b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sec</name>
    <title>kyosu::sec</title>
    <filename>group__sec.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sec</name>
      <anchorfile>group__sec.html</anchorfile>
      <anchor>gaf6e629a6211e4830fa9be0b06e57cef2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sech</name>
    <title>kyosu::sech</title>
    <filename>group__sech.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sech</name>
      <anchorfile>group__sech.html</anchorfile>
      <anchor>ga3eee368746f4dd2ba15c916dd177810d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sign</name>
    <title>kyosu::sign</title>
    <filename>group__sign.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sign</name>
      <anchorfile>group__sign.html</anchorfile>
      <anchor>ga67b994823617f74ac451898540a4dec7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>signnz</name>
    <title>kyosu::signnz</title>
    <filename>group__signnz.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::signnz</name>
      <anchorfile>group__signnz.html</anchorfile>
      <anchor>ga97b7c90af61b1ac3e294eb76a15488f6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sin</name>
    <title>kyosu::sin</title>
    <filename>group__sin.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sin</name>
      <anchorfile>group__sin.html</anchorfile>
      <anchor>ga02b482e44325ab868b423995a9cf9df2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sinc</name>
    <title>kyosu::sinc</title>
    <filename>group__sinc.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sinc</name>
      <anchorfile>group__sinc.html</anchorfile>
      <anchor>ga1ebadf9b1b77b65b5442b382a3e4a467</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sincos</name>
    <title>kyosu::sincos</title>
    <filename>group__sincos.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sincos</name>
      <anchorfile>group__sincos.html</anchorfile>
      <anchor>ga958b55049cd0ec20b14095b4b158c362</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sinh</name>
    <title>kyosu::sinh</title>
    <filename>group__sinh.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sinh</name>
      <anchorfile>group__sinh.html</anchorfile>
      <anchor>gaf9f5e943d59c79fd5f95be7df3ddbb3d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sinhc</name>
    <title>kyosu::sinhc</title>
    <filename>group__sinhc.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sinhc</name>
      <anchorfile>group__sinhc.html</anchorfile>
      <anchor>ga7d61257b252a395e77340de641a0fcfa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sinhcosh</name>
    <title>kyosu::sinhcosh</title>
    <filename>group__sinhcosh.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sinhcosh</name>
      <anchorfile>group__sinhcosh.html</anchorfile>
      <anchor>ga5ec18c46ae86e146614c7b573f146e37</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>slerp</name>
    <title>kyosu::slerp</title>
    <filename>group__slerp.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::slerp</name>
      <anchorfile>group__slerp.html</anchorfile>
      <anchor>ga1bc2cb0004a3b7a58fd9514247031b7f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sqr</name>
    <title>kyosu::sqr</title>
    <filename>group__sqr.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sqr</name>
      <anchorfile>group__sqr.html</anchorfile>
      <anchor>ga341e48919690498ce1a6cac915b3e58d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sqr_abs</name>
    <title>kyosu::sqr_abs</title>
    <filename>group__sqr__abs.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sqr_abs</name>
      <anchorfile>group__sqr__abs.html</anchorfile>
      <anchor>ga3ec084980c244c7393b5c039d69c4aa5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sqrt</name>
    <title>kyosu::sqrt</title>
    <filename>group__sqrt.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sqrt</name>
      <anchorfile>group__sqrt.html</anchorfile>
      <anchor>ga2281638c0373dd457ae6394e159a0010</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>sub</name>
    <title>kyosu::sub</title>
    <filename>group__sub.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::sub</name>
      <anchorfile>group__sub.html</anchorfile>
      <anchor>gacc787c1065460b8a8dae30ebdcdceefa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tan</name>
    <title>kyosu::tan</title>
    <filename>group__tan.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::tan</name>
      <anchorfile>group__tan.html</anchorfile>
      <anchor>ga922fad56b650ca766023b577bb08468a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tanh</name>
    <title>kyosu::tanh</title>
    <filename>group__tanh.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::tanh</name>
      <anchorfile>group__tanh.html</anchorfile>
      <anchor>ga78d8caa0d963138de3b8d7fa35bf9e6b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tchebytchev</name>
    <title>kyosu::tchebytchev</title>
    <filename>group__tchebytchev.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::tchebytchev</name>
      <anchorfile>group__tchebytchev.html</anchorfile>
      <anchor>ga232dd9d3384156fd6187ecf8f9d62e2b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tgamma</name>
    <title>kyosu::tgamma</title>
    <filename>group__tgamma.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::tgamma</name>
      <anchorfile>group__tgamma.html</anchorfile>
      <anchor>ga2592a73fafd38f5dcff68431ce527a41</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tgamma_inv</name>
    <title>kyosu::tgamma_inv</title>
    <filename>group__tgamma__inv.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::tgamma_inv</name>
      <anchorfile>group__tgamma__inv.html</anchorfile>
      <anchor>ga870e7b641a8fd3301736f1c0a545a092</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_angle_axis</name>
    <title>kyosu::to_angle_axis</title>
    <filename>group__to__angle__axis.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::to_angle_axis</name>
      <anchorfile>group__to__angle__axis.html</anchorfile>
      <anchor>ga4ab51b43625e09149d9614a764c205c6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_complex</name>
    <title>kyosu::to_complex</title>
    <filename>group__to__complex.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::complex</name>
      <anchorfile>group__to__complex.html</anchorfile>
      <anchor>gad34d6e0109b4b00e61a647cac6197786</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_cylindrical</name>
    <title>kyosu::to_cylindrical</title>
    <filename>group__to__cylindrical.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::to_cylindrical</name>
      <anchorfile>group__to__cylindrical.html</anchorfile>
      <anchor>ga75b1e4452fa2f7e46268981fac1e63e4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_cylindrospherical</name>
    <title>kyosu::to_cylindrospherical</title>
    <filename>group__to__cylindrospherical.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::to_cylindrospherical</name>
      <anchorfile>group__to__cylindrospherical.html</anchorfile>
      <anchor>ga42961187254bc61f724610896d63ddca</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_euler</name>
    <title>kyosu::to_euler</title>
    <filename>group__to__euler.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::to_euler</name>
      <anchorfile>group__to__euler.html</anchorfile>
      <anchor>gae7eecc3a7b0016fa20207efb5cd4b12a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_multipolar</name>
    <title>kyosu::to_multipolar</title>
    <filename>group__to__multipolar.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::to_multipolar</name>
      <anchorfile>group__to__multipolar.html</anchorfile>
      <anchor>ga37dfba013d9e8f32d84fed33e7c27032</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_polar</name>
    <title>kyosu::to_polar</title>
    <filename>group__to__polar.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::to_polar</name>
      <anchorfile>group__to__polar.html</anchorfile>
      <anchor>ga142fe18a19d74983fd0b09aeeb18ed8b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_quaternion</name>
    <title>kyosu::to_quaternion</title>
    <filename>group__to__quaternion.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::quaternion</name>
      <anchorfile>group__to__quaternion.html</anchorfile>
      <anchor>ga74ebf9f07f4d05907402cdf7844990d8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_rotation_matrix</name>
    <title>kyosu::to_rotation_matrix</title>
    <filename>group__to__rotation__matrix.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::to_rotation_matrix</name>
      <anchorfile>group__to__rotation__matrix.html</anchorfile>
      <anchor>ga50cf8709672a806974dc93f77c0d6e5b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_semipolar</name>
    <title>kyosu::to_semipolar</title>
    <filename>group__to__semipolar.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::to_semipolar</name>
      <anchorfile>group__to__semipolar.html</anchorfile>
      <anchor>gafd4bfbd92bfffcca410f3b739923c49a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>to_spherical</name>
    <title>kyosu::to_spherical</title>
    <filename>group__to__spherical.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::to_spherical</name>
      <anchorfile>group__to__spherical.html</anchorfile>
      <anchor>gaff0907e49def12a25b3b86b06a10eb87</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tricomi</name>
    <title>kyosu::tricomi</title>
    <filename>group__tricomi.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::tricomi</name>
      <anchorfile>group__tricomi.html</anchorfile>
      <anchor>ga647fd208e837755628ead583aec3f21e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>trunc</name>
    <title>kyosu::trunc</title>
    <filename>group__trunc.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::trunc</name>
      <anchorfile>group__trunc.html</anchorfile>
      <anchor>ga963040c6c665a0d17451be2b2fcf68c5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>xi</name>
    <title>kyosu::xi</title>
    <filename>group__xi.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::xi</name>
      <anchorfile>group__xi.html</anchorfile>
      <anchor>gacb395fe97c9b0425cd25698db9dc2ef0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>zeta</name>
    <title>kyosu::zeta</title>
    <filename>group__zeta.html</filename>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>kyosu::zeta</name>
      <anchorfile>group__zeta.html</anchorfile>
      <anchor>ga9dc4aaaee99fe3a698b09d2c63850d66</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>changelog</name>
    <title>Changelog</title>
    <filename>changelog.html</filename>
    <docanchor file="changelog.html" title="/__w/kyosu/kyosu/doc/changelog.md">md__2____w_2kyosu_2kyosu_2doc_2changelog</docanchor>
  </compound>
  <compound kind="page">
    <name>licence</name>
    <title>Licence</title>
    <filename>licence.html</filename>
    <docanchor file="licence.html" title="/__w/kyosu/kyosu/doc/licence.md">md__2____w_2kyosu_2kyosu_2doc_2licence</docanchor>
  </compound>
  <compound kind="page">
    <name>setup</name>
    <title>Installation &amp; Quick Start</title>
    <filename>setup.html</filename>
    <docanchor file="setup.html" title="/__w/kyosu/kyosu/doc/setup.md">md__2____w_2kyosu_2kyosu_2doc_2setup</docanchor>
  </compound>
  <compound kind="page">
    <name>tutorial-complex</name>
    <title>Complex numbers</title>
    <filename>tutorial-complex.html</filename>
  </compound>
  <compound kind="page">
    <name>tutorial-simd</name>
    <title>Many values at once</title>
    <filename>tutorial-simd.html</filename>
  </compound>
  <compound kind="page">
    <name>tutorial-quaternion</name>
    <title>Quaternions</title>
    <filename>tutorial-quaternion.html</filename>
  </compound>
  <compound kind="page">
    <name>tutorial-rotation</name>
    <title>Rotations</title>
    <filename>tutorial-rotation.html</filename>
  </compound>
  <compound kind="page">
    <name>tutorial-beyond</name>
    <title>Octonions and beyond</title>
    <filename>tutorial-beyond.html</filename>
  </compound>
  <compound kind="page">
    <name>tutorial-options</name>
    <title>Options</title>
    <filename>tutorial-options.html</filename>
  </compound>
  <compound kind="page">
    <name>biblio</name>
    <title>Bibliography</title>
    <filename>biblio.html</filename>
    <docanchor file="biblio.html" title="/__w/kyosu/kyosu/doc/biblio.md">md__2____w_2kyosu_2kyosu_2doc_2biblio</docanchor>
  </compound>
  <compound kind="page">
    <name>building</name>
    <title>Building for Testing</title>
    <filename>building.html</filename>
    <docanchor file="building.html" title="/__w/kyosu/kyosu/doc/building.md">md__2____w_2kyosu_2kyosu_2doc_2building</docanchor>
  </compound>
  <compound kind="page">
    <name>math_background</name>
    <title>Mathematics of Cayley-Dickson Algebras</title>
    <filename>math_background.html</filename>
    <docanchor file="math_background.html" title="/__w/kyosu/kyosu/doc/math.md">md__2____w_2kyosu_2kyosu_2doc_2math</docanchor>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>SIMD-Aware Cayley-Dickson Algebras</title>
    <filename>index.html</filename>
  </compound>
</tagfile>
