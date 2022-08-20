#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class CitiesLogic {
	vector<string> cities;
	vector<string> usedCities;
	
	bool isCityExist(const string& city) const {
		return binary_search(cities.begin(), cities.end(), city);
	}
	bool isCItyNotUsed(const string& city) const {
		return (find(usedCities.begin(), usedCities.end(), city) == usedCities.end());
	}
	bool isLetterFits(const string& city) const {
		if (usedCities.empty())
			return true;
		return getLastLetter() == city.front();
	}
public:
	CitiesLogic() {
		ifstream file("Cities DB.csv");
		string buf;
		while (!file.eof()) {
			getline(file, buf);
			if (buf.length() > 0) {
				buf = buf.substr(buf.rfind(';') + 2);
				buf.pop_back();
				this->cities.push_back(wordToLowerCase(buf));
			}
		}
		file.close();
		sort(cities.begin(), cities.end());
	}
	void checkCity(string& city) {
		if (!isCityExist(city)) 
			throw exception("Такого города не существует!");
		if (!isCItyNotUsed(city)) 
			throw exception("Такой город уже называли!");
		if (!isLetterFits(city))
			throw exception("Город, начинающийся с такой буквы, не подходит!.");
		this->usedCities.push_back(city);
	}
	char getLastLetter() const {
		if (usedCities.empty()) 
			return ' ';
		char letter = usedCities.back().back();
		int i = 1;
		while (string("ыьъёй").find(letter) != string::npos) {
			letter = usedCities.back()[usedCities.back().length() - 1 - i];
			i++;
		}
		return letter;
	}
	const string& wordToLowerCase(string& str) {
		string upperCase = "ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮЁ";
		string lowerCase = "йцукенгшщзхъфывапролджэячсмитьбюё";
		for (size_t i = 0; i < str.length(); i++)
			if (upperCase.find(str[i]) != string::npos)
				str[i] = lowerCase[upperCase.find(str[i])];
		return str;
	}
	bool isUsedCitiesEmpty() const {
		return usedCities.empty();
	}
};
