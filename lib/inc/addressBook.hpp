#pragma once
#include "contact.hpp"
#include <vector>
#include <unordered_set>
#include <map>
#include <memory>

typedef std::vector<std::shared_ptr<Contact>> contactPointers;
typedef std::map<std::string, std::weak_ptr<Contact>> contactMapping;

class AddressBook {
public:
    std::string test();
    void addContact(Contact);
    std::vector<Contact> contactsByFirstName();
private:
    contactPointers entries; // Store entries directly
    contactMapping by_first_last; // Map for sorting by first name + last name
};
