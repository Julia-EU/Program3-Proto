#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

struct Sentiment {
    string word;
    double value;
};

bool isValid(string str);

void readFile(vector <Sentiment>& v1,
    vector<Sentiment>& posV1,
    vector<Sentiment>& negV1,
    vector<Sentiment>& neutral);

void printVector(vector<Sentiment> const& v1);

string upperstr(string str);

string noPunct(string str);

string getPunct(string str1, string str2);

void getSentiment(string Review, vector<Sentiment> v1);

void changeSentiment(string Review, vector<Sentiment> v1,
    vector<Sentiment> posV1,
    vector<Sentiment> negV1,
    vector<Sentiment>& posV2,
    vector<Sentiment>& negV2,
    char choice);

