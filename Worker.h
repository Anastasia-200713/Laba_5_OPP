#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

inline void clearInput() {
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

inline int inputInt() {
    int val;
    while (true) {
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Ошибка! Введите целое число: ";
        }
        else {
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            return val;
        }
    }
}

inline double inputDouble() {
    double val;
    while (true) {
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Ошибка! Введите число: ";
        }
        else {
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            return val;
        }
    }
}

inline string inputLine() {
    string s;
    getline(cin, s);
    while (s.empty()) {
        cout << "Ошибка! Строка не может быть пустой. Введите заново: ";
        getline(cin, s);
    }
    return s;
}

class Worker {
protected:
    string name;
    bool active;
    double salary;
public:
    Worker() : name(""), active(true), salary(0.0) {}
    Worker(const string& name, double salary, bool active = true)
        : name(name), active(active), salary(salary) {
    }
    virtual ~Worker() {}

    string getName() const { return name; }
    bool getActive() const { return active; }
    double getSalary() const { return salary; }

    void setName(const string& n) { name = n; }
    void setSalary(double s) { salary = s; }
    void setActive(bool a) { active = a; }

    virtual string getType() const { return "Worker"; }
    virtual void print(ostream& os) const {
        os << left << setw(16) << name
            << "| " << setw(10) << getType()
            << "| " << setw(10) << (active ? "Активен" : "Отпуск")
            << "| " << setw(10) << fixed << setprecision(2) << salary;
    }
    virtual void saveToFile(ostream& os) const {
        os << name << ";" << getType() << ";" << (active ? "Active" : "Vacation") << ";" << salary;
    }
    virtual void edit() {
        cout << "Введите новое ФИО (" << name << "): ";
        name = inputLine();
        cout << "Введите новую зарплату (" << salary << "): ";
        salary = inputDouble();
        cout << "Введите статус (1 - Активен, 0 - В отпуске): ";
        active = (inputInt() == 1);
    }

    bool operator<(const Worker& other) const {
        return salary < other.salary;
    }
};

class Builder : public Worker {
    int qualification;
public:
    Builder() : Worker(), qualification(1) {}
    Builder(const string& name, double salary, int qualification, bool active = true)
        : Worker(name, salary, active), qualification(qualification) {
    }

    int getQualification() const { return qualification; }
    void setQualification(int q) { qualification = q; }
    string getType() const override { return "Builder"; }

    void print(ostream& os) const override {
        Worker::print(os);
        os << "| " << setw(10) << qualification;
    }
    void saveToFile(ostream& os) const override {
        Worker::saveToFile(os);
        os << ";" << qualification;
    }
    void edit() override {
        Worker::edit();
        cout << "Введите новый разряд (1-6) (" << qualification << "): ";
        qualification = inputInt();
    }
};

class Engineer : public Worker {
    double allowance;
public:
    Engineer() : Worker(), allowance(0.0) {}
    Engineer(const string& name, double salary, double allowance, bool active = true)
        : Worker(name, salary, active), allowance(allowance) {
    }

    double getAllowance() const { return allowance; }
    void setAllowance(double a) { allowance = a; }
    string getType() const override { return "Engineer"; }

    void print(ostream& os) const override {
        Worker::print(os);
        os << "| " << setw(10) << fixed << setprecision(2) << allowance;
    }
    void saveToFile(ostream& os) const override {
        Worker::saveToFile(os);
        os << ";" << allowance;
    }
    void edit() override {
        Worker::edit();
        cout << "Введите новую надбавку (" << allowance << "): ";
        allowance = inputDouble();
    }
};

inline Worker* inputNewWorkerPointer() {
    cout << "Выберите тип (1 - Строитель, 2 - Инженер): ";
    int type = inputInt();
    cout << "ФИО: "; string name = inputLine();
    cout << "Зарплата: "; double salary = inputDouble();
    cout << "Статус (1 - Активен, 0 - В отпуске): "; bool active = (inputInt() == 1);

    if (type == 1) {
        cout << "Разряд (1-6): "; int q = inputInt();
        return new Builder(name, salary, q, active);
    }
    else {
        cout << "Надбавка: "; double a = inputDouble();
        return new Engineer(name, salary, a, active);
    }
}

inline void printHeader() {
    cout << "------------------------------------------------------------------------\n";
    cout << left << setw(4) << "№"
        << "| " << setw(14) << "ФИО"
        << "| " << setw(10) << "Должн."
        << "| " << setw(10) << "Статус"
        << "| " << setw(10) << "Зарплата"
        << "| " << setw(10) << "Разряд/Надб." << "\n";
    cout << "------------------------------------------------------------------------\n";
}