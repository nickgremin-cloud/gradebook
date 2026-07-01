#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <windows.h>
using namespace std;
class Student {
public:
    // Конструкторы
    Student(const string& name, const string& surname, int id, const string& course)
        : name_(name), surname_(surname), id_(id), course_(course) {}

    Student()
        : name_("name"), surname_("surname"), id_(0), course_("0") {}

    // Геттеры
    int getId() const { return id_; }
    string getName() const { return name_; }
    string getSurname() const { return surname_; }
    string getCourse() const { return course_; }
    const vector<double>& getGrades() const { return grades_; }

    // Работа с оценками
    void addGrade(double grade) {
        if (IsValidGrade(grade)) {
            grades_.push_back(grade);
        } else {
            cout << "ERROR: Invalid grade. Grade must be between 0 and 100." << endl;
        }
    }

    bool removeGrade(size_t index) {
        if (index == 0 || index > grades_.size()) {
            return false;
        }
        grades_.erase(grades_.begin() + index - 1);
        return true;
    }

    void clearGrades() {
        grades_.clear();
    }

    bool ChangeGrade(size_t index, double grade) {
        if (index == 0 || index > grades_.size() || !IsValidGrade(grade)) {
            return false;
        }
        grades_[index - 1] = grade;
        return true;
    }

    bool IsValidGrade(double grade) const {
        return grade >= 0 && grade <= 100;
    }

    // Статистика
    double getAverage() const {
        if (!grades_.empty()) {
            return accumulate(grades_.begin(), grades_.end(), 0.0) / grades_.size();
        }
        return 0.0;
    }

    double getHighest() const {
        if (grades_.empty()) return 0.0;
        return *max_element(grades_.begin(), grades_.end());
    }

    double getLowest() const {
        if (grades_.empty()) return 0.0;
        return *min_element(grades_.begin(), grades_.end());
    }

    size_t getGradeCount() const {
        return grades_.size();
    }

    char getLetterGrade() const {
        double avg = getAverage();
        if (avg >= 80) return 'A';
        if (avg >= 60) return 'B';
        if (avg >= 40) return 'C';
        if (avg >= 20) return 'D';
        return 'F';
    }

    // Вывод информации
    void displayInfo() const {
        cout << "Name: " << name_ << endl;
        cout << "Surname: " << surname_ << endl;
        cout << "ID: " << id_ << endl;
        cout << "Course: " << course_ << endl;
        cout << "Average: " << getAverage() << endl;
        cout << "Highest: " << getHighest() << endl;
        cout << "Lowest: " << getLowest() << endl;
        cout << "Grade count: " << getGradeCount() << endl;
        cout << "Letter grade: " << getLetterGrade() << endl;
        displayGrades();
    }

    void displayGrades() const {
        int counter = 0;
        for (size_t i = 0; i < grades_.size(); i++) {
            if (counter != 5) {
                cout << grades_[i] << " ";
                counter++;
            } else {
                cout << endl;
                counter = 0;
            }
        }
        if (counter > 0) {
            cout << endl;
        }
    }

private:
    string name_ = "name";
    string surname_ = "surname";
    int id_ = 0;
    vector<double> grades_ = {};
    string course_ = "0";
};