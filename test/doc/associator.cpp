#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::associator;
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using o_t = kyosu::octonion_t<float>;

  std::cout << "Real:        " << "\n";
  e_t e0(1);
  e_t e1(2);
  e_t e2(3);
  std::cout << e0 << ", " << e1 << ", " << e2 << " -> " << associator(e0, e1, e2) << "\n";

  std::cout << "Complex:     " << "\n";
  c_t c0(1, 5);
  c_t c1(5, 9);
  c_t c2(-1, 4);
  std::cout << c0 << ", " << c1 << ", " << c2 << " -> " << associator(c0, c1, c2) << "\n";

  std::cout << "Quaternion:  " << "\n";
  q_t q0(1, 5, -2, 3);
  q_t q1(5, 9, 6, 7);
  q_t q2(-3, 6, -1, 0);
  std::cout << q0 << ", " << q1 << ", " << q2 << " -> " << associator(q0, q1, q2) << "\n";

  std::cout << "Octonion:  " << "\n";
  o_t o0(1, 5, -2, 3, 4, 8, 13, 1);
  o_t o1(5, 9, 6, 7, 6, -4, -1, 2);
  o_t o2(-3, 6, -1, 0, 4, 5, -8, 2);

  std::cout << o0 << ", " << o1 << ", " << o2 << " -> " << associator(o0, o1, o2) << "\n";
  std::cout << "Mixed:  " << "\n";
  std::cout << kyosu::associator(c0, o1, o2) << std::endl;
  std::cout << kyosu::associator(o0, o1, e0) << std::endl;

  return 0;
}
