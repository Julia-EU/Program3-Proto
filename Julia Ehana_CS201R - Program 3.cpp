// Julia Ehana_CS201R - Program 3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Program3_Header.h"

/*What this program does essentially is take a review txt file and 
replace negative words found in the file (words with values less than -1.00) with more positive ones.
If you run the program as is, you'll see what I mean by "values" - ignore the total sentiment value at the end
The replacement comes from a vector of positive words and corresponding values that I extracted from another file called "sentiment.txt"
All_sentiments is a vector of all words
Pos_Sentiments is a vector of the positive ones
Neg_sentiments is a vector of the negative ones

That said, the changeSentiment function takes all these vectors plus additional ones (to store and print only changed words each time the program runs)
It takes a string which will be the name of the review file, and it takes a choice - in this case 'P'
('P' tells it that I want the review to be more positive. I will be including more choices later)
The function reads the file and makes the change for each word it deems too negative
Positive words are chosen at random from the Pos_Sentiments vector
Right now, I have it set to just output the changed review to the screen and not to a file */

/*So basically I need the changeSentiment function to do the following:
1. Output the new review to a txt file (I already named and opened the output file to be written in the function)
2. Limit the amount of characters PER LINE to 80 in the output file (including whitespace I believe) */

/*The getSentiment function just outputs the original review, all the words in said review that 
are also in the All_Sentiments vector (from sentiment.txt file), and their corresponding values for reference*/


int main()
{
    srand(time(0));
    vector<Sentiment> All_Sentiments, Pos_Sentiments, Neg_Sentiments, Neutral_Sentiments, Pos_Sentiments2, Neg_Sentiments2; 
    //Ignore the pos_sentiments2 and neg_sentiments2, its for extra stuff...

    readFile(All_Sentiments, Pos_Sentiments, Neg_Sentiments, Neutral_Sentiments);

    string Filename = "review1"; //test file. There are two more test files "review2" and "review3". You can replace with those.
    char UserChoice = 'P';       //in the program, the user will be making a choice I need to put in the changeSentiment function below
                                 //for now lets just work with the only choice I've coded for lol


    getSentiment(Filename, All_Sentiments); 

    cout << endl;
    cout << endl;

    //This function is where I need the assistance :D
    changeSentiment(Filename, All_Sentiments,
        Pos_Sentiments,
        Neg_Sentiments,
        Pos_Sentiments2,
        Neg_Sentiments2,
        'P');

}
