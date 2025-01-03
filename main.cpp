#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

// Struct Definition (Move this above the function declarations)
struct Task {
    string description;
    bool completed;
};

// Function Declarations
void loadTasks(vector<Task>& tasks);
void saveTasks(const vector<Task>& tasks);
void displayTasks(const vector<Task>& tasks);
void addTask(vector<Task>& tasks);
void updateTask(vector<Task>& tasks);
void deleteCompletedTasks(vector<Task>& tasks);

int main() {
    vector<Task> tasks;

    loadTasks(tasks); // Automatically load tasks from file on program start

    int choice;
    do {
        cout << "\nTo-Do List\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Complete\n";
        cout << "4. Delete Completed Tasks\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                displayTasks(tasks);
                break;
            case 3:
                updateTask(tasks);
                break;
            case 4:
                deleteCompletedTasks(tasks);
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}

// Function Definitions
void loadTasks(vector<Task>& tasks) {
    ifstream file("todo.txt");
    string line;
    while (getline(file, line)) {
        Task task;
        task.description = line;
        task.completed = false; // Tasks loaded from file are not completed by default
        tasks.push_back(task);
    }
    file.close();
}

void saveTasks(const vector<Task>& tasks) {
    ofstream file("todo.txt");
    for (const auto& task : tasks) {
        file << task.description << endl;
    }
    file.close();
}

void displayTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available!" << endl;
        return;
    }
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].description << (tasks[i].completed ? " [Completed]" : "") << endl;
    }
}

void addTask(vector<Task>& tasks) {
    string description;
    cout << "Enter task description: ";
    cin.ignore(); // To clear the buffer
    getline(cin, description);
    tasks.push_back({ description, false });
    saveTasks(tasks); // Automatically save after adding a task
}

void updateTask(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to mark as complete: ";
    cin >> index;
    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        saveTasks(tasks); // Automatically save after updating a task
    } else {
        cout << "Invalid task number!" << endl;
    }
}

void deleteCompletedTasks(vector<Task>& tasks) {
    // Delete all completed tasks automatically
    tasks.erase(remove_if(tasks.begin(), tasks.end(), [](const Task& task) {
        return task.completed;
    }), tasks.end());
    saveTasks(tasks); // Automatically save after deletion
}

