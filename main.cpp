//Runtime: 0.0002157 seconds
//Runtime: 0.0002699 seconds
//Runtime: 0.0003526 seconds


#include <iostream>
#include "Stack.h"
#include <string>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

enum Error {OUT_OF_BOUND};


string Input(string title);
void KnightTour(Stack<string> &Tour, string begin);
vector<string> availablePos(const Stack<string> &Tour, const string &square, const string &checked);
vector<int> degree (const Stack<string> &Tour, vector<string> pos) ;
string Choose (const vector<string> &pos, const vector<int> &deg);
bool degZero(const vector<int> &deg);
void closed(const string &begin, const string &end);
void Show (const Stack<string> &Tour);
void PrintTour(ofstream &out, const Stack<string> &Tour);
void Checkfile(string &filename);
bool repeat();

int main()
{
    do
    {
        ofstream out;

        clock_t start = clock();

        string begin;
        Stack<string> Tour(64);

        begin = Input ("\n\n Please input beginning position: ");
        Tour.push(begin);
        KnightTour(Tour, begin);
        cout << "Tour: " << endl << Tour << endl;
        closed(begin, Tour.top());
        Show (Tour);

        clock_t finish = clock();
        cout << "Runtime: " << (finish-start)*0.1/CLOCKS_PER_SEC << " seconds "<<endl<<endl;

        PrintTour(out, Tour);

    } while (repeat());

    return 0;
}


string Input(string title)
{
    string temp, value;
    cout << title;
    cin >> temp;

    value = tolower(temp[0]);
    value += temp[1];

    while ((value[0]< 'a' || value[0] > 'h') ||
        (value[1] < '1' || value[1] > '8'))
    {
        cout << "Invalid input, please try again: ";
        cin >> temp;

        value = tolower(temp[0]);
        value += temp[1];
    }

    return value;
}

void KnightTour(Stack<string> &Tour, string begin)
{
    vector<string> pos;
    vector<int> deg;
    string checked = "", square = begin;

    while (Tour.size() < 64)
    {
        pos = availablePos(Tour, square, checked); //possible next squares
            //for (int i=0; i<pos.size(); ++i) cout << pos[i] << " " ; cout << endl;
        deg = degree(Tour, pos);
            //for (int i=0; i<deg.size(); ++i) cout << deg[i] << "  " ; cout << endl;
        if (degZero(deg) && Tour.size() < 63)
        {
            //cout << endl << "BACKTRACKING" << endl;
            checked = Tour.top();
            Tour.pop();
        }
        else
        {
            checked = "";
            Tour.push(square = Choose (pos,deg));
        }
    }
}


vector<string> availablePos(const Stack<string> &Tour, const string &square, const string &checked) // gives avialble position for given square
{
    vector<string> pos;
    string s_L2, s_L1, s_R2, s_R1, s_U1, s_U2, s_D1, s_D2;
    s_L2 = square[0]-2;
    s_L1 = square[0]-1;
    s_R2 = square[0]+2;
    s_R1 = square[0]+1;
    s_U1 = square[1]+1;
    s_U2 = square[1]+2;
    s_D1 = square[1]-1;
    s_D2 = square[1]-2;
    if (s_L2 >= "a" && s_U1 <= "8")
        pos.push_back(s_L2+s_U1);
    if (s_L2 >= "a" && s_D1 >="1")
        pos.push_back(s_L2+s_D1);
    if (s_L1 >= "a" && s_U2 <= "8")
        pos.push_back(s_L1+s_U2);
    if (s_L1 >= "a" && s_D2 >="1")
        pos.push_back(s_L1+s_D2);
    if (s_R2 <= "h" && s_U1 <= "8")
        pos.push_back(s_R2+s_U1);
    if (s_R2 <= "h" && s_D1 >="1")
        pos.push_back(s_R2+s_D1);
    if (s_R1 <= "h" && s_U2 <= "8")
        pos.push_back(s_R1+s_U2);
    if (s_R1 <= "h" && s_D2 >="1")
        pos.push_back(s_R1+s_D2);

    for (unsigned int i=0; i<pos.size(); ++i) //erase what's already in the stack
        if(Tour.find(pos[i]) || pos[i] == checked)
        {
            pos.erase(pos.begin()+i);
            --i;
        }

    return pos;
}


vector<int> degree (const Stack<string> &Tour, vector<string> pos) //gives degree for given square
{
    vector<int> deg;
    string checked = "";

    for (unsigned int i=0; i<pos.size(); ++i)
        deg.push_back(availablePos(Tour, pos[i], checked).size());
    return deg;
}


string Choose (const vector<string> &pos, const vector<int> &deg)
{
    srand(time(0));

    vector <int> which;

    int min = 8;

    for (unsigned int i=0; i< deg.size() ; ++i)
        if(deg[i] < min)
            min = deg[i];
    //cout << endl <<"min: " << min << endl;
    for (unsigned int i= 0; i < deg.size(); ++i)
        if(deg[i] == min)
            which.push_back(i);

    //for (int i=0; i<which.size(); ++i) cout << which[i] << "  " ; cout << endl;

    int minRand = (rand() % which.size());
    //cout << endl << "minRand is: " << minRand << endl << "pos[which[minRand]]: " << pos[which[minRand]]<< endl;

    return pos[which[minRand]];
}


bool degZero(const vector<int> &deg)
{
    for (unsigned int i = 0; i<deg.size(); ++i)
        if (deg[i] == 0)
            return true;
    return false;
}


void closed(const string &begin, const string &end)
{
    if ((abs(begin[0]-end[0]) == 2 && abs(begin[1]-end[1]) == 1)
            || (abs(begin[0]-end[0]) == 1 && abs(begin[1]-end[1]) == 2))
        cout << "The Knight Tour started from " << begin << " and ended in " << end << endl
             << "The tour is closed" << endl;
    else
        cout << "The Knight Tour started from " << begin << " and ended in " << end << endl
             << "The tour is open" << endl;
}


void Show (const Stack<string> &Tour)
{
    int w = 3;
    cout << "  =================================" << endl
         <<"8 ||"<<setw(w)<<Tour.index("a8")<<"|"<<setw(w)<<Tour.index("b8")<<"|"<<setw(w)<<Tour.index("c8")<<"|"<<setw(w)<<Tour.index("d8")
         <<"|"<<setw(w)<<Tour.index("e8")<<"|"<<setw(w)<<Tour.index("f8")<<"|"<<setw(w)<<Tour.index("g8")<<"|"<<setw(w)<<Tour.index("h8")<<"||"<<endl;
    cout << "  ---------------------------------" << endl
         <<"7 ||"<<setw(w)<<Tour.index("a7")<<"|"<<setw(w)<<Tour.index("b7")<<"|"<<setw(w)<<Tour.index("c7")<<"|"<<setw(w)<<Tour.index("d7")
         <<"|"<<setw(w)<<Tour.index("e7")<<"|"<<setw(w)<<Tour.index("f7")<<"|"<<setw(w)<<Tour.index("g7")<<"|"<<setw(w)<<Tour.index("h7")<<"||"<<endl;
    cout << "  ---------------------------------" << endl
         <<"6 ||"<<setw(w)<<Tour.index("a6")<<"|"<<setw(w)<<Tour.index("b6")<<"|"<<setw(w)<<Tour.index("c6")<<"|"<<setw(w)<<Tour.index("d6")
         <<"|"<<setw(w)<<Tour.index("e6")<<"|"<<setw(w)<<Tour.index("f6")<<"|"<<setw(w)<<Tour.index("g6")<<"|"<<setw(w)<<Tour.index("h6")<<"||"<<endl;
    cout << "  ---------------------------------" << endl
         <<"5 ||"<<setw(w)<<Tour.index("a5")<<"|"<<setw(w)<<Tour.index("b5")<<"|"<<setw(w)<<Tour.index("c5")<<"|"<<setw(w)<<Tour.index("d5")
         <<"|"<<setw(w)<<Tour.index("e5")<<"|"<<setw(w)<<Tour.index("f5")<<"|"<<setw(w)<<Tour.index("g5")<<"|"<<setw(w)<<Tour.index("h5")<<"||"<<endl;
    cout << "  ---------------------------------" << endl
         <<"4 ||"<<setw(w)<<Tour.index("a4")<<"|"<<setw(w)<<Tour.index("b4")<<"|"<<setw(w)<<Tour.index("c4")<<"|"<<setw(w)<<Tour.index("d4")
         <<"|"<<setw(w)<<Tour.index("e4")<<"|"<<setw(w)<<Tour.index("f4")<<"|"<<setw(w)<<Tour.index("g4")<<"|"<<setw(w)<<Tour.index("h4")<<"||"<<endl;
    cout << "  ---------------------------------" << endl
         <<"3 ||"<<setw(w)<<Tour.index("a3")<<"|"<<setw(w)<<Tour.index("b3")<<"|"<<setw(w)<<Tour.index("c3")<<"|"<<setw(w)<<Tour.index("d3")
         <<"|"<<setw(w)<<Tour.index("e3")<<"|"<<setw(w)<<Tour.index("f3")<<"|"<<setw(w)<<Tour.index("g3")<<"|"<<setw(w)<<Tour.index("h3")<<"||"<<endl;
    cout << "  ---------------------------------" << endl
         <<"2 ||"<<setw(w)<<Tour.index("a2")<<"|"<<setw(w)<<Tour.index("b2")<<"|"<<setw(w)<<Tour.index("c2")<<"|"<<setw(w)<<Tour.index("d2")
         <<"|"<<setw(w)<<Tour.index("e2")<<"|"<<setw(w)<<Tour.index("f2")<<"|"<<setw(w)<<Tour.index("g2")<<"|"<<setw(w)<<Tour.index("h2")<<"||"<<endl;
    cout << "  ---------------------------------" << endl
         <<"1 ||"<<setw(w)<<Tour.index("a1")<<"|"<<setw(w)<<Tour.index("b1")<<"|"<<setw(w)<<Tour.index("c1")<<"|"<<setw(w)<<Tour.index("d1")
         <<"|"<<setw(w)<<Tour.index("e1")<<"|"<<setw(w)<<Tour.index("f1")<<"|"<<setw(w)<<Tour.index("g1")<<"|"<<setw(w)<<Tour.index("h1")<<"||"<<endl;
    cout << "  =================================" << endl
         <<"     a   b   c   d   e   f   g   h " <<endl<<endl;
}


void PrintTour(ofstream &out, const Stack<string> &Tour)
{
    char ans;
    string filename;

    cout << "Do you wish to save the Knight Tour? " << endl
         << "Y for yes, N for no: ";
    cin >> ans;
    if (toupper(ans) == 'Y')
    {
        Checkfile(filename);
        out.open(filename.c_str());
        if(out.fail())
            cout << "File could not be created." << endl;
        else
        {
            cout <<"File " << filename << " created";
            out << Tour;
            out.clear();
            out.close();
            cout << " and Knight Tour successfully saved." << endl<<endl;
        }
     }
    else
        cout << endl;
}


void Checkfile(string &filename)
{
    ifstream test;

    cout << endl<< "Please input desired file name (.txt): ";
    cin >> filename;
    if(filename.find(".txt") == string::npos)
    {
        string txt = ".txt";
        filename+=txt;
    }
    test.open(filename.c_str());
    if (test.fail())
    {
        return;
    }
    else
    {
        cout << filename <<" already exists. Please try another file name." << endl;
        Checkfile(filename);
    }
}


bool repeat()
{
    char ans;
    cout << "Do you wish to input another starting point? " <<endl
         << "Y for yes, N for no: ";
    cin >> ans;
    if (toupper(ans) == 'Y')
        return true;
    else
        return false;
}

