#include <iostream>
#include <fstream>
#include <set>
#include <map>
using namespace std;

class CourseManagementSystem 
{
private:
    set<string> unique_students; 
    multimap<string, string> course_students; 
    multimap<int, string, greater<int>> student_grades; 

public:
    void load_from_file(const string& filename) 
    {
        ifstream file(filename);
        string course, student;
        int grade;
        while (file >> course >> student >> grade) 
        {
            add_student_to_course(course, student, grade);
        }
        file.close();
    }

    void add_student_to_course(const string& course, const string& student, int grade) 
    {
        unique_students.insert(student);
        course_students.insert(make_pair(course, student));
        student_grades.insert(make_pair(grade, student));
    }

    void update_student_grade(const string& student, int old_grade, int new_grade) 
    {
        auto range = student_grades.equal_range(old_grade);
        for (auto it = range.first; it != range.second; ++it) 
        {
            if (it->second == student) 
            {
                student_grades.erase(it);
                break;
            }
        }
        student_grades.insert(make_pair(new_grade, student));
    }

    void remove_student_from_course(const string& course, const string& student) 
    {
        auto range = course_students.equal_range(course);
        for (auto it = range.first; it != range.second; ) 
        {
            if (it->second == student) 
            {
                it = course_students.erase(it); 
            }
            else 
            {
                it++;
            }
        }
    }

    void print_courses() const 
    {
        for (const auto& entry : course_students) 
        {
            cout << "Course: " << entry.first << ", Student: " << entry.second << endl;
        }
    }

    void print_unique_students() const 
    {
        for (const auto& student : unique_students) 
        {
            cout << "Student: " << student << endl;
        }
    }

    void print_students_by_grades() const 
    {
        for (const auto& entry : student_grades) 
        {
            cout << "Student: " << entry.second << ", Grade: " << entry.first << endl;
        }
    }
};

int main() 
{
    CourseManagementSystem cms;
    cms.load_from_file("courses.txt");

    cms.add_student_to_course("Math", "Sofiya", 95);
    cms.add_student_to_course("Physics", "Roman", 85);

    cout << "Courses and Students:" << endl;
    cms.print_courses();

    cout << "\nUnique Students:" << endl;
    cms.print_unique_students();

    cms.update_student_grade("Sofiya", 95, 80);

    cout << "\nStudents by Grades:" << endl;
    cms.print_students_by_grades();
    
    cms.remove_student_from_course("Physics", "Roman");
}
