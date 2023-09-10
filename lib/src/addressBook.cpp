#include "addressBook.hpp"
#include <algorithm>
#include <memory>
#include <vector>
#include <cctype>

namespace {
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

std::string toLower(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return result;
}
} // namespace

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

std::vector<Contact> AddressBook::matchedContacts(const std::string &val) {
  std::vector<Contact> contacts;
  const auto val_lower = toLower(val);
  for (const auto &c : by_first_last) {
    if (auto contactPtr = c.second.lock()) {
      const auto first_lower = toLower(contactPtr->firstName);
      const auto last_lower = toLower(contactPtr->lastName);

      if (first_lower.compare(0, val_lower.length(), val_lower) == 0 ||
          last_lower.compare(0, val_lower.length(), val_lower) == 0) {
        contacts.push_back(*contactPtr);
      }
    }
  }
  return contacts;
}