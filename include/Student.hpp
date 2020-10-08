//
// Created by nikitaklimov on 17.09.2020.
//

#ifndef TEMPLATE_STUDENT_HPP
#define TEMPLATE_STUDENT_HPP
#include <any>
#include <exception>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
class Student {
  std::string Name;
  std::any Group;
  double Avg = 0;
  std::any Debt;

 public:
  explicit Student(const json &obj);
  Student();
  const std::string &getName() const;
  void setName(const json &name);
  const std::any &getGroup() const;
  void setGroup(const json &group);
  double getAvg() const;
  void setAvg(const json &avg);
  const std::any &getDebt() const;
  void setDebt(const json &debt);
  void from_json(const json &j);
};
void from_json(const json &j, Student &s);
#endif  // TEMPLATE_STUDENT_HPP
