#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;


// Dictionary of frequency distribution of characters for caesars cipher
static float freq_caesar[] = {
	0.08167, 0.01492, 0.02782, 0.04253, .12702, 0.02228,
	0.02015, 0.06094, 0.06996, 0.00153, 0.00772, 0.04025,
	0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
	0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
	0.01974, 0.00074
	};

int main(int argc, char **argv)
{
	// Check input from command line args
	// Check number of input paramenter
	if (argc != 2)
	{
		cout<<"Invalid number of arguments! Please go through README.md";
		return -1;
	}

	// Check for valid input
	for(int j = 0; j < string(argv[1]).length(); j++)
		if(!isdigit(argv[1][j]))
		{
			cout<<"Invalid arguments! Please go through README.md"; // Enter only numbers!
			return -1;
		}

	// End of command line arg checking
	
	int alg_choice = atoi(argv[1]);

	if(!(alg_choice == 0 || alg_choice == 1))
	{
		cout<<"Invalid choice for encryption algorithm! Please go through README.md";
		return -1;
	}

	ifstream inFPtr("vigenere-process.txt");	// Hardcoding ze name as per assignment requirements :)

	// Check if file exists first before reading it duh?
	if(!inFPtr.good())
	{
		cout<<"Unable to access/read 'process.txt'. Does the file exist in the right place?";
		return -1;
	}
	
	// String that will store the entire
	string file_data;

	// For storing the entire file contents in a string for easy manipulation! String Stream seems to be the best way!
	ostringstream string_stream;
	string_stream << inFPtr.rdbuf();
	file_data = string_stream.str();

	// Close the input file
	inFPtr.close();

	// Ze Function prototypes
	void caesar(string);
	void vigenere(string);
	string strToUpper(string);

	file_data =  strToUpper(file_data);

	switch(alg_choice)
	{
		case 0:
				caesar(file_data);
				break;

		case 1:
				vigenere(file_data);
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

void caesar(string file_data)
{
	cout<<"Caesar cipher cryptanalysis requested."<<endl;

	// Array to store frequency of each of the 
	int freq_count[26];

	// Initialize the array to 0
	for(int i = 0; i < 26; i++)
		freq_count[i] = 0;

	// Iterate through the string
	for(int i = 0; i < file_data.length(); i++)
	{
		// If not a character, print and skip processing. Mostly not possible for the way input file is made, thanks prof!
		if(!isalpha((file_data[i])))
		{
			cout<<file_data[i];
			continue;
		}

		freq_count[int(file_data[i] - 'A')]++;
	}

	int max_freq_index = 0;

	// Find word with max frequency
	for(int i = 0; i < 26; i++)
		if(freq_count[max_freq_index] < freq_count[i])
			max_freq_index = i;

	cout<<"Letter with max frequency: "<<char('A' + max_freq_index)<<endl;
	int key = max_freq_index - 4;
	cout<<"Key: "<<key<<endl;

	cout<<"Decrypted text:"<<endl;

	for(int i = 0; i < file_data.length(); i++)
	{
		char decpt_out = file_data[i] - key;
		while(decpt_out < 65)
			decpt_out += 26;

		cout<<decpt_out;
	}
}

void vigenere(string file_data)
{
	cout<<"Vigenere cipher cryptanalysis requested."<<endl;

	cout<<"Finding key length..."<<endl;

	int shift_freq[20];

	for(int i = 0; i < 20; i++)
		shift_freq[i] = 0;

	for(int i = 1; i < 20; i++)
	{
		for(int w_index = 0; w_index < file_data.length(); w_index++)
			if(file_data[w_index] == file_data[(w_index + i) % file_data.length()])
				shift_freq[i]++;
	}

	int key_length = 0;

	for(int i = 0; i < 20; i++)
		if(shift_freq[key_length] < shift_freq[i])
			key_length = i;

	cout<<"Key length size: "<<key_length<<endl;

	// for(int i = 0; i < file_data.length(); i++)
	// 	cout<<file_data[i]<<endl;

	string KEY;
	string collection[key_length];

	for(int i = 0; i < file_data.length(); i += key_length)
		for(int j = 0; j < key_length; j++)
		{
			// cout<<i<<" "<<j<<endl;
			cout<<i<<" "<<j<<" "<<file_data[i + j]<<endl;
			// collection[key_length].push_back(file_data[i + j]);
		}

	for(int i = 0; i < key_length; i++)
		cout<<collection[i]<<endl;



	// break up cipher text
	// Freq analysis
}