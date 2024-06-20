#include "person.hpp"
#include "student.hpp"
#include "authority.hpp"
#include "global.hpp"
#include "colors.hpp"
#define Num 8
Student *authenticate(string id, string password, string filename)
{
    ifstream fin;
    fin.open(filename, ios::in);
    if (fin.is_open())
    {
        int i = 0;
        while (i < Num)
        {
            Student *s = new Student;
            fin >> s; 
            if (s->login(id, password))
            {
                return s;
            }
            else
                delete s;

            i++;
        }
        return NULL;
        fin.close();
    }
    cout << "\nerror opening" << endl;
}

void student_login()
{
    bool found = false;
    string id;
    string password;
    std::cout << "\nEnter roll number : ";
    cin >> id;
    cout << "\nEnter password : ";
    password = takePasswdFromUser();
    Student *s = authenticate(id, password, "student_record.csv");
    bool flag = s->hasSeen();
    if (s->got_notification() && !flag)
    {

        cout << "\nYOU HAVE SOME NOTIFICATIONS.\n";
        cout << "1.READ\n";
        cout << "2.SKIP\n";
        cout << "\nCHOICE: ";
        int n;
        cin >> n;
        if (n == 1)
        {
            s->show_notification();
        }
    }

    if (s != NULL)
    {
    strt:
        int choice;
        cout << "\nShowing various options\n";
        cout << "\n1.mess off ";
        cout << "\n2.mess on ";
        cout << "\n3.request for sick diet ";
        cout << "\n4.check billl ";
        cout << "\n5.check balance amount ";
        cout << "\n6.show extra diet ";
        cout << "\n7.Check notifications";
        cout << "\n8.Exit";
        cout << "\nenter here: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            s->setOff();
            s->update("student_record.csv", Num);
            break;
        case 2:
            s->setOn();
            s->update("student_record.csv", Num);
            break;
        case 3:
            s->req_sick_diet();
            s->update("student_record.csv", Num);
            break;
        case 4:
            cout << "\nTOTAL BILL: " << s->check_bill(Num, 4) << endl;
            break;
        case 5:
            s->check_balance();
            break;
        case 6:
            s->show_extra_diet();
            break;
        case 7:
            s->show_notification();
            break;
        case 8:
            goto last;
        default:
            cout << "\nplease enter a valid input\n";
        }
        goto strt;
    }
    else
    {
        cout << "\nNO RECORD FOUND";
    }
last:
    if (s != NULL)
        delete s; 
    return;
}

void authority_login()
{
    string id;
    string password;
    bool login = false;
    cout << "\nEnter id : ";
    cin >> id;
    cout << "\nEnter password : ";
    password = takePasswdFromUser();
    Authority obj;
    if (obj.login(id, password))
    {
        cout << "\nlogged in successfully!\n";
        login = true;
    }
    login = true;
    if (login == true)
    {

    auth_options:
        cout << "your profile says: \n";
        cout << "\nuser-name: " << obj.getName();
        int choice;
        cout << "\nShowing various options...........\n";
        cout << "\n1.Search Room Number ";
        cout << "\n2.Check Requests for Sick Diet ";
        cout << "\n3.Set Diet Rate ";
        cout << "\n4.Check Extra diet Rate ";
        cout << "\n5.Set Extra diet Rate ";
        cout << "\n6.Set notification";
        cout << "\n7.Show Record";
        cout << "\n8.Go Back";

        cout << "\nEnter here: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            obj.searchRoomNum("student_record.csv", Num);
            break;
        case 2:
            obj.num_sick_diet(Num);
            break;
        case 3:
            obj.set_diet_rate();
            break;
        case 4:
            obj.check_extra_diet_rate();
            break;
        case 5:
            obj.set_extra_diet_rate();
            break;
        case 6:
            obj.set_notification();
            break;
        case 7:
            obj.show_record();
        case 8:
            login = false;
            return;
        default:
            cout << "\nplease enter a valid input\n";
        }
        goto auth_options;
    }
    else
    {
        cout << "\nNO RECORD FOUND";
    }
    login = false;
    return;
}

void welcome()
{
    cout << COLOR_RED << "\n\n\t\t #####################################################\n\
                 ######### WELCOME TO MESS MANAGEMENT SYSTEM #########\n\
                 #####################################################\n\n\n"
         << COLOR_RESET;
}
int menu1()
{
    int choice;
    cout << COLOR_GREEN << "\n1. authority login " << COLOR_RESET;
    cout << "\n2.student login ";
    cout << "\n3.Exit ";

    cout << "\nEnter your choice here : ";
    cin >> choice;
    cin.ignore();
    return choice;
}
void thanku()
{
    cout << "\n\n\t\t\tTHANK YOU\n\n\n";
    usleep(150000);
    system("cls");
}
int main()
{
start:
    welcome();
    switch (menu1())
    {
    case 1:
        authority_login();
        break;
    case 2:
        student_login();
        break;
    case 3:
        thanku();
        return 0;
    }
    goto start;
    thanku();
}