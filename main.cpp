#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Date {
    int year = 0;
    int month = 0;
    int day = 0;
};

istream& operator>>(istream& stream, Date& date) {
    int day, month, year;
    try {
        if (!(stream >> day) || day < 0 || day > 31 || stream.peek() != '.') throw string("");
        stream.ignore(1);
        if (!(stream >> month) || month < 0 || month > 12 || stream.peek() != '.') throw string("");
        stream.ignore(1);
        if (!(stream >> year) || year < 0 || year > 9999) throw string("");
        if (stream.peek() == ' ' || stream.peek() == '\n' || stream.peek() == '\t');
        else throw string("");
        date.year = year;
        date.month = month;
        date.day = day;
    }
    catch (string&) {}
    return stream;
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setfill('0');
    stream << setw(2) << date.day << '.' << setw(2) << date.month << '.' << setw(4) << date.year;
    return stream;
}

struct Record {
    string first_name;
    string last_name;
    Date date;
    int payment = 0;
};

istream& operator>>(istream& stream, Record& rec) {
    string first_name, last_name;
    Date date;
    int payment;
    stream >> first_name >> last_name >> date >> payment;
    rec.first_name = first_name;
    rec.last_name = last_name;
    rec.date = date;
    rec.payment = payment;
    return stream;
}

ostream& operator<<(ostream& stream, const Record& rec) {
    stream << rec.first_name << ' ' << rec.last_name << ' ' << rec.date << ' ' << rec.payment;
    return stream;
}

void AddRecordInStatement(const string& path_to_file) {
    ofstream file(path_to_file, ios::app);
    if (!file.is_open()) {
        cerr << "File opening error";
        return;
    }
    Record rec;
    if (!(cin >> rec)) {
        cerr << "Error of input" << endl;
    } else file << rec << endl;
    file.close();
}

void ReadStatementToCout(const string& path_to_file) {
    ifstream file(path_to_file);
    if (!file.is_open()) {
        cerr << "File opening error";
        return;
    }
    Record rec;
    while (!file.eof() && file >> rec) {
        cout << rec << endl;
    }
    file.close();
}

int main() {
    string path_to_file = "statement.txt";
    string command;
    cin >> command;
    if (command == "list" || command == "add") {
        AddRecordInStatement(path_to_file);
    } else if (command == "read") {
        ReadStatementToCout(path_to_file);
    } else cerr << "Unknown command" << endl;
    return 0;
}
