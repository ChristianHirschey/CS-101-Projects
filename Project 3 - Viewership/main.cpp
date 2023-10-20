#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

int main(int argc, char *argv[]) {
    bool printPrompts = true;
    if (argc == 2 && string(argv[1]) == "no") {
        printPrompts = false;
    }

    MediaList *list = new MediaList();

    string cmd, mediaName, regionName;
    int regionViewers;
    while (1) {
        if (printPrompts) cout << "Enter a command or \"help\" to get a command list: ";
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "addMedia") {
            if (printPrompts) cout << "\tEnter media name: ";
            cin >> mediaName;
            if (!list->addMedia(mediaName)) {
                cout << "Error: " << mediaName << " already exists" << endl;
            }
        }
        else if (cmd == "addRegion") {
            if (printPrompts) cout << "\tEnter media name: ";
            cin >> mediaName;
            if (printPrompts) cout << "\tEnter region name: ";
            cin >> regionName;
            if (printPrompts) cout << "\tEnter region viewers: ";
            cin >> regionViewers;
            if (!list->addRegion(mediaName, regionName, regionViewers)) {
                cout << "Error: " << mediaName << " does not exist" << endl;
            }
        }
        else if (cmd == "printMedia") {
            if (printPrompts) cout << "\tEnter media name: ";
            cin >> mediaName;
            if (!list->printMedia(cout, mediaName)) {
                cout << "Error: " << mediaName << " does not exist" << endl;
            }
            cout << endl;
        }
        else if (cmd == "count") {
            cout << "\nThere are " << list->getCount() << " media" << endl;
        }
        else if (cmd == "print") {
            list->print(cout);
            cout << endl;
        }
        else if (cmd == "addMediaOrdered") {
            if (printPrompts) cout << "\tEnter media name: ";
            cin >> mediaName;
            if (!list->addMediaOrdered(mediaName)) {
                cout << "Error: " << mediaName << " already exists" << endl;
            }
        }
        else if (cmd == "addRegionOrdered") {
            if (printPrompts) cout << "\tEnter media name: ";
            cin >> mediaName;
            if (printPrompts) cout << "\tEnter region name: ";
            cin >> regionName;
            if (printPrompts) cout << "\tEnter region viewers: ";
            cin >> regionViewers;
            if (!list->addRegionOrdered(mediaName, regionName, regionViewers)) {
                cout << "Error: " << mediaName << " does not exist" << endl;
            }
        }
        else if (cmd == "removeRegion") {
            if (printPrompts) cout << "\tEnter media name: ";
            cin >> mediaName;
            if (printPrompts) cout << "\tEnter region name: ";
            cin >> regionName;
            if (!list->removeRegion(mediaName, regionName)) {
                cout << "Error: " << mediaName << " or " << regionName << " does not exist" << endl;
            }
        }
        else if (cmd == "removeMedia") {
            if (printPrompts) cout << "\tEnter media name: ";
            cin >> mediaName;
            if (!list->removeMedia(mediaName)) {
                cout << "Error: " << mediaName << " does not exist" << endl;
            }
        }
        else if (cmd == "destroy") {
            delete list;
            list = new MediaList();
        }
        else if (cmd == "copycon" || cmd == "copy=") {
            MediaList *list2;
            if (cmd == "copycon") {
                list2 = new MediaList(*list);
            }
            else {
                list2 = new MediaList();
                *list2 = *list;
            }

            if (printPrompts) cout << "\tAdd media to copied list:" << endl;
            if (printPrompts) cout << "\tEnter media name: ";
            cin >> mediaName;
            if (!list2->addMedia(mediaName))
            {
                cout << "Error: " << mediaName << " already exists" << endl;
            }
            
            if (printPrompts) cout << "\tAdd region to copied list:" << endl;
            if (printPrompts) cout << "\tEnter media name: ";
            cin >> mediaName;
            if (printPrompts) cout << "\tEnter region name: ";
            cin >> regionName;
            if (printPrompts) cout << "\tEnter region viewers: ";
            cin >> regionViewers;
            if (!list2->addRegion(mediaName, regionName, regionViewers))
            {
                cout << "Error: " << mediaName << " or " << regionName << "does not exist" << endl;
            }

            cout << "Original list:" << endl;
            list->print(cout);
            cout << endl;

            cout << "Copied list:" << endl;
            list2->print(cout);
            cout << endl;

            delete list2;
        }
        else if (cmd == "help") {
            cout << "Valid commands:" << endl;
            cout << "***** addMedia" << endl;
            cout << "***** addRegion" << endl;
            cout << "***** printMedia" << endl;
            cout << "***** count" << endl;
            cout << "***** print" << endl;
            cout << "***** addMediaOrdered" << endl;
            cout << "***** addRegionOrdered" << endl;
            cout << "***** removeMedia" << endl;
            cout << "***** removeRegion" << endl;
            cout << "***** destroy" << endl;
            cout << "***** copycon" << endl;
            cout << "***** copy=" << endl;
            cout << "***** help" << endl;
            cout << "***** quit" << endl;
        }
        else {
            cout << "Invalid command specified - " << cmd << endl;
        }
        if (printPrompts) cout << endl;
    }
    return 0;
}
