#include "Lecturer.h"
#include "Staff.h"
#include "Student.h"

void loadfilestaff(ifstream& f, staff*& Sf, int& num)
{
	staff* cur = nullptr;
	f >> num;
	f.ignore();
	for (int i = 0;i < num;++i)
	{
		if (Sf == nullptr)
		{
			Sf = new staff;
			characterfromfile(f, Sf->user);
			characterfromfile(f, Sf->password);
			characterfromfile(f, Sf->fullname);
			f >> Sf->gender;
			Sf->pNext = nullptr;
			cur = Sf;
		}
		else
		{
			cur->pNext = new staff;
			cur = cur->pNext;
			f.ignore();
			characterfromfile(f, cur->user);
			characterfromfile(f, cur->password);
			characterfromfile(f, cur->fullname);
			f >> cur->gender;
			cur->pNext = nullptr;
		}
	}
}

void savefilestaff(ofstream& f, staff* Sf, int num)
{
	staff* cur = Sf;
	f << num << endl;
	while (cur != nullptr) {
		f << cur->user << '\n';
		f << cur->password << '\n';
		f << cur->fullname << '\n';
		if (cur->gender == true)
		{
			f << "1" << '\n';
		}
		else
		{
			f << "0" << '\n';
		}
		cur = cur->pNext;
	}
}

void loadfilelecturer(ifstream& f, lecturer*& Lt, int& num)
{
	lecturer* cur = nullptr;
	f >> num;
	f.ignore();
	for (int i = 0;i < num;++i)
	{
		if (Lt == nullptr)
		{
			Lt = new lecturer;
			characterfromfile(f, Lt->user);
			characterfromfile(f, Lt->password);
			characterfromfile(f, Lt->fullname);
			characterfromfile(f, Lt->degree);
			f >> Lt->gender;
			Lt->pNext = nullptr;
			cur = Lt;
		}
		else
		{
			cur->pNext = new lecturer;
			cur = cur->pNext;
			f.ignore();
			characterfromfile(f, cur->user);
			characterfromfile(f, cur->password);
			characterfromfile(f, cur->fullname);
			characterfromfile(f, cur->degree);
			f >> cur->gender;
			cur->pNext = nullptr;
		}
	}
}

void savefilelecturer(ofstream& f, lecturer* Lt, int num)
{
	lecturer* cur = Lt;
	f << num << endl;
	while (cur != nullptr) {
		f << cur->user << '\n';
		f << cur->password << '\n';
		f << cur->fullname << '\n';
		f << cur->degree << '\n';
		if (cur->gender == true)
		{
			f << "1" << '\n';
		}
		else
		{
			f << "0" << '\n';
		}
		cur = cur->pNext;
	}
}

void loadfilestudent(ifstream& f, student*& St, int& num)
{
	student* cur = nullptr;
	f >> num;
	for (int i = 0;i < num;++i)
	{
		if (St == nullptr)
		{
			St = new student;
			f >> St->ID;
			f.ignore();
			characterfromfile(f, St->password);
			characterfromfile(f, St->fullname);
			f >> St->gender;
			f >> St->Dob.year;
			f >> St->Dob.month;
			f >> St->Dob.day;
			f.ignore();
			characterfromfile(f, St->Class);
			St->pNext = nullptr;
			cur = St;
		}
		else
		{
			cur->pNext = new student;
			cur = cur->pNext;
			f >> cur->ID;
			f.ignore();
			characterfromfile(f, cur->password);
			characterfromfile(f, cur->fullname);
			f >> cur->gender;
			f >> cur->Dob.year;
			f >> cur->Dob.month;
			f >> cur->Dob.day;
			f.ignore();
			characterfromfile(f, cur->Class);
			cur->pNext = nullptr;
		}
	}
}

void savefilestudent(ofstream& f, student* St, int num)
{
	student* cur = St;
	f << num << endl;
	while (cur != nullptr) {
		f << cur->ID << endl;
		f << cur->password << endl;
		f << cur->fullname << endl;
		if (cur->gender == true)
		{
			f << "1" << endl;
		}
		else
		{
			f << "0" << endl;
		}
		f << cur->Dob.year << " ";
		f << cur->Dob.month << " ";
		f << cur->Dob.day << endl;
		f << cur->Class << endl;
		cur = cur->pNext;
	}
}

void loadfilestudentinclass(ifstream& f, student*& St, int& num)
{
	student* cur = St;
	f >> num;
	for (int i = 0;i < num;++i)
	{
		if (St == nullptr)
		{
			St = new student;
			f >> St->ID;
			f.ignore();
			characterfromfile(f, St->password);
			characterfromfile(f, St->fullname);
			f >> St->gender;
			f >> St->Dob.year;
			f >> St->Dob.month;
			f >> St->Dob.day;
			St->pNext = nullptr;
			cur = St;
		}
		else
		{
			cur->pNext = new student;
			cur = cur->pNext;
			f >> cur->ID;
			f.ignore();
			characterfromfile(f, cur->password);
			characterfromfile(f, cur->fullname);
			f >> cur->gender;
			f >> cur->Dob.year;
			f >> cur->Dob.month;
			f >> cur->Dob.day;
			cur->pNext = nullptr;
		}
	}
}

void savefilestudentinclass(ofstream& f, student* St, int num)
{
	student* cur = St;
	f << num << endl;
	while (cur != nullptr) {
		f << cur->ID << '\n';
		f << cur->password << '\n';
		f << cur->fullname << '\n';
		if (cur->gender == true)
		{
			f << "1" << '\n';
		}
		else
		{
			f << "0" << '\n';
		}
		f << cur->Dob.year << " ";
		f << cur->Dob.month << " ";
		f << cur->Dob.day << '\n';
		cur = cur->pNext;
	}
}

void loadfilecourseinclass(ifstream& f, course*& St, int& num)
{
	course* cur = nullptr;
	f >> num;
	for (int i = 0; i < num; ++i)
	{
		if (St == nullptr)
		{
			St = new course;
			f >> St->no;
			f.ignore();
			characterfromfile(f, St->id);
			characterfromfile(f, St->name);
			characterfromfile(f, St->Class);
			characterfromfile(f, St->ltAccount);
			characterfromfile(f, St->ltName);
			characterfromfile(f, St->degree);
			f >> St->gender;
			f >> St->start_date.month >> St->start_date.day >> St->start_date.year;
			f >> St->end_date.month >> St->end_date.day >> St->end_date.year;
			f >> St->number;
			f.ignore();

			for (int i = 0; i < St->number; i++) {
				characterfromfile(f, St->day[i].day);
				f >> St->day[i].start_hour >> St->day[i].start_min;
				f >> St->day[i].end_hour >> St->day[i].end_min;
				f.ignore();
				characterfromfile(f, St->day[i].room);
			}

			St->pNext = nullptr;
			cur = St;
		}
		else
		{
			cur->pNext = new course;
			cur = cur->pNext;
			f >> cur->no;
			f.ignore();
			characterfromfile(f, cur->id);
			characterfromfile(f, cur->name);
			characterfromfile(f, cur->Class);
			characterfromfile(f, cur->ltAccount);
			characterfromfile(f, cur->ltName);
			characterfromfile(f, cur->degree);
			f >> cur->gender;
			f >> cur->start_date.month >> cur->start_date.day >> cur->start_date.year;
			f >> cur->end_date.month >> cur->end_date.day >> cur->end_date.year;
			f >> cur->number;
			f.ignore();
			for (int i = 0; i < cur->number; i++) {
				characterfromfile(f, cur->day[i].day);
				f >> cur->day[i].start_hour >> cur->day[i].start_min;
				f >> cur->day[i].end_hour >> cur->day[i].end_min;
				f.ignore();
				characterfromfile(f, cur->day[i].room);
			}
			cur->pNext = nullptr;
		}
	}
}

void savefilecourseinclass(ofstream& f, course* St, int num)
{
	course* cur = St;
	f << num << endl;
	while (cur != nullptr) {
		f << cur->no << '\n';
		f << cur->id << endl;
		f << cur->name << endl;
		f << cur->Class << endl;
		f << cur->ltAccount << '\n';
		f << cur->ltName << '\n';
		f << cur->degree << '\n';
		f << cur->gender << '\n';
		f << cur->start_date.month << " " << cur->start_date.day << " " << cur->start_date.year << endl;
		f << cur->end_date.month << " " << cur->end_date.day << " " << cur->end_date.year << endl;
		f << cur->number << endl;
		for (int i = 0; i < cur->number; i++) {
			f << cur->day[i].day << endl;
			f << cur->day[i].start_hour << " " << cur->day[i].start_min << endl;
			f << cur->day[i].end_hour << " " << cur->day[i].end_min << endl;
			f << cur->day[i].room << endl;
		}
		cur = cur->pNext;
	}
}

void loadfilestudentincourse(ifstream& f, student*& St, int& num)
{
	student* cur = nullptr;
	f >> num;
	for (int i = 0; i < num; ++i)
	{
		if (St == nullptr)
		{
			St = new student;
			f >> St->ID;
			f.ignore();
			characterfromfile(f, St->fullname);
			f >> St->gender;
			f >> St->Dob.year;
			f >> St->Dob.month;
			f >> St->Dob.day;
			St->pNext = nullptr;
			cur = St;
		}
		else
		{
			student* newNode = new student; 
			cur->pNext = newNode;
			newNode->pNext = nullptr;
			f >> newNode->ID;
			f.ignore();
			characterfromfile(f, newNode->fullname);
			f >> newNode->gender;
			f >> newNode->Dob.year;
			f >> newNode->Dob.month;
			f >> newNode->Dob.day;
			cur = cur->pNext;
		}
	}
}

void savefilestudentincourse(ofstream& f, student* St, int num)
{
	student* cur = St;
	f << num << endl;
	while (cur != nullptr) {
		f << cur->ID << '\n';
		f << cur->fullname << '\n';
		if (cur->gender == true)
		{
			f << "1" << '\n';
		}
		else
		{
			f << "0" << '\n';
		}
		f << cur->Dob.year << " ";
		f << cur->Dob.month << " ";
		f << cur->Dob.day << '\n';
		cur = cur->pNext;
	}
}

void savefilescoreincourse(ofstream& f, student_Sche* Sc, int num, student* meow)
{
	student_Sche* cur = Sc;
	student* cur1 = meow;
	f << num << endl;
	while (cur != nullptr) {
		f << cur1->ID << endl;
		f << cur->active << '\n';
		f << cur->score.midterm << '\n';
		f << cur->score.finalterm << '\n';
		f << cur->score.bonus << '\n';
		f << cur->score.total << '\n';
		cur = cur->pNext;
		cur1 = cur1->pNext;
	}
}

void loadfilescoreincourse(ifstream& f, student_Sche*& St, int& num, student*& Stu)
{
	student_Sche* cur = nullptr;
	student* std = nullptr;
	f >> num;
	for (int i = 0; i < num; ++i)
	{
		if (Stu == nullptr)
		{
			Stu = new student;
			f >> Stu->ID;
			Stu->pNext = nullptr;
			std = Stu;
		}
		else
		{
			std->pNext = new student;
			std = std->pNext;
			f >> std->ID;
			std->pNext = nullptr;
		}
		if (St == nullptr)
		{
			St = new student_Sche;
			f >> St->active;
			f >> St->score.midterm;
			f >> St->score.finalterm;
			f >> St->score.bonus;
			f >> St->score.total;
			St->pNext = nullptr;
			cur = St;
		}
		else
		{
			cur->pNext = new student_Sche;
			cur = cur->pNext;
			f >> cur->active;
			f >> cur->score.midterm;
			f >> cur->score.finalterm;
			f >> cur->score.bonus;
			f >> cur->score.total;
			cur->pNext = nullptr;
		}
	}
}

void savefilecheckinincourse(ofstream& out, student_Sche * St, int num ,int numdate, student* gaugau) {
	student_Sche* cur_st = St;
	date_to_check * cur3 = cur_st->pHead;
	student* cur1 = gaugau;
	out << num << endl;
	out << numdate << endl;
	for (int i = 0; i < num; i++) {
		out << cur1->ID << endl;
		for (int j = 0; j< numdate; j++) {
			out << cur3->date.year << " " << cur3->date.month << " " << cur3->date.day << " "
				<< cur3->start_hour << " " << cur3->start_min << " " << cur3->end_hour << " " << cur3->end_min << " " << cur3->checkin << endl;
			cur3 = cur3->pNext;
		}
		cur_st = cur_st->pNext;
		if (cur_st != nullptr) {
			cur3 = cur_st->pHead;
			cur1 = cur1->pNext;
		}
	}
}

void loadfilecheckinincourse(ifstream& f, student_Sche*& DATE, int& num, int& numdate, student*& St) {
	
	student* tmpStu=nullptr;
	date_to_check* tmpDATE=nullptr;
	student_Sche* tmpst=nullptr;
	f >> num;
	f >> numdate;
	for (int i = 0;i < num;++i)
	{
		if (St == nullptr)
		{
			St = new student;
			f >> St->ID;
			St->pNext = nullptr;
			tmpStu = St;
		}
		else
		{
			tmpStu->pNext = new student;
			tmpStu = tmpStu->pNext;
			f >> tmpStu->ID;
			tmpStu->pNext = nullptr;
		}
		if (DATE == nullptr) {
			DATE = new student_Sche;
			DATE->pHead = nullptr;
			DATE->pNext = nullptr;
			tmpst = DATE;
		}
		else {
			tmpst->pNext = new student_Sche;
			tmpst = tmpst->pNext;
			tmpst->pHead = nullptr;
			tmpst->pNext = nullptr;
		
		}
			for (int j = 0; j < numdate; ++j)
			{
				if (tmpst->pHead == nullptr)
				{
					tmpst->pHead = new date_to_check;
					f >> tmpst->pHead->date.year;
					f >> tmpst->pHead->date.month;
					f >> tmpst->pHead->date.day;
					f >> tmpst->pHead->start_hour;
					f >> tmpst->pHead->start_min;
					f >> tmpst->pHead->end_hour;
					f >> tmpst->pHead->end_min;
					f >> tmpst->pHead->checkin;
					tmpst->pNext = nullptr;
					tmpDATE = tmpst->pHead;
				}
				else
				{
					tmpDATE->pNext = new date_to_check;
					tmpDATE = tmpDATE->pNext;
					f >> tmpDATE->date.year;
					f >> tmpDATE->date.month;
					f >> tmpDATE->date.day;
					f >> tmpDATE->start_hour;
					f >> tmpDATE->start_min;
					f >> tmpDATE->end_hour;
					f >> tmpDATE->end_min;
					f >> tmpDATE->checkin;
					tmpDATE->pNext = nullptr;
				}
			}
		}
	}

void loadfilescoreinnewcourse(ifstream& f, student_Sche*& St, int& num)
{
	student* Stu = nullptr;
	student_Sche* cur = nullptr;
	student* std = nullptr;
	f >> num;
	for (int i = 0; i < num; ++i)
	{
		if (Stu == nullptr)
		{
			Stu = new student;
			f >> Stu->ID;
			Stu->pNext = nullptr;
			std = Stu;
		}
		else
		{
			std->pNext = new student;
			std = std->pNext;
			f >> std->ID;
			std->pNext = nullptr;
		}
		if (St == nullptr)
		{
			St = new student_Sche;
			f >> St->active;
			f >> St->score.midterm;
			f >> St->score.finalterm;
			f >> St->score.bonus;
			f >> St->score.total;
			St->pNext = nullptr;
			cur = St;
		}
		else
		{
			cur->pNext = new student_Sche;
			cur = cur->pNext;
			f >> cur->active;
			f >> cur->score.midterm;
			f >> cur->score.finalterm;
			f >> cur->score.bonus;
			f >> cur->score.total;
			cur->pNext = nullptr;
		}
	}
	deleteIDincourse(Stu);
}

void loadfilecheckininnewcourse(ifstream& f, student_Sche*& DATE, int& num, int& numdate) {

	student* St = nullptr;
	student* tmpSt = nullptr;
	student_Sche* tmpSc = nullptr;
	date_to_check* tmpDATE = nullptr;
	f >> num;
	f >> numdate;
	for (int i = 0;i < num;++i)
	{
		if (St == nullptr)
		{
			St = new student;
			f >> St->ID;
			St->pNext = nullptr;
			tmpSt = St;
		}
		else
		{
			tmpSt->pNext = new student;
			tmpSt = tmpSt->pNext;
			f >> tmpSt->ID;
			tmpSt->pNext = nullptr;
		}
		if (DATE == nullptr)
		{
			DATE = new student_Sche;
			DATE->pHead = nullptr;
			DATE->pNext = nullptr;
			tmpSc = DATE;
		}
		else
		{
			tmpSc->pNext = new student_Sche;
			tmpSc = tmpSc->pNext;
			tmpSc->pHead = nullptr;
			tmpSc->pNext = nullptr;
		}
		tmpDATE = tmpSc->pHead;
		for (int j = 0;j < numdate;++j)
		{
			if (tmpSc->pHead == nullptr)
			{
				tmpSc->pHead = new date_to_check;
				f >> tmpSc->pHead->date.year;
				f >> tmpSc->pHead->date.month;
				f >> tmpSc->pHead->date.day;
				f >> tmpSc->pHead->start_hour;
				f >> tmpSc->pHead->start_min;
				f >> tmpSc->pHead->end_hour;
				f >> tmpSc->pHead->end_min;
				f >> tmpSc->pHead->checkin;
				tmpSc->pNext = nullptr;
				tmpDATE = tmpSc->pHead;
			}
			else
			{
				tmpDATE->pNext = new date_to_check;
				tmpDATE = tmpDATE->pNext;
				f >> tmpDATE->date.year;
				f >> tmpDATE->date.month;
				f >> tmpDATE->date.day;
				f >> tmpDATE->start_hour;
				f >> tmpDATE->start_min;
				f >> tmpDATE->end_hour;
				f >> tmpDATE->end_min;
				f >> tmpDATE->checkin;
				tmpDATE->pNext = nullptr;
			}
		}
	}
	deleteIDincourse(St);
}