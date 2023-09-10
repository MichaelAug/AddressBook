#pragma once
#include <string>

struct Contact {
  std::string firstName;
  std::string lastName;

// Denote no phone number as empty string
  std::string phone = "";
};