// Copyright 2020 Nikita Klimov nik179804@gmail.com

#ifndef INCLUDE_MAIN_HPP_
#define INCLUDE_MAIN_HPP_
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Student.hpp"

struct Lengths_of_fields {
  size_t length_1_field;
  size_t length_2_field;
  size_t length_3_field;
  size_t length_4_field;
};
class Main {
  std::vector<Student> students;
  Lengths_of_fields l{15, 8, 6, 15};
  void setLengths();

 public:
  Main();
  explicit Main(const std::string &path);
  ~Main();
  const std::vector<Student> &getStudents() const;
  const Lengths_of_fields &getL() const;
  void printRow(std::ostream &out, const Student &student) const;
  std::string getSeparator() const;
  void parser(const std::string &path);
  void printData();
  bool emptyJSONobject() const;
  void setJSONString(const std::string &JSON);
  friend std::ostream &operator<<(std::ostream &out, Main &p);
};
#endif  // INCLUDE_MAIN_HPP_
