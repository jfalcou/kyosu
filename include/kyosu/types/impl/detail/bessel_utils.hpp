//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <type_traits>
#include <vector>
namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  // bound
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto bound(Z const & z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    return int(eve::ceil(eve::maximum(abs(z)*u_t(1.1)+2)));
  }

  //===-------------------------------------------------------------------------------------------
  // R use lentz
  //===-------------------------------------------------------------------------------------------
  template <typename Gen>
  struct fraction_traits_simple
  {
    using  value_type = typename Gen::result_type;
    using result_type = typename Gen::result_type;
    using scalar_type = typename Gen::scalar_type;

    static result_type a(const value_type&) noexcept
    {
      return result_type(1);
    }
    static result_type b(const value_type& v) noexcept
    {
      return v;
    }

  };

  template <typename Gen>
  struct fraction_traits_pair
  {
    using value_type = typename Gen::value_type;
    using result_type = typename kumi::element<0, value_type>;
    using scalar_type = typename Gen::scalar_type;

    static result_type a(const value_type& v) noexcept
    {
      return kumi::get<1>(v);
    }
    static result_type b(const value_type& v) noexcept
    {
      return  kumi::get<0>(v);
    }
  };

  template <typename Gen>
  struct fraction_traits
    : std::conditional_t<
    std::same_as<typename Gen::result_type, typename Gen::value_type>,
    fraction_traits_simple<Gen>,
    fraction_traits_pair<Gen>>
  {
  };

  template <typename Gen, typename U>
  inline auto lentz_b(Gen& g, const U& eps, size_t const& max_terms = 1000) noexcept
  {
    using traits = fraction_traits<Gen>;
    using value_type = typename traits::value_type;
    using result_type = typename traits::result_type;
    using scalar_type = typename traits::scalar_type;
    using u_t =  scalar_type;

    u_t tiny = 16*eve::smallestposval(eve::as<u_t>()) ;
    u_t terminator(eps);
    constexpr auto b_only = std::same_as<result_type, value_type>;

    auto v = g();

    result_type f, C, delta;
    f = traits::b(v);
    //   if constexpr(b_only)
//    {
//      f = kyosu::if_else(kyosu::is_eqz(v), tiny, v) ;
//    }
//    else
//    {
//      f = kyosu::if_else(kyosu::is_eqz(kumi::get<0>(v)), tiny, kumi::get<0>(v)) ;
//    }
    C = f;
    result_type   D{}; //(u_t(0));

    std::uintmax_t counter(max_terms);
    do{
      v = g();
      if constexpr(b_only)
      {
        D = v +  D;
        C = v + kyosu::rec(C);
      }
      else
      {
        D = kumi::get<0>(v) + kumi::get<1>(v) * D;
        C = kumi::get<0>(v) + kumi::get<1>(v) / C;
      }
      D = kyosu::if_else(kyosu::is_eqz(D), tiny, D);
      C = kyosu::if_else(kyosu::is_eqz(C), tiny, C);
      D = kyosu::rec(D);
      delta = C*D;
      f = f * delta;
    } while(eve::any((kyosu::abs(kyosu::dec(delta)) > terminator) && --counter));
    g.reset();
    return f;
  }

  template <class T>
  struct R_estimate
  {
    using result_type = T;
    using value_type  = T;
    using scalar_type  = eve::underlying_type_t<T>;

    int n;
    T rz;
    int i;
    int sgn;

    R_estimate(size_t n_, T z_)
      : n(n_), rz(kyosu::rec(z_))
    {
      reset();
    }

    void reset()
    {
      i = 0; sgn = -1;
    }

    value_type operator()()
    {
      sgn = -sgn;
      ++i;
      auto r = sgn*2*(n+i-1)*rz;
      return r;
    }
  };

  template<typename Z>
  inline auto R(size_t n, Z z) noexcept
  // compute the ratio Jn(n, z)/Jn(n-1, z)J
  {
    using u_t = eve::underlying_type_t<Z>;
    R_estimate re(n, z);
    auto r = lentz_b(re, eve::eps(eve::as<u_t>()));
    return r;
  }

//   template<typename Z>
//   inline auto R(size_t n, size_t p, Z z) noexcept
//   // compute the ratio Jn(n, z)/Jp(n-1, z)J
//   {
//     using u_t = eve::underlying_type_t<Z>;
//     if (is_eqz(n)) return Z(eve::nan(as<u_t>()));
//     if (n == p)    return Z(eve::one(as<u_t>()));
//     Z r{}, s{};
//     auto rz = rec(z);
//     auto rn = R(n, z);
//     for(int i=n-1; i > p; --i)
//     {
//       rn = 2*i*rz-rec(rn);
//       pri *= rn;
//     }
//     return lri;
//   }


  template<typename Z>
  inline auto Rs(size_t n, Z z) noexcept
  // compute the ratio Jn(i, z)/Jn(i-1, z)J for i = n:-1:1
  {
    std::vector<Z> rs(n);
    using u_t = eve::underlying_type_t<Z>;
    if (is_eqz(n)) return rs;
    Z r{}, s{};
    auto rz = rec(z);
    rs[n-1] = R(n, z);
    for(int i=n-1; i >= 1; --i)
    {
      rs[i-1] = 2*i*rz-rec(rs[i]);
    }
    return rs;
  }


  template<typename Z>
  inline auto arg_adjust(Z z) noexcept
  // modify ipart of z modulo 2*pi fit in ]-pi +pi]
  {
    if constexpr(kyosu::concepts::complex<Z>)
    {
      ipart(z) = eve::to_nearest(eve::rem)(ipart(z), 2*eve::pi(eve::as(ipart(z))));
      return z;
    }
    else  return z;
  }

}
