#include <iostream>

using std::cout;
using std::endl;

class MyStudent1 {
public:
    MyStudent1() : midterm(0), final(0) { }
    
    double get_midterm() const { return midterm; }
    double get_final() const { return final; }

private:
    double midterm;
    double final;
};

class MyStudent2 {
public:
    MyStudent2() { }

    double get_midterm() const { return midterm; }
    double get_final() const { return final; }

private:
    double midterm;
    double final;
};

class MyStudent3 {
public:
    double get_midterm() const { return midterm; }
    double get_final() const { return final; }

private:
    double midterm;
    double final;
};

int main() {
    cout << "Starting." << endl;

    MyStudent1 student1;
    MyStudent2 student2;
    MyStudent3 student3;

    // Output:

    cout << "Student 1 (explicit initialization) has " << student1.get_midterm() << ", " << student1.get_final() << endl;
    cout << "Student 2 (explicit constructor without initialization) has " << student2.get_midterm() << ", " << student2.get_final() << endl;
    cout << "Student 3 (synthesized default constructor) has " << student3.get_midterm() << ", " << student3.get_final() << endl;

    cout << "End." << endl;
    return 0;
}

