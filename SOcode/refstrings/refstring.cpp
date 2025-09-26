#include <cstring>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {

    int count = 0;
    filesystem::path p = "/home/igor/Unioeste/3ano/SO/P2/dijkstra/dijkstra_2m6.trace";
    filesystem::path refstr = "./dijkstra.rstr";
    ifstream sourcefile(p);
    ofstream destfile(refstr);

    if (sourcefile) {
        cout << "File opened successfully: " << p << endl;
    } else {
        cout << "Failed to open file: " << p << endl;
    }

    string olds = "", news = "";

    for (string line; getline(sourcefile, line); ) {
        if (line[0] == '=') {
            continue;
    }

        size_t pos = line.find(',', 3);
        pos -= 3;
        while(line[pos] != ' '){
            news += line[pos];
            pos--;
        }

        reverse(news.begin(), news.end());
        if(news != olds){
            destfile << news << ", ";
            count++;
        }
        olds = news;
        news = "";

    }

    sourcefile.close();
    destfile.close();
    printf("%d entradas na reference string \n", count);

    return 0;

} 