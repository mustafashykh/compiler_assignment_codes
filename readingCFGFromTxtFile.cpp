#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Symbol
{
    char s;
    bool terminal;
};

//Grammer Rule
struct Rule
{
    Symbol rule[10];
    Rule * next;
    Rule * prev;
};

//Grammer Rule List
struct RList
{
    Symbol s;
    Rule * head;
    Rule * last;
    RList * next_rlist;
    RList * prev_rlist;
};

RList * first_rlist=nullptr,* last_rlist=nullptr;

void loadCFGFromFile(string);
void buildRuleList(string s);
RList * addRuleList(string s);
void addRule(RList * node, string rule);
void deleteRuleList(RList * node);
void deleteRule(RList * pnode,Rule * node);
bool isTerminal(char ch);
void printCFG();

int main()
{
    loadCFGFromFile("C:\\Users\\musta\\CLionProjects\\untitled\\cfg.txt");

    printCFG();

    //Delete rule(f) from (A)
    deleteRule(first_rlist->next_rlist, first_rlist->next_rlist->head->next);

    //Delete (B)
    deleteRuleList(first_rlist->next_rlist->next_rlist);

    //Delete (S)
    deleteRuleList(first_rlist);

    printCFG();

    system("pause");

    return 0;
}

void loadCFGFromFile(string fname)
{
    ifstream fin;
    fin.open(fname);

    //String to get the complete line from file
    string rlist;

    //check if the file was available and is open
    if (fin.is_open())
    {
        //read till the end of file
        while (!fin.eof())
        {
            //Read first file from the file
            getline(fin,rlist);

            //Create a new rule list assuming that each row is a new set of rules
            buildRuleList(rlist);

        }
        fin.close();
    }
    else
        cout << "File not found." << endl;


}

RList * addRuleList(string s)
{
    RList * temp = new RList;

    //Prepare the Non Terminal Symbol
    (temp->s).s = s.at(0);
    (temp->s).terminal = 0;
    temp->head = nullptr;
    temp->last = nullptr;
    temp->next_rlist = nullptr;
    temp->prev_rlist = nullptr;

    if (first_rlist == nullptr)
    {
        first_rlist = temp;
        last_rlist = temp;
    }
    else
    {
        last_rlist->next_rlist = temp;
        temp->prev_rlist = last_rlist;
        last_rlist = temp;
    }

    return temp;
}


void buildRuleList(string rlist)
{
    RList * temp = addRuleList((rlist.substr(0, rlist.find('-'))));

    //Update the string
    rlist = rlist.substr(rlist.find('>')+1,rlist.length());

    //prepare the rules
    while (rlist.find('|') != string::npos)
    {
        addRule(temp, rlist.substr(0, rlist.find('|')));
        rlist = rlist.substr(rlist.find('|') + 1, rlist.length());
    }

    if(rlist.length()>0)
        addRule(temp, rlist);
}


void addRule(RList * node, string rule)
{
    Rule * temp = new Rule;

    int i = 0;

    for (;i < rule.length(); i++)
    {
        temp->rule[i].s = rule.at(i);
        temp->rule[i].terminal = isTerminal(temp->rule[i].s);
    }

    //End marker for end of symbols
    temp->rule[i].s = '\0';

    temp->next = nullptr;
    temp->prev = nullptr;

    if (node->head == nullptr)
    {
        node->head = temp;
        node->last = temp;
    }
    else
    {
        node->last->next = temp;
        temp->prev = node->last;
        node->last = temp;
    }

}


bool isTerminal(char ch)
{
    if (ch >= 'A' && ch <= 'Z') return false;
    else
    if (ch >= 'a' && ch <= 'z') return true;
    else
        return false;
}


void deleteRuleList(RList * node)
{
    //safety check
    if (first_rlist != nullptr)
    {
        //if first node
        if (node->prev_rlist == nullptr)
        {
            first_rlist = node->next_rlist;
            node->next_rlist->prev_rlist = nullptr;
        }
            //if last node
        else if (node->next_rlist == nullptr)
        {
            node->prev_rlist->next_rlist = nullptr;
            last_rlist = node->prev_rlist;
        }
            //if middle node
        else
        {
            node->prev_rlist->next_rlist = node->next_rlist;
            node->next_rlist->prev_rlist = node->prev_rlist;
        }
    }

    //Memory leak still to be handled
    delete node;

}

void deleteRule(RList * pnode, Rule * node)
{
    //safety check
    if (pnode->head != nullptr)
    {
        //if first node
        if (node->prev == nullptr)
        {
            pnode->head = node->next;
            node->next->prev = nullptr;
        }
            //if last node
        else if (node->next == nullptr)
        {
            node->prev->next = nullptr;
            pnode->last = node->prev;
        }
            //if middle node
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }

    //Memory leak still to be handled
    delete node;

}


void printCFG()
{
    for (RList * list = first_rlist; list != nullptr; list = list->next_rlist)
    {
        cout << list->s.s << " -> ";

        for (Rule * r = list->head; r != nullptr; r = r->next)
        {
            for (int i = 0; r->rule[i].s != '\0'; i++)
            {
                cout << r->rule[i].s ;
            }

            if(r->next != nullptr)
                cout << "|";
        }

        cout << endl;
    }

}