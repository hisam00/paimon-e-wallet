/****************************************************
PROJECT C++ S5.[Paimon e-Wallet]
SECTION 38

List of member:
1. MUHAMMAD IZZUDDIN FARHAN BIN
   MUHAMMAD AMMAR FARHAN @BROREY
   A23DW0795

2. MUHAMMAD AZIM KHAN BIN AZIZ KHAN
   A23DW0682

3. NOR HISAMUDIN BIN MANAF
   A23DW0411

4. FAN YING FENG
   A23DW0682
*****************************************************/

#include <iostream>
#include <stdlib.h> //is used for system("cls") command, to clear command prompt
#include <conio.h> //is used for getch() command, to ignore invalid variable
#include <cctype> // is used to check string
#include <fstream>

using namespace std;

/******Functions prototype********/

bool validUsername(string sentence);
bool validPassword(string sentence);
bool checker(string username, string password);
void saver(string user, string pass);

//--------

class CheckBalancePaimon {
public:
    double currentAmount;

    CheckBalancePaimon(double balance) {
        currentAmount = balance;
    }

    void getinfo()  {
        cout << "Balance is: RM " << currentAmount << endl << endl;
    }
};

class Top_UpAmountPaimon : public CheckBalancePaimon {
public:
    double top_UpAmount;

    Top_UpAmountPaimon(double top_Up, double balance) : CheckBalancePaimon(balance) {
        top_UpAmount = top_Up;
        currentAmount += top_UpAmount;
    }

    void getinfo()  {
        cout << "Balance after Top-Up: RM " << currentAmount << endl << endl;
    }
};

class WithdrawAmountPaimon : public CheckBalancePaimon {
private:
    double withdrawAmount;

public:
    WithdrawAmountPaimon(double withdraw, double balance) : CheckBalancePaimon(balance) {
        withdrawAmount = withdraw;
        if (withdrawAmount <= currentAmount)
            currentAmount -= withdrawAmount;
        else
            cout << "Invalid, not enough money." << endl << endl;
    }

    double getWithdrawAmount(){
        return withdrawAmount;
    }

    ~WithdrawAmountPaimon() {
        cout << "\nThis withdrawal was destructed!" << endl << endl;
    }

    void getinfo()  {
        cout << "Balance after withdraw: RM " << currentAmount << endl;
    }
};

void showMenu() {
    cout << "**********Paimon e-wallet Transaction **********" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Top-Up" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Exit" << endl;
    cout << "************************************************" << endl;
}


//--------

int main()
{
    string user[2]; // [0] for username; [1] for password
    char determinant;

	double CurrentBalance = 0.00;
    CheckBalancePaimon balanceMoney(CurrentBalance);
    Top_UpAmountPaimon top_UpMoney(0, CurrentBalance);
    int option;

    do
    {
    	string tries;
        system("cls"); //is used so that everytime this iteration loop, it leave no traces of previous input/output
        cout<< "===== Welcome to Paimon e-wallet =====" << endl << endl;
        cout<< "[1] Sign In\n[2] Create New Account\n[3] Exit" << endl << endl;
        cout<< "Option: ";
        cin>> determinant;

        switch (determinant)
        {
            case '1':
                system("cls");
                cout<< "===== Sign-in =====" << endl << endl;
                cout<< "Username: ";
                cin>> user[0];

                cout<< "Password: ";
                cin>> user[1];

                // check if same or not

                if (checker(user[0],user[1])) {
    				cout << "Login successful!" << endl;
    				getch();
    				goto withdrawal;
    			}
				else{
        			cout << "\nInvalid username or password.\nMaybe you should create new account first." << endl;
    				getch();
				}
				//money function to be added later

                break;

            case '2':
                do
                {
                    system("cls");
                    cout<< "===== Create New Account =====" << endl
						<< "Enter 'exit' to back" << endl << endl;
                    cout<< "Username: ";
                    cin>> tries;
                    user[0] = tries;
                	if(tries == "exit"){break;}

				}
                while(!validUsername(user[0]));
				if(tries == "exit"){break;}

                do
                {
                    system("cls");
                    cout<< "===== Create New Account =====" << endl
                    	<< "Enter 'exit' to back" << endl << endl;
					cout<< "Password: ";
					cin>> tries;
                    user[1] = tries;
                	if(tries == "exit"){break;}
				}
                while(!validPassword(user[1]));
				if(tries == "exit"){break;}

                system("cls");

				// store in file
				saver(user[0],user[1]);
                break;

            case '3':
                return 0;

            default:
                cout<< "\n~~~~~ Invalid option ~~~~~";
                getch(); //allow users time to acknowledge faulty behavior and iterate back
                break;

        }
    }while (determinant != '3');


withdrawal:

	system("cls");

    do {

        showMenu();
        cout << "Option: ";
        cin >> option;
        system("cls");
        switch (option) {
            case 1: {
                balanceMoney.getinfo();
                break;
            }
            case 2: {
                double top_Up;
                cout << "Enter Top-Up amount: ";
                cin >> top_Up;
                top_UpMoney = Top_UpAmountPaimon(top_Up, balanceMoney.currentAmount);
                top_UpMoney.getinfo();
                balanceMoney = top_UpMoney;
                break;
            }
            case 3: {
                double withdraw;
                cout << "\nThis withdrawal is constructing..." << endl << endl;
                cout << "Enter withdraw amount: ";
                cin >> withdraw;
                WithdrawAmountPaimon withdrawMoney(withdraw, balanceMoney.currentAmount);
                withdrawMoney.getinfo();
                balanceMoney = withdrawMoney;
                break;
            }
            case 4: {
        	cout << "Transaction Completed"<< endl << endl;
        	break;
			}
			default: {
        	cout << "Invalid! Please enter again."<< endl << endl;
			}
        }
    } while (option != 4);

    cout << "Balance Account: RM " << balanceMoney.currentAmount << endl;

	if(balanceMoney.currentAmount <= 20){

		cout << endl << "Please Top-up Your Account" << endl;

	}

    return 0;
}

/******Functions used in int main()********/

bool validUsername (string sentence)
{
        int alpha=0, digit=0, symbol=0;

    for (int i=0; i<sentence.length(); i++)
    {
        if (isalpha(sentence[i]))
            alpha++;
        else if (isdigit(sentence[i]))
            digit++;
        else if (!(isalnum(sentence[i]))){
        	symbol++; //alnum --> alpha numeric #check whether the character is alphabet or digit
		}
    }

    if (alpha == 0 || digit == 0 || symbol >= 1)
    {
        //For debugging purpose
        //Comment below line of code if not used
//        cout<< "\n*******DEBUGGING*******" << endl;
//        cout<< "Alpha: " <<alpha << endl << "Digit: " <<digit << endl << "Symbol: " << symbol;
//        cout<< "\n***********************" << endl;

        cout<< "\nYour username must consists of only letter and number.";
        getch();
        return false;
    }
    else
        return true;
}


bool validPassword(string sentence)
{
    int upper=0, lower=0, digit=0, symbol=0, i;

    for ( i=0; i<sentence.length(); i++)
    {
        if (isupper(sentence[i]))
            upper++;
        else if (islower(sentence[i]))
            lower++;
        else if (isdigit(sentence[i]))
            digit++;
        else if (!isspace(sentence[i]))
            symbol++;
    }

    if ((upper >=1) && (lower >= 1) && (digit >= 1) && (symbol >= 1) && (i >= 8))
    {
        return true;
    }
    else
    {
        //For debugging purpose
        //Comment below line of code if not used
//        cout<< "\n*******DEBUGGING*******" << endl;
//        cout<< "Upper: " <<upper << endl << "Lower: " <<lower << endl << "Digit: " <<digit << endl << "Symbol: " <<symbol;
//    	cout<< "\n***********************" << endl;

    	cout<< "\nYour password must contains at least 8 combination of upper case character, lower case character,\nnumber and symbol.";
        getch();
		return false;
    }

}


bool checker(string username, string password) {
    ifstream checker("user.txt");

    if (!checker) {
        cerr << "Error: Unable to open file." << endl;
        return false;
    }

    string user, pass;
    while (checker >> user >> pass) {
        if (user == username && pass == password) {
            checker.close();
            return true;
        }
    }

    checker.close();
    return false;
}


void saver(string user, string pass) {
    ofstream saver("user.txt", ios::app);

    if (!saver) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    saver << user << " " << pass << endl;
    saver.close();

    cout<< "Username: " <<user << endl;
    cout<< "Password: " <<pass << endl << endl;
    cout << "Your data have been saved, you can now login.\nPress enter to continue: " << endl;
    getch();
}

