#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Sentiment {
    string word;
    double value;
};

bool isValid(string str) {
    return str.find_first_not_of("-.0123456789") == string::npos;
}

void readFile(vector <Sentiment>& v1,
    vector<Sentiment>& posV1,
    vector<Sentiment>& negV1,
    vector<Sentiment>& neutral) {

    ifstream S_File;

    S_File.open("sentiment.txt");
    if (!S_File.is_open()) {
        cout << "File did not open\n";
        return;

    }

    string S_Str, tempWord, tempValue;
    Sentiment tempRecord;
    int commaPos;
    while (S_File >> S_Str) {
        commaPos = S_Str.find(',');              //find position of comma
        tempWord = S_Str.substr(0, commaPos);    //set tempWord to instr up to comma
        tempValue = S_Str.substr(commaPos + 1);  //set tempValue to rest of instr
        if (isValid(tempValue)) {                //if tempValue is valid (0-9)
            tempRecord.word = tempWord;          //set up sentimentFile record to hold word and file together
            tempRecord.value = stod(tempValue);  //convert to float
            v1.push_back(tempRecord);            //add to vector

            /*cout << tempRecord.word << " " << tempRecord.value << endl;*/  //To print entire vector using readFile function 

            if (tempRecord.value > 1.50)
                posV1.push_back(tempRecord);
            else if (tempRecord.value < -1.50)
                negV1.push_back(tempRecord);
            else {
                neutral.push_back(tempRecord);
            }
        }

        else {
            cout << "ERROR " << tempWord << endl;
        }

    }

    S_File.close();
}

void printVector(vector<Sentiment> const& v1) {
    for (int i = 0; i < v1.size(); i++)
        cout << v1[i].word << " " << v1[i].value << endl;
}

string upperstr(string str) {
    string temp;
    for (int i = 0; i < str.length(); i++) {
        temp += toupper(str[i]);
    }
    return temp;
}

string noPunct(string str) {

    int temp = 0;
    int temp2 = 0;
    string str2;

    if (ispunct(str[str.length() - 1])) {
        temp = str.length() - 1;
        str2 = str.substr(0, temp);
    } 

    else {
        str2 = str;
    }

    if (ispunct(str2[0])) {
        temp2 = 0;
        str2 = str2.substr(temp2 + 1);
    }

    return str2;

}

string getPunct(string str1, string str2) {

    int tempchr;
    for (int i = 0; i < str2.size(); i++) {
        if (!isalpha(toupper(str2[i]))) {
            tempchr = i;
            string chr(1, str2[i]);
            if (tempchr == 0) {
                str1 = chr + str1;
            }

            else {
                str1 = str1 + chr;
            }
        }
    }

    return str1;
}

//LinearSearch algorithm modified from textbook "Figure 9.1.1: Linear search algorithm."
int vectorSearch(vector<Sentiment> v1, string word) {
    int i;
    for (i = 0; i < v1.size(); ++i) {
        if (upperstr(v1[i].word) == upperstr(word)) {
            return i;
        }
    }

    return -1; /* not found */
}

void getSentiment(string Review, vector<Sentiment> v1) {

    ifstream rev_File;
    string filename = Review + ".txt";

    rev_File.open(filename);
    if (!rev_File.is_open()) {
        cout << "File did not open\n";
        return;
    }

    string revWord_punct; //Original review word with punctuation as applicable
    string revWord;       //New word without punctuation as applicable
    vector<Sentiment> sentiments;
    vector<double> count;
    while (rev_File >> revWord_punct) {
        cout << revWord_punct << " ";
        for (int i = 0; i < v1.size(); i++) {
            revWord = noPunct(revWord_punct);
            if (upperstr(v1[i].word) == upperstr(revWord)) {
                sentiments.push_back(v1[i]);
                count.push_back(v1[i].value); //honestly don't know why I did this count. I don't think I need a separate vector for just the values.
            }
        }
    }

    cout << endl;
    cout << endl;
    double sentVal = 0;
    for (int i = 0; i < sentiments.size(); i++) {
        cout << sentiments[i].word << "  " << sentiments[i].value << endl;
        sentVal += sentiments[i].value;
    }

    cout << endl;
    cout << "Sentiment Value is: " << sentVal;
}

void changeSentiment(string Review, vector<Sentiment> v1,
    vector<Sentiment> posV1,
    vector<Sentiment> negV1,
    vector<Sentiment> &posV2,
    vector<Sentiment> &negV2,
    char choice) {

    cout << endl;

    string filename = Review + ".txt";
    string outFileName = Review + "Output.txt"; //Matching output file name

    ifstream rev_File;    //To read input file
    ofstream out_File;    //To write to output file
    string revWord_punct; //Original review word with punctuation as applicable
    string revWord;       //Review word without punctuation as applicable
    string newWord;       //New review word with punctuation as applicable

    out_File.open(outFileName);
    rev_File.open(filename);
    if (!rev_File.is_open()) {
        cout << "File did not open\n";
        return;
    }

    switch (choice) {
        case 'P': {

            string choiceword = "positive";
            int wordPos; //To find the position of each word at a time if it exists in the sentiment file

            cout << "Your more POSITIVE review is:\n" << endl;

            while (rev_File >> revWord_punct) { //Getting each string word by word
                revWord = noPunct(revWord_punct); //Removing punctuation to reference word exactly as is in sentiment file
                wordPos = vectorSearch(v1, revWord); //Searching for word in sentiment file. Returns word index or -1 if not found.
                if (wordPos == -1) { // if word is NOT in the sentiment file
                    cout << revWord_punct << " ";
                }

                else {
                    if (v1[wordPos].value < -1.00) {
                        negV2.push_back(v1[wordPos]);
                        int random = rand() % (posV1.size() - 1);
                        revWord = posV1[random].word;               //replacing revWord with random word from positive sentiments
                        posV2.push_back(posV1[random]);

                        newWord = getPunct(revWord, revWord_punct);  //Adding back any punctuation that was removed
                        cout << newWord << " ";
                    }

                    else {
                        cout << revWord_punct << " ";
                    }
                }
            }

            rev_File.close();
            out_File.close();

            cout << endl;
            
            cout << "\nThese negative words were replaced with more positive ones:" << endl;
            for (int i = 0; i < posV2.size(); i++) {
                cout << setw(15) << right << negV2[i].word << "  " << negV2[i].value;
                cout << setw(20) << right << posV2[i].word << "  " << posV2[i].value << endl;
            }

            break;
        }
    }

}
