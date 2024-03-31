#define FIO ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
#include<bits/stdc++.h>
#define v2D vector<vector<int>>v2d(n,vector<int>(n));
#define rall(v) (v).rbegin(),(v).rend()
#define all(v) (v).begin(),(v).end()
#define ull unsigned long long
#define ld long double
#define pb push_back
#define ll long long
#define endl "\n"
#define ss second
#define ff first
using namespace std;
struct Users
{
    string name,email,username,password;
    int ID;
};
struct QA
{
    string qora;
    int from,to,id;

};
int getRandomNumber()
{
    srand(time(nullptr));
    return rand();
}
vector<Users>userData;
vector<QA>answers;
vector<QA>questions;
class Data_Base
{
protected:
    map<string,int>mp;

public:

    void read_file()
    {
        userData.clear();
        Users newuser;
        ifstream userin("dataofuser.txt");
        if(!userin.fail())
        {
            while (userin >> newuser.ID >> newuser.name >> newuser.username >> newuser.email >> newuser.password)
            {

                userData.push_back(newuser);
            }
            userin.close();

        }
        else
        {
            cout<<"there is no data"<<endl;
        }

    }
    //***********************************************************************
    void storeData()
    {
        ofstream userout("dataofuser.txt",ios::trunc);

        for(int i=0;i<userData.size();i++)
        {
            Users tmp=userData[i];
            userout<<tmp.ID<<" "<<tmp.name<<" "<<tmp.username<<" "<<tmp.email<<" ";
            userout<<tmp.password<<endl;
        }
        userout.close();
    }
    ///=========================================================================================
    void uploadquestions()
    {
        ofstream Qout("questions.txt",ios::trunc);
        if(!Qout.fail())
        {
            for(int i=0;i<questions.size();i++)
            {
                QA tmp=questions[i];
                Qout<<tmp.id<<" "<<tmp.from<<" "<<tmp.to<<" "<<tmp.qora<<endl;
            }
        }
        else
        {
            cout<<"Error.."<<endl;
        }


    }
    ///************************************************************************************************
    void readquestions()
    {
        questions.clear();
        ifstream Qin("questions.txt");
        QA newq;
        if(!Qin.fail())
        {
            while(Qin>>newq.id>>newq.from>>newq.to)
            {
                getline(Qin,newq.qora);
                questions.push_back(newq);
            }
            Qin.close();
        }
        else
        {
            cout<<"Ther is no Questions"<<endl;
        }
    }
    ///===================================================================================
    void uploadanswers()
    {
        ofstream answerout("answers.txt",ios::trunc);
        for(int i=0;i<answers.size();i++)
        {
            QA temp=answers[i];
            answerout<<temp.id<<" "<<temp.from<<" "<<temp.to<<" "<<temp.qora<<endl;
        }

    }
    ///*************************************************************************
    void readanswers()
    {
        ifstream answerin("answers.txt");
        QA newans;
        answers.clear();
        if(!answerin.fail())
        {
            while(answerin>>newans.id>>newans.from>>newans.to)
            {
                getline(answerin,newans.qora);
                answers.pb(newans);
            }
            answerin.close();
        }
        else
        {
            cout<<"there is not data"<<endl;
        }

    }
    ///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

};
class base :public Data_Base
{
    QA tmp;
public:
    void setData(int f,int t,string q)
    {
        tmp.id=getRandomNumber();
        tmp.from=f;
        tmp.to=t;
        tmp.qora=q;
    }
    QA getData()
    {
        return tmp;
    }
    void feed()
    {
        readquestions();
        readanswers();
        for(int i=0;i<questions.size();i++)
        {
            vector<string>v;
            bool ch=0;
            QA tmp=questions[i];
            for(int j=0;j<answers.size();j++)
            {
                QA tmpp=answers[j];
                if(tmp.from==tmpp.to&&tmp.id!=-1)
                {
                    ch=1;

                    v.pb(tmpp.qora);

                }

            }
            if(ch==1)
            {
                if(tmp.id!=-1)
                {
                    cout<<"Question ("<<tmp.id<<") from user "<<tmp.from<<" to user "<<tmp.to<<'\t';
                    cout<<"Question: "<<tmp.qora<<"?"<<endl;
                    for(int j=0;j<v.size();j++)
                    {
                        cout<<"Answer : "<<v[j]<<"."<<endl;
                    }
                }

            }

        }
    }



};
class Question:public base {
    QA ques;
    bool flag=0;

public:
    void askquestion() {
        readquestions();
        cout << "Enter your ID and user's ID you want to ask " << endl;
        int t, f;
        string newq;
        cin >> f >> t;
        cout << "Enter your Question" << endl;
        getline(cin, newq, '?');
        string tt = "";
        for (int i = 1; i < newq.size(); i++) {
            tt += newq[i];
        }
        newq = tt;
        setData(f, t, newq);
        ques = getData();
        questions.pb(ques);
        uploadquestions();
    }

    ///*****************************************************************************
    void printquestionstome()
    {
        readquestions();
        cout << "Enter your ID" << endl;
        int id;
        cin >> id;
        if (questions.size() == 0)
        {
            cout << "there is no questions " << endl;
            return;
        }
        bool ch = 0;
        for (int i = 0; i < questions.size(); i++)
        {
            QA tmp = questions[i];
            if (tmp.to == id)
            {
                ch = 1;
                if (tmp.id!= -1)
                {
                    cout << tmp.qora << " ?" << endl;
                }
                else
                {
                    cout << "this is question has been deleted" << endl;
                }
            }
        }
        if (ch == 0)
        {
            cout << "there is no questions to you " << endl;
        }
    }

    ///***********************************************************************************************
    void printquestionsfromme() {
        readquestions();
        cout << "Enter your ID" << endl;
        int id;
        cin >> id;
        if (questions.size() == 0) {
            cout << "there is no questions " << endl;
            return;
        }
        bool ch = 0;
        for (int i = 0; i < questions.size(); i++) {
            QA tmp = questions[i];
            if (tmp.from == id) {
                if (tmp.id != -1) {
                    ch = 1;
                    cout<<tmp.id<<" "<< tmp.qora << " ?" << endl;
                }
            }
        }
        if (ch == 0)
        {
            cout << "there's no questions from you" << endl;
            flag=1;
        }

    }
    ///****************************************************************************************
    void deletequestion()
    {
        //readquestions();
        printquestionsfromme();
        if(flag==0)
        {
            cout << "Ener question's ID you want to delete" << endl;
            int id;
            cin >> id;
            bool ch=0;
            for(int i=0;i<questions.size();i++)
            {
                QA tmp=questions[i];
                if(tmp.id==id)
                {
                    questions[i].id=-1;
                    ch=1;
                    break;
                }
            }
            if(ch==0)
            {
                cout<<"it's not your question ,you can't delete it "<<endl;
            }
            else
            {
                cout<<"Done "<<endl;
            }
            uploadquestions();

        }


    }
    void editquestion()
    {
        //readquestions();
        printquestionsfromme();
        if(flag==0)
        {
            cout<<"Enter question's ID"<<endl;
            int qid;
            cin>>qid;
            string s,t;
            getline(cin,s,'?');
            for(int i=1;i<s.size();i++)
            {
                t+=s[i];
            }
            s=t;
            for(int i=0;i<questions.size();i++)
            {
                QA tmp=questions[i];
                if(tmp.id==qid)
                {
                    tmp.qora=s;
                }
            }
            uploadquestions();
        }
    }
    ///*******************************************************************************

};
///###############################################################################################
class Answer:public base
{
    QA ans;
    bool flag=0;
public:
    void setanswer()
    {
        readanswers();
        cout<<"Enter your ID and user's ID you want to Replay"<<endl;
        int t,f;
        string newans;
        cin>>f>>t;
        cout<<"Enter your answer"<<endl;
        getline(cin,newans,'.');
        string tt="";
        for(int i=1;i<newans.size();i++)
        {
            tt+=newans[i];

        }
        newans=tt;
        setData(f,t,newans);
        ans=getData();
        answers.pb(ans);
        uploadanswers();
    }
    ///**********************************************************************************************
    void printanswerstome()
    {
        readanswers();
        cout << "Enter your ID" << endl;
        int id;
        cin >> id;
        if (questions.size() == 0)
        {
            cout << "there is no questions " << endl;
            return;
        }
        bool ch = 0;
        for (int i = 0; i <answers.size(); i++)
        {
            QA tmp = answers[i];
            if (tmp.to == id)
            {
                ch = 1;
                if (tmp.id!= -1)
                {
                    cout << tmp.qora << " ." << endl;
                }
                else
                {
                    cout << "this is answer has been deleted" << endl;
                }
            }
        }
        if (ch == 0)
        {
            cout << "there is no answers to you " << endl;
        }
    }
    ///***********************************************************************************************
    void printanswersfromme()
    {
        readanswers();
        cout << "Enter your ID" << endl;
        int id;
        cin >> id;
        if (answers.size() == 0) {
            cout << "there is no answers " << endl;
            return;
        }
        bool ch = 0;
        for (int i = 0; i < answers.size(); i++) {
            QA tmp = answers[i];
            if (tmp.from == id) {
                if (tmp.id != -1) {
                    ch = 1;
                    cout<<tmp.id<<" "<< tmp.qora << " ." << endl;
                }
            }
        }
        if (ch == 0)
        {
            cout << "there's no questions from you" << endl;
            flag=1;
        }

    }
    ///****************************************************************************************
    void deleteanswer()
    {
        //readquestions();
        printanswersfromme();
        if(flag==0)
        {
            cout << "Ener question's ID you want to delete" << endl;
            int id;
            cin >> id;
            bool ch=0;
            for(int i=0;i<answers.size();i++)
            {
                QA tmp=answers[i];
                if(tmp.id==id)
                {
                    answers[i].id=-1;
                    ch=1;
                    break;
                }
            }
            if(ch==0)
            {
                cout<<"it's not your answer ,you can't delete it "<<endl;
            }
            else
            {
                cout<<"Done "<<endl;
            }
            uploadanswers();

        }
        else
        {
            cout<<"There is no answers to delete "<<endl;
        }


    }
    ///*******************************************************************************
    void editanswer()
    {
        //readquestions();
        printanswersfromme();
        if(flag==0)
        {
            cout<<"Enter answer's ID"<<endl;
            int aid;
            cin>>aid;
            string s,t;
            getline(cin,s,'?');
            for(int i=1;i<s.size();i++)
            {
                t+=s[i];
            }
            s=t;
            for(int i=0;i<answers.size();i++)
            {
                QA tmp=answers[i];
                if(tmp.id==aid)
                {
                    tmp.qora=s;
                }
            }
            uploadanswers();
        }
    }

};

///###################################################################
class Account :public Data_Base
{
protected:

    map<string,int>mp;
    Users user;
    Answer ans;
    Question ques;

public:
    void Sign_Up()
    {
        read_file();
        cout<<"Enter your Name"<<endl;
        cin>>user.name;
        cout<<"Enter your Username"<<endl;
        cin>>user.username;
        while(!checkUsername(user.username))
        {
            cout<<"this username already exists,please enter another one"<<endl;
            cin>>user.username;
        }
        cout<<"Enter your ID"<<endl;
        cin>>user.ID;
        while (!checkUsername(user.username))
        {
            cout<<"Wrong ID"<<endl;
            cin>>user.ID;
        }
        mp[user.username]=1;
        cout<<"Enter your Email"<<endl;
        cin>>user.email;
        while(!valid_Email(user.email))
        {
            cout<<"Incorrect email please try again"<<endl;
            cin>>user.email;
        }
        cout<<"Enter your password"<<endl;
        cin>>user.password;
        while(!valid_pass(user.password))
        {
            cout<<"password  should be at least 8 characters  "<<endl;
            cin>>user.password;
        }
        userData.push_back(user);
        storeData();
        cout<<"Registration Completed"<<endl;


    }
    ///*******************************************************************************
    bool valid_Email(string s)
    {
        string t="gmail.com";
        int at=s.find("@");
        // cout<<at<<endl;
        if(at==-1||at==0)
        {
            return 0;
        }
        else
        {
            int j=0;
            for(int i=at+1;i<s.size();i++)
            {
                if(s[i]!=t[j])
                {
                    return 0;
                }
                j++;
            }
        }
        return 1;
    }
    ///******************************************************************************
    bool valid_pass(string s)
    {
        if(s.size()<8)
        {
            return 0;
        }
        return 1;
    }
    ///***********************************************************************************
    bool checkUsername(string s)
    {
        if(mp[s]==1)
        {
            return 0;
        }
        else
        {
            return 1;
        }


    }
    ///**********************************************************************
    void Sign_In()
    {
        cout<<"Enter Your Username  "<<endl;
        string s;
        cin>>s;
        cout<<"Enter Your password"<<endl;
        string pass;
        cin>>pass;
        Users tmp;
        bool ch=1,flag=0;
        read_file();
        if(userData.size()==0)
        {
            cout<<"You have to sign Up first"<<endl;
            return;
        }
        // cout<<userData.size()<<endl;
        for(int i=0;i<userData.size();i++)
        {
            tmp=userData[i];
            if(tmp.ID!=-1)
            {
                if(tmp.username==s)
                {
                    flag=1;
                    if(tmp.password!=pass)
                    {
                        ch=0;
                        break;
                    }
                }
            }
        }
        if(flag==0)
        {
            cout<<"you have to sign Up first"<<endl;
        }
        else if(ch==1)
        {
            cout<<"Hello "<<s<<endl;
        }
        else
        {
            cout<<"Username or Password is wrong"<<endl;
        }

    }
    bool checkexist()
    {
        if(userData.size()==0)
        {
            return 0;
        }
        return 1;


    }
    ///*************************************************************
    void ListUsers()
    {
        read_file();
        Users tmp;
        for(int i=0;i<userData.size();i++)
        {

            tmp=userData[i];
            if(tmp.ID!=-1)
            {
                cout<<tmp.ID<<endl;
                cout<<tmp.name<<" "<<tmp.username<<" "<<tmp.email<<endl;
            }


        }
    }
    void deleteAccount()
    {
        read_file();
        cout<<"Enter you ID"<<endl;
        int id;
        cin>>id;
        for(int i=0;i<userData.size();i++)
        {
            if(userData[i].ID==id)
            {
                userData[i].ID=-1;
            }
        }
        storeData();

    }
    void printMenu()
    {
        if(checkexist()==1)
        {
            cout << "1 : Ask Question" << endl
                                          "2 : Answer Question " << endl
                                                                    "3 : print questions to me " << endl
                                                                                                    "4 : print questions from me "<< endl
                                                                                                                                     "5 : Delete question " << endl
                                                                                                                                                               "6 : Edit question " << endl
                                                                                                                                                                                       "7 : List users " << endl
                                                                                                                                                                                                            "8 : show Feed" << endl
                                                                                                                                                                                                                               "9 : print Answers to me"<<endl
                                                                                                                                                                                                                                                          "10 : print Answers from me"<<endl
                                                                                                                                                                                                                                                                                        "11 : Delete Answer"<<endl
                                                                                                                                                                                                                                                                                                              "12 : Edit Answer"<<endl
                                                                                                                                                                                                                                                                                                                                  "13 : Delete Account"<<endl;
            cout << "Enter you choice" << endl;
        }
    }
    void menu()
    {
        int ch;
        while(true)
        {
            try {
                printMenu();
                cin >> ch;
                if (ch > 13)throw "error";
            }
            catch(...) {
                cout << "please enter choice from 1 to 12" << endl;
            }
            if(ch==1)
            {
                ques.askquestion();
            }
            else if(ch==2)
            {
                ans.setanswer();
            }
            else if(ch==3)
            {
                ques.printquestionstome();
            }
            else if(ch==4)
            {
                ques.printquestionsfromme();
            }
            else if(ch==5)
            {
                ques.deletequestion();
            }
            else if(ch==6)
            {
                ques.editquestion();
            }
            else if(ch==7)
            {
                ListUsers();
            }
            else if(ch==8)
            {
                ans.feed();
            }
            else if(ch==9)
            {
                ans.printanswerstome();
            }
            else if(ch==10)
            {
                ans.printanswersfromme();
            }
            else if(ch==11) {
                ans.deleteanswer();
            }
            else if(ch==12) {
                ans.editanswer();
            }
            else if(ch==13)
            {
                deleteAccount();
            }
            if(ch==0)
            {
                break;
            }
        }




    }

};

int main()
{
    Account user;
    cout<<"1-Sign up"<<endl<<"2-Sign In"<<endl;
    int op;
    while(cin>>op)
    {
        if(op==0)
        {
            break;
        }
        if(op==1)
        {
            user.Sign_Up();
        }
        else
        {
            user.Sign_In();
        }
        user.menu();
    }
}
