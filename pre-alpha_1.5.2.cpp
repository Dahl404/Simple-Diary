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
//*********DO NOT CHANGE- THIS IS AN EXPIREMENTAL FEATURE AND IS NOT IMPLIMENTED FULLY YET*********
#define entrySize 1000
//-----
class entry
{
	public:
		int year;
	int month;
	int day;
	char data[entrySize];
};

class bufferToggle
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
	}
};

void clear()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cout << string(w.ws_row, '\n');
}

void getdata()
{
	bufferToggle bt;
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
	bt.on();
	getline(cin, dBuffer);
	strcpy(obj.data, dBuffer.c_str());;
	dataO.write((char*) &obj, sizeof(obj));
	dataO.close();
	bt.off();
}

int main()
{
	//-----dep assets for testing purposes
	//-----
	int c;
	char tes[1];

	//-----turns off input buffer
	bufferToggle bt;
	bt.off();

	//---used to get specs about the terminal
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	//---Main Loop
	while (true)
	{
		clear();
		cout << "(l)oad\n(s)ave\n(q)uit\n";
		c = getchar();
		tes[0] = c;
		if (tes[0] == 's')
		{
			getdata();
		}
		else
		{
			if (tes[0] == 'l')
			{
			 	//-----get file size
				ifstream sizeS("store.dat", ios:: in);
				const auto begin = sizeS.tellg();
				sizeS.seekg(0, ios::end);
				const auto end = sizeS.tellg();
				const auto fsize = (end - begin);
				sizeS.close();
				//-----
				ifstream fout("store.dat", ios:: in);
				// need to make this work with entry size but for now (if you dont change entry size) it works
				entry obj[(fsize / 1024) + 1];
				// Reading from file into object "obj"
				fout.read((char*) &obj[0], sizeof(obj[0]));
				int objNum = 0;
				for (int i = 1; !fout.eof(); i++)
				{
					objNum++;
					fout.read((char*) &obj[i], sizeof(obj[i]));
				}
				fout.close();
				clear();
				int i = 0;
				while (true)
				{
					clear();
					int x = 0;	// will say it yet again this needs to be made variable so it can work with any entry size but for now its ok
					for (; i != (sizeof(obj) / 1012) &x <= (w.ws_row - 8); i++)
					{
						cout << "(" << i << ")----" << obj[i].year << "/" << obj[i].month << "/" << obj[i].day << "\n";
						x++;
					}
					cout << "(n)ext page\n(p)revious page\n(q)uit\n";
					c = getchar();
					tes[0] = c;
					//*****debating having the brackets seeing as they arnt needed but it does help readability
					if (tes[0] == 'n')
					{
						x = 0;
					}
					else
					{
						if (tes[0] == 'q')
						{
							break;
						}
						else
						{
							if (tes[0] == 'p')
							{
								i = i - w.ws_row + 2;
							}
							else
							{
								if (isdigit(tes[0]))
								{
								 	//***should replace buff int with 'tes[0] - '0'' or something similiar later
									int buff = tes[0] - '0';
									while (true)
									{
										clear();
										cout << obj[buff].year << "/" << obj[buff].month << "/" << obj[buff].day << "\n\n" << obj[buff].data << "\n\n(q)uit\n(e)dit\n";
										i = 0;
										c = getchar();
										tes[0] = c;
										if (tes[0] == 'e')
										{
											char buffer[entrySize];
											char buffer2[entrySize];
											char bufferDep[entrySize];
											for (int i = 0; i != sizeof(obj[buff].data); i++)
											{
												buffer[i] = obj[buff].data[i];
												buffer2[i] = buffer[i];
												bufferDep[i] = buffer[i];
											}
											int z = 0;
											while (true)
											{
												clear();
												buffer[z] = '#';
												cout << buffer << "\n\n(s)ave\n(q)uit";
												c = getchar();
												tes[0] = c;
												buffer[z] = buffer2[z];
												if (tes[0] == 'j' &z < entrySize - w.ws_col)
												{
													z += w.ws_col;
												}
												else
												{
													if (tes[0] == 'k' &z > 0 + w.ws_col)
													{
														z -= w.ws_col;
													}
													else
													{
														if (tes[0] == 'l' &z < entrySize)
														{
															z++;
														}
														else
														{
															if (tes[0] == 'h' &z > 0)
															{
																z--;
															}
															else
															{
																if (tes[0] == 's')
																{
																	for (int i = 0; i != sizeof(obj[buff].data); i++)
																	{
																		obj[buff].data[i] = buffer2[i];
																	}
																	ofstream file("store.dat");
																	for (int i = 0; i != objNum; i++)
																	{
																		file.write((char*) &obj[i], sizeof(obj[i]));
																	}
																	file.close();
																	break;
																}
																else
																{
																	if (tes[0] == 'r')
																	{
																		c = getchar();
																		buffer2[z] = c;
																	}
																	else
																	{
																		if (tes[0] == 'q')
																		{
																			clear();
																			break;
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
										if (tes[0] == 'q')
										{
											break;
										}
									}
								}
								else
								{
									i = 0;
								}
							}
						}
					}
				}
			}
			else
			{
				if (tes[0] == 'q')
				{
					exit(1);
				}
			}
		}
	}
}
