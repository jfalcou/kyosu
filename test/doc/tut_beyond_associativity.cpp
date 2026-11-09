#include <iostream>
#include <kyosu/kyosu.hpp>

using o_t = kyosu::octonion_t<double>;
template<int N> o_t e() { o_t z{}; kyosu::get<N>(z) = 1.; return z; }

int main()
{
  auto a = e<1>(), b = e<2>(), c = e<4>();

  std::cout << "(ab)c            = " << (a*b)*c << "\n";
  std::cout << "a(bc)            = " << a*(b*c) << "\n";
  std::cout << "associator       = " << kyosu::associator(a, b, c) << "\n";

  // On quaternions the associator vanishes: they are associative.
  auto p = kyosu::quaternion_t<double>(1., 2., 3., 4.);
  auto q = kyosu::quaternion_t<double>(0., 1., -1., 2.);
  auto r = kyosu::quaternion_t<double>(3., 0., 1., 1.);
  std::cout << "on quaternions   = " << kyosu::associator(p, q, r) << "\n";
}
