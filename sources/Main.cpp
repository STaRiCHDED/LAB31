// Copyright 2020 Nikita Klimov nik179804@gmail.com

#include "Main.hpp"
#include <algorithm>

Main::Main() = default;
Main::Main(const std::string &path) { parser(path); }
const std::vector<Student> &Main::getStudents() const { return students; }
const Lengths_of_fields &Main::getL() const { return l; }

void Main::printRow(std::ostream &out, const Student &student) const {
  out << std::left << "|" << std::setw(l.length_1_field) << student.getName()
      << "|";
  if (std::any_cast<json>(student.getGroup()).is_number()) {
    out << std::setw(l.length_2_field)
        << std::any_cast<json>(student.getGroup()).get<int>();
  } else if (std::any_cast<json>(student.getGroup()).is_string()) {
    out << std::setw(l.length_2_field)
        << std::any_cast<json>(student.getGroup()).get<std::string>();
  } else {
    throw std::invalid_argument(
        "The type of the Group variable is undefined!!!");
  }
  out << "|" << std::setprecision(3) << std::setw(l.length_3_field)
      << student.getAvg() << "|";
  if (std::any_cast<json>(student.getDebt()).is_null()) {
    out << std::setw(l.length_4_field) << "null";
  } else if (std::any_cast<json>(student.getDebt()).is_array()) {
    std::string it = std::to_string(std::any_cast<json>(student.getDebt())
                                        .get<std::vector<std::string>>()
                                        .size()) +
                     " items";
    out << std::setw(l.length_4_field) << it;
  } else if (std::any_cast<json>(student.getDebt()).is_string()) {
    out << std::setw(l.length_4_field)
        << std::any_cast<json>(student.getDebt()).get<std::string>();
  } else {
    throw std::invalid_argument(
        "The type of the Debt variable is undefined!!!");
  }
  out << "|";
}
std::string Main::getSeparator() const {
  std::string sep = "|";
  for (size_t i = 0; i < l.length_1_field; ++i) {
    sep += "-";
  }
  sep += "|";
  for (size_t i = 0; i < l.length_2_field; ++i) {
    sep += "-";
  }
  sep += "|";
  for (size_t i = 0; i < l.length_3_field; ++i) {
    sep += "-";
  }
  sep += "|";
  for (size_t i = 0; i < l.length_4_field; ++i) {
    sep += "-";
  }
  sep += "|";
  return sep;
}
void Main::parser(const std::string &path) {
  if (path.empty()) {
    throw std::invalid_argument("The file path cannot be empty!!!");
  }
  std::ifstream json_file(path);
  if (!json_file.is_open()) {
    throw std::out_of_range("The file with the specified name: " + path +
                            " does not exist!!!");
  }
  json data;
  json_file >> data;
  if (!data.at("items").is_array()) {
    throw std::invalid_argument("Items is not array!!!");
  }
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
    throw std::out_of_range("Items length don't equal _meta.count!!!");
  }
  for (auto const &student : data.at("items")) {
    students.emplace_back(student);
  }
  setLengths();
}
void Main::printData() {
  std::cout << *this;
}
bool Main::emptyJSONobject() const { return students.empty(); }
void Main::setJSONString(const std::string &JSON) {
  json data = json::parse(JSON);
  if (!data.at("items").is_array()) {
    throw std::invalid_argument("Items is not array!!!");
  }
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
    throw std::invalid_argument("Items length don't equal _meta.count!!!");
  }
  for (auto const &student : data.at("items")) {
    students.emplace_back(student);
  }
  setLengths();
}
void Main::setLengths() {
  for (const auto &student : students) {
    if (student.getName().size() > l.length_1_field) {
      l.length_1_field = student.getName().size() + 1;
    }
    if (std::any_cast<json>(student.getGroup()).is_number()) {
      if (std::to_string(std::any_cast<json>(student.getGroup()).get<int>())
              .size() > l.length_2_field) {
        l.length_2_field =
            std::to_string(std::any_cast<json>(student.getGroup()).get<int>())
                .size() +
            1;
      }
    } else {
      if (std::any_cast<json>(student.getGroup()).get<std::string>().size() >
          l.length_2_field) {
        l.length_2_field =
            std::any_cast<json>(student.getGroup()).get<std::string>().size() +
            1;
      }
    }
    if (std::any_cast<json>(student.getDebt()).is_string() &&
        std::any_cast<json>(student.getDebt()).get<std::string>().size() >
        l.length_4_field) {
      l.length_4_field =
          std::any_cast<json>(student.getDebt()).get<std::string>().size() + 1;
    }
  }
}
std::ostream &operator<<(std::ostream &out, Main &p) {
  out << std::left << "|" << std::setw(p.l.length_1_field) << "name"
      << "|" << std::setw(p.l.length_2_field) << "group"
      << "|" << std::setw(p.l.length_3_field) << "avg"
      << "|" << std::setw(p.l.length_4_field) << "debt"
      << "|" << '\n';
  std::string separator = p.getSeparator();
  out << separator << "\n";
  for (const auto &student : p.students) {
    p.printRow(out, student);
    out << '\n';
    out << separator << "\n";
  }
  return out;
}
Main::~Main() = default;
