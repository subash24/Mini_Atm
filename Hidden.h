//Header files
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//Structure Declaration
struct User
{
    char UserName[32];
    char Password[32];
} User1;

struct BankAmount
{
    double DepositAmount;
    int UniqueId;

} Amount;

// Global Variable
char GUser[32], Pass[32]; //Global user and password
char DepositRegistry[50] = "D:\\C_CppDevops\\Files\\DepositRegistry.txt";
char UserRegistry[50] = "D:\\C_CppDevops\\Files\\UserRegister.txt";
char TempRegistry[50] = "D:\\C_CppDevops\\Files\\TempRegistry.tmp";

//Function Prototypes
void Show();
int SelectUser();
int SignUp();
void FirstDeposit();
int Navigate1();
int Login();
int CheckUp(char UserArr[], char PassArr[]);
void LoggedInMenu();
void WithDraw();
void Deposit();
void CheckBal();
void updateRegistry(int DLine, char array1[], char array2[], float Amount);
void TransHistory(char TN[], char TP[], float TA, char TCh);
const char* CreateFile(char f1[],char f2[],char f3[]);

// Delay Definition
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}

//Current Date Time
const char *CurrentDateTime()
{
    char *DT;
    time_t t;
    time(&t);
    DT = ctime(&t);
    return DT;
}
//End
void Show()
{
    system("cls");
    printf("\n\t*************************************\n");
    printf("\t*                                   *\n");
    printf("\t*  THANK YOU FOR USING OUR SERVICE  *\n");
    printf("\t*                                   *");
    printf("\n\t*************************************\n");
    printf("\nPress Any Key To Exit\n");
    if (getch())
    {
        exit(EXIT_SUCCESS);
    }
}

//User Selection
int SelectUser()
{
    bool ReVal, ReVal1 = false; //ReVal is Return Value
    int choice = 0;
retry:
    printf(">>>>>Select User Type\n");
    printf("1.NEW USER\n2.LOGIN\n3.EXIT\n");
    scanf("%d", &choice);
    printf("\n");
retry1:
    switch (choice)
    {
    case 1:
        ReVal = SignUp(); //calling Signup function
        if (ReVal == true)
        {
            choice = 2;
            goto retry1;
        }
        else if (ReVal == false)
        {
            system("cls");
            goto retry;
        }
        break;
    case 2:
        ReVal1 = Login(); //calling Login function
        break;
    case 3:
        Show();
    default:
        system("cls");
        printf("*****Choose a Correct type\n");
        goto retry;
    }

    return ReVal1;
}

//User Signup
int SignUp()
{
    bool ReVal2 = false;
    char SChoice = 'S';
    char SPin[8];
    FILE *Sfp;
    Sfp = fopen(UserRegistry, "a+");
    if (Sfp == NULL)
    {
        printf("Problem Has been Detected \"Please Try Again Later\"\n");
        delay(1000);
        Show();
    }
    else
    {
        system("cls");
        printf("\n*****SIGNUP*****\n");
        printf("--------------------\n\n");
        printf("Enter a Username\n");
        scanf("%s", User1.UserName);
        printf("Enter a Password ( Must only 4 digits ) \n");
    retry2:
        scanf("%s", User1.Password);
        if (strlen(User1.Password) != 4)
        {
            printf("\n****Password does not meet requirement\n");
            printf(">>>>Please Re-Enter Password( Must be only 4 Digits)\n");
            goto retry2;
        }
        printf("\nPress \"Enter\" to Confirm.........\n");
        if (getch() == 13)
        {
            fprintf(Sfp, "%s \t\t\t %s \n", User1.UserName, User1.Password);
            Amount.UniqueId = (rand() % 9000) + 1000;
            sprintf(SPin, "%d", Amount.UniqueId);
            TransHistory(User1.UserName, SPin, Amount.DepositAmount, SChoice);
            fclose(Sfp);
            printf("\n*******User successfully Created*******\n");
            delay(1500);
            FirstDeposit();
            ReVal2 = Navigate1();
        }
        else
        {
            printf("\nConfirmation Failed\n");
            printf("*******User Not Created*******\n");
            printf("Retrying.....\n\n");
            delay(2000);
            ReVal2 = SignUp();
        }
    }
    return ReVal2;
}

//First Deposit
void FirstDeposit()
{
    double TempDepo;
    Amount.DepositAmount = 0.0;
    char FDChoice = 'F';
    FILE *FDfp;
    char FDPin[8];
    FDfp = fopen(DepositRegistry, "a");
    if (FDfp == NULL)
    {
        printf("Problem Has been Detected \"Please Try Again Later\"");
        Show();
    }
    else
    {
        system("cls");
        printf("*****Auto Directed For First Deposit*****\n");
        printf("\nYour Initial balance is : %0.2lf \n\n", Amount.DepositAmount);
    retry3:
        printf("Enter Your First Deposit (Must be Below 50000 Above 10000)\n");
    retry4:
        scanf("%lf", &Amount.DepositAmount);
        if (Amount.DepositAmount > 50000 || Amount.DepositAmount < 10000)
        {
            delay(500);
            printf(">>>DEPOSIT REQUIREMENTS NOT MET\n");
            printf("Retrying......\n");
            delay(1500);
            system("cls");
            goto retry3;
        }
        else
        {
            printf("Press \"ENTER\" to Continue\n");
            if (getch() == 13)
            {
                system("cls");
                printf("Transaction Id is Generating..... \n");
                printf("*** ID is used to record Transaction Details\n");
                delay(1000);
                printf("\nNOTE THE ID CAREFULLY \n\t>>>> %d \n", Amount.UniqueId);
                printf("\nPress any key.....\n");
                getch();
                fprintf(FDfp, "%s\t\t\t%d\t\t\t%0.2lf\n", User1.UserName, Amount.UniqueId, Amount.DepositAmount);
                fclose(FDfp);
                printf("\n>>>Intial Amount of %0.2f is Deposited in Your Account Successfully\n", Amount.DepositAmount);
                sprintf(FDPin, "%d", Amount.UniqueId);
                TransHistory(User1.UserName, FDPin, Amount.DepositAmount, FDChoice);
            }
            else
            {
                printf("\n>>Wrong Key Pressed\n");
                scanf("RE-ENTER DEPOSIT AMOUNT\n");
                goto retry4;
            }
        }
    }
}

// Navigated to Login Screen
int Navigate1()
{
    char Gval; //get value
    printf("\nWould You Like To Login\n");
    printf(">>>>Press \'Y\' to Continue OR \'N\' to User Select\n");
    Gval = getch();
    if (Gval == 'y' || Gval == 'Y')
    {
        return true;
    }
    else if (Gval == 'n' || Gval == 'N')
    {
        printf("\n");
        return false;
    }
}

//User Login
int Login()
{
    int counter = 3;
    system("cls");
    bool Reval3 = false;
    printf("\n*****LOGIN*****\n");
Retry5:
    printf(">>>Enter Your Details To Authenticate\n\n");
    printf("User Name   : ");
    scanf("%s", GUser);
    printf("\n");
    printf("Password    : ");
    scanf("%s", Pass);
    printf("\n");
    Reval3 = CheckUp(GUser, Pass);
    if (Reval3 == false)
    {
        if (counter > 0)
        {
            delay(1000);
            system("cls");
            printf("\nTHE CREDENTIALS ARE WRONG\n");
            printf("*****You have %d chances left\n\n", counter);
            delay(800);
            counter--;
            goto Retry5;
        }
        else
        {
            printf("\nYou cannot be logged in\n");
            printf(".......TERMINATING.......\n");
            delay(2000);
            exit(EXIT_FAILURE);
        }
    }
    return Reval3;
}

//Validate User's Credentials
int CheckUp(char UserArr[], char PassArr[])
{
    FILE *Cfp;
    bool Result;
    char TempUser[32], TempPass[32];
    Cfp = fopen(UserRegistry, "r");
    if (Cfp == NULL)
    {
        printf("Database Empty\n");
        Show();
    }
    while (!feof(Cfp))
    {

        fscanf(Cfp, "%32s", TempUser);
        fscanf(Cfp, "%32s", TempPass);
        if (strncmp(UserArr, TempUser, 32) == 0 && strncmp(PassArr, TempPass, 32) == 0)
        {
            delay(1000);
            printf("*****Your Credentials are Authenticated*****\n");
            fclose(Cfp);
            delay(1500);
            Result = true;
            break;
        }
        else
        {
            Result = false;
        }
    }
    return Result;
}

void LoggedInMenu()
{
    system("cls");
    char TempUser[32];
    int Lopt;
    strcpy(TempUser, GUser);
    printf("\n\tWELCOME %s \n", strupr(TempUser));
    printf("---------------------------------------------------------------------------------------------------");
    printf("\n\n");
    printf("Select The Mode of Transaction\n*******************************\n\n1.WITHDRAW\n2.DEPOSIT\n3.CHECK BALANCE\n4.EXIT\n");
    scanf("%d", &Lopt);
    switch (Lopt)
    {
    case 1:
        WithDraw();
        break;
    case 2:
        Deposit();
        break;
    case 3:
        CheckBal();
        break;
    case 4:
        Show();
        break;
    default:
        printf("\nChoose a valid Option\n");
        delay(1500);
        LoggedInMenu();
    }
}

// Withdraw Menu
void WithDraw()
{
    system("cls");
    int Ch;
    char WChoice = 'W';
    bool WReval = false;
    FILE *Wfp;
    int CurLine = 0;
    float WithDrawAmount, WTAmount, WNewAmount;
    char Wname[12], Wpin[8], WTPin[8];
    printf("Welcome %s \n", GUser);
    printf("----------------------------------------------------------------------------------------\n");
    printf("Enter The Amount to be Withdrawed (Below 20000)\n>>>> ");
    scanf("%f", &WithDrawAmount);
    if (WithDrawAmount > 20000)
    {
        printf("Withdraw Amount is Limited to 20000\n");
        delay(1200);
        WithDraw();
    }
    else
    {
        printf("\nEnter your Unique ID to continue \n>>>> ");
        scanf("%s", WTPin);
        Wfp = fopen(DepositRegistry, "r");
        while (!feof(Wfp))
        {
            fscanf(Wfp, "%s", Wname);
            fscanf(Wfp, "%s", Wpin);
            fscanf(Wfp, "%f", &WTAmount);
            ++CurLine;
            if (strncmp(Wname, GUser, 32) == 0 && strncmp(Wpin, WTPin, 12) == 0)
            {
                WNewAmount = WTAmount - WithDrawAmount;
                fclose(Wfp);
                if (WNewAmount > 0)
                {
                    updateRegistry(CurLine, Wname, WTPin, WNewAmount);
                    Amount.DepositAmount = WNewAmount;
                    printf("\n>INR %.2f has been debited to your account\n", WithDrawAmount);
                    TransHistory(GUser, Wpin, WithDrawAmount, WChoice);
                    printf("\n\t\t*********Thank You*********\n");
                    printf("\nPress ENTER to Main Menu or Any other key to Exit\n");
                    if (getch() == 13)
                    {
                        LoggedInMenu();
                    }
                    else
                    {
                        Show();
                    }
                }
                else
                {
                    printf("\nYOU DON'T HAVE ENOUGH BALANCE ");
                    delay(500);
                    printf("\nYour Being Directed to main menu.......\n");
                    delay(1500);
                    LoggedInMenu();
                }
                break;
            }
        }
        if (strncmp(Wname, GUser, 32) == 0 && strncmp(Wpin, WTPin, 12) != 0)
        {
            printf("\nYOUR ID IS WRONG....\n");
            printf("\nSelect your option\n1.Retry\n2.Forgot Id\n3.Exit\n");
            scanf("%d", &Ch);
            switch (Ch)
            {
            case 1:
                WithDraw();
                break;
            case 2:
                printf("Login into your Account to view the Id\n ");
                delay(1200);
                WReval = Login();
                if (WReval == true)
                {
                    printf("\nYour Id is \"%s\"\n >", Wpin);
                    printf("Press Any key to continue\n");
                    if (getch())
                    {
                        printf("Directing to the withdraw Menu\n");
                        delay(1000);
                        WithDraw();
                    }
                }
                else
                {
                    printf("Sorry The Account Cannot be Accessed\n");
                    Show();
                }
                break;
            case 3:
                Show();
            default:
                printf("No valid key pressed\n");
                printf(" EXITTING...... ");
                delay(500);
                Show();
            }
        }
    }
}

//Deposit
void Deposit()
{
    system("cls");
    FILE *Dfp;
    int opt1;
    char Dchoice = 'D';
    bool DReval = false;
    char Dname[32], Dpin[12], DTpin[12];
    float DAmount, DepositAmount, DNewAmount;
    int CurLine = 0;
    printf("Welcome %s\n", GUser);
    printf("-----------------------------------------------\n");
    printf("Enter The Amount To Be Deposited\n");
    scanf("%f", &DepositAmount);
    printf("Enter your Id to Continue\n");
    scanf("%s", DTpin);
    Dfp = fopen(DepositRegistry, "r");
    if (Dfp == NULL)
    {
        printf("File cannot Be Opened\n");
    }
    if (DAmount < 15000)
    {

        while (!feof(Dfp))
        {
            fscanf(Dfp, "%s", Dname);
            fscanf(Dfp, "%s", Dpin);
            fscanf(Dfp, "%f", &DAmount);
            ++CurLine;
            if (strncmp(Dname, GUser, 32) == 0 && strncmp(Dpin, DTpin, 12) == 0)
            {
                fclose(Dfp);
                DNewAmount = DAmount + DepositAmount;
                if (DNewAmount < 1000000)
                {
                    updateRegistry(CurLine, Dname, Dpin, DNewAmount);
                    Amount.DepositAmount = DNewAmount;
                    printf("\n>INR %.2f Has Been Credited To Your Account\n", DepositAmount);
                    TransHistory(Dname, Dpin, DepositAmount, Dchoice);
                    printf("\n\t\t*********Thank You*********\n");
                    printf("\nPress ENTER to Main Menu or Any other key to Exit\n");
                    if (getch() == 13)
                    {
                        LoggedInMenu();
                    }
                    else
                        Show();
                }
                else
                {
                    printf("\nYour Account balance is More Than 10lakh\n>>>No More Deposit is Posible\n");
                    delay(500);
                    printf("\nYour Being Directed to main menu.......\n");
                    delay(1500);
                    LoggedInMenu();
                }
                break;
            }
        }
        if (strncmp(Dname, GUser, 32) == 0 && strncmp(Dpin, DTpin, 12) != 0)
        {
            printf("\nYOUR ID IS WRONG....\n");
            printf("\nSelect your option\n1.Retry\n2.Forgot Id\n3.Exit\n");
            scanf("%d", &opt1);
            switch (opt1)
            {
            case 1:
                Deposit();
                break;
            case 2:
                printf("Login into your Account to view the Id\n ");
                delay(1200);
                DReval = Login();
                if (DReval == true)
                {
                    printf("\nYour Id is \"%s\"\n >", Dpin);
                    printf("Press Any key to continue\n");
                    if (getch())
                    {
                        printf("RE-Directing....\n");
                        delay(1200);
                        Deposit();
                    }
                }
                else
                {
                    printf("Sorry The Account Cannot be Accessed\n");
                    Show();
                }
                break;
            case 3:
                Show();
            default:
                printf("No valid key pressed\n");
                printf(" EXITTING...... ");
                delay(500);
                Show();
            }
        }
        else
        {
            printf("Please Note : \n1.The Deposit Limit is 15000 \n\"You Cannot Deposit More than 15000 per Transaction\"\n");
            printf("You Will be redirected to the Deposit Screen......\n");
            printf("Press Enter\n");
            if (getch() == 13)
            {
                delay(1000);
                Deposit();
            }
            else
            {
                printf("Wrong Key Pressed\n");
                Show();
            }
        }
    }
}

//Check balance
void CheckBal()
{
    system("cls");
    FILE *Cfp;
    int opt;
    bool CReval = false;
    char CUser[32], Cpin[12], Tpin[12];
    float Balance;
    printf("Welcome %s \n", GUser);
    printf("----------------------------------------------------------------------------");
    Cfp = fopen(DepositRegistry, "r");
    if (Cfp == NULL)
    {
        printf("Some Problem is Detected\"Retry Later\"\n");
        delay(1000);
        Show();
    }
    else
    {
        printf("\nEnter your Id : ");
        scanf("%s", Tpin);
        while (!feof(Cfp))
        {

            fscanf(Cfp, "%s", CUser);
            fscanf(Cfp, "%s", Cpin);
            fscanf(Cfp, "%f", &Balance);
            if (strncmp(CUser, GUser, 32) == 0 && strncmp(Cpin, Tpin, 12) == 0)
            {
                fclose(Cfp);
                printf("\nThe Current balance in your account is : \n");
                printf("\n\t\t\"%.2f\"\n", Balance);
                printf("\nThank You for Your Time \n");
                printf("\nPress ENTER to main menu or Any other key to exit.\n");
                if (getch() == 13)
                {
                    LoggedInMenu();
                }
                else
                    Show();

                break;
            }
        }
        if (strncmp(CUser, GUser, 32) == 0 && strncmp(Cpin, Tpin, 12) != 0)
        {
            printf("\nYOUR ID IS WRONG....\n");
            printf("\nSelect your option\n1.Retry\n2.Forgot Id\n3.Exit\n");
            scanf("%d", &opt);
            switch (opt)
            {
            case 1:
                CheckBal();
                break;
            case 2:
                printf("Login into your Account to view the Id\n ");
                delay(1500);
                CReval = Login();
                if (CReval == true)
                {
                    printf("\nYour Id is \"%s\"\n >", Cpin);
                    printf("Press Any key to continue\n");
                    if (getch())
                    {
                        printf("RE-Directing....\n");
                        delay(1200);
                        CheckBal();
                    }
                }
                else
                {
                    printf("Sorry The Account Cannot be Accessed\n");
                    Show();
                }
                break;
            case 3:
                Show();
                break;
            default:
                printf("No valid key pressed\n");
                printf(" EXITTING...... ");
                delay(1000);
                Show();
            }
        }
    }
}

//Update Registry
void updateRegistry(int DelLine, char TNarray[], char TParray[], float NAmount)
{
    FILE *fp1, *fp2;
    int temp;
    char buffer[32];
    fflush(stdin);
    fp1 = fopen(DepositRegistry, "r");
    fp2 = fopen(TempRegistry, "w");
    if (fp1 == NULL || fp2 == NULL)
    {
        printf("unable to open file\n");
        exit(EXIT_SUCCESS);
    }
    temp = 0;
    while (fgets(buffer, 32, fp1) != NULL)
    {
        temp++;
        if (temp == DelLine)
        {
            fprintf(fp2, "%s\t\t\t%s\t\t\t%0.2f\n", TNarray, TParray, NAmount);
        }
        else
        {
            fputs(buffer, fp2);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fflush(stdin);
    int Status = remove(DepositRegistry);
    if (Status == 0)
    {
        printf("\nTransaction Successfull\n");
    }
    else
        printf("Transcation Unsuccessful\n");
    rename(TempRegistry, DepositRegistry);
}

//Transaction Tracker
void TransHistory(char Tname[], char Tpin[], float TAmount, char TChoice)
{
    FILE *Tfp;
    char filepath[48] = "D:/C_CppDevops/TransHistory/";
    char filename1[24];
    char filename2[24];
    char *finalpath;
    strcpy(filename1,Tname);
    strcpy(filename2,Tpin);
    strcat(filename1,filename2);
    strcat(filepath,filename1);
    strcat(filepath,".txt");
    finalpath=filepath;
    Tfp = fopen(finalpath, "a");
    if (Tfp == NULL)
    {
        printf("Problem Tracking transaction \"Try later\"\n");
        Show();
    }
    else
    {
        switch (TChoice)
        {
        case 'S':
            fprintf(Tfp, "\nAccount Created By %s On %s", User1.UserName, CurrentDateTime());
            fprintf(Tfp, "******************************************************************\n");
            fclose(Tfp);
            break;
        case 'F':
            fprintf(Tfp, "\t>>>Initial Deposit Of INR %0.2f Has Been Deposited into Your Account\t\t%s\n", TAmount, CurrentDateTime());
            fprintf(Tfp, "----------------------------------------------------------------------------------------------------------\n");
            fclose(Tfp);
            break;
        case 'D':
            fprintf(Tfp, "\t>>>>Rupees %0.2f is deposited to Your Account\t\t%s\n", TAmount, CurrentDateTime());
            fclose(Tfp);
            break;
        case 'W':
            fprintf(Tfp, "\t>>>>Rupees %0.2f is Withdrawed from Your Account\t\t%s\n", TAmount, CurrentDateTime());
            fclose(Tfp);
            break;
        default:
            Show();
            break;
        }
    }
}