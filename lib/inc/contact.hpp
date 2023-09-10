#pragma once
#include <string>
#include <iostream>

struct Contact {
  std::string firstName;
  std::string lastName;

  // Denote no phone number as empty string
  std::string phone = "";

  // Needed for GTest
  bool operator==(const Contact &other) const {
    return firstName == other.firstName && lastName == other.lastName &&
           phone == other.phone;
  }

  friend std::ostream& operator<<(std::ostream& os, const Contact& contact) {
        os << contact.firstName << ", " << contact.lastName << ", " << contact.phone << std::endl;
        return os;
    }
};