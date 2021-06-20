#include<iostream>
#include<fstream>
using namespace std;
//Helper Class basically just doing help in calculating the length of a particular string and geeting the string from a temporary Array
class Helper {

public:
	//Calculating the Length of String
	static int StrLen(string _string)
	{
		int _stringLength = NULL;

		for (int index = NULL; _string[index] != '\0'; index++)
			_stringLength++;

		return _stringLength;
	}
	//Extracting the string which is created on heap from a temporary Array
	static char* getstringfrombuffer(char* temp)
	{
		int Length = StrLen(temp);

		char* stringfrombuffer = new char[Length + 1];
		int counter = 0;
		for (char* i = temp; *i != '\0'; i++, counter++)
		{
			stringfrombuffer[counter] = *i;
		}
		stringfrombuffer[counter] = '\0';

		return stringfrombuffer;
	}
};
//Book class is holding the data of Available Books
class Book {

public:
	char* ID;	//ID of the Book
	char* Title; //Title of the Book
	char* Type;	  //Type of the Book
	char* Author;	//Author of the Book
	int Quantity;	//Quantity of a particular Book
	//Constructor
	Book()
	{
		ID = nullptr;
		Title = nullptr;
		Author = nullptr;
		Quantity = 0;
	}
	//Loading the data from the file
	void LoadDataFromFile(ifstream & book)
	{
		char temp[10];
		book >> temp;
		ID = Helper::getstringfrombuffer(temp);
		char temp2[100];
		book.getline(temp2, 45);
		book.getline(temp2, 45);
		Title = Helper::getstringfrombuffer(temp2);
		book.getline(temp2, 45);
		Author = Helper::getstringfrombuffer(temp2);
		book >> Quantity;
	}
	//Copy Constructor
	/*Book(const Book& rhs)
	{
		ID = Helper::getstringfrombuffer(rhs.ID);
		Title = Helper::getstringfrombuffer(rhs.Title);
		Author = Helper::getstringfrombuffer(rhs.Author);
		Quantity = rhs.Quantity;
	}*/
	//Assignment Operator
	void operator=(const Book& rhs)
	{
		ID = Helper::getstringfrombuffer(rhs.ID);
		Title = Helper::getstringfrombuffer(rhs.Title);
		Author = Helper::getstringfrombuffer(rhs.Author);
		Quantity = rhs.Quantity;
	}
};

class Library {

public:
	Book* OrderdBook;	//Record of Ordered Books
	Book** BookList;	//Record of all Avaialable Books
	int AvailableBooks;	//Number of Available Books
	//Constructor
	Library()
	{
		BookList = nullptr;
		OrderdBook = nullptr;
		AvailableBooks = 0;
	}
	//UpdateBooks function is writting the data of updated books
	void UpdateBooks()
	{
		ofstream write("Books.txt");

		for (int i = 0; i < AvailableBooks; i++)
		{
			write << BookList[i]->ID;
			write << endl;
			write << BookList[i]->Title;
			write << endl;
			write << BookList[i]->Author;
			write << endl;
			write << BookList[i]->Quantity;
			if(i!=AvailableBooks-1)
				write << endl;
		}
		write.close();
	}
	//ReadDataFromFile is reading the data from file and setting up the BookList Record
	void ReadDataFromFile()
	{
		ifstream book("Books.txt");
		char ID[10];
		char Title[100];
		char Author[100];
		int Quantity;

		while (!book.eof())
		{
			book >> ID;
			book.getline(Title, 20);
			book.getline(Title, 45);
			book.getline(Author, 45);
			book >> Quantity;

			AvailableBooks++;
		}
		book.close();

		BookList = new Book * [AvailableBooks];

		ifstream Rebook("Books.txt");

		for (int i = 0; i < AvailableBooks; i++)
		{
			BookList[i] = new Book;
			BookList[i]->LoadDataFromFile(Rebook);

		}
		Rebook.close();
	}
	//ViewAvailableBooks Function is outputting the Available Books on console
	void ViewAvailableBooks()
	{
		//ReadDataFromFile();
		if (BookList != nullptr)
		{
			for (int i = 0; i < AvailableBooks; i++)
			{
				cout << BookList[i]->ID << "\t" << BookList[i]->Title << "\t" << BookList[i]->Author << "\t" << BookList[i]->Quantity << endl;
			}
		}
		else
		{
			cout << "Not Found!!!\n";
		}
	}
	//Searching the ID from Record and returning the BookList's index of that particular Book
	Book* SearchByID(char* ID)
	{
		int Length = Helper::StrLen(ID);

		for (int i = 0; i < AvailableBooks; i++)
		{
			if (ID[0] == BookList[i]->ID[0])
			{
				int counter = 1;
				for (int j = 1; j < Length; j++)
				{
					if (ID[j] == BookList[i]->ID[j])
					{
						counter++;
					}
					if (ID[j] != BookList[i]->ID[j])
					{
						j = Length;
					}
					if (counter == Length)
					{
						return BookList[i];
					}
				}
			}
		}

		return nullptr;
	}
	//Searching the Title from Record and returning the BookList's index of that particular Book
	Book* SearchByTitle(char* Title)
	{
		int Length = Helper::StrLen(Title);

		for (int i = 0; i < AvailableBooks; i++)
		{
			if (Title[0] == BookList[i]->Title[0])
			{
				int counter = 1;
				for (int j = 1; j < Length; j++)
				{
					if (Title[j] == BookList[i]->Title[j])
					{
						counter++;
					}
					if (Title[j] != BookList[i]->Title[j])
					{
						j = Length;
					}
					if (counter == Length)
					{
						return BookList[i];
					}
				}
			}
		}

		return nullptr;
	}
	//Searching the Author Name from Recordand returning the BookList's index of that particular Book
	Book** SearchByAuthor(char* Author, int& count)
	{
		int Length = Helper::StrLen(Author);
		Book** Authors = new Book * [AvailableBooks];
		count = 0;

		for (int i = 0; i < AvailableBooks; i++)
		{
			if (Author[0] == BookList[i]->Author[0])
			{
				int counter = 1;
				for (int j = 1; j < Length; j++)
				{
					if (Author[j] == BookList[i]->Author[j])
					{
						counter++;
					}
					if (Author[j] != BookList[i]->Author[j])
					{
						j = Length;
					}
					if (counter == Length)
					{
						Authors[count] = new Book;
						Authors[count] = BookList[i];
						count++;
						//return BookList;
					}
				}
			}
		}

		if (Authors != nullptr)
		{
			return Authors;
		}
		return nullptr;
	}

	//SearchBook function is searching the book a particular book on the desire of the user
	void SearchBook()
	{
		//ReadDataFromFile();
		cout << "1.Search by ID \n2.Seach by Title \n3.Search by Author \n";
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			char ID[4];
			cout << "Enter the ID: ";
			cin >> ID;
			Book* book;
			book = SearchByID(ID);
			if (book != nullptr)
			{
				//cout << "ID\tTitle\t\t\tAuthor\t\t\tQuantity\n";
				cout << book->ID << "\t" << book->Title << "\t" << book->Author << "\t" << book->Quantity << endl;
				delete[] book;
				book = nullptr;
			}
			else
			{
				cout << "ID not Found!!!\n";
			}
		}
		if (choice == 2)
		{
			char Title[100];
			cin.ignore();
			cout << "Enter the Title:";
			cin.getline(Title, 100);

			Book* book;
			book = SearchByTitle(Title);
			if (book != nullptr)
			{
				cout << book->ID << "\t" << book->Title << "\t" << book->Author << "\t" << book->Quantity << endl;
				delete[] book;
				book = nullptr;
			}
			else
			{
				cout << "Title not Found!!!\n";
			}
		}

		if (choice == 3)
		{
			char Author[100];
			cin.ignore();
			cout << "Enter the Author Name:";
			cin.getline(Author, 100);

			Book** book;
			int NoA;
			book = SearchByAuthor(Author, NoA);
			if (book != nullptr)
			{
				for (int i = 0; i < NoA; i++)
				{
					cout << book[i]->ID << "\t" << book[i]->Title << "\t" << book[i]->Author << "\t" << book[i]->Quantity << endl;
				}
				for (int i = 0; i < NoA; i++)
				{
					delete book[i];
				}
				delete[] book;
				book = nullptr;

			}
			else
			{
				cout << "Title not Found!!!\n";
			}
		}


	}

};
//class StudentData is holding the data of Students
class StudentData {

public:
	char* Roll_No;	//Roll No of the Student
	char* First_Name;	//First Name of the Student
	char* Last_Name;	//Last Name of the Student
	char* Password;		//Password of Student Login
};

//class Student is holding the data of Students which ordered the book and who is the currentStudent
class Student : public Library {

	Student** StudentList;	//StudentList keeping the Record of all the Students who bored the book
	StudentData* CurrentStudent;	//CurrentStudent keeps the record who is current logged in
	char* RollNo;	//Roll No of the User
	char* FirstName;	//First Name of the User
	char* LastName;		//Last Name of the Student
	int I_Date, I_Month, I_Year, R_Date, R_Month, R_Year;	//Date of Issue and Date of Return
	int No_OrderedBook;		//Number of Books Ordered

	StudentData** Students;	//Associating with StudentData

public:
	//Loading the Data from the File
	void LoadDatafromFile()
	{
		//Ordered Books
		int counter = 0;
		ifstream file("Students.txt");
		while (!file.eof())
		{
			char temp[400];
			file.getline(temp, 400);
			counter++;
		}
		No_OrderedBook = counter;

		StudentList = new Student * [counter + 1];
		ifstream Refile("Students.txt");
		counter = 0;
		while (!Refile.eof())
		{
			StudentList[counter] = new Student;
			char temp[20];
			Refile >> temp;
			StudentList[counter]->RollNo = Helper::getstringfrombuffer(temp);
			Refile >> temp;
			StudentList[counter]->FirstName = Helper::getstringfrombuffer(temp);
			Refile >> temp;
			StudentList[counter]->LastName = Helper::getstringfrombuffer(temp);
			Refile >> temp;
			StudentList[counter]->OrderdBook = new Book;
			StudentList[counter]->OrderdBook->ID = Helper::getstringfrombuffer(temp);
			Refile >> StudentList[counter]->I_Date;
			Refile >> StudentList[counter]->I_Month;
			Refile >> StudentList[counter]->I_Year;
			Refile >> StudentList[counter]->R_Date;
			Refile >> StudentList[counter]->R_Month;
			Refile >> StudentList[counter]->R_Year;

			counter++;
		}

	}
	//Sign In Function is checking the information which user entered with our database and returning whether it is right information or not
	bool SignIn()
	{
		ifstream Information("StudentUsers.txt");
		char temp[100];
		int counter = 0;
		while (!Information.eof())
		{
			Information.getline(temp, 100);
			counter++;
		}

		ifstream StudentsInformation("StudentUsers.txt");
		
		Students = new StudentData*[counter];
		int count = 0;
		char temporary[100];
		while (!StudentsInformation.eof())
		{
			Students[count] = new StudentData;

			StudentsInformation >> temporary;
			Students[count]->Roll_No = Helper::getstringfrombuffer(temporary);

			StudentsInformation >> temporary;
			Students[count]->First_Name = Helper::getstringfrombuffer(temporary);

			StudentsInformation >> temporary;
			Students[count]->Last_Name = Helper::getstringfrombuffer(temporary);
			
			StudentsInformation >> temporary;
			Students[count]->Password = Helper::getstringfrombuffer(temporary);
			count++;
		}

		char _RollNo[20];
		char _Password[20];
		cout << "Enter the RollNo:";
		cin >> _RollNo;
		cout << "Enter the Password:";
		cin >> _Password;

		int _Length_RollNo = Helper::StrLen(_RollNo);
		int _Length_Password = Helper::StrLen(_Password);

		for (int i = 0; i < counter; i++)
		{
			if (Helper::StrLen(Students[i]->Roll_No) == _Length_RollNo)
			{
				int Roll = 0;
				for (int j = 0; j < _Length_RollNo; j++)
				{
					if (Students[i]->Roll_No[j] == _RollNo[j])
					{
						Roll++;
					}
				}
				int Pass = 0;
				for (int j = 0; j < _Length_Password; j++)
				{
					if (Students[i]->Password[j] == _Password[j])
					{
						Pass++;
					}
				}
				if (Roll == _Length_RollNo && Pass == _Length_Password)
				{
					CurrentStudent = Students[i];
					return true;
				}
			}
		}

		return false;
	}

	//SignUp Function is adding a new user
	bool SignUp()
	{
		ifstream Information("StudentUsers.txt");
		char temp[100];
		int counter = 0;
		while (!Information.eof())
		{
			Information.getline(temp, 100);
			counter++;
		}

		ifstream StudentsInformation("StudentUsers.txt");

		Students = new StudentData * [counter + 1];
		int count = 0;
		char temporary[100];
		while (!StudentsInformation.eof())
		{
			Students[count] = new StudentData;

			StudentsInformation >> temporary;
			Students[count]->Roll_No = Helper::getstringfrombuffer(temporary);

			StudentsInformation >> temporary;
			Students[count]->First_Name = Helper::getstringfrombuffer(temporary);

			StudentsInformation >> temporary;
			Students[count]->Last_Name = Helper::getstringfrombuffer(temporary);

			StudentsInformation >> temporary;
			Students[count]->Password = Helper::getstringfrombuffer(temporary);
			count++;
		}

		char _FirstName[20];
		char _LastName[20];
		char _RollNo[20];
		char _Password[20];
		cout << "Enter your First Good Name:";
		cin >> _FirstName;
		cout << "Enter your Second Name:";
		cin >> _LastName;
		cout << "Enter the RollNo:";
		cin >> _RollNo;
		cout << "Enter the Password:";
		cin >> _Password;

		Students[count] = new StudentData;

		Students[count]->Roll_No = Helper::getstringfrombuffer(_RollNo);

		StudentsInformation >> temporary;
		Students[count]->First_Name = Helper::getstringfrombuffer(_FirstName);

		StudentsInformation >> temporary;
		Students[count]->Last_Name = Helper::getstringfrombuffer(_LastName);

		StudentsInformation >> temporary;
		Students[count]->Password = Helper::getstringfrombuffer(_Password);

		CurrentStudent = Students[count];

		ofstream out("StudentUsers.txt");

		for (int i = 0; i <= count; i++)
		{
			out << Students[i]->Roll_No << "\t";
			out << Students[i]->First_Name << " ";
			out << Students[i]->Last_Name << "\t";
			out << Students[i]->Password;
			out << endl;
		}

		return true;
	}

	//Assignment Operator 
	void operator=(const Student& rhs)
	{
		RollNo = Helper::getstringfrombuffer(rhs.RollNo);
		OrderdBook = new Book;
		OrderdBook->ID = Helper::getstringfrombuffer(rhs.OrderdBook->ID);
		FirstName = Helper::getstringfrombuffer(rhs.FirstName);
		LastName = Helper::getstringfrombuffer(rhs.LastName);
		I_Date = rhs.I_Date;
		I_Month = rhs.I_Month;
		I_Year = rhs.I_Year;
		R_Date = rhs.R_Date;
		R_Month = rhs.R_Month;
		R_Year = rhs.R_Year;
	}
	//Updating the list of Students
	void UpdateStudent(Book* book)
	{
		Student** tempStudent;
		tempStudent = new Student * [No_OrderedBook];

		for (int i = 0; i < No_OrderedBook; i++)
		{
			tempStudent[i] = new Student;
			*tempStudent[i] = *StudentList[i];
		}

		for (int i = 0; i < No_OrderedBook; i++)
		{
			delete StudentList[i];
			StudentList[i] = nullptr;
		}
		delete[] StudentList;

		StudentList = new Student * [No_OrderedBook + 1];

		for (int i = 0; i < No_OrderedBook; i++)
		{
			StudentList[i] = new Student;
			*StudentList[i] = *tempStudent[i];
		}
		StudentList[No_OrderedBook - 1] = new Student;

		StudentList[No_OrderedBook - 1]->RollNo = Helper::getstringfrombuffer(CurrentStudent->Roll_No);
		StudentList[No_OrderedBook - 1]->FirstName = Helper::getstringfrombuffer(CurrentStudent->First_Name);
		StudentList[No_OrderedBook - 1]->LastName = Helper::getstringfrombuffer(CurrentStudent->Last_Name);
		StudentList[No_OrderedBook - 1]->OrderdBook = new Book;
		StudentList[No_OrderedBook - 1]->OrderdBook->ID = Helper::getstringfrombuffer(book->ID);
		StudentList[No_OrderedBook - 1]->I_Date = 20;
		StudentList[No_OrderedBook - 1]->I_Month = 6;
		StudentList[No_OrderedBook - 1]->I_Year = 2021;
		StudentList[No_OrderedBook - 1]->R_Date = 20;
		StudentList[No_OrderedBook - 1]->R_Month = 7;
		StudentList[No_OrderedBook - 1]->R_Year = 2021;

		ofstream out("Students.txt");

		for (int i = 0; i < No_OrderedBook; i++)
		{
			out << StudentList[i]->RollNo;
			out << "\t";
			out << StudentList[i]->FirstName << " ";
			out << StudentList[i]->LastName;
			out << "\t";
			out << StudentList[i]->OrderdBook->ID;
			out << "\t";
			out << StudentList[i]->I_Date << " ";
			out << StudentList[i]->I_Month << " ";
			out << StudentList[i]->I_Year ;
			out << "\t";
			out << StudentList[i]->R_Date << " ";
			out << StudentList[i]->R_Month << " ";
			out << StudentList[i]->R_Year;
			out << endl;
		}


	}

	//Place order will perform it's task if any student place the order of the book
	void PlaceOrder()
	{
		ViewAvailableBooks();
		LoadDatafromFile();

		char ID[4];
		cout << "Enter the ID: ";
		cin >> ID;
		Book* book;
		book = SearchByID(ID);
		if (book != nullptr)
		{
			cout << book->ID << "\t" << book->Title << "\t" << book->Author << "\t" << book->Quantity << endl;
			
			UpdateStudent(book);
			book->Quantity--;
			UpdateBooks();
		}
		else
		{
			cout << "ID not Found!!!\n";
		}

	}
	//Returns the Book and remove from the issued book and addition in the available books
	void ReturnBook()
	{

	}
};
//class Librarian holding the data of Libaray Manager
class Librarian : public Library {

public:
	//Constructor
	Librarian()
	{
		BookList = nullptr;
		AvailableBooks = 0;
	}
	// Sign In Function is checking the information which user entered with our database and returning whether it is right information or not
	bool SignIn()
	{
		ifstream LibrarianInformation("Librarian.txt");

		char UserName[20];
		char Password[20];

		LibrarianInformation >> UserName;
		LibrarianInformation >> Password;

		char _UserName[20];
		char _Password[20];
		cout << "Enter the UserName:";
		cin >> _UserName;
		cout << "Enter the Password:";
		cin >> _Password;

		int Length_UserName = Helper::StrLen(UserName);
		int _Length_UserName = Helper::StrLen(_UserName);
		int Length_Password = Helper::StrLen(Password);
		int _Length_Password = Helper::StrLen(_Password);

		if (Length_UserName == _Length_UserName)
		{
			for (int i = 0; i < Length_UserName; i++)
			{
				if (UserName[i] != _UserName[i])
				{
					cout << "InValid UserName or Password!!!\n";
					return false;
				}
			}
		}
		else
		{
			cout << "InValid UserName or Password!!!\n";
			return false;
		}

		if (Length_Password == _Length_Password)
		{
			for (int i = 0; i < Length_Password; i++)
			{
				if (Password[i] != _Password[i])
				{
					cout << "InValid UserName or Password!!!\n";
					return false;
				}
			}
		}
		else
		{
			cout << "InValid UserName or Password!!!\n";
			return false;
		}

		cout << "\n----------------Successfully Signed IN----------------\n\n";

		cout << "----------------------Librarian Panel-----------------------\n";

		cout << "\nPress 1 to Change Password\nPress any Number for Admin Panel\n";
		int choice ;
		cin >> choice;
		if (choice == 1)
		{
			char NewPassword[20];
			cout << "Enter your New Password:";
			cin >> NewPassword;

			ofstream Write("Librarian.txt");
			Write << UserName;
			Write << endl;
			Write << NewPassword;

			cout << "\n----------------Successfully Password Updated----------------\n\n";

		}

		return true;
	}
	//AddBook adds the Book which Librarian want to add
	void AddBook()
	{
		//ReadDataFromFile();

		Book** tempBooks;
		tempBooks = new Book* [AvailableBooks];

		for (int i = 0; i < AvailableBooks; i++)
		{
			tempBooks[i] = new Book;
			*tempBooks[i] = *BookList[i];
		}

		for (int i = 0; i < AvailableBooks; i++)
		{
			delete BookList[i];
			BookList[i] = nullptr;
		}
		delete[] BookList;

		BookList = new Book * [AvailableBooks + 1];

		for (int i = 0; i < AvailableBooks; i++)
		{ 
			BookList[i] = new Book;
			*BookList[i] = *tempBooks[i];
		}
		BookList[AvailableBooks -1] = new Book;

		char temp[10];
		cout << "Enter the ID:";
		cin >> temp;
		cin.ignore();
		BookList[AvailableBooks -1] ->ID = Helper::getstringfrombuffer(temp);

		char temp2[100];
		cout << "Enter the Title:";
		cin.getline(temp2,100);
		BookList[AvailableBooks -1] ->Title= Helper::getstringfrombuffer(temp2);

		cout << "Enter the Quantity:";
		cin >> BookList[AvailableBooks -1]->Quantity;
		cin.ignore();

		char temp3[100];
		cout << "Enter the Author:";
		cin.getline(temp3, 100);
		BookList[AvailableBooks -1] ->Author = Helper::getstringfrombuffer(temp3);

		UpdateBooks();

		for (int i = 0; i < AvailableBooks; i++)
		{
			delete tempBooks[i];
			tempBooks[i] = nullptr;
		}
		delete[] tempBooks;

	}
	//Edit Book can edit the information of the a particular book
	void EditBook()
	{
		//ReadDataFromFile();
		ViewAvailableBooks();
		char ID[4];
		cout << "Enter the ID: ";
		cin >> ID;
		Book* book;
		book = SearchByID(ID);
		if (book != nullptr)
		{
			cout << book->ID << "\t" << book->Title << "\t" << book->Author << "\t" << book->Quantity << endl;
			cout << "1.Update Title\n2.Update Author\n3.Update Quantity\n";
			int choice;
			cin >> choice;
			if (choice == 1)
			{
				char temp[100];
				cout << "Enter the Title:";
				cin.ignore();
				cin.getline(temp, 100);
				book->Title = Helper::getstringfrombuffer(temp);
			}
			if (choice == 2)
			{
				char temp[100];
				cin.ignore();
				cout << "Enter the Author:";
				cin.getline(temp, 100);
				book->Author = Helper::getstringfrombuffer(temp);
			}
			if (choice == 3)
			{
				cout << "Enter the Quantity:";
				cin >> book->Quantity;
			}

			UpdateBooks();
		}
		else
		{
			cout << "ID not Found!!!\n";
		}
	}
};

//Driving Function
void main()
{
	cout << "_____________________________________________________________________________________" << endl;
	cout << "\t\t\tLibrary Managment System\n";
	cout << "_____________________________________________________________________________________" << endl;
	cout << "\t\t1.Librarian\t\t\t2.Student\n";
	cout << "_____________________________________________________________________________________" << endl;
	int choice;
	cout << "Press 1 for Librarian Interface\nPress 2 for Student Interface\n";
	cout << "----------------------------Enter your Choice:\t";
	cin >> choice;
	//Librarian Interface
	if (choice == 1)
	{
		cout << "\n-------------Enter your UserName and Password for Sign IN-----------------------------\n\n";
		Librarian librarian;
		if (librarian.SignIn())
		{			
			librarian.ReadDataFromFile();
			while (true)
			{
				cout << "\n__________________________________________________________________________________________\n";
				cout << "Press 1 to Add Book\nPress 2 to Search Book\nPress 3 to View Available Books\n" <<
					"Press 4 to Edit Information of Book" << "\nPress 5 to Exit\n";
				cout << "__________________________________________________________________________________________\n";
				int select;
				cout << "--------------Enter your Choice:\t";
				cin >> select;
				while (select < 0 && select > 5)
				{
					cout << "--------------Enter the Correct Choice:\t";
					cout << "1.Add Book\n2.Search Book\n3.View Available Books\n4.Edit Book Information\n";
					cin >> select;
				}
				switch (select)
				{
				case 1:
					librarian.AddBook();
					break;
				case 2:
					librarian.SearchBook();
					break;
				case 3:
					librarian.ViewAvailableBooks();
					break;
				case 4:
					librarian.EditBook();
					break;
				case 5:
					return;

				}
			}
		}		
	}
	//Student Interface
	if (choice == 2)
	{
		Student Students;
		
		cout << "1.SignIn\n2.SignUp\n";
		int choose;
		cin >> choose;
		if (choose == 1 && Students.SignIn())
		{
			cout << "1.View Books List\n2.Search Book\n3.Place Order\n4.Return Book\n";
			int select;
			cin >> select;
			while (select < 0 && select > 5)
			{
				cout << "1.View Books List\n2.Search Book\n3.Place Order\n4.Return Book\n";
				cin >> select;
			}
			switch (select)
			{
			case 1:
				Students.ViewAvailableBooks();
				break;
			case 2:
				Students.SearchBook();
				break;
			case 3:
				Students.PlaceOrder();
				break;
			case 4:
				Students.ReturnBook();
				break;
			case 5:
				return;

			}
		}
		if (choose == 2 && Students.SignUp())
		{
			cout << "1.View Books List\n2.Search Book\n3.Place Order\n4.Return Book\n";
			int select;
			cin >> select;
			while (select < 0 && select > 5)
			{
				cout << "1.View Books List\n2.Search Book\n3.Place Order\n4.Return Book\n";
				cin >> select;
			}
			switch (select)
			{
			case 1:
				Students.ViewAvailableBooks();
				break;
			case 2:
				Students.SearchBook();
				break;
			case 3:
				Students.PlaceOrder();
				break;
			case 4:
				Students.ReturnBook();
				break;
			case 5:
				return;

			}
		}		
	}

	system("pause");
}