#pragma once
#include <queue>
#include <fstream>
#include <algorithm>
#include "Worker.h"

inline void manageQueue(queue<Worker*>& c, const string& title) {
    int ch;
    do {
        cout << "\n--- МЕНЮ [" << title << "] (FIFO) ---\n"
            << "1. Добавить в конец (push)\n"
            << "2. Удалить из начала (pop)\n"
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
            cout << "Элемент добавлен в очередь!\n";
        }
        else if (ch == 2) {
            if (c.empty()) cout << "Очередь пуста!\n";
            else {
                delete c.front();
                c.pop();
                cout << "Первый элемент удален.\n";
            }
        }
        else if (ch == 3) {
            if (c.empty()) { cout << "Очередь пуста.\n"; continue; }
            cout << "\nСодержимое очереди (от начала к концу):\n";
            printHeader();

            queue<Worker*> temp = c;
            int idx = 0;
            while (!temp.empty()) {
                cout << left << setw(4) << idx++;
                temp.front()->print(cout);
                cout << "\n";
                temp.pop();
            }
            cout << "------------------------------------------------------------------------\n";
        }
        else if (ch == 4) {
            ofstream f(title + "_data.txt");
            queue<Worker*> temp = c;
            while (!temp.empty()) {
                temp.front()->saveToFile(f);
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

            queue<Worker*> temp = c;
            bool found = false;
            while (!temp.empty()) {
                if (temp.front()->getName().find(query) != string::npos) { found = true; break; }
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
                    if (temp.front()->getName().find(query) != string::npos) {
                        cout << left << setw(4) << idx;
                        temp.front()->print(cout);
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
            while (!c.empty()) { vec.push_back(c.front()); c.pop(); }

            cout << "\nСписок элементов очереди:\n";
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
            for (size_t i = 0; i < vec.size(); ++i) {
                c.push(vec[i]);
            }
        }
        else if (ch == 7) {
            if (c.empty()) { cout << "Очередь пуста.\n"; continue; }
            vector<Worker*> vec;
            while (!c.empty()) { vec.push_back(c.front()); c.pop(); }

            sort(vec.begin(), vec.end(), [](Worker* a, Worker* b) {
                return a->getSalary() < b->getSalary();
                });

            for (size_t i = 0; i < vec.size(); ++i) {
                c.push(vec[i]);
            }
            cout << "Очередь отсортирована по возрастанию зарплаты!\n";
        }
        else if (ch == 8) {
            if (c.empty()) { cout << "Очередь пуста.\n"; continue; }
            cout << "Фильтр: 1 - Активные, 0 - В отпуске: ";
            bool act = (inputInt() == 1);

            queue<Worker*> temp = c;
            bool found = false;
            while (!temp.empty()) {
                if (temp.front()->getActive() == act) { found = true; break; }
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
                    if (temp.front()->getActive() == act) {
                        cout << left << setw(4) << idx;
                        temp.front()->print(cout);
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