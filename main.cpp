// Cristian Rodriguez CPSC 362 Due: March 3, 2021
//Visual Studio Community 2019
//Brief Program desc: a program that has a menu with 6 options which includes InputData in which the user will input a string that is less than or equal to 128 characters
//and then ask the user to input an 8 character CryptoKey, the user can then Encrypt the message by using a XOR operation and can then Display the Encrypted string,
//the user can Decrypt the message back using the XOR operation and can Display the Decrypted string and then the user has the option to quit or can insert new data.

#include"Crypto.h"

//Displays InputDataBuffer, CryptoKey, and CryptoMatrix
void Crypto::DisplayCryptoMatrix(){
	system("CLS");
	if (InputDataCount == 0)
		cout << "Nothing to encrypt.\n\n";
	else {
		cout << "Displaying Crypto Matrix.\n\n"
			<< "The string that you entered was: " << InputDataBuffer
			<< "\n\nYour Crypto Key that you entered was: " << CryptoKey
			<< "\n\nDisplaying Crypto Matrix: " << CryptoMatrix
			<< endl << endl;
	}
}

//Displays CryptoMatrix, CryptoKey, ClearMatrix
void Crypto::DisplayClearMatrix(){
	system("CLS");
	if (InputDataCount == 0)
		cout << "Nothing to decrypt.\n\n";
	else {
		cout << "Displaying Clear Matrix.\n\n"
			<< "The Crypto Matrix string that was created is: " << CryptoMatrix
			<< "\n\nYour Crypto Key that you entered was: " << CryptoKey
			<< "\n\nDisplaying Clear Matrix: " << ClearMatrix
			<< endl << endl;
	}
}


void Crypto::InputData(){
	system("CLS");
	memset(InputDataBuffer, ' ', sizeof(InputDataBuffer));
	
	string temp;

	//Keeps looping until user input is less than or equal to 128 characters
	do {
		int j = 0;
		InputDataCount = 0;

		//Ask user to input a string of size 128 or less
		cout << "Enter a string: ";
		cin.ignore();
		getline(cin, temp);

		while (temp[j]) {
			InputDataCount++;
			j++;
		}

	} while (InputDataCount > 128);

	//Inputs user input into InputDataBuffer
	strncpy_s(InputDataBuffer, temp.c_str(), sizeof(InputDataBuffer));

	//Ask user to input a 8 character key
	cout << "\nEnter an 8 character crypto key: ";
	cin >> CryptoKey;
	
	int len, i;

	//Counts the size of the user key and keeps looping until key size is equal to 8
	do {
		len = 0, i = 0;

		while (CryptoKey[i]) {
			len++;
			i++;
		}

		if (len < 8) {
			cout << "\nCrypto key is shorter than 8 characters please re-enter key: ";
			cin >> CryptoKey;
		}
		else if (len > 8) {
			cout << "\nCrypto key is longer than 8 character please re-enter key: ";
			cin >> CryptoKey;
		}

	} while (len != 8);
}

//Decrypts the CryptoMatrix using the CryptoKey and stores it into ClearMatrix array
void Crypto::Decrypt(){
	int counter = 0;

	for (int i = 0; i <= InputDataCount; i++) {
		if (counter == 8)
			counter = 0;

		ClearMatrix[i] = CryptoMatrix[i] ^ CryptoKey[counter];
		counter++;
	}
}

//Encrypts the user InputDataBuffer using the CryptoKey and stores it into CryptoMatrix array
void Crypto::Encrypt(){
	int counter = 0;
	int i;

	for (i = 0; i <= InputDataCount; i++) {
		while (InputDataCount % 8 != 0) {
			InputDataBuffer[InputDataCount] = ' ';
			InputDataCount++;

			if (InputDataCount % 8 == 0)
				InputDataBuffer[InputDataCount] = '\0';
		}

		if (counter == 8)
			counter = 0;
		
		CryptoMatrix[i] = InputDataBuffer[i] ^ CryptoKey[counter];
		counter++;
	}
	CryptoMatrix[i] = '\0';
}

int main() {
	Crypto crypto;
	int number;
	bool flag = false;
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;

	do {
		cout << "Main Menu\n"
			<< "1. Input Data\n"
			<< "2. Encrypt\n"
			<< "3. Decrypt\n"
			<< "4. Display Crypto Matrix\n"
			<< "5. Display Clear Matrix\n"
			<< "6. Quit\n\n"
			<< "Select a number: ";
		while (!(cin >> number)) {
			cin.clear();
			cin.ignore();
			cout << "\nError: That is not a valid number. Enter again: ";
		}
		if (number == 1) {
			crypto.InputData();
			flag1 = true;
			system("CLS");
		} else if (number == 2 && flag1 == true) {
			crypto.Encrypt();
			cout << "Data has been Encrypted.\n\n";
			flag = true;
			flag1 = false;
			flag2 = true;
		} else if (number == 3 && flag == true) {
			crypto.Decrypt();
			cout << "Data has been Decrypted.\n\n";
			flag = false;
			flag3 = true;
		} else if (number == 4 && flag2 == true) {
			crypto.DisplayCryptoMatrix();
			flag2 = false;
		}
		else if (number == 5 && flag3 == true) {
			crypto.DisplayClearMatrix();
			flag3 = false;
		}
	} while (number != 6);
}