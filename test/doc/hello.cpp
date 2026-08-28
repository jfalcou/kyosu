#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::octonion_t;
  using kyosu::quaternion_t;

  // The same function, over three algebras of growing dimension.
  auto c = complex_t<double>(1., 2.);
  auto q = quaternion_t<double>(1., 2., 3., 4.);
  auto o = octonion_t<double>(1., 2., 3., 4., 5., 6., 7., 8.);

  std::cout << "complex:    " << c << " -> exp " << kyosu::exp(c) << "\n";
  std::cout << "quaternion: " << q << " -> exp " << kyosu::exp(q) << "\n";
  std::cout << "octonion:   " << o << " -> exp " << kyosu::exp(o) << "\n";

  // Dimensions mix freely, the widest one wins.
  std::cout << "\nc + q     = " << c + q << "\n";
  std::cout << "q * o     = " << q * o << "\n";

  // And every one of them vectorizes, without changing a line of the maths.
  using wq_t = eve::wide<quaternion_t<double>, eve::fixed<2>>;
  wq_t w(q);
  std::cout << "\nSIMD quaternion: " << w << "\n";
  std::cout << "            exp: " << kyosu::exp(w) << "\n";

  return 0;
}
