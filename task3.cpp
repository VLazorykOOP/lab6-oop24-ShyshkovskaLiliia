#include "Lab6Example.h"
#include <iostream>
#include <string>
using namespace std;
#include <cstdlib>
namespace SpaceExample3 {
    // MultipleInheritance.cpp  
    // Ієрархія типів складається з сутностей:
    // особа, жінка, працівник та працівник-жінка.  
    //  

    // Базовий клас Особа
    class Person {
    protected:
        string name;
        int age;
    public:
        Person() : name("Unknown"), age(0) {}
        Person(const string& n, int a) : name(n), age(a) {}
        virtual ~Person() { cout << "Person destructor: " << name << endl; }

        virtual void print(ostream& os) const {
            os << "Name: " << name << ", Age: " << age;
        }

        friend ostream& operator<<(ostream& os, const Person& p);
        friend istream& operator>>(istream& is, Person& p);
    };

    ostream& operator<<(ostream& os, const Person& p) {
        p.print(os);
        return os;
    }

    istream& operator>>(istream& is, Person& p) {
        cout << "Enter name: ";
        getline(is, p.name);
        cout << "Enter age: ";
        is >> p.age;
        is.ignore();
        return is;
    }

    // Клас Жінка
    class Woman : virtual public Person {
    protected:
        string maidenName;
    public:
        Woman() : Person(), maidenName("Unknown") {}
        Woman(const string& n, int a, const string& mn)
            : Person(n, a), maidenName(mn) {
        }
        virtual ~Woman() { cout << "Woman destructor: " << name << endl; }

        void print(ostream& os) const override {
            Person::print(os);
            os << ", Maiden Name: " << maidenName;
        }

        friend istream& operator>>(istream& is, Woman& w);
    };

    istream& operator>>(istream& is, Woman& w) {
        is >> static_cast<Person&>(w);
        cout << "Enter maiden name: ";
        getline(is, w.maidenName);
        return is;
    }

    // Клас Працівник
    class Employee : virtual public Person {
    protected:
        string position;
        double salary;
    public:
        Employee() : Person(), position("Unknown"), salary(0) {}
        Employee(const string& n, int a, const string& p, double s)
            : Person(n, a), position(p), salary(s) {
        }
        virtual ~Employee() { cout << "Employee destructor: " << name << endl; }

        void print(ostream& os) const override {
            Person::print(os);
            os << ", Position: " << position << ", Salary: " << salary;
        }

        friend istream& operator>>(istream& is, Employee& e);
    };

    istream& operator>>(istream& is, Employee& e) {
        is >> static_cast<Person&>(e);
        cout << "Enter position: ";
        getline(is, e.position);
        cout << "Enter salary: ";
        is >> e.salary;
        is.ignore();
        return is;
    }

    // Похідний клас Працівник-Жінка (множинне успадкування)
    class FemaleEmployee : public Woman, public Employee {
    public:
        FemaleEmployee() : Person(), Woman(), Employee() {}
        FemaleEmployee(const string& n, int a, const string& mn,
            const string& p, double s)
            : Person(n, a), Woman(n, a, mn), Employee(n, a, p, s) {
        }
        ~FemaleEmployee() override { cout << "FemaleEmployee destructor: " << name << endl; }

        void print(ostream& os) const override {
            os << "=== Female Employee ===\n";
            Person::print(os);
            os << "\nWoman info: Maiden Name - " << maidenName;
            os << "\nEmployee info: Position - " << position
                << ", Salary - " << salary;
        }

        friend istream& operator>>(istream& is, FemaleEmployee& fe);
    };

    istream& operator>>(istream& is, FemaleEmployee& fe) {
        cout << "Enter person details:\n";
        is >> static_cast<Person&>(fe);
        cout << "Enter woman details:\n";
        cout << "Maiden name: ";
        getline(is, fe.maidenName);
        cout << "Enter employee details:\n";
        cout << "Position: ";
        getline(is, fe.position);
        cout << "Salary: ";
        is >> fe.salary;
        is.ignore();
        return is;
    }

    int mainExample3() {
        // Тестування класів
        cout << "Creating FemaleEmployee object:\n";
        FemaleEmployee fe("Anna Petrova", 32, "Ivanova", "Manager", 25000.0);

        cout << "\nOutput using overloaded operator<<:\n";
        cout << fe << endl;

        cout << "\nCreating another FemaleEmployee with user input:\n";
        FemaleEmployee fe2;
        cin >> fe2;

        cout << "\nEntered FemaleEmployee details:\n";
        cout << fe2 << endl;

        return 0;
    }
} 
