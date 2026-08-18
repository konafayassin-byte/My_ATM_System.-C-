#include"cpp.h"

const string Clients_File_Name = "clients_Local_Data_Base.txt";

//                                          .<---->[ATM-System]<---->.

struct sClient
{
    string Account_Number;
    string Pin_Code;
    string Name;
    string Phone;
    double Balance;
    bool Mark_For_Delete = false;
};

sClient Currnet_Client;

void Show_Main_Menue();
void Show_Quick_Withdraw();
void show_Login_screen();
void Go_Back_2_Main_Menue();

enum enQuick_Withdraw_Options
{
    e20D = 1, e50D = 2, e100D = 3, e200 = 4,
    e400D = 5, e600D = 6, e800D = 7, e1000D = 8, eExit = 9
};

enum enMain_Menue_Options
{
    eQuick_Withdraw = 1, eNormal_Withdraw = 2,
    eDeposit = 3, eCheck_Balance = 4, eLogout = 5
};

vector<string> Split_String(string S1, string Delim)
{
    vector<string> vString;

    short pos = 0;
    string sWord;

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient Convert_Line_2_Record(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = Split_String(Line, Seperator);

    Client.Account_Number = vClientData[0];
    Client.Pin_Code = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.Balance = stod(vClientData[4]);//cast string to double
    return Client;
}

string Convert_Record_2_Line(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";
    stClientRecord += Client.Account_Number + Seperator;
    stClientRecord += Client.Pin_Code + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.Balance);
    return stClientRecord;
}

bool Client_Exists_By_Account_Number_PIN_Code(string AccountNumber, string Pin_Code, string FileName)
{

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = Convert_Line_2_Record(Line);
            if (Client.Account_Number == AccountNumber && Client.Pin_Code == Pin_Code)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}

vector <sClient> Save_Cleints_Data_2_File(string FileName, vector <sClient>& vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // Overwrite mode


    string DataLine;


    if (MyFile.is_open())
    {
        for (sClient& C : vClients)
        {
            
            if (C.Account_Number == Currnet_Client.Account_Number)
            {
                C = Currnet_Client;
            }

            
            if (!C.Mark_For_Delete)
            {
                DataLine = Convert_Record_2_Line(C);
                MyFile << DataLine << endl;        
            }
        }

        MyFile.close();
    }

    return vClients;
}

vector <sClient> Load_Cleints_Data_From_File(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = Convert_Line_2_Record(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void Print_Client_Card(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\n|Accout Number: " << Client.Account_Number;
    cout << "\n|Pin Code     : " << Client.Pin_Code;
    cout << "\n|Name         : " << Client.Name;
    cout << "\n|Account Balance: " << Client.Balance;
    cout << "\n-----------------------------------\n";
}

void Print_Client_Balance_RecordLine()
{
    system("cls");
    cout << "|Your Balance " << setw(12) << left << Currnet_Client.Balance;
    cout<<"\n\n\tDo you want to show more info about your card ? \n[Y] | [N] ---> ";
    char c;
    cin>>c;
    if (toupper(c) == 'Y' )
    {
        Print_Client_Card(Currnet_Client);
    }
    else
    {
        Go_Back_2_Main_Menue();
    }
    
}

void Normal_Withdraw(vector <sClient>& vClients)
{

    double Cash_Withdrawed = 0;
    cout << "\n Enter The cash you want to Withdraw to Account : ";
    cin >> Cash_Withdrawed;
    char c;
    cout << "\nAre you sure to add this cash [Y] or [N]? \n";
    cin >> c;
        if (toupper(c) == 'Y')
        {
            Currnet_Client.Balance -= Cash_Withdrawed;
            Save_Cleints_Data_2_File(Clients_File_Name, vClients);
            cout << "\n \tThe cash Withdrawed Successfully!";
            cout << "\nNew Balance: " << Currnet_Client.Balance;
        }
        else
        {
            cout << "No cash Added!";
        }
    return;
}

void Deposit(vector <sClient>& vClients)
{

    double Cash_Added = 0;
    cout << "\n Enter The cash you want to Add to Account : ";
    cin >> Cash_Added;
    char c;
    cout << "\nAre you sure to add this cash [Y] or [N]? \n";
    cin >> c;
    if (toupper(c) == 'Y')
    {
        Currnet_Client.Balance += Cash_Added;
        Save_Cleints_Data_2_File(Clients_File_Name, vClients);
        cout << "\n \tThe cash Added Successfully!";
        cout << "\nNew Balance: " << Currnet_Client.Balance;
    }
    else
    {
        cout << "No cash Added!";
    }
    return;
}

void Show_Deposit_Screen()
{
    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = Load_Cleints_Data_From_File(Clients_File_Name);
    Deposit(vClients);
}

void Show_Normal_Withdraw_Screen()
{
    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = Load_Cleints_Data_From_File(Clients_File_Name);
    Normal_Withdraw(vClients);
}

short Read_Quick_Withdraw_Option()
{
    cout << "Choose what do you want to do? [1 to 9]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

short Read_Main_Menue_Option()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

string Read_Client_Account_Number()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void Go_Back_2_Main_Menue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    Show_Main_Menue();
}

void Go_Back_2_Quick_Withdraw()
{
    cout << "\n\nPress any key to go back to Quick Withdraw...";
    system("pause>0");
    Show_Quick_Withdraw();
}

string Read_Client_PIN_Code()
{
    string PinCode = "";
    cout << "\nPlease enter Pincode? ";
    cin >> PinCode;
    return PinCode;

}

void perform_Quick_Withdraw(vector <sClient>& vClients, enQuick_Withdraw_Options Quick_Withdraw_Option)
{
    switch (Quick_Withdraw_Option)
    {
    case enQuick_Withdraw_Options::e20D:
        Currnet_Client.Balance -= 20;
        cout<<"The New Balance Is"<<Currnet_Client.Balance<<endl;
        Save_Cleints_Data_2_File(Clients_File_Name, vClients);
        Go_Back_2_Quick_Withdraw();
        break;
    case enQuick_Withdraw_Options::e50D:
        Currnet_Client.Balance -= 50;
        cout<<"The New Balance Is"<<Currnet_Client.Balance<<endl;
        Save_Cleints_Data_2_File(Clients_File_Name, vClients);
        Go_Back_2_Quick_Withdraw();
        break;
    case enQuick_Withdraw_Options::e100D:
        Currnet_Client.Balance -= 100;
        cout<<"The New Balance Is"<<Currnet_Client.Balance<<endl;
        Save_Cleints_Data_2_File(Clients_File_Name, vClients);
        Go_Back_2_Quick_Withdraw();
        break;
    case enQuick_Withdraw_Options::e200:
        Currnet_Client.Balance -= 200;
        cout<<"The New Balance Is"<<Currnet_Client.Balance<<endl;
        Save_Cleints_Data_2_File(Clients_File_Name, vClients);
        Go_Back_2_Quick_Withdraw();
        break;
    case enQuick_Withdraw_Options::e400D:
        Currnet_Client.Balance -= 400;
        cout<<"The New Balance Is"<<Currnet_Client.Balance<<endl;
        Save_Cleints_Data_2_File(Clients_File_Name, vClients);
        Go_Back_2_Quick_Withdraw();
        break;
    case enQuick_Withdraw_Options::e600D:
        Currnet_Client.Balance -= 600;
        cout<<"The New Balance Is"<<Currnet_Client.Balance<<endl;
        Save_Cleints_Data_2_File(Clients_File_Name, vClients);
        Go_Back_2_Quick_Withdraw();
        break;
    case enQuick_Withdraw_Options::e800D:
        Currnet_Client.Balance -= 800;
        cout<<"The New Balance Is"<<Currnet_Client.Balance<<endl;
        Save_Cleints_Data_2_File(Clients_File_Name, vClients);
        Go_Back_2_Quick_Withdraw();
        break;
    case enQuick_Withdraw_Options::e1000D:
        Currnet_Client.Balance -= 1000;
        cout<<"The New Balance Is"<<Currnet_Client.Balance<<endl;
        Save_Cleints_Data_2_File(Clients_File_Name, vClients);
        Go_Back_2_Quick_Withdraw();
        break;
    case enQuick_Withdraw_Options::eExit:
        Go_Back_2_Main_Menue();
        break;

    default:
        break;
    }
}

void perform_Main_Menue(enMain_Menue_Options Main_Menue_Option)
{
    switch (Main_Menue_Option)
    {
    case enMain_Menue_Options::eQuick_Withdraw:
        Show_Quick_Withdraw();
        Go_Back_2_Main_Menue();
        break;
    case enMain_Menue_Options::eNormal_Withdraw:
        Show_Normal_Withdraw_Screen();
        Go_Back_2_Main_Menue();
        break;
    case enMain_Menue_Options::eDeposit:
        Show_Deposit_Screen();
        Go_Back_2_Main_Menue();
        break;
    case enMain_Menue_Options::eCheck_Balance:
        Print_Client_Balance_RecordLine();
        Go_Back_2_Main_Menue();
        break;
    case enMain_Menue_Options::eLogout:
        show_Login_screen();
        break;

    default:
        break;
    }
}

void Show_Quick_Withdraw()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tQuick Withdraw Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] 20            [2] 50\n";
    cout << "\t[3] 100           [4] 200\n";
    cout << "\t[5] 400           [6] 600\n";
    cout << "\t[7] 800           [8] 1000\n";
    cout << "\t[9] Exit.\n";
    cout << "===========================================\n";

    vector<sClient> vClients = Load_Cleints_Data_From_File(Clients_File_Name);

    perform_Quick_Withdraw(vClients, enQuick_Withdraw_Options(Read_Quick_Withdraw_Option()));
}

void Show_Main_Menue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw .\n";
    cout << "\t[2] Normal withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    perform_Main_Menue(enMain_Menue_Options(Read_Main_Menue_Option()));
}

bool Check_Login_Requirements(string Account_Number, string PinCode, vector<sClient>& vClients, sClient& Currnet_Client)
{
    for (const sClient& C : vClients)
    {
        if (C.Account_Number == Account_Number && C.Pin_Code == PinCode)
        {
            Currnet_Client = C;
            return true;
        }
    }
    return false;
}

void show_Login_screen()
{

    vector<sClient> vClients = Load_Cleints_Data_From_File(Clients_File_Name);

    bool LoginFailed = false;
    sClient Client;

    do
    {
        system("cls");
        cout << "===========================================\n";
        cout << "\t\tLogin System\n";
        cout << "===========================================\n";

        if (LoginFailed)
        {
            cout << "Invalid Account Number/Pincode! Try Again.\n";
        }

        string Account_Number = Read_Client_Account_Number();
        string PinCode = Read_Client_PIN_Code();

        LoginFailed = !Check_Login_Requirements(Account_Number, PinCode, vClients, Currnet_Client);

    } while (LoginFailed);

    Show_Main_Menue();
}

int main()
{
    
    show_Login_screen();

    system("pause>0");
    return 0;
}
