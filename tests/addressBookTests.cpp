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

TEST_F(AddressBookTestFixture, ContactPhoneIsOptional) {
  Contact c = {"Jane", "Doe"};

  EXPECT_EQ(c.firstName, "Jane");
  EXPECT_EQ(c.lastName, "Doe");
  EXPECT_EQ(c.phone, "");
}

TEST_F(AddressBookTestFixture, AddAndRetrieveContactToAddressBook) {
  AddressBook b;
  Contact c = {"Jane", "Doe", "123145235"};

  // Contact is taken by copy so can be referenced later
  b.addContact(c);

  EXPECT_EQ(b.contactsByFirstName(), std::vector<Contact>{c});
}