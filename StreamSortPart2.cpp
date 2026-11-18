#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct MediaItem {
    string title;
    int runtime; // whole minutes
};

int readMenuChoice() {
    string input;
    getline(cin, input);

    istringstream parser(input);
    int choice;
    char extra;

    if (!(parser >> choice) || (parser >> extra)) {
        throw invalid_argument("Enter one whole number from 1 to 6.");
    }

    if (choice < 1 || choice > 6) {
        throw out_of_range("Menu choice must be from 1 to 6.");
    }

    return choice;
}

int readRuntimeMinutes() {
    string input;
    getline(cin, input);

    istringstream parser(input);
    int minutes;
    char extra;

    if (!(parser >> minutes) || (parser >> extra)) {
        throw invalid_argument("Runtime must be a whole number of minutes.");
    }

    if (minutes <= 0) {
        throw out_of_range("Runtime must be greater than 0 minutes.");
    }

    return minutes;
}

void addTitle(vector<MediaItem>& catalog) {
    cout << "Enter a title: ";
    string title;
    getline(cin, title);

    if (title.find_first_not_of(" \t\r\n") == string::npos) {
        throw invalid_argument("A title cannot be blank.");
    }

    cout << "Enter runtime (in whole minutes): ";
    int runtime = readRuntimeMinutes();

    catalog.push_back({title, runtime});
    cout << "Added: " << title << " (" << runtime << " minutes)\n";
}

void displayQueue(const vector<MediaItem>& catalog) {
    if (catalog.empty()) {
        cout << "Your queue is empty.\n";
        return;
    }

    cout << "Your queue:\n";
    for (size_t i = 0; i < catalog.size(); ++i) {
        cout << (i + 1) << ". " << catalog[i].title
             << " (" << catalog[i].runtime << " minutes)\n";
    }
}

void playNext(vector<MediaItem>& catalog) {
    if (catalog.empty()) {
        throw runtime_error("The queue is empty. Add a title first.");
    }

    MediaItem nextItem = catalog.front();
    catalog.erase(catalog.begin());
    cout << "Now playing: " << nextItem.title
         << " (" << nextItem.runtime << " minutes)\n";
}

// Step 2: Recursive exact, case-sensitive title search
int findTitleRecursive(const vector<MediaItem>& catalog, const string& title, size_t index) {
    // Base case 1: Reached the end of the vector without finding a match
    if (index >= catalog.size()) {
        return -1;
    }

    // Base case 2: Found an exact case-sensitive match at current index
    if (catalog[index].title == title) {
        return static_cast<int>(index);
    }

    // Recursive step: Check the next index
    return findTitleRecursive(catalog, title, index + 1);
}

// Step 3: Recursive total runtime calculation
long long totalRuntimeRecursive(const vector<MediaItem>& catalog, size_t index) {
    // Base case: No entries left in the vector
    if (index >= catalog.size()) {
        return 0;
    }

    // Recursive step: Current record's runtime + total of remaining records
    return catalog[index].runtime + totalRuntimeRecursive(catalog, index + 1);
}

void handleFindTitle(const vector<MediaItem>& catalog) {
    cout << "Enter exact title to search: ";
    string searchTitle;
    getline(cin, searchTitle);

    int foundIndex = findTitleRecursive(catalog, searchTitle, 0);

    if (foundIndex == -1) {
        cout << "Title not found.\n";
    } else {
        cout << "Found at index " << foundIndex << ": "
             << catalog[foundIndex].title << " ("
             << catalog[foundIndex].runtime << " minutes)\n";
    }
}

void handleTotalRuntime(const vector<MediaItem>& catalog) {
    long long total = totalRuntimeRecursive(catalog, 0);
    cout << "Total runtime: " << total << " minutes\n";
}

int main() {
    vector<MediaItem> catalog;
    bool running = true;

    while (running) {
        cout << "\nStreamSort++: Reliable Queue\n\n"
             << "1. Add a title\n"
             << "2. View queue\n"
             << "3. Play next title\n"
             << "4. Find a title\n"
             << "5. Calculate total runtime\n"
             << "6. Exit\n\n"
             << "Enter your choice: ";

        try {
            int choice = readMenuChoice();

            switch (choice) {
                case 1:
                    addTitle(catalog);
                    break;
                case 2:
                    displayQueue(catalog);
                    break;
                case 3:
                    playNext(catalog);
                    break;
                case 4:
                    handleFindTitle(catalog);
                    break;
                case 5:
                    handleTotalRuntime(catalog);
                    break;
                case 6:
                    running = false;
                    cout << "Exiting StreamSort++. Goodbye!\n";
                    break;
            }
        } catch (const exception& error) {
            cout << "Error: " << error.what() << '\n';
        }
    }

    return 0;
}
