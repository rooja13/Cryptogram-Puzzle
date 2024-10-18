#include <iostream>
#include <string>
using namespace std;

/*TODO
- Create a menu with options
	-Cryptogram Puzzle
	-Encrypt your word
	-Decrypt your word
	- quit*/

// lower case ascii range is [97-122]
// Upper case ascii range is [65-90]

int a = 11;
int b = 13;
int m = 26;

/*Encryption Algorithm: E(x) = (ax + b) % m
 where m is modulus and a and b are keys to the cypher. GCD of a and m must be 1
 possible values for a: 1, 3, 5, 7, 11, 15, 17, 19, 21, 23, 25
 */
string Encryption(string plainText) {
	string temp = "";
	for (int i = 0; i < plainText.size(); i++) {
		int x = plainText[i];
		int shift = 0;

		if (x >= 'A' && x <= 'Z') {
			shift = 'A'; // 65
		}
		else if (x >= 'a' && x <= 'z') {
			shift = 'a'; // 97
		}
		else {
			temp += x;
			continue;
		}

		x -= shift;
		int encrptedNumber = (a * x + b) % m;
		char newLetter = char(encrptedNumber) + shift;
		temp += newLetter;
	}
	return temp;
}

//Decryption Algorithm : D(x) = a ^ -1(x - b) % 26
//Where a^-1 is the modular multiplicitive inverse(a * a ^ -1 = 1 mod m)

int GCD(int a, int b) {
	// A > B for algorithm to work
	if (a < b) {
		int temp = a;
		a = b;
		b = temp;
	}
	// A and B are NOT coprime
	if (b == 0) {
		return a;
	}
	// A and B are coprime
	if (b == 1) {
		return 1;
	}

	return GCD(b, a % b);
}
int ModularInverse(int a, int b, int x, int y) {
	// Inverse does not exist if A and B are not coprime
	if (GCD(a, b) != 1) {
		cout << a << " and " << b << " are not coprime\n";
		return -1;
	}
	// base case
	if (b == 0) return x;

	int quotient = a / b;
	int remainder = a % b;
	int t = x - y * quotient;

	int inverse = ModularInverse(b, remainder, y, t);

	if (inverse < 0) {
		return inverse + 26;
	}
	return inverse;
}
string Decryption(string encryptedText) {
	string temp = "";
	int inverse = ModularInverse(m, a, 0, 1);
	for (int i = 0; i < encryptedText.size(); i++) {
		int x = encryptedText[i];
		int shift = 0;

		if (x >= 'A' && x <= 'Z') {
			shift = 'A'; // 65
		}
		else if (x >= 'a' && x <= 'z') {
			shift = 'a'; // 97
		}
		else {
			temp += x;
			continue;
		}

		x -= shift;
		// Affine Encryption Algorithm returns a number from [0,25]
		int decryptedNumber = inverse * (x - b) % m;
		// learned that modulus on negative numbers behaves differently than expected
		while (decryptedNumber < 0) {
			decryptedNumber += m; // puts number in range [0,26]
		}
		// Shift the domain back to [97,122] thne stor the char
		char newLetter = char(decryptedNumber) + shift;
		temp += newLetter;
	}
	return temp;
}

void UserEncrypt() {
	string plainText = "";
	int choice = -1;
	system("cls");
	printf("Enter the message you want to encrypt: ");

	cin.ignore(10000, '\n'); // ignore the input buffer
	getline(cin, plainText);
	string cipherText = Encryption(plainText);

	printf("\nYour encrypted message is: %s\n\n", cipherText.c_str());

	printf("1. Encrypt another Message\n");
	printf("2. Return to Main Menu\n");

	while (choice != 2) {
		cin >> choice;
		if (choice == 1) {
			UserEncrypt();
		}
		else if (choice == 2) {
			system("cls");
			break;
		}
		else {
			printf("Enter a valid option\n");
		}
	}
}
void UserDecrypt() {
	string plainText = "";
	int choice = -1;
	system("cls");
	printf("Enter the message you want to encrypt: ");

	cin.ignore(10000, '\n'); // ignore the input buffer
	getline(cin, plainText);
	string cipherText = Encryption(plainText);

	printf("\nYour encrypted message is: %s\n\n", cipherText.c_str());

	printf("1. Encrypt another Message\n");
	printf("2. Return to Main Menu\n");

	while (choice != 2) {
		cin >> choice;
		if (choice == 1) {
			UserEncrypt();
		}
		else if (choice == 2) {
			system("cls");
			break;
		}
		else {
			printf("Enter a valid option\n");
		}
	}
}
void Puzzle() {

}

void MainMenu() {
	printf("CRYPTOGRAM PUZZLE\n\n");

	printf("Enter a number:\n");
	printf("1. Encrypt a Message\n");
	printf("2. Decrypt a Message\n");
	printf("3. Solve a puzzle\n");
	printf("0. quit\n\n");
}

int main() {
	int choice = -1;
	while (choice != 0) {
		MainMenu();
		if(choice == -2) printf("Enter a valid option\n");
		cin >> choice;

		switch (choice) {
		case 0:
			choice = 0;
			continue;
			break;

		case 1:
			UserEncrypt();
			break;

		case 2:
			break;

		case 3:
			break;

		default:
			choice = -2;
			break;
		}
		cin.ignore(10000, '\n'); // ignore the input buffer
	}

	printf("\nThank you for checking out my Cryptogram Program!\n");
	return 0;
}