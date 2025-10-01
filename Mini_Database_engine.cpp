#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Record {
    map<string, string> fields;
};

vector<Record> database;
string filename = "data.txt";

// ----------------- Parsing -----------------
Record parseRecord(string input) {
    Record r;
    stringstream ss(input);
    string pair;
    while (ss >> pair) {
        size_t pos = pair.find('=');
        if (pos != string::npos) {
            string key = pair.substr(0, pos);
            string value = pair.substr(pos+1);
            r.fields[key] = value;
        }
    }
    return r;
}

// ----------------- Insert -----------------
void insertRecord(string input) {
    Record r = parseRecord(input);
    database.push_back(r);
    cout << "✅ Record inserted!\n";
}

// ----------------- Select -----------------
void selectRecords(string condition = "") {
    if (database.empty()) {
        cout << "⚠️ No records found.\n";
        return;
    }

    string condKey, condValue;
    if (!condition.empty()) {
        size_t pos = condition.find('=');
        if (pos != string::npos) {
            condKey = condition.substr(0, pos);
            condValue = condition.substr(pos+1);
        }
    }

    for (auto &rec : database) {
        if (!condKey.empty()) {
            if (rec.fields.count(condKey) == 0 || rec.fields[condKey] != condValue)
                continue; // skip if condition not met
        }
        for (auto &p : rec.fields) {
            cout << p.first << "=" << p.second << " ";
        }
        cout << "\n";
    }
}

// ----------------- Delete -----------------
void deleteRecords(string condition) {
    string condKey, condValue;
    size_t pos = condition.find('=');
    if (pos != string::npos) {
        condKey = condition.substr(0, pos);
        condValue = condition.substr(pos+1);
    }

    int before = database.size();
    database.erase(remove_if(database.begin(), database.end(),
        [&](Record &rec) {
            return rec.fields.count(condKey) && rec.fields[condKey] == condValue;
        }), database.end());

    int after = database.size();
    cout << "🗑️ Deleted " << (before - after) << " record(s).\n";
}

// ----------------- Update -----------------
void updateRecords(string setPart, string condition) {
    // Parse SET part
    Record newValues = parseRecord(setPart);

    // Parse condition
    string condKey, condValue;
    size_t pos = condition.find('=');
    if (pos != string::npos) {
        condKey = condition.substr(0, pos);
        condValue = condition.substr(pos+1);
    }

    int count = 0;
    for (auto &rec : database) {
        if (rec.fields.count(condKey) && rec.fields[condKey] == condValue) {
            for (auto &p : newValues.fields) {
                rec.fields[p.first] = p.second;
            }
            count++;
        }
    }
    cout << "✏️ Updated " << count << " record(s).\n";
}

// ----------------- File Handling -----------------
void saveToFile() {
    ofstream file(filename);
    for (auto &rec : database) {
        bool first = true;
        for (auto &p : rec.fields) {
            if (!first) file << ",";
            file << p.first << "=" << p.second;
            first = false;
        }
        file << "\n";
    }
    file.close();
    cout << "💾 Database saved to " << filename << "\n";
}

void loadFromFile() {
    ifstream file(filename);
    if (!file.is_open()) return;

    database.clear();
    string line;
    while (getline(file, line)) {
        Record r;
        stringstream ss(line);
        string pair;
        while (getline(ss, pair, ',')) {
            size_t pos = pair.find('=');
            if (pos != string::npos) {
                string key = pair.substr(0, pos);
                string value = pair.substr(pos+1);
                r.fields[key] = value;
            }
        }
        database.push_back(r);
    }
    file.close();
    cout << "📂 Database loaded from " << filename << "\n";
}

// ----------------- Main -----------------
int main() {
    loadFromFile();
    string command;

    cout << "🚀 MiniDB started. Commands:\n";
    cout << "INSERT key=value key=value\n";
    cout << "SELECT [condition]\n";
    cout << "DELETE key=value\n";
    cout << "UPDATE key=value WHERE key=value\n";
    cout << "EXIT (saves and quits)\n\n";

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command.find("INSERT") == 0) {
            insertRecord(command.substr(7));

        } else if (command.find("SELECT") == 0) {
            if (command.size() > 6)
                selectRecords(command.substr(7));
            else
                selectRecords();

        } else if (command.find("DELETE") == 0) {
            deleteRecords(command.substr(7));

        } else if (command.find("UPDATE") == 0) {
            size_t pos = command.find("WHERE");
            if (pos != string::npos) {
                string setPart = command.substr(7, pos - 8);
                string condition = command.substr(pos + 6);
                updateRecords(setPart, condition);
            } else {
                cout << "⚠️ Syntax: UPDATE key=value WHERE key=value\n";
            }

        } else if (command == "EXIT") {
            saveToFile();
            cout << "👋 Exiting MiniDB.\n";
            break;

        } else {
            cout << "❓ Unknown command!\n";
        }
    }

    return 0;
}
