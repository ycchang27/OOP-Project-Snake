/*
	Author: Yun Chul Chang
	Purpose: Represent a score manager that stores top 10 scores
*/

#ifndef _SCOREKEEPER_H
#define _SCOREKEEPER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Define Score class
class Score
{
public:
	Score() {}
	Score(int score, string player_name) : score(score), player_name(player_name) {}
	~Score() {}
	int score;
	string player_name;
	bool operator<(const Score& checkMe) const 
	{
		return score < checkMe.score;
	}
};

typedef vector<Score> ScoreList;

// Define ScoreKeeper class
class ScoreKeeper
{
private:
	// Private instance variables:
	ifstream file_reader;					// Used to import scores from the file
	ofstream file_writer;					// Used to save the scores into the file
	unsigned int current_score;				// Current score of the game
	unsigned int lowest_score;				// Keep track of lowest score
	string player_name;						// Current player name
	ScoreList score_list;

private:
	// Private method:
	
	// Insert into the vector
	// Maintains the sorted state
	void insert(Score insertMe)
	{
		// Find a place to insert
		int index = 0;
		for (auto it = score_list.begin(); it != score_list.end(); ++it)
		{
			if (*it < insertMe)
				break;
			++index;
		}

		// Insert into vector
		if (index == score_list.size())
			score_list.push_back(insertMe);
		else
			score_list.insert(score_list.begin() + index, insertMe);
	}
	
public:
	// Constructors:
	
	// Import the scores from the file to a vector
	// The scores in the file are sorted
	ScoreKeeper()
	{
		current_score = 0;					// Set current score to 0
		
	}
	ScoreKeeper(GameDifficulty difficulty)
	{
		current_score = 0;					// Set current score to 0
		// reset vector
		score_list.clear();
		// Assumes that d is already initialized
		switch (difficulty)
		{
		case Easy: file_reader.open("../scoreE.txt"); break;			// Attempt opening the file
		case Intermediate: file_reader.open("../scoreI.txt"); break;	// Attempt opening the file
		case Hard: file_reader.open("../scoreH.txt"); break;			// Attempt opening the file
		}
		if (file_reader.is_open())
		{
			string line;
			unsigned int score;
			char* temp;

			// Start reading the file here...
			while (file_reader.good())
			{
				// Get the score (string to char* conversion is needed for atoi)
				getline(file_reader, line, '|');
				temp = new char[line.size() + 1];
				strcpy(temp, line.c_str());
				score = atoi(temp);

				// Get the player name
				getline(file_reader, line, '|');
				score_list.push_back(Score(score, line));
			}
			lowest_score = score;			// Set the lowest score
			file_reader.close();			// Close the file
		}
		else
			cout << "Error: File not found.\n";		// Print error message
	}

	// Public methods:

	// Save the current score if the score is in top 10
	void save(string player_name, GameDifficulty difficulty)
	{
		this->player_name = player_name;	// Set the player_name

		// Attempt updating the file
		// Assumes that d is already initialized
		switch (difficulty)
		{
		case Easy: file_writer.open("../scoreE.txt"); break;			// Attempt opening the file
		case Intermediate: file_writer.open("../scoreI.txt"); break;	// Attempt opening the file
		case Hard: file_writer.open("../scoreH.txt"); break;			// Attempt opening the file
		default: cout << "Error: Difficulty is invalid" << endl;
		}
		if (file_writer.is_open())
		{
			// Update score board
			insert(Score(current_score, player_name));

			// Save the score here...
			int n = score_list.size();
			string insertMe = "";

			// Set up the text to write
			int i = 0;
			insertMe += to_string(score_list[i].score) + "|" + score_list[i].player_name;
			for (i = 1; i < n - 1; ++i)
				insertMe += "|" + to_string(score_list[i].score) + "|" + score_list[i].player_name;
			if(n != 11)	
				insertMe += "|" + to_string(score_list[i].score) + "|" + score_list[i].player_name;

			// Write into file then close
			file_writer << insertMe;
			file_writer.close();
		}
		else
			cout << "Error: File not found.\n";		// Print error message
	}

	// Fill the vector with vector's Score
	void display(vector<Score> &fillMe, GameMode difficulty)
	{
		// reset vector
		score_list.clear();
		// Assumes that d is already initialized
		switch (difficulty)
		{
		case ScoreDisplayEasy: file_reader.open("../scoreE.txt"); break;			// Attempt opening the file
		case ScoreDisplayInt: file_reader.open("../scoreI.txt"); break;	// Attempt opening the file
		case ScoreDisplayHard: file_reader.open("../scoreH.txt"); break;			// Attempt opening the file
		}
		if (file_reader.is_open())
		{
			string line;
			unsigned int score;
			char* temp;

			// Start reading the file here...
			while (file_reader.good())
			{
				// Get the score (string to char* conversion is needed for atoi)
				getline(file_reader, line, '|');
				temp = new char[line.size() + 1];
				strcpy(temp, line.c_str());
				score = atoi(temp);

				// Get the player name
				getline(file_reader, line, '|');
				score_list.push_back(Score(score, line));
			}
			lowest_score = score;			// Set the lowest score
			file_reader.close();			// Close the file
		}
		else
			cout << "Error: File not found.\n";		// Print error message
		fillMe = vector<Score>(score_list);
	}

	// Check if the current score belongs to top 10
	bool isTop10()
	{
		return !(score_list.size() == 10 && current_score <= lowest_score);
	}

	// Setter/Getter:
	// Increase the current score by 10 points
	void increaseScore()
	{
		current_score += 10;
	}

	void resetScore()							// Reset score
	{
		current_score = 0;
	}

	unsigned int getCurrentScore()				// Get current score
	{
		return current_score;
	}
};

#endif // _SCOREKEEPER_H