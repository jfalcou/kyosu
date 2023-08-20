#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::dist;
  using kyosu::complex;
  using kyosu::quaternion;
  using e_t = float;
  using c_t = complex<float>;
  using q_t = quaternion<float>;

  std::cout << "Real:        "<< "\n";
  e_t e0(1);
  e_t e1(2);
  std::cout << e0 << ", " << e1 << " -> " << dist(e0, e1) << "\n";

  std::cout << "Complex:     "<< "\n";
  c_t c0(1, 5);
  c_t c1(5, 9);
  std::cout << c0 << ", " << c1 << " -> " << dist(c0, c1) << "\n";



  std::cout << "Quaternion:  "<< "\n";
  q_t q0(1, 5);
  q_t q1(5, 9);
  std::cout << q0 << ", " << q1 << " -> " << dist(q0, q1) << "\n";


//   std::cout << "SIMD:        ";
//    using wc_t = eve::wide<complex<double>, eve::fixed<2>>;
//    std::cout << wc_t(complex<double>(1.3,-3.7)) << " -> " << dist(wc_t(complex<double>(1.3,-3.7))) << "\n";
//    std::cout << wc_t(complex<double>(1.3,-3.7)) << " -> " <<    (wc_t(complex<double>(1.3,-3.7)))*(wc_t(complex<double>(1.3,-3.7)))<< "\n";

  return 0;
}
