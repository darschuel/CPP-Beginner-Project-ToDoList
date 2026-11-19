#include <iostream>
#include <string>
#include <ctime>
#include <vector>

struct Task {
    std::string name;
    std::string description;
    std::time_t created_at = std::time(nullptr);
    int task_id = 1;
    bool completed = false;
};

static std::string formatTime(const std::time_t time) {
    char buffer[16];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", std::localtime(&time));
    return buffer;
}

static std::string statusCheck(const Task& task) {
    if (task.completed == true) {
        return "Completed";
    }
    return "Not Completed";
}


static void viewTask(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
    }else {
        for (const auto& task : tasks) {
            std::cout << task.task_id << ". "
                  << task.name << "\n"
                  << "Description: " << task.description << "\n"
                  << "created at: " << formatTime(task.created_at) << "\n"
                  << "Status: " << statusCheck(task) << "\n";
        }
    }


}

static void addTask(std::vector<Task>& tasks) {
    Task task;
    std::cout << "name of the task: \n";
    std::cin >> std::ws;
    getline(std::cin, task.name);

    std::cout << "description of the task: \n";
    std::cin >> std::ws;
    getline(std::cin, task.description);

    task.task_id = tasks.size() + 1;

    tasks.push_back(task);
}

static int findTaskIndex(const std::vector<Task>& tasks, int id) {
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].task_id == id) {
            return i;
        }
    }
    return -1;
}

static void completeTask(std::vector<Task>& tasks) {
    int inp;
    std::cout << "Which task do you want to complete?: \n";
    for (const auto& task : tasks) {
        std::cout << task.task_id << ". " << task.name << " Status: " << statusCheck(task) << std::endl;;
    }

    int index = -1;
    while (index == -1) {
        std::cout << "Choose task by ID.\n";
        std::cin >> inp;
        index = findTaskIndex(tasks, inp);
        if (index == -1) {
            std::cout << "Please choose a valid Task ID: \n";
        }
    }

    std::cout << "Completing Task " << inp << "\n";
    tasks[index].completed = true;
}

static void deleteTask(std::vector<Task>& tasks) {
    int inp;
    std::cout << "Which task do you want to delete?: \n";
    for (const auto& task : tasks) {
        std::cout << task.task_id << ". " << task.name << " Status: " << statusCheck(task) << std::endl;;
    }

    std::cout << "choose a Task by ID: \n";
    std::cin >> inp;

    int index = findTaskIndex(tasks, inp);
    if (index != -1) {
        tasks.erase(tasks.begin() + index);
    }else {
        std::cout << "Please choose a valid Task ID: \n";
    }
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