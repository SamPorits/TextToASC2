#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <map>
#include <sstream>
#include <string.h>
#include <vector>
#include <list>
#include <ctype.h>
#include <cstring>
#include <thread>
#include <chrono>

using std::cout;
using std::cin;
using std::string;
using std::to_string;
using std::endl;
using std::map;
using std::stoi;

map<char, string> binaryDictionary{ //Dictionary of non computable characters
	{'A', "01000001"},
	{'a', "01100001"},
	{'B', "01000010"},
	{'b', "01100010"},
	{'C', "01000011"},
	{'c', "01100011"},
	{'D', "01000100"},
	{'d', "01100100"},
	{'E', "01000101"},
	{'e', "01100101"},
	{'F', "01000110"},
	{'f', "01100110"},
	{'G', "01000111"},
	{'g', "01100111"},
	{'H', "01001000"},
	{'h', "01101000"},
	{'I', "01001001"},
	{'i', "01101001"},
	{'J', "01001010"},
	{'j', "01101010"},
	{'K', "01001011"},
	{'k', "01101011"},
	{'L', "01001100"},
	{'l', "01101100"},
	{'M', "01001101"},
	{'m', "01101101"},
	{'N', "01001110"},
	{'n', "01101110"},
	{'O', "01001111"},
	{'o', "01101111"},
	{'P', "01010000"},
	{'p', "01110000"},
	{'Q', "01010001"},
	{'q', "01110001"},
	{'R', "01010010"},
	{'r', "01110010"},
	{'S', "01010011"},
	{'s', "01110011"},
	{'T', "01010100"},
	{'t', "01110100"},
	{'U', "01010101"},
	{'u', "01110101"},
	{'V', "01010110"},
	{'v', "01110110"},
	{'W', "01010111"},
	{'w', "01110111"},
	{'X', "01011000"},
	{'x', "01111000"},
	{'Y', "01011001"},
	{'y', "01111001"},
	{'Z', "01011010"},
	{'z', "01111010"},
	{'`', "01100000"},
	{'~', "01111110"},
	{'!', "00100001"},
	{'@', "01000000"},
	{'#', "00100011"},
	{'$', "00100100"},
	{'%', "00100101"},
	{'^', "01011110"},
	{'&', "00100110"},
	{'*', "00101010"},
	{'(', "00101000"},
	{')', "00101001"},
	{'_', "01011111"},
	{'-', "00101101"},
	{'=', "00111101"},
	{'+', "00101011"},
	{'[', "01011011"},
	{']', "01011101"},
	{'{', "01111011"},
	{'}', "01111101"},
	{'\\', "01011100"},
	{':', "00111010"},
	{';', "00111011"},
	{'\'', "00100111"},
	{'"', "00100010"},
	{',', "00101100"},
	{'.', "00101110"},
	{'<', "00111100"},
	{'>', "00111110"},
	{'/', "00101111"},
	{'?', "00111111"},
	{' ', "00100000"}
};

string numberToBinary(int input) //Takes in an integer and outputs a string version of that in binary
{
	int remainder; // This is the numbe to input every iteration
	int dividend = input; // Leaves us with the remaining number
	string binary = "1"; // Storage for output binary
	string newBinary = "";

	if (input == 48) //for if its 0
	{
		newBinary += "00000000";
	}

	else if (input == 49) { //1 case
		newBinary += "00000001";

	} 
	else 
	{
		binary = "";
		while (dividend >= 1) // Checking remainder to keep loop going untill nothing left
		{
			remainder = dividend % 2;
			binary += to_string(remainder); // Adding onto binary output
			dividend = dividend / 2;
		}

		//Warning below
		// "ill defined loop, loop executes indefentily"
		// 
		//Reversing the binary string adding it to new variable
		for (size_t i = binary.length() - 1; i --> 0;) { //binary.length is returning size_t type of number comparing 32 bit to 64 bit
			newBinary += binary[i];
		}

		//Addidnt extra 0s on front to make it ASC2 readable
		size_t binaryLength = newBinary.length();
		if (binaryLength < 8)
		{
			size_t difference = 8 - binaryLength;
			for (int m = 0; m < difference; m++)
			{
				newBinary = '0' + newBinary;
			}
		}
	}
	return newBinary;
}

int checkLength(string userInput, int i, int numberInRow) {
	// Need to check if there are more than 1 numbers in a row
	// loop that checks if next iteration is number

	// Need to figure out how to check next iteration without breaking it
	while (isdigit(userInput.at(i)) && (i + numberInRow <= userInput.size() - 1)) { //Checking digit if next its not bigger than size
		if (isdigit(userInput.at(i + numberInRow)))
		{
			numberInRow += 1;
		}
		else 
		{
			return numberInRow;
		}
	}
	return numberInRow;
}

void slowprint(string word, int speed) 
{
	for (int i = 0; i < word.size(); i++)
	{
		cout << word[i];
		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}
}

int main()
{
	string binaryOutput;
	string userInput;
	size_t userInputSize;
	bool moreThanOneNumber = false;
	int numberInRow = 0;

	// Introduction
	if (true) //for debugging purposes
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		slowprint("Hello, ", 90);
		std::this_thread::sleep_for(std::chrono::milliseconds(600));
		slowprint("and welcome to the english to ASC2 translator!", 60);
		cout << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1200));
		slowprint("Please input what you would like to translate!", 60);
		cout << endl;

	}



	//Input Stage
	std::getline(cin, userInput); //Input from user
	userInputSize = userInput.size(); // Gets input length

	//Proccessing Stage

	for (int i = 0; i < userInputSize; i++)
	{
		int current = i;
		if (isdigit(userInput.at(i))) { //Checking if i is digit to convert to binary

			int stringLength = checkLength(userInput, i, numberInRow); // Getting length of numbers in a row

			i += stringLength - 1; // Skipping iterations to count whole number
			string binaryRowResult = ""; // string to turn into number

			if (stringLength == 1) // Proccessing numbers 0-10
			{
				if (userInput[current] == '0')  //if numbers 0 or 1 adding to output
				{
					binaryOutput += "00000000";
				}
				else if (userInput[current] == '1') 
				{
					binaryOutput += "00000001";
				}
				else // to binary digits 2-9
				{
					binaryOutput += numberToBinary(userInput[current] - 48); //Takes 48 off bcz of stoi conversion
				}
			} else { // Proccessing numbers >= 10 into binary

				for (current; current <= i; current++) { //Putting indiviudal number char into one number string
					binaryRowResult += userInput[current];
				}
				binaryOutput += numberToBinary(stoi(binaryRowResult)); //Turning into int to put into equation
			}
		} else { //If its not integer its a char
			numberInRow = 0;
			binaryOutput += binaryDictionary[userInput[i]]; //Referencing dictionary to get binary
		}
		
	}
	//Output Stage

	if (true) //debugging purposes
	{
		slowprint("Original input: ", 90);
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		slowprint(userInput, 90);
		cout << endl;
		slowprint("Binary output: ", 90);
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		slowprint(binaryOutput, 90);
	}

	if (false) 
	{
		cout << "Original inut: " << userInput << endl;
		cout << "Binary output: " << binaryOutput << endl;
	}

	return 0;
};
