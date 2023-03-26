#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " file" << std::endl;
        exit(1);
    }
    map<string, int> fileCount;

    ifstream myReadFile;
    myReadFile.open(argv[1]);
    string output;
    if (myReadFile.is_open())
    {
        for (int i = 1; !myReadFile.eof(); i++)
        {
            myReadFile >> output;
            //cout<<i<<" "<<output<<endl;
            for (size_t pos = output.find_last_of('/');
                    pos != string::npos;
                    pos = output.find_last_of('/'))
            {
                output = output.substr(0, pos);
                //cout << "    " << output << endl;
                if (fileCount.count(output) == 0)
                    fileCount[output] = 1;
                else
                    fileCount[output]++;
            }

        }
    }
    myReadFile.close();
    // show content:
    std::cout<< "contents:" << endl;
    for (std::map<string,int>::iterator it=fileCount.begin(); it!=fileCount.end(); ++it)
        std::cout << std::setw(6) << it->second << " " << it->first << '\n';
    return 0;
}


