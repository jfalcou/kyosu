#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using kyosu::to_angle_axis;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;

  std::cout << "Real:        " << "\n";
  e_t e0(1);
  auto [ae, axe] = to_angle_axis(e0);
  std::cout << e0 << " -> " << ae << ",  (" << axe[0] << ", " << axe[1] << ", " << axe[2]
            << ") "
               "\n";
  auto [aep, axep] = to_angle_axis[kyosu::radpi](e0);
  std::cout << e0 << " -> " << aep << ",  (" << axep[0] << ", " << axep[1] << ", " << axep[2]
            << ") "
               "\n";

  std::cout << "Complex:     " << "\n";
  c_t c0(1, 5);
  auto [ac, axc] = to_angle_axis(c0);
  std::cout << c0 << " -> " << ac << ",  (" << axc[0] << ", " << axc[1] << ", " << axc[2]
            << ") "
               "\n";
  auto [acp, axcp] = to_angle_axis[kyosu::radpi](c0);
  std::cout << c0 << " -> " << acp << ",  (" << axcp[0] << ", " << axcp[1] << ", " << axcp[2]
            << ") "
               "\n";

  std::cout << "Quaternion:  " << "\n";
  q_t q0(1, 5, 2, 3);
  auto [aq, axq] = to_angle_axis(q0);
  std::cout << q0 << " -> " << aq << ",  (" << axq[0] << ", " << axq[1] << ", " << axq[2]
            << ") "
               "\n";
  auto [aqp, axqp] = to_angle_axis[kyosu::radpi](q0);
  std::cout << q0 << " -> " << aqp << ",  (" << axqp[0] << ", " << axqp[1] << ", " << axqp[2]
            << ") "
               "\n";

  return 0;
}
