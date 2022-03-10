#include<iostream>

#include<stdio.h>

#include<fstream>

#include<string>

#include<cstring>

#include<filesystem>

#include <sys/ioctl.h>

#include <unistd.h>

using namespace std;

class entry {
  public:
    int year;
  int month;
  int day;
  char data[1000];
};

bool isNumber(const string & str) {
  for (char
    const & c: str) {
    if (std::isdigit(c) == 0) return false;
  }
  return true;
}

void clear() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, & w);
  cout << string(w.ws_row, '\n');
}

void getdata() {
  string dBuffer;
  entry obj;
  ofstream dataO("store.dat", ios::app);
  clear();
  cout << "year:";
  cin >> obj.year;
  cout << "month:";
  cin >> obj.month;
  cout << "day:";
  cin >> obj.day;
  cout << "entry:";
  cin >> ws;
  getline(cin, dBuffer);
  strcpy(obj.data, dBuffer.c_str());;
  dataO.write((char * ) & obj, sizeof(obj));
  dataO.close();
}

int main() {
  string inp;
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, & w);
  int choice;
  while (1) {
    clear();
    cout << "load(1)\nsave(2)\nexit(3)\n>>>";
    cin >> inp;

    if (inp == "2") {
      getdata();
    } else {
      if (inp == "1") {

        ifstream sizeS("store.dat", ios:: in );
        const auto begin = sizeS.tellg();
        sizeS.seekg(0, ios::end);
        const auto end = sizeS.tellg();
        const auto fsize = (end - begin);
        sizeS.close();
        ifstream fout("store.dat", ios:: in );
        entry obj[(fsize / 1024) + 1];
        // Reading from file into object "obj"
        fout.read((char * ) & obj[0], sizeof(obj[0]));
        for (int i = 1; !fout.eof(); i++) {
          fout.read((char * ) & obj[i], sizeof(obj[i]));
        }
        fout.close();
        clear();
        int i = 0;
        bool running = true;
        while (running) {

          int x = 0;
          for (; i != (sizeof(obj) / 1012) & x <= (w.ws_row - 8); i++) {
            cout << "(" << i << ")----" << obj[i].year << "/" << obj[i].month << "/" << obj[i].day << "\n";
            x++;
          }
          cout << "(n)ext page\n(p)revious page\n(e)xit\n\n";
          cout << ">>>";
          cin >> inp;
          if (isNumber(inp)) {
            int buff = stoi(inp);
            while (1) {
              clear();
              cout << obj[buff].year << "/" << obj[buff].month << "/" << obj[buff].day << "\n\n" << obj[buff].data << "\n\n(e)xit\n>>>";
              i = 0;
              cin >> inp;
              if (inp == "e") {
                inp = "";
                clear();
                break;
              }
            }

          } else {
            if (inp == "n") {
              x = 0;
            } else {
              if (inp == "e") {
                running = false;
              } else {
                if (inp == "p") {
                  i = i - w.ws_row + 2;
                } else {
                  i = 0;
                }
              }
            }
            clear();
          }
        }
      } else {
        if (inp == "3") {
          exit(1);
        }
      }

    }
  }
}
