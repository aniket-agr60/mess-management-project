#include "student.hpp"
#include "global.hpp"
// using namespace std;
// Student::Student(string id, string pw, string name = "Guest") : Person(id, pw, name)
// {
//     // cout << "std contructor\n";
// }
Student::Student::Student()
{
    // this->id = "";
    // this->password = "";
}

string Student::getName()
{
    return uname;
}

int Student::getRoomNum()
{
    return roomNum;
}

string Student::getRollNum()
{
    return rollNum;
}

string Student::getContact()
{
    return contact;
}
string Student::getHostelInfo()
{
    return hostelInfo;
}

void Student::getDetails()
{
    cout << "\nRoom Number        : " << this->roomNum;
    cout << "\nStudent Name       : " << this->uname;
    cout << "\nRoll Number        : " << this->rollNum;
    cout << "\nStudent contact    : " << this->contact;
    cout << "\nHostel Info        : " << this->hostelInfo;
    cout << "\nMess info          : " << (this->off == true ? "off " : "on ");
    cout << "\nRequested sick diet: " << (this->sickDietReqd == true ? "yes " : "no ") << endl;
}
void Student::setDetails()
{
    cout << "\nEnter Room Number: ";
    cin >> this->roomNum;
    cin.ignore();
    cout << "\nEnter Student Name: ";
    getline(cin >> ws, this->uname);
    cout << "\nEnter Roll Number: ";
    cin >> this->rollNum;

    cout << "\nEnter Password: ";
    this->password = takePasswdFromUser();

    cout << "\nEnter Student contact: ";
    cin >> this->contact;
    cout << "\nEnter Hostel Info(eg: MBH-B): ";
    cin >> this->hostelInfo;
    this->off = false;
    this->sickDietReqd = false;
    this->seen = false;
}
void Student::setDetails(vector<string> &vect)
{
    this->roomNum = stoi(vect[0]);
    this->uname = vect[1];
    this->rollNum = vect[2];
    this->hostelInfo = vect[3];
    this->off = (vect[4] == "off") ? true : false;
    this->contact = vect[5];
    this->password = vect[6];
    this->sickDietReqd = (vect[7] == "yes") ? true : false;
    this->seen = false;
}

bool Student::isOff()
{
    return off;
}

bool Student::login(string id, string pwd)
{
    if (this->rollNum == id && this->password == pwd)
    {
        return true;
    }
    return false;
}
bool Student::logout()
{
    // student logout
}

bool Student::authenticate()
{
}

void Student::markMeal(int Num)
{
    int day;
    int meal;
    cout << "Enter day \n";
    cin >> day;
    cin.ignore();
    cout << "\nChoose meal\n";
    cout << "\n1. Breakfast";
    cout << "\n2. Lunch";
    cout << "\n3. Dinner";
    cout << "\nEnter your input: ";
    cin >> meal;
    cin.ignore();
    ifstream fin;
    ofstream fout;
    fin.open("mess_record.csv", ios::in);
    fout.open("mess_recordnew.csv", ios::out);

    if (fin.is_open())
    {
        int i = 0;
        while (i < Num) // reading line by line;
        {
            vector<string> vect;
            fin >> vect; // read each line
            if (vect[0] == this->rollNum)
            {
                vect[day][meal] = '1';
            }
            int n = vect.size();
            for (int i = 0; i < n - 1; i++)
            {
                fout << vect.at(i) << ",";
            }
            fout << vect.at(n - 1) << '\n';
            vect.clear();
            i++;
        }
        fin.close();
        fout.close();
        remove("mess_record.csv");
        rename("mess_recordnew.csv", "mess_record.csv");
    }
    else
    {
        cout << "\nError in opening file\n";
    }
}

void Student::update(string filename, int Num)
{
    ifstream fin;
    ofstream fout;
    fout.open("student_recordnew.csv", ios::out);
    fin.open(filename, ios::in);
    if (fin.is_open() && fout.is_open())
    {
        int i = 0;
        while (i < Num) // reading line by line;
        {
            vector<string> vect;
            fin >> vect; // read each line one by one
            if (this->rollNum == vect[2])
            {
                fout << this->roomNum << "," << this->uname << "," << this->rollNum << "," << this->hostelInfo << "," << ((this->off == true) ? "off" : "on") << "," << this->contact << "," << this->password << "," << ((this->sickDietReqd == true) ? "yes" : "no") << endl;
            }
            else
            {
                int n = vect.size();
                for (int i = 0; i < n - 1; i++)
                {
                    fout << vect.at(i) << ",";
                }
                fout << vect.at(n - 1) << '\n';
            }
            i++;
        }
        fout.close();
        fin.close();
        remove(filename.c_str());
        rename("student_recordnew.csv", filename.c_str());
    }
}
bool Student::hasSeen()
{
    return seen;
}
bool Student::isSick()
{
    return sickDietReqd;
}
void Student::req_sick_diet()
{
    string choice;
    cout << "\nnoted request sick diet \n";
    cout << "\nDo you want sick diet? ";
    cout << "\nPress 'y' for yes or 'n' for no: ";
    cin >> choice;
    if (choice == "y" || choice == "Y")
    {
        this->sickDietReqd = true;
    }
    else
    {
        this->sickDietReqd = false;
    }
}
void Student::setOff()
{
    this->off = true;
    cout << this->uname << "\n:your mess has been off\n";
}
void Student::setOn()
{
    this->off = false;
    cout << this->uname << "\n:your mess has been on\n";
}

float Student::check_bill(int Num, int day = 4)
{
    ifstream fin; 
    fin.open("mess_record.csv", ios::in);
    if (fin.is_open())
    {
        int i = 0;
        int sum = 0;
        while (i < Num)
        {
            vector<string> vect;
            fin >> vect; 
            if (vect[0] == this->rollNum)
            {
                for (int j = 1; j < vect.size(); j++)
                {
                    for (int k = 1; k < vect[j].size(); k++)
                    {
                        int num = (vect.at(j).at(k) - '0'); // char  convert to number (make a function)
                        sum += num;
                    }
                }
                break;
            }
            vect.clear();
            i++;
        }
        float total = sum * 30.0;
        fin.close();
        return total;
    }
}

void Student::check_balance()
{
    int f = this->check_bill(8, 4);
    cout << "\n\tMess advance      :"
         << "rs." << 35000;
    cout << "\n\tTotal amount      :"
         << "rs." << f;
    cout << "\n\tAmount left:      :" << 35000 - f << endl;

}
void Student::show_extra_diet()
{
    cout << "\nreturning extra diet balances\n";
}
void Student::launch_complaint()
{

}
void Student::check_diet_rate()
{
    cout << "\nCURRENT DIET RATE IS rs.30 per meal\n";
}
void Student::show_notification()
{
    ifstream fin;
    fin.open("notifications_record.csv", ios::in);
    if (fin.is_open())
    {
        bool flag = true; // dont print newline
        this->seen = true;
        system("cls");
        cout << BG_GREEN << "\t\t\t\t\t\t\t  ************** NOTIFICATIONS ****************\n\n";

        while (!fin.eof())
        {
            string str;
            getline(fin, str);
            if (flag)
            {
                transition(str);
                cout << "  ";
                flag = false;
            }
            else
            {
                transition(str);
                cout << '\n';
                flag = true;
            }
        }
        cout << COLOR_RESET;
        fin.close();
    }
    else
        cout << "\nerror";
    cout << "\n\n\npress any key to continue.....\n";
    getch();
    system("cls");
}

bool Student::got_notification()
{
    ifstream fin;
    fin.open("notifications_record.csv", ios::in);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        if (str != "")
        {
            fin.close();
            return true;
        }
        fin.close();
        return false;
    }
    else
    {
        cout << "error opening\n";
    }
}

void Student::found_lost_sec()
{
}