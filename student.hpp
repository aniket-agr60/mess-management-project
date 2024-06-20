#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "person.hpp"

class Student : public Person
{
    int roomNum; // take input
    string uname;
    string rollNum;
    string contact;
    string hostelInfo;
    string password;
    bool off;          // for checking mess off or not
    bool sickDietReqd; // for sick diet
    bool seen;         // for notification

public:
    Student();
    int getRoomNum();
    string getName();
    string getRollNum();
    string getContact();
    string getHostelInfo();
    void setDetails();
    void setDetails(vector<string> &); // overloaded function
    void getDetails();

    bool isOff();
    void setOff();
    void setOn();
    bool isSick();
    bool hasSeen();

    void markMeal(int);
    bool login(string, string);
    bool logout();
    void update(string, int); // may take filename
    bool authenticate();
    void req_sick_diet();
    float check_bill(int, int);
    void check_balance();
    void show_extra_diet();
    void launch_complaint();
    void check_diet_rate();
    void show_notification();
    bool got_notification();
    void found_lost_sec();
};

#endif