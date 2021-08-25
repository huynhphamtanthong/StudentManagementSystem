#include "Lecturer.h"

void profileLt(lecturer* Lt) {
	cout << "My profile : " << endl;
	cout << "Username : " << Lt->user << endl;
	cout << "Fullname : " << Lt->fullname << endl;
	cout << "Degree : " << Lt->degree << endl;
	if (Lt->gender == 0)
	{
		cout << "Gender : Male" << endl;
	}
	else
	{
		cout << "Gender : Female" << endl;
	}
	system("pause");
	cout << '\n';
}

void changePassLt(lecturer*& Lt) {
	int check = 1;
	char* old_pass;
	bool changedPass = false;
	cin.ignore();
	do {
		cout << "Pleas input your old password : ";
		inputcharacter(old_pass);
		if (compare(old_pass, Lt->password) == true) changedPass = true;
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
	delete[]Lt->password;
	delete[]old_pass;
	cout << "Please input your new password : ";
	inputcharacter(Lt->password);
	lecturer* newLt = nullptr;
	int total = 0;
	ifstream in;
	in.open("Lecturer.txt");
	if (!in.is_open())
	{
		cout << "Lecturer's data is missing." << endl;
	}
	else
	{
		loadfilelecturer(in, newLt, total);
		in.close();
	}
	lecturer* newcur = newLt;
	while (newcur != nullptr)
	{
		if (compare(newcur->fullname, Lt->fullname))
		{
			delete[]newcur->password;
			newcur->password = Lt->password;
			break;
		}
		newcur = newcur->pNext;
	}
	ofstream out;
	out.open("Lecturer.txt");
	if (!out.is_open())
	{
		cout << "Lecturer's data is missing." << endl;
	}
	else
	{
		savefilelecturer(out, newLt, total);
		out.close();
	}
	cout << "Change password successfully." << endl;
	system("pause");
	cout << endl;
}

void viewCourseforlec(lecturer* Lt)
{
	ifstream in;
	in.open("Course.txt");
	if (!in.is_open()) {
		cout << "Cannot open file. " << endl;
		return;
	}
	course* head = nullptr;
	int num = 0, num1 = 0;
	loadfilecourseinclass(in, head, num);
	in.close();
	course* cur = head;
	while (cur != nullptr) {
		if (compare(cur->ltAccount, Lt->user)) {
			num1++;
		}
		cur = cur->pNext;
	}
	cout << "There are " << num1 << " courses in this semester. " << endl;
		cur = head;
		while (cur != nullptr) {
			if (compare(cur->ltAccount, Lt->user))
				cout << cur->id << " " << cur->name << " " << cur->Class << endl;
			cur = cur->pNext;
		}
		deletecourseinclass(head);
		system("pause");
}

void viewStudentinCourseforlec(lecturer* Lt)
{
	cout << endl;
	ifstream in;
	int num;
	course* crs = nullptr;
	course* cur = nullptr;
	in.open("Course.txt");
	if (!in.is_open())
	{
		cout << "Course file is missing." << endl;
	}
	else
	{
		loadfilecourseinclass(in, crs, num);
	}
	in.close();
	int choice = -1;
	bool check = false;
	while (!check)
	{
		cur = crs;
		num = 1;
		cout << "Please choose the course you'd like to view students : " << endl;
		while (cur != nullptr)
		{
			if (compare(Lt->user, cur->ltAccount)) {
				cout << num << ". " << cur->Class << "-" << cur->id << endl;
			}
			num++;
			cur = cur->pNext;
		}
		cout << "Your choice : ";
		cin >> choice;
		for (int i = 1; i < num; ++i)
		{
			if (choice == i)
			{
				check = true;
				break;
			}
		}
		if (check == false)
		{
			cout << "Your course choice is invalid." << endl;
			cout << "Please input 1 to continue viewing class." << endl;
			cout << "Or input 0 to return no menu." << endl;
			cout << "Your choice : ";
			cin >> choice;
			if (choice == 0) return;
			cout << endl;
		}
	}
	cur = crs;
	for (int i = 1; i < choice; ++i)
	{
		cur = cur->pNext;
	}
	char* Cs = cur->Class;
	char* id = cur->id;
	strcat(Cs, "-");
	strcat(Cs, id);
	strcat(Cs, ".txt");
	in.open(Cs);
	if (!in.is_open())
	{
		cout << "Students' data is missing." << endl;
	}
	else
	{
		int total = 0;
		student* viewpH = nullptr;
		loadfilestudentincourse(in, viewpH, total);
		student* stcur = viewpH;
		cout << endl << "List of students in this course : " << endl;
		while (stcur)
		{
			cout << stcur->ID << endl;
			cout << stcur->fullname << endl;
			if (stcur->gender == 0)
			{
				cout << "Male" << endl;
			}
			else
			{
				cout << "Female." << endl;
			}
			cout << stcur->Dob.year << " ";
			cout << stcur->Dob.month << " ";
			cout << stcur->Dob.day << endl;
			cout << endl;
			stcur = stcur->pNext;
		}
		deletestudentincourse(viewpH);
	}
	in.close();
	system("pause");
}

void editattendance()
{
	cin.ignore();
	char Tmp[1000], courseid[1000];
	cout << "Please input class you'd like to edit : ";
	cin.getline(Tmp, 1000, '\n');
	cout << "Please input course id you'd like to edit : ";
	cin.getline(courseid, 1000, '\n');
	strcat(Tmp, "-");
	strcat(Tmp, courseid);
	strcat(Tmp, "-checkin.txt");

	student* St = nullptr;
	student_Sche* Sc = nullptr;
	int num = 0;
	int numdate = 0;

	ifstream loadcheckin;
	loadcheckin.open(Tmp);
	if (!loadcheckin.is_open())
	{
		cout << "Checkin's file is missing." << endl;
	}
	else
	{
		loadfilecheckinincourse(loadcheckin, Sc, num, numdate, St);
	}
	loadcheckin.close();
	bool again = true;
	while (again == true)
	{
		int ID;
		cout << "Please input the ID of student you'd like to edit : ";
		cin >> ID;

		student* curSt = St;
		student_Sche* curSc = Sc;
		date_to_check* cur = nullptr;

		int check = 0;
		while (curSt != nullptr && curSc != nullptr)
		{
			cur = curSc->pHead;
			if (curSt->ID == ID)
			{
				for (int i = 0;i < numdate;++i)
				{
					cout << i + 1 << ". " << cur->date.year << " " << cur->date.month << " " << cur->date.day
						<< " " << cur->start_hour << "h" << cur->start_min << "-" << cur->end_hour << "h" << cur->end_min << " ";
					if (cur->checkin == 1)
					{
						cout << "Present" << endl;
					}
					else
					{
						cout << "Absent" << endl;
					}
					cur = cur->pNext;
				}
				check++;
				break;
			}
			curSt = curSt->pNext;
			curSc = curSc->pNext;
		}
		if (check == 0)
		{
			cout << "Your inputted ID is invalid. Please try another one." << endl
				<< "Or input 0 to exit." << endl
				<< "Your choice : ";
			cin >> ID;
			if (ID == 0)
			{
				return;
			}
			else
			{
				continue;
			}
		}
		bool more = true;
		while (more == true)
		{
			cout << "Please input the check-in of any dates you'd like to edit : ";
			int choice;
			cin >> choice;
			cout << endl;
			while (choice <= 0 && choice > numdate)
			{
				cout << "Invalid option. Please try again." << endl;
				cout << "Please input the check-in of any dates you'd like to edit (Change absent to present or vice versa) : " << endl;
				cout << "Or input 0 to return to main menu." << endl;
				cout << "Your choice : ";
				cin >> choice;
				if (choice == 0)
					return;
			}

			cur = curSc->pHead;
			for (int i = 1;i < choice;++i)
			{
				cur = cur->pNext;
			}

			if (cur->checkin == -1)
			{
				cur->checkin = 1;
			}
			else
			{
				cur->checkin = -1;
			}
			cout << "Please choose the following options : " << endl
				<< "1. If you want to edit any other check-in dates of this student." << endl
				<< "2. If you want to edit another student's check-in dates." << endl
				<< "3. Return to main menu." << endl
				<< "Your choice : ";
			int ch;
			cin >> ch;
			cout << endl;
			while (ch < 1 && ch>3)
			{
				cout << "Invalid option. Please try another one." << endl
					<< "Please choose the following options : " << endl
					<< "1. If you want to edit any other check-in dates of this student." << endl
					<< "2. If you want to edit another student's check-in dates." << endl
					<< "3. Return to main menu." << endl
					<< "Your choice : ";
				cin >> ch;
				cout << endl;
			}
			if (ch == 1)
			{
				more = true;
			}
			else if (ch == 2)
			{
				more = false;
				again = true;
			}
			else
			{
				more = false;
				again = false;
			}
		}
	}
	ofstream savecheckin;
	savecheckin.open(Tmp);
	if (!savecheckin.is_open())
	{
		cout << "Check-in's file is missing." << endl;
	}
	else
	{
		savefilecheckinincourse(savecheckin, Sc, num, numdate, St);
	}
	savecheckin.close();
	deletecheckinincourse(Sc);
	deleteIDincourse(St);
	cout << "Edit successfully." << endl;
}

void viewscoreboard()
{
	cin.ignore();
	char Tmp[1000];
	cout << "Please input class : ";
	cin.getline(Tmp, 1000, '\n');
	char* cls = nullptr;
	cls = new char[strlen(Tmp) + 1];
	strcpy_s(cls, strlen(Tmp) + 1, Tmp);

	char* curcls = nullptr;
	curcls = new char[strlen(Tmp) + 1];
	strcpy_s(curcls, strlen(Tmp) + 1, Tmp);

	cout << "Please input course : ";
	cin.getline(Tmp, 1000, '\n');
	char* id = nullptr;
	id = new char[strlen(Tmp) + 1];
	strcpy_s(id, strlen(Tmp) + 1, Tmp);

	strcat(cls, "-");
	strcat(cls, id);
	strcat(cls, "-score.txt");

	student* St = nullptr;
	student_Sche* Sc = nullptr;
	int num;

	ifstream loadscore;
	loadscore.open(cls);
	if (!loadscore.is_open())
	{
		cout << "Score's file is missing." << endl;
		return;
	}
	else
	{
		loadfilescoreincourse(loadscore, Sc, num, St);
	}
	loadscore.close();

	student* curSt = St;
	student_Sche* curSc = Sc;
	cout << endl;
	cout << "Scoreboard in course " << id << " of class " << curcls << " : " << endl;
	for (int i = 0;i < num;++i)
	{
		cout << "ID : " << curSt->ID << endl;
		cout << "Midterm : " << curSc->score.midterm << endl;
		cout << "Final : " << curSc->score.finalterm << endl;
		cout << "Bonus : " << curSc->score.bonus << endl;
		cout << "Total : " << curSc->score.total << endl;
		cout << endl;
		curSt = curSt->pNext;
		curSc = curSc->pNext;
	}
	deletescoreincourse(Sc);
	deleteIDincourse(St);
	system("pause");
}
void editGrade() {
	ifstream ip;
	ofstream op;
	bool checkf = true;
	do {
		cin.ignore();
		int std_id;
		char clss[100], id[100];
		cout << "Please input student's ID you want to edit : ";
		cin >> std_id;
		cin.ignore();
		cout << "Please input class this student joins : ";
		cin.getline(clss, 100, '\n');
		cout << "Please input course id : ";
		cin.getline(id, 100, '\n');

		strcat_s(clss, "-");
		strcat_s(clss, id);
		strcat_s(clss, "-score.txt");

		student_Sche* St = nullptr;
		int num = 0;
		student* st = nullptr;

		ip.open(clss);
		if (!ip.is_open()) {
			cout << "Cannot open file " << clss << endl;
			return;
		}
		else {
			loadfilescoreincourse(ip, St, num, st);
			ip.close();
		}

		student* cur_st = st;
		student_Sche* cur_St = St;
		while (cur_st != nullptr) {
			if (cur_st->ID == std_id) break;
			else {
				cur_st = cur_st->pNext;
				cur_St = cur_St->pNext;
			}
		}
		if (cur_st == nullptr) {
			cout << "This student is not already in course. Please re-check again before editing grade " << endl;
		}
		else{
		bool check_edit = true;
		do {
			int edit;
			cout << "Which grade you want to edit ? " << endl;
			cout << "1. Midterm " << cur_St->score.midterm << endl;
			cout << "2. Finalterm " << cur_St->score.finalterm << endl;
			cout << "3. Bonus " << cur_St->score.bonus << endl;
			cout << "4. Total " << cur_St->score.total << endl;
			cout << "Your choice = ";
			cin >> edit;
			while (edit != 1 && edit != 2 && edit != 3 && edit != 4 && edit != 5) {
				cout << "Wrong choice. Input again : ";
				cin >> edit;
			}
			if (edit == 1) {
				cout << "You choose to edit midterm score" << endl;
				cout << "Input new score = ";
				cin >> cur_St->score.midterm;
				cout << "DONE!" << endl;
			}
			else if (edit == 2) {
				cout << "You choose to edit finalterm score" << endl;
				cout << "Input new score = ";
				cin >> cur_St->score.finalterm;
				cout << "DONE!" << endl;
			}
			else if (edit == 3) {
				cout << "You choose to edit bonus score" << endl;
				cout << "Input new score = ";
				cin >> cur_St->score.bonus;
				cout << "DONE!" << endl;
			}
			else if (edit == 4) {
				cout << "You choose to edit total score" << endl;
				cout << "Input new score = ";
				cin >> cur_St->score.total;
				cout << "DONE!" << endl;
			}
			int ask;
			cout << "Do you want to edit other score ? (press any button = YES, 0 = NO) ";
			cin >> ask;
			if (ask == 0) {

				op.open(clss);
				savefilescoreincourse(op, St, num, st);
				op.close();
				check_edit = false;

				deletescoreincourse(St);
				deleteIDincourse(st);
			}
		} while (check_edit == true);
	    }
		int checktodo;
		cout << "Do you want to edit grade of another student ? ( 1: YES , 0: NO) ";
		cin >> checktodo;
		while (checktodo != 1 && checktodo != 0) {
			cout << "Wrong choice. Please input again !!!" << endl;
			cout << "Do you want to edit grade of another student ? ( 1: YES , 0: NO) ";
			cin >> checktodo;
		}
		if (checktodo == 0) {
			checkf = false;
		}
	} while (checkf == true);
	cout << "Edit successfully." << endl;
	system("pause");
}