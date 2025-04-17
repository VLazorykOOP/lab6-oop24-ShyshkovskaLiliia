#include "Lab6Example.h"  
#include <iostream>  
#include <cmath>  
#include <string>  
#ifndef M_PI  
constexpr double M_PI = 3.14159265358979323846;  
#endif  
using namespace std;  
namespace SpaceExample2 {
    // Задача. Створити ієрархію класів для геометричних фігур:  
        namespace SpaceExample2 {  
        }
    // прямокутник, коло, прямокутний трикутник, трапеція  
    class Shape {
    protected:
        string name;
    public:
        Shape(string n = "noname") : name(n) {}
        virtual double Perimeter() = 0;
        virtual ~Shape() {}
        string getName() { return name; }
    };

    class Rectangle : public Shape {
    private:
        double width, height;
    public:
        Rectangle(string n, double w, double h) : Shape(n), width(w), height(h) {}
        double Perimeter() override {
            return 2 * (width + height);
        }
    };

    class Circle : public Shape {
    private:
        double radius;
    public:
        Circle(string n, double r) : Shape(n), radius(r) {}
        double Perimeter() override {
            return 2 * M_PI * radius;
        }
    };

    class RightTriangle : public Shape {
    private:
        double leg1, leg2;
    public:
        RightTriangle(string n, double l1, double l2) : Shape(n), leg1(l1), leg2(l2) {}
        double Perimeter() override {
            double hypotenuse = sqrt(leg1 * leg1 + leg2 * leg2);
            return leg1 + leg2 + hypotenuse;
        }
    };

    class Trapezoid : public Shape {
    private:
        double base1, base2, side1, side2;
    public:
        Trapezoid(string n, double b1, double b2, double s1, double s2)
            : Shape(n), base1(b1), base2(b2), side1(s1), side2(s2) {
        }
        double Perimeter() override {
            return base1 + base2 + side1 + side2;
        }
    };

    string setRandomName() {
        string prefixes[] = { "Geo", "Poly", "Tri", "Circ", "Rect" };
        string suffixes[] = { "gon", "oid", "le", "um", "angle" };
        return prefixes[rand() % 5] + suffixes[rand() % 5];
    }

    int mainExample2() {
        srand(time(0));
        Shape** shapes;
        int n;

        do {
            cout << "How many shapes? (1-100): ";
            cin >> n;
        } while (n <= 0 || n > 100);

        shapes = new Shape * [n];

        cout << "Input 1 for random shapes, 2 for manual input: ";
        int choice;
        cin >> choice;

        for (int i = 0; i < n; i++) {
            string name;
            int type;
            cout << "\nShape " << i + 1 << ":\n";
            cout << "1 - Rectangle\n2 - Circle\n3 - Right Triangle\n4 - Trapezoid\n";
            cout << "Choose type: ";
            cin >> type;
            cout << "Enter name: ";
            cin >> name;

            switch (type) {
            case 1: {
                double w, h;
                if (choice == 1) {
                    w = rand() % 20 + 1;
                    h = rand() % 20 + 1;
                    cout << "Random width: " << w << ", height: " << h << endl;
                }
                else {
                    cout << "Enter width and height: ";
                    cin >> w >> h;
                }
                shapes[i] = new Rectangle(name, w, h);
                break;
            }
            case 2: {
                double r;
                if (choice == 1) {
                    r = rand() % 20 + 1;
                    cout << "Random radius: " << r << endl;
                }
                else {
                    cout << "Enter radius: ";
                    cin >> r;
                }
                shapes[i] = new Circle(name, r);
                break;
            }
            case 3: {
                double l1, l2;
                if (choice == 1) {
                    l1 = rand() % 20 + 1;
                    l2 = rand() % 20 + 1;
                    cout << "Random legs: " << l1 << ", " << l2 << endl;
                }
                else {
                    cout << "Enter two legs: ";
                    cin >> l1 >> l2;
                }
                shapes[i] = new RightTriangle(name, l1, l2);
                break;
            }
            case 4: {
                double b1, b2, s1, s2;
                if (choice == 1) {
                    b1 = rand() % 20 + 1;
                    b2 = rand() % 20 + 1;
                    s1 = rand() % 20 + 1;
                    s2 = rand() % 20 + 1;
                    cout << "Random bases: " << b1 << ", " << b2 << "; sides: " << s1 << ", " << s2 << endl;
                }
                else {
                    cout << "Enter two bases and two sides: ";
                    cin >> b1 >> b2 >> s1 >> s2;
                }
                shapes[i] = new Trapezoid(name, b1, b2, s1, s2);
                break;
            }
            default:
                cout << "Invalid type, using Rectangle\n";
                shapes[i] = new Rectangle(name, 1, 1);
            }
        }

        cout << "\nShapes and their perimeters:\n";
        double totalPerimeter = 0;
        for (int i = 0; i < n; i++) {
            cout << shapes[i]->getName() << ": " << shapes[i]->Perimeter() << endl;
            totalPerimeter += shapes[i]->Perimeter();
        }
        cout << "Total perimeter: " << totalPerimeter << endl;

        for (int i = 0; i < n; i++) {
            delete shapes[i];
        }
        delete[] shapes;

        return 0;
    }
} 
