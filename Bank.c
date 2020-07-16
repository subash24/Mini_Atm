//All in One Header
#include "Hidden.h"

//Start of main Function
int main()
{
    bool Is_Logged = false;
    srand(time(0));
    printf("**********Welcome To Mini_Atm**********\n");
    printf("---------------------------------------\n\n");
    Is_Logged = SelectUser();
    if (Is_Logged == true)
    {
        printf("Logging in.........");
        delay(1500);
        LoggedInMenu();
    }
    return 0;
}
