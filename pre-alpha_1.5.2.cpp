#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<cstring>
#include<filesystem>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

using namespace std;

#define entrySize 1000

class entry {
  public:
    int year;
  int month;
  int day;
  char data[entrySize];
};

class BufferToggle
{
    private:
        struct termios t;
    public:
        void off(void)
        {
            tcgetattr(STDIN_FILENO, &t);
            t.c_lflag &= ~ICANON;
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
        }

        void on(void)
        {
            tcgetattr(STDIN_FILENO, &t);
            t.c_lflag |= ICANON;
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
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
	BufferToggle bt;
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
        ifstream sizeS("store.dat", ios::in );
        const auto begin = sizeS.tellg();
        sizeS.seekg(0, ios::end);
        const auto end = sizeS.tellg();
        const auto fsize = (end - begin);
        sizeS.close();
        ifstream fout("store.dat", ios::in );
	// need to make this work with entry size but for now if you dont alter the entry size it should work lol
        entry obj[(fsize / 1024) + 1];
        // Reading from file into object "obj"
        fout.read((char * ) & obj[0], sizeof(obj[0]));
	int objNum = 0;
        for (int i = 1; !fout.eof(); i++) {
		objNum++;
          fout.read((char * ) & obj[i], sizeof(obj[i]));
        }
        fout.close();
        clear();
        int i = 0;
        bool running = true;
        while (running) {
          int x = 0;// will say it yet again this needs to be made variable so it can work with any entry size but for now its ok
          for (; i != (sizeof(obj) / 1012) & x <= (w.ws_row - 8); i++) {
            cout << "(" << i << ")----" << obj[i].year << "/" << obj[i].month << "/" << obj[i].day << "\n";
            x++;
          }
          cout << "(n)ext page\n(p)revious page\n(e)xit\n" << objNum << "\n";
          cout << ">>>";
          cin >> inp;
          if (isNumber(inp)) {
            int buff = stoi(inp);
            while (1) {
              clear();
              cout << obj[buff].year << "/" << obj[buff].month << "/" << obj[buff].day << "\n\n" << obj[buff].data << "\n\n(x)it\n(e)dit\n>>>";
              i = 0;
              cin >> inp;
	      if (inp == "e"){
			char buffer[entrySize];
			char buffer2[entrySize];
			for (int i = 0; i != sizeof(obj[buff].data); i++){
			buffer[i] = obj[buff].data[i];
			buffer2[i] = buffer[i];
			}
			bt.off();
			running = true;
			int z = 0;
			int c;
			char tes[1];
			while(running){
				    	clear();
				    	buffer[z] = '#';
				    	cout << buffer << "\n\n(x)it";
				    	c = getchar();
				    	buffer[z] = buffer2[z];
				    	tes[0] = c;
				    	if (tes[0] == 'j' & z < entrySize-w.ws_col){z+=w.ws_col;}else{
				    	if (tes[0] == 'k' & z > 0+w.ws_col){z-=w.ws_col;}else{
            			    	if (tes[0] == 'l' & z < entrySize){z++;}else{
            				if (tes[0] == 'h' & z > 0){z--;}else{
				    	if (tes[0] == 'r'){c = getchar();buffer2[z] = c;}}}}}
					if (tes[0] == 'x'){
                				for (int i = 0; i != sizeof(obj[buff].data); i++){
			          			obj[buff].data[i] = buffer2[i];
                				}
						ofstream file("store.dat");
						for (int i = 0; i != objNum; i++) {
							file.write((char * ) & obj[i], sizeof(obj[i]));
						}
						file.close();
						break;
					}
			}
	      }
              if (inp == "x") {
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
