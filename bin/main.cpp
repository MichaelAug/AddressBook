#include "addressBook.hpp"
#include <iostream>

void printContacts(const std::string &message,
                   const std::vector<Contact> &contacts) {
  std::cout << message << std::endl;
  for (const auto &c : contacts) {
    std::cout << c;
  }
  std::cout << std::endl;
}

int main() {
  AddressBook b;

  b.addContact({"John", "Smith", "555123456"});
  b.addContact({"Alice", "Johnson", "987654321"});
  b.addContact({"Michael", "Brown", "123456789"});
  b.addContact({"Emily", "Davis", "555555555"});
  b.addContact({"David", "Lee"});
  b.addContact({"Sarah", "Wilson", "111223344"});
  b.addContact({"Robert", "Taylor", "999000111"});
  b.addContact({"Linda", "Martinez"});
  b.addContact({"James", "Anderson", "333444555"});
  b.addContact({"Mary", "Harris", "222333444"});

  printContacts("All contacts by first name...", b.contactsByFirstName());

  std::cout << "Removing Michael Brown...\n\n";
  b.removeContact("Michael", "Brown");

  printContacts("All contacts by last name...", b.contactsByLastName());

  printContacts("Returning all contacts matching \"dav\"...",
                b.matchedContacts("dav"));

  return 0;
}
