// basic file operations
#include <iostream>
#include <iomanip>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <sstream>
#include <ctime>
#include "sys/stat.h"
using namespace std;

string timestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // create timestamp from various components of tm structure.
    ostringstream os;
    os << setfill('0')
       // Year
       << setw(4) << 1900 + ltm->tm_year
       // Month
       << "-" << setw(2) << ltm->tm_mon
       // Day
       << "-" << setw(2) << ltm->tm_mday
       // Hours
       << "_" << setw(2) << ltm->tm_hour
       // Minutes
       << "-" << setw(2) << ltm->tm_min
       // Seconds
       << "-" << setw(2) << ltm->tm_sec;
    return os.str();
}

bool createDirectory(string dirname, string& errorMsg) {
    // make directory
    errorMsg = "";
    cout << "createDirectory: dirname " << dirname << endl;
    int check = (mkdir(dirname.c_str(), 0777) == -1);
    if (check != 0)
        errorMsg = strerror(errno);
    cout << "createDirectory: check " << check << " errorMsg " << errorMsg << endl;
    return (check == 0);
}

int main () {
    // time test
    time_t ttime = time(0);

    char* dt = ctime(&ttime);
    cout << "The current local date and time is: " << dt << endl;

    tm *gmt_time = gmtime(&ttime);
    dt = asctime(gmt_time);
    cout << "The current UTC date and time is:"<< dt << endl;
    string tstamp = timestamp();
    cout << "timestamp '" << tstamp << "'" << endl;
     
    string dir = "dir-"+tstamp;
    cout << "good dir " << dir << endl;
    string errorMsg1 = "";
    if (createDirectory(dir, errorMsg1))
        cout << "createDirectory succeeds  " << endl;
    else
        cout << "createDirectory failed: " << errorMsg1 << endl;
    cout << endl;

    string bad_dir = "invalid/directory";
    cout << "bad dir " << bad_dir << endl;
    string errorMsg2 = "";
    if (createDirectory(bad_dir, errorMsg2))
        cout << "createDirectory succeeds  " << endl;
    else
        cout << "createDirectory failed: " << errorMsg2 << endl;

    // write to file in directory
    ofstream myfile;
    string filename = dir+"/example.txt";
    cout << "filename " << filename << endl;
    myfile.open(filename);
    myfile << "Writing this to a file." << endl;;
    myfile.close();
    return 0;
}
