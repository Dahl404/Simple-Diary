#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>

// would like to make these functions and classes in a seperate file which i
// refrence but that will be for next update
using namespace std;
// if you change the entry size you will need to create a new data file to store
// them
//***create its own new dat files and connect to them is WIP(bigger issues to
//deal with)
//***might make it where you can select entry size in the program and it will
//load it to the approriate file
//***i would like to make it have variable entry lengths loaded and unloaded
//from one file
#define entrySize 6000
// this is the entry class; the heart of the program
class entry {
 public:
  int year;
  int month;
  int day;
  char data[entrySize];
};

// used later to find the size of the window
struct winsize w;

// got this off stackoverflow; don't fully understand it but its just a place
// holder till i make one
class bufferToggle {
 private:
  struct termios t;

 public:
  void off(void) {
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
  }
  void on(void) {
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
  }
};

// clears screen
void clear(winsize w) {
  // would like to make this without the str function so i could remove the
  // header
  cout << string(w.ws_row, '\n');
}
// prompts user for data then loads it into file
void getdata(bufferToggle bt) {
  //****alot of this stuff i could input into the function from main but it
  //works for now would like to find a work around from using this str so i dont
  // have to import the whole file
  string dBuffer;
  entry obj;
  ofstream dataO("store.dat", ios::app);
  clear(w);
  bt.on();
  cout << "year:";
  cin >> obj.year;
  cout << "month:";
  cin >> obj.month;
  cout << "day:";
  cin >> obj.day;
  cout << "entry:";
  cin >> ws;
  getline(cin, dBuffer);
  // used to use strcpy but i made this so i didnt have to include the entire
  // header file
  // could have taken out the brackets but they make it more readble
  for (int i = 0; i != dBuffer.length(); i++) {
    obj.data[i] = dBuffer[i];
  }
  dataO.write((char*)&obj, sizeof(obj));
  dataO.close();
  bt.off();
}

int main() {
  //-----dep assets for testing purposes
  //-----

  //*** would like to make a single file stream that everything uses instead of
  //declaring new ones but that will be in the next update
  int x = 0;
  int i = 0;
  int c;
  entry objT;
  // used to hold the character your own durring editing
  char cBuff[1];
  // used to hold your input(ik i could make it work with just the int but i
  // have bigger things on my plate rn here)
  char tes[1];

  //-----turns off input buffer
  bufferToggle bt;
  bt.off();

  //---Main Loop
  while (true) {
    // moved this here and some other places so it can adapt to variable
    // terminal sizes would like to make it a function you press a key for but i
    // think it would just over complicate it less eff. but more user friendly
    // and simpler ui
    //*** would like to make a seperate thread just for checking term size every
    //few seconds
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    //-----
    clear(w);
    cout << "(l)oad\n(s)ave\n(q)uit\n";
    c = getchar();
    tes[0] = c;
    if (tes[0] == 's') {
      getdata(bt);
    } else {
      if (tes[0] == 'l') {
        x = 0;
        //-----get file size
        ifstream file("store.dat", ios::in);
        const auto begin = file.tellg();
        file.seekg(0, ios::end);
        const auto end = file.tellg();
        const auto fsize = (end - begin);
        file.close();
        //-----
        ifstream fout("store.dat", ios::in);

        entry obj[fsize / sizeof(objT)];
        // Reading from file into object "obj"
        fout.read((char*)&obj[0], sizeof(obj[0]));
        for (int i = 1; !fout.eof(); i++) {
          fout.read((char*)&obj[i], sizeof(obj[i]));
        }
        fout.close();
        while (true) {
          // another case of wanting it to update; same as line 93 (as of now)
          ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
          clear(w);
          // this peints the entries up tot he end of a terminal page then
          // pauses
          for (; i != (sizeof(obj) / sizeof(objT)) & x <= (w.ws_row - 8); i++) {
            cout << "(" << i << ")----" << obj[i].year << "/" << obj[i].month
                 << "/" << obj[i].day << "\n";
            x++;
          }
          cout << "(n)ext page\n(p)revious page\n(q)uit\n";
          c = getchar();
          tes[0] = c;
          //*****debating having the brackets seeing as they arnt needed but it
          //does help readability
          if (tes[0] == 'n') {
            x = 0;
          } else {
            if (tes[0] == 'q') {
              i = 0;
              break;
            } else {
              if (tes[0] == 'p') {
                i = i - w.ws_row + 2;
              } else {
                if (isdigit(tes[0])) {
                  //***should replace buff int with 'tes[0] - '0'' or something
                  //similiar later
                  int buff = tes[0] - '0';
                  while (true) {
                    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
                    clear(w);
                    cout << obj[buff].year << "/" << obj[buff].month << "/"
                         << obj[buff].day << "\n\n"
                         << obj[buff].data << "\n\n(q)uit\n(e)dit\n";
                    i = 0;
                    c = getchar();
                    tes[0] = c;
                    if (tes[0] == 'e') {
                      char buffer[entrySize];
                      for (int i = 0; i != sizeof(obj[buff].data); i++) {
                        buffer[i] = obj[buff].data[i];
                      }
                      int z = 0;
                      while (true) {
                        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
                        clear(w);
                        cBuff[0] = buffer[z];
                        buffer[z] = '#';
                        cout << buffer
                             << "\n\n(r)eplace\n(i)nsert\n(s)ave\n(q)uit";
                        c = getchar();
                        tes[0] = c;
                        buffer[z] = cBuff[0];
                        if (tes[0] == 'j' & z < entrySize - w.ws_col) {
                          z += w.ws_col;
                        } else {
                          if (tes[0] == 'k' & z > 0 + w.ws_col) {
                            z -= w.ws_col;
                          } else {
                            if (tes[0] == 'l' & z < entrySize) {
                              z++;
                            } else {
                              if (tes[0] == 'h' & z > 0) {
                                z--;
                              } else {
                                if (tes[0] == 's') {
                                  buffer[z] = cBuff[0];
                                  for (int i = 0; i != sizeof(obj[buff].data);
                                       i++) {
                                    obj[buff].data[i] = buffer[i];
                                  }
                                  ofstream file("store.dat");
                                  for (int i = 0;
                                       i != sizeof(obj) / sizeof(obj[0]); i++) {
                                    file.write((char*)&obj[i], sizeof(obj[i]));
                                  }
                                  file.close();
                                  break;
                                } else {
                                  if (tes[0] == 'r') {
                                    c = getchar();
                                    buffer[z] = c;
                                  } else {
                                    if (tes[0] == 'i') {
                                      int space;
                                      while (true) {
                                        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
                                        clear(w);
                                        cout << buffer << "\n\n(|)exit";
                                        c = getchar();
                                        tes[0] = c;
                                        if (tes[0] == '|') {
                                          break;
                                        }
                                        for (int i = entrySize; i != z; i--) {
                                          buffer[i + 1] = buffer[i];
                                        }
                                        buffer[z] = tes[0];
                                        z++;
                                      }
                                    } else {
                                      if (tes[0] == 'q') {
                                        clear(w);
                                        break;
                                      } else {
                                        if (tes[0] == 'x') {
                                          for (int i = z; i != entrySize; i++) {
                                            buffer[i] = buffer[i + 1];
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                    if (tes[0] == 'q') {
                      x = 0;
                      break;
                    }
                  }
                } else {
                  i = 0;
                }
              }
            }
          }
        }
      } else {
        if (tes[0] == 'q') {
          exit(1);
        }
      }
    }
  }
}
