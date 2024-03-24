#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

/* CEmployee for storing data of employees */
struct CEmployee
{
  CEmployee(const string &, const string &, const string &, unsigned int);
  CEmployee(const string &, const string &, const string &);
  CEmployee(const string &, const string &);
  CEmployee(const string &);

  string name, surname, email;
  unsigned int salary = 0;
};

CEmployee::CEmployee(const string &name, const string &surname, const string &email, unsigned int salary)
    : name(name), surname(surname), email(email), salary(salary) {}

CEmployee::CEmployee(const string &name, const string &surname, const string &email)
    : name(name), surname(surname), email(email) {}

CEmployee::CEmployee(const string &name, const string &surname)
    : name(name), surname(surname) {}

CEmployee::CEmployee(const string &email)
    : email(email) {}

bool compare_name(const CEmployee *a, const CEmployee &b)
{
  if (a->surname == b.surname)
  {
    return a->name < b.name;
  }
  return a->surname < b.surname;
}

bool compare_email(const CEmployee *a, const CEmployee &b)
{
  return a->email < b.email;
}

class CPersonalAgenda
{
public:
  CPersonalAgenda();
  ~CPersonalAgenda();
  bool add(const string &name,
           const string &surname,
           const string &email,
           unsigned int salary);
  bool del(const string &name,
           const string &surname);
  bool del(const string &email);
  bool changeName(const string &email,
                  const string &newName,
                  const string &newSurname);
  bool changeEmail(const string &name,
                   const string &surname,
                   const string &newEmail);
  bool setSalary(const string &name,
                 const string &surname,
                 unsigned int salary);
  bool setSalary(const string &email,
                 unsigned int salary);
  unsigned int getSalary(const string &name,
                         const string &surname) const;
  unsigned int getSalary(const string &email) const;
  bool getRank(const string &name,
               const string &surname,
               int &rankMin,
               int &rankMax) const;
  bool getRank(const string &email,
               int &rankMin,
               int &rankMax) const;
  bool getFirst(string &outName,
                string &outSurname) const;
  bool getNext(const string &name,
               const string &surname,
               string &outName,
               string &outSurname) const;

private:
  // vector stored with sorted names and surnames
  vector<CEmployee *> by_name;
  // vector stored with sorted emails
  vector<CEmployee *> by_email;
  // vector stored with sorted salaries
  vector<unsigned int> salary_vec;

  bool find_with_name(const CEmployee, vector<CEmployee *>::const_iterator &name_idx) const;
  bool find_with_email(const CEmployee, vector<CEmployee *>::const_iterator &email_idx) const;
  bool find_salary(const unsigned int, vector<unsigned int>::const_iterator &salary_idx) const;
};

CPersonalAgenda::CPersonalAgenda()
{
}

// destructor
CPersonalAgenda::~CPersonalAgenda()
{
  for (auto emp : by_name)
  {
    delete emp;
  }
}

/* returns finds index in the name vector and set output parameter to name_idx if exists */
bool CPersonalAgenda::find_with_name(const CEmployee emp, vector<CEmployee *>::const_iterator &name_idx) const
{
  name_idx = lower_bound(by_name.begin(), by_name.end(), emp, compare_name);

  return (name_idx != by_name.end() && (*name_idx)->name == emp.name && (*name_idx)->surname == emp.surname);
}

/* returns finds index in the email vector and set output parameter to email_idx if exists */
bool CPersonalAgenda::find_with_email(const CEmployee emp, vector<CEmployee *>::const_iterator &email_idx) const
{
  email_idx = lower_bound(by_email.begin(), by_email.end(), emp, compare_email);

  return (email_idx != by_email.end() && (*email_idx)->email == emp.email);
}

/* returns finds index in the salary vector and set output parameter to salary if exists */
bool CPersonalAgenda::find_salary(const unsigned int salary, vector<unsigned int>::const_iterator &salary_idx) const
{
  salary_idx = lower_bound(salary_vec.begin(), salary_vec.end(), salary);

  return (salary_idx != salary_vec.end() && (*salary_idx) == salary);
}

bool CPersonalAgenda::add(const string &name,
                          const string &surname,
                          const string &email,
                          unsigned int salary)
{
  CEmployee *emp = new CEmployee(name, surname, email, salary);
  vector<CEmployee *>::const_iterator name_idx, email_idx;
  vector<unsigned int>::const_iterator salary_idx;

  if (find_with_name(*emp, name_idx) || find_with_email(*emp, email_idx))
  {
    delete emp;
    return false;
  }

  find_salary(emp->salary, salary_idx);
  by_name.insert(name_idx, emp);
  by_email.insert(email_idx, emp);
  salary_vec.insert(salary_idx, emp->salary);
  return true;
}

bool CPersonalAgenda::del(const string &name,
                          const string &surname)
{
  CEmployee emp(name, surname);
  vector<CEmployee *>::const_iterator name_idx, email_idx;
  vector<unsigned int>::const_iterator salary_idx;

  if (!find_with_name(emp, name_idx))
  {
    return false;
  }

  emp.email = (*name_idx)->email;
  if (!find_with_email(emp, email_idx))
  {
    return false;
  }

  emp.salary = (*name_idx)->salary;
  find_salary(emp.salary, salary_idx);

  delete *name_idx;
  by_name.erase(name_idx);
  by_email.erase(email_idx);
  salary_vec.erase(salary_idx);
  return true;
}

bool CPersonalAgenda::del(const string &email)
{
  CEmployee emp(email);
  vector<CEmployee *>::const_iterator name_idx, email_idx;
  vector<unsigned int>::const_iterator salary_idx;

  if (!find_with_email(emp, email_idx))
  {
    return false;
  }

  emp.name = (*email_idx)->name;
  emp.surname = (*email_idx)->surname;
  if (!find_with_name(emp, name_idx))
  {
    return false;
  }

  emp.salary = (*email_idx)->salary;
  find_salary(emp.salary, salary_idx);

  delete *email_idx;
  by_email.erase(email_idx);
  by_name.erase(name_idx);
  salary_vec.erase(salary_idx);
  return true;
}

bool CPersonalAgenda::changeName(const string &email,
                                 const string &newName,
                                 const string &newSurname)
{
  vector<CEmployee *>::const_iterator name_idx, email_idx;
  if (!find_with_email(CEmployee(email), email_idx))
  {
    return false;
  }

  if ((*email_idx)->name == newName && (*email_idx)->surname == newSurname)
  {
    return false;
  }

  if (find_with_name(CEmployee(newName, newSurname), name_idx))
  {
    return false;
  }

  if (!find_with_name(CEmployee((*email_idx)->name, (*email_idx)->surname), name_idx))
  {
    return false;
  }

  by_name.erase(name_idx);
  (*email_idx)->name = newName;
  (*email_idx)->surname = newSurname;

  find_with_name(CEmployee((*email_idx)->name, (*email_idx)->surname), name_idx);
  by_name.insert(name_idx, (*email_idx));

  return true;
}

bool CPersonalAgenda::changeEmail(const string &name,
                                  const string &surname,
                                  const string &newEmail)
{
  vector<CEmployee *>::const_iterator name_idx, email_idx;
  if (!find_with_name(CEmployee(name, surname), name_idx))
  {
    return false;
  }

  if ((*name_idx)->email == newEmail)
  {
    return false;
  }

  if (find_with_email(CEmployee(newEmail), email_idx))
  {
    return false;
  }

  if (!find_with_email(CEmployee((*name_idx)->email), email_idx))
  {
    return false;
  }

  by_email.erase(email_idx);
  (*name_idx)->email = newEmail;

  find_with_email(CEmployee((*name_idx)->email), email_idx);
  by_email.insert(email_idx, (*name_idx));

  return true;
}

bool CPersonalAgenda::setSalary(const string &name,
                                const string &surname,
                                unsigned int salary)
{
  CEmployee emp(name, surname);
  vector<CEmployee *>::const_iterator email_idx, name_idx;
  vector<unsigned int>::const_iterator salary_idx;
  if (!find_with_name(emp, name_idx))
  {
    return false;
  }

  if ((*name_idx)->salary == salary)
  {
    return false;
  }
  emp.salary = (*name_idx)->salary;
  if (!find_salary(emp.salary, salary_idx))
  {
    return false;
  }

  emp.email = (*name_idx)->email;
  if (!find_with_email(emp, email_idx))
  {
    return false;
  }

  (*email_idx)->salary = salary;
  (*name_idx)->salary = salary;

  salary_vec.erase(salary_idx);
  find_salary((*name_idx)->salary, salary_idx);
  salary_vec.insert(salary_idx, salary);
  return true;
}

bool CPersonalAgenda::setSalary(const string &email,
                                unsigned int salary)
{
  CEmployee emp(email);
  vector<CEmployee *>::const_iterator name_idx, email_idx;
  vector<unsigned int>::const_iterator salary_idx;

  if (!find_with_email(emp, email_idx))
  {
    return false;
  }

  if ((*email_idx)->salary == salary)
  {
    return false;
  }

  emp.salary = (*email_idx)->salary;
  if (!find_salary(emp.salary, salary_idx))
  {
    return false;
  }

  emp.name = (*email_idx)->name;
  emp.surname = (*email_idx)->surname;
  if (!find_with_name(emp, name_idx))
  {
    return false;
  }

  (*email_idx)->salary = salary;
  (*name_idx)->salary = salary;

  salary_vec.erase(salary_idx);
  find_salary((*email_idx)->salary, salary_idx);
  salary_vec.insert(salary_idx, salary);
  return true;
}

unsigned int CPersonalAgenda::getSalary(const string &name,
                                        const string &surname) const
{
  CEmployee emp(name, surname);
  vector<CEmployee *>::const_iterator name_idx;

  if (!find_with_name(emp, name_idx))
  {
    return 0;
  }

  return (*name_idx)->salary;
}

unsigned int CPersonalAgenda::getSalary(const string &email) const
{
  CEmployee emp(email);
  vector<CEmployee *>::const_iterator email_idx;

  if (!find_with_email(emp, email_idx))
  {
    return 0;
  }

  return (*email_idx)->salary;
}

bool CPersonalAgenda::getFirst(string &outName,
                               string &outSurname) const
{
  if (by_name.empty())
  {
    return false;
  }

  outName = by_name.front()->name;
  outSurname = by_name.front()->surname;
  return true;
}

bool CPersonalAgenda::getNext(const string &name, const string &surname, string &outName, string &outSurname) const
{
  CEmployee emp(name, surname);
  vector<CEmployee *>::const_iterator name_idx;

  if (!find_with_name(emp, name_idx))
  {
    return false;
  }

  name_idx++;

  if (name_idx == by_name.end())
  {
    return false;
  }

  outName = (*name_idx)->name;
  outSurname = (*name_idx)->surname;

  return true;
}

bool CPersonalAgenda::getRank(const string &name, const string &surname, int &rankMin, int &rankMax) const
{
  CEmployee emp(name, surname);
  vector<CEmployee *>::const_iterator name_idx;

  if (!find_with_name(emp, name_idx))
  {
    return false;
  }

  auto lower_salary = lower_bound(salary_vec.begin(), salary_vec.end(), (*name_idx)->salary);
  auto upper_salary = upper_bound(lower_salary, salary_vec.end(), (*name_idx)->salary);

  rankMin = (int)(lower_salary - salary_vec.begin());
  rankMax = rankMin + (int)(upper_salary - lower_salary) - 1;
  return true;
}

bool CPersonalAgenda::getRank(const string &email, int &rankMin, int &rankMax) const
{
  CEmployee emp(email);
  vector<CEmployee *>::const_iterator email_idx;

  if (!find_with_email(emp, email_idx))
  {
    return false;
  }

  auto lower_salary = lower_bound(salary_vec.begin(), salary_vec.end(), (*email_idx)->salary);
  auto upper_salary = upper_bound(lower_salary, salary_vec.end(), (*email_idx)->salary);

  rankMin = (int)(lower_salary - salary_vec.begin());
  rankMax = rankMin + (int)(upper_salary - lower_salary) - 1;
  return true;
}

#ifndef __PROGTEST__
int main(void)
{
  string outName, outSurname;
  int lo, hi;

  CPersonalAgenda b1;
  assert(b1.add("John", "Smith", "john", 30000));
  assert(b1.add("John", "Miller", "johnm", 35000));
  assert(b1.add("Peter", "Smith", "peter", 23000));
  assert(b1.getFirst(outName, outSurname) && outName == "John" && outSurname == "Miller");
  assert(b1.getNext("John", "Miller", outName, outSurname) && outName == "John" && outSurname == "Smith");
  assert(b1.getNext("John", "Smith", outName, outSurname) && outName == "Peter" && outSurname == "Smith");
  assert(!b1.getNext("Peter", "Smith", outName, outSurname));
  assert(b1.setSalary("john", 32000));
  assert(b1.getSalary("john") == 32000);
  assert(b1.getSalary("John", "Smith") == 32000);
  assert(b1.getRank("John", "Smith", lo, hi) && lo == 1 && hi == 1);
  assert(b1.getRank("john", lo, hi) && lo == 1 && hi == 1);
  assert(b1.getRank("peter", lo, hi) && lo == 0 && hi == 0);
  assert(b1.getRank("johnm", lo, hi) && lo == 2 && hi == 2);
  assert(b1.setSalary("John", "Smith", 35000));
  assert(b1.getSalary("John", "Smith") == 35000);
  assert(b1.getSalary("john") == 35000);
  assert(b1.getRank("John", "Smith", lo, hi) && lo == 1 && hi == 2);
  assert(b1.getRank("john", lo, hi) && lo == 1 && hi == 2);
  assert(b1.getRank("peter", lo, hi) && lo == 0 && hi == 0);
  assert(b1.getRank("johnm", lo, hi) && lo == 1 && hi == 2);
  assert(b1.changeName("peter", "James", "Bond"));
  assert(b1.getSalary("peter") == 23000);
  assert(b1.getSalary("James", "Bond") == 23000);
  assert(b1.getSalary("Peter", "Smith") == 0);
  assert(b1.getFirst(outName, outSurname) && outName == "James" && outSurname == "Bond");
  assert(b1.getNext("James", "Bond", outName, outSurname) && outName == "John" && outSurname == "Miller");
  assert(b1.getNext("John", "Miller", outName, outSurname) && outName == "John" && outSurname == "Smith");
  assert(!b1.getNext("John", "Smith", outName, outSurname));
  assert(b1.changeEmail("James", "Bond", "james"));
  assert(b1.getSalary("James", "Bond") == 23000);
  assert(b1.getSalary("james") == 23000);
  assert(b1.getSalary("peter") == 0);
  assert(b1.del("james"));
  assert(b1.getRank("john", lo, hi) && lo == 0 && hi == 1);
  assert(b1.del("John", "Miller"));
  assert(b1.getRank("john", lo, hi) && lo == 0 && hi == 0);
  assert(b1.getFirst(outName, outSurname) && outName == "John" && outSurname == "Smith");
  assert(!b1.getNext("John", "Smith", outName, outSurname));
  assert(b1.del("john"));
  assert(!b1.getFirst(outName, outSurname));
  assert(b1.add("John", "Smith", "john", 31000));
  assert(b1.add("john", "Smith", "joHn", 31000));
  assert(b1.add("John", "smith", "jOhn", 31000));

  CPersonalAgenda b2;
  assert(!b2.getFirst(outName, outSurname));
  assert(b2.add("James", "Bond", "james", 70000));
  assert(b2.add("James", "Smith", "james2", 30000));
  assert(b2.add("Peter", "Smith", "peter", 40000));
  assert(!b2.add("James", "Bond", "james3", 60000));
  assert(!b2.add("Peter", "Bond", "peter", 50000));
  assert(!b2.changeName("joe", "Joe", "Black"));
  assert(!b2.changeEmail("Joe", "Black", "joe"));
  assert(!b2.setSalary("Joe", "Black", 90000));
  assert(!b2.setSalary("joe", 90000));
  assert(b2.getSalary("Joe", "Black") == 0);
  assert(b2.getSalary("joe") == 0);
  assert(!b2.getRank("Joe", "Black", lo, hi));
  assert(!b2.getRank("joe", lo, hi));
  assert(!b2.changeName("joe", "Joe", "Black"));
  assert(!b2.changeEmail("Joe", "Black", "joe"));
  assert(!b2.del("Joe", "Black"));
  assert(!b2.del("joe"));
  assert(!b2.changeName("james2", "James", "Bond"));
  assert(!b2.changeEmail("Peter", "Smith", "james"));
  assert(!b2.changeName("peter", "Peter", "Smith"));
  assert(!b2.changeEmail("Peter", "Smith", "peter"));
  assert(b2.del("Peter", "Smith"));
  assert(!b2.changeEmail("Peter", "Smith", "peter2"));
  assert(!b2.setSalary("Peter", "Smith", 35000));
  assert(b2.getSalary("Peter", "Smith") == 0);
  assert(!b2.getRank("Peter", "Smith", lo, hi));
  assert(!b2.changeName("peter", "Peter", "Falcon"));
  assert(!b2.setSalary("peter", 37000));
  assert(b2.getSalary("peter") == 0);
  assert(!b2.getRank("peter", lo, hi));
  assert(!b2.del("Peter", "Smith"));
  assert(!b2.del("peter"));
  assert(b2.add("Peter", "Smith", "peter", 40000));
  assert(b2.getSalary("peter") == 40000);

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
