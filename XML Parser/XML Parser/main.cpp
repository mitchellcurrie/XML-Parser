#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void CreateXMLFile();
void CreateCSVFile();
void ConvertFromXMLtoCSV();
void ConvertFromCSVtoXML();
bool IsTitleAdded(vector<string> _vector, string _strToCheck);
void AddCSVRow(ofstream& _file, vector<string> _vector);
void AddXMLSection(ofstream& _file, vector<string> _titleVector, vector<string> _gameInfoVector, string _child);


int main()
{
	cout << "XML Parser" << endl;

//	CreateXMLFile();
//	CreateCSVFile();

//	ConvertFromXMLtoCSV();
	ConvertFromCSVtoXML();

	int i = 0;
	cin >> i;
}

void ConvertFromCSVtoXML()
{
	string filename;
	cout << "Enter the filename of the CSV file to convert to XML: ";
	getline(cin, filename);

	string xmlFilename = filename.substr(0, filename.find_first_of('.')) + ".xml";
	ofstream xmlFile;
	xmlFile.open(xmlFilename);

	ifstream csvFile(filename);
	string line;
	string data;
	string root = "rootNode";
	string child = "child";
	vector <string> titles;
	vector <string> gameInfo;
	bool bTitlesSet = false;
	bool bRowSet = false;

	xmlFile << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n\n";
	xmlFile << "<" << root << ">\n\n";

	if (csvFile.is_open())
	{			
		(getline(csvFile, line));

		while (!bTitlesSet)
		{
			if (line.find(',') != string::npos)
			{
				data = line.substr(0, line.find_first_of(","));
				line.erase(0, line.find_first_of(",") + 1);
				if (line[0] == ' ')
					line.erase(0, 1);
			}	
			else
			{ 
				data = line.substr(0, line.length());
				bTitlesSet = true;
			}

			titles.push_back(data);
		}

		while (getline(csvFile, line))
		{
			while (!bRowSet)
			{
				if (line.find(',') != string::npos)
				{
					data = line.substr(0, line.find_first_of(","));
					line.erase(0, line.find_first_of(",") + 1);
					if (line[0] == ' ')
						line.erase(0, 1);
				}
				else
				{
					data = line.substr(0, line.length());
					bRowSet = true;
				}

				gameInfo.push_back(data);
			}

			AddXMLSection(xmlFile, titles, gameInfo, child);
			gameInfo.clear();
			bRowSet = false;		
		}

		xmlFile << "</" << root << ">\n\n";
	}
	else
	{
		cout << "Could not open csv file";
	}

}
void ConvertFromXMLtoCSV()
{
	string filename;
	cout << "Enter the filename of the XML file to convert to CSV: ";
	getline(cin, filename);

	string csvFilename = filename.substr(0, filename.find_first_of('.')) + ".csv";
	ofstream csvFile;
	csvFile.open(csvFilename);

	ifstream xmlFile(filename);
	string line;
	string firstTitle;
	string groupTitle;
	vector <string> rowText;

	bool bPassedFirstTitle = false;
	bool bGroupTitleSet = false;

	if (xmlFile.is_open())
	{
		// Get XML titles
		while (getline(xmlFile, line))
		{	
			// Set the group title - ignores blank lines and set up lines with "?" at the second to last position
			if ((line != "") && !bGroupTitleSet && (line.at(line.length()-2) != '?'))
			{
				if (bPassedFirstTitle)
				{
					groupTitle = line.substr(1, line.length() - 2);
					bGroupTitleSet = true;
				}
				else
				{
					firstTitle = line.substr(1, line.length() - 2);
					bPassedFirstTitle = true;
				}			
			}		
			else if (bGroupTitleSet)
			{
				// Ignore blank lines, set up lines (as above), and lines with the group title and first title found above
				if ((line != "") && (line.at(line.length() - 2) != '?') && (line.find(groupTitle) == string::npos) &&
					(line.find(firstTitle) == string::npos))
				{
					//string title = line.substr(1, line.find_first_of('>') - 1);

					string title = line.substr((line.find_first_of('<') + 1), (line.size() - 1));
					title = title.substr(0, title.find_first_of('>'));

					if (!IsTitleAdded(rowText, title))
						rowText.push_back(title);
				}
			}
		}

		// Write xml titles to first row of csv file
		AddCSVRow(csvFile, rowText);

		// Move back to the start of the file and clear row text vector
		xmlFile.clear();
		xmlFile.seekg(0, ios::beg);
		rowText.clear();

		int iTitleCounter = 0;

		// Populate other lines
		while (getline(xmlFile, line))
		{
			if ((line.find(groupTitle) != string::npos) && (line.at(line.length() - 2) != '?'))
				iTitleCounter++;

			if (iTitleCounter == 2)
			{
				AddCSVRow(csvFile, rowText);
				rowText.clear();
				iTitleCounter = 0;
			}
			
			if ((line != "") && (line.at(line.length() - 2) != '?') && (line.find(groupTitle) == string::npos) &&
				(line.find(firstTitle) == string::npos))
			{
				string data = line.substr((line.find_first_of('>') + 2), (line.size() - 1));
				data = data.substr(0, data.find_last_of(' '));
				rowText.push_back(data);
			}
		}
	
		// Close files
		xmlFile.close();
		csvFile.close();
	}
	else
	{
		cout << "Could not open xml file";
	}
}
void CreateXMLFile()
{
	ofstream xmlFile;
	xmlFile.open("test.xml");
	xmlFile << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n\n";

	// Input favourite game information
	xmlFile << "<favouriteGames>\n\n";
		xmlFile << "<game>\n";
			xmlFile << "<title> Uncharted 2 </title>\n";
			xmlFile << "<year> 2009 </year>\n";
			xmlFile << "<genre> Action-Adventure </genre>\n";
			xmlFile << "<platform> PS3 </platform>\n";
			xmlFile << "<developer> Naughty Dog </developer>\n";
		xmlFile << "</game>\n\n";

		xmlFile << "<game>\n";
			xmlFile << "<title> Red Dead Redemption </title>\n";
			xmlFile << "<year> 2010 </year>\n";
			xmlFile << "<genre> Action-Adventure </genre>\n";
			xmlFile << "<platform> PS3 </platform>\n";
			xmlFile << "<developer> Rockstar San Diego </developer>\n";
		xmlFile << "</game>\n\n";

		xmlFile << "<game>\n";
			xmlFile << "<title> Dirt 3 </title>\n";
			xmlFile << "<year> 2011 </year>\n";
			xmlFile << "<genre> Racing </genre>\n";
			xmlFile << "<platform> PS3 </platform>\n";
			xmlFile << "<developer> Codemasters </developer>\n";
		xmlFile << "</game>\n\n";

		xmlFile << "<game>\n";
			xmlFile << "<title> GTA V </title>\n";
			xmlFile << "<year> 2013 </year>\n";
			xmlFile << "<genre> Action-Adventure </genre>\n";
			xmlFile << "<platform> PS3 </platform>\n";
			xmlFile << "<developer> Rockstar North </developer>\n";
		xmlFile << "</game>\n\n";

		xmlFile << "<game>\n";
			xmlFile << "<title> COD Advance Warfare </title>\n";
			xmlFile << "<year> 2014 </year>\n";
			xmlFile << "<genre> FPS </genre>\n";
			xmlFile << "<platform> Xbox One </platform>\n";
			xmlFile << "<developer> Sledgehammer Games </developer>\n";
		xmlFile << "</game>\n\n";
	xmlFile << "</favouriteGames>\n";

	xmlFile.close();
}
void CreateCSVFile()
{
	ofstream csvFile;
	csvFile.open("CSV File.csv");
	csvFile << "Game, Year, Genre, Platform, Developer\n";
	csvFile << "Uncharted 2, 2009, Action-Adventure, PS3, Naughty Dog\n";
	csvFile << "Red Dead Redemption, 2010, Action-Adventure, PS3, Rockstar San Diego\n";
	csvFile << "Dirt 3, 2011, Racing, PS3, Codemasters\n";
	csvFile << "GTA V, 2013, Action-Adventure, PS3, Rockstar North\n";
	csvFile << "COD Advanced Warfare, 2014, FPS, XBOX One, Sledgehammer Games\n";
	csvFile.close();
}
bool IsTitleAdded(vector<string> _vector, string _strToCheck)
{
	for (auto itr = _vector.begin(); itr != _vector.end(); itr++)
	{
		if ((*itr) == _strToCheck)
			return true;
	}

	return false;
}
void AddCSVRow(ofstream& _file, vector<string> _vector)
{
	for (auto itr = _vector.begin(); itr != _vector.end(); itr++)
	{
		if (itr == _vector.end() - 1)
			_file << (*itr);
		else
			_file << (*itr) << ", ";
	}

	_file << "\n";
}
void AddXMLSection(ofstream& _file, vector<string> _titleVector, vector<string> _gameInfoVector, string _child)
{
	size_t NumberOfItems = _titleVector.size();
	
	_file << "\t<" << _child << ">\n";
	
	for (size_t x = 0; x < NumberOfItems; x++)
	{
		_file << "\t\t<" << _titleVector[x] << "> " << _gameInfoVector[x] << " </" << _titleVector[x] << ">\n";
	}

	_file << "\t</" << _child << ">\n\n";
}

/*

Title					Year		Genre					Platform		Developer
Uncharted 2				2009		Action-Adventure		PS3				Naughty Dog
Red Dead Redemption		2010		Action-Adventure		PS3				Rockstar San Diego
Dirt 3					2011		Racing					PS3				Codemasters
GTA V					2013		Action-Adventure		PS3				Rockstar North
COD Advanced Warfare	2014		FPS						XBOX One		Sledgehammer Games

*/