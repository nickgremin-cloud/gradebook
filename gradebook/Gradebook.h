#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include "Student.h"
#include <windows.h>
using namespace std;

class GradeBook {
public:
    static inline int nextId_ = 0;


    // Конструкторы
    GradeBook() {}
    GradeBook(const string& courseName): courseName_(courseName) {}

    // Управление студентами
    int addStudent(const string& name, const string& surname, const string& course) {
        students_.push_back(Student(name, surname, nextId_, course));
        nextId_++;
        return nextId_-1; // возвращаем предыдущий ID, так как nextId_ уже увеличен
    }

    bool removeStudent(int id){                            // Удаляет по ID
        for (size_t i = 0; i < students_.size(); i++) {
            if (students_[i].getId() == id) {
                students_.erase(students_.begin() + i);
                return true;
            }
        }
        return false; // добавляем возвращаемое значение
    }
    Student* findStudent(int id) const {                          // Поиск по ID (возвращает указатель), добавляем const
        for (size_t i = 0; i < students_.size(); i++) {
            if (students_[i].getId() == id) {
                return const_cast<Student*>(&students_[i]); // приведение const к неконстантному указателю
            }
        }
        return nullptr; // добавляем возвращаемое значение
    }


    
    // Работа с оценками
    bool addGradeToStudent(int studentId, double grade) {   // Добавить оценку конкретному студенту
        for (size_t i = 0; i < students_.size(); i++) { // изменяем тип на size_t
            if (students_[i].getId() == studentId) {
                students_[i].addGrade(grade);
                return true;
            }
        }
        return false; // добавляем возвращаемое значение
    }

    bool removeGradeFromStudent(int studentId, size_t index) {
        for (size_t i = 0; i < students_.size(); i++) { // изменяем тип на size_t
            if (students_[i].getId() == studentId) {
                return students_[i].removeGrade(index); // возвращаем результат работы метода removeGrade
            }
        }
        return false; // добавляем возвращаемое значение
    }

    
    // Статистика по классу
    double getClassAverage() const {                        // Средний балл всех студентов
        if (students_.empty()) return 0.0; // защищаемся от деления на 0
        double sum_grades = 0;
        size_t count_grades = 0;
        for (size_t i = 0; i < students_.size(); i++) { // изменяем тип на size_t
            sum_grades += students_[i].getAverage();
            count_grades++;
        }
        return sum_grades / count_grades;            
    }
    Student* getTopStudent() const { // добавляем const
        if (students_.empty()) return nullptr; // Защита от пустого списка
        auto it = std::max_element(students_.begin(), students_.end(), [](const Student& a, const Student& b) {return a.getAverage() < b.getAverage();});
        return const_cast<Student*>(&(*it)); // приведение const к неконстантному указателю
    }
    Student* getBottomStudent() const {                           // Студент с lowest average, добавляем const
        if (students_.empty()) return nullptr;
        auto it = std::min_element(students_.begin(), students_.end(), [](const Student& a, const Student& b) {return a.getAverage() < b.getAverage();});
        return const_cast<Student*>(&(*it)); // приведение const к неконстантному указателю
    }

    map<char, int> getGradeDistribution() const { // Распределение буквенных оценок {A: 5, B: 3...} - убираем лишнюю квалификацию
        map<char, int> distribution;
        
        // Проходим по всем студентам
        for (const auto& student : students_) {
            char letter = student.getLetterGrade(); // Получаем букву (A, B, C...)
            distribution[letter]++;                 // Увеличиваем счетчик для этой буквы
        }
        
        return distribution;
    }
    // Вывод
    void displayAllStudents() const {                       // Список всех студентов
        for (size_t i = 0; i < students_.size(); i++) { // изменяем тип на size_t
            students_[i].displayInfo();
            cout << endl;
        }
    }

    void displayStudentDetails(int id) const {              // Детали конкретного студента
        Student* student = findStudent(id);
        if(student != nullptr){
            student->displayInfo();
        }else{
            cout << "Student with ID " << id << " not found." << endl;
        }
    }
    void displayClassStatistics() const {                   // Общая статистика класса
        cout << "Class average: " << getClassAverage() << endl;
        cout << "Grade distribution: " << endl;
        map<char, int> distribution = getGradeDistribution();
        for(auto const& pair : distribution) {
            cout << pair.first << ": " << pair.second << " ";
        }
        cout << endl;
    }
    
    // Сохранение/загрузка (опционально)
    bool saveToFile(const string& /*filename*/) const { // используем комментарий для подавления предупреждения об неиспользуемом параметре
        // Заглушка для реализации сохранения в файл
        return true;
    }

    bool loadFromFile(const string& /*filename*/) { // используем комментарий для подавления предупреждения об неиспользуемом параметре
        // Заглушка для реализации загрузки из файла
        return true;
    }

private:
    vector<Student> students_;       // Все студенты
    string courseName_;              // Название курса
};