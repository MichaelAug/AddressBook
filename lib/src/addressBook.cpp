#include "addressBook.hpp"
#include <memory>
#include <vector>

static std::vector<Contact> buildVecFromMap(const contactMapping &map) {
  std::vector<Contact> contacts;
  for (const auto &pair : map) {

    if (auto shared_contact = pair.second.lock()) {
      contacts.push_back(*shared_contact);
    }
  }
  return contacts;
}

void AddressBook::addContact(Contact contact) {
  auto contactPtr = std::make_shared<Contact>(contact);
  entries.push_back(contactPtr);
  by_first_last[contactPtr->firstName + contactPtr->lastName] = contactPtr;
  by_last_first[contactPtr->lastName + contactPtr->firstName] = contactPtr;
}

std::vector<Contact> AddressBook::contactsByFirstName() {
  return buildVecFromMap(by_first_last);
}

std::vector<Contact> AddressBook::contactsByLastName() {
  return buildVecFromMap(by_last_first);
}