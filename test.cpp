#include <iostream>
#include <sstream> 
#include <vector>

using namespace std;

void tokenizeString(string input)
{
	vector <string> tokens;

	// sstream type
	stringstream stream(input);

	string token;

	while(getline(stream, token, ' '))
	{
		tokens.push_back(token);
	}

	if(tokens.size() == 1)
	{
		if(tokens[0] == "QUIT")
		{
			cout << "quitting...";
			return;
		}
	}else if(tokens.size() == 2)
	{
		if(tokens[0] == "LOAD")
		{
			cout << "loading from file " << tokens[1] << endl;
			return;
		}else if(tokens[0] == "SAVE")
		{
			cout << "saving to file" << tokens[1] << endl;
			return;
		}else
		{
			cout << "placing to => " << tokens[0] << " : " << tokens[1] << endl;
		}
	}else
	{
		cout << "invalid input..." << endl;
	}


}

int main() 
{

	int a; 
	char ch[80]; 
	
	// Enter input from user 
	// - 4 for example 
	cin >> a; 

	// cin.ignore(10, '\n');
	cin.ignore(1000, '\n');
	
	// Get input from user - 
	// "GeeksforGeeks" for example 
	cin.getline(ch,80); 
	
	// Prints 4 
	cout << a << endl; 
	
	// Printing string : This does 
	// not print string 
	cout << ch << endl; 
	



	// string input = "QUIT";

	// tokenizeString(input);


	return 0; 
}

