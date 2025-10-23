#include <iostream>
#include <vector>
using namespace std;

// make sure it make it virtual

class Employee
{
private:
  string name;
  double salary;

public:
  Employee(string n, int s)
  {
    name = n;
    salary = s;
  }

  double getSalary()
  {
    cout << "Salary: " << salary << endl;
    return salary;
  }

  string getName()
  {
    cout << "Name: " << name << endl;
    return name;
  }

  void showInfo()
  {
    cout << "Employee name: " << name << endl
         << "Salary: " << salary << endl;
  }

  virtual void calculateBonus()
  {
    cout << "Employee you got a bonus!" << endl;
  }
};

class Manager : public Employee
{
public:
  double bonus;

  Manager(string n, int s) : Employee(n, s) {}

  void calculateBonus() override
  {
    bonus = getSalary() * 0.2;
    cout << "Manager you got a " << bonus << " bonus!" << endl;
  }
};

class Developer : public Employee
{
public:
  double bonus;

  Developer(string n, int s) : Employee(n, s) {}

  void calculateBonus() override
  {
    bonus = getSalary() * 0.1;
    cout << "Developer you got a " << bonus << " bonus!" << endl;
  }
};

class Intern : public Employee
{
public:
  double bonus;

  Intern(string n, int s) : Employee(n, s) {
    s = 1000;
  }

  void calculateBonus() override
  {
    bonus = 0;
    cout << "Intern, you don't get a bonus!" << endl;
  }
};

int main()
{
  // Manager manager("Manager", 96000); // manager has access to all functions from base class
  // manager.showInfo();
  // manager.calculateBonus();
  // Developer developer("Developer", 70000);
  // developer.showInfo();
  // developer.calculateBonus();
  vector<Employee> employeeList;
  Employee *manager = new Manager("Manager", 96000);
  manager->showInfo();
  manager->calculateBonus();
  Employee *developer = new Developer("Developer", 80000);
  developer->showInfo();
  developer->calculateBonus();
  Employee *intern = new Intern("Intern", 2000);
  intern->showInfo();
  intern->calculateBonus();

  return 0;
}
