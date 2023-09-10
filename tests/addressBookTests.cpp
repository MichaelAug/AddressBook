#include "gtest/gtest.h"
#include "contact.hpp"

class AddressBookTestFixture : public ::testing::Test {
protected:
  void SetUp() override {
    
  }
};

TEST_F(AddressBookTestFixture, CreateContact) {
  Contact c = {"Jane", "Doe", "123145235"};

  EXPECT_EQ(c.firstName, "Jane");
  EXPECT_EQ(c.lastName, "Doe");
  EXPECT_EQ(c.phone, "123145235");
}