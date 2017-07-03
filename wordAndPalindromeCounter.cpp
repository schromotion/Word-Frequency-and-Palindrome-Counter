#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
 
using namespace std;
 
//****************************************************************************************************************
//Structure for key variables
struct LetterFreqStruct
{
	char letters[26];
	string words[1000];
	string palindromes[1000];
	int letterCounter, wordCounter, palindCounter;
	int freq[26];
};

//****************************************************************************************************************
// Function Prototypes 
void newpg();
void userfriendly();
void IDpalindrome(string candidate, LetterFreqStruct &FreqStruct);
void openfiles(ifstream &fin, ofstream &fout);
void display(ofstream &fout, LetterFreqStruct &FreqStruct);
void fillFreq(string correctWord, LetterFreqStruct &FreqStruct);
void initialize(LetterFreqStruct &FreqStruct, int size);
string makeCleanWord(string inputWord);
void Proccessing(LetterFreqStruct &FreqStruct, string &correctWord, string inputWord, int x);

//****************************************************************************************************************
int main()
{
	// Call the structure
	LetterFreqStruct FreqStruct = {0};
	// Initialize the structure
	initialize(FreqStruct, 26);
    // Variables For Main() in the house
    string inputWords = "", corWord = "";
	int i = 0;
    // My Lame-O Intro Screen
    cout<<"\t Welcome To My Program! :) \n\n";
    cout<<"The purpose of this program is to help a user";
    cout<<"\nidentify the number of wordsand palindromes in an input text\nfile and the frequency of the each letter in the file.";
    cout<<"\n\n   Be sure to read the corresponding user document\nfor a great user experience. Thanks!";
    cout<<"\n\n\n\t *Press ENTER To Continue*";
    cin.ignore(); 
    newpg();
    cout<<"Please Type Your Paragraph Into Your Input File In The Folder.";
    cout<<"\n\n**Be Sure To Read The Help File For The Correct Format**";
    cout<<"\n\nThen Press *ENTER*";
    newpg();
    cin.ignore();
    //open the files dawg
    ifstream fin;
    ofstream fout;
    openfiles(fin, fout);
    //just for a more satisyfing user experience
    userfriendly();
	// Getting initial input 
	fin >> inputWords;
	// Key Loop Right Hurrrrrr
	while (!fin.eof())
	{
		// This will make sure words don't contain anything but letters
		// and will get the frequency for the letters and keep updating
		// the counters.
		Proccessing(FreqStruct, corWord, inputWords, i);
		// Getting new input.
		fin >> inputWords;
		// Keeping a count for the number of words.
		i++;
	}
	// Closing the input file.
	fin.close(); 
	// Displaying output.
	// It will display the frequency, count and letters.
	display(fout, FreqStruct);
	fout.close();
	newpg();
	cout<<"\n\n\n\tHave A Nice Day! :)";
	Sleep(500);
}
//****************************************************************************************************************
//A fun display page
void userfriendly()
{
    cout<<"\n\n\n\t\tProcessing Your File...";
    for(int time = 1; time < 7; time++) {
    Sleep(200);
    cout<<"..."; 
    }
    cout<<"...\n\n\t\tProcessing Complete!";
    cin.get();
}

//****************************************************************************************************************
//open the files... Not sure how to clear a fin.open() so if that isn't true than the program is in barney
void openfiles(ifstream &fin, ofstream &fout) 
{
    string infile;
    string outfile;
    newpg();
    cout<<"\n\n\nPlease Enter Your Input File Name: ";
    getline (cin,infile);
    fin.open(infile.c_str() );
    newpg();
    cout<<"\n\n\nPlease Enter Your Output File Name: ";
    getline (cin,outfile);
    fout.open(outfile.c_str() );
    newpg();
    if (!fin || !fout)
    {
      newpg();
      cout<<"Sorry Your File Could Not Be Opened. Please Wait And Try Again.";
      Sleep(1000);
      exit(0);  
    } 
}

//****************************************************************************************************************
//more or less clears the screen on the program
void newpg() {
     cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

//****************************************************************************************************************
//displays the outout 
void display(ofstream &fout, LetterFreqStruct &FreqStruct)
{
	fout << setw(6) << "Letter"		<< "\t"
		 << setw(5) << "Count"		<< "\t"
		 << setw(9) << "Frequency"	<< endl
 
		 << setw(6) << "______"		<< "\t"
		 << setw(5) << "_____"		<< "\t"
		 << setw(9) << "_________"	<< endl;
	for (int i = 0; i < 26; i++)
	{
		fout << left << setw(6) << FreqStruct.letters[i] << "\t"
			 << left << setw(5) << FreqStruct.freq[i]   << "\t";
		// Displaying the frequency bars
		for (int x = 0; x < FreqStruct.freq[i]; x++)
		{
			fout << "=";
		}
		fout << endl;
	}
	fout << endl << "The file has " << FreqStruct.letterCounter << " characters, " << FreqStruct.wordCounter 
         << " words and " << FreqStruct.palindCounter << " palindromes." << endl << endl;
    //Only write out the palindromes if there are any
    if (FreqStruct.palindCounter != 0)
    {   
    fout << "The Palindromes in this file are : ";
            for (int l = 0; l < 1000; l++)
            {
            fout << FreqStruct.palindromes[l] << " ";
            }
    }
}

//**************************************************************************************************************** 
// Filling the frequency for every letter. 
void fillFreq(string correctWord, LetterFreqStruct &FreqStruct)
{
	for (string::size_type i = 0; i < correctWord.size(); i++)
	{
		// This says whatever the number of the letter inside correctWord
		// at position "i" is minus 65. 
		FreqStruct.freq[(toupper(
        correctWord[i])) - 65]++;
	}
}

//****************************************************************************************************************
// Initializing the structure.
void initialize(LetterFreqStruct &FreqStruct, int size)
{
	for (int i = 0; i < size; i++)
	{
		FreqStruct.freq[i] = 0; 
		FreqStruct.letters[i] = i + 65;
		FreqStruct.words[i] = "";
		FreqStruct.palindromes[i] = "";
	}
	FreqStruct.letterCounter = 0;
	FreqStruct.wordCounter = 0;
	FreqStruct.palindCounter = 0;
}

//**************************************************************************************************************** 
// Eliminate Strings Not Composed of English Words 
string makeCleanWord(string inputWord)
{
	string newWord = "";
	for (string::size_type i = 0; i < inputWord.size(); i++)
	{
		// If the ascii code is not in english letter range dont include it
		if ((inputWord[i] >= 'A' && inputWord[i] <= 'Z') ||
			(inputWord[i] >= 'a' && inputWord[i] <= 'z'))
		{
			newWord += inputWord[i];
		}
	}
	// Return the clean word.
	return newWord;
}
 

//****************************************************************************************************************
// Make the words contain only letters and count the words and letters 
void Proccessing(LetterFreqStruct &FreqStruct, string &correctWord, string inputWord, int x)
{ 
	correctWord = makeCleanWord(inputWord);
	if (correctWord != "")
	{
		// If correctWord has something in it then increment
		// the word counter, letter counter, fill the frequency
		// and fill the words and ID palindromes. If not, skip these to avoid issues
		FreqStruct.wordCounter++;
		FreqStruct.letterCounter += correctWord.size();
		fillFreq(correctWord, FreqStruct);
		IDpalindrome(correctWord, FreqStruct);
		FreqStruct.words[x] = correctWord;
	}
}

//****************************************************************************************************************
// Identify the palindromes in the file

void IDpalindrome(string candidate, LetterFreqStruct &FreqStruct)
{
     int len = candidate.length();
     bool isPalindrome = true;
     if(len < 3) //Eliminate single and double letter words
     { 
            isPalindrome = false; 
     } else
     {
     for(int j=0; j<len/2; j++) //Cut the candidate in half and compare the halves
     {
             if (candidate[j] != candidate[len -1 -j])
             {
                    isPalindrome = false;
                    break;
             }
     }
     }
     if(isPalindrome){
             // Increase the palindrome counter and save the word at the counters point in the array
             FreqStruct.palindCounter++;
             FreqStruct.palindromes[FreqStruct.palindCounter - 1] = candidate;
     }
}

             
             
              
     
 
