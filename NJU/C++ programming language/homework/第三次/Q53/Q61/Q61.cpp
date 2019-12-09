#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;

class Account {
protected:
	double balance;
	string customer_name;
	vector<string> operations;
public:
	string setName(string name) { customer_name = name; }
	double getBalance() { return balance; }
	string getName() { return customer_name; }
	void deposit(double amount) { 
		string op = "deposit $";
		char str[30];
		sprintf_s(str, "%.2f", amount);
		op += str;
		operations.push_back(op);
		balance = balance + amount; 
	}
	void withdraw(double amount) { 
		if (balance == 0) {
			cout << "sumTransactions must be greater than zero" << endl;
			return;
		}
		string op = "withdrawal $";
		char str[30];
		sprintf_s(str, "%.2f", amount);
		op += str;
		operations.push_back(op);

		balance = balance - amount; }
	virtual double getInterest() = 0;
	virtual string getAccountType() = 0;
	vector<string>& getOperations() {
		return operations;
	}
};

class checkAccount :public Account {
public:
	string getAccountType() {
		return "Checking Account";
	}
	double getInterest() {
		return balance * 0.001;
	}
};

class storageAccount :public Account {
public:
	string getAccountType() {
		return "Savings Account";
	}
	double getInterest() {
		if (balance > 1000) {
			return 1000 * 0.001 + (balance - 1000)*0.002;
		}
		else {
			return balance * 0.001;
		}
	}
};

class maxiSavingsAccount :public Account {
public:
	string getAccountType() {
		return "Maxi-Savings Account";
	}
	double getInterest() {
		if (balance <= 1000) {
			return balance * 0.02;
		}
		else if (balance > 1000 && balance <= 2000) {
			return 1000 * 0.02 + (balance - 1000)*0.05;
		}
		else {
			return 1000 * 0.02 + 1000 * 0.05 + (balance - 2000)*0.1;
		}
	}
};

class Customer {
private:
	string cus_name;
	vector<Account*> cus_accounts;

public:
	Customer(string name) :cus_name(name) {}
	void addAccount(Account* account) {
		cus_accounts.push_back(account);
	}
	string getName() { return cus_name; }
	int getAccountsSize() { return cus_accounts.size(); }
	double getInterests() {
		double sum = 0;
		for (int i = 0; i < cus_accounts.size(); i++) {
			sum += cus_accounts[i]->getInterest();
		}
		return sum;
	}
	vector<string>& getAccountOperationsByIndex(int index){
		return cus_accounts[index]->getOperations();
	}
	double getTotalLeft(int index) {
		return cus_accounts[index]->getBalance();
	}
	string getAccountTypeByIndex(int index) {
		return cus_accounts[index]->getAccountType();
	}
};

class Bank {
private:
	vector<Account*> accounts;
	vector<Customer> customers;

	Customer& findCustomer(string name) {
		bool hasName = false;
		int cus_index = 0;
		for (int i = 0; i < customers.size(); i++) {
			if (customers[i].getName() == name) {
				hasName = true;
				cus_index = i;
			}
		}
		if (hasName) {
			return customers[cus_index];
		}
		else {
			cout << "can't found customer:" << name << endl;
			return customers[0];
		}
	}
public:


	void createCustomer(string name) {
		Customer newCus(name);
		customers.push_back(newCus);
	}
	void createAccount(int type) {
		switch (type) {
		case 0: {
			accounts.push_back(new checkAccount());
			break;
		}
		case 1: {
			accounts.push_back(new storageAccount());
			break;
		}
		case 2: {
			accounts.push_back(new maxiSavingsAccount());
			break;
		}
		default: {
			cout << type << "is not a valid account type" << endl;
			break;
		}
		}
	}

	void addToCustomer(int index, string name) {
		findCustomer(name).addAccount(accounts[index]);
	}

	void accountDeposit(int index, double amount) {
		if (amount < 0) {
			cout << "amount must be greater than zero" << endl;
			return;
		}
		accounts[index]->deposit(amount);
	}

	void accountWithdraw(int index, double amount) {
		if (amount < 0) {
			cout << "amount must be greater than zero" << endl;
			return;
		}
		accounts[index]->withdraw(amount);
	}

	double getSumBalance(int index) {
		return accounts[index]->getBalance();
	}

	int getNumOfAccount(string name) {
		return findCustomer(name).getAccountsSize();
	}

	double getInterestEarned(string name) {
		return findCustomer(name).getInterests();
	}

	void getStatement(string name) {
		cout << "Statement for " + name << endl << endl;
		Customer tempCus = findCustomer(name);
		double sumTotal = 0;
		for (int i = 0; i < tempCus.getAccountsSize(); i++) {
			vector<string> ops = tempCus.getAccountOperationsByIndex(i);
			cout<< tempCus.getAccountTypeByIndex(i) << endl;
			for (int j = 0; j < ops.size(); j++) {
				cout << " " << ops[j]<< endl;
			}
			double total = tempCus.getTotalLeft(i);
			sumTotal += total;
			char str[20];
			string s = "Total $";
			sprintf_s(str, "%.2f", total);
			s += str;
			cout << s << endl << endl;
		}
		string s = "Total In All Accounts $";
		char str[20];
		sprintf_s(str, "%.2f", sumTotal);
		s += str;
		cout << s << endl;
		
	}

	double getBankTotalInterestPaid() {
		double sum = 0;
		for (int i = 0; i < customers.size(); i++) {
			sum += customers[i].getInterests();
		}
		return sum;
	}

	void customerSum() {
		cout << "Customer Summary" << endl;
		for (int i = 0; i < customers.size(); i++) {
			int num = customers[i].getAccountsSize();
			string name = customers[i].getName();
			if (num != 1) {
				cout << "- " << name << " (" << num << " accounts)" << endl;
			}
			else {
				cout << "- " << name << " (" << num << " account)" << endl;
			}
		}
		cout << endl;
	}
};

vector<string>& splitSpace(vector<string>& tokens, string s) {
	//vector<string> tokens;
	string token;
	stringstream ss(s);
	while (getline(ss, token, ' ')) {
		tokens.push_back(token);
	}
	return tokens;
}

int main() {
	string command;
	Bank bank;
	//ofstream outfile("E:\\input.txt", ios::app);
	//for (int i = 0; i < 20; i++) {
	//	getline(cin, command);
	//	outfile << command << endl;
	//}
	//outfile << endl << endl;

	while (getline(cin, command)) {
		vector<string> commandList;
		splitSpace(commandList, command);

		if (command == "end") {
			break;
		}
		if (commandList[0] == "createAccount") {
			bank.createAccount(stoi(commandList[1]));
		}
		else if (commandList[0] == "createCustomer") {
			bank.createCustomer(commandList[1]);
		}
		else if (commandList[0] == "addToCustomer") {
			bank.addToCustomer(stoi(commandList[1]), commandList[2]);
		}
		else if (commandList[0] == "accountDeposit") {
			bank.accountDeposit(stoi(commandList[1]), stof(commandList[2]));
		}
		else if (commandList[0] == "accountWithdraw") {
			bank.accountWithdraw(stoi(commandList[1]), stof(commandList[2]));
		}
		else if (commandList[0] == "customsum") {
			bank.customerSum();
		}
		else if (commandList[0] == "banktotalInserstPaid") {
			double res = bank.getBankTotalInterestPaid();
			printf("%.1f\n", res);

		}
		else if (commandList[0] == "getStatement") {
			bank.getStatement(commandList[1]);
		}
		else if (commandList[0] == "sumTransactions") {
			double res = bank.getSumBalance(stoi(commandList[1]));
			printf("%.1f\n", res);

		}
		else if (commandList[0] == "totalInterestEarned") {
			double res = bank.getInterestEarned(commandList[1]);
			printf("%.1f\n",res);
		
		}
		else {
			cout << "not a valid command" << endl;
		}
	}
	return 0;
}