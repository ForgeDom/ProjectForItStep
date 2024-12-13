#include "Admin.h"
#include <iostream>
#include <fstream>

Admin::Admin(const std::string& username, const std::string& password)
    : User(username, password) {}

Admin::Admin(std::ifstream& inFile) {
    std::getline(inFile, username);
    std::getline(inFile, password);
}

void Admin::saveToFile(std::ofstream& outFile) const {
    outFile << username << '\n';
    outFile << password << '\n';
}


void Admin::displayMenu() const {
    std::cout << "Admin Menu:\n";
    std::cout << "1. View all students\n";
    std::cout << "2. View all teachers\n";
    std::cout << "3. Add Teacher\n";
    std::cout << "4. Add Student\n";
    std::cout << "5. Delete Teacher\n";
    std::cout << "6. Delete Student\n";
    std::cout << "7. Add Course\n";
    std::cout << "8. Delete Course\n";
    std::cout << "0. Return to Main Menu\n";
    std::cout << "Enter your choice: ";
}


void Admin::viewStudents(const std::vector<User*>& users) const {
    std::cout << "List of Students:\n";
    bool found = false;
    for (const auto* user : users) {
        if (const auto* student = dynamic_cast<const Student*>(user)) {
            std::cout << "- " << student->getUsername() << '\n';
            found = true;
        }
    }
    if (!found) {
        std::cout << "No students found.\n";
    }
}

void Admin::viewTeachers(const std::vector<User*>& users) const {
    std::cout << "List of Teachers:\n";
    bool found = false;
    for (const auto* user : users) {
        if (const auto* teacher = dynamic_cast<const Teacher*>(user)) {
            std::cout << "- " << teacher->getUsername() << '\n';
            found = true;
        }
    }
    if (!found) {
        std::cout << "No teachers found.\n";
    }
}



void Admin::addTeacher(std::vector<User*>& users) {
    std::string username, password;
    std::cout << "Enter new teacher's username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    Teacher* newTeacher = new Teacher(username, password);
    users.push_back(newTeacher);

    std::ofstream outFile("users.txt", std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file for saving teacher.\n";
        return;
    }

    outFile << "Teacher\n";
    outFile << username << '\n' << password << '\n';
    outFile << "END\n";  
    std::cout << "Teacher added successfully.\n";
}


void Admin::deleteTeacher(std::vector<User*>& users) {
    std::string username;
    std::cout << "Enter teacher's username to delete: ";
    std::cin >> username;

    auto it = std::remove_if(users.begin(), users.end(), [&username](User* user) {
        return dynamic_cast<Teacher*>(user) && user->getUsername() == username;
        });

    if (it != users.end()) {
        delete* it;  
        users.erase(it, users.end()); 
        std::cout << "Teacher " << username << " deleted successfully.\n";
    }
    else {
        std::cout << "Teacher not found.\n";
    }
}


void Admin::addStudent(std::vector<User*>& users) {
    std::string username, password;
    std::cout << "Enter new student's username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    Student* newStudent = new Student(username, password);
    users.push_back(newStudent);

    std::ofstream outFile("users.txt", std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file for saving student.\n";
        return;
    }

    outFile << "Student\n";
    outFile << username << '\n' << password << '\n';
    outFile << "END\n";     
    std::cout << "Student added successfully.\n";
}


void Admin::deleteStudent(std::vector<User*>& users) {
    std::string username;
    std::cout << "Enter student's username to delete: ";
    std::cin >> username;

    auto it = std::remove_if(users.begin(), users.end(), [&username](User* user) {
        return dynamic_cast<Student*>(user) && user->getUsername() == username;
        });

    if (it != users.end()) {
        delete* it; 
        users.erase(it, users.end());  
        std::cout << "Student " << username << " deleted successfully.\n";
    }
    else {
        std::cout << "Student not found.\n";
    }
}


void Admin::saveToFile(const std::string& filename, User* user) const {
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile) {
        std::cerr << "Помилка: не вдалося відкрити файл для запису.\n";
        return;
    }
    outFile << user->getUsername() << '\n';
    outFile << user->getPassword() << '\n';
    outFile.close(); 
    std::cout << "Користувач успішно збережений у файл " << filename << ".\n";
}

void Admin::addCourse(std::vector<Course>& courses) {
    std::string courseName;
    std::cout << "Enter course name: ";
    std::cin.ignore();
    std::getline(std::cin, courseName);
    courses.emplace_back(courseName);
    std::cout << "Course added successfully.\n";
}

void Admin::deleteCourse(std::vector<Course>& courses) {
    std::string courseName;
    std::cout << "Enter course name to delete: ";
    std::cin.ignore(); 
    std::getline(std::cin, courseName);

    auto it = std::remove_if(courses.begin(), courses.end(), [&courseName](const Course& course) {
        return course.getName() == courseName;
        });

    if (it != courses.end()) {
        courses.erase(it, courses.end());
        std::cout << "Course " << courseName << " deleted successfully.\n";
    }
    else {
        std::cout << "Course not found.\n";
    }
}