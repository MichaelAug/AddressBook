#pragma once
#include <string>

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
};