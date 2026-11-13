#pragma once
#include <stack>
#include <fstream>
#include <algorithm>
#include "Worker.h"

inline void manageStack(stack<Worker*>& c, const string& title) {
    int ch;
    do {
        cout << "\n--- МЕНЮ [" << title << "] (LIFO) ---\n"
            << "1. Добавить (push)\n"
            << "2. Удалить верхний (pop)\n"
            << "3. Вывод на экран\n"
            << "4. Сохранить в файл\n"
            << "5. Поиск по ФИО\n"
            << "6. Редактировать элемент\n"
            << "7. Сортировка (по зарплате)\n"
            << "8. Фильтрация (по статусу)\n"
            << "0. Назад\nВыбор: ";
        ch = inputInt();

        if (ch == 1) {
            c.push(inputNewWorkerPointer());
            cout << "Элемент добавлен на вершину стека!\n";
        }
        else if (ch == 2) {
            if (c.empty()) cout << "Стек пуст!\n";
            else {
                delete c.top();
                c.pop();
                cout << "Верхний элемент удален.\n";
            }
        }
        else if (ch == 3) {
            if (c.empty()) { cout << "Стек пуст.\n"; continue; }
            cout << "\nСодержимое стека (от вершины к основанию):\n";
            printHeader();

            stack<Worker*> temp = c;
            int idx = 0;
            while (!temp.empty()) {
                cout << left << setw(4) << idx++;
                temp.top()->print(cout);
                cout << "\n";
                temp.pop();
            }
            cout << "------------------------------------------------------------------------\n";
        }
        else if (ch == 4) {
            ofstream f(title + "_data.txt");
            stack<Worker*> temp = c;
            while (!temp.empty()) {
                temp.top()->saveToFile(f);
                f << "\n";
                temp.pop();
            }
            f.close();
            cout << "Сохранено в " << title << "_data.txt\n";
        }
        else if (ch == 5) {
            if (c.empty()) { cout << "Стек пуст.\n"; continue; }
            cout << "Введите часть ФИО для поиска: ";
            string query = inputLine();

            stack<Worker*> temp = c;
            bool found = false;
            while (!temp.empty()) {
                if (temp.top()->getName().find(query) != string::npos) { found = true; break; }
                temp.pop();
            }

            if (!found) {
                cout << "Ничего не найдено.\n";
            }
            else {
                temp = c; 
                printHeader();
                int idx = 0;
                while (!temp.empty()) {
                    if (temp.top()->getName().find(query) != string::npos) {
                        cout << left << setw(4) << idx;
                        temp.top()->print(cout);
                        cout << "\n";
                        idx++;
                    }
                    temp.pop();
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
        else if (ch == 6) {
            if (c.empty()) { cout << "Стек пуст.\n"; continue; }
            vector<Worker*> vec;
            while (!c.empty()) { vec.push_back(c.top()); c.pop(); }

            cout << "\nСписок элементов стека:\n";
            for (size_t i = 0; i < vec.size(); ++i) {
                cout << i << ". " << vec[i]->getName() << " (" << vec[i]->getType() << ")\n";
            }
            cout << "Введите индекс элемента для редактирования: ";
            int idx = inputInt();
            if (idx >= 0 && idx < (int)vec.size()) {
                vec[idx]->edit();
                cout << "Элемент успешно отредактирован!\n";
            }
            else {
                cout << "Неверный индекс!\n";
            }
            for (int i = (int)vec.size() - 1; i >= 0; --i) {
                c.push(vec[i]);
            }
        }
        else if (ch == 7) {
            if (c.empty()) { cout << "Стек пуст.\n"; continue; }
            vector<Worker*> vec;
            while (!c.empty()) { vec.push_back(c.top()); c.pop(); }

            sort(vec.begin(), vec.end(), [](Worker* a, Worker* b) {
                return a->getSalary() > b->getSalary();
                });

            for (int i = (int)vec.size() - 1; i >= 0; --i) {
                c.push(vec[i]);
            }
            cout << "Стек отсортирован по убыванию зарплаты!\n";
        }
        else if (ch == 8) {
            if (c.empty()) { cout << "Стек пуст.\n"; continue; }
            cout << "Фильтр: 1 - Активные, 0 - В отпуске: ";
            bool act = (inputInt() == 1);

            stack<Worker*> temp = c;
            bool found = false;
            while (!temp.empty()) {
                if (temp.top()->getActive() == act) { found = true; break; }
                temp.pop();
            }

            if (!found) {
                cout << "Ничего не найдено.\n";
            }
            else {
                temp = c;
                printHeader();
                int idx = 0;
                while (!temp.empty()) {
                    if (temp.top()->getActive() == act) {
                        cout << left << setw(4) << idx;
                        temp.top()->print(cout);
                        cout << "\n";
                        idx++;
                    }
                    temp.pop();
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
    } while (ch != 0);
}