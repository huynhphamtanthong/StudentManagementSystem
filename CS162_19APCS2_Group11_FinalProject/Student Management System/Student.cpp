#include "Student.h"

void profileSt(student* St) {
	cout << "My profile : " << endl;
	cout << "Student's ID : " << St->ID << endl;
	cout << "Fullname : " << St->fullname << endl;
	cout << "Class : " << St->Class << endl;
	if (St->gender == 0)
	{
		cout << "Gender : Male" << endl;
	}
	else
	{
		cout << "Gender : Female" << endl;
	}
	cout << "Date of birth : " << St->Dob.year << " - " << St->Dob.month << " - " << St->Dob.day << endl;
	system("pause");
	cout << '\n';
}

void changePassSt(student*& St) {
	int check = 1;
	char* old_pass;
	bool changedPass = false;
	cin.ignore();
	do {
		cout << "Pleas input your old password : ";
		inputcharacter(old_pass);
		if (compare(old_pass, St->password) == true) changedPass = true;
		else {
			cout << "Your password is incorrect." << endl
				<< "Input 1 to try again." << endl
				<< "Or input 0 to turn back to menu" << endl
				<< "Your choice : ";
			cin >> check;
			cin.ignore();
			if (check == 0)return;
			cout << endl;
		}
	} while (changedPass == false);
	delete[]St->password;
	delete[]old_pass;
	St->password = nullptr;
	cout << "Please input your new password : ";
	inputcharacter(St->password);
	student* newSt = nullptr;
	int total = 0;
	ifstream in;
	in.open("Student.txt");
	if (!in.is_open())
	{
		cout << "Student's data is missing." << endl;
	}
	else
	{
		loadfilestudent(in, newSt, total);
		in.close();
	}
	student* newcur = newSt;
	while (newcur != nullptr)
	{
		if (compare(newcur->fullname, St->fullname))
		{
			delete[]newcur->password;
			newcur->password = St->password;
			break;
		}
		newcur = newcur->pNext;
	}
	ofstream out;
	out.open("Student.txt");
	if (!out.is_open())
	{
		cout << "Student's data is missing." << endl;
	}
	else
	{
		savefilestudent(out, newSt, total);
		out.close();
	}
	cout << "Change password successfully." << endl;
	system("pause");
	cout << endl;
}
void check_in(student*& St) {
	ifstream ip;
	ofstream op;
	bool checkf = true;
	do {
		cin.ignore();

		char clss[100];
		char cour[100];
		student_Sche* date = nullptr;
		student_Sche* cur = nullptr;
		student* st = nullptr, * cur2 = nullptr;
		cout << "You choose check in session !"
			<< "Input class you want to check-in :";
		cin.getline(clss,100);
		cout << "Input course of class you want to check in: ";
		cin.getline(cour,100);

		strcat(clss, "-");
		strcat(clss, cour);
		strcat(clss, "-checkin.txt");

		ip.open(clss);
		if (!ip.is_open()) {
			cout << "Cannot find " << clss << endl;
			return;
		}
		int num = 0, numdate = 0;
		loadfilecheckinincourse(ip, date, num, numdate, st);
		ip.close();
		cur = date;
		cur2 = st;
		//check if student is in class or not 
		for (int i = 0; i < num; i++) {
			if (cur2->ID == St->ID) {
				break;
			}
			else {
				cur = cur->pNext;
				cur2 = cur2->pNext;
			}
		}
		if (cur == nullptr) {
			cout << "You are not entered into this course. Please check class and course again " << endl;
			return;
		}
		date_to_check* cur1 = cur->pHead;
		int option, day, mon, year, hour, min;
		cout << "Press 1 to check in " << endl;
		cout << "Press 2 to back to menu " << endl;
		int i = 1;
		cout << "Input your option : ";
		cin >> option;
		while (option != 1 && option != 2)
		{
			cout << "Your input is invalid. Please try another one." << endl;
			cout << "1: check-in   2: back to menu" << endl;
			cout << "Your option : ";
			cin >> option;
		}
		if (option == 1) {
			cout << "Your schedule of this course : " << endl;
			while (cur1 != nullptr) {
				cout << i << ". " << cur1->date.year << " " << cur1->date.month << " " << cur1->date.day << " " << cur1->start_hour << " " << cur1->start_min << " " << cur1->end_hour << " " << cur1->end_min <<" "<<cur1->checkin << endl;
				cur1 = cur1->pNext;
				i++;
			}
			cur1 = cur->pHead;

			int checkin;
			cout << "Choose period you want to check in : " << endl;
			cin >> checkin;

			//get current time
			getTime(day, mon, year, hour, min);

			if (checkin == 1) {
				if (cur1->checkin == 1) {
					cout << "You have checked in before !" << endl;
					return;
				}
				else if (cur1->checkin == -1) {
					if (checkDate(day, mon, year, hour, min, cur1) == 1) {
						cur1->checkin = 1;
						cout << "Your check-in succesfully. Enter class please !" << endl;
						op.open(clss);
						savefilecheckinincourse(op, date, num, numdate, st);
						op.close();
						return;
					}
					else if (checkDate(day, mon, year, hour, min, cur1) == 0) {
						cout << "You are marked absense. You are late for class !" << endl;
						return;
					}
					else {
						cout << "Class is not ready. Please be back after several minutes !" << endl;
						return;
					}
				}
			}
			else {
				for (int j = 0; j < checkin - 1; j++) {
					cur1 = cur1->pNext;
				}
				if (cur1->checkin == 1) {
					cout << "You have checked in before !" << endl;
					return;
				}
				else if (cur1->checkin == -1) {
					if (checkDate(day, mon, year, hour, min, cur1) == 1) {
						cur1->checkin = 1;
						cout << "Your check-in succesfully. Enter class please !" << endl;
						op.open(clss);
						savefilecheckinincourse(op, date, num, numdate, st);
						op.close();
						return;
					}
					else if (checkDate(day, mon, year, hour, min, cur1) == 0) {
						cout << "You are late for class !" << endl;
						return;
					}
					else {
						cout << "Class is not ready. Please be back in exact course's time!" << endl;
						return;
					}
				}
			}
		}
		else if (option == 2) {
			return;
		}
		deletecheckinincourse(date);
		deletestudentincourse(st);
	} while (checkf == true);
	system("pause");
}


void viewcheckin(int ID)
{
	ifstream in;
	char* crs, cls[1000];
	cout << "Input your course ID:";
	cin.ignore();
	inputcharacter(crs);
	cout << "Input the class of the course you are in:";
	cin.getline(cls, 1000);
	char tmpcls[1000];
	strcpy(tmpcls, cls);
	strcat(tmpcls, "-");
	strcat(tmpcls, crs);
	strcat(tmpcls, "-score.txt");
	in.open(tmpcls);
	student_Sche* sc = nullptr;
	student* st = nullptr;
	if (!in.is_open()) {
		cout << "can't open file";
		return;
	}
	int num;
	loadfilescoreincourse(in, sc, num, st);
	in.close();
	student* cur = st;
	student_Sche* cursc = sc;
	int chck = 0;
	while (cur != nullptr) {
		if (cur->ID = ID) {
			chck = 1;
			break;
		}
		else
			cursc = cursc->pNext;
		cur = cur->pNext;
		chck = 0;
	}
	if (!chck) {
		cout << "no student data found in this course";
		return;
	}
	if (cursc->active == -1) {
		cout << "you are no longer in this course";
		return;
	}
	deletescoreincourse(sc);
	sc = nullptr;
	deleteIDincourse(st);
	st = nullptr;
	char tmpcls1[1000];
	strcpy(tmpcls1, cls);
	strcat(tmpcls1, "-");
	strcat(tmpcls1, crs);
	strcat(tmpcls1, "-checkin.txt");
	in.open(tmpcls1);
	if (!in.is_open()) {
		cout << "no check in file available";
		return;
	}
	int numdate;
	loadfilecheckinincourse(in, sc, num, numdate, st);
	in.close();
	cur = st;
	cursc = sc;
	while (cur != nullptr) {
		if (cur->ID = ID) {
			cout << ID << endl;
			date_to_check* curdt = cursc->pHead;
			for (int i = 0; i < numdate; i++) {
				cout << curdt->date.year << " " << curdt->date.month << " " << curdt->date.day << " " << curdt->start_hour << " " << curdt->start_min
					<< " " << curdt->end_hour << " " << curdt->end_min;
				if (curdt->checkin == -1) {
					cout << "  - Absent" << endl;
				}
				else {
					cout << "  - Present" << endl;
				}
				curdt = curdt->pNext;
			}
			break;
		}
		cur = cur->pNext;
		cursc = cursc->pNext;
	}
	deletecheckinincourse(sc);
	sc = nullptr;
	deleteIDincourse(st);
	st = nullptr;
	system("pause");
}

void viewschedule(student*& St)
{
	cout << endl;
	bool getback = true;
	while (getback == true)
	{
		cout << "How many classes whose courses you are studying? " << endl
			<< "Or input 0 to return back to menu" << endl
			<< "Your input : ";
		int clsnum;
		cin >> clsnum;
		cout << endl;
		while (clsnum < 0)
		{
			cout << "Invalid number. Please try again." << endl
				<< "How many classes whose courses you are studying? " << endl
				<< "Or input 0 to return back to menu" << endl
				<< "Your input : ";
			cin >> clsnum;
			cout << endl;
		}
		if (clsnum == 0)
		{
			return;
		}
		course* allcourse = nullptr;
		for (int i = 0; i < clsnum;++i)
		{
			char tmpcls[1000];

			// Get class
			if (clsnum == 1)
			{
				cout << "Are your courses included in your recent class?" << endl
					<< "1. Yes" << endl
					<< "2. No" << endl
					<< "3. Return back" << endl
					<< "Your choice : ";
				int choice1;
				cin >> choice1;
				cout << endl;
				while (choice1 != 1 && choice1 != 2 && choice1 != 3)
				{
					cout << "Invalid option. Please try again." << endl
						<< "Are your courses included in your recent class?" << endl
						<< "1. Yes" << endl
						<< "2. No" << endl
						<< "3. Return back" << endl
						<< "Your choice : ";
					cin >> choice1;
					cout << endl;
				}
				cin.ignore();
				if (choice1 == 3)
				{
					getback = true;
					break;
				}
				else if (choice1 == 1)
				{
					strcpy(tmpcls, St->Class);
				}
				else
				{
					cout << "Please input your class of your courses : ";
					cin.getline(tmpcls, 1000, '\n');
				}
			}
			else
			{
				cin.ignore();
				cout << "Please input class " << i + 1 << " : ";
				cin.getline(tmpcls, 1000, '\n');
			}

			// Get course
			course* Cse = nullptr;
			int num = 0;

			strcat(tmpcls, "-schedule.txt");
			ifstream loadcourse;
			loadcourse.open(tmpcls);
			if (!loadcourse.is_open())
			{
				cout << "Course's file is missing." << endl;
			}
			else
			{
				loadfilecourseinclass(loadcourse, Cse, num);
			}
			loadcourse.close();

			bool finish = false;
			int var = 1;
			while (finish == false)
			{
				course* tmpCse = Cse;
				cout << "Please choose a course you are studying in this class : " << endl;
				int numcse = 1;
				while (tmpCse)
				{
					cout << numcse << ". " << tmpCse->id << "-" << tmpCse->name << endl;
					tmpCse = tmpCse->pNext;
					numcse++;
				}
				cout << "Your choice : ";
				int cschoice;
				cin >> cschoice;
				if (cschoice == 1)
				{
					course* tmpcourse = Cse;
					Cse = Cse->pNext;
					tmpcourse->pNext = nullptr;
					if (allcourse == nullptr)
					{
						allcourse = tmpcourse;
					}
					else
					{
						course* curcourse = allcourse;
						while (curcourse->pNext != nullptr)
						{
							curcourse = curcourse->pNext;
						}
						curcourse->pNext = tmpcourse;
					}
				}
				else
				{
					course* curCse = Cse;
					for (int i = 0;i < cschoice - 2;++i)
					{
						curCse = curCse->pNext;
					}
					course* tmpcourse = curCse->pNext;
					curCse->pNext = curCse->pNext->pNext;
					tmpcourse->pNext = nullptr;
					if (allcourse == nullptr)
					{
						allcourse = tmpcourse;
					}
					else
					{
						course* curcourse = allcourse;
						while (curcourse->pNext != nullptr)
						{
							curcourse = curcourse->pNext;
						}
						curcourse->pNext = tmpcourse;
					}
				}
				cout << endl << "Do you have any other courses in this class?" << endl
					<< "1. Yes" << endl
					<< "2. No" << endl
					<< "Your choice : ";
				int nextchoice;
				cin >> nextchoice;
				cout << endl;
				while (nextchoice != 1 && nextchoice != 2)
				{
					cout << endl << "Invalid option. Please try again." << endl
						<< "Do you have any other courses in this class?" << endl
						<< "1. Yes" << endl
						<< "2. No" << endl
						<< "Your choice : ";
					cin >> nextchoice;
					cout << endl;
				}
				if (nextchoice == 1)
				{
					if (Cse == nullptr)
					{
						cout << "No courses available." << endl;
						finish = true;
					}
					else
						finish = false;
				}
				else
				{
					finish = true;
				}
			}
			deletecourseinclass(Cse);
		}
		if (allcourse == nullptr)
		{
			cout << "No courses are inputted." << endl;
			continue;
		}
		cout << setw(50) << "YOUR SCHEDULE" << endl;
		cout << setw(21) << "MON" << setw(13) << "TUE" << setw(13) << "WED" << setw(13) << "THU" << setw(13) << "FRI" << setw(13) << "SAT";
		course* cur = nullptr;
		
		string date[] = { "MON","TUE","WED","THU","FRI","SAT" };
		for (int k = 0;k < 4;++k)
		{
			cout << endl;
			int hour;
			int minite = 30;
			switch (k)
			{
			case 0:
				hour = 7;
				cout << "7h30 - 9h30" << setw(10);
				break;
			case 1:
				hour = 9;
				cout << "9h30 - 11h30" << setw(9);
				break;
			case 2:
				hour = 13;
				cout << "13h30 - 15h30" << setw(8);
				break;
			case 3:
				hour = 15;
				cout << "15h30 - 17h30" << setw(8);
				break;
			}
			for (int i = 0; i < 6;++i)
			{
				int check = 0;
				cur = allcourse;
				while (cur)
				{
					for (int j = 0;j < cur->number;++j)
					{
						if (strcmp(date[i].c_str(), cur->day[j].day) == 0 && cur->day[j].start_hour == hour)
						{
							cout << cur->id << " (" << cur->day[j].room << ")" << setw(7);
							check++;
							break;
						}
					}
					cur = cur->pNext;
				}
				if (check == 0)
				{
					cout << "     //" << setw(13);
				}
			}
		}
		getback = false;
		deletecourseinclass(allcourse);
		cout << endl;
	}
	system("pause");
}

void viewownscore(student*& St)
{
	ifstream in;
	char* ID, *clss;
	cin.ignore();
	cout << "Enter the course ID: ";
	inputcharacter(ID);
	cout << "Enter the clss: ";
	inputcharacter(clss);
	strcat(clss, "-");
	strcat(clss, ID);
	strcat(clss, "-score.txt");
	in.open(clss);
	if (!in.is_open()) {
		cout << "No score data found";
		system("Pause");
		return;
	}
	int num;
	student* head=nullptr, *cur;
	student_Sche* headS = nullptr,*curS;
	loadfilescoreincourse(in, headS,num, head);
	in.close();
	cur = head;
	curS = headS;
	for (int i = 0; i < num; i++) {
		if (cur->ID == St->ID) {
			cout << "Bonus: " << curS->score.bonus<<endl;
			cout << "Midterm: " << curS->score.midterm<<endl;
			cout << "Final: " << curS->score.finalterm<<endl;
			cout << "Toatal:" << curS->score.total<<endl;
			deletescoreincourse(headS);
			student* tmp=head;
			for (int j = 0; j < num; j++) {
				head = head->pNext;
				delete tmp;
				tmp = head;
			}
			system("Pause");
			return;
		}
		else {
			cur = cur->pNext;
			curS = curS->pNext;
		}
	}
	cout << "Can't find your score in the course.";
		deletescoreincourse(headS);
		student* tmp = head;
		for (int j = 0; j < num; j++) {
			head = head->pNext;
			delete tmp;
			tmp = head;
		}
		system("pause");
}
