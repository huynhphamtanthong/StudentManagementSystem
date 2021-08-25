#ifndef _GENERAL_H_
#define _GENERAL_H_
#define _CRT_SECURE_NO_WARNINGS


#include <string.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <chrono>
#include <conio.h>
#include <ctime>
#include <math.h>
#include <iomanip>
using namespace std;

struct date
{
	int day;
	int month;
	int year;
};

struct staff
{
	char* user = nullptr;
	char* password = nullptr;
	char* fullname = nullptr;
	bool gender;
	staff* pNext;
};

struct lecturer
{
	char* user = nullptr;
	char* password = nullptr;
	char* fullname = nullptr;
	char* degree = nullptr;
	bool gender;
	lecturer* pNext;
};

struct student
{
	unsigned int ID;
	char* password ;
	char* fullname ;
	date Dob;
	char* Class ;
	bool gender;
	student* pNext;
};

struct Day {
	int end_min;
	int end_hour;
	int start_min;
	int start_hour;
	char* room = nullptr;
	char* day = nullptr;
};
struct course {
	int no;
	char* id = nullptr;
	char* name = nullptr;
	char* Class = nullptr;
	char* ltAccount = nullptr;
	char* ltName = nullptr;
	char* degree = nullptr;
	int gender;
	int number;
	date start_date;
	date end_date;
	Day* day = new Day[20];
	course* pNext;
};

struct date_to_check {
	date date;
	int start_hour;
	int start_min;
	int end_hour;
	int end_min;
	int checkin = -1;
	date_to_check* pNext;
};
struct Score {
	float midterm = -1;
	float finalterm = -1;
	float bonus = -1;
	float total = -1;
};
struct student_Sche {
	int active = 0 ;
	Score score;
	date_to_check* pHead = nullptr;
	student_Sche* pNext;
};
struct CLASS
{
	char* classname = nullptr;
	CLASS* pNext;
};

void generatePass(char*& arr, int year, int month, int day);
void characterfromfile(ifstream& f, char*& arr);
void inputcharacter(char*& arr);
bool compare(char* ptr1, char* ptr2);
void convert(char*& arr, string str);
bool Login(staff*& Sf, lecturer*& Lt, student*& St, int choice);
void checkExistClass(char* arr);
float getDecimal(string str);
void changeDate(int& day, int& month, int& year, int& gap);
int findDate(char* str);
bool difference(int day, int month, int year, course* cur2);
void getTime(int& day, int& mon, int& year, int& hour, int& min);
int checkDate(int day,int mon, int year,int hour,int min, date_to_check* cur); 
int compareTime(int hour, int min, date_to_check* cur);
void readCSVscore();
void create_date_to_check(char tmpcls[], char* id, course* cur2,student* st, int num1);
void getStr(char*& arr, string str);

void deletestaff(staff*& pH);
void loadfilestaff(ifstream& f, staff*& Sf, int& num);
void savefilestaff(ofstream& f, staff* Sf, int num);

void deletelecturer(lecturer*& pH);
void loadfilelecturer(ifstream& f, lecturer*& Lt, int& num);
void savefilelecturer(ofstream& f, lecturer* Lt, int num);

void deletestudent(student*& pH);
void loadfilestudent(ifstream& f, student*& St, int& num);
void savefilestudent(ofstream& f, student* St, int num);

void loadfilestudentinclass(ifstream& f, student*& St, int& num);
void savefilestudentinclass(ofstream& f, student* St, int num);
void deletestudentinclass(student*& pH);

void loadfilecourseinclass(ifstream& f, course*& St, int& num);
void savefilecourseinclass(ofstream& f, course* St, int num);
void deletecourseinclass(course*& pH);

void loadfilestudentincourse(ifstream& f, student*& St, int& num);
void savefilestudentincourse(ofstream& f, student* St, int num);
void deletestudentincourse(student*& St);

void savefilescoreincourse(ofstream& f, student_Sche* St, int num, student* meow);
void loadfilescoreincourse(ifstream& f, student_Sche*& St, int& num, student*& Stu);

void deleteIDincourse(student*& St);
void deletescoreincourse(student_Sche*& Sc);

void savefilecheckinincourse(ofstream& out, student_Sche* St, int num, int numdate, student* gaugau);
void loadfilecheckinincourse(ifstream& f, student_Sche*& DATE, int& num, int& numdate, student*& St);
void deletecheckinincourse(student_Sche*& Sc);

void loadfilescoreinnewcourse(ifstream& f, student_Sche*& St, int& num);
void loadfilecheckininnewcourse(ifstream& f, student_Sche*& DATE, int& num, int& numdate);

void deleteDATE(date_to_check*& date);
#endif
