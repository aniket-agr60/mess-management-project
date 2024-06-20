#include "global.hpp"
#include "authority.hpp"
#include "student.hpp"
using namespace std;
enum IN
{
    IN_BACK = 8,
    IN_RET = 13
};
string takePasswdFromUser()
{
    char sp = '*';
    string passwd = "";
    char ch_ipt;
    while (true)
    {
        ch_ipt = getch();
        if (ch_ipt == IN::IN_RET)
        {
            cout << endl;
            return passwd;
        }
        else if (ch_ipt == IN::IN_BACK && passwd.length() != 0)
        {
            passwd.pop_back();
            cout << "\b \b";

            continue;
        }
        else if (ch_ipt == IN::IN_BACK && passwd.length() == 0)
        {
            continue;
        }

        passwd.push_back(ch_ipt);
        cout << BOLD_MODE << sp << COLOR_RESET;
    }
}

void transition(string chars)
{
    int n = chars.size();
    for (int i = 0; i < n; i++)
    {
        usleep(115000);
        cout << chars.at(i);
    }
    return;
}
// overloading << operator for writing student info in file(student_record.csv)
ofstream &operator<<(ofstream &fout, Student &s)
{
    fout << s.getRoomNum() << "," << s.getName() << "," << s.getRollNum() << "," << s.getHostelInfo() << "," << ((s.isOff() == true) ? "off" : "on") << "," << s.getContact() << endl;
    return fout;
}

ofstream &operator<<(ofstream &fout, const vector<string> &v)
{
    int n = v.size();
    for (int i = 0; i < n - 1; i++)
    {
        fout << v.at(i) << ",";
    }
    fout << v.at(n - 1) << '\n';
    return fout;
}

ifstream &operator>>(ifstream &fin, Student *s) 
{
    string line = "";
    getline(fin, line);
    stringstream ss(line);
    vector<string> cols;
    string str;
    while (getline(ss, str, ',')) 
    {
        cols.push_back(str);
        str = "";
    }
    s->setDetails(cols);
    return fin; // for cascading
}
ifstream &operator>>(ifstream &fin, vector<string> &row) 
{
    string line = "";
    getline(fin, line);
    stringstream ss(line);
    string str;
    while (getline(ss, str, ',')) 
    {

        row.push_back(str);
        str = "";
    }
    return fin; // for cascading
}

void check_list()
{
    system("cls");
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
    cout << "\nread successfuly\n";
    cout << "\npress any key to continue\n";
    getch();
    return;
}
void update_list()
{
ulist:
    system("cls");
    cout << "\n1. Add Item";
    cout << "\n2. Remove Item";
    cout << "\n3. Update RateList ";
    cout << "\n4.Exit";
    cout << "\nenter choice: ";
    int choice;
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1:
        add_item(); // global
        break;
    case 2:
        remove_item(); // global;
        break;
    case 3:
        update_ratelist(); // global;
        break;
    case 4:
        return;
    default:
        cout << "\ninvalid input\n";
    }
    goto ulist;
}

void add_item()
{
    // open file in append mode
    ofstream fout;
    fout.open("extra_diet_record.csv", ios::app);
    if (fout.is_open())
    {
        int n;
        cout << "\nHow many items you want to add: ";
        cin >> n;
        cin.ignore();
        string name;
        string price;
        for (int i = 0; i < n; i++)
        {
            cout << "\nname of item: ";
            cin >> name;
            cout << "\nPrice of item: ";
            cin >> price;
            fout << name << "," << price << endl;
        }
        // fout<< endl;
        fout.close();
    }
    else
    {
        cout << "\nerror opening\n";
    }
    cout << "\npress any key to continue";
    getch();
}

void remove_item()
{
    // open file in append mode
    ofstream fout;
    ifstream fin;
    fin.open("extra_diet_record.csv", ios::in);
    fout.open("extra_diet_recordnew.csv", ios::out);
    if (fout.is_open() && fin.is_open())
    {
        int n;
        cout << "\nHow many items you want to remove: ";
        cin >> n;
        cin.ignore();
        vector<string> names;
        cout << "\nEnter all the names : ";
        for (int i = 0; i < n; i++)
        {

            string name;
            cin >> name;
            cout << name << " ";
            cin.ignore();
            // cin.clear();
            names.push_back(name);
        }
        while (!fin.eof())
        {
            string line;
            getline(fin, line);
            vector<string> vect;
            stringstream ss(line);
            string str;

            while (getline(ss, str, ','))
            {
                vect.push_back(str);

                str = "";
            }
            bool matched = false;
            for (int i = 0; i < n; i++)
            {
                if (vect.size() != 0 && (vect.at(0) == names.at(i)))
                {
                    matched = true;
                    break;
                }
            }
            if (!matched && vect.size() != 0)
            {
                // fout << line << endl;
                fout << vect.at(0) << "," << vect.at(1) << endl;
            }
            line = "";
        }
        fin.close();
        fout.close();
        remove("extra_diet_record.csv");
        rename("extra_diet_recordnew.csv", "extra_diet_record.csv");
        // cout << "\nList updated successfully\n";
        // check_list();
    }
    else
    {
        cout << "\nerror opening\n";
    }
    cout << "\npress any key to continue";
    getch();
}

void update_ratelist()
{
    // open file in append mode
    ofstream fout;
    ifstream fin;
    fin.open("extra_diet_record.csv", ios::in);      // reading
    fout.open("extra_diet_recordnew.csv", ios::out); // writing
    if (fout.is_open() && fin.is_open())
    {
        int n;
        cout << "\nHow many items you want to update: ";
        cin >> n;
        cin.ignore();
        vector<pair<string, string>> names;
        cout << "\nEnter all the items and their prices: ";
        for (int i = 0; i < n; i++)
        {
            string name, price;
            cout << "\nEnter name for item_" << i + 1 << ": ";
            cin >> name;
            cout << "\nEnter price for item_" << i + 1 << ": ";
            cin >> price;
            cin.ignore();
            names.push_back(make_pair(name, price));
        }
        while (!fin.eof())
        {
            string line;
            getline(fin, line);
            vector<string> vect;
            stringstream ss(line);
            string str;

            while (getline(ss, str, ','))
            {
                vect.push_back(str);

                str = "";
            }
            bool matched = false;
            for (int i = 0; i < n; i++)
            {
                if (vect.size() != 0 && (vect.at(0) == names.at(i).first))
                {
                    fout << names.at(i).first << "," << names.at(i).second << endl;
                    matched = true;
                    break;
                }
            }
            if (!matched && vect.size() != 0)
            {
                fout << line << endl;
            }
            line = "";
        }
        fin.close();
        fout.close();
        remove("extra_diet_record.csv");
        rename("extra_diet_recordnew.csv", "extra_diet_record.csv");
    }
    else
    {
        cout << "\nerror opening\n";
    }
    cout << "\npress any key to continue";
    getch();
}

void readfile_record(string filename)
{
    ifstream fin;
    fin.open(filename, ios::in); // read file
    if (fin.is_open())
    {
        string line;
        vector<string> vect;
        getStrings(fin, vect);
        cout << "\n\t"
             << vect.at(0) << "\t\t\t\t\t\t\t\t\t\t\t" << vect.at(1) << endl
             << endl;
        vect.clear();
        getStrings(fin, vect);
        cout << "\t" << vect.at(0) << "   " << vect.at(1) << "   " << vect.at(2) << "   " << vect.at(3) << "   " << vect.at(4) << "   " << vect.at(5) << "   " << vect.at(6) << "   " << vect.at(7) << "   " << vect.at(8) << "   " << vect.at(9) << "   " << vect.at(10) << "   " << vect.at(11) << endl;
        while (!fin.eof())
        {
            vect.clear();
            getStrings(fin, vect);
            cout << "\t" << left << setw(8) << vect.at(0) << "   " << setw(19) << vect.at(1) << "   " << vect.at(2) << "   " << vect.at(3) << "   " << right << setw(7) << vect.at(4) << "   " << setw(8) << vect.at(5) << "   " <<setw(10)<< vect.at(6) << "   " << vect.at(7) << "   " <<setw(3)<< vect.at(8) << "   " << vect.at(9) << "   " << vect.at(10) << "   " << vect.at(11) << endl;
        }

        fin.close();
    }
    else
    {
        cout << "\nERROR";
    }
}

void getStrings(ifstream &fin, vector<string> &vect)
{
    string line, str;
    getline(fin, line);
    stringstream ss(line);
    while (getline(ss, str, ','))
    {
        vect.push_back(str);
        str = "";
    }
    return;
}