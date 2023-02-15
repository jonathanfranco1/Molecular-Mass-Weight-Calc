#include<iostream>
#include<map>
#include<string>
using namespace std;
void incrMass(int multiplier, string elementName, string elementN, double & mass);
//Increments the mass using the pareneters

int main(int argc, char *argv[]) {
	if (argc != 2) {
		//cout << "Usage error: please use one command line argument.\n";
		return 1;
	}
	string molecule = argv[1];
	string elementName = "";
	string elementN = "";
	int multiplier = 1;
	double mass = 0;
	for (int i = 0; i < molecule.length(); i++) {
		//cout << "Parsing symbol " << molecule[i] << endl;
		if (molecule[i] == '[') {
			if (elementName != "") {
				incrMass(multiplier, elementName, elementN, mass);
				elementName = "";
				elementN = "";
			}
			//cout << "\tFound a [, starting loop to find matching ]\n";
			int parenN = 1;
			for (int j = i+1; j < molecule.length(); j++) {
				//cout << "\t\tlooking at " << molecule[j] << endl;
				if (molecule[j] == '[') {
					parenN++;
				} else if (molecule[j] == ']') {
					parenN--;
				}
				if (parenN == 0) {
					//cout << "\t\t found matching ], looping to get multiplier\n";
					string m = "";
					int k = j+1;
					while (isdigit(molecule[k]) && k < molecule.length()) {
						//cout << "\t\t\tLooking at " << molecule[k] << endl;
						m += molecule[k];
						k++;
					}
					if (m != "") {
						//cout << "\t\t\tScaling multiplier by " << stoi(m) << endl;
						multiplier *= stoi(m);
					}
					break;
				}
			}
		} else if (molecule[i] == ']') {
			if (elementName != "") {
				incrMass(multiplier, elementName, elementN, mass);
				elementName = "";
				elementN = "";
			}
			//cout << "\tFound ], looking for following number\n";
			string m = "";
			int j = i+1;
			while (isdigit(molecule[j]) && j < molecule.length()) {
				//cout << "\t\tLooking at " << molecule[j] << endl;
				m += molecule[j];
				j++;
			}
			//cout << "\tSkipping ahead " << j - i - 1 << " numbers\n";
			i += j - i - 1;
			if (m != "") {
				//cout << "\tDecreasing multiplier by " << stoi(m) << endl;
				multiplier /= stoi(m);
			}
		} else if (isupper(molecule[i])) {
			if (elementName != "") {
				incrMass(multiplier, elementName, elementN, mass);
				elementName = molecule[i];
				elementN = "";
			} else {
				elementName = molecule[i];
				//cout << "Found the first character of the element name: " << elementName << endl;
			}
		} else if (islower(molecule[i])) {
			elementName += molecule[i];
			//cout << "Added a lowercase letter to the element name: " << elementName << endl;
		} else if (isdigit(molecule[i])) {
			if (elementName.length() == 0) {
				//cout << "There needs to be something for a number to follow\n";
				return 1;
			}
			elementN += molecule[i];
			//cout << "Set the element number of the element " << elementName << " to " << elementN << endl;
		}
	}
	if (elementName != "") {
		incrMass(multiplier, elementName, elementN, mass);
	}
	cout << "Molar Mass: " << mass << endl;
	return 0;
}
void incrMass(int multiplier, string elementName, string elementN, double & mass) {
	map<string, double> massMap;
	massMap["H"] = 1.008;
	massMap["He"] = 4.00;
	massMap["Li"] = 6.94;
	massMap["Be"] = 9.01;
	massMap["B"] = 10.81;
	massMap["C"] = 12.01;
	massMap["N"] = 14.01;
	massMap["O"] = 16.00;
	massMap["F"] = 19.00;
	massMap["Ne"] = 20.18;
	massMap["Na"] = 22.99;
	massMap["Na"] = 22.99;
	massMap["Mg"] = 24.31;
	massMap["Al"] = 26.98;
	massMap["Si"] = 28.09;
	massMap["P"] = 30.97;
	massMap["S"] = 32.06;
	massMap["Cl"] = 35.45;
	massMap["Ar"] = 39.95;
	massMap["K"] = 39.10;
	massMap["Ca"] = 40.08;
	massMap["Sc"] = 44.96;
	massMap["Ti"] = 47.87;
	massMap["V"] = 50.94;
	massMap["Cr"] = 52.00;
	massMap["Mn"] = 54.94;
	massMap["Fe"] = 55.85;
	massMap["Co"] = 58.93;
	massMap["Ni"] = 58.69;
	massMap["Cu"] = 63.55;
	massMap["Zn"] = 65.38;
	massMap["Ga"] = 69.72;
	massMap["Ge"] = 72.63;
	massMap["As"] = 74.92;
	massMap["Se"] = 78.97;
	massMap["Br"] = 79.90;
	massMap["Kr"] = 83.80;
	massMap["Uut"] = 284;
	if (elementN != "") {
		multiplier *= stoi(elementN);
	}
	//cout << "\tIncreasing mass by " << multiplier << " " << elementName << endl;
	mass += massMap.at(elementName) * multiplier;
}
