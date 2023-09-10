#pragma once
#include "contact.hpp"
#include <map>
#include <memory>
#include <unordered_set>
#include <vector>

typedef std::vector<std::shared_ptr<Contact>> contactPointers;
typedef std::map<std::string, std::weak_ptr<Contact>> contactMapping;

class AddressBook {
public:
  // Take Contacts by value because it's safest
  void addContact(Contact);
  std::vector<Contact> contactsByFirstName();
  std::vector<Contact> contactsByLastName();
  std::vector<Contact> matchedContacts(const std::string&);

  void removeContact(const std::string&, const std::string&);
private:
  contactPointers entries;      // Store entries directly, owns the pointers
  contactMapping by_first_last; // Map for sorting by first name + last name
  contactMapping by_last_first; // Map for sorting by last name + first name
};
