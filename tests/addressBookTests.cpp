#include "addressBook.hpp"
#include "gtest/gtest.h"

class AddressBookTestFixture : public ::testing::Test {
protected:
  void SetUp() override {}

  AddressBook addrBook;
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
  Contact c = {"Jane", "Doe", "123145235"};

  // Contact is taken by copy so c can be referenced later
  addrBook.addContact(c);

  EXPECT_EQ(addrBook.contactsByFirstName(), std::vector<Contact>{c});
}

TEST_F(AddressBookTestFixture, RetrieveContactsSortedByFirstName) {
  std::vector<Contact> contacts = {
      {"aaaaaa", "Doe"}, {"bbbbbb", "Doe"}, {"cccccc", "Doe"}};

  // Add contacts in random order
  addrBook.addContact(contacts[1]);
  addrBook.addContact(contacts[2]);
  addrBook.addContact(contacts[0]);

  EXPECT_EQ(addrBook.contactsByFirstName(), contacts);
}

TEST_F(AddressBookTestFixture, RetrieveContactsSortedByLastName) {
  std::vector<Contact> contacts = {
      {"aaaaaa", "ddddd"}, {"cccccc", "eeeee"}, {"bbbbbb", "ff"}};

  // Add contacts in random order
  addrBook.addContact(contacts[2]);
  addrBook.addContact(contacts[0]);
  addrBook.addContact(contacts[1]);

  EXPECT_EQ(addrBook.contactsByLastName(), contacts);
}

TEST_F(AddressBookTestFixture, AddAndRemoveContact) {
  addrBook.addContact({"bbbbbb", "ff"});
  addrBook.addContact({"aaaaaa", "ddddd"});
  addrBook.addContact({"cccccc", "eeeee"});

  EXPECT_EQ(addrBook.contactsByFirstName().size(), 3);
  EXPECT_EQ(addrBook.contactsByLastName().size(), 3);

  addrBook.removeContact("aaaaaa", "ddddd");

  EXPECT_EQ(addrBook.contactsByFirstName().size(), 2);
  EXPECT_EQ(addrBook.contactsByLastName().size(), 2);
  EXPECT_EQ(addrBook.contactsByFirstName(),
            (std::vector<Contact>{{"bbbbbb", "ff"}, {"cccccc", "eeeee"}}));
  EXPECT_EQ(addrBook.contactsByLastName(),
            (std::vector<Contact>{{"cccccc", "eeeee"}, {"bbbbbb", "ff"}}));
}

TEST_F(AddressBookTestFixture, RetrievePartialOrFullNameMatch) {
  addrBook.addContact({"Bob", "ffff"});
  addrBook.addContact({"Daniel", "ddddd"});
  addrBook.addContact({"Dan", "eeeee"});
  addrBook.addContact({"Bob", "Danielson"});

  EXPECT_EQ(addrBook.matchedContacts("dan").size(), 3);
  EXPECT_EQ(addrBook.matchedContacts("dan"),
            (std::vector<Contact>{
                {"Bob", "Danielson"}, {"Dan", "eeeee"}, {"Daniel", "ddddd"}}));
}

TEST_F(AddressBookTestFixture, PartialOrFullNameMatchLongVal) {
  addrBook.addContact({"Bob", "ffff"});
  addrBook.addContact({"Daniel", "ddddd"});
  addrBook.addContact({"Dan", "eeeee"});
  addrBook.addContact({"Bob", "Danielson"});

  EXPECT_EQ(addrBook.matchedContacts("danaaaaskugh*&^&$FTU!").size(), 0);
}

TEST_F(AddressBookTestFixture, OverwriteContact) {
  // Contact with no number
  addrBook.addContact({"Bob", "ffff"});

  EXPECT_EQ(addrBook.contactsByFirstName(), (std::vector<Contact>{{"Bob", "ffff"}}));

  // Add number to Bob
  addrBook.addContact({"Bob", "ffff", "12345235"});

  EXPECT_EQ(addrBook.contactsByFirstName(), (std::vector<Contact>{{"Bob", "ffff", "12345235"}}));
}