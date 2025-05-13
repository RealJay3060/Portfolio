#ifndef SETADT_H
#define SETADT_H

#include <iostream>
#include <set>
#include <string>

using namespace std;

class SetRecord {
public:
    string month;
    string artist;
    string title;
    string label;
    int year;
    int weeks;

    SetRecord(string mon, int yr, string singer, string song, string house, int noWeeks)
        : month(mon), year(yr), artist(singer), title(song),
          label(house), weeks(noWeeks) {}

    string getData() const {
        return month + " | " + to_string(year) + " | " + artist + " | " +
               title + " | " + label + " | " + to_string(weeks) + "\n";
    }

    // Use title as the unique key
    bool operator<(const SetRecord& other) const {
        return title < other.title;
    }
};

class SetADT {
private:
    set<SetRecord> recordSet;

public:
    SetADT() {}

    void insert(string mon, int yr, string singer, string song, string house, int noWeeks) {
        SetRecord newRecord(mon, yr, singer, song, house, noWeeks);
        recordSet.insert(newRecord);
    }

    void remove(string song) {
        for (auto it = recordSet.begin(); it != recordSet.end(); ++it) {
            if (it->title == song) {
                recordSet.erase(it);
                return;
            }
        }
    }

    bool contains(string song) const {
        for (const auto& rec : recordSet) {
            if (rec.title == song)
                return true;
        }
        return false;
    }

    string printSet() const {
        string output;
        for (const auto& rec : recordSet) {
            output += rec.getData();
        }
        return output;
    }

    bool isEmpty() const {
        return recordSet.empty();
    }

    int size() const {
        return recordSet.size();
    }

    const set<SetRecord>& getSet() const { return recordSet; }

};

#endif
