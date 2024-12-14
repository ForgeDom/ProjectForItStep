#include "libs.h"

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
    ofstream outFile("users.txt");
    if (!outFile) {
        cerr << "Error saving users to file.\n";
        return;
    }

    for (const auto* user : users) {
        if (user == nullptr) {
            continue; 
        }
        if (dynamic_cast<const Admin*>(user)) {
            continue;
        }
        string type = typeid(*user).name();
        outFile << type << '\n';
        user->saveToFile(outFile);
        outFile << "END\n"; 
    }
}

void Menu::loadUsersFromFile() {
    ifstream inFile("users.txt");
    if (!inFile) {
        cerr << "Error: Unable to open users.txt for reading.\n";
        return;
    }

    string type;
    while (getline(inFile, type)) {
         if (type == "Teacher") {
            users.push_back(new Teacher(inFile));
        }
        else if (type == "Student") {
            users.push_back(new Student(inFile));
        }
        else {
            cerr << "Unknown user type: " << type << "\n";
            continue;
        }

        string endMarker;
        getline(inFile, endMarker);
        if (endMarker != "END") {
            cerr << "Error: Missing END marker for user type " << type << "\n";
        }
    }

    cout << "Loaded " << users.size() << " users from file.\n";
}

void Menu::registerStudent() {
    string username, password;
    cout << "Enter new Student Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    auto* newStudent = new Student(username, password);
    users.push_back(newStudent);

    ofstream outFile("users.txt", ios::app);
    if (!outFile) {
        cerr << "Error saving student to file.\n";
        return;
    }

    outFile << "Student\n";
    outFile << username << '\n';
    outFile << password << '\n';
    outFile << "END\n";

    cout << "Student registered successfully.\n";
}



void Menu::displayMainMenu() {
    while (true) {
        cout << "Main Menu:\n";
        cout << "1. Log in as Admin\n";
        cout << "2. Log in as Teacher\n";
        cout << "3. Log in as Student\n";
        cout << "4. Register as Student\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string username, password;
            cout << "Enter Admin Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            for (auto* user : users) {
                if (auto* admin = dynamic_cast<Admin*>(user)) {
                    if (admin->getUsername() == username && admin->verifyPassword(password)) {
                        adminMenu(admin);
                        return;
                    }
                }
            }
            cout << "Invalid Admin credentials.\n";
            break;
        }
        case 2: {
            string username, password;
            cout << "Enter Teacher Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            for (auto* user : users) {
                if (auto* teacher = dynamic_cast<Teacher*>(user)) {
                    if (teacher->getUsername() == username && teacher->verifyPassword(password)) {
                        teacherMenu(teacher);
                        return;
                    }
                }
            }
            cout << "Invalid Teacher credentials.\n";
            break;
        }
        case 3: {
            string username, password;
            cout << "Enter Student Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            for (auto* user : users) {
                if (auto* student = dynamic_cast<Student*>(user)) {
                    if (student->getUsername() == username && student->verifyPassword(password)) {
                        studentMenu(student);
                        return;
                    }
                }
            }
            cout << "Invalid Student credentials.\n";
            break;
        }
        case 4:
            registerStudent();
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice.\n";
        }
    }
}

void Menu::adminMenu(Admin* admin) {
    int choice;
    do {
        admin->displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            admin->viewStudents("users.txt");
            break;
        case 2:
            admin->viewTeachers("users.txt");
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
            cout << "Returning to main menu...\n";
            return;  
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}

void Menu::teacherMenu(Teacher* teacher) {
    int choice;
    string fileName = "courses.txt";

    do {
        teacher->displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            teacher->viewCourses(fileName);
            break;
        case 2:
            teacher->viewStudentsInCourse(fileName); 
            break;
        case 3:
            teacher->addStudentToCourse(fileName); 
            break;
        case 4:
            teacher->removeStudentFromCourse(fileName);
            break;
        case 5:
            teacher->assignGradeToStudent(fileName);
            break;
        case 0:
            cout << "Returning to the main menu...\n";
            return; 
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}


void Menu::studentMenu(Student* student) {
    cout << "Student menu coming soon.\n";
}
