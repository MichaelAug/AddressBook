#include "addressBook.hpp"
#include "gtest/gtest.h"

class AddressBookTestFixture : public ::testing::Test {
protected:
  void SetUp() override {}
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

  // Contact is taken by copy so c can be referenced later
  b.addContact(c);

  EXPECT_EQ(b.contactsByFirstName(), std::vector<Contact>{c});
}

TEST_F(AddressBookTestFixture, RetrieveContactsSortedByFirstName) {
  AddressBook b;

  std::vector<Contact> contacts = {{"aaaaaa", "Doe"}, {"bbbbbb", "Doe"}, {"cccccc", "Doe"}};

  // Add contacts in random order
  b.addContact(contacts[1]);
  b.addContact(contacts[2]);
  b.addContact(contacts[0]);

  EXPECT_EQ(b.contactsByFirstName(), contacts);
}

TEST_F(AddressBookTestFixture, RetrieveContactsSortedByLastName) {
  AddressBook b;

  std::vector<Contact> contacts = {{"aaaaaa", "ddddd"}, {"cccccc", "eeeee"}, {"bbbbbb", "ff"}};

  // Add contacts in random order
  b.addContact(contacts[2]);
  b.addContact(contacts[0]);
  b.addContact(contacts[1]);

  EXPECT_EQ(b.contactsByLastName(), contacts);
}