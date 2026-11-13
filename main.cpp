#include <iostream>
#include <stack>
#include <queue>
#include <windows.h>
#include "Worker.h"
#include "StackManager.h"
#include "QueueManager.h"
#include "PriorityQueueManager.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    stack<Worker*> workerStack;
    queue<Worker*> workerQueue;
    priority_queue<Worker*> workerPriorityQueue;

    workerStack.push(new Builder("Иванов И.И.", 1600.0, 5, true));
    workerStack.push(new Builder("Петров П.П.", 1300.0, 4, true));

    workerQueue.push(new Engineer("Смирнова Е.А.", 2200.0, 450.0, true));
    workerQueue.push(new Builder("Сидоров С.С.", 1500.0, 3, false));

    workerPriorityQueue.push(new Builder("Иванов И.И.", 1600.0, 5, true));
    workerPriorityQueue.push(new Engineer("Смирнова Е.А.", 2200.0, 450.0, true));
    workerPriorityQueue.push(new Builder("Петров П.П.", 1300.0, 4, true));

    int choice = -1;
    do {
        cout << "\n===================================================================\n";
        cout << " ЛАБОРАТОРНАЯ РАБОТА №5: АДАПТЕРЫ КОНТЕЙНЕРОВ STL\n";
        cout << " Предметная область: Учет данных о работниках строительной организации\n";
        cout << "===================================================================\n";
        cout << " 1. STACK (LIFO - Стек)\n";
        cout << " 2. QUEUE (FIFO - Очередь)\n";
        cout << " 3. PRIORITY_QUEUE (Очередь с приоритетом)\n";
        cout << " 0. Выход из программы\n";
        cout << "Ваш выбор: ";

        choice = inputInt();

        if (choice == 1) manageStack(workerStack, "STACK");
        else if (choice == 2) manageQueue(workerQueue, "QUEUE");
        else if (choice == 3) managePriorityQueue(workerPriorityQueue, "PRIORITY_QUEUE");
        else if (choice != 0) {
            cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);

    while (!workerStack.empty()) { delete workerStack.top(); workerStack.pop(); }
    while (!workerQueue.empty()) { delete workerQueue.front(); workerQueue.pop(); }
    while (!workerPriorityQueue.empty()) { delete workerPriorityQueue.top(); workerPriorityQueue.pop(); }

    cout << "Завершение работы программы.\n";
    return 0;
}