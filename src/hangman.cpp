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
#include <ctime> // seed input for rand

#define false 0
#define true 1

#define DEBUG 1


using namespace std;

class Player {
private:
	string _name;
	int _score;
	int _wins;
	int _times;
public:
	Player() {
		cout << "Your name: ";
		cin >> _name;
		_score = 0;
		_wins = 0;
		_times = 0;
	};
	void newGame() {
		_score = 0;
		_wins = 0;
		_times = 0;
	}
	char askLetter() {
		char letter;

		cout << "\nInform a letter: ";
		cin >> letter;
		return (char)letter;
	}
	bool askPlayAgain() {
		bool ret = true;
		string reply;
		string yes("yYsSYESyesYesSIMsimSim");

		cout << "Play Again? ";
		cin >> reply;

		if (yes.find(reply) == string::npos) // did not match
			ret = false;

		return ret;
	}
	void printStats() {
		cout << "\nName: " << _name << endl;
		cout <<	"Score: " << _score << endl;
		cout << "Wins: " << _wins << endl;
		cout <<	"Times: " << _times << endl;
	}
	void hitLetter() {
		_score++;
	}
	void missedLetter() {
		_score--;
	}
	void win() {
		_wins++;
	}
};

class Word {
private:
	string _word;
	string _hint;
	string _visible;
public:
	bool set(string word, string hint) {
		_word = word;
		_hint = hint;
		_visible.append(word.size(), '_');

		return true;
	}
	bool hasLetter(char letter) {
		bool has = false;

		/* using iterator */
		for (string::iterator i = _word.begin(); i != _word.end(); i++)
			if (*i == letter) {
				has = true;
				_visible[distance(_word.begin(), i)] = letter;
			}

		/*
		 * using find
		 *
		 * return of find: The position of the first character of the first match.
		 * if no matches were found, the function returns string::npos.
		 * ref: http://www.cplusplus.com/reference/string/string/find/
		 */
		/*uint i = _word.find(letter);
		while (i != string::npos) {
			_visible[i] = letter;
			has = true;
		}*/

		return has;
	}
	int missing() {
		bool missing = true;
		string::size_type i;

		i = _visible.find('_');

		if (i == string::npos) // reach end of string
			missing = false;

		return missing;
	}
	string word() {
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
	void reset() {
		string tmp(_word.size(), '_');
		_visible = tmp;
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
	std::vector<Word> _words;
public:
	void addWord(Word word) {
		_words.push_back(word);
	}
	bool set(string filename) {
		ifstream file;
		bool ret = false;

		file.open(filename);
		if (file.is_open()) {
			string line;

			while(getline(file, line)) {
				char i_separator;
				string word, hint;
				Word word_obj;

				i_separator = line.find_first_of(',');
				word = line.substr(0, i_separator);
				hint = line.substr(i_separator + 1, line.size() - 1);

				word_obj.set(word, hint);
				this->addWord(word_obj);
			}

			file.close();
			ret = true;
		}
		else {
			cout << "Unable to open file " << filename << '\n';
			ret = false;
		}

#ifdef DEBUG
	this->printWords();
#endif

	return ret;
	}
	Word selectWord() {
		static bool seeded = false;

		/* we should invoke seed only once */
		if (!seeded) {
			srand(time(NULL));
			seeded = true;
		}

		int r = rand() % _words.size();
		return _words[r];
	}
	void printWords() {
		std::vector<Word>::iterator i;
		for (i = _words.begin(); i != _words.end(); i++) {
			cout << i->word() << ", " << i->hint() << "\n";
		}
	}
};

class Hangman {
private:
	uint8_t _wrong_tries;
	Player _player;
	Word _hang_word;
	Dictionary _vocabulary;
	const uint _LIVES = 6;

	bool playWord() {

		do {
			char letter;

			cout << "\nWord: " << _hang_word.visible() << "\n";

			letter = _player.askLetter();

			if (_hang_word.hasLetter(letter)) {
				cout << "Gotcha.\n";
				_player.hitLetter();
			}
			else {
				cout << "Missed.\n";
				_player.missedLetter();
				_wrong_tries++;
			}

			if (_wrong_tries >= _LIVES)
				return false;

		} while (_hang_word.missing());

		return true;
	}
public:
	Hangman() {
		_wrong_tries = 0;
		_vocabulary.set("words.txt"); /* TODO open file in parent directory */
		//_hang_word = _vocabulary.selectWord();
	}

	void run() {
		bool hit_word;

		cout << "\n****** Hangman Game ******";

		while (true) {

			_hang_word = _vocabulary.selectWord();
			cout << "\nNew word. Word's Hint:" << _hang_word.hint() << "\n";
			hit_word = playWord();
			cout << "\nThe Word Is: " << _hang_word._word() << endl;

			if (hit_word) {
				_player.win();
				_player.printStats();
			}
			else if (!_player.askPlayAgain()) {
				break;
			}
			else {
				break;
			}
		}

		cout << "\n\nEnd game. Thank you!!!\n" << endl;

	}

	int gameScore() {

		return 0;
	}

	void printStatus() {

	}
};

int main() {
	Hangman game = Hangman();
	game.run();

	return 0;
}

