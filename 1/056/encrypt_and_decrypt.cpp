#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

int main(int argc, char **argv)
{
	// Check input from command line args
	// Check number of input paramenter
	if (argc != 4)
	{
		cout<<"Invalid number of arguments! Please go through README.md";
		return -1;
	}

	// Check for valid input
	for(int i = 1; i < argc - 1; i++)
		for(int j = 0; j < string(argv[i]).length(); j++)
			if(!isdigit(argv[i][j]))
			{
				cout<<"Invalid arguments! Please go through README.md"; // Enter only numbers!
				return -1;
			}

	// End of command line arg checking
	
	int alg_choice = atoi(argv[1]);
	int do_encrypt = atoi(argv[2]);
	string KEY = argv[3];

	if(!(alg_choice >= 0 && alg_choice <= 2))
	{
		cout<<"Invalid choice for encryption algorithm! Please go through README.md";
		return -1;
	}
	
	if(!(do_encrypt == 0 || do_encrypt == 1))
	{
		cout<<"Invalid choice for encryption or decryption. Please go through README.md";
		return -1;
	}

	ifstream inFPtr("process.txt");	// Hardcoding the name as per assignment requirements :)

	// Check if file exists first before reading it duh?
	if(!inFPtr.good())
	{
		cout<<"Unable to access/read 'process.txt'. Does the file exist in the right place?";
		return -1;
	}
	
	// String that will store the entire
	string file_data;

	ostringstream string_stream;
	string_stream << inFPtr.rdbuf();
	file_data = string_stream.str();

	// Close the input file
	inFPtr.close();

	// Function prototypes
	void caesar(string, int, string);
	void vigenere(string, int, string);
	void playfair(string, int, string);
	string strToUpper(string);

	file_data =  strToUpper(file_data);

	switch(alg_choice)
	{
		case 0:
				caesar(file_data, do_encrypt, KEY);
				break;

		case 1:
				vigenere(file_data, do_encrypt, KEY);
				break;

		case 2:
				playfair(file_data, do_encrypt, KEY);
				break;

		default:
				cout<<"How did you even come here?? This is fatal!!";
	}

	return 0;
}

string strToUpper(string the_string)
{
	// Iterating through all chars of the string
	for(int i = 0; i < the_string.length(); i++)
	{
		if(!isalpha(the_string[i]))
			continue;
		
		the_string[i] = (isupper(the_string[i])) ? the_string[i] : toupper(the_string[i]);
	}
	
	return the_string;
}

void caesar(string file_data, int do_encrypt, string KEY)
{
	// Iterating through all chars of the key
	for(int i = 0; i < KEY.length(); i++)
		// Making sure we get a numeric key for Caesar's cipher
		if(!isdigit(KEY[i]))
		{
			cout<<"Invalid key entered for Caesar's Cipher! Please go through README.md";
			exit(-1);
		}

	// Converting KEY from char to string
	int KEY_VAL = stoi(KEY);

	// Encryption
	if(!do_encrypt)
	{
		cout<<"Encrypted text:"<<endl;

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			// Adding the key for the encryption
			char encpt_out = file_data[i] + (KEY_VAL % 26);

			// Rollover incase of value overflow
			while(encpt_out > 90)
				encpt_out -= 26;
			
			cout<<encpt_out;
		}
	}
	
	// Decryption
	else
	{
		cout<<"Decrypted text:"<<endl;

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			// Adding the key for the encryption
			char encpt_out = file_data[i] - (KEY_VAL % 26);

			// Rollover incase of value overflow
			while(encpt_out < 65)
				encpt_out += 26;
			
			cout<<encpt_out;
		}
	}
}

void vigenere(string file_data, int do_encrypt, string KEY)
{
	// Check for sus characters in KEY
	for(int i = 0; i < KEY.length(); i++)
		if(!isalpha(KEY[i]))
		{
			cout<<"Invalid key entered for Vigenère Cipher! Please go through README.md";
			exit(-1);
		}

	KEY = strToUpper(KEY);
	int key_track = 0;

	// Encryption
	if(!do_encrypt)
	{
		cout<<"Encrypted text:"<<endl;

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			// Adding the key for the encryption
			char encpt_out = file_data[i] + (KEY[key_track % KEY.length()] % 26);

			// Rollover incase of value overflow
			while(encpt_out > 90)
				encpt_out -= 26;
			
			cout<<encpt_out;
		}
	}

	// Decryption
	else
	{
		cout<<"Decrypted text:"<<endl;

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			// Adding the key for the encryption
			char encpt_out = file_data[i] - (KEY[key_track % KEY.length()] % 26);

			// Rollover incase of value overflow
			while(encpt_out < 65)
				encpt_out += 26;
			
			cout<<encpt_out;
			key_track++;
		}
	}
}

// Function to check if a character is in the matrix
int inMatrix(char matrix[5][5], char findChar)
{
	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 5; j++)
			if(findChar == matrix[i][j] || (findChar == 'I' && matrix[i][j] == 'J') || (findChar == 'J' && matrix[i][j] == 'I'))	// Weird edge case for the cipher
			{
				// cout<<"Found "<<findChar<<endl;
				return 1;
			}

	return 0;
}

// Funtion to get the coordinates of a given character from the key table in playfair cipher
int *getCoords(char KEY_TABLE[5][5], char letter)
{
	int *coords = (int*)malloc(2 * sizeof(int));

	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 5; j++)
			if(KEY_TABLE[i][j] == letter || (KEY_TABLE[i][j] == 'I' && letter == 'J') || (KEY_TABLE[i][j] == 'J' && letter == 'I'))	// Again, the weird edge case for the cipher
			{
				coords[0] = i;
				coords[1] = j;
				return coords;
			}

	// Incase we don't find the letter in the matrix
	coords[0] = coords[1] = -1;
	return coords;
}

char getCharAtCoords(char KEY_TABLE[5][5], int x, int y)
{
	return KEY_TABLE[x][y];
}

void playfair(string file_data, int do_encrypt, string KEY)
{
	// Check for sus characters in KEY
	for(int i = 0; i < KEY.length(); i++)
	if(!isalpha(KEY[i]))
		{
			cout<<"Invalid key entered for Playfair Cipher! Please go through README.md";
			exit(-1);
		}

	// Converting key to uppercase to maintain consistency
	KEY = strToUpper(KEY);
	
	// To store the key table
	char KEY_TABLE[5][5];

	// Initializing the keytable with all 1s
	for(int i = 0; i < 5; i ++)
		for(int j = 0; j < 5; j++)
			KEY_TABLE[i][j] = '1';
	
	// Variable to keep track of the 
	int key_track = 0;

	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 5; j++)
		{
			// Fill key_table with key characters
			if(key_track < KEY.length())
			{
				// Skip character if already in matrix
				while(inMatrix(KEY_TABLE, KEY[key_track]))
					if(key_track < KEY.length())
						key_track++;
					else
						break;

				// Check if length of the key is lesser than 
				if(key_track < KEY.length())
					KEY_TABLE[i][j] = KEY[key_track++];
				else
					goto REST_OF_THE_CHARS;
			}

			// Fill with rest of the alphabets
			else
			{
				REST_OF_THE_CHARS:
				for(char ch = 'A'; ch <= 'Z'; ch++)
					if(inMatrix(KEY_TABLE, ch))
						continue;
					else
					{
						KEY_TABLE[i][j] = ch;
						break;
					}
			}
		}

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
			cout<<KEY_TABLE[i][j]<<"\t";
		cout<<endl;
	}

	int char_reset = 0;
	char letter_pair[2];
	int *coords[2];

	// Encryption
	if(!do_encrypt)
	{
		cout<<"Encrypted text:"<<endl;

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			if(!(getCoords(KEY_TABLE, file_data[i])[0] == -1))
				letter_pair[char_reset++] = file_data[i];

			// Takes every 2 characters encrypt them
			if(!(char_reset % 2))
			{
				char_reset = 0;
				
				// Getting the coordinates
				for(int j = 0; j < 2; j++)
					coords[j] = getCoords(KEY_TABLE, letter_pair[j]);
				
				// Array to store encrypted text
				char encrypted_pair[2];

				for(int j = 0; j < 2; j++)
				{
					// Same column
					if(coords[0][1] == coords[1][1])
						encrypted_pair[j] = getCharAtCoords(KEY_TABLE, ((coords[j][0] + 1) % 5), coords[j][1]);

					// Same row
					else if(coords[0][0] == coords[1][0])
						encrypted_pair[j] = getCharAtCoords(KEY_TABLE, coords[j][0], ((coords[j][1] + 1) % 5));

					// Rectangle, take opposite corners
					else
						encrypted_pair[j] = getCharAtCoords(KEY_TABLE, coords[j][0], coords[(j + 1) % 2][1]);
				}

				// print encrypted pair
				cout<<encrypted_pair[0]<<encrypted_pair[1];
			}
		}
	}

	// Decryption
	else
	{
		cout<<"Decrypted text: ";

		// Iterating through all characters in the file.
		for(int i = 0; i < file_data.length(); i++)
		{
			// Check if character is an alphabet, print it directly if it isn't
			if(!isalpha(file_data[i]))
			{
				cout<<file_data[i];
				continue;
			}

			if(!(getCoords(KEY_TABLE, file_data[i])[0] == -1))
				letter_pair[char_reset++] = file_data[i];

			// Takes every 2 characters encrypt them
			if(!(char_reset % 2))
			{
				char_reset = 0;
				
				// Getting the coordinates
				for(int j = 0; j < 2; j++)
					coords[j] = getCoords(KEY_TABLE, letter_pair[j]);
				
				// Array to store encrypted text
				char decrypted_pair[2];

				for(int j = 0; j < 2; j++)
				{
					// Same column
					if(coords[0][1] == coords[1][1])
						decrypted_pair[j] = getCharAtCoords(KEY_TABLE, ((coords[j][0] + 4) % 5), coords[j][1]);

					// Same row
					else if(coords[0][0] == coords[1][0])
						decrypted_pair[j] = getCharAtCoords(KEY_TABLE, coords[j][0], ((coords[j][1] + 4) % 5));

					// Rectangle, take opposite corners
					else
						decrypted_pair[j] = getCharAtCoords(KEY_TABLE, coords[j][0], coords[(j + 1) % 2][1]);
				}

				// print encrypted pair
				cout<<decrypted_pair[0]<<decrypted_pair[1];
			}
		}
	}
}