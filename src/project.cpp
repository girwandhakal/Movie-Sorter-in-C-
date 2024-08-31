/*
 Name: Girwan Dhakal
 Email: gdhakal@crimson.ua.edu
 Course Section: Fall 2023 CS 201
 Homework #:0
 Instructions to Compile: g++ homework0.cpp
 Instructions to Execute: .\a.exe dbfile0.txt
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<chrono>

using namespace std;


class Movie
{
    public:
    string getYear() const
    {
        return year;
    }
    string getActors() const
    {
        return actors;
    }
    string getName() const
    {
        return title;
    }

    string year;
    string actors;
    string title;
};

bool sortByTitle(Movie* a, Movie* b)
{
    if(a->getName() < b->getName())
    {
        return true;
    }
    else if(a->getName() == b->getName())
    {
        return (a->getYear() < b->getYear());
    }
    else
    {
        return false;
    }
}

bool sortByYear(Movie* a, Movie* b)
{
    if(a->getYear()  < b->getYear() )
    {
        return true;
    }
    else if(a->getYear()  == b->getYear() )
    {
        return(a->getName() < b->getName());
    }
    else
    {
        return false;
    }
}

string getFileName_sortByName(string inputFile)
{
    int pos = inputFile.find('.');
    string fileName;
    fileName.append(inputFile, 0 , pos);
    fileName += "ByName.txt";
    return fileName;
}

string getFileName_sortByYear(string inputFile)
{
    int pos = inputFile.find('.');
    string fileName;
    fileName.append(inputFile, 0 , pos);
    fileName += "ByYear.txt";
    return fileName;
}

int main(int argc, char* argv[])
{

    if(argc != 2)
    {
        cout << "Usage: .\a.exe input.txt" << endl;
        return 1;
    }
    string inputFile = argv[1];
    ifstream inFS;
    inFS.open(inputFile);
    if(!inFS.is_open())
    {
        cout << "File cannot be opened" << endl;
    }

    vector<Movie*>v; //vector of Movie objects created
    while(inFS) // creates the collection
    {
        Movie* m = new Movie; // dynamically creates a movie object for each line
        getline(inFS, m->title, '(');
        getline(inFS, m->year,')');
        inFS.get(); // gets rid of the '/' after the year
        getline(inFS, m->actors);
        if(!inFS) // checks if there is an error in the buffer. stop it from inputting an empty line at the end
        {
            break;
        }
        v.push_back(m);
    }
    inFS.close();
    

    sort(v.begin(), v.end(), sortByTitle); // sorts based on title


    ofstream dataFS;
    dataFS.open(getFileName_sortByName(inputFile));
    for(auto item : v) //outputs into the text file
    {
        dataFS << item->title << "(" << item->year << ")/" << item->actors << endl;
    }
    dataFS.close();

    
    sort(v.begin(), v.end(), sortByYear);

    dataFS.open(getFileName_sortByYear(inputFile));
    for(auto item : v) //outputs into text file
    {
        dataFS << item->title << "(" << item->year << ")/" << item->actors << endl;
    }
    dataFS.close();

    // clear the allocated memory
    for( auto item : v)
    {
        delete item;
    }
    v.clear();

}