#ifndef _STAFF_H_
#define _STAFF_H_

#include "General.h"

void profileSf(staff* Sf);
void changePassSf(staff*& Sf);

void readCSVSt();
void addStudent();
void editStudent();
void removeStudent();
void changeClass();
void academicyear();
void viewClass();
void viewStudentsInAClass();

void readCourseCSV();
void addCourse();
void editCourse();
void removeCourse();
void removeStdinCourse();
void viewCourse();
void viewStudentinCourse();
void editlecturer();
void exportscoreboardtocsv();
void exportattendancetocsv();
void viewAttendance();
void addStdinCourse();
#endif 
