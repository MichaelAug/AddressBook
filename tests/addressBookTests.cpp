#include "gtest/gtest.h"

class AddressBookTestFixture : public ::testing::Test {
protected:
  void SetUp() override {
    
  }
};

TEST_F(AddressBookTestFixture, CreateContact) {
  Contact c = Contact("Jane", "Doe", "123145235");

  EXPECT_EQ(c.firstName, "Jane");
  EXPECT_EQ(c.lastName, "Doe");
  EXPECT_EQ(c.phone, "123145235");
}