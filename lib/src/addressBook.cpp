#include "addressBook.hpp"
#include <memory>

void AddressBook::addContact(Contact contact) {
    auto contactPtr = std::make_shared<Contact>(contact);
    entries.push_back(contactPtr);
    by_first_last[contactPtr->firstName + contactPtr -> lastName] = contactPtr;
}

std::vector<Contact> AddressBook::contactsByFirstName() {
    std::vector<Contact> contacts;
    for(const auto& pair : by_first_last) {

        if(auto shared_contact = pair.second.lock()) {
            contacts.push_back(*shared_contact);
        }
    }
    return contacts;
}