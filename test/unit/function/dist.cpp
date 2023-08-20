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
  c_t c1(4, 9);
  std::cout << c0 << ", " << c1 << " -> " << dist(c0, c1) << "\n";



  std::cout << "Quaternion:  "<< "\n";
  q_t q0(1, 5, 2, 3);
  q_t q1(5, 9, 6, 7);
  std::cout << q0 << ", " << q1 << " -> " << dist(q0, q1) << "\n";


  std::cout << "SIMD:        "<< "\n";
  using wq_t = eve::wide<quaternion<double>, eve::fixed<2>>;
  wq_t wq0(1, 5, 2, 3);
  wq_t wq1(5, 9, 6, 7);
  std::cout << wq0 << ", " << wq1 << " -> " << dist(wq0, wq1) << "\n";

  return 0;
}
