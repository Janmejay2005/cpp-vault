// This is a small version of the code so that we dan't get any problem

#include <iostream>
#include <ctime>
using namespace std;

int main() {
    int d, m, y, h, min, s;
    cout << "Enter DOB (day month year hour minute second): ";
    cin >> d >> m >> y >> h >> min >> s;

    // birth time
    tm birth = {};
    birth.tm_mday = d;
    birth.tm_mon  = m - 1;
    birth.tm_year = y - 1900;
    birth.tm_hour = h;
    birth.tm_min  = min;
    birth.tm_sec  = s;

    // current time
    time_t now = time(0);
    tm *cur = localtime(&now);

    // difference in seconds
    time_t birth_time = mktime(&birth);
    long long diff = difftime(now, birth_time);

    int years = diff / (365*24*3600);
    diff %= (365*24*3600);
    int days = diff / (24*3600);
    diff %= (24*3600);
    int hours = diff / 3600;
    diff %= 3600;
    int minutes = diff / 60;
    int seconds = diff % 60;

    cout << "\nYour age is: " 
         << years << " years, " 
         << days << " days, " 
         << hours << " hours, " 
         << minutes << " minutes, " 
         << seconds << " seconds.\n";
}
