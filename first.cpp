#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

const int DAYS_IN_WEEK = 5;  // Monday to Friday

// Function to create the timetable
std::vector<std::vector<std::string>> createTimetable(std::map<std::string, int> &subjects, int periodsPerDay) {
    std::vector<std::vector<std::string>> timetable(DAYS_IN_WEEK, std::vector<std::string>(periodsPerDay, ""));

    std::vector<std::pair<std::string, int>> subjectList;
    for (const auto &subject : subjects) {
        subjectList.push_back(subject);
    }

    int day = 0;
    int period = 0;
    while (!subjectList.empty()) {
        for (auto it = subjectList.begin(); it != subjectList.end(); ) {
            timetable[day][period] = it->first;
            if (--it->second == 0) {
                it = subjectList.erase(it);
            } else {
                ++it;
            }
            period = (period + 1) % periodsPerDay;
            if (period == 0) {
                day = (day + 1) % DAYS_IN_WEEK;
            }
        }
    }

    return timetable;
}

// Function to print the timetable
void printTimetable(const std::vector<std::vector<std::string>> &timetable) {
    std::cout << std::setw(10) << "Period";
    for (int i = 1; i <= timetable[0].size(); ++i) {
        std::cout << std::setw(10) << i;
    }
    std::cout << std::endl;

    const std::string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    for (int i = 0; i < DAYS_IN_WEEK; ++i) {
        std::cout << std::setw(10) << days[i];
        for (const auto &subject : timetable[i]) {
            std::cout << std::setw(10) << subject;
        }
        std::cout << std::endl;
    }
}

int main() {
    int numSubjects;
    std::cout << "Enter the number of subjects: ";
    std::cin >> numSubjects;

    std::map<std::string, int> subjects;
    for (int i = 0; i < numSubjects; ++i) {
        std::string subjectName;
        int frequency;
        std::cout << "Enter the name of subject " << i + 1 << ": ";
        std::cin >> subjectName;
        std::cout << "Enter the number of periods per week for " << subjectName << ": ";
        std::cin >> frequency;
        subjects[subjectName] = frequency;
    }

    int periodsPerDay;
    std::cout << "Enter the number of periods per day: ";
    std::cin >> periodsPerDay;

    auto timetable = createTimetable(subjects, periodsPerDay);
    printTimetable(timetable);

    return 0;
}
