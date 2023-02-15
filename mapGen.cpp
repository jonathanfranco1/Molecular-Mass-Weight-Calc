#include<iostream>
using namespace std;
int main() {
    string message = "";
    string element;
    string mass;
    while (true) {
        cout << "Enter the name of the element (or done to finish): ";
        cin >> element;
        if (element == "done") {
            break;
        }
        cout << "Enter the mass of " << element << ": ";
        cin >> mass;
        message += "massMap[\"" + element + "\"] = " + mass + ";\n";
    }
    cout << message;
    return 0;
}
