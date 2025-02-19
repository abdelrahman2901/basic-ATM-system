#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>  
using namespace std;
const string clientfile = "clients.txt";
const string seperator = "#//#";
void login();

struct stclient {
	string accountnumber, pincode;
	double accountbalance;
};
enum enATMmainmenuscreen{enquickwithdraw=1,normalwithdraw=2,deposit=3,checkbalance=4,logout=5};

vector<string> splitstring(string line) {
	vector<string>vstring;
	string sword;
	short pos = 0;
	while ((pos = line.find(seperator)) != string::npos) {
		sword = line.substr(0, pos);
		if (sword != seperator) {
			vstring.push_back(sword);
		}
		line.erase(0, pos + seperator.length());
	}
	if (line != seperator) {
		vstring.push_back(line);
	}
	return vstring;
}
string convertline(stclient &client) {
	string line = "";
	line += client.accountnumber + seperator;
	line += client.pincode+ seperator;
	line += to_string(client.accountbalance);
	return line;
}

stclient fillclientdata(string line) {
	stclient client;
	vector<string>vstring = splitstring(line);
	client.accountnumber = vstring[0];
	client.pincode = vstring[1];
	client.accountbalance = stod(vstring[2]);
	return client;
}

stclient fillstructwithclientdata(vector<stclient>&vclient,string accnum) {
	stclient client;
	for (stclient& c : vclient) {
		if (c.accountnumber == accnum) {
			client = c;
		}
	}
	return client;
}
vector<stclient> loadvectorfromfile() {
	fstream myfile;
	string line;
	vector<stclient>vclient;
	myfile.open(clientfile, ios::in);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			vclient.push_back(fillclientdata(line));
		}
		myfile.close();
	}
	else {
		cout << "\nfile not found\n";
	}
	return vclient;
}

void saveclientdata(vector<stclient>vclient) {
	fstream myfile;
	myfile.open(clientfile, ios::out);
	if (myfile.is_open()) {
		for (stclient& c : vclient) {
			myfile << convertline(c) << endl;
		}
		myfile.close();
	}
	
	else {
		cout << "\nfile is not found.\n";
	}

}

bool isaccountnumberexists(vector<stclient>& vclient, string accountnumber) {
	for (stclient& c : vclient) {
		if (c.accountnumber == accountnumber) {
			return true;
		}
	}
	return false;
}

bool isloginvalid(vector<stclient>& vclient, string accnum, string pincode) {
	for (stclient& c : vclient) {
		if (c.accountnumber == accnum && c.pincode == pincode) {
			return true;
		}
	}
	cout << "\ninvalid accnumber/pincode , try again.\n";
	return false;
}
string readaccoutnumber() {
	string accnum;
	cout << "\nenter accountnumber ? ";
		getline(cin >> ws, accnum);		
	return accnum;
}
string readpincode() {
	string pincode;
	cout << "\nenter pincode ? ";
	getline(cin >> ws,pincode);
	return pincode;

}
void printloginscrean(vector<stclient>&vclient,stclient &loggedinclient) {
	string accnum,pincode;
	cout << "\n======================================\n";
	cout << "\t\tLOGIN SCREEN\n";
	cout << "\n======================================\n";
	do {
		accnum = readaccoutnumber();
		pincode = readpincode();
		if (isloginvalid(vclient, accnum, pincode)) {
			
			for (stclient& c : vclient) {
				if (c.accountnumber == accnum && c.pincode == pincode) {
					loggedinclient = c;
					break;
				}
			}
			return;
		}
	} while (true);
}

short readmainmenuenumber() {
	short choice;
	do {
		cout << "choose what do you want to do ? [ 1 - 5 ] ? ";
		cin >> choice;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
			cout << "invalid number , enter valid number. [1 - 5 ]\n";
			cin >> choice;
		}
		if (choice < 1 || choice>5) {
			cout << "invalid number \n\n";
	}
	} while (choice < 0 || choice>5);
	return choice;
}

short readATMmainmenue() {
	short choice;
	cout << "============================================================\n";
	cout << "\t\t\tATM Main Menue Screen\n";
	cout << "============================================================\n";
	cout << "\t[1] QUick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "============================================================\n";
	choice=	readmainmenuenumber();
	return choice;
}

short readqickwithdrawchoice() {
		short choice;
		do {
			cout << "choose what do you want to do ? [ 1 - 9 ] ? ";
			cin >> choice;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
				cout << "invalid number , enter valid number. [1 - 9 ] ? \n";
				cin >> choice;
			}
			if (choice < 0 || choice>9) {
				cout << "\ninvalid number \n\n";
			}
		} while (choice < 1 || choice>9);
		return choice;
	}

enum enwithdrawchoice{one=1,two=2,three=3,four=4,five=5,six=6,seven=7,eight=8,nine=9};
short printquickwithdrawoptions(stclient client) {
	short choice;
	cout << "=====================================================\n";
	cout << "\t\t\tQuick Withdraw\n";
	cout << "=====================================================\n";
	cout << "\t[1] 20             [2] 50\n";
	cout << "\t[3] 100             [4] 200\n";
	cout << "\t[5] 400             [6] 600\n";
	cout << "\t[7] 800             [8] 1000\n";
	cout << "\t[9] exit \n";
	cout << "=====================================================\n";
	cout << "your balance is " << client.accountbalance << endl;
	choice = readqickwithdrawchoice();
	return choice;
}

bool withdrawbalance(vector<stclient>&vclient,stclient &client,double number) {
	for (stclient& c : vclient) {
		if (c.accountnumber == client.accountnumber) {
			c.accountbalance -= number;
			client = c;
			cout << "\nwithdraw done succefully your current balance : " << c.accountbalance<<endl;
			return true;
		}
	}
	return false;
	
}
void checktoconfirmwithdraw(vector<stclient>&vclient,stclient &client,double number) {
	char answer = 'n';
	cout << "\nare you sure you want to do this transaction ? Y/N? ";cin >> answer;
	if (toupper(answer) == 'Y') {
		withdrawbalance(vclient,client,number);
			saveclientdata(vclient);
			vclient = loadvectorfromfile();
	}
	else {
		cout << "\naction calnceled\n";
	}
}
void Quickwithdraw(vector<stclient>&vclient,stclient &client) {

		enwithdrawchoice userchoice = enwithdrawchoice(printquickwithdrawoptions(client));

		switch (userchoice) {

		case(enwithdrawchoice::one): {
			checktoconfirmwithdraw(vclient, client,20);
		
			break;
		}
		case(enwithdrawchoice::two): {
			checktoconfirmwithdraw(vclient, client,50);
			break;

		}
		case(enwithdrawchoice::three): {
			checktoconfirmwithdraw(vclient, client,100);
			break;

		}
		case(enwithdrawchoice::four): {
			checktoconfirmwithdraw(vclient, client,200);
			break;

		}
		case(enwithdrawchoice::five): {
			checktoconfirmwithdraw(vclient, client,400);
			break;
		}
		case(enwithdrawchoice::six): {
			checktoconfirmwithdraw(vclient, client,600);
			break;

		}
		case(enwithdrawchoice::seven): {
			checktoconfirmwithdraw(vclient, client,800);
			break;

		}
		case(enwithdrawchoice::eight): {
			checktoconfirmwithdraw(vclient, client,1000);
			break;

		}
		case(enwithdrawchoice::nine): {
			system("cls");
			return;
			break;
		}
		}
	}

bool numbervalidation(int number) {
	return number % 5 == 0 ? true : false;
}
int withdrawingnumber() {
	int number;
	do {
		cout << "enter amount multiply of 5's ? ";
		cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
			cout << "invalid number , enter valid number\n";
			cin >> number;
		}
		
	} while (number <0 );
	return number;
}

void normalwithdrawing(vector<stclient>& vclient, stclient& client) {
	char answer = 'n';
	int number = withdrawingnumber();
	if (client.accountbalance > number) {
		if (numbervalidation(number)) {
			checktoconfirmwithdraw(vclient, client, number);
		}
		else {
			normalwithdrawing(vclient,client);
		}
	}
	else {
		cout << "\nnumber exceeds your balance enter another balance ? Y/N?  ";
		cin >> answer;
		if (toupper(answer) == 'Y') {
			
			normalwithdrawing(vclient, client);
		}
		else {
			return;
		}
	}
}
void normalwithdrawingtransaction(vector<stclient>& vclient, stclient& client) {
	cout << "=======================================\n";
	cout << "\t\tNormal withdrawing Screen\n";
	cout << "=======================================\n";
	normalwithdrawing(vclient, client);
}

int readpositivenumber() {
	int number;
	do {
		cout << "enter a positive number to deposit ? ";cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');
			cout << "invalid number , enter valid number\n";
			cin >> number;
		}

	} while (number < 0);
	return number;
}
bool deposittheamount(vector<stclient>&vclient,stclient &client,int number) {
	for (stclient& c : vclient) {
		if (c.accountnumber == client.accountnumber) {
			c.accountbalance += number;
			 client=c;
			 return true;
		}
	}
	return false;
}
void checktoconfirmdeposit(vector<stclient>& vclient, stclient& client, int number) {
	char answer = 'n';
	cout << "\nare you sure you want to do this transaction ? Y/N? ";cin >> answer;
	if (toupper(answer) == 'Y') {
		deposittheamount(vclient,client,number);
		saveclientdata(vclient);
		vclient = loadvectorfromfile();
		cout << "\ndeposit done successfuly , your current deposit : " << client.accountbalance<<endl;
	}
	else {
		cout << "\naction calnceled\n";
	}
}
void deposittransaction(vector<stclient>& vclient, stclient& client) {
	cout << "=========================================================\n"
		;		cout << "\t\tDeposit Screan\n";
	cout << "=========================================================\n";

		int number=readpositivenumber();
		checktoconfirmdeposit(vclient, client, number);
}


void checkclientbalance(stclient &client) {
	cout << "==============================================\n";
	cout << "\t\t Check Balance\n";
	cout << "==============================================\n";
	cout << "your balance is : " << client.accountbalance;
}

bool askuser() {
	char answer = 'n';
	cout << "do you want to log in again ? Y/N ? ";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		return true ;
	}
	return false;
}

void ATMmainmenue() {
	stclient loggedinclient;
	vector<stclient>vclient = loadvectorfromfile();
	if (!vclient.empty()) {
	printloginscrean(vclient,loggedinclient);
	system("cls");
	
		while (true) {
			enATMmainmenuscreen userchoice = (enATMmainmenuscreen)readATMmainmenue();
			switch (userchoice) {
			case(enATMmainmenuscreen::enquickwithdraw): {
				system("cls");
				Quickwithdraw(vclient, loggedinclient);
				loggedinclient = fillstructwithclientdata(vclient, loggedinclient.accountnumber);
				break;
			}
			case(enATMmainmenuscreen::normalwithdraw): {
				system("cls");
				normalwithdrawingtransaction(vclient, loggedinclient);
				loggedinclient = fillstructwithclientdata(vclient, loggedinclient.accountnumber);
				break;
			}
			case(enATMmainmenuscreen::deposit): {
				system("cls");
				deposittransaction(vclient, loggedinclient);
				loggedinclient = fillstructwithclientdata(vclient, loggedinclient.accountnumber);
				break;

			}
			case(enATMmainmenuscreen::checkbalance): {
				system("cls");
				checkclientbalance(loggedinclient);
				break;
			}
			case(enATMmainmenuscreen::logout): {
				system("cls");
				if (askuser()) {
					system("cls");
					login();
				}
				else {
					system("cls");
					cout << "====================================\n";
					cout << "\tProgram ends ^^\n";
					cout << "====================================\n";
					return;
				}
				break;
			}
			}

			cout << "\nclick enter to go back to the main menue...\n";
			cin.ignore();
			cin.get();
			system("cls");

		}
	}
	else {
		cout << "\nfile is empty.\n";
	}
}

void login() {
	
	
	ATMmainmenue();
}

int main()
{
	login();
}

