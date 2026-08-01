<div align="center">
  <h1>🎓 Student Management System (C++)</h1>
  <p>A robust terminal-based Student Record Management System built in standard C++.</p>

  [![Language: C++](https://img.shields.io/badge/Language-C++-blue.svg)]()
  [![Build: Make](https://img.shields.io/badge/Build-Make-green.svg)]()
  [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
</div>

---

> [!NOTE]
> **Academic Project**
> This repository demonstrates a classic data structures and algorithms project. It focuses on robust input validation, custom string formatting, and implementing sorting algorithms (like Bubble Sort) from scratch without relying on modern C++ STL shortcuts.

## 📖 Table of Contents
- [About the Project](#about-the-project)
- [Key Features](#key-features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [License](#license)

## 🕵️‍♂️ About the Project

The **Student Management System** is a console application designed to manage student records efficiently. Each record consists of a Student ID, Name, CGPA, and Section. 

A major focus of this project is **Input Validation** and **Data Integrity**. It uses custom string parsing to ensure users cannot crash the program by entering letters where numbers belong or by leaving fields empty. It also automatically formats names (e.g., auto-capitalizing first letters) to keep records standardized.

## ✨ Key Features

- **Robust Input Validation**: Prevents infinite loops caused by `cin` failures. Safely parses integers, floats, and characters, strictly enforcing ranges (e.g., CGPA must be between 0.0 and 4.0).
- **Custom Name Formatting**: Automatically capitalizes the first letter of each name and lowercases the rest, rejecting any names containing digits.
- **Custom Sorting Algorithms**: Implements ascending and descending Bubble Sort on the array of student structs to rank students by CGPA.
- **CRUD Operations**: Complete capability to Create, Read, Update, and Delete student records safely.

## 🚀 Getting Started

### Prerequisites
You need a standard C++ compiler (like `g++`) installed on your machine.
- **Windows**: Install MinGW-w64.
- **Linux/Mac**: `sudo apt install build-essential` or install Xcode Command Line Tools.

### Build Instructions
Clone the repository and compile using the included `Makefile`:

```bash
git clone https://github.com/4li466as/Student-Management-System.git
cd Student-Management-System
make
```

## 🎮 Usage

Run the compiled executable:

```bash
# On Linux/Mac:
./student_management

# On Windows:
.\student_management.exe
```

Follow the on-screen prompts to start adding students, sorting them by CGPA, or searching for specific IDs!

## 📝 License

Distributed under the MIT License. See `LICENSE` for more information.
