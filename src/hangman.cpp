//============================================================================
// Name        : hangman.cpp
// Author      : R. G. Nagel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib> // random number

using namespace std;

class Player {
private:
	string _name;
	int _score;
	int _wins;
	int _times;
public:
	Player(string name) {
		_name = name;
		_score = 0;
		_wins = 0;
		_times = 0;
	};
	void newGame() {

	}
	void askLetter(char letter) {

	}
	void printStats() {

	}
};

class Word {
private:
	string _word;
	string _hint;
	string _visible;
public:
	Word(string word, string hint) {
		_word = word;
		_hint = hint;
		_visible.append('_', word.size());
	}
	bool hasLetter(char letter) {
		bool has = false;
		int i;

		/* using iterator */
		/*for (string::iterator i = _word.begin(); i != _word.end(); i++)
			if (*i == letter) {
				has = true;
				_visible[distance(_word.begin(), i)] = letter;
			}*/

		/*
		 * using find
		 *
		 * return of find: The position of the first character of the first match.
		 * if no matches were found, the function returns string::npos.
		 * ref: http://www.cplusplus.com/reference/string/string/find/
		 */

		i = _word.find(letter);
		while (i != _word.npos) {
			_visible[i] = letter;
			has = true;
		}

		return has;
	}
	int missing() {

		return 0;
	}
	string str() {
		return _word;
	}
	string hint() {
		return _hint;
	}
	string visible() {
		return _visible;
	}
	int size() {
		return _word.size();
	}
	void print() {

	}
	void reset() {

	}
};

/*
 * dictionary object is bound to a *.csv file which each line correspond to a word and its hink:
 * e.g.: file words.csv
 * elephant,a very big animal
 * rafael, a very beautiful name
 */
class Dictionary {
private:
	vector<Word> _words;
public:
	void addWord(Word *word) {
		_words.push_back(*word);
	}
	Dictionary(string filename) {
		ifstream file;

		file.open(filename);
		if (file.is_open()) {
			string line;

			while(getline(file, line)) {
				char i_separator;
				string word, hint;

				i_separator = line.find_first_of(',');
				word = line.substr(0, i_separator - 1);
				hint = line.substr(i_separator + 1, line.size() - 1);

				Word word_obj = Word(word, hint);
				this->addWord(&word_obj);
			}

			file.close();
		}
		else
			cout << "Unable to open file " << filename << '\n';
	}
	Word * selectWord() {
		int r = rand() % _words.size();
		return &_words[r];
	}
};

/*class Hangman {
private:
	uint8_t _wrong_tries;
	Player _player;
	Word _hang_word;
	Dictionary _vocabulary;
public:
	Hangman(Player *player) {
		_player = player;
		_wrong_tries = 0;
	}
	void run() {

	}
	int gameScore() {

		return 0;
	}
	void printStatus() {

	}
};*/



int main() {
	Dictionary dictionary("words.txt");



	return 0;
}

