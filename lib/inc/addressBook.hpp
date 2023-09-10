#pragma once
#include "contact.hpp"
#include <map>
#include <memory>
#include <unordered_set>
#include <vector>

typedef std::map<std::string, std::shared_ptr<Contact>> contactMapping;

class AddressBook {
public:
  // Adds a contact to the address book.
  // The contact is taken by value for safety.
  // Parameters:
  // Contact: The contact to be added to the address book
  void addContact(Contact);

  // Returns a vector of contacts sorted by first name.
  std::vector<Contact> contactsByFirstName();

  // Returns a vector of contacts sorted by last name.
  std::vector<Contact> contactsByLastName();

  // Returns a vector of contacts that match the provided string value.
  // The comparison is case-insensitive.
  // Matching is performed on both first names and last names.
  // If a contact's first or last name starts with the provided value, it's
  // considered a match.
  // Parameters:
  // const std::string&: The value to be matched against contact names.
  std::vector<Contact> matchedContacts(const std::string &);

  // Removes a contact from the address book based on their first and last
  // names. Both first name and last name are required to identify the contact
  // to be removed.
  // Parameters:
  // const std::string&: The first name of the contact to be removed.
  // const std::string&: The last name of the contact to be removed.
  void removeContact(const std::string &, const std::string &);

private:
  contactMapping by_first_last; // Map for sorting by first name + last name
  contactMapping by_last_first; // Map for sorting by last name + first name
};
