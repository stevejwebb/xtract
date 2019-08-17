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
    cout << endl << "usage: " << programName << " <filename>" << endl;
    exit(0);
}

int main(int argc, const char * argv[]) {
    if ( argc !=2 )
    {
        usage(argv[0]);
    }   
    string programName = argv[0];
    string inputFileName = argv[1];
    ifstream inFile;
    ofstream outFile;
    string outFileName;
    string line;
    bool foundSection;
    string timeStamp;
    string counterOutput;

    //try to open file
    inFile.open(inputFileName);
    if (inFile.is_open()) {
        cout << "File " << inputFileName << " is open." << endl;
    }
    else{
        cout << "Error could not open file " << inputFileName << endl;
        exit(-1);
    }

    //main loop for all counters
    //the idea is to loop through all the counters and produce a csv file for each one
    for (string counterLoop : counters) {

    }


    return 0;
}