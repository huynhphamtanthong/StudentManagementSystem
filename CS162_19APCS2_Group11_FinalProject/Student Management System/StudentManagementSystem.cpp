// Group : 11
// Class : 19CTT2

#include "General.h"
#include "Staff.h"
#include "Lecturer.h"
#include "Student.h"

int main()
{
	// Login
	staff* Sf=nullptr;
	lecturer* Lt=nullptr;
	student* St=nullptr;
	int option, choice;
	bool logoutcheck = false;
	do
	{
		bool logincheck = false;
		cout << "Please choose the following options : " << endl
			<< "1.Login" << endl
			<< "2.Exit" << endl;
		cout << "Your choice : ";
		cin >> option;
		while (option != 1 && option != 2)
		{
			cout << "Your option is invalid. Please try again." << endl;
			cout << "1.Login" << endl
				<< "2.Exit" << endl;
			cin >> option;
		}
		if (option == 1)
		{
			while (logincheck == false)
			{
				cout << "What's your role? (0:Staff ; 1:Lecturer ; 2:Student) OR choose 3 to exit : ";
				cin >> choice;
				while (choice < 0 || choice > 3)
				{
					cout << "Your role is invalid. Please try again : ";
					cin >> choice;
				}
				if (choice == 3) {
					cout << "Thanks for using my program." << endl;
					return 0;
				}
				logincheck = Login(Sf, Lt, St, choice);
				if (logincheck == false)
				{
					Sf = nullptr;
					Lt = nullptr;
					St = nullptr;
					cout << "Login failed." << endl;
				}
			}
			cout << "Login successfully." << endl;
		}
		else if (option == 2) {
			cout << "Thanks for using my program." << endl;
			return 0;
		}
		// Menu
		bool getback = true;
		do
		{
			if (choice == 0)
			{
				cout << endl << "Hello, ";
				if (Sf->gender == 1)
				{
					cout << "Ms " << Sf->fullname << endl;
				}
				else
				{
					cout << "Mr " << Sf->fullname << endl;
				}
				int feature;
				cout << "Please choose the following features : " << endl
					<< "1. View profile information" << endl
					<< "2. Change password" << endl
					<< "3. Import student from a csv file" << endl
					<< "4. Add a student to a class" << endl
					<< "5. Edit an existing student" << endl
					<< "6. Remove a student" << endl
					<< "7. Change students from class A to class B" << endl
					<< "8. View list of classes" << endl
					<< "9. View list of students in a class" << endl
					<< "10. Create / update / delete / view academic years (2018-2019), and semesters (Fall)" << endl
					<< "11. Import courses from a csv file" << endl
					<< "12. Add a new course" << endl
					<< "13. Edit an existing course" << endl
					<< "14. Remove a course" << endl
					<< "15. Remove a specific student from a course" << endl
					<< "16. Add a specific student to a course" << endl
					<< "17. View list of courses in the current semester" << endl
					<< "18. View list of students of a course" << endl
					<< "19. View attendance list of a course" << endl
					<< "20. Create / update / delete / view all lecturers" << endl
					<< "21. Search and view the scoreboard of a course." << endl
					<< "22. Export a scoreboard to a csv file." << endl
					<< "23. Search and view attendance list of a course" << endl
					<< "24. Export a attendance list to a csv file" << endl
					<< "25. Log out" << endl
					<< "Your choice : ";
				cin >> feature;
				cout << endl;
				switch (feature)
				{
				case 1:
					profileSf(Sf);
					logoutcheck = false;
					break;
				case 2:
					changePassSf(Sf);
					logoutcheck = false;
					break;
				case 3:
					readCSVSt();
					logoutcheck = false;
					break;
				case 4:
					addStudent();
					logoutcheck = false;
					break;
				case 5:
					editStudent();
					logoutcheck = false;
					break;
				case 6:
					removeStudent();
					logoutcheck = false;
					break;
				case 7:
					changeClass();
					logoutcheck = false;
					break;
				case 8:
					viewClass();
					logoutcheck = false;
					break;
				case 9:
					viewStudentsInAClass();
					logoutcheck = false;
					break;
				case 10:
					academicyear();
					logoutcheck = false;
					break;
				case 11:
					readCourseCSV();
					logoutcheck = false;
					break;
				case 12:
					addCourse();
					logoutcheck = false;
					break;
				case 13:
					editCourse();
					logoutcheck = false;
					break;
				case 14:
					removeCourse();
					logoutcheck = false;
					break;
				case 15:
					removeStdinCourse();
					logoutcheck = false;
					break;
				case 16:
					addStdinCourse();
					logoutcheck = false;
					break;
				case 17:
					viewCourse();
					logoutcheck = false;
					break;
				case 18:
					viewStudentinCourse();
					logoutcheck = false;
					break;
				case 19:
					viewAttendance();
					logoutcheck = false;
					break;
				case 20:
					editlecturer();
					logoutcheck = false;
					break;
				case 21:
					viewscoreboard();
					logoutcheck = false;
					break;
				case 22:
					exportscoreboardtocsv();
					logoutcheck = false;
					break;
				case 23:
					viewAttendance();
					logoutcheck = false;
					break;
				case 24:
					exportattendancetocsv();
					logoutcheck = false;
					break;
				case 25:
					deletestaff(Sf);
					Sf = nullptr;
					getback = false;
					logoutcheck = true;
					break;
				default :
					logoutcheck = false;
					cout << "Invalid feature. Please try again." << endl;
					system("pause");
					break;
				}
			}
			else if (choice == 1)
			{
				cout << endl << "Hello, " << Lt->degree << " " << Lt->fullname << endl;
				int feature;
				cout << "Please choose the following features : " << endl
					<< "1. View profile information" << endl
					<< "2. Change password" << endl
					<< "3. View list of courses in the current semester" << endl
					<< "4. View list of students of a course" << endl
					<< "5. View attendance list of a course" << endl
					<< "6. Edit an attendance" << endl
					<< "7. Import scoreboard of a course (midterm, final, lab, bonus) from a csv file" << endl
					<< "8. Edit grade of a student" << endl
					<< "9. View a scoreboard" << endl
					<< "10. Log out" << endl
					<< "Your choice : ";
				cin >> feature;
				switch (feature)
				{
				case 1:
					profileLt(Lt);
					logoutcheck = false;
					break;
				case 2:
					changePassLt(Lt);
					logoutcheck = false;
					break;
				case 3:
					viewCourseforlec(Lt);
					logoutcheck = false;
					break;
				case 4:
					viewStudentinCourseforlec(Lt);
					logoutcheck = false;
					break;
				case 5:
					viewAttendance();
					logoutcheck = false;
					break;
				case 6:
					editattendance();
					logoutcheck = false;
					break;
				case 7:
					readCSVscore();
					logoutcheck = false;
					break;
				case 8:
					editGrade();
					logoutcheck = false;
					break;
				case 9:
					viewscoreboard();
					logoutcheck = false;
					break;
				case 10:
					deletelecturer(Lt);
					Lt = nullptr;
					getback = false;
					logoutcheck = true;
					break;
				default :
					logoutcheck = false;
					cout << "Invalid feature. Please try again." << endl;
					system("pause");
					break;
				}
			}
			else
			{
				cout << endl << "Hello, " << St->fullname << endl;
				int feature;
				cout << "Please choose the following features : " << endl
					<< "1. View profile information" << endl
					<< "2. Change password" << endl
					<< "3. Check-in " << endl
					<< "4. View check-in result" << endl
					<< "5. View schedule" << endl
					<< "6. View your scores of a course" << endl
					<< "7. Log out" << endl
					<< "Your choice : ";
				cin >> feature;
				switch (feature)
				{
				case 1 :
					profileSt(St);
					logoutcheck = false;
					break;
				case 2:
					changePassSt(St);
					logoutcheck = false;
					break;
				case 3:
					check_in(St);
					logoutcheck = false;
					break;
				case 4:
					viewcheckin(St->ID);
					logoutcheck = false;
					break;
				case 5:
					viewschedule(St);
					logoutcheck = false;
					break;
				case 6:
					viewownscore(St);
					logoutcheck = false;
					break;
				case 7:
					deletestudent(St);
					St = nullptr;
					getback = false;
					logoutcheck = true;
					break;
				default:
					logoutcheck = false;
					cout << "Invalid feature. Please try again." << endl;
					system("pause");
					break;
				}
			}
		} while (getback == true);
	} while (logoutcheck == true);

	return 0;
}