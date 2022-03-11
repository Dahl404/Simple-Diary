#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstring>
#include <filesystem>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

using namespace std;

#define entrySize 1000

class entry {
        public:
		int year;
		int month;
		int day;
		char data[entrySize];
};

class bufferToggle {
        private:
                struct termios t;
        public:
                void off(void) {
                        tcgetattr(STDIN_FILENO, & t);
                        t.c_lflag &= ~ICANON;
                        tcsetattr(STDIN_FILENO, TCSANOW, & t);
                }

		void on(void) {
                	tcgetattr(STDIN_FILENO, & t);
                	t.c_lflag |= ICANON;
                	tcsetattr(STDIN_FILENO, TCSANOW, & t);
		}
};

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
	cout << "year:"; 	cin >> obj.year;
	cout << "month:"; 	cin >> obj.month;
	cout << "day:";		cin >> obj.day;
	cout << "entry:"; 	cin >> ws;
	getline(cin, dBuffer);	strcpy(obj.data, dBuffer.c_str());;
	dataO.write((char * ) & obj, sizeof(obj));
	dataO.close();
}

int main() {
	ifstream fileI("store.dat", ios::in );
	ofstream fileO("store.dat", ios::out);
	int c;
	char tes[1];

	//-----turns of input buffer
	bufferToggle bt;
	bt.off();

	//---used to get specs about the terminal
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, & w);

	//---Main Loop
	while (true) {
		clear();
		cout << "(l)oad\n(s)ave\n(e)xit\n";
		c = getchar(); tes[0] = c;
		if (tes[0] == 's') {
			getdata();
		} else {
			if (tes[0] == 'l') {
				//-----gets file size
				const auto begin = fileI.tellg();
				fileI.seekg(0, ios::end);
				const auto end = fileI.tellg();
				const auto fsize = (end - begin);
				//*****need to make this work with entrySize but for now (if you dont alter the entry size) it should work
				entry obj[(fsize / 1024) + 1];
				//-----Reading from file into object "obj"
				fileI.read((char * ) & obj[0], sizeof(obj[0]));
				int objNum = 0;
				for (int i = 1; !fileI.eof(); i++) {
					objNum++;
					fileI.read((char * ) & obj[i], sizeof(obj[i]));
				}
				clear();
				int i = 0;
				while (true) {
					int x = 0; // will say it yet again this needs to be made variable so it can work with any entry size but for now its ok
					for (; i != (sizeof(obj) / 1012) & x <= (w.ws_row - 8); i++) {
						cout << "(" << i << ")----" << obj[i].year << "/" << obj[i].month << "/" << obj[i].day << "\n";
						x++;
					}
					cout << "(n)ext page\n(p)revious page\n(e)xit\n" << objNum << "\n";
					c = getchar(); tes[0] = c;
					if (isdigit(tes[0])) {
						int buff = tes[0] - '0';
						while (1) {
							clear();
							cout << obj[buff].year << "/" << obj[buff].month << "/" << obj[buff].day << "\n\n" << obj[buff].data << "\n\n(x)it\n(e)dit\n>>>";
							i = 0;
							c = getchar(); tes[0] = c;
							if (tes[0] == 'e') {
								char buffer[entrySize];
								char buffer2[entrySize];
								for (int i = 0; i != sizeof(obj[buff].data); i++) {
									buffer[i] = obj[buff].data[i];
									buffer2[i] = buffer[i];
								}
								running = true;
								int z = 0;
								while (running) {
									clear();
									buffer[z] = '#';
									cout << buffer << "\n\n(s)ave";
									c = getchar();
									tes[0] = c;
									buffer[z] = buffer2[z];
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
													if (tes[0] == 'r') {
														c = getchar();
														buffer2[z] = c;
													}
												}
											}
										}
									}
									if (tes[0] == 's') {
										for (int i = 0; i != sizeof(obj[buff].data); i++) {
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
							if (tes[0] == 'e') {
								clear();
								break;
							}
						}

					} else {
						if (tes[0] == 'n') {
							x = 0;
						} else {
							if (tes[0] == 'x') {
								break;
							} else {
								if (tes[0] == 'p') {
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
				if (tes[0] == 'e') {
					exit(1);
				}
			}

		}
	}
}
