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



void viewTask(const Task task) {
    std::cout << task.task_id << "." << std::endl << task.name << std::endl << task.description << std::endl
    << task.created_at << std::endl << task.completed << std::endl;
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

int main() {
    std::vector<Task> tasks;

    std::cout << "-----ToDo List-----\n\n";
    std::cout << "1. View tasks\n";
    std::cout << "2. Add task\n";
    std::cout << "3. Complete task\n";
    std::cout << "4. Delete tasks\n";
    std::cout << "5. Exit\n";

    std::cout << "Choose an option: \n\n"


    return 0;
}