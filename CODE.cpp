#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

// =====================================================
// USER CLASS
// =====================================================

class User
{
protected:
    string username;
    string password;

public:

    User()
    {
        username = "";
        password = "";
    }

    User(string u, string p)
    {
        username = u;
        password = p;
    }

    string getUsername()
    {
        return username;
    }

    bool checkPassword(string p)
    {
        return password == p;
    }

    // Register a new user
    bool registerUser()
    {
        string u, p;

        cout << "\n========== REGISTRATION ==========\n";

        cout << "Enter username: ";
        cin >> u;

        cout << "Enter password: ";
        cin >> p;

        // Check whether username already exists
        ifstream file("dlwise_users.txt");

        string savedUser, savedPassword;

        while (file >> savedUser >> savedPassword)
        {
            if (savedUser == u)
            {
                cout << "\nUsername already exists!\n";
                file.close();
                return false;
            }
        }

        file.close();

        // Save new user
        ofstream outFile("dlwise_users.txt", ios::app);

        outFile << u << " " << p << endl;

        outFile.close();

        username = u;
        password = p;

        cout << "\nRegistration successful!\n";

        return true;
    }

    // Login existing user
    bool login()
    {
        string u, p;

        cout << "\n========== LOGIN ==========\n";

        cout << "Enter username: ";
        cin >> u;

        cout << "Enter password: ";
        cin >> p;

        ifstream file("dlwise_users.txt");

        string savedUser, savedPassword;

        while (file >> savedUser >> savedPassword)
        {
            if (savedUser == u && savedPassword == p)
            {
                username = u;
                password = p;

                file.close();

                cout << "\nLogin successful!\n";
                return true;
            }
        }

        file.close();

        cout << "\nInvalid username or password!\n";

        return false;
    }
};


// =====================================================
// STUDENT CLASS
// =====================================================

class Student : public User
{
private:
    string name;

public:

    Student()
    {
        name = "";
    }

    void setName(string n)
    {
        name = n;
    }

    string getName()
    {
        return name;
    }

    void displayStudent()
    {
        cout << "\nWelcome, " << name << "!\n";
    }
};


// =====================================================
// DEADLINE / EVENT CLASS
// =====================================================

class Event
{
private:

    int deadlineID;
    string username;

    string title;
    string date;
    string time;

    string location;
    string description;
    string type;

    string reminder;
    string priority;

public:

    Event()
    {
        deadlineID = 0;
    }

    // Set event details
    void setEvent(int id, string user)
    {
        deadlineID = id;
        username = user;

        cin.ignore();

        cout << "\n========== ADD DEADLINE / EVENT ==========\n";

        cout << "Enter deadline/event title: ";
        getline(cin, title);

        cout << "Enter deadline date (DD/MM/YYYY): ";
        getline(cin, date);

        cout << "Enter time (HH:MM): ";
        getline(cin, time);

        cout << "Enter location: ";
        getline(cin, location);

        cout << "Enter description: ";
        getline(cin, description);

        cout << "\nSelect Deadline Type:\n";
        cout << "1. Exam\n";
        cout << "2. Assignment\n";
        cout << "3. Class\n";
        cout << "4. Lab\n";
        cout << "5. Meeting\n";
        cout << "6. Project\n";
        cout << "7. Personal\n";
        cout << "8. Other\n";

        int choice;

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            type = "Exam";
            break;

        case 2:
            type = "Assignment";
            break;

        case 3:
            type = "Class";
            break;

        case 4:
            type = "Lab";
            break;

        case 5:
            type = "Meeting";
            break;

        case 6:
            type = "Project";
            break;

        case 7:
            type = "Personal";
            break;

        default:
            type = "Other";
        }

        cout << "\nSet Priority:\n";
        cout << "1. High\n";
        cout << "2. Medium\n";
        cout << "3. Low\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: priority = "High"; break;
        case 2: priority = "Medium"; break;
        default: priority = "Low";
        }

        cout << "\nSet Reminder:\n";
        cout << "1. 10 minutes before\n";
        cout << "2. 30 minutes before\n";
        cout << "3. 1 hour before\n";
        cout << "4. 1 day before\n";
        cout << "5. No reminder\n";

        cout << "Enter choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            reminder = "10 minutes";
            break;

        case 2:
            reminder = "30 minutes";
            break;

        case 3:
            reminder = "1 hour";
            break;

        case 4:
            reminder = "1 day";
            break;

        default:
            reminder = "None";
        }

        cout << "\nDeadline added successfully!\n";
    }

    // Display event
    void display()
    {
        cout << "\n----------------------------------------\n";

        cout << "Deadline ID    : " << deadlineID << endl;
        cout << "Title       : " << title << endl;
        cout << "Date        : " << date << endl;
        cout << "Time        : " << time << endl;
        cout << "Location    : " << location << endl;
        cout << "Type        : " << type << endl;
        cout << "Description : " << description << endl;
        cout << "Priority    : " << priority << endl;
        cout << "Reminder    : " << reminder << " before" << endl;

        cout << "----------------------------------------\n";
    }

    int getID()
    {
        return deadlineID;
    }

    string getDate()
    {
        return date;
    }

    string getTitle()
    {
        return title;
    }

    string getUsername()
    {
        return username;
    }

    string getPriority()
    {
        return priority;
    }

    string getReminder()
    {
        return reminder;
    }

    string getTime()
    {
        return time;
    }

    // Save event to file
    void saveToFile(ofstream &file)
    {
        file << username << "|"
             << deadlineID << "|"
             << title << "|"
             << date << "|"
             << time << "|"
             << location << "|"
             << description << "|"
             << type << "|"
             << priority << "|"
             << reminder << endl;
    }

    // Load event from file
    void loadFromFile(string line)
    {
        stringstream ss(line);

        string temp;

        getline(ss, username, '|');

        getline(ss, temp, '|');
        deadlineID = stoi(temp);

        getline(ss, title, '|');
        getline(ss, date, '|');
        getline(ss, time, '|');
        getline(ss, location, '|');
        getline(ss, description, '|');
        getline(ss, type, '|');
        getline(ss, priority, '|');
        if (priority != "High" && priority != "Medium" && priority != "Low")
        {
            // Backward compatibility with older DLWISE files.
            reminder = priority;
            priority = "Medium";
            return;
        }
        getline(ss, reminder, '|');
    }
};


// =====================================================
// REMINDER CLASS
// =====================================================

class Reminder
{
public:

    void showReminders(vector<Event> events, string username)
    {
        cout << "\n========== DEADLINE REMINDERS ==========\n";

        bool found = false;

        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getUsername() == username)
            {
                if (events[i].getReminder() != "None")
                {
                    cout << "\nDeadline: "
                         << events[i].getTitle() << endl;

                    cout << "Date: "
                         << events[i].getDate() << endl;

                    cout << "Time: "
                         << events[i].getTime() << endl;

                    cout << "Reminder: "
                         << events[i].getReminder()
                         << " before\n";

                    found = true;
                }
            }
        }

        if (!found)
        {
            cout << "\nNo reminders available.\n";
        }
    }
};


// =====================================================
// DLWISE DEADLINE MANAGER CLASS
// =====================================================

class DeadlineManager
{
private:

    vector<Event> events;

public:

    // Load events from file
    void loadEvents()
    {
        events.clear();

        ifstream file("dlwise_deadlines.txt");

        string line;

        while (getline(file, line))
        {
            if (line != "")
            {
                Event e;

                e.loadFromFile(line);

                events.push_back(e);
            }
        }

        file.close();
    }

    // Save all events
    void saveEvents()
    {
        ofstream file("dlwise_deadlines.txt");

        for (int i = 0; i < events.size(); i++)
        {
            events[i].saveToFile(file);
        }

        file.close();
    }

    // Add event
    void addEvent(string username)
    {
        int id = 1;

        if (events.size() > 0)
        {
            id = events.back().getID() + 1;
        }

        Event e;

        e.setEvent(id, username);

        events.push_back(e);

        saveEvents();
    }

    // View all events
    void viewEvents(string username)
    {
        cout << "\n========== MY DEADLINES / EVENTS ==========\n";

        bool found = false;

        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getUsername() == username)
            {
                events[i].display();

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo deadlines/events found.\n";
        }
    }

    // Search event by date
    void searchEvent(string username)
    {
        string date;

        cin.ignore();

        cout << "\nEnter deadline date to search (DD/MM/YYYY): ";
        getline(cin, date);

        bool found = false;

        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getUsername() == username &&
                events[i].getDate() == date)
            {
                events[i].display();

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo deadline/event found on this date.\n";
        }
    }

    // Delete event
    void deleteEvent(string username)
    {
        int id;

        cout << "\nEnter Deadline ID to delete: ";
        cin >> id;

        bool found = false;

        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getID() == id &&
                events[i].getUsername() == username)
            {
                events.erase(events.begin() + i);

                saveEvents();

                cout << "\nDeadline deleted successfully!\n";

                found = true;

                break;
            }
        }

        if (!found)
        {
            cout << "\nDeadline not found.\n";
        }
    }

    // Edit event
    void editEvent(string username)
    {
        int id;

        cout << "\nEnter Deadline ID to edit: ";
        cin >> id;

        bool found = false;

        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getID() == id &&
                events[i].getUsername() == username)
            {
                cout << "\nDeadline found.\n";

                cout << "\nEnter updated deadline details:\n";

                events[i].setEvent(id, username);

                saveEvents();

                cout << "\nDeadline updated successfully!\n";

                found = true;

                break;
            }
        }

        if (!found)
        {
            cout << "\nDeadline not found.\n";
        }
    }

    // Display calendar (for deadline date planning)
    void displayCalendar()
    {
        int month, year;

        cout << "\n========== CALENDAR ==========\n";

        cout << "Enter month (1-12): ";
        cin >> month;

        cout << "Enter year: ";
        cin >> year;

        string months[] =
        {
            "",
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
        };

        cout << "\n       " << months[month]
             << " " << year << "\n\n";

        cout << "Mon Tue Wed Thu Fri Sat Sun\n";

        // Calculate first day of month
        tm timeInfo = {};

        timeInfo.tm_mday = 1;
        timeInfo.tm_mon = month - 1;
        timeInfo.tm_year = year - 1900;

        mktime(&timeInfo);

        int firstDay = timeInfo.tm_wday;

        // Convert Sunday = 0 to Monday = 0
        if (firstDay == 0)
        {
            firstDay = 6;
        }
        else
        {
            firstDay--;
        }

        int daysInMonth;

        if (month == 2)
        {
            if ((year % 400 == 0) ||
                (year % 4 == 0 && year % 100 != 0))
            {
                daysInMonth = 29;
            }
            else
            {
                daysInMonth = 28;
            }
        }
        else if (month == 4 ||
                 month == 6 ||
                 month == 9 ||
                 month == 11)
        {
            daysInMonth = 30;
        }
        else
        {
            daysInMonth = 31;
        }

        // Spaces before first date
        for (int i = 0; i < firstDay; i++)
        {
            cout << "    ";
        }

        // Print dates
        for (int day = 1; day <= daysInMonth; day++)
        {
            cout << setw(3) << day << " ";

            if ((day + firstDay) % 7 == 0)
            {
                cout << endl;
            }
        }

        cout << endl;
    }

    // Show upcoming events
    void upcomingEvents(string username)
    {
        cout << "\n========== UPCOMING DEADLINES ==========\n";

        bool found = false;

        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getUsername() == username)
            {
                events[i].display();

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo upcoming deadlines.\n";
        }
    }

    // Return all events
    vector<Event> getEvents()
    {
        return events;
    }
};


// =====================================================
// MAIN FUNCTION
// =====================================================

int main()
{
    Student student;

    DeadlineManager calendar;

    Reminder reminder;

    int choice;

    bool loggedIn = false;

    cout << "\n========================================\n";
    cout << "     DLWISE - DEADLINE WISE\n";
    cout << "  Student Deadline Tracking System\n";
    cout << "========================================\n";

    // ================================================
    // LOGIN / REGISTER MENU
    // ================================================

    while (!loggedIn)
    {
        cout << "\n1. Login";
        cout << "\n2. Register";
        cout << "\n3. Exit";

        cout << "\n\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            loggedIn = student.login();
        }

        else if (choice == 2)
        {
            student.registerUser();
        }

        else if (choice == 3)
        {
            cout << "\nThank you for using DLWISE!\n";
            return 0;
        }

        else
        {
            cout << "\nInvalid choice!\n";
        }
    }

    // Load saved events
    calendar.loadEvents();

    // ================================================
    // STUDENT NAME
    // ================================================

    cin.ignore();

    cout << "\nEnter your name: ";

    string studentName;

    getline(cin, studentName);

    student.setName(studentName);

    student.displayStudent();

    // ================================================
    // MAIN DASHBOARD
    // ================================================

    do
    {
        cout << "\n\n========================================\n";
        cout << "          DLWISE DASHBOARD\n";
        cout << "========================================\n";

        cout << "1. View Calendar\n";
        cout << "2. Add Deadline / Event\n";
        cout << "3. View All Deadlines\n";
        cout << "4. Search Deadline by Date\n";
        cout << "5. Edit Deadline\n";
        cout << "6. Delete Deadline\n";
        cout << "7. View Upcoming Deadlines\n";
        cout << "8. View Deadline Reminders\n";
        cout << "9. Logout\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:

            calendar.displayCalendar();

            break;

        case 2:

            calendar.addEvent(student.getUsername());

            break;

        case 3:

            calendar.viewEvents(student.getUsername());

            break;

        case 4:

            calendar.searchEvent(student.getUsername());

            break;

        case 5:

            calendar.editEvent(student.getUsername());

            break;

        case 6:

            calendar.deleteEvent(student.getUsername());

            break;

        case 7:

            calendar.upcomingEvents(student.getUsername());

            break;

        case 8:

            reminder.showReminders(
                calendar.getEvents(),
                student.getUsername()
            );

            break;git config --global user.name "Your Name"

        case 9:

            cout << "\nLogging out...\n";

            break;

        default:

            cout << "\nInvalid choice!\n";
        }

    } while (choice != 9);

    cout << "\n========================================\n";
    cout << "        Thank you for using it!\n";
    cout << "========================================\n";

    return 0;
}