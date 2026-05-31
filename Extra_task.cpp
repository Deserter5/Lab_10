#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

enum class TriangleType { Equilateral, Isosceles, Scalene };

template <typename T>
class Shape {
public:
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual ~Shape() {}
};

template <typename T>
class Rectangle : public Shape<T> {
private:
    T width, height;
public:
    Rectangle(T w, T h) : width(w), height(h) {
        if (width <= 0 || height <= 0) {
            throw invalid_argument("Rectangle width and height must be greater than 0!");
        }
    }
    double calculateArea() const override { return width * height; }
    double calculatePerimeter() const override { return 2 * (width + height); }
    T getWidth() const { return width; }
    T getHeight() const { return height; }
};

template <typename T>
class Circle : public Shape<T> {
private:
    T radius;
    const double PI = 3.1415926535;
public:
    Circle(T r) : radius(r) {
        if (radius <= 0) {
            throw invalid_argument("Circle radius must be greater than 0!");
        }
    }
    double calculateArea() const override { return PI * radius * radius; }
    double calculatePerimeter() const override { return 2 * PI * radius; }
    T getRadius() const { return radius; }
};

template <typename T>
class Triangle : public Shape<T> {
private:
    T sideA, sideB, sideC;
    TriangleType type;

    void validateTriangle() {
        if (sideA <= 0 || sideB <= 0 || sideC <= 0)
            throw invalid_argument("Triangle sides must be greater than 0!");

        if (sideA + sideB <= sideC || sideA + sideC <= sideB || sideB + sideC <= sideA)
            throw invalid_argument("Such a triangle does not exist (sum of two sides must be greater than the third)!");

        if (type == TriangleType::Equilateral && (sideA != sideB || sideB != sideC))
            throw invalid_argument("Sides do not correspond to an equilateral triangle!");

        if (type == TriangleType::Isosceles && (sideA != sideB && sideB != sideC && sideA != sideC))
            throw invalid_argument("Sides do not correspond to an isosceles triangle!");
    }
public:
    Triangle(T a, T b, T c, TriangleType t) : sideA(a), sideB(b), sideC(c), type(t) {
        validateTriangle();
    }
    double calculatePerimeter() const override { return sideA + sideB + sideC; }
    double calculateArea() const override {
        double p = calculatePerimeter() / 2.0;
        return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
    }
    T getA() const { return sideA; }
    T getB() const { return sideB; }
    T getC() const { return sideC; }
};

template <typename T>
bool compareShapes(const Shape<T>& a, const Shape<T>& b) {
    return a.calculateArea() == b.calculateArea();
}

template <typename T>
bool compareShapes(const Rectangle<T>& a, const Rectangle<T>& b) {
    return a.getWidth() == b.getWidth() && a.getHeight() == b.getHeight();
}

template <typename T>
bool compareShapes(const Triangle<T>& a, const Triangle<T>& b) {
    return a.getA() == b.getA() && a.getB() == b.getB() && a.getC() == b.getC();
}

int main() {
    cout << "--- ADDITIONAL TASK ---" << endl;

    try {
        Rectangle<double> rect1(4.0, 5.0);
        Rectangle<double> rect2(4.0, 5.0);
        Circle<double> circ(3.0);
        Triangle<double> tri1(3.0, 4.0, 5.0, TriangleType::Scalene);
        Triangle<double> tri2(3.0, 4.0, 5.0, TriangleType::Scalene);

        cout << "Circle area: " << circ.calculateArea() << endl;
        cout << "Triangle area: " << tri1.calculateArea() << endl;

        cout << "Are rect1 and rect2 identical (by sides)? " << boolalpha << compareShapes(rect1, rect2) << endl;
        cout << "Are tri1 and tri2 identical (by sides)? " << compareShapes(tri1, tri2) << endl;

        cout << "\nAttempting to create an invalid circle (radius -5)..." << endl;
        Circle<double> badCirc(-5.0);
    }
    catch (const exception& e) {
        cout << "EXCEPTION HANDLED: " << e.what() << endl;
    }

    try {
        cout << "\nAttempting to create a non-existent triangle (sides 1, 2, 10)..." << endl;
        Triangle<double> badTri(1.0, 2.0, 10.0, TriangleType::Scalene);
    }
    catch (const exception& e) {
        cout << "EXCEPTION HANDLED: " << e.what() << endl;
    }

    return 0;
}