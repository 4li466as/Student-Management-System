#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
using namespace std;


// Struct Definition
struct Student {
    int id;
    string name;
    float cgpa;
    char section;
};

// String helpers (no regex used)
static string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

static bool allDigits(const string& s) {
    if (s.empty()) return false;
    for (char c : s) if (!isdigit(static_cast<unsigned char>(c))) return false;
    return true;
}

// Robust input helpers
int readIntInRange(const string& prompt, int minVal, int maxVal) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) { cin.clear(); continue; }
        line = trim(line);
        if (!allDigits(line)) {
            cout << "Invalid input. Enter digits only.\n";
            continue;
        }
        // safe to parse (non-negative only)
        // prevent leading zeros confusion? not necessary
        long long v = 0;
        for (char c : line) { v = v * 10 + (c - '0'); if (v > maxVal) break; }
        if (v < minVal || v > maxVal) {
            cout << "Value must be between " << minVal << " and " << maxVal << ".\n";
            continue;
        }
        return static_cast<int>(v);
    }
}

float readFloatInRange(const string& prompt, float minVal, float maxVal) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) { cin.clear(); continue; }
        line = trim(line);
        if (line.empty()) { cout << "Empty input.\n"; continue; }

        // parse with stringstream and ensure no trailing junk
        stringstream ss(line);
        float v;
        ss >> v;
        if (ss.fail()) { cout << "Invalid number. Use digits (e.g., 3.25).\n"; continue; }
        // ensure nothing else after the number
        ss >> ws;
        if (!ss.eof()) { cout << "Invalid format. Extra characters detected.\n"; continue; }
        if (v < minVal || v > maxVal) {
            cout << "Value must be between " << minVal << " and " << maxVal << ".\n";
            continue;
        }
        return v;
    }
}

char readSectionAZ(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) { cin.clear(); continue; }
        line = trim(line);
        if (line.size() != 1) {
            cout << "Enter exactly one character (A-Z).\n";
            continue;
        }
        char c = static_cast<char>(toupper(static_cast<unsigned char>(line[0])));
        if (c < 'A' || c > 'Z') {
            cout << "Section must be a letter A-Z.\n";
            continue;
        }
        return c;
    }
}

string readNonEmptyLine(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) { cin.clear(); continue; }
        line = trim(line);
        if (line.empty()) {
            cout << "Value cannot be empty.\n";
            continue;
        }
        return line;
    }
}

// Name helpers
static bool hasDigit(const string& s) {
    for (char c : s) {
        if (isdigit(static_cast<unsigned char>(c))) return true;
    }
    return false;
}

static string formatName(const string& s) {
    string result = s;
    bool newWord = true;
    for (size_t i = 0; i < result.size(); i++) {
        char& c = result[i];
        if (isspace(static_cast<unsigned char>(c))) {
            newWord = true;
        } else {
            if (newWord) {
                c = toupper(static_cast<unsigned char>(c));
                newWord = false;
            } else {
                c = tolower(static_cast<unsigned char>(c));
            }
        }
    }
    return result;
}

string readName(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) { cin.clear(); continue; }
        line = trim(line);
        if (line.empty()) {
            cout << "Name cannot be empty.\n";
            continue;
        }
        if (hasDigit(line)) {
            cout << "Name cannot contain digits.\n";
            continue;
        }
        // format with capitalization
        return formatName(line);
    }
}

// Utility Functions
void printStudent(const Student& s) {
    cout << "ID: " << s.id
         << " | Name: " << s.name
         << " | CGPA: " << s.cgpa
         << " | Section: " << s.section << endl;
}

// Read student with validation (ID digits only, CGPA numeric, Section single char)
bool readStudent(Student& s) {
    s.id = readIntInRange("Enter ID (Digits Only, Above Zero): ", 1, numeric_limits<int>::max());
    s.name = readName("Enter Name (No Digits): "); // <--- updated
    s.cgpa = readFloatInRange("Enter CGPA (0.0 - 4.0): ", 0.0f, 4.0f);
    s.section = readSectionAZ("Enter Section (A-Z, Single Letter): ");
    return true;
}


// Part B — Arrays of Structs
int indexOfId(const Student arr[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id)
            return i;
    }
    return -1;
}

// Sorting Helpers (no STL sort)
// Bubble sort by CGPA (asc or desc) into temp array
void sortByCgpa(const Student src[], int n, Student dst[], bool ascending) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool swapNeeded = ascending ? (dst[j].cgpa > dst[j + 1].cgpa)
                                        : (dst[j].cgpa < dst[j + 1].cgpa);
            if (swapNeeded) {
                Student temp = dst[j];
                dst[j] = dst[j + 1];
                dst[j + 1] = temp;
            }
        }
    }
}

// Bubble sort by ID (ascending) into temp array
void sortById(const Student src[], int n, Student dst[]) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (dst[j].id > dst[j + 1].id) {
                Student temp = dst[j];
                dst[j] = dst[j + 1];
                dst[j + 1] = temp;
            }
        }
    }
}

// Analysis, Update & Delete
Student topCgpa(const Student arr[], int n) {
    int topIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i].cgpa > arr[topIndex].cgpa)
            topIndex = i;
    }
    return arr[topIndex];
}

float averageCgpaBySection(const Student arr[], int n, char section) {
    float sum = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].section == section) {
            sum += arr[i].cgpa;
            count++;
        }
    }
    if (count == 0) return 0.0f;
    return sum / count;
}

int filterByCgpa(const Student src[], int n, float threshold, Student dst[]) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (src[i].cgpa >= threshold) {
            dst[j++] = src[i];
        }
    }
    return j;
}

bool updateSection(Student arr[], int n, int id, char newSection) {
    int idx = indexOfId(arr, n, id);
    if (idx == -1) return false;
    arr[idx].section = newSection;
    return true;
}

bool deleteById(Student arr[], int& n, int id) {
    int idx = indexOfId(arr, n, id);
    if (idx == -1) return false;
    for (int i = idx; i < n - 1; i++) arr[i] = arr[i + 1];
    n--;
    return true;
}

// Main Menu
int main() {
    const int MAX = 100;
    Student students[MAX];
    int n = 0;

    while (true) {
        cout << "\n--- Student Management Menu ---\n";
        cout << "1. Add student\n";
        cout << "2. Show all students (ID order)\n";
        cout << "3. Find by ID\n";
        cout << "4. Top CGPA\n";
        cout << "5. Average by section\n";
        cout << "6. Filter by CGPA\n";
        cout << "7. Sort by CGPA (choose order)\n";
        cout << "8. Update section by ID\n";
        cout << "9. Delete by ID\n";
        cout << "10. Exit\n";

        int choice = readIntInRange("Enter choice (1-10): ", 1, 10);

        if (choice == 1) {
            if (n >= MAX) {
                cout << "Array full!\n";
                continue;
            }
            Student s;
            if (readStudent(s)) {
                if (indexOfId(students, n, s.id) != -1) {
                    cout << "ID already exists!\n";
                } else {
                    students[n++] = s;
                    cout << "Student added!\n";
                }
            }
        }
        else if (choice == 2) {
            if (n == 0) cout << "No students to display.\n";
            else {
                Student sorted[MAX];
                sortById(students, n, sorted);
                for (int i = 0; i < n; i++) printStudent(sorted[i]);
            }
        }
        else if (choice == 3) {
            int id = readIntInRange("Enter ID to search: ", 1, numeric_limits<int>::max());
            int idx = indexOfId(students, n, id);
            if (idx == -1) cout << "Not found.\n";
            else printStudent(students[idx]);
        }
        else if (choice == 4) {
            if (n == 0) cout << "No students.\n";
            else printStudent(topCgpa(students, n));
        }
        else if (choice == 5) {
            char sec = readSectionAZ("Enter section (A-Z): ");
            float avg = averageCgpaBySection(students, n, sec);
            if (avg == 0.0f) cout << "No students in this section.\n";
            else cout << "Average CGPA for section " << sec << " = " << avg << endl;
        }
        else if (choice == 6) {
            float th = readFloatInRange("Enter CGPA threshold (0.0 - 4.0): ", 0.0f, 4.0f);
            Student result[MAX];
            int m = filterByCgpa(students, n, th, result);
            if (m == 0) cout << "No students with CGPA >= " << th << ".\n";
            else {
                cout << "Students with CGPA >= " << th << ":\n";
                for (int i = 0; i < m; i++) printStudent(result[i]);
            }
        }
        else if (choice == 7) {
            if (n == 0) { cout << "No students.\n"; continue; }
            int opt = readIntInRange("1. Ascending\n2. Descending\nEnter option: ", 1, 2);
            Student sorted[MAX];
            if (opt == 1) {
                sortByCgpa(students, n, sorted, true);
                cout << "Sorted by CGPA (ascending):\n";
            } else {
                sortByCgpa(students, n, sorted, false);
                cout << "Sorted by CGPA (descending):\n";
            }
            for (int i = 0; i < n; i++) printStudent(sorted[i]);
        }
        else if (choice == 8) {
            int id = readIntInRange("Enter ID: ", 1, numeric_limits<int>::max());
            char sec = readSectionAZ("Enter new Section (A-Z): ");
            if (updateSection(students, n, id, sec)) cout << "Updated!\n";
            else cout << "Not found.\n";
        }
        else if (choice == 9) {
            int id = readIntInRange("Enter ID to delete: ", 1, numeric_limits<int>::max());
            if (deleteById(students, n, id)) cout << "Deleted.\n";
            else cout << "Not found.\n";
        }
        else if (choice == 10) {
            cout << "Exiting...\n";
            break;
        }
    }
    return 0;
}

