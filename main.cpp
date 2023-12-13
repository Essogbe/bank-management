#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>


#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif


using namespace std;

class BankAccount{
private:
    string name;
    int accountNum;
    double balance;
    vector <string> transactions ;
public:
    // Constructor
    BankAccount(string n,int ac, double  bal){
        name = n;
        accountNum = ac;
        balance = bal;
    }
    // Setter
    void setName(string n) {
        name = n;
    }
    void setBalance(int newBalance){
        balance = newBalance;
    }


    //Getter
    string getName(){
        return name;
    }
    int getAccountNum(){
        return accountNum;
    }
    double getBalance(){
        return balance ;
    }

    //Other Methods
    void savetransaction(string transactiontype,const double money){
        time_t now; // variable for store datetime format

        time(&now); // get current time

        ostringstream oss;// For concatening many variables,expressions into string

        oss << "Time: " << ctime(&now) << " | " <<"Transaction Type : " <<transactiontype << " | "<< "Money : "  << money<< " | " <<" Bal. : "<< balance ;

        //ctime(&now) ==> convert time into String
        string transaction = oss.str(); // Convert stream into String

        //save
        transactions.push_back(transaction);

}

    void displayTransactions(){

        if (!transactions.empty()) {
            cout << "\t\t**********************************Transactions Info**********************************";
            cout << "\t\t\tAccount Number: " << accountNum << endl;
            for (int i=0 ;i<transactions.size();i++) {

                cout <<"\t\t\tno "<<i+1 <<" ==> "<< transactions[i]<<endl;
            }
            cout << "\t\t**************************************************************************************";
        }
        else{

        cout << "No transactions Found";

    }
    }


    void depositMoney(double money){
        balance +=money;

        cout << "Successful Deposit Operation  . New Balance: "<<balance<<endl;
        this->savetransaction("DEPOSIT",money);
    }

    void withdrawMoney(double taken) {
        if (taken <= balance) {
            balance -= taken;
            this->savetransaction("WITHDRAW",taken);
            cout << "Successful WithDraw Operation  . New Balance: " << balance << endl;
        }
        else
            cout << "Insufficient Balance....";
}};


class BankManagement {
private:
    vector<BankAccount> accounts;

public:
    void AddAccount(string name, int accountNum, double balance) {
        accounts.push_back(BankAccount(name, accountNum, balance));
    }

    void ShowAccount(int i) {
        cout << "Name : " << accounts[i].getName() << "     Account Number : " << accounts[i].getAccountNum()
             << "  Balance : " << accounts[i].getBalance() << endl;
        cout << "\t\t***************INFO***************" << endl;
        cout << "\t\t\t♠ Name : " << accounts[i].getName() << endl;
        cout << "\t\t\t♠ Account Number : " << accounts[i].getAccountNum() << endl;
        cout << "\t\t\t♠ Balance : " << accounts[i].getBalance() << endl;
        cout << "\t\t**********************************" << endl;
    }

    void ShowAllAccounts() {
        cout << "\t\tAll Account Holders" << endl;
        for (int i = 0; i < accounts.size(); i++)
            ShowAccount(i);
    }

    int SearchAccount(int accountnum) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNum() == accountnum)
                return i;
        }
        return -1;
    }

    BankAccount *findAccount(int accountnum) {
        if (this->SearchAccount(accountnum) >= 0) {
            int found = this->SearchAccount(accountnum);
            return &accounts[found];
        }
    }


};



int main() {
    std::cout << "Hello, World!" << std::endl;
    BankManagement bank;
    int choice;
    char option;
    do{
        system(CLEAR_SCREEN);
        cout << "\t\t  Bank Management System" <<  endl;
        cout << "\t\t\tMain Menu" << endl;
        cout << "\t\t 1. Create New Account "<<endl;
        cout << "\t\t 2. Show All Account "<<endl;
        cout << "\t\t 3. Search Account "<< endl;
        cout << "\t\t 4. Deposit  Money"<< endl;
        cout << "\t\t 5. Withdraw Money" << endl;
        cout << "\t\t 6. Display Transactions" << endl;
        cout << "\t\t 7. Exit" << endl;
        cout << "---------------------------------------------"<<endl;
        cout << "\tEnter Your Choice : ";
        cin >> choice;
        switch (choice) {
            case 1:
            {
                string name;
                int accountNum;
                double balance;
                cout << "\t\tEnter Name :";
                cin >> name;
                cout << "\t\tEnter the account number : ";
                cin >> accountNum;
                cout << "\t\tEnter Initial Balance : ";
                cin >> balance;
                bank.AddAccount(name,accountNum,balance);
                cout << "\t\t Account Created Succesfully....."<< endl;
                break;
            }
            case 2:{
                bank.ShowAllAccounts();
                break;
            }
            case 3 : {
                int num;
                int found;

                cout << "\t\tEnter the account number : ";
                cin >>num;
                found= bank.SearchAccount(num);
                if (found >0)
                    bank.ShowAccount(found);
                else
                    cout<< " Account not found ";
                break;
            }
            case 4:
            {
                int num;
                double money;
                cout << "\t\tEnter the account number : ";
                cin >>num;
                BankAccount* account = bank.findAccount(num);
                if (account !=NULL){
                    cout<< "\t\tEnter the money to deposit : ";
                    cin>> money;
                    account->depositMoney(money);
                }
                else
                    cout<< " Account not found ";
                break;
            }
            case 5:
            {
                int num;
                double money;

                cout << "\t\tEnter your account number : ";
                cin >> num;
                BankAccount* account=bank.findAccount(num);
                if (account !=NULL){
                    cout << "Enter the money to withdraw";
                    cin >> money;
                    account->withdrawMoney(money);
                }
                else{
                    cout <<" Account not Found";
                }
                break;
            }
            case 6:
            {
                int num;


                cout << "\t\tEnter your account number : ";
                cin >> num;
                BankAccount* account=bank.findAccount(num);
                if (account !=NULL){

                    account->displayTransactions();
                }
                else{
                    cout <<" Account not Found";
                }
                break;
            }
            case 7:
            {
            option = 'n';
                break;
            }
        }

        cout << "\t\t Do you want to continue [Y/N] ?";
        cin >> option;

    }while(option== 'y' || option =='Y');

    return 0;
}
