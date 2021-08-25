#include "Staff.h"

void profileSf(staff* Sf) {
	cout << "My profile : " << endl;
	cout << "Username : " << Sf->user << endl;
	cout << "Fullname : " << Sf->fullname << endl;
	if (Sf->gender == 0)
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

void changePassSf(staff*& Sf) {
	int check = 1;
	char* old_pass;
	bool changedPass = false;
	cin.ignore();
	do {
		cout << "Pleas input your old password : ";
		inputcharacter(old_pass);
		if (compare(old_pass, Sf->password) == true) changedPass = true;
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
	delete[]Sf->password;
	delete[]old_pass;
	Sf->password = nullptr;
	cout << "Please input your new password : ";
	inputcharacter(Sf->password);
	staff* newSf = nullptr;
	int total = 0;
	ifstream in;
	in.open("Staff.txt");
	if (!in.is_open())
	{
		cout << "Staff's data is missing." << endl;
	}
	else
	{
		loadfilestaff(in, newSf, total);
		in.close();
	}
	staff* newcur = newSf;
	while (newcur != nullptr)
	{
		if (compare(newcur->fullname, Sf->fullname))
		{
			delete[]newcur->password;
			newcur->password = Sf->password;
			break;
		}
		newcur = newcur->pNext;
	}
	ofstream out;
	out.open("Staff.txt");
	if (!out.is_open())
	{
		cout << "Staff's data is missing." << endl;
	}
	else
	{
		savefilestaff(out, newSf, total);
		out.close();
	}
	cout << "Change password successfully." << endl;
	system("pause");
	cout << endl;
}

void readCSVSt() {
	char tmpcls[1000];

	student* head = nullptr;
	cin.ignore();
	cout << "Please input the class: ";
	cin.getline(tmpcls, 1000, '\n');

	checkExistClass(tmpcls);

	char* clss = nullptr;
	clss = new char[strlen(tmpcls) + 1];
	strcpy_s(clss, strlen(tmpcls) + 1, tmpcls);
	strcat(tmpcls, "-student.csv");
	
	int count = 0, tmp = 0;
	string str;
	ifstream ip;
	ip.open(tmpcls);
	if (!ip.is_open()) cout << "ERROR: File Open" << '\n';
	while (getline(ip, str)) {
		count++;
	}
	ip.close();

	ip.open(tmpcls);
	if (!ip.is_open()) cout << "ERROR: File Open" << '\n';
	string id, gender, year, month, day, password, name, no;
	
	getline(ip, str);
	head = new student;
	getline(ip, no, ',');
	getline(ip, id, ',');
	head->ID = atoi(id.c_str());
	getline(ip, password, ',');
	convert(head->password, password);
	getline(ip, name, ',');
	convert(head->fullname, name);

	getline(ip, gender, ',');
	head->gender = atoi(gender.c_str());
	getline(ip, year, ',');
	head->Dob.year = atoi(year.c_str());
	getline(ip, month, ',');
	head->Dob.month = atoi(month.c_str());
	getline(ip, day, '\n');
	head->Dob.day = atoi(day.c_str());
	head->Class = clss;
	tmp++;
	student* cur = head;

	while (tmp < count - 1) {
		student* newNode = new student;
		newNode->pNext = nullptr;
		cur->pNext = newNode;
		getline(ip, no, ',');
		getline(ip, id, ',');
		newNode->ID = atoi(id.c_str());

		getline(ip, password, ',');
		convert(newNode->password, password);

		getline(ip, name, ',');
		convert(newNode->fullname, name);

		getline(ip, gender, ',');
		newNode->gender = atoi(gender.c_str());

		getline(ip, year, ',');
		newNode->Dob.year = atoi(year.c_str());

		getline(ip, month, ',');
		newNode->Dob.month = atoi(month.c_str());

		getline(ip, day, '\n');
		newNode->Dob.day = atoi(day.c_str());
		newNode->Class = clss;
		tmp++;
		cur = cur->pNext;
	}
	cur = nullptr;
	ip.close();
	ofstream out;
	student* head1 = nullptr, *tmp1 = nullptr;
	ip.open("Student.txt");
	if (!ip.is_open()) {
		cout << "Student.txt is not exist";
	}
	else {
		int num;
		loadfilestudent(ip, head1, num);
		ip.close();
		
		if (head1 == nullptr) {
			head1 = head;
			num += count - 1;
		}
		else {
			tmp1 = head1;
			while (tmp1->pNext != nullptr) tmp1 = tmp1->pNext;
			tmp1->pNext = head;
			num += count-1;
		}
		out.open("Student.txt");
		savefilestudent(out, head1, num);
		out.close();
		strcat(clss, "-student.txt");
		out.open(clss);
		savefilestudentinclass(out, head, count - 1);
		out.close();
	}
	deletestudentinclass(head);
	tmp1->pNext = nullptr;
	deletestudent(head1);
}

void addStudent() {
	cin.ignore();
	student* head = nullptr;
	ifstream load;
	load.open("Student.txt");
	if (!load.is_open())
	{
		cout << "Student's data is missing." << endl;
		return;
	}
	int num;
	loadfilestudent(load, head, num);
	load.close();
	student* tmp = head;
	while (tmp->pNext != nullptr) tmp = tmp->pNext;
	char* clss, * fullname, * password;
	int id, year, month, day, gen;

	student* newStudent = new student;
	cout << "Please input class : ";
	inputcharacter(clss);
	cout << "Please input name : ";
	inputcharacter(fullname);
	cout << "Please input student ID : ";
	cin >> id;
	cout << "Please input date of birth : ";
	cin >> year >> month >> day;
	cout << "Please input gender (0: Male, 1: Female) : ";
	cin >> gen;
	generatePass(password, year, month, day);
	newStudent->Class = new char[strlen(clss) + 1];
	strcpy_s(newStudent->Class, strlen(clss) + 1, clss);
	newStudent->fullname = new char[strlen(fullname) + 1];
	strcpy_s(newStudent->fullname, strlen(fullname) + 1, fullname);
	newStudent->Dob.day = day;
	newStudent->Dob.month = month;
	newStudent->Dob.year = year;
	newStudent->ID = id;
	newStudent->gender = gen;
	newStudent->password = new char[strlen(password) + 1];
	strcpy_s(newStudent->password, strlen(password) + 1, password);
	cout << "\nStudent's account is created based on ID and Date of Birth !";
	tmp->pNext = newStudent;
	newStudent->pNext = nullptr;
	tmp = nullptr;
	newStudent = nullptr;
	ofstream save;
	save.open("Student.txt");
	savefilestudent(save, head, num + 1);
	save.close();
	deletestudent(head);

	head = nullptr;
	strcat(clss, "-student.txt");
	load.open(clss);
	if (!load.is_open())
	{
		cout << "Class' student's data is missing." << endl;
		return;
	}
	num = 0;
	loadfilestudentinclass(load, head, num);
	load.close();
	tmp = head;
	while (tmp->pNext != nullptr) tmp = tmp->pNext;

	newStudent = new student;
	newStudent->fullname = new char[strlen(fullname) + 1];
	strcpy_s(newStudent->fullname, strlen(fullname) + 1, fullname);
	newStudent->Dob.day = day;
	newStudent->Dob.month = month;
	newStudent->Dob.year = year;
	newStudent->ID = id;
	newStudent->gender = gen;
	newStudent->password = new char[strlen(password) + 1];
	strcpy_s(newStudent->password, strlen(password) + 1, password);
	tmp->pNext = newStudent;
	newStudent->pNext = nullptr;
	tmp = nullptr;
	newStudent = nullptr;
	save.open(clss);
	savefilestudentinclass(save, head, num + 1);
	save.close();
	deletestudentinclass(head);
}

void editStudent() {
	int id_edit;
	cout << "Choose student's ID you want to edit : ";
	cin >> id_edit;
	student* head = nullptr, * head1 = nullptr;
	ifstream in, in1;
	in.open("Student.txt");
	if (!in.is_open()) {
		cout << "Student's data does not exist.";
		return;
	}
	int num = 0;
	loadfilestudent(in, head, num);
	student* cur = head;
	while (cur != nullptr) {
		if (cur->ID == id_edit) break;
		else cur = cur->pNext;
	}
	char clss[100];
	strcpy(clss, cur->Class);
	in.close();
	strcat(clss, "-student.txt");
	in1.open(clss);
	if (!in1.is_open()) {
		cout << "Student's data does not exist.";
		return;
	}
	int num1 = 0;
	loadfilestudentinclass(in1, head1, num1);
	student* cur1 = head1;
	in1.close();
	while (cur1 != nullptr) {
		if (cur1->ID == id_edit) break;
		else cur1 = cur1->pNext;
	}
	bool enter = true;
	while (enter) {
		cout << "You have chosen student " << cur->fullname << " with " << cur->ID << endl;
		cout << "1. Edit student ID " << endl;
		cout << "2. Edit Fullname " << endl;
		cout << "3. Edit gender " << endl;
		cout << "4. Edit password " << endl;
		cout << "5. Edit date of birth " << endl;
		cout << "0. Exit the edit." << endl;
		int select;
		cout << "Option : ";
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "Student ID : ";
			cin >> cur->ID;
			cur1->ID = cur->ID;
			cout << "Edit successfully." << endl;
			break;
		case 2:
			cout << "Fullname : ";
			cin.ignore();
			inputcharacter(cur->fullname);
			char name[100];
			strcpy(name, cur->fullname);
			strcpy((char*)cur1->fullname, name);
			cout << "Edit successfully." << endl;
			break;
		case 3:
			cout << "Gender : ";
			cin >> cur->gender;
			cout << "Edit successfully." << endl;
			break;
		case 4:
			cout << "Password : ";
			cin.ignore();
			inputcharacter(cur->password);
			strcpy((char*)cur1->password, cur->password);
			cout << "Edit successfully." << endl;
			break;
		case 5:
			cout << "Date of birth (year, month, day respectively) : ";
			cin >> cur->Dob.year >> cur->Dob.month >> cur->Dob.day;
			cur1->Dob.year = cur->Dob.year;
			cur1->Dob.month = cur->Dob.month;
			cur1->Dob.day = cur->Dob.day;
			generatePass(cur1->password, cur1->Dob.year, cur1->Dob.month, cur1->Dob.day);
			cout << "Edit successfully." << endl;
			break;
		case 0:
			enter = false;
			cout << "You choose to exit edit program and be back to MENU." << '\n';
			break;
		}
		ofstream out, out1;
		out.open("Student.txt");
		savefilestudent(out, head, num);
		out.close();
		out1.open(clss);
		savefilestudentinclass(out1, head1, num1);
		out.close();
	}
	system("pause");
}

void removeStudent() {
	int input_remove;
	student* head = nullptr;
	ifstream in;
	ofstream out;
	in.open("Student.txt");
	if (!in.is_open()) {
		cout << "Student's data is missing";
		return;
	}
	int num = 0;
	loadfilestudent(in, head, num);
	in.close();

	student* cur1 = nullptr;
	student* temp = nullptr;

	bool check = true;
	while (check == true)
	{
		cout << "Input student's ID to be removed : ";
		cin >> input_remove;
		cur1 = head;
		temp = nullptr;
		int checkstd = 0;
		if (cur1->ID == input_remove) {
			temp = cur1;
			head = head->pNext;
			checkstd = 1;
		}
		else {
			while (cur1->pNext != nullptr) {
				if (cur1->pNext->ID == input_remove) {
					checkstd = 1;
					break;
				}
				else cur1 = cur1->pNext;
			}
			temp = cur1->pNext;
			cur1->pNext = cur1->pNext->pNext;
		}
		if (checkstd == 0)
		{
			cout << "No student's ID in this class is suitable your input ID." << endl;
			cout << "Please input 1 to input another ID." << endl;
			cout << "Or input 0 to return to main menu." << endl;
			cout << "Your choice : ";
			int choice;
			cin >> choice;
			while (choice != 0 && choice != 1)
			{
				cout << "Invalid option. Please try again." << endl;
				cout << "Please input 1 to input another ID." << endl;
				cout << "Or input 0 to return to main menu." << endl;
				cout << "Your choice : ";
				cin >> choice;
			}
			if (choice == 1)
			{
				continue;
			}
			else if (choice == 0)
			{
				deletestudent(head);
				return;
			}
		}
		check = false;
	}
	char clss[100];
	strcpy(clss, temp->Class);
	delete[] temp->fullname;
	delete[] temp->password;
	delete[] temp->Class;
	delete temp;
	num -= 1;
	out.open("Student.txt");
	savefilestudent(out, head, num);
	out.close();
	deletestudent(head);
	strcat(clss, "-student.txt");
	in.open(clss);
	if (!in.is_open()) {
		cout << "Class Student's data is missing";
		return;
	}
	num = 0;
	loadfilestudentinclass(in, head, num);
	in.close();
	cur1 = head;
	temp;
	if (cur1->ID == input_remove) {
		temp = cur1;
		head = head->pNext;
	}
	else {
		while (cur1->pNext != nullptr) {
			if (cur1->pNext->ID == input_remove) {
				break;
			}
			else cur1 = cur1->pNext;
		}
		temp = cur1->pNext;
		cur1->pNext = cur1->pNext->pNext;
	}
	delete[] temp->fullname;
	delete[] temp->password;
	delete temp;
	num -= 1;
	out.open(clss);
	savefilestudentinclass(out, head, num);
	out.close();
	deletestudentinclass(head);
	cout << "Remove successfully." << endl;
	system("pause");
}

void changeClass() {
	bool again = 1;
	bool exist = true;
	while (again) {
		student* head1 = nullptr, * head2 = nullptr, * head = nullptr;
		cout << "Input student's ID you want to move : ";
		int input_move;
		char oldclss[100], * newclss;
		cin >> input_move;
		cout << "Input the class you want the student to move to: ";
		cin.ignore();
		inputcharacter(newclss);
		checkExistClass(newclss);
		ifstream in;
		ofstream out,out1,out2;
		in.open("Student.txt");
		if (!in.is_open()) {
			cout << "Student data file is not exist";
			return;
		}
		int num = 0;
		loadfilestudent(in, head, num);
		in.close();
		student* cur = head;
		bool chck;
		while (cur != nullptr) {
			if (cur->ID == input_move) {
				chck = 1;
				break;
			}
			cur = cur->pNext;
			chck = 0;
		}
		if (!chck) {
			int back;
			cout << "No students' ID in this class fit your inputted ID." << endl
				<< "Please input 1 if you'd like to commit another change." << endl
				<< "Else input 0 to return to main menu." << endl
				<< "Your choice : ";
			cin >> back;
			while (back != 1 && back != 0)
			{
				cout << "No suitable options. Please try again : ";
				cin >> back;
			}
			if (back == 1)
				continue;
			else
			{
				return;
			}
		}
		if (compare(cur->Class, newclss))
		{
			cout << "The student is already in this class." << endl;
			system("pause");
			return;
		}
		strcpy(oldclss, cur->Class);
		strcpy(cur->Class, newclss);
		out.open("Student.txt");
		savefilestudent(out, head, num);
		strcat(oldclss, "-student.txt");
		strcat(newclss, "-student.txt");
		in.open(oldclss);
		if (!in.is_open()) {
			cout << oldclss << " does not exist";
			return;
		}
		int num1 = 0;
		loadfilestudentinclass(in, head1, num1);
		in.close();
		in.open(newclss);
		if (!in.is_open()) {
			cout << newclss << " does not exist";
			return;
		}
		int num2 = 0;
		loadfilestudentinclass(in, head2, num2);
		in.close();
		student* cur2 = head2, * cur1;
		student* tmp;
		while (cur2->pNext != nullptr) cur2 = cur2->pNext;
		if (head1->ID == input_move) {
			tmp = head1;
			head1 = head1->pNext;
			tmp->pNext = nullptr;
			cur2->pNext = tmp;
		}
		else {
			cur1 = head1;
			while (cur1->pNext != nullptr) {
				if (cur1->pNext->ID == input_move) break;
				else cur1 = cur1->pNext;
			}
			tmp = cur1->pNext;
			cur1->pNext = cur1->pNext->pNext;
			tmp->pNext = nullptr;
			cur2->pNext = tmp;
		}
		num1 -= 1;
		num2 += 1;
		out2.open(newclss);
		savefilestudentinclass(out2, head2, num2);
		out2.close();
		out1.open(oldclss);
		savefilestudentinclass(out1, head1, num1);
		out1.close();
		cout << "Do you want to commit another change (1-Yes, 0-No) ?";
		cin >> again;
	}
}

void viewClass()
{
	ifstream view;
	view.open("Class.txt");
	if (!view.is_open())
	{
		cout << "Class' file is missing." << endl;
	}
	else
	{
		int num;
		view >> num;
		view.ignore();
		cout << endl << "There are " << num << " classes in this year : " << endl;
		for (int i = 0;i < num;++i)
		{
			char* classname;
			characterfromfile(view, classname);
			cout << classname << endl;
		}
	}
	view.close();
	system("pause");
}

void viewStudentsInAClass() { 
	cout << endl;
	ifstream in;
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
	int choice = -1;
	bool check = false;
	while (!check)
	{
		cur = cls;
		num = 1;
		cout << "Please choose the class you'd like to view students : " << endl;
		while (cur)
		{
			cout << num << ". " << cur->classname << endl;
			num++;
			cur = cur->pNext;
		}
		cout << "Your choice : ";
		cin >> choice;
		for (int i = 1;i < num;++i)
		{
			if (choice == i)
			{
				check = true;
				break;
			}
		}
		if (check == false)
		{
			cout << "Your class choice is invalid." << endl;
			cout << "Please input 1 to continue viewing class." << endl;
			cout << "Or input 0 to return no menu." << endl;
			cout << "Your choice : ";
			cin >> choice;
			if (choice == 0) return;
			cout << endl;
		}
	}
	cur = cls;
	for (int i = 1; i < choice;++i)
	{
		cur = cur->pNext;
	}
	char* Cs = cur->classname;
	strcat(Cs, "-student.txt");
	ifstream inview;
	inview.open(Cs);
	if (!inview.is_open())
	{
		cout << "Students' data is missing." << endl;
	}
	else
	{
		int total = 0;
		student* viewpH = nullptr;
		loadfilestudentinclass(inview, viewpH, total);
		student* stcur = viewpH;
		cout << endl << "List of students in this class : " << endl;
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
		deletestudentinclass(viewpH);
	}
	inview.close();
	system("pause");
}

void academicyear()
{
	cout << endl;
	char* recyear = nullptr;
	char* recseason = nullptr;
	ifstream sem;
	sem.open("Semester.txt");
	if (!sem.is_open())
	{
		cout << "Semester's file is missing." << endl;
	}
	else
	{
		characterfromfile(sem, recyear);
		characterfromfile(sem, recseason);
	}
	sem.close();
	cout << "Please select one of the following options : " << endl
		<< "1. Create" << endl
		<< "2. Update" << endl
		<< "3. Delete" << endl
		<< "4. View" << endl
		<< "5. Return to menu." << endl;
	int choice;
	cout << "Your choice : ";
	cin >> choice;
	while (choice < 1 || choice > 5)
	{
		cout << "Your inputted number is invalid. Please try another one : ";
		cin >> choice;
	}
	if (choice == 4)
	{
		cout << "Academic year : " << recyear << endl;
		cout << "Season : " << recseason << endl;
	}
	else if (choice == 5)
	{
		return;
	}
	else
	{
		ofstream out;
		out.open("Semester.txt");
		if (!out.is_open())
		{
			cout << "Semester's file is missing." << endl;
		}
		else
		{
			if (choice == 3)
			{
				out << "";
			}
			else 
			{
				char* year;
				char* season;
				cin.ignore();
				cout << "Please input the recent academic year : ";
				inputcharacter(year);
				cout << "Please input the recent season : ";
				inputcharacter(season);
				out << year << endl;
				out << season << endl;
			}
		}
		out.close();
	}
	system("pause");
}

void getStr(char*& arr, string str)
{
	char Tmp[1000];
	int i = 0;
	while (str[i] != ',') {
		Tmp[i] = str[i];
		i++;
	}
	Tmp[i] = '\0';
	arr = new char[i + 1];
	strcpy_s(arr, i + 1, Tmp);
}

void readCourseCSV()
{
	string file;

	char tmpcls[1000];
	course* head = nullptr;
	student* head1 = nullptr;
	int num = 0;
	cin.ignore();
	cout << "Please input the class: ";
	cin.getline(tmpcls, 1000, '\n');

	char* clss = nullptr;
	clss = new char[strlen(tmpcls) + 1];
	strcpy_s(clss, strlen(tmpcls) + 1, tmpcls);
	checkExistClass(clss);

	char* clss1 = nullptr;
	clss1 = new char[strlen(tmpcls) + 1];
	strcpy_s(clss1, strlen(tmpcls) + 1, tmpcls);
	
	cout << "Please input the link of csv file: ";
	getline(cin, file, '\n');

	int count = 0, tmp = 0;
	string str;
	ifstream ip;
	ofstream out;
	strcat(clss1 , "-student.txt");
	ip.open(clss1);
	if (!ip.is_open()) {
		cout << "Cannot open " << clss1 << endl;
	}
	loadfilestudentinclass(ip, head1 , num);
	ip.close();

	ip.open(file);
	if (!ip.is_open()) {
		cout << "ERROR: File Open" << '\n';
		return;
	}
	while (getline(ip, str)) {
		count++;
	}
	ip.close();

	ip.open(file);
	if (!ip.is_open()) {
		cout << "ERROR: File Open" << '\n';
		return;
	}
	string no, id, name, Class, lec, lec_name, degree, gender, 
		start_m, start_d, start_y, end_m, end_d, end_y, day_1, room_1, start_h_1, end_h_1, start_m_1, end_m_1, number;

	getline(ip, str);
	head = new course;
	getline(ip, no, ',');
	head->no = atoi(no.c_str());
	getline(ip, id, ',');
	convert(head->id, id);
	getline(ip, name, ',');
	convert(head->name, name);
	getline(ip, Class, ',');
	convert(head->Class, Class);
	getline(ip, lec, ',');
	convert(head->ltAccount, lec);
	getline(ip, lec_name, ',');
	convert(head->ltName, lec_name);
	getline(ip, degree, ',');
	convert(head->degree, degree);
	getline(ip, gender , ',');
	if (gender == "Female") {
		head->gender = 1;
	}
	else if  (gender == "Male"){
		head->gender = 0;
	}
	getline(ip, start_m, '/');
	head->start_date.month = atoi(start_m.c_str());
	getline(ip, start_d, '/');
	head->start_date.day = atoi(start_d.c_str());
	getline(ip, start_y, ',');
	head->start_date.year = atoi(start_y.c_str());
	getline(ip, end_m, '/');
	head->end_date.month = atoi(end_m.c_str());
	getline(ip, end_d, '/');
	head->end_date.day = atoi(end_d.c_str());
	getline(ip, end_y, ',');
	head->end_date.year = atoi(end_y.c_str());
	getline(ip, number, ',');
	head->number = atoi(number.c_str());

	for (int i = 0; i < head->number; i++) {
		getline(ip, day_1, ',');
		convert(head->day[i].day, day_1);
		getline(ip, start_h_1, ',');
		head->day[i].start_hour = atoi(start_h_1.c_str());
		getline(ip, start_m_1, ',');
		head->day[i].start_min = atoi(start_m_1.c_str());
		getline(ip, end_h_1, ',');
		head->day[i].end_hour = atoi(end_h_1.c_str());
		getline(ip, end_m_1, ',');
		head->day[i].end_min = atoi(end_m_1.c_str());
		if (i == head->number - 1) {
			getline(ip, room_1, '\n');
			if (room_1[room_1.length() - 1] == ',') {
				getStr(head->day[i].room, room_1);
			}
			else {
				convert(head->day[i].room, room_1);
			}
		}
		else {
			getline(ip, room_1, ',');
			convert(head->day[i].room, room_1);
		}
	}
	tmp++;
	course* cur = head;
	
	while (tmp < count - 1) {
		course* newNode = new course;
		newNode->pNext = nullptr;
		cur->pNext = newNode;
		getline(ip, no, ',');
		newNode->no = atoi(no.c_str());
		getline(ip, id, ',');
		convert(newNode->id, id);
		getline(ip, name, ',');
		convert(newNode->name, name);
		getline(ip, Class, ',');
		convert(newNode->Class, Class);
		getline(ip, lec, ',');
		convert(newNode->ltAccount, lec);
		getline(ip, lec_name, ',');
		convert(newNode->ltName, lec_name);
		getline(ip, degree, ',');
		convert(newNode->degree, degree);
		getline(ip, gender, ',');
		if (gender == "Female") {
			newNode->gender = 1;
		}
		else if (gender == "Male") {
			newNode->gender = 0;
		}
		getline(ip, start_m, '/');
		newNode->start_date.month = atoi(start_m.c_str());
		getline(ip, start_d, '/');
		newNode->start_date.day = atoi(start_d.c_str());
		getline(ip, start_y, ',');
		newNode->start_date.year = atoi(start_y.c_str());
		getline(ip, end_m, '/');
		newNode->end_date.month = atoi(end_m.c_str());
		getline(ip, end_d, '/');
		newNode->end_date.day = atoi(end_d.c_str());
		getline(ip, end_y, ',');
		newNode->end_date.year = atoi(end_y.c_str());
		getline(ip, number, ',');
		newNode->number = atoi(number.c_str());

		for (int i = 0; i < newNode->number; i++) {
			getline(ip, day_1, ',');
			convert(newNode->day[i].day, day_1);
			getline(ip, start_h_1, ',');
			newNode->day[i].start_hour = atoi(start_h_1.c_str());
			getline(ip, start_m_1, ',');
			newNode->day[i].start_min = atoi(start_m_1.c_str());
			getline(ip, end_h_1, ',');
			newNode->day[i].end_hour = atoi(end_h_1.c_str());
			getline(ip, end_m_1, ',');
			newNode->day[i].end_min = atoi(end_m_1.c_str());
			if (i == newNode->number - 1) {
				getline(ip, room_1, '\n');
				if (room_1[room_1.length() - 1] == ',') {
					getStr(newNode->day[i].room, room_1);
				}
				else {
					convert(newNode->day[i].room, room_1);
				}
			}
			else {
				getline(ip, room_1, ',');
				convert(newNode->day[i].room, room_1);
			}
		}
		
		tmp++;
		cur = cur->pNext;
	}
	ip.close();
	strcat(clss, "-schedule.txt");
	out.open(clss);
	savefilecourseinclass(out, head, count - 1);
	out.close();

	cur = head;
	char clss2[1000];
	int day, month, year, gap, numdate;
	date_to_check* cur3 = nullptr, * head3 = nullptr;
	while (cur != nullptr) {
	
		clss1 = new char[strlen(tmpcls) + 1];
		strcpy_s(clss1, strlen(tmpcls) + 1, tmpcls);
		strcat(clss1, "-"); 
		strcat(clss1, cur->id);
		strcat(clss1, ".txt");

		out.open(clss1);
		if (!out.is_open()) {
			cout << "Cannot open " << clss1 << endl;
			return;
		}
		savefilestudentincourse(out, head1, num);
		out.close();
		
		head3 = nullptr;
		cur3 = nullptr;
		day = cur->start_date.day,
		month = cur->start_date.month,
		year = cur->start_date.year;
		gap = 0;
		numdate = 0;

		while (difference(day, month, year, cur) == true) {
			for (int i = 0; i < cur->number; i++) {
				if (head3 == nullptr) {
					head3 = new date_to_check;
					head3->date.day = day;
					head3->date.month = month;
					head3->date.year = year;
					head3->start_hour = cur->day[i].start_hour;
					head3->start_min = cur->day[i].start_min;
					head3->end_hour = cur->day[i].end_hour;
					head3->end_min = cur->day[i].end_min;
					head3->pNext = nullptr;
					cur3 = head3;
				}
				else {
					if (i == 0) {
						changeDate(day, month, year, gap);
					}
					else {
						gap = findDate(cur->day[i].day) - findDate(cur->day[i - 1].day);
						changeDate(day, month, year, gap);
					}
					if (difference(day, month, year, cur) == false)
						break;
					date_to_check* newNode = new date_to_check;
					newNode->pNext = nullptr;
					cur3->pNext = newNode;

					newNode->date.day = day;
					newNode->date.month = month;
					newNode->date.year = year;
					newNode->start_hour = cur->day[i].start_hour;
					newNode->start_min = cur->day[i].start_min;
					newNode->end_hour = cur->day[i].end_hour;
					newNode->end_min = cur->day[i].end_min;

					if (i == cur->number - 1) {
						gap = 7 - (findDate(cur->day[i].day) - findDate(cur->day[0].day));
					}
					cur3 = cur3->pNext;
				}
				numdate++;
			}

		}
		cur3 = head3;

		student_Sche* head_st = nullptr;
		student_Sche* cur_st = nullptr;

		date_to_check* cur_date = nullptr;
		for (int i = 0; i < num; i++) {
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
		
		strcpy_s(clss2, strlen(tmpcls) + 1, tmpcls);
		strcat(clss2, "-");
		strcat(clss2, cur->id);
		strcat(clss2, "-checkin.txt");
		out.open(clss2);
		savefilecheckinincourse(out, head_st, num, numdate, head1);
		out.close();

		deletecheckinincourse(head_st);
		deleteDATE(head3);
		// END HERE
		cur = cur->pNext;
	}
	
	course* course_all = nullptr;
	int num1 = 0;
	ip.open("Course.txt");
	loadfilecourseinclass(ip, course_all, num1);
	ip.close();

	course* cur_course = course_all;
	if (course_all == nullptr) course_all = head;
	else {
		while (cur_course->pNext != nullptr) cur_course = cur_course->pNext;
		cur_course->pNext = head;
	}
	out.open("Course.txt");
	savefilecourseinclass(out, course_all, num1 + count - 1 );
	out.close();
	
	cout << "Process has been done! " << endl;

	deletestudentincourse(head1);
	deletecourseinclass(course_all);

	system("pause");
}
void addCourse() {
	cin.ignore();
	course* head = nullptr;
	ifstream load;
	char tmpcls[100];
	cout << "Please input class you want to add course : ";
	cin.getline(tmpcls, 100, '\n');

	char* clss = nullptr;
	clss = new char[strlen(tmpcls) + 1];
	strcpy_s(clss, strlen(tmpcls) + 1, tmpcls);

	strcat(clss,"-schedule.txt");
	load.open(clss);
	if (!load.is_open())
	{
		cout << "Course's data is missing." << endl;
		return;
	}
	int num;
	loadfilecourseinclass(load, head, num);
	load.close();
	course* tmp = head;
	if (head)
	{
		while (tmp->pNext != nullptr) tmp = tmp->pNext;
	}

	char* id, * name, * Class, * lec, * lec_name, * degree, * room_1, * day_1;
	int  gender, start_m, start_d, start_y, end_m, end_d, end_y
		, start_h_1, end_h_1, start_m_1, end_m_1, number;

	course* newCourse = new course;
	
	newCourse->no = num + 1;

	cout << "Please input id : ";
	inputcharacter(id);
	course* cur = head;
	while (cur != nullptr) {
		if (compare(cur->id, id)) {
			cout << "This course already exists. Please check again !" << endl;
			break;
		}
		else {
			cur = cur->pNext;
		}
	}
	if (cur == nullptr) {
		newCourse->id = new char[strlen(id) + 1];
		strcpy_s(newCourse->id, strlen(id) + 1, id);
	}
	else return;

	cout << "Please input name of course : ";
	inputcharacter(name);
	newCourse->name = new char[strlen(name) + 1];
	strcpy_s(newCourse->name, strlen(name) + 1, name);

	cout << "Please input class : ";
	inputcharacter(Class);
	newCourse->Class = new char[strlen(Class) + 1];
	strcpy_s(newCourse->Class, strlen(Class) + 1, Class);

	cout << "Please input lecture nickname : ";
	inputcharacter(lec);
	newCourse->ltAccount = new char[strlen(lec) + 1];
	strcpy_s(newCourse->ltAccount, strlen(lec) + 1, lec);

	cout << "Please input lecture fullname : ";
	inputcharacter(lec_name);
	newCourse->ltName = new char[strlen(lec_name) + 1];
	strcpy_s(newCourse->ltName, strlen(lec_name) + 1, lec_name);

	cout << "Please input degree of lecture : ";
	inputcharacter(degree);
	newCourse->degree = new char[strlen(degree) + 1];
	strcpy_s(newCourse->degree, strlen(degree) + 1, degree);

	cout << "Please input gender (1: Female, 0:Male) : ";
	cin >> gender;
	newCourse->gender = gender;

	cout << "Please input starting month / day / year : ";
	cin >> start_m >> start_d >> start_y;
	newCourse->start_date.day = start_d;
	newCourse->start_date.month = start_m;
	newCourse->start_date.year = start_y;

	cout << "Please input ending month / day / year : ";
	cin >> end_m >> end_d >> end_y;
	newCourse->end_date.day = end_d;
	newCourse->end_date.month = end_m;
	newCourse->end_date.year = end_y;

	cout << "Please input number of period in a week : ";
	cin >> number;
	newCourse->number = number;
	cin.ignore();
	for (int i = 0; i < number; i++) {

		cout << "Day in week : "; 
		inputcharacter(day_1);
		newCourse->day[i].day = new char[strlen(day_1) + 1];
		strcpy_s(newCourse->day[i].day, strlen(day_1) + 1, day_1);

		cout << "Start time : "; 
		cin >> start_h_1 >> start_m_1;
		newCourse->day[i].start_hour = start_h_1;
		newCourse->day[i].start_min = start_m_1;
		cout << "End time : ";
		cin >> end_h_1 >> end_m_1;
		newCourse->day[i].end_hour = end_h_1;
		newCourse->day[i].end_min = end_m_1;
		cin.ignore();

		cout << "Room : ";
		inputcharacter(room_1);
		newCourse->day[i].room = new char[strlen(room_1) + 1];
		strcpy_s(newCourse->day[i].room, strlen(room_1) + 1, room_1);
	}
	if(!head)
	{
		head = newCourse;
	}
	else
	{
		tmp->pNext = newCourse;
	}
	newCourse->pNext = nullptr;

	ofstream save;
	save.open(clss);
	savefilecourseinclass(save, head, num + 1);
	save.close();
	tmp->pNext = nullptr;

	course* head1 = nullptr;
	int num1;
	load.open("Course.txt");
	if (!load.is_open()) cout << "ERROR: File Open" << '\n';
	else {
		loadfilecourseinclass(load, head1, num1);
	}
	load.close();
	tmp = head1;
	while (tmp->pNext != nullptr) tmp = tmp->pNext;
	tmp->pNext = newCourse;
	newCourse->pNext = nullptr;
	tmp = nullptr;
	save.open("Course.txt");
	savefilecourseinclass(save, head1, num1 + 1);
	save.close();

	char* clss1 = nullptr;
	clss1 = new char[strlen(tmpcls) + 1];
	strcpy_s(clss1, strlen(tmpcls) + 1, tmpcls);
	strcat(clss1, "-student.txt");

	student* st = nullptr;
	load.open(clss1);
	loadfilestudentinclass(load, st, num);
	load.close();

	clss1 = new char[strlen(tmpcls) + 1];
	strcpy_s(clss1, strlen(tmpcls) + 1, tmpcls);
	strcat(clss1,"-");
	strcat(clss1, id);
	strcat(clss1, ".txt");
	save.open(clss1);
	savefilestudentincourse(save, st, num);
	save.close();
	
	student_Sche* SCORE = new student_Sche;

	char* clss2;
	clss2 = new char[strlen(tmpcls) + 1];
	strcpy_s(clss2, strlen(tmpcls) + 1, tmpcls);
	strcat(clss2, "-");
	strcat(clss2, id);
	strcat(clss2, "-score.txt");

	save.open(clss2);
	save << num << endl;
	student * CUR = st;
	while (CUR != nullptr) {
		save << CUR->ID << endl;
		save << SCORE->active << endl;
		save << SCORE->score.midterm << endl;
		save << SCORE->score.finalterm << endl;
		save << SCORE->score.bonus << endl;
		save << SCORE->score.total << endl;
		CUR = CUR->pNext;
	}
	save.close();
	create_date_to_check(tmpcls, id, newCourse, st, num);

	deletecourseinclass(head);
	deletecourseinclass(head1);
	deletestudentinclass(st);
}
void editCourse() {
	char* id;
	cout << "Choose course's ID you want to edit : ";
	cin.ignore();
	inputcharacter(id);
	course* head = nullptr, * head1 = nullptr;
	ifstream in;
	ofstream out;
	in.open("Course.txt");
	if (!in.is_open()) {
		cout << "Course's data does not exist.";
		return;
	}
	int num = 0;
	loadfilecourseinclass(in, head, num);
	course* cur = head;
	while (cur != nullptr) {
		if (compare(id, cur->id)) break;
		else cur = cur->pNext;
	}
	in.close();
	char* clss;
	cout << "Input class you want to edit course : ";
	inputcharacter(clss);
	strcat(clss, "-schedule.txt");
	in.open(clss);
	if (!in.is_open()) {
		cout << "Course's data does not exist.";
		return;
	}
	int num1 = 0;
	loadfilecourseinclass(in, head1, num1);
	in.close();
	course* cur1 = head1;
	while (cur1 != nullptr) {
		if (compare(id, cur1->id)) break;
		else cur1 = cur1->pNext;
	}
	bool enter = true;
	while (enter) {
		cout << "You have chosen course " << cur->name << " with " << cur->id << endl;
		cout << "1. Edit course name " << endl;
		cout << "2. Edit lecture username " << endl;
		cout << "3. Edit lecture fullname " << endl;
		cout << "4. Edit lecture degree " << endl;
		cout << "5. Edit lecture gender " << endl;
		cout << "6. Edit information of session " << endl;
		cout << "0. Exit the edit." << endl;
		int select;
		cout << "Option : ";
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "Course name : ";
			cin.ignore();
			//inputcharacter(cur->name);
			char name[100];
			cin.getline(name, 100, '\n');
			strcpy_s(cur->name, strlen(name) + 1, name);
			strcpy_s(cur1->name, strlen(name) + 1, name);
			cout << "Edit successfully." << endl;
			break;

		case 2:
			cout << "Lecturer username : ";
			inputcharacter(cur->ltAccount);
			strcpy((char*)cur1->ltAccount, cur->ltAccount);
			cout << "Edit successfully." << endl;
			break;
		case 3:
			cout << "Lecture fullname : ";
			cin.ignore();
			inputcharacter(cur->ltName);
			strcpy((char*)cur1->ltName, cur->ltName);
			cout << "Edit successfully." << endl;
			break;
		case 4:
			cout << "Lecturer degree : ";
			inputcharacter(cur->degree);
			strcpy((char*)cur1->degree, cur->degree);
			cout << "Edit successfully." << endl;
			break;
		case 5:
			cout << "Gender (1:Female | 0:Male) : ";
			cin >> cur->gender;
			cur1->gender = cur->gender;
			cout << "Edit successfully." << endl;
			break;
		case 0:
			enter = false;
			cout << "You choose to exit edit program and be back to MENU." << '\n';
			break;

		case 6:
			int choice;
			bool edit = true;
			do {
				cout << "1 : Edit all to synchronize" << endl;
				cout << "2 : Edit detail (time to check in)" << endl;
				cout << "0 : Exit" << endl;
				cout << "Your choice : ";
				cin >> choice;
				while (choice != 1 && choice != 2 && choice != 0) {
					cout << "Wrong choice. Please check again" << endl;
					cout << "Your choice : ";
					cin >> choice;
				}
				if (choice == 0) {
					edit = false;
				}
				else if (choice == 1) {
					student_Sche* DATE = nullptr;
					student* st = nullptr;
					int num2 = 0, numdate = 0;
					in.open("19APCS1-CS162-checkin.txt");
					loadfilecheckinincourse(in, DATE, num2, numdate, st);
					in.close();

					student_Sche* cur_date = DATE;
					date_to_check* cur2 = nullptr;

					bool edit_edit = true;
					do {

						cout << "Timetable in a week :" << endl;
						for (int i = 0; i < cur->number; i++) {
							cout << "Press " << i << " : DAY " << i << " : " << endl;
							cout << cur->day[i].day << " " << cur->day[i].start_hour << ":" << cur->day[i].start_min << " " << cur->day[i].end_hour << ":" << cur->day[i].end_min << " " << cur->day[i].room << endl;
						}
						int i;
						cout << "Your choice :";
						cin >> i;
						while (i > cur->number - 1 || i < 0) {
							cout << "Your choice is not included in studying process. Please check again " << endl;
							cout << "Your choice : ";
							cin >> i;
						}
						cout << "You choose to edit day " << i << endl;

						cout << "Start hour / start min of DAY : ";
						cin >> cur->day[i].start_hour >> cur->day[i].start_min;
						cur1->day[i].start_hour = cur->day[i].start_hour;
						cur1->day[i].start_min = cur->day[i].start_min;

						cout << "End hour / end min of DAY : ";
						cin >> cur->day[i].end_hour >> cur->day[i].end_min;
						cur1->day[i].end_hour = cur->day[i].end_hour;
						cur1->day[i].end_min = cur->day[i].end_min;

						cin.ignore();
						cout << "ROOM : ";
						inputcharacter(cur->day[i].room);
						strcpy((char*)cur1->day[i].room, cur->day[i].room);

						int day, mon, year, hour, min;
						getTime(day, mon, year, hour, min);

						while (cur_date != nullptr) {
							cur2 = cur_date->pHead;
							int count = 0;
							while (cur2 != nullptr) {
								if (checkDate(day, mon, year, hour, min, cur2) == 2) break;
								else cur2 = cur2->pNext;
							}
							while ((count - i) % cur->number != 0) {
								count ++;
								cur2 = cur2->pNext;
							}
							while (cur2 != nullptr) {

								cur2->start_hour = cur->day[i].start_hour;
								cur2->start_min = cur->day[i].start_min;
								cur2->end_hour = cur->day[i].end_hour;
								cur2->end_min = cur->day[i].end_min;

								for (int k = 0; k < cur->number; k++) cur2 = cur2->pNext;

							}
							cur_date = cur_date->pNext;
						}

						cur_date = DATE;
						cur2 = nullptr;

						int again;
						cout << "Do you want to edit other days (1: YES, 0: NO) ?";
						cin >> again;
						while (again != 0 && again != 1) {
							cout << "Wrong choice! Check again !" << endl;
							cin >> again;
						}
						if (again == 0) {
							edit_edit = false;

							out.open("19APCS1-CS162-checkin.txt");
							savefilecheckinincourse(out, DATE, num2, numdate, st);
							out.close();

							deletecourseinclass(cur1);
							deletecourseinclass(cur);
							delete cur2;
							deletecheckinincourse(DATE);
							deleteIDincourse(st);
						}

					} while (edit_edit);

				}
				else if (choice == 2) {
					student_Sche* DATE = nullptr;
					student* st = nullptr;
					int num2 = 0, numdate = 0;

					in.open("19APCS1-CS162-checkin.txt");
					loadfilecheckinincourse(in, DATE, num2, numdate, st);
					in.close();
					student_Sche* cur_date = DATE->pNext;
					date_to_check* cur1 = DATE->pHead;
					int i = 1;
					int checkin, day, mon, year, hour, min;
					while (cur1 != nullptr) {
						cout << i << ". " << cur1->date.year << " " << cur1->date.month << " " << cur1->date.day << " " << cur1->start_hour << " " << cur1->start_min << " " << cur1->end_hour << " " << cur1->end_min << " " << cur1->checkin << endl;
						cur1 = cur1->pNext;
						i++;
					}
					cur1 = DATE->pHead;
					cout << "Choose date to edit :";
					cin >> checkin;
					if (checkin == 1) {
						getTime(day, mon, year, hour, min);
						if (checkDate(day, mon, year, hour, min, cur1) == 2) {
							cout << "Year : "; cin >> cur1->date.year;
							cout << "Month : "; cin >> cur1->date.month;
							cout << "Day : "; cin >> cur1->date.day;
							cout << "Start hour / start minute : "; cin >> cur1->start_hour >> cur1->start_min;
							cout << "End hour / end minute : "; cin >> cur1->end_hour >> cur1->end_min;
						}
						else {
							cout << "This period has been occuring or has ended. You cannot change its information! " << endl;
						}
					}
					else {
						for (int j = 0; j < checkin - 1; j++) {
							cur1 = cur1->pNext;
						}
						getTime(day, mon, year, hour, min);
						if (checkDate(day, mon, year, hour, min, cur1) == 2) {
							cout << "Year : "; cin >> cur1->date.year;
							cout << "Month : "; cin >> cur1->date.month;
							cout << "Day : "; cin >> cur1->date.day;
							cout << "Start hour / start minute : "; cin >> cur1->start_hour >> cur1->start_min;
							cout << "End hour / end minute : "; cin >> cur1->end_hour >> cur1->end_min;
						}
						else {
							cout << "This period has been occuring or has ended.You cannot change its information!" << endl;
						}
					}
					date_to_check* cur2 = nullptr;
					while (cur_date != nullptr) {

						cur2 = cur_date->pHead;
						if (checkin != 1) {
							for (int j = 0; j < checkin - 1; j++) {
								cur2 = cur2->pNext;
							}
						}
						cur2->date.month = cur1->date.month;
						cur2->date.year = cur1->date.year;
						cur2->date.day = cur1->date.day;
						cur2->start_hour = cur1->start_hour;
						cur2->start_min = cur1->start_min;
						cur2->end_hour = cur1->end_hour;
						cur2->end_min = cur1->end_min;

						cur_date = cur_date->pNext;
					}
					out.open("19APCS1-CS162-checkin.txt");
					savefilecheckinincourse(out, DATE, num2, numdate, st);
					out.close();

					deleteIDincourse(st);
					deletecheckinincourse(DATE);
				}

			} while (edit == true);
			cout << "Edit successfully." << endl;
			break;

			out.open("Course.txt");
			savefilecourseinclass(out, head, num);
			out.close();
			out.open(clss);
			savefilecourseinclass(out, head1, num1);
			out.close();
		}
	}
	system("pause");
}
void removeCourse() {
	char* input_remove, *clss;
	course* head = nullptr;
	ifstream in;
	ofstream out;
	in.open("Course.txt");
	if (!in.is_open()) {
		cout << "Course's data is missing";
		return;
	}
	int num = 0;
	loadfilecourseinclass(in, head, num);
	in.close();
	cout << "Input course's ID to be removed : ";
	cin.ignore();
	inputcharacter(input_remove);
	cout << "Class: ";
	inputcharacter(clss);
	course* cur1 = head;
	course* temp = nullptr;

	bool check = true;
	while (check == true)
	{
		int checkcourse = 0;
		if (compare(cur1->id, input_remove) && compare(cur1->Class, clss)) {
			temp = cur1;
			head = head->pNext;
			checkcourse = 1;
		}
		else {
			while (cur1->pNext != nullptr) {
				if (compare(cur1->id, input_remove) && compare(cur1->Class, clss)) {
					checkcourse = 1;
					break;
				}
				else cur1 = cur1->pNext;
			}
			temp = cur1->pNext;
			cur1->pNext = cur1->pNext->pNext;
		}
		if (checkcourse == 0)
		{
			cout << "No course is suitable with your input data." << endl
				<< "Please input 1 to input another course." << endl
				<< "Or input 0 to return to main menu." << endl
				<< "Your choice : ";
			int choice;
			cin >> choice;
			while (choice != 1 && choice != 0)
			{
				cout << "Invalid option. Please try again." << endl
					<< "Please input 1 to input another course." << endl
					<< "Or input 0 to return to main menu." << endl
					<< "Your choice : ";
				cin >> choice;
			}
			if (choice == 1)
			{
				continue;
			}
			else if (choice == 0)
			{
				deletecourseinclass(head);
				break;
			}
		}
		check = false;
	}

	char clss1[100];
	strcpy(clss1, clss);
	delete[] temp->ltAccount;
	delete[] temp->ltName;
	delete[] temp->Class;
	delete[] temp->degree;
	delete[] temp->name;
	delete temp;
	num -= 1;
	out.open("Course.txt");
	savefilecourseinclass(out, head, num);
	out.close();
	deletecourseinclass(head);
	strcat(clss1, "-schedule.txt");
	in.open(clss1);
	if (!in.is_open()) {
		cout << "Class course's data is missing";
		return;
	}
	num = 0;
	loadfilecourseinclass(in, head, num);
	in.close();
	cur1 = head;
	temp;
	if (compare(cur1->id,input_remove)) {
		temp = cur1;
		head = head->pNext;
	}
	else {
		while (cur1->pNext != nullptr) {
			if (compare(cur1->id, input_remove)) {
				break;
			}
			else cur1 = cur1->pNext;
		}
		temp = cur1->pNext;
		cur1->pNext = cur1->pNext->pNext;
	}
	delete[] temp->ltAccount;
	delete[] temp->ltName;
	delete[] temp->Class;
	delete[] temp->degree;
	delete[] temp->name;
	delete temp;
	num -= 1;
	out.open(clss1);
	savefilecourseinclass(out, head, num);
	out.close();
	deletecourseinclass(head);
	cout << "Remove successfully." << endl;
	system("pause");
}

void removeStdinCourse()
{
	bool checkf = true;
	do
	{
		cin.ignore();
		char Tmp[1000];
		cout << "Please input class : ";
		cin.getline(Tmp, 1000, '\n');

		char* cls1;
		cls1 = new char[strlen(Tmp) + 1];
		strcpy_s(cls1, strlen(Tmp) + 1, Tmp);

		cout << "Please input course : ";
		cin.getline(Tmp, 1000, '\n');
		char* id;
		id = new char[strlen(Tmp) + 1];
		strcpy_s(id, strlen(Tmp) + 1, Tmp);

		strcat(cls1, "-");
		strcat(cls1, id);
		strcat(cls1, "-score.txt");

		int num;
		student* St = nullptr;
		student_Sche* Sc = nullptr;

		ifstream loadscore;
		loadscore.open(cls1);
		if (!loadscore.is_open())
		{
			cout << "Score's file is missing." << endl;
			return;
		}
		else
		{
			loadfilescoreincourse(loadscore, Sc, num, St);
		}

		student* curSt = St;
		student_Sche* curSc = Sc;

		cout << "Please input student's ID you'd like to remove : ";
		int ID;
		cin >> ID;
		int check = 0;
		for (int i = 0;i < num;++i)
		{
			if (ID == curSt->ID && curSc->active == 0)
			{
				curSc->active = -1;
				cout << "Student has been removed from this course." << endl;
				break;
			}
			else if (ID == curSt->ID && curSc->active == -1)
			{
				cout << "Student was removed from this course before." << endl;
				break;
			}
			curSt = curSt->pNext;
			curSc = curSc->pNext;
			check++;
		}
		if (check == num)
		{
			cout << "No student's ID suitable your ID.";
		}

		ofstream savescore;
		savescore.open(cls1);
		if (!savescore.is_open())
		{
			cout << "Score's file is missing." << endl;
			return;
		}
		else
		{
			savefilescoreincourse(savescore, Sc, num, St);
			savescore.close();
		}
		deletescoreincourse(Sc);
		deleteIDincourse(St);

		int checktodo;
		cout << "Do you want to remove another student? (1: YES; 0: NO)" << endl;
		cout << "Your choice : ";
		cin >> checktodo;
		while (checktodo != 1 && checktodo != 0)
		{
			cout << "Your input is invalid. Please try another one." << endl;
			cout << "Do you want to remove another student? (1: YES; 0: NO)" << endl;
			cout << "Your choice : ";
			cin >> checktodo;
		}
		if (checktodo == 0)
		{
			checkf = false;
		}
	} while (checkf == true);
	cout << "Remove successfully." << endl;
	system("pause");
}

void addStdinCourse() {
	ifstream ip;
	ofstream op;
	bool checkf = true;
	do {
		cin.ignore();
		
		char tmpcls[1000];
		cout << "Please input class you want to add student : ";
		cin.getline(tmpcls, 1000, '\n');

		char clss[1000] ;
		char clss1[1000];
		char clss2[1000];
		char id[100];
		cout << "Please input course you want to add student : ";
		cin.getline(id, 100, '\n');
		
	    strcpy_s(clss, strlen(tmpcls) + 1, tmpcls);
		strcat(clss, "-");
		strcat(clss, id);
		strcat(clss, ".txt");

		strcpy_s(clss1, strlen(tmpcls) + 1, tmpcls);
		strcat(clss1, "-");
		strcat(clss1, id);
		strcat(clss1, "-score.txt");

		strcpy_s(clss2, strlen(tmpcls) + 1, tmpcls);
		strcat(clss2, "-");
		strcat(clss2, id);
		strcat(clss2, "-checkin.txt");
	
		student* st = nullptr;
		int num = 0;
		int std_id;

		cout << "Input student's ID you want to add : ";
		cin >> std_id;

		ip.open("Student.txt");
		if (!ip.is_open()) {
			cout << "Cannot open Student.txt " << endl;
			return;
		}
		else {
			loadfilestudent(ip, st, num);
			ip.close();
		}
		student* cur = st;
		while (cur != nullptr) {
			if (cur->ID == std_id) break;
			else cur = cur->pNext;
		}
		if (cur == nullptr) {
			cout << "This student with id = " << std_id << " is not in K19. Please add him/her before adding to course " << endl;
			checkf = false;
		}
		else {
			student* st1 = nullptr;
			int num1 = 0;

			ip.open(clss);
			if (!ip.is_open()) {
				cout << "Cannot open file " << clss << endl;
				return;
			}
			else {
				loadfilestudentincourse(ip, st1, num1);
				ip.close();
			}

			student* cur1 = st1;

			if (cur1->ID == std_id) {
				cout << "This student is already in this course. Please check again! " << endl;
			}
			else {
				while (cur1->pNext != nullptr) {
					if (cur1->ID == std_id) {
						break;
					}
					else cur1 = cur1->pNext;
				}
				if (cur1->pNext != nullptr) {
					cout << "This student is already in this course. Check again " << endl;
				}
				else {
					cur1->pNext = new student;
					cur1 = cur1->pNext;
					cur1->pNext = nullptr;
					cur1->ID = cur->ID;
					cur1->gender = cur->gender;
					cur1->Dob.day = cur->Dob.day;
					cur1->Dob.month = cur->Dob.month;
					cur1->Dob.year = cur->Dob.year;

					char tmp[1000];
					strcpy(tmp, cur->Class);
					cur1->Class = new char[strlen(tmp) + 1];
					strcpy_s(cur1->Class, strlen(tmp) + 1, tmp);

					char tmp2[1000];
					strcpy(tmp2, cur->fullname);
					cur1->fullname = new char[strlen(tmp2) + 1];
					strcpy_s(cur1->fullname, strlen(tmp2) + 1, tmp2);
					num1++;

					op.open(clss);
					if (!op.is_open()) {
						cout << "Cannot open file " << clss << endl;
						return;
					}
					else {
						savefilestudentincourse(op, st1, num1);
						op.close();
					}

					deletestudent(st);
					deletestudentincourse(st1);
					//add that node to checkin file

					student_Sche* head_st = nullptr;
					student* st2 = nullptr;
					int numdate = 0;

					ip.open(clss2);
					if (!ip.is_open()) {
						cout << "Cannot open file " << clss1 << endl;
						return;
					}
					else {
						loadfilecheckinincourse(ip, head_st, num1, numdate, st2);
						ip.close();
					}
					student* curst2 = st2;
					while (curst2->pNext != nullptr) {
						curst2 = curst2->pNext;
					}
					curst2->pNext = new student;
					curst2->pNext->ID = std_id;
					curst2->pNext->pNext = nullptr;
					student_Sche* cur2 = head_st;
					while (cur2->pNext != nullptr) {
						cur2 = cur2->pNext;
					}

					//create node hold information of that student in course
					student_Sche* newNode = new student_Sche;
					newNode->pNext = nullptr;
					newNode->pHead = new date_to_check;
					date_to_check* cur_temp = cur2->pHead;

					newNode->pHead->date.day = cur_temp->date.day;
					newNode->pHead->date.month = cur_temp->date.month;
					newNode->pHead->date.year = cur_temp->date.year;
					newNode->pHead->start_hour = cur_temp->start_hour;
					newNode->pHead->start_min = cur_temp->start_min;
					newNode->pHead->end_hour = cur_temp->end_hour;
					newNode->pHead->end_min = cur_temp->end_min;
					cur_temp = cur_temp->pNext;

					date_to_check* cur_tmp = newNode->pHead;
					cur_tmp->pNext = nullptr;

					for (int i = 0; i < numdate - 1; i++) {

						date_to_check* NODE = new date_to_check;
						NODE->pNext = nullptr;
						NODE->date.day = cur_temp->date.day;
						NODE->date.month = cur_temp->date.month;
						NODE->date.year = cur_temp->date.year;
						NODE->start_hour = cur_temp->start_hour;
						NODE->start_min = cur_temp->start_min;
						NODE->end_hour = cur_temp->end_hour;
						NODE->end_min = cur_temp->end_min;
						cur_tmp->pNext = NODE;

						cur_temp = cur_temp->pNext;
						cur_tmp = cur_tmp->pNext;
					}

					cur2->pNext = newNode;
					num1++;
					op.open(clss2);
					if (!op.is_open()) {
						cout << "Cannot open file " << clss1 << endl;
						return;
					}
					else {
						savefilecheckinincourse(op, head_st, num1, numdate, st2);
						op.close();
					}

					deleteIDincourse(st2);
					// add that node to score file
					student_Sche* head_st2 = nullptr;
					st2 = nullptr;
					ip.open(clss1);
					if (!ip.is_open()) {
						cout << "Cannot open file " << clss2 << endl;
						return;
					}
					else {
						loadfilescoreincourse(ip, head_st2, num1, st2);
						ip.close();
					}
					student_Sche* cur3 = head_st2;
					while (cur3->pNext != nullptr) {
						cur3 = cur3->pNext;
					}
					cur3->pNext = newNode;

					num1++;
					op.open(clss1);
					curst2 = st2;
					while (curst2->pNext != nullptr) {
						curst2 = curst2->pNext;
					}
					curst2->pNext = new student;
					curst2->pNext->ID = std_id;
					curst2->pNext->pNext = nullptr;
					if (!op.is_open()) {
						cout << "Cannot open file " << clss2 << endl;
						return;
					}
					else {
						savefilescoreincourse(op, head_st2, num1, st2);
						op.close();
					}
					cur3->pNext = nullptr;
					cout << "Student with id = " << std_id << " has been added to course " << id << endl;
					deletescoreincourse(head_st2);
					deletestudentincourse(st1);
					deletestudentinclass(st);
					deleteIDincourse(st2);
					deletecheckinincourse(head_st);
				}
			}
			int checktodo;
			cout << "Do you want to add another student? (1: YES; 0: NO)" << endl;
			cout << "Your choice : ";
			cin >> checktodo;
			while (checktodo != 1 && checktodo != 0)
			{
				cout << "Your input is invalid. Please try another one." << endl;
				cout << "Do you want to add another student? (1: YES; 0: NO)" << endl;
				cout << "Your choice : ";
				cin >> checktodo;
			}
			if (checktodo == 0)
			{
				checkf = false;
			}
		}

	} while (checkf == true);
	cout << "Add successfully." << endl;
	system("pause");
}
void viewCourse() {
	ifstream in;
	in.open("Course.txt");
	if (!in.is_open()) {
		cout << "Cannot open file. " << endl;
		return;
	}
	course* head = nullptr;
	int num = 0;
	loadfilecourseinclass(in, head, num);
	in.close();
	cout << "There are " << num << " courses in this semester. " << endl;
	course* cur = head;
	while (cur != nullptr) {
		cout << cur->id << " " << cur->name << " " << cur->Class << endl;
		cur = cur->pNext;
	}
	deletecourseinclass(head);
	system("pause");
}

void viewStudentinCourse() {
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
		while (cur!=nullptr)
		{
			cout << num << ". " << cur->Class <<"-"<<cur->id<< endl;			
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

void editlecturer()
{
	bool check = true;
	do
	{
		cout << "Please choose one of the following options : " << endl
			<< "1. Create a new lecturer." << endl
			<< "2. Update lecturers." << endl
			<< "3. Delete lecturers." << endl
			<< "4. View all lecturer." << endl
			<< "0. Exit." << endl
			<< "Your choice : ";
		int choice;
		cin >> choice;
		// Check condition
		while (choice < 0 || choice > 5)
		{
			cout << "Your option is invalid. Please try another one : " << endl;
			cin >> choice;
		}
		if (choice == 0)
			return;

		int num;
		lecturer* Lt = nullptr;
		ifstream load;
		load.open("Lecturer.txt");
		if (!load.is_open())
		{
			cout << "Lecturer's file is missing." << endl;
		}
		else
		{
			loadfilelecturer(load, Lt, num);
		}
		load.close();

		cin.ignore();
		// Create
		if (choice == 1)
		{
			lecturer* cur = Lt;
			while (cur->pNext != nullptr)
			{
				cur = cur->pNext;
			}
			cur->pNext = new lecturer;
			cur = cur->pNext;
			cout << "Please input username : ";
			inputcharacter(cur->user);
			cout << "Please input password : ";
			inputcharacter(cur->password);
			cout << "Please input fullname : ";
			inputcharacter(cur->fullname);
			cout << "Please input degree : ";
			inputcharacter(cur->degree);
			cout << "Please input gender (0: male; 1: female) : ";
			cin >> cur->gender;
			cur->pNext = nullptr;
			ofstream save;
			save.open("Lecturer.txt");
			if (!save.is_open())
			{
				cout << "Lecturer's file is missing." << endl;
			}
			else
			{
				savefilelecturer(save, Lt, num + 1);
				save.close();
			}
		}
		// Update
		else if (choice == 2)
		{
			cout << "Which festures you'd like to update?" << endl
				<< "1. Lecturer's username." << endl
				<< "2. Lecturer's password." << endl
				<< "3. Lecturer's fullname." << endl
				<< "4. Lecturer's degree." << endl
				<< "5. Lecturer's gender." << endl
				<< "0. Return back." << endl
				<< "Your choice : ";
			int op;
			cin >> op;
			cin.ignore();
			while (op < 0 || op > 5)
			{
				cout << "Your option is invalid. Please try another one : ";
				cin >> op;
			}
			if (op == 0)
			{
				continue;
			}
			cout << "Please input the fullname of the lecturer : ";
			char* fname;
			inputcharacter(fname);
			lecturer* cur = Lt;
			while (cur != nullptr)
			{
				if (compare(fname, cur->fullname))
				{
					char* newedit;
					if (op == 1)
					{
						cout << "Please input the new lecturer's username : ";
						inputcharacter(newedit);
						cur->user = newedit;
					}
					else if (op == 2)
					{
						cout << "Please input the new lecturer's password : ";
						inputcharacter(newedit);
						cur->password = newedit;
					}
					else if (op == 3)
					{
						cout << "Please input the new lecturer's fullname : ";
						inputcharacter(newedit);
						cur->fullname = newedit;
					}
					else if (op == 4)
					{
						cout << "Please input the new lecturer's degree : ";
						inputcharacter(newedit);
						cur->fullname = newedit;
					}
					else if (op == 5)
					{
						cout << "Please input the new lecturer's gender (0: Male; 1: Female) : ";
						cin >> cur->gender;
					}
					break;
				}
				cur = cur->pNext;
			}
			ofstream save;
			save.open("Lecturer.txt");
			if (!save.is_open())
			{
				cout << "Lecturer's file is missing." << endl;
			}
			else
			{
				savefilelecturer(save, Lt, num);
				save.close();
			}
		}
		// Delete
		else if (choice == 3)
		{
			cout << "Please input the lecturer's name  you'd like to delete : ";
			char* fname;
			inputcharacter(fname);
			if (Lt == nullptr)
			{
				cout << "There are no lecturers left." << endl;
				system("pause");
			}
			else if (compare(fname, Lt->fullname))
			{
				lecturer* tmp = Lt;
				Lt = Lt->pNext;
				tmp->pNext = nullptr;
				deletelecturer(tmp);
				num--;
			}
			else
			{
				lecturer* cur = Lt;
				while (cur && cur->pNext)
				{
					if (compare(cur->pNext->fullname, fname))
					{
						lecturer* tmp = cur->pNext;
						cur->pNext = cur->pNext->pNext;
						tmp->pNext = nullptr;
						deletelecturer(tmp);
						num--;
						break;
					}
					cur = cur->pNext;
				}
			}
			ofstream save;
			save.open("Lecturer.txt");
			if (!save.is_open())
			{
				cout << "Lecturer's file is missing." << endl;
			}
			else
			{
				savefilelecturer(save, Lt, num);
				save.close();
			}
		}
		// View
		else if (choice == 4)
		{
			lecturer* cur = Lt;
			cout << "There are " << num << " lecturers." << endl;
			cout << endl;
			for (int i = 0;i < num; ++i)
			{
				cout << "Lecturer " << i + 1 << " : " << endl;
				cout << "Username : " << cur->user << endl;
				cout << "Fullname : " << cur->fullname << endl;
				cout << "Degree : " << cur->degree << endl;
				if (cur->gender == 0)
				{
					cout << "Gender : Male" << endl;
				}
				else
				{
					cout << "Gender : Female" << endl;
				}
				cout << endl;
				cur = cur->pNext;
			}
		}
		deletelecturer(Lt);
		cout << "Do you wanna to edit a new one? (1: YES; 2: NO) : ";
		int checknum;
		cin >> checknum;
		if (checknum == 2)
			check = false;
	} while (check == true);
	cout << "Edit successfully." << endl;
	system("pause");
}

void viewAttendance() {
	cin.ignore();

	char tmpcls[1000];
	cout << "Input class : ";
	cin.getline(tmpcls, 1000, '\n');

	char tmpid[100];
	cout << "Input id : ";
	cin.getline(tmpid, 100, '\n');

	char id[100] , id1[100] ;
	strcpy_s(id, strlen(tmpid) + 1, tmpid);
	strcpy_s(id1, strlen(tmpid) + 1, tmpid);
	
	char clss[1000];
	strcpy_s(clss, strlen(tmpcls) + 1, tmpcls);
	strcat(clss, "-");
	strcat(clss, id);
	strcat(clss, "-score.txt");

	char clss1[1000];
	strcpy_s(clss1, strlen(tmpcls) + 1, tmpcls);
	strcat(clss1, "-");
	strcat(clss1, id1);
	strcat(clss1, ".txt");

	strcat(tmpcls, "-");
	strcat(tmpcls, tmpid);
	strcat(tmpcls, "-checkin.txt");

	student_Sche* head_st = nullptr;
	student* st = nullptr;
	student* st1 = nullptr;

	ifstream ip;
	
	int num = 0;
	ip.open(clss);
	if (!ip.is_open()) {
		cout << "Cannot open " << clss << endl;
		return;
	}
	loadfilescoreincourse(ip, head_st, num ,st);
	ip.close();

	ip.open(clss1);
	if (!ip.is_open()) {
		cout << "Cannot open " << clss1 << endl;
		return;
	}
	int num1 = 0;
	loadfilestudentincourse(ip, st1, num1);
	ip.close();
	ip.open(tmpcls);
	student* st2 = nullptr;
	int numdate = 0;
	student_Sche* date = nullptr;
	if (!ip.is_open())
	{
		cout << "Cannot open file " << tmpcls << endl;
	}
	else {
		loadfilecheckinincourse(ip, date, num1, numdate, st2);
		ip.close();
	} 

	student_Sche* cur_st = head_st;
	student_Sche* cur_st2 = date;
	date_to_check* cur_date = nullptr;
	student* cur = st1;
	cout << "Attendance of " << tmpid << " in class " << tmpcls << " : " << endl << endl;
	while (cur_st != nullptr) {
		if (cur_st->active == 0) {
			cout << cur->ID << " " << cur->fullname << " ACTIVE" << endl;
			cur_date = cur_st2->pHead;
			while (cur_date != nullptr) {
				cout << cur_date->date.year << " " << cur_date->date.month << " " << cur_date->date.day << " " << cur_date->start_hour << " " << cur_date->start_min << " " << cur_date->end_hour << " " << cur_date->end_min << " " << cur_date->checkin << endl;
				cur_date = cur_date->pNext;
			}
				cout << "--------------------------------" << endl;
		}
		cur_st = cur_st->pNext;
		cur = cur->pNext;
		cur_st2 = cur_st2->pNext;
	}
	deletescoreincourse(head_st);
	deletestudentincourse(st1);
	deleteIDincourse(st);
	deletecheckinincourse(date);
	deleteIDincourse(st2);
	delete cur_st2;
	delete cur_date;
	delete cur_st;
	delete cur;
	system("pause");
}

void exportscoreboardtocsv()
{
	cin.ignore();
	char Tmp[1000];
	cout << "Please input class : ";
	cin.getline(Tmp, 1000, '\n');

	char cls[100];
	strcpy_s(cls, strlen(Tmp) + 1, Tmp);

	char cls1[100];
	strcpy_s(cls1, strlen(Tmp) + 1, Tmp);

	char cls2[100];
	strcpy_s(cls2, strlen(Tmp) + 1, Tmp);

	cout << "Please input course : ";
	cin.getline(Tmp, 1000, '\n');
	char* id = nullptr;
	id = new char[strlen(Tmp) + 1];
	strcpy_s(id, strlen(Tmp) + 1, Tmp);

	// File score
	strcat(cls, "-");
	strcat(cls, id);
	strcat(cls, "-score.txt");

	// File student
	strcat(cls1, "-");
	strcat(cls1, id);
	strcat(cls1, ".txt");

	student* St = nullptr;
	student_Sche* Sc = nullptr;
	int num;

	ifstream loadstd;
	loadstd.open(cls1);
	if (!loadstd.is_open())
	{
		cout << "Student's file is missing." << endl;
		return;
	}
	else
	{
		loadfilestudentincourse(loadstd, St, num);
	}
	loadstd.close();

	ifstream loadscore;
	loadscore.open(cls);
	if (!loadscore.is_open())
	{
		cout << "Score's file is missing." << endl;
		deletestudentincourse(St);
		return;
	}
	else
	{
		loadfilescoreinnewcourse(loadscore, Sc, num);
	}
	loadscore.close();

	strcat(cls2, "-");
	strcat(cls2, id);
	strcat(cls2, "-Scoreboard.csv");

	student* curSt = St;
	student_Sche* curSc = Sc;
	ofstream exportscore;
	exportscore.open(cls2);
	if (!exportscore.is_open())
	{
		cout << "Score's csv file is missing." << endl;
		deletestudentincourse(St);
		deletescoreincourse(Sc);
		return;
	}
	else
	{
		exportscore << "No,StudentID,Fullname,Midterm,Final,Bonus,Total" << endl;
		for (int i = 0;i < num;++i)
		{
			exportscore << i + 1 << "," << curSt->ID << "," << curSt->fullname << "," << curSc->score.midterm << ","
				<< curSc->score.finalterm << "," << curSc->score.bonus << "," << curSc->score.total << endl;
			if (curSt->pNext && curSc->pNext)
			curSt = curSt->pNext;
			curSc = curSc->pNext;
		}
		exportscore.close();
	}
	deletestudentincourse(St);
	deletescoreincourse(Sc);
	delete[] id;
	cout << "Export successfully." << endl;
}

void exportattendancetocsv()
{
	cin.ignore();
	char Tmp[1000];
	cout << "Please input class : ";
	cin.getline(Tmp, 1000, '\n');
	char* cls = nullptr;
	cls = new char[strlen(Tmp) + 1];
	strcpy_s(cls, strlen(Tmp) + 1, Tmp);

	char cls1[100];
	strcpy_s(cls1, strlen(Tmp) + 1, Tmp);

	char cls2[100];
	strcpy_s(cls2, strlen(Tmp) + 1, Tmp);

	char cls3[100];
	strcpy_s(cls3, strlen(Tmp) + 1, Tmp);

	cout << "Please input course : ";
	cin.getline(Tmp, 1000, '\n');

	char* id = nullptr;
	id = new char[strlen(Tmp) + 1];
	strcpy_s(id, strlen(Tmp) + 1, Tmp);

	// Load file course.txt
	strcat(cls, "-");
	strcat(cls, id);
	strcat(cls, ".txt");

	student* St = nullptr;
	int num = 0;
	
	ifstream loadStd;
	loadStd.open(cls);
	if (!loadStd.is_open())
	{
		cout << "Student's file is missing." << endl;
		return;
	}
	else
	{
		loadfilestudentincourse(loadStd, St, num);
	}
	loadStd.close();

	// File score
	strcat(cls1, "-");
	strcat(cls1, id);
	strcat(cls1, "-score.txt");

	student_Sche* Sc = nullptr;
	ifstream loadSc;
	loadSc.open(cls1);
	if (!loadSc.is_open())
	{
		cout << "Score's file is missing." << endl;
		return;
	}
	else
	{
		loadfilescoreinnewcourse(loadSc, Sc, num);
	}
	loadSc.close();

	// File checkin
	strcat(cls2, "-");
	strcat(cls2, id);
	strcat(cls2, "-checkin.txt");

	int numdate = 0;

	student_Sche* ScDate = nullptr;
	ifstream loaddate;
	loaddate.open(cls2);
	if (!loaddate.is_open())
	{
		cout << "Check-in 's file is missing." << endl;
		return;
	}
	else
	{
		loadfilecheckininnewcourse(loaddate, ScDate, num, numdate);
	}
	loaddate.close();

	// Check active
	while (Sc->active == -1)
	{
		student_Sche* TmpSc = Sc;
		student* TmpSt = St;
		student_Sche* TmpScDate = ScDate;
		Sc = Sc->pNext;
		St = St->pNext;
		ScDate = ScDate->pNext;

		TmpSc->pNext = nullptr;
		TmpSt->pNext = nullptr;
		TmpScDate->pNext = nullptr;

		delete TmpSc;
		deletestudentincourse(TmpSt);
		deletecheckinincourse(TmpScDate);
		num--;
	}

	student* curSt = St;
	student_Sche* curSc = Sc;
	student_Sche* curScDate = ScDate;

	while (curSt->pNext&& curSc->pNext&& curScDate->pNext)
	{
		if (curSc->pNext->active == -1)
		{
			student_Sche* TmpSc = curSc->pNext;
			student* TmpSt = curSt->pNext;
			student_Sche* TmpScDate = curScDate->pNext;
			curSc->pNext = curSc->pNext->pNext;
			curSt->pNext = curSt->pNext->pNext;
			curScDate->pNext = curScDate->pNext->pNext;

			TmpSc->pNext = nullptr;
			TmpSt->pNext = nullptr;
			TmpScDate->pNext = nullptr;

			delete TmpSc;
			deletestudentincourse(TmpSt);
			deletecheckinincourse(TmpScDate);
			num--;
		}
		else
		{
			curSc = curSc->pNext;
			curSt = curSt->pNext;
		}
	}

	// Export to csv
	curSc = Sc;
	curSt = St;
	curScDate = ScDate;

	if (curSc == nullptr || curSt == nullptr || curScDate == nullptr)
	{
		cout << "Export failed. Because there are no students left in this course." << endl;
		return;
	}

	date_to_check* curdate = nullptr;

	strcat(cls3, "-");
	strcat(cls3, id);
	strcat(cls3, "-Attendance.csv");
	ofstream exportcsv;
	exportcsv.open(cls3);
	if (!exportcsv.is_open())
	{
		cout << "Attendance's file is missing." << endl;
		return;
	}
	else
	{
		exportcsv << "No,ID,Fullname,Year,Month,Day,Start-hour,Start-minute,Attendance" << endl;
		for (int i = 0;i < num;++i)
		{
			curdate = curScDate->pHead;
			for (int j = 0;j < numdate;++j)
			{
				exportcsv << i + 1 << "," << curSt->ID << "," << curSt->fullname << ","
					<< curdate->date.year << "," << curdate->date.month << "," << curdate->date.day << ","
					<< curdate->start_hour << "," << curdate->start_min << ",";
				if (curdate->checkin == -1)
					exportcsv << "Absent" << endl;
				else
					exportcsv << "Present" << endl;
				curdate = curdate->pNext;
			}
			curSt = curSt->pNext;
			curScDate = curScDate->pNext;
			if (curSt == nullptr || curScDate == nullptr)
				break;
		}
	}
	exportcsv.close();
	cout << "Export successfully." << endl;
	deletestudentincourse(St);
	deletecheckinincourse(ScDate);
	deletescoreincourse(Sc);
	delete[]id;
}