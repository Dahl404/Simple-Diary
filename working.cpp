#include <iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<cstring>
#include<filesystem>

using namespace std;

class entry{
  public:
    int year;
    int month;
    int day;
    char data[1000];
};

void getdata(){
  string dBuffer;
  entry obj;
  ofstream dataO("store.dat", ios::app);
  cout << "year:";cin >> obj.year;
  cout << "month:";cin >> obj.month;
  cout << "day:";cin >> obj.day;
  cout << "entry:";cin >> ws;getline(cin,dBuffer);
  strcpy(obj.data, dBuffer.c_str());;
  dataO.write((char*)&obj, sizeof(obj));
  dataO.close();
}

void load(){
    ifstream sizeS("store.dat", ios::in);
    const auto begin = sizeS.tellg();
    sizeS.seekg (0, ios::end);
    const auto end = sizeS.tellg();
    const auto fsize = (end-begin);
    sizeS.close();
    ifstream fout("store.dat", ios::in);
    entry obj[(fsize/1024)+1];
    // Reading from file into object "obj"
    fout.read((char*)&obj[0], sizeof(obj[0]));
    for (int i = 1; !fout.eof(); i++) {
      fout.read((char*)&obj[i], sizeof(obj[i]));
    }
    fout.close();
    // one entry is 1012
    for(int i = 0; i != (sizeof(obj)/1012); i++){
      cout << obj[i].year << "/" << obj[i].month << "/" << obj[i].day << "\n" << obj[i].data << "\n\n";
      }
}

int main() {
  int choice;
  while (1){
  cout << "load(1)\nsave(2)\nexit(3)\n>>>";cin >> choice;

  if (choice == 2){
    getdata();
  }else{
	  if (choice == 1){
		  load();
	  }else{
		  if (choice == 3){
			  exit(1);

		  }

	  }}}


}
