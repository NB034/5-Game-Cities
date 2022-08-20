#pragma once
#include <iostream>
#include <Windows.h>
#include "Logic.h"

class CitiesGame {
	CitiesLogic logic;
	vector<string> players;
public:
	CitiesGame() {
		int amount;
		string name;
		cout << "������� ���������� �������: ";
		cin >> amount;
		cin.ignore();
		for (size_t i = 0; i < amount; i++) {
			system("cls");
			cout << "������� ��� ������ " << i + 1 << ": ";
			getline(cin, name);
			players.push_back(name);
		}
		system("cls");
	}
	void playGame() {
		int player = 0;
		string city;
		while (this->players.size() > 1) {
			cout << "��� ������ " << players[player] << endl
				<< "������� �������� ������";
			if (!logic.isUsedCitiesEmpty())
				cout << " �� ����� \"" << logic.getLastLetter() << "\" ��� \"������\"";
			cout << ": ";
			getline(cin, city);
			cout << endl;
			city = logic.wordToLowerCase(city);
			if (city == "������") {
				players.erase(players.begin() + player);
				if (player == players.size())
					player = 0;
				continue;
			}
			try {
				logic.checkCity(city);
				player++;
				if (player == players.size())
					player = 0;
			}
			catch (exception& e) {
				cout << e.what() << endl << endl;
			}
		}
		cout << "������� ����� " << players[0] << "!" << endl;
	}
};
