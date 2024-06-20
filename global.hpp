#ifndef GLOBAL_HPP
#define GLOBAL_HPP
#include "student.hpp"
string takePasswdFromUser();
void transition(string chars);
ofstream &operator<<(ofstream &fout, Student &s);
ifstream &operator>>(ifstream &fin, Student *s);
ifstream &operator>>(ifstream &fin, vector<string> &row);
ofstream &operator<<(ofstream &fout, vector<string> &v);
void update_list();
void check_list();
void add_item();
void remove_item();
void update_ratelist();
void readfile_record(string filename);
void getStrings(ifstream &fin, vector<string> &vect);
#endif