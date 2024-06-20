#ifndef AUTHORITY_HPP
#define AUTHORITY_HPP

#include "person.hpp"

class Authority : public Person
{
    string uname;

public:
    Authority();
    string getName();
    void num_sick_diet(int);
    bool login(string, string);
    bool logout();
    bool authenticate();
    void searchRoomNum(string, int);
    void check_diet_rate();
    void check_extra_diet_rate();
    void set_extra_diet_rate();
    void set_diet_rate();

    void set_notification();
    void show_record();
    void found_lost_sec();
};

#endif