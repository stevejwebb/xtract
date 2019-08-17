//
//  main.cpp
//  wtm4k-stat-analysis
//
//  Created by Steven Webb on 14/08/2019.
//  Copyright © 2019 Steven Webb. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> counters = {
"discards",
"in-unicast-pkts",
"in-broadcast-pkts",
"in-multicast-pkts",
"in-fcs-errors",
"in-undersize-pkts",
"in-oversize-pkts",
"in-oversize-pkts",
"in-fragments",
"in-jabbers",
"collisions",
"in-total-packets",
"in-octets",
"out-octets",
"out-unicast-pkts",
"out-broadcast-pkts",
"out-multicast-pkts",
"out-total-packets"
};


void usage(string programName){
    cout << endl << "usage: " << programName << " <filename> <counter>" << endl;
    cout << endl << "Counters that can be processed:" << endl;
    for (string output : counters)
    {
        cout << output << endl;
    }
    exit(0);
}


int main(int argc, const char * argv[]) {
    if ( argc !=3 )
    {
        usage(argv[0]);
    }   
    string programName = argv[0];
    string inputFileName = argv[1];
    string counterSpecify = argv[2];
    
    //check that a valid counter is used in the argument
    bool validCounter = false;
    for (string check : counters)
    {
        if ( check == counterSpecify) validCounter = true;
    }
    if (!validCounter)
    {
        cout << "Not a valid counter as input!" << endl;
        usage(programName);
    }
    
    ifstream inFile;
    ofstream outFile;
    string outFileName = "wtm-qhour-" + counterSpecify + ".csv";
    
    //try to open file
    inFile.open(inputFileName);
    if (inFile.is_open()) {
        cout << "File " << inputFileName << " is open." << endl;
    }
    else{
        cout << "Error could not open file " << inputFileName << endl;
        exit(-1);
    }

    string line;
    bool foundSection;
    while (inFile)
    {
        getline(inFile, line);
        //this is the start of the stats
        if (line.find("stats-history qhour") != string::npos)
        {
            //found the section
            foundSection = true;
            break;
        }
    }// this should position the file at the right section.
    if (!foundSection)
    {
        cout << "Could not find the start of the  stats!" << endl;;
        exit(-1);
    }

    //must be okay so open file to write to
    outFile.open(outFileName);

    if (outFile.is_open())
    {
        cout << "Out file open " << outFileName << endl;
    }else
    {
        cout << "Could not open file " << outFileName << " for writing" << endl;
        exit(-1);
    }

    //process the stats
    //process the stats
    string timeStamp;
    string counterOutput;
    //write the header to file
    outFile << "Time Stamp,GigabitEthernet1/1,GigabitEthernet1/2,Radio1,TenGigE1/1,TenGigE1/2";
    
    while (inFile)
    {           
        getline(inFile, line);
        if (line.find("timestamp") != string::npos)
        {
            //found string timestamp
            timeStamp = line;
            outFile << endl;
            outFile << timeStamp << "," ;
        };
        if (line.find(counterSpecify) != string::npos)
        {
            //found string timestamp
            //in_fcs_errors = line;
            outFile << line << ",";
        };
    }
    cout << endl << "Done! " << outFileName << " created." << endl;
    //Tidy up
    outFile.close();
    inFile.close();
    return 0;
}
          