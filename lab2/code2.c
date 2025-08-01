// Write a C program to assign values to each member of the following structure.
// Pass the populated structure to a function Using call-by-value and another
// function using call-by-address and print the value of each member of the
// structure.
// struct student_info{
// int roll_no;
// char name [50];
// float CGPA;
// struct dob age;
// };



#include <stdio.h>
#include <string.h>

struct dob {
    int day;
    int month;
    int year;
};

struct student_info {
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

void print_student_info_by_value(struct student_info student) {
    printf("\n--- Printing by Call-by-Value ---\n");
    printf("Roll No: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %.2f\n", student.CGPA);
    printf("Date of Birth: %d/%d/%d\n", student.age.day, student.age.month, student.age.year);
}

void print_student_info_by_address(struct student_info *student_ptr) {
    printf("\n--- Printing by Call-by-Address ---\n");
    printf("Roll No: %d\n", student_ptr->roll_no);
    printf("Name: %s\n", student_ptr->name);
    printf("CGPA: %.2f\n", student_ptr->CGPA);
    printf("Date of Birth: %d/%d/%d\n", student_ptr->age.day, student_ptr->age.month, student_ptr->age.year);
}

int main() {
    struct student_info student1;

    student1.roll_no = 101;
    strcpy(student1.name, "Alice Smith");
    student1.CGPA = 8.75;
    student1.age.day = 15;
    student1.age.month = 9;
    student1.age.year = 2002;

    print_student_info_by_value(student1);

    print_student_info_by_address(&student1);

    return 0;
}