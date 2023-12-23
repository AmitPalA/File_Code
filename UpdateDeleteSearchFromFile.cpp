#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<conio.h>
using namespace std;

class student
{
    private:
        char name[30];
        int rollno;
        float marks;
    public:
        student()
        {
            rollno=0;
            marks=0;
        }
        void SetName();
        void SetRollNumber();
        void SetMarks();
        void setter();
        void getter();
        void writeToFile();
        void readAllFileData();
        void updateData();
        void searchData();
        void deleteData();

};
void student::SetName()
{
        cout<<"Enter Name : ";
        cin.ignore();
        cin.getline(name,29);
}
void student::SetRollNumber()
{
        cout<<"Enter Roll Number: ";
        cin>>rollno;
}
void student::SetMarks()
{
        cout<<"Enter Marks : ";
        cin>>marks;
}
void student::setter()
{
     SetName();
     SetRollNumber();
     SetMarks();
}
void student::getter()
{
            cout<<"\nName- "<<name<<endl;
            cout<<"Rollno- "<<rollno<<endl;
            cout<<"Marks- "<<marks<<endl;
}
void student::writeToFile()
{
            setter();
            ofstream fout;
            fout.open("studentDataStore.txt",ios::app|ios::binary);
            if(!fout){
                cerr<<"File not open...";
                return;
            }
            else{

                fout.write((char*)this, sizeof(*this));
                cout<<"\nData successfully written into file...";
                fout.close();
            }
}
void student::readAllFileData()
{
            int flag=0;
            ifstream fin;
            fin.open("studentDataStore.txt",ios::in|ios::binary);
            if(!fin){
                cerr<<"file not exist...";
                return;
            }
            else{
                fin.seekg(0,ios::beg);
                fin.read((char*)this,sizeof(*this));
                while(!fin.eof()){
                    getter();
                    flag=1;
                    fin.read((char*)this,sizeof(*this));
                }
                fin.close();
                if(flag==0)
                    cout<<"No record found...";
            }
}
void student::updateData()
{
                int flag=0;
            ofstream fout;
            ifstream fin;
            student stu;

            fin.open("studentDataStore.txt",ios::in|ios::binary);
            if(!fin)
            {
                cerr<<"Data not exist..";
                return ;
            }
            else
            {
                int roll;
                cout<<"Enter Roll Number For Update : ";
                cin>>roll;


                fout.open("temp.txt", ios::out|ios::binary);
                if(!fout){
                    cout<<"File not open...";
                    return;
                }

                fin.read((char*)this,sizeof(*this));
                do{
                    if(!(roll == rollno)){
                        fout.write((char*)this,sizeof(*this));
                    }else{

                        stu = *this;
                        cout<<"\n1.Name Update...";
                        cout<<"\n2.Roll Number Update...";
                        cout<<"\n3.Marks Update...";
                        cout<<"\n4.No Update...";

                        int key;
                        cout<<"\n\nEnter choice : ";
                        cin>>key;

                        switch(key)
                        {
                            case 1:
                                stu.SetName();
                                break;
                            case 2:
                                stu.SetRollNumber();
                                break;
                            case 3:
                                stu.SetMarks();
                                break;
                            case 4:
                                return ;
                                break;
                            default:
                                cout<<"Invalid Choice...";

                        }


                        flag=1;
                    }
                    fin.read((char*)this,sizeof(*this));
                }while(!fin.eof());

            }
            fout.close();
            fin.close();
            remove("studentDataStore.txt");
            rename("temp.txt","studentDataStore.txt");
            if(flag==1){


                    ofstream fout;
                    fout.open("studentDataStore.txt",ios::app | ios::binary);
                    if(!fout)
                    {
                        cerr<<"file is not exist";
                        return ;
                    }
                    else
                    {
                        fout.write((char*)&stu,sizeof(stu));
                        fout.close();
                    }
                    cout<<"Student Data Updated successfully...";




            }
             else
                    cout<<"Data is not found...";

}
void student::deleteData()
{
            int flag=0;
            ofstream fout;
            ifstream fin;

            fin.open("studentDataStore.txt",ios::in|ios::binary);
            if(!fin)
            {
                cerr<<"Data not exist..";
                return ;
            }
            else
            {
                int roll;
                cout<<"Enter Roll Number : ";
                cin>>roll;


                fout.open("temp.txt", ios::out|ios::binary);
                if(!fout){
                    cout<<"File not open...";
                    return;
                }

                fin.read((char*)this,sizeof(*this));
                do{
                    if(!(roll == rollno)){
                        fout.write((char*)this,sizeof(*this));
                    }else{
                        flag=1;
                    }
                    fin.read((char*)this,sizeof(*this));
                }while(!fin.eof());

            }
            fout.close();
            fin.close();
            remove("studentDataStore.txt");
            rename("temp.txt","studentDataStore.txt");
            if(flag==1)
                    cout<<"Student Data deleted successfully...";
             else
                    cout<<"Data is not found...";

}
void student::searchData()
{
            int flag=0;
            ifstream fin;

            fin.open("studentDataStore.txt",ios::in|ios::binary);
            if(!fin)
            {
                cerr<<"Data not exist..";
                return ;
            }
            else
            {
                char userName[30];
                cout<<"Enter Name For Search: ";
                cin.ignore();
                cin.getline(userName,29);

                    fin.read((char*)this,sizeof(*this));
                    do{
                        int r=strcmp(name,userName);
                        if((r==0)){
                            getter();
                            flag=1;
                            break;
                    }else{
                        fin.read((char*)this,sizeof(*this));}
                    }while(!fin.eof());
             }
            fin.close();
            if(!(flag==1))
                    cout<<"Data is not found...";

}

int main()
{
    student s1;

    while(1)
    {
        system("cls");
        cout<<"\n 1.write data";
        cout<<"\n 2.read all data";
        cout<<"\n 3.update data";
        cout<<"\n 4.delete data";
        cout<<"\n 5.search data";
        cout<<"\n 6.exit";
        cout<<"\n\n Select an option : ";
        int input;
        cin>>input;

        switch(input)
        {
            case 1:
                s1.writeToFile();
                getch();
                break;
            case 2:
                s1.readAllFileData();
                getch();
                break;
            case 3:
                s1.updateData();
                getch();
                break;
            case 4:
                s1.deleteData();
                getch();
                break;
            case 5:
                s1.searchData();
                getch();
                break;
            case 6:
                exit(0);
                getch();
                break;
            default:

                cout<<"\n Invalid option...";

        }
    }


    return 0;

}

