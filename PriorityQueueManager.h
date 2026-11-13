#pragma once
#include <queue>
#include <fstream>
#include <algorithm>
#include "Worker.h"

inline void managePriorityQueue(priority_queue<Worker*>& c, const string& title) {
    int ch;
    do {
        cout << "\n--- МЕНЮ [" << title << "] (Приоритет: ЗП) ---\n"
            << "1. Добавить (push)\n"
            << "2. Удалить самый приоритетный (pop)\n"
            << "3. Вывод на экран\n"
            << "4. Сохранить в файл\n"
            << "5. Поиск по ФИО\n"
            << "6. Редактировать элемент\n"
            << "7. Фильтрация (по статусу)\n"
            << "0. Назад\nВыбор: ";
        ch = inputInt();

        if (ch == 1) {
            c.push(inputNewWorkerPointer());
            cout << "Элемент добавлен!\n";
        }
        else if (ch == 2) {
            if (c.empty()) cout << "Очередь пуста!\n";
            else {
                delete c.top();
                c.pop();
                cout << "Самый приоритетный элемент удален.\n";
            }
        }
        else if (ch == 3) {
            if (c.empty()) { cout << "Очередь пуста.\n"; continue; }
            cout << "\nСодержимое приоритетной очереди (по убыванию ЗП):\n";
            printHeader();

            vector<Worker*> vec;
            priority_queue<Worker*> temp = c;
            while (!temp.empty()) {
                vec.push_back(temp.top());
                temp.pop();
            }
            sort(vec.begin(), vec.end(), [](Worker* a, Worker* b) {
                return a->getSalary() > b->getSalary();
                });

            int idx = 0;
            for (Worker* w : vec) {
                cout << left << setw(4) << idx++;
                w->print(cout);
                cout << "\n";
            }
            cout << "------------------------------------------------------------------------\n";
        }
        else if (ch == 4) {
            ofstream f(title + "_data.txt");
            priority_queue<Worker*> temp = c;
            while (!temp.empty()) {
                temp.top()->saveToFile(f);
                f << "\n";
                temp.pop();
            }
            f.close();
            cout << "Сохранено в " << title << "_data.txt\n";
        }
        else if (ch == 5) {
            if (c.empty()) { cout << "Очередь пуста.\n"; continue; }
            cout << "Введите часть ФИО для поиска: ";
            string query = inputLine();

            priority_queue<Worker*> temp = c;
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
            if (c.empty()) { cout << "Очередь пуста.\n"; continue; }
            vector<Worker*> vec;
            while (!c.empty()) { vec.push_back(c.top()); c.pop(); }

            cout << "\nСписок элементов (для редактирования):\n";
            for (size_t i = 0; i < vec.size(); ++i) {
                cout << i << ". " << vec[i]->getName() << " (ЗП: " << vec[i]->getSalary() << ")\n";
            }
            cout << "Введите индекс элемента для редактирования: ";
            int idx = inputInt();
            if (idx >= 0 && idx < (int)vec.size()) {
                vec[idx]->edit();
                cout << "Элемент отредактирован!\n";
            }
            else {
                cout << "Неверный индекс!\n";
            }

            sort(vec.begin(), vec.end(), [](Worker* a, Worker* b) {
                return a->getSalary() < b->getSalary();
                });

            for (Worker* w : vec) {
                c.push(w);
            }
        }
        else if (ch == 7) {
            if (c.empty()) { cout << "Очередь пуста.\n"; continue; }
            cout << "Фильтр: 1 - Активные, 0 - В отпуске: ";
            bool act = (inputInt() == 1);

            priority_queue<Worker*> temp = c;
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