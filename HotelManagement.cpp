#include<iostream.h> // HEADER FILES
#include<fstream.h>
#include<string.h> 
#include<process.h>
#include<stdio.h>
  
class person // FIRST CLASS
{ 
    char name[50], credit[100]; // Credit card code 
	int password, tax, rooms; // password of the owner, total number of rooms  present, final tax of a stay
	int nor, room_id;
	int days; // number of rooms
    char mobile[100]; //  mobile number
    char date[100], month[150]; //date of arrival, month of arrival
public:
	void wtfowner(); // function for the owner
	void getowner(); // function to get details of hotel
    void wtf(); // function to write in file 
    void rff(); // function to read all details 
    void get(); // function to get details 
    void disp(); // function to display details 
    void del(); // function to delete details 
    void search(); // function to search details 
	void modify(); // function to modify details
	int available(int r); // function to check the availability of rooms
	void per_bill();
	int room_no();
} s;       // class ends here 


class room  // SECOND CLASS
{ 
	int suite_price, bed, no_ac_price; // price of a suite, price per bed, price of a non ac room
	int del_price, ac_price;
	char name[50], credit[50], type[50]; // name of the person, credit card number, deluxe or suite  
	char occ[30], ac[50]; // single, double, triple, AC / NON AC ROOM
public: 
	void wtf1owner();
	void get1owner();
    void wtf1(); // function to write in file 
    void rff1(); // function to read all details 
    void get1(); // function to get details 
    void disp1(); // function to display details 
    void del1(); // function to delete details 
    void search1(); // function to search details 
	void modify1(); // function to modify details
	void roombill();
} s1;       // class ends here 

// ************************ CLASS PERSON ***************************

void person::wtfowner()
{
	int ans, M;
M :
    cout<<"ENTER THE PASSWORD."<<endl;
	cin>>password;
	cout<<endl;
	if ( password==123)
	{
	ofstream ofile; 
    ofile.open("person", ios::app); 
        getowner(); 
        ofile.write((char*)&s, sizeof(s)); 
    ofile.close(); 
	}
	else
	{
		cout<<"Wrong Password. To try again enter 1, else enter 2."<<endl;
		cin>>ans;
		if (ans==2)
			exit(0);
		if (ans==1)
			goto M;
	}
}

void person::getowner()
{
	cout<<"Total number of rooms              : ";
	cin>>rooms;
	cout<<"Tax per room per day               : "; 
	cin>>tax;
}

void person::wtf() // function to write in file ( person )
{ 
    ofstream ofile;
    ofile.open("person", ios::app); 
        get(); 
        ofile.write((char*)&s, sizeof(s)); 
    ofile.close();
} 

void person::get() // function to get details ( person )
{ 
	int n;
	cout<<endl;
	cout<<"PERSONAL DETAILS                   : "<<endl;
	cout<<"Number of rooms                    : ";
	cin>>nor;
	nor=available(nor);
	cout<<"Name                               : "; 
    cin>>name;
    cout<<"Mobile Number                      : "; 
    cin>>mobile; 
    cout<<"Credit Card Number                 : "; 
    cin>>credit; 
    cout<<"Date of arrival                    : "; 
    cin>>date; 
    cout<<"Month of arrival                   : "; 
    cin>>month;   
	cout<<"Number of days                     : ";
	cin>>days;
	room_id=((room_no()/528)+100); // size of one entire record was 528
} 

int person::room_no()
{
	ifstream ifile;
	ifile.open("person");
	ifile.seekg(0, ios::end);
	int n=ifile.tellg();
	return n;
}

int person::available(int r) 
{
	fstream f("person",ios::in|ios::out);
	f.seekg(0,ios::beg);
	f.read((char*)&s,sizeof(s));
	int k=f.tellg();
	if ( rooms==0)
		{
		    cout<<"Sorry. All rooms are booked. Try again later. "<<endl;
			exit(0);
		}
	    if ( rooms>0)
		{ 
			    cout<<"Rooms are available."<<endl;
		        rooms=rooms-r;
		        f.seekp(k-sizeof(s),ios::beg);
		        f.write((char*)&s,sizeof(s));
		}
		return r;
		f.close();
} 

void person::rff() // function to read a file ( person )
{ 
    ifstream ifile; 
    ifile.open("person"); 
    ifile.read((char*)&s, sizeof(s)); 
    if (!ifile)
		cout<<"NO RECORD EXISTS."<<endl;
	while(ifile) 
    {
		if ( days!=0)
		{
        disp();
		}
        ifile.read((char*)&s, sizeof(s)); 
    }
    ifile.close(); 
} 

void person::search() // function to search a file ( person )
{ 
    ifstream ifile; 
    char word[20]; // name of the file to be searched 
    char code[20]; // credit card code of the file to be searched 
    int flag=0; // to check whether the record exists or not 
    cout<<endl; 
    cout<<"Name of the person                 : "; 
    cin>>word; 
    cout<<"Credit Card Number                 : "; 
    cin>>code; 
    ifile.open("person"); 
    ifile.read((char*)&s, sizeof(s)); 
    while (ifile) 
    { 
    if (( strcmp(word, name)==0)&&(strcmp(code, credit)==0)) 
    { 
               disp(); 
               flag=1; 
    } 
               ifile.read((char*)&s, sizeof(s)); 
    } 
    if ( flag==0) 
        cout<<"RECORD DOES NOT EXIST. PLEASE TRY AGAIN. "<<endl; 
    ifile.close(); 
} 

void person::disp() // function to display a file ( person )
{ 
	cout<<endl;
    cout<<"The entered details are as follows : "<<endl;
	cout<<"Room number                        : "<<room_id<<endl;
    cout<<"Name                               : "<<name<<endl; 
    cout<<"Mobile Number                      : "<<mobile<<endl; 
    cout<<"Credit card code                   : "<<credit<<endl; 
    cout<<"Date and month of arrival          : "<<date<<" / "<<month<<" / 2013 "<<endl; 
    cout<<"Number of days                     : "<<days<<endl; 
	cout<<"Number of rooms                    : "<<nor<<endl;
} 

void person::del() // function to delete a file ( person )
{ 
	cout<<endl;
    char nam[20], co[20]; // nam, co- name and credit card code of the file to be deleted 
    int flag=0; // to check whether record exists or not 
    ifstream ifile; 
    ofstream ofile; 
    cout<<"Name of the person to be deleted   : "; 
    cin>>nam; 
    cout<<"Credit card code                   : "; 
    cin>>co; 
	cout<<endl;
    ifile.open("person"); 
    ofile.open("Temp", ios::app); 
        ifile.seekg(0, ios::beg); 
        ifile.read((char*)&s, sizeof(s)); 
    while(ifile) 
    { 
        if((strcmp(nam, name)!=0)&&(strcmp(co, credit)!=0)) 
        { 
            ofile.write((char*)&s, sizeof(s));
        } 
		else
			flag=1;
        ifile.read((char*)&s, sizeof(s)); 
    } 
    if ( flag==0) 
        cout<<"RECORD DOES NOT EXIST. PLEASE TRY AGAIN. "<<endl;
        ofile.close(); 
        ifile.close(); 
        remove("person"); 
        rename("Temp","person"); 
        cout<<"RECORD DELETED. "<<endl; 
} 

void person::modify() // function to modify a file ( person )
{
	int choice;
	char n[40], ccc[20];
	fstream f("person", ios::in|ios::out);
	f.seekg(0, ios::beg);
	cout<<"Enter the name of the person       : ";
	cin>>n;
	cout<<"Enter the Credit Card Number       : ";
	cin>>ccc;
	cout<<endl;
	f.read((char*)&s, sizeof(s));
	int a=f.tellg();
	while(!f.eof())
	{
		if((strcmp(n, name)==0)&&(strcmp(ccc, credit)==0))
		{
			cout<<"1. Modify all details"<<endl;
			cout<<"2. Modify date of arrival"<<endl;
			cout<<"3. Modify days of stay"<<endl;
			cout<<"4. Modify number of rooms"<<endl;
			cout<<"Enter your choice          : ";
			cin>>choice;
			switch (choice)
			{
			case 1: {
				get();
				break;
					}
			case 2: {
				cout<<endl;
			    cout<<"Enter the date of arrival  : ";
				cin>>date;
			    cout<<"Enter the month of arrival : ";
				cin>>month;
				break;
					}
			case 3: {
				cout<<endl;
				cout<<"Enter the days of stay     : ";
				cin>>days;
				break;
					}
			case 4: {
				cout<<endl;
				cout<<"Enter the number of rooms  : ";
				cin>>nor;
				break;
					}
			}
			f.seekg(a-sizeof(s), ios::beg);
			f.write((char*)&s, sizeof(s));
		}
		f.read((char*)&s, sizeof(s));
		a=f.tellg();
	}
	f.close();
}

void person::per_bill()
{
	int bill;
	int flag=0;
	ifstream ifile;
	char naam[50], code[50];
	ifile.open("person");  
    if (!ifile)
		cout<<"NO RECORD EXISTS."<<endl;
    cout<<"Enter the name                     : ";
	cin>>naam;
	cout<<"Enter the credit card number       : ";
	cin>>code;
	ifile.read((char*)&s, sizeof(s));
	while (ifile)
	{
		if ((strcmp(naam, name)==0)&&(strcmp(code, credit)==0))
		{
			flag=1;
	     /* cout<<"Number of rooms are                : "<<nor<<endl;
	        cout<<"Days of stay are                   : "<<days<<endl; */
			bill=tax*nor*days;
	        cout<<"The tax price for the stay is      : "<<bill<<endl;
		}
		ifile.read((char*)&s, sizeof(s));
	}
	if ( flag==0)
		cout<<"RECORD NOT FOUND."<<endl;
	ifile.close();
} 

// ************************* CLASS ROOM ******************************

void room::wtf1owner()
{
	ofstream ofile; 
    ofile.open("room", ios::app); 
        get1owner(); 
        ofile.write((char*)&s1, sizeof(s1)); 
    ofile.close(); 
}

void room::get1owner()
{
	cout<<"Price of a deluxe room             : ";
	cin>>del_price;
	cout<<"Price of a suite                   : ";
	cin>>suite_price;
	cout<<"Price of one bed                   : ";
	cin>>bed;
	cout<<"Price of an Ac room                : ";
	cin>>ac_price;
	cout<<"Price of a Non Ac room             : ";
	cin>>no_ac_price;
}

void room::wtf1() // function to write in file ( room )
{ 
    ofstream ofile1; 
    ofile1.open("room", ios::app); 
        get1(); 
        ofile1.write((char*)&s1, sizeof(s1)); 
    ofile1.close(); 
} 

void room::get1() // function to get details ( room )
{ 
	cout<<endl;
    cout<<"ROOM DETAILS                       : "<<endl;
    cout<<"Name                               : "; 
    cin>>name; 
	cout<<"Credit Card Number                 : ";
	cin>>credit;
	cout<<"For Ac enter A, for Non Ac enter N : ";
	cin>>ac;
    cout<<"Type of room  ( deluxe / suite)    : "; 
    cin>>type; 
    cout<<"Occupancy ( double / triple )      : "; 
    cin>>occ;  
}

void room::rff1() // function to read a file ( room )
{  
    ifstream ifile1; 
    ifile1.open("room"); 
    ifile1.read((char*)&s1, sizeof(s1)); 
	if (!ifile1)
		cout<<"NO RECORD EXISTS."<<endl;
    while(ifile1) 
    { 
        disp1(); 
        ifile1.read((char*)&s1, sizeof(s1)); 
    }
    ifile1.close(); 
} 
 
void room::search1() // function to search a file ( room )
{  
    ifstream ifile1; 
    char nam[20], ccc[50]; // name of the file to be searched 
    int flag=0; // to check whether the record exists or not 
    cout<<endl; 
    cout<<"Name of the person                 : "; 
    cin>>nam;  
	cout<<"Credit Card Number                 : ";
	cin>>ccc;
    ifile1.open("room"); 
    ifile1.read((char*)&s1, sizeof(s1)); 
    while (ifile1) 
    { 
    if((strcmp(nam, name)==0)&&(strcmp(ccc, credit)==0)) 
    { 
               disp1(); 
               flag=1; 
    } 
               ifile1.read((char*)&s1, sizeof(s1)); 
    } 
    if ( flag==0) 
        cout<<"RECORD DOES NOT EXIST. PLEASE TRY AGAIN. "<<endl; 
    ifile1.close(); 
}
  
void room::disp1() // function to display a file ( room )
{ 
	cout<<endl;
    cout<<endl<<"The entered details are as follows : "<<endl;
    cout<<"Name                               : "<<name<<endl; 
	cout<<"Credit card code                   : "<<credit<<endl;
	cout<<"Ac or non Ac rooms                 : "<<ac<<endl;
    cout<<"Type or rooms                      : "<<type<<endl; 
    cout<<"Occupancy                          : "<<occ<<endl; 
}

void room::del1() // function to delete a file ( room )
{ 
    char nam[20], ccc[50];// name of the file to be deleted, credit card code
    int flag=0; // to check whether record exists or not 
    ifstream ifile1; 
    ofstream ofile1; 
    cout<<"Name of the person                 : "; 
    cin>>nam;
	cout<<"Credit Card Number                 : ";
	cin>>ccc;
	cout<<endl;
    ifile1.open("room"); 
    ofile1.open("Tem", ios::app); 
        ifile1.seekg(0, ios::beg); 
        ifile1.read((char*)&s1, sizeof(s1)); 
    while(ifile1) 
    { 
        if((strcmp(nam, name)!=0)&&(strcmp(ccc, credit)!=0)) 
        { 
            ofile1.write((char*)&s1, sizeof(s1)); 
        } 
		else
			flag=1;
        ifile1.read((char*)&s1, sizeof(s1)); 
    } 
    if ( flag==0) 
        cout<<"RECORD DOES NOT EXIST. PLEASE TRY AGAIN. "<<endl; 
        ofile1.close(); 
        ifile1.close(); 
        remove("room"); 
        rename("Tem","room"); 
        cout<<"RECORD DELETED. "<<endl; 
} 

void room::modify1() // function to modify a file ( room )
{
	int choic;
	char nam[40], ccc[50];
	fstream f1 ("room", ios::in|ios::out);
	f1.seekg(0, ios::beg);
	cout<<"Enter the name of the person       : ";
	cin>>nam;
	cout<<"Credit Card Number                 : ";
	cin>>ccc;
	cout<<endl;
	f1.read((char*)&s1, sizeof(s1));
	int a1=f1.tellg();
	while(!f1.eof())
	{
		if((strcmp(nam, name)==0)&&(strcmp(ccc, credit)==0)) 
		{
			cout<<"1. Modify all details"<<endl;
			cout<<"2. Modify type of room"<<endl;
			cout<<"3. Modify occupancy"<<endl;
            cout<<"Enter your choice                  : "<<endl;
			cin>>choic;
			switch (choic)
			{
			case 1: {
				get1();
				break;
					}
			case 2: {
				cout<<endl;
	            cout<<"Enter the type of room             : ";
				cin>>type;
				break;
					}
			case 3: {
				cout<<endl;
	            cout<<"Enter the occupancy                : ";
				cin>>occ;
				break;
					}
			}
			f1.seekg(a1-sizeof(s1), ios::beg);
			f1.write((char*)&s1, sizeof(s1));
		}
		f1.read((char*)&s1, sizeof(s1));
		a1=f1.tellg();
	}
	f1.close();
}

void room::roombill()
{
	double bill;
	int flag=0, t=0;
	ifstream ifile;
	char naam[50], code[50];
	ifile.open("room"); 
    if (!ifile)
		cout<<"NO RECORD EXISTS."<<endl;
    cout<<"Enter the name                     : ";
	cin>>naam;
	cout<<"Credit Card Number                 : ";
	cin>>code;
	ifile.read((char*)&s, sizeof(s));
	while (ifile)
	{
		if ((strcmp(naam, name)==0)&&(strcmp(code, credit)==0))
		{
			flag=1;
			if (strcmp(type,"deluxe")==0)
			{
				if ( strcmp(ac, "A")==0)
				{
					if ( strcmp(occ, "double")==0)
					{
						t=1;
					}
					else 
					{
						t=2;
					}
				}
				else
				{
					if ( strcmp(occ, "double")==0)
					{
                        t=3;
					}
					else
					{
						t=4;
					}
				}
			}
			if ( strcmp(type, "suite")==0)
			{
				if ( strcmp(ac, "A")==0)
				{
					if ( strcmp(occ, "double")==0)
					{
						t=5;
					}
					else 
					{
						t=6;
					}
				}
				else
				{
					if ( strcmp(occ, "double")==0)
					{
						t=7;
					}
					else
					{
						t=8;
					}
				}
			}
		}
		ifile.read((char*)&s1, sizeof(s1));
	}
	if ( flag==0)
		cout<<"RECORD NOT FOUND."<<endl;
	ifile.close();
	ifile.open("room");
	ifile.read((char*)&s1, sizeof(s1));
	if ( t==1)
		bill=del_price+ac_price+(2*bed);
	else if ( t==2)
		bill=del_price+ac_price+(3*bed);
	else if ( t==3)
		bill=del_price+no_ac_price+(2*bed);
	else if ( t==4)
		bill=del_price+no_ac_price+(3*bed);
	else if ( t==5)
		bill=suite_price+ac_price+(2*bed);
	else if ( t==6)
		bill=suite_price+ac_price+(3*bed);
	else if ( t==7)
		bill=suite_price+no_ac_price+(2*bed);
	else 
		bill=suite_price+no_ac_price+(3*bed);
	cout<<"The room bill per room per day is  : Rs."<<bill<<endl;
	ifile.close();
}

//************************* MAIN FUNCTION ****************************

void main() // main function
{ 
    int n, N, ch, ans, yes; // option choice 
    cout<<endl; 
    cout<<"WELCOME TO MEDALLION HOTEL RESERVATION SYSTEM"<<endl;
	cout<<endl;
	cout<<"Enter the choice                   : "<<endl;
	cout<<"1. Employee"<<endl;
	cout<<"2. Customer"<<endl;
	cout<<"3. Exit"<<endl;
	cin>>ans;
	if ( ans==1)
	{
		cout<<"1. Write"<<endl;
		cout<<"2. Exit"<<endl;
		cin>>yes;
		if ( yes==1)
		{
		    s.wtfowner();
			s1.wtf1owner();
		}
		if ( yes==2)
			exit(0);
	}
	if ( ans==2)
	{
	    do
	    {
	        cout<<endl;
            cout<<"Enter the choice                   : "<<endl;
	        cout<<" 1. Personal details"<<endl;
	        cout<<" 2. Room details"<<endl;
           	cout<<" 3. Bill"<<endl;
	        cin>>ch;
	        switch ( ch)
	        {
	            case 1 : {
	                cout<<endl;
                    cout<<"Personal details                  :"<<endl<<endl;
                    cout<<"1. Write data"<<endl; 
                    cout<<"2. Read data"<<endl; 
                    cout<<"3. Search data"<<endl; 
                    cout<<"4. Delete data"<<endl; 
	                cout<<"5. Modify data"<<endl;
	                cout<<"6. Exit"<<endl<<endl;
                    cout<<"ENTER YOUR CHOICE : "; 
                    cin>>n; 
                    switch (n) 
                    { 
                        case 1: { 
                            s.wtf(); 
		                    s1.wtf1();
                            break; 
                                } 
                        case 2: { 
                            s.rff(); 
                            break; 
                                } 
                        case 3: { 
                            s.search(); 
                            break; 
                                } 
                       case 4: { 
                            s.del(); 
                            break; 
                               } 
	                   case 5: {
	                        s.modify();
	                    	break;
		                   	   }
                       case 6: { 
                            exit(0); 
                               } 
                   } 
                   break;
			            }
	          case 2 : {
	              cout<<endl;
	              cout<<"Room details                       :"<<endl<<endl; 
                  cout<<"1. Read data"<<endl; 
                  cout<<"2. Search data"<<endl; 
                  cout<<"3. Delete data"<<endl; 
	              cout<<"4. Modify data"<<endl;
	              cout<<"5. Exit"<<endl<<endl;
                  cout<<"Enter your choice                 : "; 
                  cin>>N; 
                  switch (N) 
                  {  
                      case 1: { 
                          s1.rff1(); 
                          break; 
                              } 
                      case 2: { 
                          s1.search1(); 
                          break; 
                              } 
                      case 3: { 
                          s1.del1(); 
                          break; 
                              } 
	                  case 4: {
	                      s1.modify1();
		                  break;
			                  }
                      case 5: { 
                          exit(0); 
                              } 
                  }  
	              break;
		          	 }
			  case 3 : {
				  	int z;
		            cout<<"Enter the choice                : "<<endl;
		            cout<<"1. Personal bill"<<endl;
		            cout<<"2. Room bill"<<endl;
	             	cin>>z;
	              	switch (z)
		                {
		                    case 1 : { s.per_bill(); break; }
	                     	case 2 : { s1.roombill(); break; }
		                }
		                break;
	                    }
			}
	    }
	    while ( ch!='2');
	}
}
