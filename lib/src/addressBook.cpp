#include "addressBook.hpp"
#include <algorithm>
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

static void removeFromMap(contactMapping &map, const std::string &key) {
  auto it = map.find(key);
  if (it != map.end()) {
    map.erase(it);
  }
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

void AddressBook::removeContact(const std::string &first_name,
                                const std::string &last_name) {
  // Could do integrity checks here to make sure all collections find the
  // element
  auto entries_it = std::find_if(
      entries.begin(), entries.end(),
      [&first_name, &last_name](const std::shared_ptr<Contact> &contact) {
        return contact->firstName == first_name &&
               contact->lastName == last_name;
      });

  if (entries_it != entries.end()) {
    // Contact found, remove it from the vector
    entries.erase(entries_it);
  }

  removeFromMap(by_first_last, first_name + last_name);
  removeFromMap(by_last_first, last_name + first_name);
}