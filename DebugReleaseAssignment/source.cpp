#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
};


int main()
{
    std::vector<STUDENT_DATA> students;
    std::ifstream inputFile("StudentData.txt");

    if (!inputFile.is_open())
    {
        std::cout << "Error: Could not open StudentData.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::stringstream ss(line);
        std::string first, last;

        std::getline(ss, first, ',');
        std::getline(ss, last, ',');

        STUDENT_DATA student;
        student.firstName = first;
        student.lastName = last;

        students.push_back(student);
    }

    inputFile.close();

#ifdef _DEBUG
    std::cout << "=== DEBUG MODE: Student List ===" << std::endl;
    for (const auto& s : students)
    {
        std::cout << s.firstName << " " << s.lastName << std::endl;
    }
#endif

    return 1;
}