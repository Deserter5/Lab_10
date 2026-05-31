#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
bool compareValues(T a, T b) {
    return a == b;
}

template <typename T>
class List {
private:
    vector<T> elements;
public:
    void add(T item) {
        elements.push_back(item);
    }

    void remove() {
        if (!elements.empty()) {
            elements.pop_back();
        }
    }

    void print() const {
        cout << "[ ";
        for (const auto& el : elements) {
            cout << el << " ";
        }
        cout << "]" << endl;
    }
};

template <typename T>
class Figure {
public:
    virtual T getArea() const = 0;
    virtual T getPerimeter() const = 0;
    virtual ~Figure() {}
};

template <typename T>
class Rectangle : public Figure<T> {
private:
    T width, height;
public:
    Rectangle(T w, T h) : width(w), height(h) {}
    T getArea() const override { return width * height; }
    T getPerimeter() const override { return 2 * (width + height); }
};

template <typename T>
class Circle : public Figure<T> {
private:
    T radius;
    const T PI = 3.14159;
public:
    Circle(T r) : radius(r) {}
    T getArea() const override { return PI * radius * radius; }
    T getPerimeter() const override { return 2 * PI * radius; }
};

class ArrayProcessor {
public:
    template <typename T, size_t N>
    double getAverage(const T(&arr)[N]) {
        double sum = 0;
        for (size_t i = 0; i < N; ++i) {
            sum += arr[i];
        }
        return sum / N;
    }
};

int main() {
    cout << "--- Task 1: Function template ---" << endl;
    cout << "int (5 == 5): " << boolalpha << compareValues(5, 5) << endl;
    cout << "double (3.14 == 2.71): " << compareValues(3.14, 2.71) << endl;
    cout << "string (\"C++\" == \"C++\"): " << compareValues(string("C++"), string("C++")) << endl;

    cout << "\n--- Task 2: Class template ---" << endl;
    List<int> intList;
    cout << "Adding int: "; intList.add(10); intList.add(20); intList.print();
    cout << "Removing int: "; intList.remove(); intList.print();

    List<double> doubleList;
    cout << "Adding double: "; doubleList.add(3.14); doubleList.add(2.71); doubleList.print();

    List<string> strList;
    cout << "Adding string: "; strList.add("Hello"); strList.add("World"); strList.print();

    cout << "\n--- Task 3: Inheritance ---" << endl;
    Rectangle<int> rectInt(4, 5);
    cout << "Rectangle (int): Area = " << rectInt.getArea() << ", Perimeter = " << rectInt.getPerimeter() << endl;

    Circle<double> circleDouble(2.5);
    cout << "Circle (double): Area = " << circleDouble.getArea() << ", Perimeter = " << circleDouble.getPerimeter() << endl;

    cout << "\n--- Task 4: Class with template method ---" << endl;
    ArrayProcessor proc;
    int arrInt[] = { 1, 2, 3, 4, 5 };
    double arrDouble[] = { 1.5, 2.5, 3.5 };

    cout << "Average of int array: " << proc.getAverage(arrInt) << endl;
    cout << "Average of double array: " << proc.getAverage(arrDouble) << endl;

    return 0;
}