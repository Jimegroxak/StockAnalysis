//Noah Petzinger
//May 24, 2023
//Helper program to ProcessStockData.cpp
//Splits data from scandi.csv into individual csv files for each stock
//Done in order to improve memory usage

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void ReadFile(string fileName);
void AddToFile(vector<string> row);
string removeSpaces(string str);

string fileName = "scandi.csv";

int main()
{
    ReadFile(fileName);

    return 0;
}

void ReadFile(string fileName)
{
    ifstream fin;

    fin.open(fileName, ios::in);

    vector<string> row;
    string line, word;

    if (fin.is_open())
    {
        while (getline(fin, line))
        {
            row.clear();

            stringstream str(line);

            while(getline(str, word, ','))
            {
                row.push_back(word);
            }

            //check to exclude auction trades
            if (row[14] == "" || row[14] == "XT")
                AddToFile(row);
        }
    }
}

void AddToFile(vector<string> row)
{
    string fileName = "StockFiles/" + removeSpaces(row[0]) + ".csv";

    ofstream fout;

    fout.open(fileName, ios::app);

    for(int i = 0; i < row.size(); i++)
    {
        fout << row[i];
        if (i != row.size()-1)
            fout << ',';
    }

    fout << '\n';

    fout.close();
}

// Function to remove all spaces from a given string
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}