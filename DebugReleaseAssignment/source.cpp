#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
    std::string email;
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

        if (!last.empty() && last[0] == ' ')
            last.erase(0, 1);

        STUDENT_DATA student;
        student.firstName = first;
        student.lastName = last;

        students.push_back(student);
    }

    inputFile.close();

#ifdef PRE_RELEASE
    std::cout << "Running PRE-RELEASE version." << std::endl;

    std::ifstream emailFile("StudentData_Emails.txt");
    if (emailFile.is_open())
    {
        std::string emailLine;
        while (std::getline(emailFile, emailLine))
        {
            std::stringstream ess(emailLine);
            std::string eLast, eFirst, email;

            std::getline(ess, eLast, ',');
            std::getline(ess, eFirst, ',');
            std::getline(ess, email, ',');

            // trim leading space that follows the comma
            if (!eFirst.empty() && eFirst[0] == ' ')
                eFirst.erase(0, 1);

            for (auto& s : students)
            {
                if (s.firstName == eLast && s.lastName == eFirst)
                {
                    s.email = email;
                    break;
                }
            }
        }
        emailFile.close();
    }
    else
    {
        std::cout << "Error: Could not open StudentData_Emails.txt" << std::endl;
    }
#else
    std::cout << "Running STANDARD version." << std::endl;
#endif

#ifdef _DEBUG
    std::cout << "=== DEBUG MODE: Student List ===" << std::endl;
    for (const auto& s : students)
    {
        std::cout << s.firstName << " " << s.lastName;
        if (!s.email.empty())
        {
            std::cout << " - " << s.email;
        }
        std::cout << std::endl;
    }
#endif

    return 1;
}