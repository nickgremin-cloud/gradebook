#include "Gradebook.h"
#include <locale>
#include <windows.h>

int main()
{
    // Устанавливаем локаль для поддержки кириллицы
    SetConsoleOutputCP(65001);

    GradeBook gradebook("Computer Science");
    int choice;
    
    cout << "=====================================" << endl;
    cout << "   СИСТЕМА УЧЕТА ОЦЕНОК СТУДЕНТОВ" << endl;
    cout << "=====================================" << endl;

    while(true) {
        cout << "\n1. Добавить нового студента" << endl;
        cout << "2. Удалить студента" << endl;
        cout << "3. Добавить оценку студенту" << endl;
        cout << "4. Удалить оценку у студента" << endl;
        cout << "5. Просмотреть информацию о студенте" << endl;
        cout << "6. Показать всех студентов" << endl;
        cout << "7. Показать статистику класса" << endl;
        cout << "8. Найти лучшего студента" << endl;
        cout << "9. Сохранить в файл" << endl;
        cout << "10. Загрузить из файла" << endl;
        cout << "0. Выход" << endl;
        
        cout << "\nВыберите действие: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                // Добавить нового студента
                string name, surname, course;
                cout << "Введите имя студента: ";
                cin >> name;
                cout << "Введите фамилию студента: ";
                cin >> surname;
                cout << "Введите курс: ";
                cin >> course;
                
                int id = gradebook.addStudent(name, surname, course);
                cout << "Студент добавлен с ID: " << id << endl;
                break;
            }
            
            case 2: {
                // Удалить студента
                int id;
                cout << "Введите ID студента для удаления: ";
                cin >> id;
                
                if(gradebook.removeStudent(id)) {
                    cout << "Студент с ID " << id << " удален." << endl;
                } else {
                    cout << "Студент с ID " << id << " не найден." << endl;
                }
                break;
            }
            
            case 3: {
                // Добавить оценку студенту
                int id;
                double grade;
                cout << "Введите ID студента: ";
                cin >> id;
                cout << "Введите оценку: ";
                cin >> grade;
                
                if(gradebook.addGradeToStudent(id, grade)) {
                    cout << "Оценка добавлена." << endl;
                } else {
                    cout << "Ошибка: студент не найден." << endl;
                }
                break;
            }
            
            case 4: {
                // Удалить оценку у студента
                int id, index;
                cout << "Введите ID студента: ";
                cin >> id;
                cout << "Введите индекс оценки для удаления: ";
                cin >> index;
                
                if(gradebook.removeGradeFromStudent(id, index)) {
                    cout << "Оценка удалена." << endl;
                } else {
                    cout << "Ошибка: студент не найден или неверный индекс." << endl;
                }
                break;
            }
            
            case 5: {
                // Просмотреть информацию о студенте
                int id;
                cout << "Введите ID студента: ";
                cin >> id;
                
                Student* student = gradebook.findStudent(id);
                if(student != nullptr) {
                    student->displayInfo();
                } else {
                    cout << "Студент с ID " << id << " не найден." << endl;
                }
                break;
            }
            
            case 6: {
                // Показать всех студентов
                cout << "\nВсе студенты:" << endl;
                gradebook.displayAllStudents();
                break;
            }
            
            case 7: {
                // Показать статистику класса
                cout << "\nСтатистика класса:" << endl;
                cout << "Средний балл класса: " << gradebook.getClassAverage() << endl;
                
                // Показать распределение оценок
                map<char, int> distribution = gradebook.getGradeDistribution();
                cout << "Распределение оценок: ";
                for(auto const& pair : distribution) {
                    cout << pair.first << ": " << pair.second << " ";
                }
                cout << endl;
                
                // Показать худшего студента
                Student* bottomStudent = gradebook.getBottomStudent();
                if(bottomStudent != nullptr) {
                    cout << "Худший студент: " << bottomStudent->getName() << " " << bottomStudent->getSurname() << endl;
                } else {
                    cout << "Нет студентов в системе." << endl;
                }
                break;
            }
            
            case 8: {
                // Найти лучшего студента
                Student* topStudent = gradebook.getTopStudent();
                if(topStudent != nullptr) {
                    cout << "\nЛучший студент:" << endl;
                    topStudent->displayInfo();
                } else {
                    cout << "Нет студентов в системе." << endl;
                }
                break;
            }
            
            case 9: {
                // Сохранить в файл
                string filename;
                cout << "Введите имя файла для сохранения: ";
                cin >> filename;
                
                if(gradebook.saveToFile(filename)) {
                    cout << "Данные сохранены в файл " << filename << endl;
                } else {
                    cout << "Ошибка при сохранении в файл." << endl;
                }
                break;
            }
            
            case 10: {
                // Загрузить из файла
                string filename;
                cout << "Введите имя файла для загрузки: ";
                cin >> filename;
                
                if(gradebook.loadFromFile(filename)) {
                    cout << "Данные загружены из файла " << filename << endl;
                } else {
                    cout << "Ошибка при загрузке из файла." << endl;
                }
                break;
            }
            
            case 0:
                cout << "Выход из программы..." << endl;
                return 0;
                
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
        }
    }
}