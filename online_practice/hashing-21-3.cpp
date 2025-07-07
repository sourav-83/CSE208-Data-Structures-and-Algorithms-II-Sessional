#include <bits/stdc++.h>

using namespace std;



int main()
{
    map<string,pair<string,string>>nid;
    map<string,pair<string,string>>name;
    map<string,pair<string,string>>phone;

    while (1)
    {
        cout<<"Enter choice: 1. Enter Data 2.Search Index"<<endl;
        int choice;
        cin>>choice;
        cin.ignore();
        if (choice == 1)
        {
           string id,nm,phn;
           cout<<"Enter name: ";
           getline(cin,nm);
           cout<<"Enter NID no: ";
           cin>>id;
           cout<<"Enter phone no: ";
           cin>>phn;
           nid[id] = {nm,phn};
           name[nm] = {id,phn};
           phone[phn] = {id,nm};

        }
        else if (choice == 2)
        {
            cout<<"Enter search string: ";
            string search;
            getline(cin,search);
            if (nid.count(search))
            {
               cout<<"Match Found:"<<endl;
               cout<<"Name: "<<nid[search].first<<endl;
               cout<<"NID no: "<<search<<endl;
               cout<<"Phone no: "<<nid[search].second<<endl;
            }
            else if (name.count(search))
            {
               cout<<"Match Found:"<<endl;
               cout<<"Name: "<<search<<endl;
               cout<<"NID no: "<<name[search].first<<endl;
               cout<<"Phone no: "<<name[search].second<<endl;
            }
            else if (phone.count(search))
            {
               cout<<"Match Found:"<<endl;
               cout<<"Name: "<<phone[search].second<<endl;
               cout<<"NID no: "<<phone[search].first<<endl;
               cout<<"Phone no: "<<search<<endl;
            }
            else cout<<"No match found"<<endl;


        }
        else continue;

    }
}


