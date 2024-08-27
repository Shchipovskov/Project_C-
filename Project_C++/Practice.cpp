#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

using namespace std;

class student {
private:
    std::wstring FirstName;
    int Age;
    std::vector<double> Scores;

public:
    // Конструктор
    student(std::wstring FN, int A) : FirstName(FN), Age(A) {}

    // Метод для добавления оценки
    void addScore(double score) {
        Scores.push_back(score);
    }

    // Метод для вычисления средней оценки
    double calculateAverageScore() const {
        if (Scores.empty()) {
            return 0.0; // Возвращаем 0, если нет оценок
        }
        double sum = 0.0;
        for (double score : Scores) {
            sum += score;
        }
        return sum / Scores.size();
    }

    // Метод для получения оценки на основе средней баллов
    std::wstring getGrade() const {
        double averageScore = calculateAverageScore();
        if (averageScore > 8.0) {
            return L"Отлично";
        }
        else if (averageScore >= 6.0) {
            return L"Хорошо";
        }
        else if (averageScore >= 4.0) {
            return L"Удовлетворительно";
        }
        else {
            return L"Неудовлетворительно";
        }
    }

    // Метод display
    void display() const {
        wcout << L"Имя: " << FirstName << L"\nВозраст: " << Age << L"\nСредний балл: " << calculateAverageScore() << L"\nОценка: " << getGrade() << endl;
    }

    // Метод для получения имени студента
    std::wstring getFirstName() const {
        return FirstName;
    }
};

// Функция поиска студента по имени
student* findStudentByName(std::vector<student>& students, const std::wstring& name) {
    for (auto& st : students) {
        if (st.getFirstName() == name) {
            return &st; // Возвращаем указатель на студента
        }
    }
    return nullptr; // Если студент не найден
}

int main() {
    // Настройка локали для поддержки Unicode
    setlocale(LC_ALL, "rus_rus.866");

    std::vector<student> students;

    // Ввод информации о студентах
    while (true) {
        wcout << L"Введите имя студента (или 'close' для завершения ввода): ";
        wchar_t name[255];
        wcin.getline(name, 255);
        std::wstring studentName(name);

        if (studentName == L"close") {
            break;
        }

        wcout << L"Введите возраст студента: ";
        int age;
        wcin >> age;
        wcin.ignore(); // Игнорируем остаток строки после ввода возраста

        students.emplace_back(studentName, age);
    }

    // Ввод оценок для студентов
    while (true) {
        wcout << L"Введите имя студента для добавления оценок (или 'close' для завершения): ";
        wchar_t name[255];
        wcin.getline(name, 255);
        std::wstring studentName(name);

        if (studentName == L"close") {
            break;
        }

        student* st = findStudentByName(students, studentName);

        if (st) {
            while (true) {
                wcout << L"Введите оценку для студента " << studentName << L" (или 'end' для завершения ввода оценок): ";
                wchar_t scoreInput[255];
                wcin.getline(scoreInput, 255);

                std::wstring input(scoreInput);

                if (input == L"end") {
                    break;
                }

                try {
                    double score = stod(input);
                    st->addScore(score);
                }
                catch (const invalid_argument& e) {
                    wcout << L"Неверный формат оценки. Пожалуйста, введите число." << endl;
                }
            }
        }
        else {
            wcout << L"Студент с именем " << studentName << L" не найден." << endl;
        }
    }

    // Поиск и отображение информации о студенте
    while (true) {
        wcout << L"Введите имя студента для поиска информации (или 'close' для завершения): ";
        wchar_t name[255];
        wcin.getline(name, 255);
        std::wstring studentName(name);

        if (studentName == L"close") {
            break;
        }

        student* st = findStudentByName(students, studentName);

        if (st) {
            st->display();
        }
        else {
            wcout << L"Студент с именем " << studentName << L" не найден." << endl;
        }
    }

    return 0;
}