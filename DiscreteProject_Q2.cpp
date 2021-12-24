#include<iostream>
#include<math.h>
#include<windows.h>
const int setSize = 3;
using namespace std;
int main()
{
	string set1[setSize];
	string set2[setSize];
	int counter = 0;
	int relations = 0;
	int symmetricCount = 0;
	int antiSymmetricCount = 0;
	int reflexsiveCount = 0;
	int RefSym = 0;
	int SymAsym = 0;
	string choice;
	system("color 3F");
	    cout << "\n\n\t----------Welcome sir!----------\n\n\nCurrent Program is running for 2 sets having 3 elements or members\n\n";
		cout << "\n\nPlease choose the [functionality] you want to perform\n\n1- To add members of the sets and shows their entire data about relatiosn\n2- Exit\n\n";
		cin >> choice;
		if (choice == "1")
		{
			system("cls");
			for (int i = 0; i < 3; i++)
			{
				cout << "Enter element number " << i + 1 << " for set " << 1 << ": " << endl;
				cin >> set1[i];
			}
			for (int i = 0; i < 3; i++)
			{
				cout << "Enter element number " << i + 1 << " for set " << 2 << ": " << endl;
				cin >> set2[i];
			}
			system("cls");
			cout << "\n\n\n\n\t----------Loading Results----------\t";
			Sleep(1000);
			system("cls");
			cout << "\n\n\n\t----------RESULTS----------\n\n\nTotal Number of relations that can be formed are: ";
			relations = pow(2, (setSize * setSize));
			cout << relations << endl;
			cout << "Total number of reflexsive relations are: ";
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (set1[i] == set2[j])
					{
						counter++;
					}
				}
			}
			if (counter == 3)
			{
				reflexsiveCount = pow(2, (setSize * (setSize - 1)));
				cout << reflexsiveCount << endl;
			}
			else if (counter == 2 || counter == 1 || counter == 0)
			{
				cout << "0" << endl;
			}
			cout << "Total number of symmetric relations: ";
			if (counter == 3)
			{
				symmetricCount = pow(2, (setSize * (setSize + 1)) / 2);
				cout << symmetricCount << endl;
			}
			else if (counter == 2 || counter == 1 || counter == 0)
			{
				cout << "0" << endl;
			}
			cout << "Total number of symmetric and reflexsive relation are: ";
			if (counter == 3)
			{
				RefSym = pow(2, (((3 * 3) - 3) / 2));
				cout << RefSym << endl;
			}
			else if (counter == 2 || counter == 1 || counter == 0)
			{
				cout << "0" << endl;
			}
			int second_counter = 0;
			cout << "Total number of anti-symmetric relation are: ";
			antiSymmetricCount = pow(2, setSize) * pow(3, ((setSize * (setSize - 1)) / 2));
			cout << antiSymmetricCount << endl;
			cout << "The total number of symmetric and anti-symmetric on a set are: ";
			if (counter == 3)
			{
				SymAsym = 2 * 3;
				cout << SymAsym << endl;
			}
			else
			{
				cout << "0" << endl;
			}
		}
		else if (choice == "2")
		{
			return 0;
		}
		else
		{
			cout << "Invalid Input! Please Try Again" << endl;
			Sleep(1000);
			system("cls");
		}
	return 0;
}
