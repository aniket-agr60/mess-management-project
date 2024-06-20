#ifndef PERSON_HPP
#define PERSON_HPP
#include <bits/stdc++.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <ctime>
#include "colors.hpp"
using namespace std;
class Person
{
public:
    Person()
    {
    }
    virtual void found_lost_sec() = 0;
    virtual bool login(string, string) = 0;
    virtual bool authenticate() = 0;
};

#endif