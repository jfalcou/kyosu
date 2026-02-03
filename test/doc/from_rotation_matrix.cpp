#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::from_rotation_matrix;
  using kyosu::quaternion_t;
  using kyosu::to_rotation_matrix;
  using q_t = kyosu::quaternion_t<float>;

  std::cout << "Quaternion:  " << "\n";
  q_t q0(1, 5, 2, 3);
  q0 = kyosu::sign(q0); // normalization is optional
  auto m = to_rotation_matrix(q0);
  std::cout << "q0 =  " << q0 << std::endl;
  std::cout << "m = to_rotation_matrix(q0) = \n";
  for (int i = 0; i < 3; ++i)
  {
    std::cout << "    ";
    for (int j = 0; j < 2; ++j) { std::cout << m[i][j] << ", "; }
    std::cout << m[i][2] << "\n";
  }
  std::cout << "from_rotation_matrix(m) =  " << from_rotation_matrix(m) << std::endl;

  return 0;
}
