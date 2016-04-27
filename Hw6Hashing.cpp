#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

/**Make a hashtable with data type int and which has the capacity to store 10,000 integers*/
int hashTable[10000];

/**Extract the third, fifth, seventh, and eighth digit from a person's social security number.
It makes a string start that consists of only four zeros, and then it takes out the needed digits from them.*/
int Now_Extract(int number) {
    string start = "00000";//
    char * char_val=new char[100];
    sprintf(char_val,"%i",number);
    string val =(string)char_val;
    int j = 0;

    for (int i = 0; i < val.size(); i++) /**get characters into val*/
    {
        start[i] = val[j];
        j++;
    }

    string final = "0000";
    final[0] = start[2]; /**get 3rd*/
    final[1] = start[4]; /**get 5th*/
    final[2] = start[6]; /**get 7th*/
    final[3] = start[7]; /**get 8th*/

    return atoi(final.c_str());
}
/**Probing function executes quadratic probing without replacement.*/
int Now_Probing(int hash_Table[], int indexNumber, int userInput) {
    int pos;
    pos = indexNumber % userInput;

    for(int i=1; i<10000; i++)
    {
        if(hash_Table[(pos+(userInput+i)*(userInput+i)) % 10000]==0) /**keep checking for the next "square" spot*/
        {
            return (pos+(userInput+i)*(userInput+i)) % 10000; /**return spot that is available*/
        }
    }

    return -1; /**return -1 if no spots are available*/
}

int main()
{
    /**Make a hashtable that consists of 10000 digit. First, make each digit a zero.*/
    for (int i = 0; i < 10000; i++) {
        hashTable[i] = 0;
    }
    /**Ask for a file to open; check if can open it. If can, put into a string. If not ask again for a file name until use names an existing file.*/
    ifstream current_file;     ofstream outfile;
    string file_name;
    int user_num;
    cout << "What is the name of the file: ";
    getline(cin, file_name);
    current_file.open(file_name.c_str()); /**open input file*/
    while(current_file.fail()) /**makes sure file name is  valid*/
    {
        cout << file_name << " " << "file not found" << endl;
        cout << "Enter in another file: ";
        getline(cin, file_name);
        current_file.open(file_name.c_str());
    }
    string fileContents = "", temp;
	if (current_file.is_open())
	{
		outfile.open("hashed_socials.txt"); /**open output file*/
        while (current_file.peek() != EOF){
		    current_file >> temp;
		    fileContents += temp;
		}
	}

	vector<int> allNumbers; /**numbers go into vector*/
	temp = "";
	for (int i = 0; i < fileContents.size(); i++) {
        if (fileContents[i] == ',') {
            allNumbers.push_back(atoi(temp.c_str())); /**push to vector*/
            temp = "";
        }
        else {
            temp += fileContents[i];
        }
	}

	cout << "Enter a number between 1 and 450,000,000: ";
    cin >> user_num;

    user_num = user_num % 10000; /**user number set*/

    while(!(user_num >= 0 && user_num <= 450000000))
    {
        cout << "Enter a number between 0 and 450000000: " << endl;
        cin >> user_num;
    }

	for (int i = 0; i < allNumbers.size(); i++) {
        int index =  Now_Extract(allNumbers[i]);
        if (hashTable[index] == 0) { /**if spot is empty*/
            hashTable[index] = allNumbers[i];
            cout << allNumbers[i] << " NO COLLISION" << endl;
        }
        else { /**if spot is full*/
            cout << allNumbers[i] << " COLLISION" << endl;
            int index =  Now_Probing(hashTable, index, user_num);
            if (index != -1) {
                    cout << index << endl;
                hashTable[index] = allNumbers[i];
                cout << "put in " << index << " instead" << endl;
            }
            else { /**if hash table is full*/
                cout << "FULL" << endl;
                break;
            }
        }
	}


    for (int i = 0; i < 10000; i++) { /**output file*/
        outfile << hashTable[i];
        if(i<9999)
        {
            outfile << ",";
        }

    }

	current_file.clear();
	outfile.clear();
	current_file.close();
	outfile.close();
    outfile << "\n";

    cout<< Now_Extract(123456789) << endl;

    cout << "Done, good job!" << endl;
    return 0;
}
