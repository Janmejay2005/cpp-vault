#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

struct DateTime {
    int day, month, year, hour, minute, second;
};

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

bool isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month, year)) return false;
    return true;
}

bool isValidTime(int hour, int minute, int second) {
    return (hour >= 0 && hour < 24) && 
           (minute >= 0 && minute < 60) && 
           (second >= 0 && second < 60);
}

DateTime getCurrentDateTime() {
    time_t now = time(0);
    tm* current = localtime(&now);
    
    DateTime dt;
    dt.day = current->tm_mday;
    dt.month = current->tm_mon + 1;  // tm_mon is 0-11
    dt.year = current->tm_year + 1900; // tm_year is years since 1900
    dt.hour = current->tm_hour;
    dt.minute = current->tm_min;
    dt.second = current->tm_sec;
    
    return dt;
}

long long dateTimeToSeconds(DateTime dt) {
    // Convert date and time to total seconds since epoch (simplified calculation)
    tm timeinfo = {};
    timeinfo.tm_year = dt.year - 1900;
    timeinfo.tm_mon = dt.month - 1;
    timeinfo.tm_mday = dt.day;
    timeinfo.tm_hour = dt.hour;
    timeinfo.tm_min = dt.minute;
    timeinfo.tm_sec = dt.second;
    
    return mktime(&timeinfo);
}

void calculateAge(DateTime birth, DateTime current) {
    long long birthSeconds = dateTimeToSeconds(birth);
    long long currentSeconds = dateTimeToSeconds(current);
    
    if (birthSeconds > currentSeconds) {
        cout << "\nError: Birth date is in the future!" << endl;
        return;
    }
    
    long long totalSeconds = currentSeconds - birthSeconds;
    
    // Calculate age components
    int ageYears = current.year - birth.year;
    int ageMonths = current.month - birth.month;
    int ageDays = current.day - birth.day;
    int ageHours = current.hour - birth.hour;
    int ageMinutes = current.minute - birth.minute;
    int ageSecondsLeft = current.second - birth.second;
    
    // Adjust for negative values
    if (ageSecondsLeft < 0) {
        ageSecondsLeft += 60;
        ageMinutes--;
    }
    if (ageMinutes < 0) {
        ageMinutes += 60;
        ageHours--;
    }
    if (ageHours < 0) {
        ageHours += 24;
        ageDays--;
    }
    if (ageDays < 0) {
        int prevMonth = (current.month == 1) ? 12 : current.month - 1;
        int prevYear = (current.month == 1) ? current.year - 1 : current.year;
        ageDays += daysInMonth(prevMonth, prevYear);
        ageMonths--;
    }
    if (ageMonths < 0) {
        ageMonths += 12;
        ageYears--;
    }
    
    // Display results
    cout << "\n" << string(50, '=') << endl;
    cout << "           AGE CALCULATION RESULTS" << endl;
    cout << string(50, '=') << endl;
    
    cout << "\nCurrent Date & Time: " 
         << setfill('0') << setw(2) << current.day << "/"
         << setw(2) << current.month << "/" << current.year << " "
         << setw(2) << current.hour << ":"
         << setw(2) << current.minute << ":"
         << setw(2) << current.second << endl;
    
    cout << "Birth Date & Time:   " 
         << setfill('0') << setw(2) << birth.day << "/"
         << setw(2) << birth.month << "/" << birth.year << " "
         << setw(2) << birth.hour << ":"
         << setw(2) << birth.minute << ":"
         << setw(2) << birth.second << endl;
    
    cout << "\nYour Age:" << endl;
    cout << "  " << ageYears << " years, " << ageMonths << " months, " 
         << ageDays << " days" << endl;
    cout << "  " << ageHours << " hours, " << ageMinutes << " minutes, " 
         << ageSecondsLeft << " seconds" << endl;
    
    // Additional statistics
    long long totalDays = totalSeconds / (24 * 60 * 60);
    long long totalHours = totalSeconds / (60 * 60);
    long long totalMinutes = totalSeconds / 60;
    
    cout << "\nTime Elapsed Since Birth:" << endl;
    cout << "  Total Days: " << totalDays << endl;
    cout << "  Total Hours: " << totalHours << endl;
    cout << "  Total Minutes: " << totalMinutes << endl;
    cout << "  Total Seconds: " << totalSeconds << endl;
    
    cout << string(50, '=') << endl;
}

int main() {
    DateTime birth;
    
    cout << string(50, '=') << endl;
    cout << "          REAL-TIME AGE CALCULATOR" << endl;
    cout << string(50, '=') << endl;
    
    // Input birth date
    cout << "\nEnter your birth details:" << endl;
    cout << "Day (1-31): ";
    cin >> birth.day;
    cout << "Month (1-12): ";
    cin >> birth.month;
    cout << "Year: ";
    cin >> birth.year;
    
    // Validate date
    if (!isValidDate(birth.day, birth.month, birth.year)) {
        cout << "Error: Invalid date entered!" << endl;
        return 1;
    }
    
    // Input birth time
    cout << "\nEnter your birth time:" << endl;
    cout << "Hour (0-23): ";
    cin >> birth.hour;
    cout << "Minute (0-59): ";
    cin >> birth.minute;
    cout << "Second (0-59): ";
    cin >> birth.second;
    
    // Validate time
    if (!isValidTime(birth.hour, birth.minute, birth.second)) {
        cout << "Error: Invalid time entered!" << endl;
        return 1;
    }
    
    // Get current date and time
    DateTime current = getCurrentDateTime();
    
    // Calculate and display age
    calculateAge(birth, current);
    
    return 0;
}
