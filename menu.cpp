#include "Menu.h"
#include <fstream>
#include <iostream>

Menu::Menu() {
    loadUsersFromFile();

    bool adminExists = false;
    for (const auto* user : users) {
        if (dynamic_cast<const Admin*>(user)) {
            adminExists = true;
            break;
        }
    }

    if (!adminExists) {
        users.push_back(new Admin());
    }
}

Menu::~Menu() {
    saveUsersToFile();
    for (auto* user : users) {
        delete user;
    }
}

void Menu::saveUsersToFile() const {
    std::ofstream outFile("users.txt");
    if (!outFile) {
        std::cerr << "Error saving users to file.\n";
        return;
    }

    for (const auto* user : users) {
        if (user == nullptr) {
            continue; // Skip if the pointer is null
        }
        if (dynamic_cast<const Admin*>(user)) {
            continue;
        }
        std::string type = typeid(*user).name();
        outFile << type << '\n';
        user->saveToFile(outFile);
        outFile << "END\n"; // Mark the end of a user's data for clarity
    }
}

void Menu::loadUsersFromFile() {
    std::ifstream inFile("users.txt");
    if (!inFile) {
        std::cerr << "Error: Unable to open users.txt for reading.\n";
        return;
    }

    std::string type;
    while (std::getline(inFile, type)) {
         if (type == "Teacher") {
            users.push_back(new Teacher(inFile));
        }
        else if (type == "Student") {
            users.push_back(new Student(inFile));
        }
        else {
            std::cerr << "Unknown user type: " << type << "\n";
            continue;
        }

        std::string endMarker;
        std::getline(inFile, endMarker);
        if (endMarker != "END") {
            std::cerr << "Error: Missing END marker for user type " << type << "\n";
        }
    }

    std::cout << "Loaded " << users.size() << " users from file.\n";
}


void Menu::registerStudent() {
    std::string username, password;
    std::cout << "Enter new Student Username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> password;

    auto* newStudent = new Student(username, password);
    users.push_back(newStudent);

    std::ofstream outFile("users.txt", std::ios::app);
    if (!outFile) {
        std::cerr << "Error saving student to file.\n";
        return;
    }

    outFile << "Student\n";
    outFile << username << '\n';
    outFile << password << '\n';
    outFile << "END\n";

    std::cout << "Student registered successfully.\n";
}



void Menu::displayMainMenu() {
    while (true) {
        std::cout << "Main Menu:\n";
        std::cout << "1. Log in as Admin\n";
        std::cout << "2. Log in as Teacher\n";
        std::cout << "3. Log in as Student\n";
        std::cout << "4. Register as Student\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string username, password;
            std::cout << "Enter Admin Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            std::cin >> password;

            for (auto* user : users) {
                if (auto* admin = dynamic_cast<Admin*>(user)) {
                    if (admin->getUsername() == username && admin->verifyPassword(password)) {
                        adminMenu(admin);
                        return;
                    }
                }
            }
            std::cout << "Invalid Admin credentials.\n";
            break;
        }
        case 2: {
            std::string username, password;
            std::cout << "Enter Teacher Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            std::cin >> password;

            for (auto* user : users) {
                if (auto* teacher = dynamic_cast<Teacher*>(user)) {
                    if (teacher->getUsername() == username && teacher->verifyPassword(password)) {
                        teacherMenu(teacher);
                        return;
                    }
                }
            }
            std::cout << "Invalid Teacher credentials.\n";
            break;
        }
        case 3: {
            std::string username, password;
            std::cout << "Enter Student Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            std::cin >> password;

            for (auto* user : users) {
                if (auto* student = dynamic_cast<Student*>(user)) {
                    if (student->getUsername() == username && student->verifyPassword(password)) {
                        studentMenu(student);
                        return;
                    }
                }
            }
            std::cout << "Invalid Student credentials.\n";
            break;
        }
        case 4:
            registerStudent();
            break;
        case 5:
            return;
        default:
            std::cout << "Invalid choice.\n";
        }
    }
}

void Menu::adminMenu(Admin* admin) {
    int choice;
    do {
        admin->displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            admin->viewStudents(users);
            break;
        case 2:
            admin->viewTeachers(users);
            break;
        case 3:
            admin->addTeacher(users);
            break;
        case 4:
            admin->addStudent(users);
            break;
        case 5:
            admin->deleteTeacher(users);
            break;
        case 6:
            admin->deleteStudent(users);
            break;
        case 7:
            admin->addCourse(courses);
            break;
        case 8:
            admin->deleteCourse(courses);
            break;
        case 0:
            displayMainMenu();
            std::cout << "Returning to main menu...\n";
            return;  // Повертає до головного меню
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}



void Menu::teacherMenu(Teacher* teacher) {
    int choice;
    do {
        teacher->displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            teacher->viewCourses(courses);
            break;
        case 2:
            teacher->viewStudentsInCourse(courses);
            break;
        case 3:
            teacher->addStudentToCourse(courses);
            break;
        case 4:
            teacher->removeStudentFromCourse(courses);
            break;
        case 5:
            teacher->assignGradeToStudent();
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void Menu::studentMenu(Student* student) {
    std::cout << "Student menu coming soon.\n";
}
