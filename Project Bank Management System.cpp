#include<iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
using namespace std;

class Account
{
	private:
		int id,iamount,depo;
		char hname[50],type;
	public:
		Account(){id=iamount=0;strcpy(hname,"Null");}

		void new_account()
		{
		    cout<<"\n*******************************";
			cout<<"\nEnter the Account ID : ";cin>>id;
			cout<<"\nEnter the Name of Account Holder : ";cin.ignore();cin>>hname;
			cout<<"\nEnter the Type of Account (C/S) : ";cin>>type;
                if(type=='S')
                {
                    cout<<"Your Amount is Saving Account";
                }
                if(type=='C')
                {
                    cout<<"Your Amount is Current Account";
                }
                else{
                    cout<<"Enter Correct Type";
                }
			cout<<"\nEnter the Initial Amount(>=500) : ";cin>>iamount;
                    if (iamount<500)
                    {
                        while(iamount<500)
                        {
                            cout<<"Add "<<500-iamount<<" more ";
                            cin>>depo;
                            iamount=iamount+depo;
                        }
                        cout<<"Your Balance is "<<iamount;
                    }
                    else{
                        cout<<"Your Balance is "<<iamount;
                    }
			cout<<"\nNew Account Created Successfully...";
			cout<<"\n*******************************";
		}
		void show_account()
		{
		    cout<<"\n*******************************";
			cout<<"\nAccount ID : "<<id;
			cout<<"\nAccount Holder Name :"<<hname;
			cout<<"\nType of Account :"<<type;
			cout<<"\nBalance :"<<iamount;
			cout<<"\n*******************************";
		}
		void account_modify()
		{
		    cout<<"\n*******************************";
			cout<<"\nAccount ID : "<<id;
			cout<<"\nModify Account Holder Name : ";cin.ignore();cin>>hname;
			cout<<"Modify Type of Account(C/S) : ";cin>>type;
			cout<<"\nAccount Balance Will not Modify : "<<iamount;
			cout<<"\n*******************************";
		}
        void write_account();
        void display_sp();
        void search_name(char *);
        void search_id(int );
        void modify_account(char *);
        void delete_account(char *);
        void intro();
};
void Account::write_account()
{
    if (id==0)
    {
    	cout<<"\nAccount data not Initialized.";
    }
    else{
    ofstream fout;
    fout.open("account.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
    }
}
void Account::display_sp()
{
    ifstream fin;
    fin.open("account.dat",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"\nFile not found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            show_account();
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }
}
void Account::search_name(char *hn)
{
    int counter=0;
    ifstream fin;
    fin.open("account.dat",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"\nFile not found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(!strcmp(hn,hname)){
                show_account();
                counter++;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(counter==0)
            cout<<"\nRecord not found";
        fin.close();
    }

}
void Account::search_id(int ia)
{
    bool found = false;
	ifstream fin("account.dat");
	if(!fin)
	{
		cout<<"File not found\a\n";
		return;
	}

	else
	{
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof())
		{
			if(ia==id)
			{
				found = true;
				show_account();
			}
			fin.read((char*)this,sizeof(*this));
		}
		if(!found)
			cout<<"Record not found\n";
		fin.close();
	}

}
void Account::delete_account(char *hn)
{
    ifstream fin;
    ofstream fout;
    fin.open("account.dat",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"\nFile not found";
    }
    else{

        fout.open("tempfile.dat",ios::out|ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(strcmp(hname,hn))
            {
                fout.write((char*)this,sizeof(*this));
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("account.dat");
        rename("tempfile.dat","account.dat");
    }
}
void Account::modify_account(char *moac)
{
    fstream file;
    file.open("account.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));
    while(!file.eof()){
        if(!strcmp(moac,hname)){
            account_modify();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }
    file.close();
}
int intro()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : ALI HASNAT, SYED NAD-E-ALI, BURHAN ALI";
	cout<<"\n\nUNIVERSITY : NATIONAL TEXTILE UNIVERSITY";
	cin.get();
}
int menu()
{
    int choice;
    cout<<"\n\n\n\tMAIN MENU";
    cout<<"\n\n\t01. NEW ACCOUNT";
    cout<<"\n\n\t02. ALL ACCOUNT HOLDER LIST";
    cout<<"\n\n\t03. SEARCH BY NAME";
    cout<<"\n\n\t04. SEARCH BY ID";
    cout<<"\n\n\t05. DELETE AN ACCOUNT";
    cout<<"\n\n\t06. MODIFY AN ACCOUNT";
    cout<<"\n\n\t07. EXIT\n";
    cout<<"\n\n\tEnter your choice--> ";
    cin>>choice;
    return(choice);
}
int main()
{
    Account a1;
    intro();
    while(1){
            system("cls");
        switch(menu())
        {
            case 1:
                a1.new_account();
                a1.write_account();
                break;
            case 2:
                a1.display_sp();
                break;
            case 3:
                cout<<"\nEnter Name of Account Holder to Search : ";
                char nam[20];
                cin.ignore();
                cin>>nam;
                a1.search_name(nam);
                break;
            case 4:
                cout<<"\nEnter Account ID to Search : ";
                int ID;
                cin.ignore();
                cin>>ID;
                a1.search_id(ID);
                break;
            case 5:
                cout<<"\nEnter Account Name to Delete Account : ";
                char hnam[20];
                cin.ignore();
                cin>>hnam;
                a1.delete_account(hnam);
                break;
            case 6:
                cout<<"\nEnter Account Name to Modify Record : ";
                char hna[20];
                cin.ignore();
                cin>>hna;
                a1.modify_account(hna);
                break;
            case 7:
                cout<<"\nThank you for using BANK MANAGEMENT SYSTEM";
                exit(0);
            default:
                cout<<"\nInvalid Choice";
        }
        getch();
    }
}

