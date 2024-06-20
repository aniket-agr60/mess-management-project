#include "person.hpp"
#include "authority.hpp"
#include "global.hpp"
Authority::Authority()
{
}
string Authority::getName()
{
    return uname;
}
void Authority::num_sick_diet(int Num)
{
    int count = 0;
    ifstream fin;
    fin.open("student_record.csv", ios::in);
    if (fin.is_open())
    {
        string line = "";
        int i = 0;
        while (i < Num) // reading line by line;
        {
            getline(fin, line);
            i++;
            vector<string> vect;
            vect.clear();
            string cols = "";
            stringstream ss(line);
            while (getline(ss, cols, ','))
            {
                vect.push_back(cols);
                cols = "";
            }
            line = "";
            if (vect[7] == "yes")
            {
                count++;
            }
        }
        cout << "\nNumber of students requestd for sick diet: " << count << endl;
    }
    else
        cout << "couldn't open";
}
bool Authority::login(string id, string pwd)
{
    return true;
}
bool Authority::logout()
{
}
bool Authority::authenticate()
{
    string id, password;
    bool found = true;
    if (!found)
    {
        cout << "\nNO RECORD FOUND FOR THIS USERNAME AND PASSWORD\n";
        return false;
    }
    else
    {
        return true;
    }
}
void Authority::searchRoomNum(string filename, int Num)
{
    int roomNum;
    transition("\nEnter room number that you want to search: ");
    cin >> roomNum;
    cin.ignore();
    ifstream fin;
    fin.open("student_record.csv", ios::in);
    if (fin.is_open())
    {
        int i = 0;
        vector<Student> students; // for storing two students of same room

        while (i < Num)
        {
            Student *s = new Student;
            fin >> s; // working************overloaded extraction
            if (roomNum == s->getRoomNum())
            {
                s->getDetails();
                students.push_back(*s);
            }
            delete s;
            i++;
        }
        if (!students.empty())
        {
            int choice;
            cout << "\nStudents are: " << endl;
            cout << "\n1.Roll Number: " << students[0].getRollNum();
            cout << "\n2.Roll Number: " << students[1].getRollNum();
            cout << "\nChoose students: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1)
            {
                if (students[0].isOff())
                {
                    cout << "\nmess is oFF!\n";
                }
                else
                {
                    students[0].markMeal(Num);
                }
            }
            else
            {
                if (students[1].isOff())
                {
                    cout << "\nmess is oFF!\n";
                }
                else
                {
                    students[1].markMeal(Num);
                }
            }
        }
        else
        {
            cout << "\nNO record\n";
        }
        fin.close();
    }
    else
        cout << "couldn't open";
}
void Authority::set_extra_diet_rate()
{
sedr:
    system("cls");
    cout << "\n1.Check List";
    cout << "\n2.Update List";
    cout << "\n3.exit";
    cout << "\nEnter here: ";
    int choice;
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1:
        check_list(); // global
        break;
    case 2:
        update_list(); // global;
        break;
    case 3:
        return;
    default:
        cout << "\ninvalid input\n";
    }
    goto sedr;
}

void Authority::check_diet_rate()
{
    cout << "\nchecking det rate";
}
void Authority::check_extra_diet_rate() 
{
    cout << "\n\n\t\tshowing extra diet rate list\n\n";
    ifstream fin;
    fin.open("extra_diet_record.csv", ios::in);
    string line;
    int i = 1;
    vector<string> colors = {BG_GREEN, BG_BLACK};
    string col = "\033[97;100m ";

    while (getline(fin, line, '\n') && (!fin.eof()))
    {
        vector<string> v;
        stringstream ss(line);
        string str;
        while (getline(ss, str, ','))
        {
            v.push_back(str);
        }
        cout << "\t\t\t\t" << colors[i % 2] << i << ". " << left << setw(20) << v[0] << setw(20) << v[1] << COLOR_RESET << endl;
        i++;
    }
    fin.close();
    cout << "\nread successfuly\n";
}
void Authority::set_diet_rate()
{
    ifstream fin;
    fin.open("misc.csv", ios::in);
    if (fin.is_open())
    {
        string rate;
        getline(fin, rate);
        cout << "\n\nCURRENT DIET RATE: Rs " << rate << " (per meal)" << endl;
        cout << "\nWant to reset diet rate?(y/n) :";
        string choice;
        cin >> choice;
        if (choice == "y" || choice == "Y")
        {
            ofstream fout;
            fout.open("miscnew.csv", ios::out);
            if (fout.is_open())
            {
                cout << "\nEnter New Rate: ";
                cin >> rate;
                fout << rate << endl;
            }

            fout.close();
            fin.close();
            remove("misc.csv");
            rename("miscnew.csv", "misc.csv");
        }
        else
        {
            fin.close();
        }
    }
    else
    {

        cout << "\nerror\n";
    }
}
void Authority::set_notification()
{
    time_t tt;

    ofstream fout;
    fout.open("notifications_record.csv", ios::app);
    if (fout.is_open())
    {
        cout << "\nType your message: \n";
        string msg;
        getline(cin >> ws, msg);

        time(&tt);
        struct tm tm = *(localtime(&tt));
        string str = asctime(&tm);
        fout << str << "MESSAGE: " << msg << endl;
        fout.close();
    }
    else
        cout << "\nerror\n";
}

void Authority::show_record()
{
showrecord:
    string filename;
    cout << "\nCheck record for: \n";
    cout << "\n1.MBH-A";
    cout << "\n2.MBH-B";
    cout << "\n3.MBH-F";
    cout << "\n4.Go back";
    int choice;
    cout << "\nEnter your choice:";
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1:
        filename = "record_mbha.csv";
        break;
    case 2:
        filename = "record_mbhb.csv";
        break;
    case 3:
        filename = "record_mbhf.csv";
        break;
    case 4:
        return;
    default:
        cout << "\nPlease enter  Valid choice\n";
    }
    readfile_record(filename);
    goto showrecord;
}
void Authority::found_lost_sec()
{
}