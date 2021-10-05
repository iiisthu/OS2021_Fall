#include <gtest/gtest.h>
#include "utils.h"

namespace proj1 {
namespace testing{


TEST(UtilTest, test_sigmoid) {
    EXPECT_NEAR(0.731059, sigmoid(1.0), 0.0001);   
}

TEST(UtilTest, test_sigmoid_backward) {
    EXPECT_NEAR(0.196612, sigmoid_backward(1.0), 0.0001);   
}

} // namespace testing
} // namespace proj1

int main(int argc,char **argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
