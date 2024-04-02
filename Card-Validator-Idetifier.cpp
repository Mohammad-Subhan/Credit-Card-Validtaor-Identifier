// Header Files
#include<iostream>
#include<string>
#include<cctype>

using namespace std;

// Functions prototypes
string input();
bool valid_input(string&);
bool luhn_algorithm(string&);
string type_check(string&);
void result(string&, string&);

// main function
int main() {

	string c_number, c_type;

	c_number = input();

	c_type = type_check(c_number);

	result(c_number, c_type);

	return 0;
}

// Input Function .. gets input from user and return it
string input() {

	string input;
	cout << "----------------------------------------------------------------------------\n";
	do
	{
		cout << "\t\t   Enter Card Number: ";
		getline(cin, input);

		// if input is valid returns the input else keep looping until valid
		if (valid_input(input))
			return input;

		cout << "\t\t   Invalid Input. Enter again\n" << endl;

	} while (!valid_input(input));
}

// validinput function .. check if the input is valid or not
bool valid_input(string& input) {

	string formatted;

	// format the input by removing dashes and hyphens
	for (char c : input) {
		if (c == ' ' || c == '-')
			continue;
		formatted += c;
	}

	input = formatted;

	// checks for the length of input
	if (input.length() >= 13 && input.length() <= 19) {
		for (char c : input) {
			// checks for any character
			if (!isdigit(c))
				return false;
		}
		return true;
	}
	else {
		return false;
	}
}

// type_check function .. checks for the type of card network
string type_check(string& input) {

	int prefix = stoi(input.substr(0, 2));
	int length = input.length();

	if ((prefix >= 40 && prefix <= 49) && (length == 13 || length == 16))
		return "\t    Card Type: VISA";
	else if (((prefix >= 51 && prefix <= 55) || (stoi(input.substr(0, 4)) >= 2221 && stoi(input.substr(0, 4)) <= 2720)) && length == 16)
		return "\t Card Type: Master Card";
	else if ((prefix == 34 || prefix == 37 || prefix == 30) && length == 15)
		return "      Card Type: American Express";
	else if (prefix == 35 && length == 16)
		return "\t     Card Type: JCB";
	else if (prefix == 62 && (length >= 16 && length <= 19))
		return "\t Card Type : Union Pay";
	else if ((prefix == 30 || prefix == 36 || prefix == 38 || prefix == 39) && length == 14)
		return "\t Card Type: Diners Club";
	else if ((prefix >= 60 && prefix <= 69) && length == 16)
		return "\t  Card Type: Discover";
	else {
		return "\t   Unknown Card Type \n\t\t      (Card may not be supported)";
	}
}

// luhnalgorithm function .. checks if the number if it is valid card number or not
bool luhn_algorithm(string& input) {

	long long cardnumber = stoll(input);
	long long oddplace = cardnumber;
	int	sum = 0;

	// sum of the digits at the odd place
	while (oddplace > 0) {
		sum += (oddplace % 10);
		oddplace = oddplace / 100;
	}

	// to access the even placed digits
	long long evenplace = cardnumber / 10;
	int lastdigit, timestwo;

	// sum of the digits at even place after proper calculatins
	while (evenplace > 0) {
		lastdigit = evenplace % 10;
		timestwo = lastdigit * 2;
		sum += (timestwo >= 10 ? (timestwo - 9) : timestwo);
		evenplace = evenplace / 100;
	}

	// checks for the sum to be the multiple of 10
	if (sum % 10 == 0)
		return true;
	else
		return false;
}

// result function .. displays the corresponding result
void result(string& c_number, string& c_type) {

	cout << "----------------------------------------------------------------------------\n";

	// checks for the luhn algorithm to be valid 
	if (luhn_algorithm(c_number)) {

		// outputs the result for valid card number
		cout << "\t\t\tThe Card Number is Valid\n";
		cout << "\t\t " << c_type;
	}
	else {
		// outputs the result for invalid card number
		cout << "\t\t\t   Invalid Card Number";
	}

	cout << "\n----------------------------------------------------------------------------\n";
}