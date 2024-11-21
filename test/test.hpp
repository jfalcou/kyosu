//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#define TTS_MAIN
#define TTS_CUSTOM_DRIVER_FUNCTION kyosu_entry_point
#include <tts/tts.hpp>

//==================================================================================================
// EVE Speci1fic testing overloads
//==================================================================================================
#include <eve/arch/fundamental_cardinal.hpp>
#include <eve/module/core.hpp>
#include <eve/traits.hpp>
#include <eve/wide.hpp>
#include <kyosu/kyosu.hpp>

namespace eve
{
  template<typename T, typename N>
  inline bool compare_equal(wide<T, N> const &l, wide<T, N> const &r)
  {
    return eve::all(l == r);
  }

  template<typename T>
  inline bool compare_equal(logical<T> const &l, logical<T> const &r)
  {
    if constexpr(eve::simd_value<T>)  return eve::all(l == r);
    else                              return l == r;
  }
}

namespace eve::detail
{
  template<typename T, typename V> auto as_value(callable_object<V> const& v)
  {
    return v(eve::as<T>{});
  }
}

namespace kyosu
{
  using scalar_real_types   = tts::types< float, double>;
  using simd_real_types     = tts::types< eve::wide<float>, eve::wide<double>
                                        , eve::wide<float , eve::wide<float>::cardinal_type::combined_type>
                                        , eve::wide<double, eve::wide<double>::cardinal_type::combined_type>
                                        >;
  using real_types          = tts::concatenate_t<scalar_real_types, simd_real_types>;

  template<typename T>    struct tts_complex_t;
  template<typename... T> struct tts_complex_t<tts::types<T...>> { using types_list = tts::types<complex_t<T>...>; };

  using scalar_complex_types = tts_complex_t<scalar_real_types>;
  using simd_complex_types   = tts_complex_t<simd_real_types>;
  using complex_types        = tts_complex_t<real_types>;
}

//==================================================================================================
// KYOSU TTS Entrypoint
//==================================================================================================
#include <iostream>

int main(int argc, char const **argv)
{
  ::tts::initialize(argc,argv);
  auto seed = ::tts::random_seed(18102008);
#ifdef NDEBUG
  constexpr auto assert_status = "Disabled";
#else
  constexpr auto assert_status = "Enabled";
#endif

  std::cout << "[KYOSU] - Target: " << eve::current_api
            << " - Assertions: "    << assert_status
            << " - PRNG Seed: "     << seed
            << std::endl;

  kyosu_entry_point(argc, argv);
  return tts::report(0,0);
}

namespace tts
{
  template<typename T> struct bunch
  {
    template<typename L> struct make;
    template<typename... Ls> struct make<tts::types<Ls...>>
    {
      using type = tts::types<std::array<Ls,10>...>;
    };

    using types_list = typename make<T>::type;
  };

  template<typename T>
  inline bool compare_equal(eve::logical<T> const &l, eve::logical<T> const &r)
  {
    if constexpr(eve::simd_value<T>)  return eve::all(l == r);
    else                              return l == r;
  }

  template<kyosu::concepts::cayley_dickson T> inline bool is_ieee_equal(T const &l, T const &r)
  {
    return kumi::all_of(kumi::map( [](auto a, auto b) { return tts::is_ieee_equal(a,b); }, l, r));
  }

  template<typename T, typename N>
  inline bool is_ieee_equal(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    bool check = true;
    for(auto i = 0; i < l.size(); ++i)
      check = check && tts::is_ieee_equal(l.get(i), r.get(i));

    return check;
  }

  template<kyosu::concepts::cayley_dickson T> double relative_distance(T const &l, T const &r)
  {
    return kyosu::reldist[eve::numeric](l, r);
  }

  template<kyosu::concepts::cayley_dickson T> double absolute_distance(T const &l, T const &r)
  {
    if(is_ieee_equal(l, r))
      return 0.0;
    else
      return kyosu::dist(l, r);
  }

  template<typename T, typename N>
  inline double ulp_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, ulp_distance(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template<typename T, typename N>
  inline double relative_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, relative_distance(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template<typename T, typename N>
  inline double absolute_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, absolute_distance(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template <typename T> inline double constexpr prec()
  {
    if constexpr( sizeof(eve::element_type_t<T>) == 4) return 1.0e-3; else return 1.0e-6;
  }

  template <typename T> inline double constexpr prec(double f,  double d)
  {
    if constexpr( sizeof(eve::element_type_t<T>) == 4) return f; else return d;
  }

  //================================================================================================
  // Poison wide data when using sub-sized types
  //================================================================================================
  template<eve::simd_value W> auto poison(W data)
  {
    using v_t = eve::element_type_t<W>;

    // Add garbage at the end of sub-native registers
    // For emulated type, there is no such gap so we don't do anything
    if constexpr( (W::size() < eve::fundamental_cardinal_v<v_t>) && !eve::has_emulated_abi_v<W> )
    {
      using p_t   = eve::as_arithmetic_t<eve::as_integer_t<v_t, unsigned>>;
      using ftype = eve::as_wide_t<v_t, eve::fundamental_cardinal_t<v_t>>;

      ftype these(data.storage());

      // Compute a recognizable filler
      for(std::ptrdiff_t i=data.size();i<these.size();++i)
      {
        p_t filler = eve::constant<p_t, static_cast<p_t>(0xDEADBEEFBABE0000)>() + p_t(i);
        these.set(i, eve::bit_cast(filler,eve::as<v_t>()) );
      }

      return W(these.storage());
    }
    else
    {
      return data;
    }
  }

  //================================================================================================
  // Customization point for argument building
  //================================================================================================
  template<eve::simd_value T>
  auto produce(type<T> const&, auto g, auto& rng, auto... args)
  {
    using e_t = eve::element_type_t<T>;
    auto data = produce(type<std::array<e_t,T::size()>>{},g,rng, args...);

    using v_t = typename decltype(data)::value_type;
    eve::as_wide_t<v_t, eve::cardinal_t<T>> that = eve::load(&data[0], eve::cardinal_t<T>{});

    return poison(that);
  }
}
