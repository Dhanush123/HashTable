// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

#include <cstring> // for strtok and strcpy

int hashCode(const string& key)
{
  int result = 0;
  for (int i = 0; i < key.length(); i++)
    result += key.at(i);
  return result;
}

#include "HashTable.h"

int main(){
  cout << "Programmer: Dhanush Patel\n";
  cout << "Programmer's ID: 1553428\n";
  cout << "File: " << __FILE__ << endl;

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

//  DynamicArray<string> alreadySeen;
//  DynamicArray<CInfo> recordKeep;
  HashTable<string, bool, 74411> seen(hashCode);
  HashTable<string, int, 188> count(hashCode);
  int duplicates = 0;
  int county = 0;
  // read the input file
  while (fin.good()){
    county++;
    cout << (county/74411) * 100 << "% \r";
    cout.flush();
    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue; // skip blank lines

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectCode(course.begin(), course.begin() + course.find('-'));

    string key = term + "," +section;
    bool found = false;
    for (int i = 0; i < seen.size(); i++){
    	if (seen.containsKey(key)){
    		found = true;
        duplicates++;
        break;
    	}
    }

    if(!found){
      seen[key] = true;
      count[subjectCode]++;
    }
  }
  fin.close();
  cout << "number of duplicates: " << duplicates << endl;

  queue<string> q = count.keys();
  set<string> s;

  while(!q.empty()){
    s.insert(q.front());
    q.pop();
  }

  for(auto& i : s) {
    cout << i << ": " << seen[i] << endl;
  }
}
