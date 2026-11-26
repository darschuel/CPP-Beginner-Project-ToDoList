#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

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
    if (task.completed) {
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

    int maxId = 0;
    for (const auto& task : tasks) {
        if (task.task_id > maxId) {
            maxId = task.task_id;
        }
    }
    task.task_id = maxId + 1;

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

static void cinInputValidation(auto& inp, std::vector<Task>& tasks, int& index) {
    while (true) {
        if (!(std::cin >> inp)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else {
            index = findTaskIndex(tasks, inp);
            if (index != -1) {
                break;
            }
        }
        std::cout << "Please choose a valid Task ID: \n";
    }
}

static void completeTask(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }
    int inp;
    std::cout << "Which task do you want to complete?: \n";
    for (const auto& task : tasks) {
        std::cout << task.task_id << ". " << task.name << " Status: " << statusCheck(task) << std::endl;
    }

    int index = -1;
    cinInputValidation(inp, tasks, index);

    std::cout << "Completing Task " << inp << "\n";
    tasks[index].completed = true;
}

static void deleteTask(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }
    int inp;
    std::cout << "Which task do you want to delete?: \n";
    for (const auto& task : tasks) {
        std::cout << task.task_id << ". " << task.name << " Status: " << statusCheck(task) << std::endl;;
    }

    std::cout << "choose a Task by ID: \n";

    int index = -1;

    cinInputValidation(inp, tasks, index);

    tasks.erase(tasks.begin() + index);
}

static void saveTask(const std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    if (!file) {
        std::cout << "could not save tasks\n";
        return;
    }
    for (const auto& task : tasks) {
        file << task.name << "\n"
             << task.description << "\n"
             << task.created_at << "\n"
             << task.task_id << "\n"
             << task.completed << "\n";
    }
}

static void loadTasks(std::vector<Task>& tasks) {
    std::ifstream file("tasks.txt");
    if (!file) {
        return;
    }
    Task task;
    while (std::getline(file, task.name) &&
           std::getline(file, task.description) &&
           (file >> task.created_at >> task.task_id >> task.completed)) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        tasks.push_back(task);
           }
}

int main() {
    std::vector<Task> tasks;
    loadTasks(tasks);
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
            case '5':
                saveTask(tasks);
                std::cout << "Exiting now\n";
                return 0;
            default:
                std::cout << "Please choose a valid option: \n";
        }
    }

    return 0;
}