#include "General.h"

void deletestaff(staff*& pH)
{
	staff* tmp = pH;
	while (pH != nullptr)
	{
		pH = pH->pNext;
		delete[]tmp->user;
		delete[]tmp->password;
		delete[]tmp->fullname;
		delete tmp;
		tmp = pH;
	}
}

void deletelecturer(lecturer*& pH)
{
	lecturer* tmp = pH;
	while (pH != nullptr)
	{
		pH = pH->pNext;
		delete[]tmp->user;
		delete[]tmp->password;
		delete[]tmp->fullname;
		delete[]tmp->degree;
		delete tmp;
		tmp = pH;
	}
}

void deletestudent(student*& pH)
{
	student* tmp = pH;
	while (pH != nullptr)
	{
		pH = pH->pNext;
		delete[]tmp->password;
		delete[]tmp->fullname;
		delete[]tmp->Class;
		delete tmp;
		tmp = pH;
	}
}

void deletestudentinclass(student*& pH)
{
	student* tmp = pH;
	while (pH != nullptr)
	{
		pH = pH->pNext;
		delete[]tmp->password;
		delete[]tmp->fullname;
		delete tmp;
		tmp = pH;
	}
}

void deletecourseinclass(course*& pH)
{
	course* tmp = pH;
	while (pH)
	{
		pH = pH->pNext;
		delete[]tmp->id;
		delete[]tmp->name;
		delete[]tmp->Class;
		delete[]tmp->ltAccount;
		delete[]tmp->ltName;
		delete[]tmp->degree;
		for (int i = 0;i < tmp->number;++i)
		{
			delete[]tmp->day[i].room;
			delete[]tmp->day[i].day;
		}
		delete[]tmp->day;
		delete tmp;
		tmp = pH;
	}
}

void deletestudentincourse(student*& pH)
{
	student* tmp = pH;
	while (pH != nullptr)
	{
		pH = pH->pNext;
		delete[]tmp->fullname;
		delete tmp;
		tmp = pH;
	}
}

void deleteIDincourse(student*& St)
{
	student* TmpSt = St;
	while (St)
	{
		St = St->pNext;
		delete TmpSt;
		TmpSt = St;
	}
}

void deletescoreincourse(student_Sche*& Sc)
{
	student_Sche* TmpSc = Sc;
	while (Sc)
	{
		Sc = Sc->pNext;
		delete TmpSc;
		TmpSc = Sc;
	}
}

void deletecheckinincourse(student_Sche*& Sc)
{
	date_to_check* Tmp = Sc->pHead;
	while (Sc)
	{
		while (Sc->pHead)
		{
			Sc->pHead = Sc->pHead->pNext;
			delete Tmp;
			Tmp = Sc->pHead;
		}
		Sc = Sc->pNext;
	}
}

void deleteDATE(date_to_check*& date) {
	date_to_check* tmp = date;
	while (date) {
		date = date->pNext;
		delete tmp;
		tmp = date; 
	}
}