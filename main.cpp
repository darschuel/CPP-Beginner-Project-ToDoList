#include <iostream>
#include <string>
#include <ctime>

struct Task {
    std::string name;
    std::string description;
    std::time_t created_at = std::time(nullptr);
    int task_id = 1;
    bool completed = false;
};

std::string statusCheck(const Task& task) {
    if (task.completed == true) {
        return "Completed";
    } else {
        return "Not Completed";
    }
}



void viewTask(std::vector<Task>& tasks) {
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << tasks[i].task_id << ".\n"
              << tasks[i].name << "\n"
              << tasks[i].description << "\n"
              << tasks[i].created_at << "\n"
              << statusCheck(tasks[i]) << "\n";
    }
}

void addTask(std::vector<Task>& tasks) {
    Task task;
    std::cout << "name of the task: \n";
    std::getline(std::cin, task.name);

    std::cout << "description of the task: \n";
    std::getline(std::cin, task.description);

    task.task_id = tasks.size() + 1;

    tasks.push_back(task);
}

void completeTask(std::vector<Task>& tasks) {
    char inp;
    std::cout << "Which task do you want to complete?: \n";
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << tasks[i].task_id << ". " << tasks[i].name << " Status: " << statusCheck(tasks[i]) << std::endl;;
    }

    std::cout << "choose a Task by ID: \n";
    std::cin >> inp;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].task_id == inp) {
            tasks[i].completed = true;
            break;
        }
    }

}

void deleteTask(std::vector<Task>& tasks) {
    char inp;
    Task task;
    std::cout << "Which task do you want to delete?: \n";
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << tasks[i].task_id << ". " << tasks[i].name << " Status: " << statusCheck(tasks[i]) << std::endl;;
    }

    std::cout << "choose a Task by ID: \n";
    std::cin >> inp;

    tasks.erase(tasks.begin() + inp);
}

int main() {
    std::vector<Task> tasks;
    char input;
    while (true) {
        std::cout << "-----ToDo List-----\n\n";
        std::cout << "1. View tasks\n";
        std::cout << "2. Add task\n";
        std::cout << "3. Complete task\n";
        std::cout << "4. Delete tasks\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: \n\n";

        std::cin >> input;

        switch (input) {
            case '1':
                viewTask(tasks);
                break;
            case '2':
                addTask(tasks);
                break;
            case '3':
                completeTask(tasks);
                break;
            case '4':
                deleteTask(tasks);
                break;
            default:;
        }

        if (input == '5') {
            std::cout << "Exiting now\n";
            break;
        }



    }








    return 0;
}