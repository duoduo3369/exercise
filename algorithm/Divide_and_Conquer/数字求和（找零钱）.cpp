#include  <iostream>

using namespace std;

int change(int number,int denomination)
{
    cout << number << " " << denomination << endl;
    if(number == 0)
    {
        return 1;
    }
    else if(number < 0 || denomination <= 0)
    {
        return 0;
    }
    else
    {
        return change(number,denomination-1) + change(number-denomination,denomination);
    }
}

int main(int argc, char *argv[])
{
    int count = change(6,6);
    char* star = "*****************";
    cout << star << endl
         << count << endl;
    return 0;
}
