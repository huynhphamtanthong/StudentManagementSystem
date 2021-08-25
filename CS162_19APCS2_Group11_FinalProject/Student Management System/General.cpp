#include "General.h"

void characterfromfile(ifstream& f, char*& arr)
{
	char Tmp[1000];
	f.getline(Tmp, 1000, '\n');
	arr = new char[strlen(Tmp) + 1];
	strcpy_s(arr, strlen(Tmp) + 1, Tmp);
}

void inputcharacter(char*& arr)
{
	char Tmp[1000];
	cin.getline(Tmp, 1000, '\n');
	arr = new char[strlen(Tmp) + 1];
	strcpy_s(arr, strlen(Tmp) + 1, Tmp);
}

void generatePass(char*& arr, int year, int month, int day) {
	char str1[100], str2[100], str3[100], Tmp[100];
	sprintf_s(str1, "%d", year);
	if (month < 10) sprintf_s(str2, "0%d", month);
	else sprintf_s(str2, "%d", month);
	if (day < 10) sprintf_s(str3, "0%d", day);
	else sprintf_s(str3, "%d", day);

	arr = new char[strlen(str1) + strlen(str2) + strlen(str3) + 1];
	strcpy_s(Tmp, 100, str1);
	strcat_s(Tmp, 100, str2);
	strcat_s(Tmp, 100, str3);
	strcpy_s(arr, strlen(Tmp) + 1, Tmp);
}

bool compare(char* ptr1, char* ptr2)
{
	while (*ptr1 == *ptr2)
	{
		if (*ptr1 == '\0' && *ptr2 == '\0')
		{
			return true;
		}
		ptr1++;
		ptr2++;
	}
	return false;
}

bool Login(staff*& Sf, lecturer*& Lt, student*& St, int choice)
{
	int num;
	cin.ignore();
	if (choice == 0) { // staff
		char* input_user, * input_password;
		cout << "Username : ";
		inputcharacter(input_user);
		cout << "Password : ";
		inputcharacter(input_password);
		ifstream in;
		in.open("Staff.txt");
		if (!in.is_open()) {
			cout << "Staff's data is missing." << endl;
			return false;
		}
		else {
			if (Sf != nullptr)return false;
			loadfilestaff(in, Sf, num);
			in.close();
			staff* cur = Sf;
			while (cur != nullptr)
			{
				if (compare(input_user, cur->user) == true && compare(input_password, cur->password) == true)
				{
					staff* tmp = Sf;
					if (cur == tmp)
					{
						staff* moretmp = cur->pNext;
						cur->pNext = nullptr;
						deletestaff(moretmp);
						return true;
					}
					while (tmp->pNext != cur)
					{
						tmp = tmp->pNext;
					}
					tmp->pNext = cur->pNext;
					cur->pNext = nullptr;
					deletestaff(Sf);
					Sf = cur;
					return true;
				}
				else
				{
					cur = cur->pNext;
				}
			}
			return false;
		}
	}
	else if (choice == 1) // lecturer
	{
		char* input_user, * input_password;
		cout << "Username : ";
		inputcharacter(input_user);
		cout << "Password : ";
		inputcharacter(input_password);
		ifstream in;
		in.open("Lecturer.txt");
		if (!in.is_open()) {
			cout << "Lecturer's data is missing." << endl;
			return false;
		}
		else {
			if (Lt != nullptr)return false;
			loadfilelecturer(in, Lt, num);
			in.close();
			lecturer* cur = Lt;
			while (cur != nullptr)
			{
				if (compare(input_user, cur->user) == true && compare(input_password, cur->password) == true)
				{
					lecturer* tmp = Lt;
					if (cur == tmp)
					{
						lecturer* moretmp = cur->pNext;
						cur->pNext = nullptr;
						deletelecturer(moretmp);
						return true;
					}
					while (tmp->pNext != cur)
					{
						tmp = tmp->pNext;
					}
					tmp->pNext = cur->pNext;
					cur->pNext = nullptr;
					deletelecturer(Lt);
					Lt = cur;
					return true;
				}
				else
				{
					cur = cur->pNext;
				}
			}
			return false;
		}
	}
	else if (choice == 2) //student
	{
		char* input_password;
		int StudentID;
		cout << "Your ID : ";
		cin >> StudentID;
		cin.ignore();
		cout << "Password : ";
		inputcharacter(input_password);
		ifstream in;
		in.open("Student.txt");
		if (!in.is_open()) {
			cout << "Student's data is missing." << endl;
			return false;
		}
		else {
			if (St != nullptr)return false;
			loadfilestudent(in, St, num);
			in.close();
			student* cur = St;
			while (cur != nullptr)
			{
				if (StudentID == cur->ID && compare(input_password, cur->password) == true)
				{
					student* tmp = St;
					if (cur == tmp)
					{
						student* moretmp = cur->pNext;
						cur->pNext = nullptr;
						deletestudent(moretmp);
						return true;
					}
					while (tmp->pNext != cur)
					{
						tmp = tmp->pNext;
					}
					tmp->pNext = cur->pNext;
					cur->pNext = nullptr;
					deletestudent(St);
					St = cur;
					return true;
				}
				else
				{
					cur = cur->pNext;
				}
			}
			return false;
		}
	}
}

void convert(char*& arr, string str) {
	arr = new char[strlen(str.c_str()) + 1];
	strcpy_s(arr, strlen(str.c_str()) + 1, str.c_str());
}

void checkExistClass(char* arr)
{
	ifstream in;
	bool check = false;
	int num;
	CLASS* cls = nullptr;
	CLASS* cur = nullptr;
	in.open("Class.txt");
	if (!in.is_open())
	{
		cout << "Class' file is missing." << endl;
	}
	else
	{
		in >> num;
		in.ignore();
		for (int i = 0;i < num;++i)
		{
			if (cls == nullptr)
			{
				cls = new CLASS;
				characterfromfile(in, cls->classname);
				cls->pNext = nullptr;
				cur = cls;
			}
			else
			{
				cur->pNext = new CLASS;
				cur = cur->pNext;
				characterfromfile(in, cur->classname);
				cur->pNext = nullptr;
			}
		}
		cur = nullptr;
	}
	in.close();
	cur = cls;
	while (cur != nullptr)
	{
		if (compare(arr, cur->classname))
		{
			check = true;
			break;
		}
		cur = cur->pNext;
	}
	if (check == false)
	{
		ofstream ofclass;
		ofclass.open("Class.txt");
		if (!ofclass.is_open())
		{
			cout << "Class' file is missing." << endl;
		}
		else
		{
			if (cls == nullptr)
			{
				cls = new CLASS;
				cls->classname = arr;
				cls->pNext = nullptr;
			}
			else
			{
				cur = cls;
				while (cur->pNext != nullptr)
				{
					cur = cur->pNext;
				}
				cur->pNext = new CLASS;
				cur = cur->pNext;
				cur->classname = arr;
				cur->pNext = nullptr;
			}
			num++;
			ofclass << num << endl;
			cur = cls;
			while (cur)
			{
				ofclass << cur->classname << endl;
				cur = cur->pNext;
			}
		}
		ofclass.close();
	}
}

void readCSVscore()
{
	cin.ignore();
	cout << "Please input the class: ";
	char tmpcls[1000];
	cin.getline(tmpcls, 1000, '\n');
	// Get scoreboard
	char clss[100];
	strcpy_s(clss, strlen(tmpcls) + 1, tmpcls);
	// destination 
	char clss1[100];
	strcpy_s(clss1, strlen(tmpcls) + 1, tmpcls);
	
	char clss2[100];
	strcpy_s(clss2, strlen(tmpcls) + 1, tmpcls);

	char id[100];
	student_Sche* head = new student_Sche;
	cout << "Please input course's id: ";
	cin.getline(id, 100, '\n');

	strcat(clss, "-");
	strcat(clss, id);
	strcat(clss, "-Scoreboard.csv");

	int count = 0, tmp = 0;
	string str;
	ifstream ip;
	ofstream out;
	ip.open(clss);
	if (!ip.is_open()) cout << "ERROR: File Open" << '\n';
	while (getline(ip, str)) {
		count++;
	}
	ip.close();

	ip.open(clss);
	if (!ip.is_open()) cout << "ERROR: File Open" << '\n';
	string no, std, name, midterm, finalterm, bonus, total;

	getline(ip, str);
	getline(ip, no, ',');
	getline(ip, std, ',');
	getline(ip, name, ',');
	getline(ip, midterm, ',');
	head->score.midterm = atoi(midterm.c_str()) + getDecimal(midterm.c_str());
	getline(ip, finalterm, ',');
	head->score.finalterm = atoi(finalterm.c_str()) + getDecimal(finalterm.c_str());
	getline(ip, bonus, ',');
	head->score.bonus = atoi(bonus.c_str()) + getDecimal(bonus.c_str());
	getline(ip, total, '\n');
	head->score.total = atoi(total.c_str()) + getDecimal(total.c_str());

	tmp++;
	student_Sche* cur = head;

	while (tmp < count - 1) {
		student_Sche* newNode = new student_Sche;
		newNode->pNext = nullptr;
		cur->pNext = newNode;
		getline(ip, no, ',');
		getline(ip, std, ',');
		getline(ip, name, ',');
		getline(ip, midterm, ',');
		getline(ip, finalterm, ',');
		newNode->score.midterm = atoi(midterm.c_str()) + getDecimal(midterm.c_str());
		newNode->score.finalterm = atoi(finalterm.c_str()) + getDecimal(finalterm.c_str());
		getline(ip, bonus, ',');
		getline(ip, total, '\n');
		newNode->score.bonus = atoi(bonus.c_str()) + getDecimal(bonus.c_str());
		newNode->score.total = atoi(total.c_str()) + getDecimal(total.c_str());
		tmp++;
		cur = cur->pNext;
	}
	ip.close();
	strcat(clss1, "-");
	strcat(clss1, id);
	strcat(clss1, "-score.txt");
	strcat(clss2, "-");
	strcat(clss2, id);
	strcat(clss2, ".txt");
	ip.open(clss2);
	if (!ip.is_open()) {
		cout << "Cannot open file " << clss2 << endl;
		return;
	}
	int num = 0;
	student* St = nullptr;
	loadfilestudentincourse(ip, St, num);
	ip.close();
	out.open(clss1);
	if (!out.is_open()) {
		cout << "Cannot open " << clss1 << endl;
		return;
	}
	savefilescoreincourse(out, head , count-1, St );
	out.close();
	cout << "Import score of clss " << tmpcls <<" in course " << id << " successfully! " << endl;
	deletestudentincourse(St);
	deletescoreincourse(head);
}
float getDecimal(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.') {
			return float(atoi((str.substr(i + 1, str.length() - 1 - i)).c_str())) / pow(10, str.length() - 1 - i);
			break;
		}
	}
	return 0;
}

void changeDate(int& day, int& month, int& year, int& gap) {
	tm t = { 0 };
	t.tm_mday = day;
	t.tm_mon = month - 1;
	t.tm_year = year - 1900;

	t.tm_mday += gap;
	mktime(&t);
	day = t.tm_mday;
	month = t.tm_mon + 1;
	year = t.tm_year + 1900;
}

int findDate(char* str) {
	if (compare(str, (char*)"MON")) return 2;
	else if (compare(str, (char*)"TUE")) return 3;
	else if (compare(str, (char*)"WED")) return 4;
	else if (compare(str, (char*)"THU")) return 5;
	else if (compare(str, (char*)"FRI")) return 6;
	else if (compare(str, (char*)"SAT")) return 7;
	else if (compare(str, (char*)"SUN")) return 8;
}

bool difference(int day, int month, int year, course* cur2) {
	if (year < cur2->end_date.year) 
		return true;
	else if (year == cur2->end_date.year) 
	{
		if (month < cur2->end_date.month) 
			return true;
		else if (month == cur2->end_date.month)
		{
			if (day <= cur2->end_date.day) 
				return true;
		}
	}
	return false;
}
void getTime(int& day, int& mon, int& year, int& hour, int& min) {// head is that log-in student

	time_t now = time(0);
	struct tm ltm;
	localtime_s(&ltm, &now);

	year = 1900 + ltm.tm_year;
	mon = 1 + ltm.tm_mon;
	day = ltm.tm_mday;
	hour = 1 + ltm.tm_hour;
	min = 1 + ltm.tm_min;
}
// 0 : late, 1 : ok, 2: soon
int checkDate(int day, int mon,int year,int hour,int min, date_to_check* cur) {
	if (year == cur->date.year) {
		if (mon == cur->date.month) {
			if (day == cur->date.day) {
				if (compareTime(hour, min, cur) == 1) return 1;
				else if (compareTime(hour, min, cur) == 2) return 2;
				else return 0;
			}
			else if (day < cur->date.day) return 2;
			else return 0;
		}
		else if (mon < cur->date.month) return 2;
		else return 0;
	}
	else if (year < cur->date.year) return 2;
	else return 0;
}
int compareTime(int hour, int min, date_to_check* cur) {
	if (cur->start_hour < hour < cur->end_hour) return 1;
	else if (cur->start_hour == hour) {
		if (cur->start_min <= min) return 1;
		else return 2;
	}
	else if (cur->end_hour == hour) {
		if (cur->end_min >= min) return 1;
		else return 0;
	}
	else if (cur->start_hour > hour) return 2; // soon
	else return 0; // late
}
void create_date_to_check(char tmpcls[], char* id, course* cur2, student* st, int num1) {
	ifstream ip;
	ofstream out;
	
	// below is code for auto creating date served for check-in session
	date_to_check* head3 = nullptr;
	int day = cur2->start_date.day,
		month = cur2->start_date.month,
		year = cur2->start_date.year;
	int gap = 0;
	int numdate = 0;

	date_to_check* cur3 = nullptr;
	while (difference(day, month, year, cur2) == true) {
		for (int i = 0; i < cur2->number; i++) {
			if (head3 == nullptr) {
				head3 = new date_to_check;
				head3->date.day = day;
				head3->date.month = month;
				head3->date.year = year;
				head3->start_hour = cur2->day[i].start_hour;
				head3->start_min = cur2->day[i].start_min;
				head3->end_hour = cur2->day[i].end_hour;
				head3->end_min = cur2->day[i].end_min;
				head3->pNext = nullptr;
				cur3 = head3;
			
			}
			else {
				if (i == 0) {
					gap = 7 - (findDate(cur2->day[i].day) - findDate(cur2->day[0].day));
					changeDate(day, month, year, gap);
				}
				else {
					gap = findDate(cur2->day[i].day) - findDate(cur2->day[i - 1].day);
					changeDate(day, month, year, gap);
				}
				if (difference(day, month, year, cur2) == false)
					break;

				date_to_check* newNode = new date_to_check;
				newNode->pNext = nullptr;
				cur3->pNext = newNode;
				newNode->date.day = day;
				newNode->date.month = month;
				newNode->date.year = year;
				newNode->start_hour = cur2->day[i].start_hour;
				newNode->start_min = cur2->day[i].start_min;
				newNode->end_hour = cur2->day[i].end_hour;
				newNode->end_min = cur2->day[i].end_min;
				
				cur3 = cur3->pNext;
			}
			numdate++;
		}
	}
	cur3 = head3;
	student_Sche* head_st = nullptr;
	student_Sche* cur_st = nullptr;

	date_to_check* cur_date = nullptr;
	for (int i = 0; i < num1; i++) {
		if (head_st == nullptr) {
			head_st = new student_Sche;
			head_st->pNext = nullptr;
			head_st->pHead = nullptr;
			for (int j = 0; j < numdate; j++) {
				if (head_st->pHead == nullptr)
				{
					head_st->pHead = new date_to_check;
					head_st->pHead->date.day = cur3->date.day;
					head_st->pHead->date.month = cur3->date.month;
					head_st->pHead->date.year = cur3->date.year;
					head_st->pHead->start_hour = cur3->start_hour;
					head_st->pHead->start_min = cur3->start_min;
					head_st->pHead->end_hour = cur3->end_hour;
					head_st->pHead->end_min = cur3->end_min;
					head_st->pHead->checkin = cur3->checkin;
					head_st->pHead->pNext = nullptr;
					cur_date = head_st->pHead;
				}
				else {
					date_to_check* newNode = new date_to_check;
					cur_date->pNext = newNode;
					newNode->pNext = nullptr;
					newNode->date.day = cur3->date.day;
					newNode->date.month = cur3->date.month;
					newNode->date.year = cur3->date.year;
					newNode->start_hour = cur3->start_hour;
					newNode->start_min = cur3->start_min;
					newNode->end_hour = cur3->end_hour;
					newNode->end_min = cur3->end_min;
					newNode->checkin = cur3->checkin;
					cur_date = cur_date->pNext;
				}
				cur3 = cur3->pNext;
			}
			cur_st = head_st;
		}
		else {
			student_Sche* Node = new student_Sche;
			Node->pNext = nullptr;
			cur_st->pNext = Node;
			cur_st = cur_st->pNext;
			Node->pHead = nullptr;
			for (int j = 0; j < numdate; j++) {
				if (Node->pHead == nullptr)
				{
					Node->pHead = new date_to_check;
					Node->pHead->date.day = cur3->date.day;
					Node->pHead->date.month = cur3->date.month;
					Node->pHead->date.year = cur3->date.year;
					Node->pHead->start_hour = cur3->start_hour;
					Node->pHead->start_min = cur3->start_min;
					Node->pHead->end_hour = cur3->end_hour;
					Node->pHead->end_min = cur3->end_min;
					Node->pHead->checkin = cur3->checkin;
					Node->pHead->pNext = nullptr;
					cur_date = Node->pHead;
				}
				else {
					date_to_check* newNode = new date_to_check;
					cur_date->pNext = newNode;
					newNode->pNext = nullptr;
					newNode->date.day = cur3->date.day;
					newNode->date.month = cur3->date.month;
					newNode->date.year = cur3->date.year;
					newNode->start_hour = cur3->start_hour;
					newNode->start_min = cur3->start_min;
					newNode->end_hour = cur3->end_hour;
					newNode->end_min = cur3->end_min;
					newNode->checkin = cur3->checkin;
					cur_date = cur_date->pNext;
				}
				cur3 = cur3->pNext;
			}
			cur_st->pNext = Node;
			cur_st = cur_st->pNext;
			cur_st->pNext = nullptr;
		}
		cur3 = head3;
	}

	char clss1[100];
	strcpy_s(clss1, strlen(tmpcls) + 1, tmpcls);
	strcat(clss1, "-");
	strcat(clss1, id);
	strcat(clss1, "-checkin.txt");
	out.open(clss1);
	savefilecheckinincourse(out, head_st, num1, numdate, st);
	out.close();

	deletecheckinincourse(head_st);
	deleteDATE(head3);
}