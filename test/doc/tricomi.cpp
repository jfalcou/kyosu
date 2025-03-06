#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  auto eps = eve::eps(eve::as(1.0))*1024;
  auto ops = 1.0+eps;
 auto I = kyosu::complex(0.0, 1.0);
//   std::cout << "tricomi(2.0, 1, 1.5)         "<< kyosu::tricomi(2.0, 1, 1.5)        << std::endl;
//   std::cout << "tricomi(2.0, 1, I)           "<< kyosu::tricomi(2.0, 1, I)          << std::endl;
  std::cout << "tricomi( 1.72725307941437, 1.0, 1.0)  "<< kyosu::tricomi( 1.72725307941437, 1.0, 1.0)        << std::endl;
  std::cout << "tricomi( 1.72725307941437, 1.0, 1.0+I*eps)  "<< kyosu::tricomi( 1.72725307941437, 1.0, 1.0+I*eps)        << std::endl;
  std::cout << "tricomi( 1.72725307941437, 1.0, ops)  "<< kyosu::tricomi( 1.72725307941437, 1.0, ops)        << std::endl;
  std::cout << "tricomi( 1.72725307941437, 1., 1.00001)  "<< kyosu::tricomi( 1.72725307941437, 1., 1.00001)        << std::endl;
//   std::cout << "tricomi( 1.72725307941437, -1.0, -1.0)  "<< kyosu::tricomi( 1.72725307941437, -1.0, -1.0)        << std::endl;
//   std::cout << "tricomi( 1.72725307941437, -1.00001, -1.00001)  "<< kyosu::tricomi( 1.72725307941437, -1.00001, -1.00001)        << std::endl;
  return 0;
}
