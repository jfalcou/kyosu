#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::to_rotation_matrix;
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using q_t = kyosu::quaternion_t<float>;


  std::cout << "Quaternion:  "<< "\n";
  q_t q0(1, 5, 2, 3);
  auto m = to_rotation_matrix(q0, kyosu::normalize);
  std::cout << "q0 =  " << q0 << std::endl;
  std::cout << "to_rotation_matrix(q0) = \n";
  for(int i=0; i <3 ; ++i)
  {
    std::cout << "    ";
    for(int j=0; j < 2 ; ++j)
    {
      std::cout << m[i][j] << ", ";
    }
    std::cout << m[i][2] << "\n";
  }
  return 0;
}
