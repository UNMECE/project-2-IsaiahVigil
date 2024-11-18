#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Student {
protected:
    std::string fname;
    std::string lname;
    double gpa;
    int gradYr;
    std::string gradSem;
    int enrollYr;
    std::string enrollSem;
    std::string lvl;

public:
        Student()
        : fname("Unknown"), lname("Unknown"), gpa(0.0),
          gradYr(0), gradSem("Unknown"),
          enrollYr(0), enrollSem("Unknown"), lvl("Undergrad") {}

    virtual ~Student() {}

    void setName(const std::string& first, const std::string& last) {
        fname = first;
        lname = last;
    }

    void setGPA(double g) { gpa = g; }
    void setGradYr(int year) { gradYr = year; }
    void setGradSem(const std::string& sem) { gradSem = sem; }
    void setEnrollYr(int year) { enrollYr = year; }
    void setEnrollSem(const std::string& sem) { enrollSem = sem; }
    void setLvl(const std::string& level) { lvl = level; }

    virtual void displayInfo(std::ostream& os) const {
        os << "Name: " << fname << " " << lname << "\n"
           << "GPA: " << gpa << "\n"
           << "Graduation: " << gradSem << " " << gradYr << "\n"
           << "Enrolled: " << enrollSem << " " << enrollYr << "\n"
           << "Level: " << lvl << "\n";
    }
};

class Art_Student : public Student {
private:
    std::string artFocus;

public:
    Art_Student() : artFocus("Unknown") {}
    ~Art_Student() {}

    void setArtFocus(const std::string& focus) { artFocus = focus; }

    void displayInfo(std::ostream& os) const override {
        Student::displayInfo(os);
        os << "Art Focus: " << artFocus << "\n";
    }
};

class Physics_Student : public Student {
private:
    std::string physFocus;

public:
    Physics_Student() : physFocus("Unknown") {}
    ~Physics_Student() {}

    void setPhysFocus(const std::string& focus) { physFocus = focus; }

    void displayInfo(std::ostream& os) const override {
        Student::displayInfo(os);
        os << "Physics Focus: " << physFocus << "\n";
    }
};

int main() {
    std::vector<Art_Student*> artStudents;
    std::vector<Physics_Student*> physStudents;

    for (int i = 0; i < 5; i++) {
        Art_Student* student = new Art_Student();
        student->setName("ArtFirst" + std::to_string(i + 1), "ArtLast" + std::to_string(i + 1));
        student->setGPA(3.5 + i * 0.1);
        student->setGradYr(2025 + i);
        student->setGradSem("Spring");
        student->setEnrollYr(2021 + i);
        student->setEnrollSem("Fall");
        student->setArtFocus(i % 2 == 0 ? "Art Studio" : "Art History");
        artStudents.push_back(student);
    }

    for (int i = 0; i < 5; i++) {
        Physics_Student* student = new Physics_Student();
        student->setName("PhysicsFirst" + std::to_string(i + 1), "PhysicsLast" + std::to_string(i + 1));
        student->setGPA(3.8 + i * 0.05);
        student->setGradYr(2024 + i);
        student->setGradSem("Fall");
        student->setEnrollYr(2020 + i);
        student->setEnrollSem("Spring");
        student->setPhysFocus(i % 2 == 0 ? "Biophysics" : "Earth and Planetary Sciences");
        physStudents.push_back(student);
    }

    std::ofstream outfile("student_info.dat");
    if (outfile.is_open()) {
        for (const auto& student : artStudents) {
            student->displayInfo(outfile);
            outfile << "----------------------\n";
        }
        for (const auto& student : physStudents) {
            student->displayInfo(outfile);
            outfile << "----------------------\n";
        }
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing.\n";
    }

    for (auto& student : artStudents) delete student;
    for (auto& student : physStudents) delete student;

    return 0;
}
