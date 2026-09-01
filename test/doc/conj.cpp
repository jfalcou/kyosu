#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::conj;
  using kyosu::quaternion_t;

  std::cout << "Real:        ";
  std::cout << 72.9f << " -> " << conj(72.9f) << "\n";

  std::cout << "Complex:     \n";
  using c_t = kyosu::complex_t<float>;
  using wc_t = eve::wide<c_t, eve::fixed<4>>;
  c_t a   = c_t(3.5f, -2.9f);
  c_t b   = c_t(3.5f,  2.9f);
  c_t a0  = c_t(3.5f,  0.0f);
  c_t am0 = c_t(3.5f, -0.0f);
  std::cout << a   <<     " conj->                     " << conj(a) << "\n";
  std::cout << b   <<     " conj->                     " << conj(b) << "\n";
  std::cout << a0  <<     "   conj->                     " << conj(a0) << "\n";
  std::cout << am0 <<     "   conj->                     " << conj(am0) << "\n";
  auto wa = wc_t(a, b, a0, am0);
  std::cout << wa << " conj->                          " << conj(wa) << "\n";
  std::cout << wa << " conj[kyosu::is_not_real] ->     " << conj[kyosu::is_not_real(wa)](wa) << "\n";

  std::cout << "Quaternion:  \n";
  std::cout << kyosu::quaternion_t<double>(1., 2., 3., 4.) << " conj -> "
            << conj(kyosu::quaternion_t<double>(1., 2., 3., 4.)) << "\n";

  return 0;
}
