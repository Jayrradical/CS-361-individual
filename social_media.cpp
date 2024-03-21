#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct SocialMediaInfo
{
	string site;
	string link;
};

int main()
{
	ifstream file_in;
	ofstream file_out;
	const int MAX_ENTRIES = 256;
	int entry_count = 0;
	SocialMediaInfo* infoList = new SocialMediaInfo[MAX_ENTRIES];


	cout << "awaiting input...\n";
	while (true)
	{
		file_in.open("social_media_io.txt");
		if (!file_in.is_open())
		{
			cout << "Error opening file.\n";
			continue;
		}

		string command;

		if (getline(file_in, command)) {

			if (command == "add")
			{
				cout << "add command received.\n";
				while (true)
				{
					string site;
					string link;
					if (!(file_in >> site) || !(file_in >> link))
					{
						break;
					}
					infoList[entry_count].site = site;
					infoList[entry_count].link = link;
					
					entry_count++;
				}
				
				file_out.open("social_media_io.txt", std::ofstream::out | std::ofstream::trunc); // removes file contents
				file_out.close();

				cout << "recieved following entries: \n";
				for (int i = 0; i < entry_count; i++)
				{
					cout << "site: " << infoList[i].site << " link: " << infoList[i].link << "\n";
				}
				cout << "\n";

				cout << "awaiting input...\n";
			}
			else if (command == "get links")
			{
				cout << "get links command received.\n";
				file_out.open("social_media_io.txt", std::ofstream::out | std::ofstream::trunc); // removes file contents

				for (int i = 0; i < entry_count; i++)
				{
					file_out << infoList[i].link << '\n';
				}

				file_out.close();
				cout << "awaiting input...\n";
			}
			else if (command == "get sites")
			{
				cout << "get sites command received.\n";
				file_out.open("social_media_io.txt", std::ofstream::out | std::ofstream::trunc); // removes file contents

				for (int i = 0; i < entry_count; i++)
				{
					file_out << infoList[i].site << '\n';
				}

				file_out.close();
				cout << "awaiting input...\n";
			}
			else if (command == "get sites and links")
			{
				cout << "get sites and links command received.\n";
				file_out.open("social_media_io.txt", std::ofstream::out | std::ofstream::trunc); // removes file contents

				for (int i = 0; i < entry_count; i++)
				{
					file_out << infoList[i].site << ' ' << infoList[i].link <<  '\n';
				}

				file_out.close();
				cout << "awaiting input...\n";
			}
			else if (command == "end" || command == "exit" || command == "quit")
			{
				cout << "end command received.\n";
				file_out.open("social_media_io.txt", std::ofstream::out | std::ofstream::trunc); // removes file contents
				file_out.close();
				file_in.close();
				break;
			}
			
		}
		file_in.close();
	}

	delete[] infoList;
	
	return 0;
}