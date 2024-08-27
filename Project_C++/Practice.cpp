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
    // �����������
    student(std::wstring FN, int A) : FirstName(FN), Age(A) {}

    // ����� ��� ���������� ������
    void addScore(double score) {
        Scores.push_back(score);
    }

    // ����� ��� ���������� ������� ������
    double calculateAverageScore() const {
        if (Scores.empty()) {
            return 0.0; // ���������� 0, ���� ��� ������
        }
        double sum = 0.0;
        for (double score : Scores) {
            sum += score;
        }
        return sum / Scores.size();
    }

    // ����� ��� ��������� ������ �� ������ ������� ������
    std::wstring getGrade() const {
        double averageScore = calculateAverageScore();
        if (averageScore > 8.0) {
            return L"�������";
        }
        else if (averageScore >= 6.0) {
            return L"������";
        }
        else if (averageScore >= 4.0) {
            return L"�����������������";
        }
        else {
            return L"�������������������";
        }
    }

    // ����� display
    void display() const {
        wcout << L"���: " << FirstName << L"\n�������: " << Age << L"\n������� ����: " << calculateAverageScore() << L"\n������: " << getGrade() << endl;
    }

    // ����� ��� ��������� ����� ��������
    std::wstring getFirstName() const {
        return FirstName;
    }
};

// ������� ������ �������� �� �����
student* findStudentByName(std::vector<student>& students, const std::wstring& name) {
    for (auto& st : students) {
        if (st.getFirstName() == name) {
            return &st; // ���������� ��������� �� ��������
        }
    }
    return nullptr; // ���� ������� �� ������
}

int main() {
    // ��������� ������ ��� ��������� Unicode
    setlocale(LC_ALL, "rus_rus.866");

    std::vector<student> students;

    // ���� ���������� � ���������
    while (true) {
        wcout << L"������� ��� �������� (��� 'close' ��� ���������� �����): ";
        wchar_t name[255];
        wcin.getline(name, 255);
        std::wstring studentName(name);

        if (studentName == L"close") {
            break;
        }

        wcout << L"������� ������� ��������: ";
        int age;
        wcin >> age;
        wcin.ignore(); // ���������� ������� ������ ����� ����� ��������

        students.emplace_back(studentName, age);
    }

    // ���� ������ ��� ���������
    while (true) {
        wcout << L"������� ��� �������� ��� ���������� ������ (��� 'close' ��� ����������): ";
        wchar_t name[255];
        wcin.getline(name, 255);
        std::wstring studentName(name);

        if (studentName == L"close") {
            break;
        }

        student* st = findStudentByName(students, studentName);

        if (st) {
            while (true) {
                wcout << L"������� ������ ��� �������� " << studentName << L" (��� 'end' ��� ���������� ����� ������): ";
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
                    wcout << L"�������� ������ ������. ����������, ������� �����." << endl;
                }
            }
        }
        else {
            wcout << L"������� � ������ " << studentName << L" �� ������." << endl;
        }
    }

    // ����� � ����������� ���������� � ��������
    while (true) {
        wcout << L"������� ��� �������� ��� ������ ���������� (��� 'close' ��� ����������): ";
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
            wcout << L"������� � ������ " << studentName << L" �� ������." << endl;
        }
    }

    return 0;
}