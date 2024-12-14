#include "libs.h"

Admin::Admin(const string& username, const string& password)
    : User(username, password), courses() {}

Admin::Admin(ifstream& inFile): courses() {
    getline(inFile, username);
    getline(inFile, password);
}

void Admin::saveToFile(ofstream& outFile) const {
    outFile << username << '\n';
    outFile << password << '\n';
}


void Admin::displayMenu() const {
    cout << "Admin Menu:\n";
    cout << "1. View all students\n";
    cout << "2. View all teachers\n";
    cout << "3. Add Teacher\n";
    cout << "4. Add Student\n";
    cout << "5. Delete Teacher\n";
    cout << "6. Delete Student\n";
    cout << "7. Add Course\n";
    cout << "8. Delete Course\n";
    cout << "0. Return to Main Menu\n";
    cout << "Enter your choice: ";
}

void Admin::viewStudents(const string& fileName) const {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Unable to open " << fileName << " for reading.\n";
        return;
    }

    cout << "List of Students:\n";
    bool found = false;
    string type, username;

    while (getline(inFile, type)) {
        if (type == "Student") {
            getline(inFile, username);  // Читаємо ім'я користувача
            cout << "- " << username << '\n';
            found = true;
        }
        // Пропускаємо інші дані користувача
        string skipLine;
        while (getline(inFile, skipLine) && skipLine != "END") {}
    }

    if (!found) {
        cout << "No students found.\n";
    }

    inFile.close();
}


void Admin::viewTeachers(const string& fileName) const {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Unable to open " << fileName << " for reading.\n";
        return;
    }

    cout << "List of Teachers:\n";
    bool found = false;
    string type, username;

    while (getline(inFile, type)) {
        if (type == "Teacher") {
            getline(inFile, username);  // Читаємо ім'я користувача
            cout << "- " << username << '\n';
            found = true;
        }
        // Пропускаємо інші дані користувача
        string skipLine;
        while (getline(inFile, skipLine) && skipLine != "END") {}
    }

    if (!found) {
        cout << "No teachers found.\n";
    }

    inFile.close();
}


void Admin::addTeacher(vector<User*>& users) {
    string username, password;
    cout << "Enter new teacher's username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Teacher* newTeacher = new Teacher(username, password);
    users.push_back(newTeacher);

    ofstream outFile("users.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file for saving teacher.\n";
        return;
    }

    outFile << "Teacher\n";
    outFile << username << '\n' << password << '\n';
    outFile << "END\n";  
    cout << "Teacher added successfully.\n";
}


void Admin::deleteTeacher(vector<User*>& users) {
    string username;
    cout << "Enter teacher's username to delete: ";
    cin >> username;

    auto it = remove_if(users.begin(), users.end(), [&username](User* user) {
        return dynamic_cast<Teacher*>(user) && user->getUsername() == username;
        });

    if (it != users.end()) {
        delete* it;  
        users.erase(it, users.end()); 
        cout << "Teacher " << username << " deleted successfully.\n";
    }
    else {
        cout << "Teacher not found.\n";
    }
}


void Admin::addStudent(vector<User*>& users) {
    string username, password;
    cout << "Enter new student's username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Student* newStudent = new Student(username, password);
    users.push_back(newStudent);

    ofstream outFile("users.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file for saving student.\n";
        return;
    }

    outFile << "Student\n";
    outFile << username << '\n' << password << '\n';
    outFile << "END\n";     
    cout << "Student added successfully.\n";
}


void Admin::deleteStudent(vector<User*>& users) {
    string username;
    cout << "Enter student's username to delete: ";
    cin >> username;

    auto it = remove_if(users.begin(), users.end(), [&username](User* user) {
        return dynamic_cast<Student*>(user) && user->getUsername() == username;
        });

    if (it != users.end()) {
        delete* it; 
        users.erase(it, users.end());  
        cout << "Student " << username << " deleted successfully.\n";
    }
    else {
        cout << "Student not found.\n";
    }
}


void Admin::saveToFile(const string& filename, User* user) const {
    ofstream outFile(filename, ios::app);
    if (!outFile) {
        cerr << "Помилка: не вдалося відкрити файл для запису.\n";
        return;
    }
    outFile << user->getUsername() << '\n';
    outFile << user->getPassword() << '\n';
    outFile.close(); 
    cout << "Користувач успішно збережений у файл " << filename << ".\n";
}

void Admin::addCourse(vector<Course>& courses) {
    string courseName;
    cout << "Enter course name: ";
    cin.ignore();
    getline(cin, courseName);

    courses.emplace_back(courseName);

    ofstream outFile("courses.txt", ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open courses.txt for writing.\n";
        return;
    }
    outFile << courseName << '\n';
    outFile.close();

    cout << "Course added successfully.\n";
}

void Admin::deleteCourse(vector<Course>& courses) {
    string courseName;
    cout << "Enter course name to delete: ";
    cin.ignore();
    getline(cin, courseName);

    auto it = remove_if(courses.begin(), courses.end(), [&courseName](const Course& course) {
        return course.getName() == courseName;
        });

    if (it != courses.end()) {
        courses.erase(it, courses.end());

        ofstream outFile("courses.txt");
        if (!outFile) {
            cerr << "Error: Unable to open courses.txt for writing.\n";
            return;
        }
        for (const auto& course : courses) {
            outFile << course.getName() << '\n';
        }
        outFile.close();

        cout << "Course " << courseName << " deleted successfully.\n";
    }
    else {
        cout << "Course not found.\n";
    }
}

