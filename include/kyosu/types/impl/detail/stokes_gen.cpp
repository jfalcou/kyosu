//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <iostream>
#include <array>
#include <utility>

  // These routines are not used
  // They were used to generate the p and q coefficients of
  // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
  //  treatise on Bessel functions and their applications to
  //  physics, 1895.
  // They can be used anew if we implement bessel for more
  // accurate type in the future

  template < size_t Degree, typename T>
  auto stokes_gen(size_t nu) noexcept
  {
    // once p and q tabulated and given  the adapted value of n. considering a as
    // the coefficients of two polynomial in ascending power order. For large z (abs(z) > 12, real(z) > 0)
    // P(z) = p(rec(z*z)) and Q(z) = q(rec(z*z))/z
    // Jnu(z) ~ (c*P(z) + s*Q(z))/(sqrt(z*pi));
    // s = sin(zz) and c = cos(zz),  zz = z-nu.pi/2-pi/4
    constexpr size_t N = Degree+1u;
    T mu = 4*nu*nu;
    std::array<T, 2*N> a;
    std::array<T, N> p, q;
    a[0] = T(1);
    for(size_t i=1; i < 2*N ; ++i)
    {
      auto ii = 2*i-1;
      auto ii2 = ii*ii;
      a[i] = a[i-1]*(ii2-mu)/(8*i);
    }
    T sgn(1);
    for(size_t i=0; i < N ; ++i)
    {
      p[i] = sgn*a[2*i];
      q[i] = sgn*a[2*i+1];
      sgn = -sgn;
    }
    return std::pair{p, q};
  }

auto pr = [](auto name, auto p){
  std::cout.precision(16); 
  std::cout << name << "\n{" << std::scientific; ;
  for(size_t i=0; i < p.size(); ++i)
 {
   std::cout << p[i];
   if(i != p.size()-1) std::cout << ",  ";
   if(i%4 == 0) std::cout << "\n  ";
 }
  std::cout << "\n}; ";

};

int main()
{
  auto [p, q] = stokes_gen<14, double>(0u);
  pr("p =  ", p);
  pr("q =  ", q);
}
