#include "gtest/gtest.h"

class AddressBookTestFixture : public ::testing::Test {
protected:
  void SetUp() override {
    
  }
};

TEST_F(AddressBookTestFixture, firstTest) {
  EXPECT_EQ(1, 2);
}