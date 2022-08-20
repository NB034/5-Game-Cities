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
		cout << "Введите количество игроков: ";
		cin >> amount;
		cin.ignore();
		for (size_t i = 0; i < amount; i++) {
			system("cls");
			cout << "Введите имя игрока " << i + 1 << ": ";
			getline(cin, name);
			players.push_back(name);
		}
		system("cls");
	}
	void playGame() {
		int player = 0;
		string city;
		while (this->players.size() > 1) {
			cout << "Ход игрока " << players[player] << endl
				<< "Введите название города";
			if (!logic.isUsedCitiesEmpty())
				cout << " на букву \"" << logic.getLastLetter() << "\" или \"Сдаюсь\"";
			cout << ": ";
			getline(cin, city);
			cout << endl;
			city = logic.wordToLowerCase(city);
			if (city == "сдаюсь") {
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
		cout << "Победил игрок " << players[0] << "!" << endl;
	}
};
