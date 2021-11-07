#include "Eigen/Dense"
#include "gtest/gtest.h"

TEST(EigenTest, CanCompile) {
  Eigen::MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);

  EXPECT_EQ(1.5, m(1, 1));
}
