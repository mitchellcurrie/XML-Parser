#include <iostream>
#include <fstream>
using namespace std;

void CreateXMLFile();
void CreateCSVFile();



int main()
{
	cout << "XML Parser" << endl;

	CreateXMLFile();
	CreateCSVFile();


	int i = 0;
	cin >> i;
}

/*

	Game					Year		Genre					Platform		Developer
	Uncharted 2				2009		Action-Adventure		PS3				Naughty Dog
	Red Dead Redemption		2010		Action-Adventure		PS3				Rockstar San Diego
	Dirt 3					2011		Racing					PS3				Codemasters
	GTA V					2013		Action-Adventure		PS3				Rockstar North
	COD Advanced Warfare	2014		FPS						XBOX One		Sledgehammer Games

*/

void CreateXMLFile()
{
	ofstream xmlFile;
	xmlFile.open("XML File.xml");
	xmlFile << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n\n";

	// Input favourite game information
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
		xmlFile << "<developer> Rockstar North</developer>\n";
	xmlFile << "</game>\n\n";

	xmlFile << "<game>\n";
		xmlFile << "<title> COD Advance Warfare </title>\n";
		xmlFile << "<year> 2014 </year>\n";
		xmlFile << "<genre> FPS </genre>\n";
		xmlFile << "<platform> XBOX One </platform>\n";
		xmlFile << "<developer> Sledgehammer Games </developer>\n";
	xmlFile << "</game>\n\n";

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