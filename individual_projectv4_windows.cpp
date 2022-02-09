#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;

void header();
void pause();
void banner(string);
int mainMenu();
int adminMenu();
int userMenu();
int customerMenu();
void statusOfStocks();
void transactions();
bool newStock(string, int);
bool newItem(string, int, int);
bool isValidEMAIL(string);
bool addEmail(string);
void receptionistOrder(string, int);
bool decreaseStock(string, int);
void customerOrder(string, int);
void productReturn(string, int, bool, string);
int productPrice(string);
void listItems();
bool addFeedback(string);
bool addReturn(int, string);
int getItemIndex(string);
int getMaxIndex(int[], int);
void sortArray(int[]);
void swap(int, int);
void load();
void store();
string getField(string, int);
int convertToInt(string);
void drugDealerLicense();
void listFeedbacks();
void listReturns();
bool redeemCoupon(int);
int generateCoupon(int);

const int MAX_ITEMS = 30;
string itemNames[MAX_ITEMS];
int itemPrices[MAX_ITEMS];
int itemCounts[MAX_ITEMS];
int itemSold[MAX_ITEMS];
int nStocks = 0;

string feedbackBox[MAX_ITEMS];
int feedbackCount = 0;

string orderReturns[MAX_ITEMS];
int returnCount = 0;

string emails[MAX_ITEMS];
int emailCount = 0;

int tmpInt, totalCash = 0, couponAmout = 0;
string tmpString;

int main(){
	int option;
	string reasonReturn;

	load();
	while(true){
		header();
		
		option = mainMenu();

		if(option == 1){
			while(true){
				option = adminMenu();

				if(option == 1){
					banner("User > Manager > Status of stocks");
					statusOfStocks();
				}
				else if(option == 2){
					banner("User > Manager > Transactions");
					transactions();
				}
				else if(option == 3){
					banner("User > Manager > New stocks");

					cout << "Drug Name: ";
					cin >> tmpString;
					cout << "Stock Quantity: ";
					cin >> tmpInt;

					if(!newStock(tmpString, tmpInt)){
						cout << tmpString << " not found in stock" << endl;
					}
				}
				else if(option == 4){
					banner("User > Manager > New item");

					cout << "Drug Name: ";
					cin >> tmpString;
					cout << "Price: ";
					cin >> tmpInt;
					cout << "Stock Quantity: ";
					cin >> option;

					if(!newItem(tmpString, tmpInt, option)){
						cout << "We cannot add more new items" << endl;
					}
				}
				else if(option == 5){
					banner("User > Manager > Drug Dealer License");
					
					drugDealerLicense();
				}
				else if(option == 6){
					banner("User > Manager > Feedback Box");
					listFeedbacks();
				}
				else if(option == 7){
					banner("User > Manager > Returns");
					listReturns();
				}
				else if(option == 8) {
					break;
				}
				else {
					cout << "Invalid option" << endl;
				}

				pause();
			}
		}
		else if(option == 2){
			while(true){
				option = userMenu();

				if(option == 1){
					banner("User > Receptionist > Order");

					cout << "Item Name: ";
					cin >> tmpString;

					tmpInt = getItemIndex(tmpString);

					if(tmpInt != -1){
						cout << "Quantity: ";
						cin >> tmpInt;

						receptionistOrder(tmpString, tmpInt);
					}
					else {
						cout << tmpString << " is not available here" << endl;
					}
				}
				else if(option == 2){
					banner("User > Receptionist > Decrease stocks");

					cout << "Item Name: ";
					cin >> tmpString;
					cout << "Quantity: ";
					cin >> tmpInt;

					if(!decreaseStock(tmpString, tmpInt)){
						cout << tmpString << " not found in stock" << endl;
					}
				}
				else if(option == 3){
					banner("User > Receptionist > Increase cash");
					cout << "Extra cash: ";
					cin >> tmpInt;

					totalCash += tmpInt;
				}
				else if(option == 4){
					banner("User > Receptionist > Redeem coupon");
					
					cout << "Coupon: ";
					cin >> tmpInt;

					if(redeemCoupon(tmpInt)){
						cout << "Your coupon has been added for Rs. " << couponAmout << "/-" << endl;
					}
					else {
						cout << "Invalid coupon" << endl;
					}
				}
				else if(option == 5){
					banner("User > Receptionist > Generate coupon");
					
					cout << "Amount: ";
					cin >> tmpInt;

					tmpInt = generateCoupon(tmpInt);

					if(tmpInt){
						cout << "Coupon: " << tmpInt << endl;
					}
					else {
						cout << "Invalid amout" << endl;
					}
				}
				else if(option == 6){
					break;
				}
				else {
					cout << "Invalid option" << endl;
				}

				pause();
			}
		}
		else if(option == 3){
			while(true){
				option = customerMenu();

				if(option == 1){
					banner("User > Customer > Buy product");

					listItems();
					sortArray(itemSold);
					if(nStocks > 0){
						cout << "Recommended Item: " << itemNames[0] << endl;
					}

					cout << "Item Name: ";
					cin >> tmpString;

					tmpInt = getItemIndex(tmpString);

					if(tmpInt != -1){
						cout << "Quantity: ";
						cin >> tmpInt;

						customerOrder(tmpString, tmpInt);
					}
					else {
						cout << tmpString << " is not available here" << endl;
					}
				}
				else if(option == 2){
					banner("User > Customer > Drug dealer license");
					
					cout << "The manager is not available right now" << endl;
					cout << "Please provide us your email: ";
					cin >> tmpString;

					if(!addEmail(tmpString)){
						cout << "Something went wrong" << endl;
					}
					else {
						cout << "You'll receive a copy of the license in your mail" << endl;
					}

					pause();
				}
				else if(option == 3){
					banner("User > Customer > Redeem coupon");
					
					cout << "Coupon: ";
					cin >> tmpInt;

					if(redeemCoupon(tmpInt)){
						cout << "Your coupon has been added for Rs. " << couponAmout << "/-" << endl;
					}
					else {
						cout << "Invalid coupon" << endl;
					}
				}
				else if(option == 4){
					banner("User > Customer > Return");

					cout << "Product name: ";
					cin >> tmpString;

					tmpInt = getItemIndex(tmpString);

					if(tmpInt != -1){
						cout << "Quantity: ";
						cin >> tmpInt;
						// getchar();
						cout << "Reason of return: ";
						getline(cin, reasonReturn);

						cout << "What do you want?" << endl
							<< "1. Cash" << endl
							<< "2. Coupon" << endl;
						cin >> option;

						if(option == 1){
							productReturn(tmpString, tmpInt, true, reasonReturn);
						}
						else {
							productReturn(tmpString, tmpInt, false, reasonReturn);
						}
					}
					else {
						cout << "We don't sale " << tmpString << endl;
					}
				}
				else if(option == 5){
					banner("User > Customer > Product price");

					cout << "Product name: ";
					cin >> tmpString;

					tmpInt = productPrice(tmpString);

					if(tmpInt != 0){
						cout << "Price: Rs. " << tmpInt << "/-" << endl;
					}
					else {
						cout << "We don't have " << tmpString << endl;
					}
				}
				else if(option == 6){
					banner("User > Customer > List of items");

					listItems();                    
				}
				else if(option == 7){
					banner("User > Customer > Feedback");
					cout << "Enter feedback: ";
					getline(cin, tmpString);

					if(!addFeedback(tmpString)){
						cout << "Something went wrong" << endl;
					}
					else {
						cout << "Your feedback has been added" << endl;
					}
				}
				else if(option == 8){
					break;
				}
				else {
					cout << "Invalid option";
				}
				
				pause();
			}
		}
		else if(option == 4){
			break;
		}
		else {
			cout << "Invalid option" << endl;
		}
		pause();
	}
	store();
}

void pause(){
	// system("pause");
	getchar();
	// getchar();
}

void header(){
	system("clear");
	cout << "┌──────────────────────────────────────────────────────────┐" << endl
		 << "│                Pharmacy Management System                │" << endl
		 << "└──────────────────────────────────────────────────────────┘" << endl << endl;
}

void banner(string s){
	header();
	cout << s << endl
		<< "────────────────────────────────────────────────────────────" << endl;
}

int mainMenu(){
	int opt;

	cout << "Select User: " << endl
		<< "1. Manager" << endl
		<< "2. Receptionist" << endl
		<< "3. Customer (self-service)" << endl
		<< "4. Exit" << endl;
	cin >> opt;
	// getchar();

	return opt;
}

int adminMenu(){
	int opt;

	banner("User > Manager");
	cout << "1. Check status of stocks" << endl
		<< "2. Check total cash" << endl
		<< "3. Add new stocks" << endl
		<< "4. Add new items" << endl
		<< "5. Show drug dealer license" << endl
		<< "6. Look at feedbacks" << endl
		<< "7. Look at returned orders" << endl
		<< "8. Go back to main menu" << endl;
	cin >> opt;
	// getchar();

	return opt;
}

int userMenu(){
	int opt;

	banner("User > Receptionist");
	cout << "1. Place customer's order" << endl
		<< "2. Decrease stocks" << endl
		<< "3. Increase cash amount" << endl
		<< "4. Redeem coupon" << endl
		<< "5. Give coupons or cash for return of orders" << endl
		<< "6. Go back to main menu" << endl;
	cin >> opt;
	// getchar();

	return opt;
}

int customerMenu(){
	int opt;

	banner("User > Customer");
	cout << "1. Buy product" << endl
		<< "2. Ask for drug dealer license" << endl
		<< "3. Redeem coupon" << endl
		<< "4. Return product" << endl
		<< "5. Check price of product" << endl
		<< "6. Get list of items available" << endl
		<< "7. Add feedback" << endl
		<< "8. Go back to main menu" << endl;
	cin >> opt;
	// getchar();

	return opt;
}

void statusOfStocks(){
	if(nStocks != 0){
		sortArray(itemCounts);

		for(int i = 0; i < nStocks; i++){
			cout << itemNames[i] << ": " << itemCounts[i] << endl;
		}
	}
	else {
		cout << "No item in stock" << endl;
	}
}

void transactions(){
	if(nStocks != 0){
		sortArray(itemSold);

		for(int i = 0; i < nStocks; i++){
			cout << itemNames[i] << ": " << itemSold[i] << endl; 
		}
	}
	else {
		cout << "No item sold" << endl;
	}

	cout << "Total Cash: Rs. " << totalCash << "/-" << endl;
}

bool newStock(string drugName, int drugCount){
	int idx = getItemIndex(drugName);

	if(idx != -1){
		itemCounts[idx] += drugCount;
		return true;
	}
	else {
		return false;
	}
}

bool newItem(string drugName, int price, int count){
	if(nStocks < MAX_ITEMS){
		
		itemNames[nStocks] = drugName;
		itemPrices[nStocks] = price;
		itemCounts[nStocks] = count;

		nStocks++;
		return true;
	}
	else {
		return false;
	}

}

bool isValidEMAIL(string text){
	int atIndex = -1, dotIndex = -1;

	for(int i = 0; i < text.length(); i++){
		if(text[i] == '@'){
			atIndex = i;
			break;
		}
	}

	if(atIndex != -1){
		for(int i = atIndex; i < text.length(); i++){
			if(text[i] == '.'){
				dotIndex = i;
				break;
			}
		}
	}

	if(atIndex != -1 && dotIndex != -1){
		return true;
	}

	return false;
}

bool addEmail(string email){
	if(isValidEMAIL(email) && emailCount < MAX_ITEMS){
		emails[emailCount] = email;
		emailCount++;
		return true;
	}
	else {
		return false;
	}
}

void receptionistOrder(string drugName, int qty){
	int idx = getItemIndex(drugName);
	int total = 0;

	if(idx != -1){
		if(qty > itemCounts[idx]){
			cout << "We don't have that much in stock" << endl;
		}
		else {
			itemCounts[idx] -= qty;
			itemSold[idx] += qty;
			total = qty * itemPrices[idx];
		}
	}
	
	if(total != 0){
		cout << "Your total is Rs. " << total << "/-"<< endl;

		if(couponAmout != 0){
			cout << "Do you want to use your coupon on this order? (y/n): ";
			cin >> tmpString;

			if(tmpString == "y"){
				if(couponAmout > total){
					couponAmout -= total;
					total = 0;
				}
				else {
					total -= couponAmout;
					couponAmout = 0;
				}

				cout << "Your new total is Rs. " << total << "/-"<< endl;
			}
		}

		totalCash += total;
	}
}

bool decreaseStock(string drugName, int qty){
	int idx = getItemIndex(drugName);

	if(idx != -1){
		itemCounts[idx] -= qty;
		return true;
	}
	else {
		return false;
	}
}

void customerOrder(string drugName, int qty){
	int idx = getItemIndex(drugName);
	int total = 0;

	if(idx != -1){
		if(qty > itemCounts[idx]){
			cout << "We don't have that much in stock" << endl;
		}
		else {
			itemCounts[idx] -= qty;
			itemSold[idx] += qty;
			total = qty * itemPrices[idx];
		}
	}
	
	if(total != 0){
		cout << "Your total is Rs. " << total << "/-"<< endl;

		if(couponAmout != 0){
			cout << "Do you want to use your coupon on this order? (y/n): ";
			cin >> tmpString;

			if(tmpString == "y"){
				if(couponAmout > total){
					couponAmout -= total;
					total = 0;
				}
				else {
					total -= couponAmout;
					couponAmout = 0;
				}

				cout << "Your new total is Rs. " << total << "/-"<< endl;
			}
		}

		totalCash += total;
	}
}

void productReturn(string drugName, int qty, bool cash, string reason){
	int idx = getItemIndex(drugName);

	if(idx != -1){
		qty *= itemPrices[idx];

		if(cash == true){
		cout << "Here's your Rs. " << qty << "/- return amount" << endl;
		totalCash -= qty;
		}
		else {
			qty += 123456;

			cout << "Coupon: " << qty << endl;
		}

		addReturn(idx, reason);
	}
}

bool addReturn(int index, string reason){
	if(returnCount < MAX_ITEMS){
		orderReturns[returnCount] = itemNames[index] + " was returned because of " + reason;
		returnCount++;
		return true;
	}
	else {
		return false;
	}
}

void listItems(){
	sortArray(itemCounts);

	tmpInt = 0;
	for(int i = 0; i < nStocks; i++){
		if(itemCounts[i] != 0){
			cout << tmpInt + 1 << ". " << itemNames[i] << endl;
			tmpInt++;
		}
	}
}

int productPrice(string drugName){
	int idx = getItemIndex(drugName);

	if(idx != -1){
		return itemPrices[idx];
	}
	
	return 0;
}

bool addFeedback(string feedback){
	if(feedbackCount < MAX_ITEMS){
		feedbackBox[feedbackCount] = feedback;
		feedbackCount++;
		return true;
	}
	else {
		return false;
	}
}

int getItemIndex(string name){
	for(int i = 0; i < nStocks; i++){
		if(itemNames[i] == name){
			return i;
		}
	}

	return -1;
}

void sortArray(int array[]){
	for(int i = 0; i < nStocks; i++){
		swap(i, getMaxIndex(array, i));
	}
}

int getMaxIndex(int array[], int start){
	int max = start;

	for(int i = start; i < nStocks; i++){
		if(array[i] > array[max]){
			max = i;
		}
	}

	return max;
}

void swap(int idx1, int idx2){
	tmpString = itemNames[idx1];
	itemNames[idx1] = itemNames[idx2];
	itemNames[idx2] = tmpString;

	tmpInt = itemPrices[idx1];
	itemPrices[idx1] = itemPrices[idx2];
	itemPrices[idx2] = tmpInt;

	tmpInt = itemCounts[idx1];
	itemCounts[idx1] = itemCounts[idx2];
	itemCounts[idx2] = tmpInt;

	tmpInt = itemSold[idx1];
	itemSold[idx1] = itemSold[idx2];
	itemSold[idx2] = tmpInt;
}

void store(){
	fstream file;

	file.open("projectData.txt", ios::out);

	for (int i = 0; i < nStocks; i++) {
		file << itemNames[i] << ","
			<< itemPrices[i] << ","
			<< itemCounts[i] << ","
			<< itemSold[i] << endl;
	}

	file << endl;
	
	for (int i = 0; i < feedbackCount; i++) {
		file << feedbackBox[i] << endl;
	}

	file << endl;

	for (int i = 0; i < returnCount; i++){
		file << orderReturns[i] << endl;
	}

	file << endl;

	for (int i = 0; i < emailCount; i++){
		file << emails[i] << endl;
	}

	file.close();
}

void load(){
	fstream file;
	string line = "";
	nStocks = 0;
	feedbackCount = 0;
	returnCount = 0;
	emailCount = 0;

	file.open("projectData.txt", ios::in);
	while(!file.eof()){
		getline(file, line);

		if(line == ""){
			break;
		}

		itemNames[nStocks] = getField(line, 0);
		itemPrices[nStocks] = convertToInt(getField(line, 1));
		itemCounts[nStocks] = convertToInt(getField(line, 2));
		itemSold[nStocks] = convertToInt(getField(line, 3));
		nStocks++;
	}

	while(!file.eof()){
		getline(file, line);

		if(line == ""){
			break;
		}

		feedbackBox[feedbackCount] = line;
		feedbackCount++;
	}

	while(!file.eof()){
		getline(file, line);

		if(line == ""){
			break;
		}

		orderReturns[returnCount] = line;
		returnCount++;
	}

	while(!file.eof()){
		getline(file, line);

		if(line == ""){
			break;
		}

		emails[emailCount] = line;
		emailCount++;
	}

	file.close();
}

string getField(string record, int field){
	int seps = 0;
	string ret = "";
	char sep = ',';

	for(int i = 0; i < record.length(); i++){
		if(record[i] == sep){
			seps++;
			continue;
		}
		else if(seps == field){
			ret += record[i];
		}
		else if(seps > field){
			break;
		}
	}

	return ret;
}

int convertToInt(string orig){
	int n = 0, idx = 0;
	int sign = 1;
	bool signChecked = false;

	while(orig[idx] != '\0'){
		if(orig[idx] == ' '){
			continue;
		}

		if((orig[idx] == '-' || orig[idx] == '+') && !signChecked){
			if(orig[idx] == '-'){
				sign = -1;
			}

			signChecked = true;
		}
		else if(orig[idx] >= '0' && orig[idx] <= '9'){
			n = n * 10 + orig[idx] - '0';
		}
		else {
			break;
		}

		idx++;
	}

	return sign * n;
}

void drugDealerLicense(){
	cout << "Issued to: M. Khalid Ramzan" << endl
		<< "License number: 123789-DRA" << endl
		<< "Issuer: Drug Regulatory Authority" << endl
		<< "Expiry Date: 11-Dec-2030" << endl;
	
	cout << "Emails have been sent" << endl;
}

void listFeedbacks(){
	if(feedbackCount > 0){
		for(int i = 0; i < feedbackCount; i++){
			cout << i + 1 << ". " << feedbackBox[i] << endl;
		}
	}
	else {
		cout << "No feedbacks yet" << endl;
	}
}

void listReturns(){
	if(returnCount > 0){
		for(int i = 0; i < returnCount; i++){
			cout << i + 1 << ". " << orderReturns[i] << endl;
		}
	}
	else {
		cout << "No product has been returned yet" << endl;
	}
}

bool redeemCoupon(int coupon){
	coupon -= 123456;

	if(coupon < 0){
		return false;
	}

	couponAmout += coupon;
	return true;
}

int generateCoupon(int amount){
	if(amount > 0){
		return 123456 + amount;
	}

	return 0;
}