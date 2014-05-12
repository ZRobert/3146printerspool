/*
Group 4: Derek Mayfield, Robert Payne, Maybellin Burgos, Laura Delgado
        Rose Yen
ITCS 3146-096
2/24/2013
printer.cpp

The idea behind the project is to create a program that runs
looking for files added to the directory to "print." In order to
simulate the files being printed we will output them in notepad
after a simulated amount of printing time(5 seconds). The idea is to queue
the files in order and output out to the notepad based on the
contents of the queue.
*/
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <queue>
#include <fstream>
#include<stdlib.h>
using namespace std;

//Creates the files that will be spooled to the 'printer'
//Input: reference to the queue of file names
//Output: Boolean value for success/fail of file creation
bool createFiles(queue<string> &qf);

//Outputs the file being printed into notepad
//Input: reference to the queue with file names
//Output: opens notepad with txt file; does not have a return value
void printFile(queue<string> &qf);

int main()
{
    system("color f9");
    cout<<"Printer Deamon" <<endl;

    long deltaTime = time(0);       //used to track the timer of the printer
    queue<string> fileQueue;        //stores the filenames as strings to the queue

    if(createFiles(fileQueue))      //checks to make sure that the files have been
                                    //created successfully
        cout<<"Files created";
    else
        cout<<"Files not created :(";
    cout<<endl;

    //infinate loop that checks deltaTime relative to the CPU's clock
    while(1)
    {
        //Every 5 seconds searches the directory for a new file to put in
        //the queue

        if(deltaTime + 5 < time(0)) {

            if(!fileQueue.empty()){     //checks the queue to see if there are
                                        //files that need to be printed

                cout<<"Printing..." <<endl;
                printFile(fileQueue);   //calls the printFile function if needed
            }
            else
                cout<<"Not printing..." <<endl;
             deltaTime = time(0);       //resets the timer on the printer
            cout<<"Remaining jobs to print: " << fileQueue.size() <<endl;
        }                               //outputs the number of remaining jobs for
                                        //printer

    }
    return 0;
}

void printFile(queue<string> &fq){

        system(fq.front().c_str());     //outputs the txt file to notepad by filename
        fq.pop();
}

bool createFiles(queue<string> &qf){


    fstream wf;                         //the writefile
    FILE *cf;                           //used to create the files
    //creating the files to be printed
    //can add more if desired
    cf = fopen("print1.txt", "w");
    fclose(cf);
    cf = fopen("print2.txt", "w");
    fclose(cf);
    cf = fopen("print3.txt", "w");
    fclose(cf);

    //writing to the files so we have something to show for output
    //just using simple loops to write ASCII values to the files
    wf.open("print1.txt");
    if(!wf.good())              //checks to make sure that the file
                                //will open properly for writing
        return false;          //returns false if not
    for(int i = 0; i < 50; i++)
        wf<<(char)( i + 64);
    qf.push("print1.txt");
    wf.close();

    wf.open("print2.txt");
    if(!wf.good())
        return false;
    for(int i = 0; i < 10; i++)
        wf<<(char)( i + 74);
    qf.push("print2.txt");
    wf.close();

    wf.open("print3.txt");
    if(!wf.good())
        return false;
    for(int i = 0; i < 35; i++){
        wf<<(char) (i+64);
        if(i%5 == 4)
            wf<<'\n';               //creates line breaks in the file after
                                    //every fifth character
    }
    qf.push("print3.txt");
    wf.close();

    return true;                    //returns true if successfully created and
                                     //wrote to each file
}
