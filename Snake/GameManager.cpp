#include "GameManager.h"

GameManager::GameManager()
{
	// code here...	
	mode = Menu;
	status = StandBy;
	keyboard = 'x';
	special_keyboard = -1;
}

void GameManager::AIDecision()
{
	// code here...
}

Collision GameManager::checkCollision(const Player player)
{
	// code here...
	return NONE;
}

void GameManager::changeDirection()
{
	// code here...	
	if (turn == Player1)													// snake1
	{
		switch (keyboard)
		{
		case 'w': snake1.setDirection(North); break;
		case 's': snake1.setDirection(West); break;
		case 'a': snake1.setDirection(East); break;
		case 'd': snake1.setDirection(South); break;
		}
	}
	else if (turn == Player2)												// snake2
	{
		switch (special_keyboard)
		{
		case GLUT_KEY_LEFT:  /* code here */ break;
		case GLUT_KEY_RIGHT: /* code here */ break;
		case GLUT_KEY_UP:    /* code here */ break;
		case GLUT_KEY_DOWN:  /* code here */ break;
		}
	}
}

void GameManager::setupSingle()
{
	snake1 = Snake(1.0,1.0,0,1,0);
	fruit = Fruit(1.0,1.0,1,0,1); 
	ScoreKeeper score;
	Player Player1;
}

void GameManager::setupTwoPlayer()
{
	/*Snake snake1;
	Fruit fruit(1.0, 1.0, 1, 0, 1);
	Snake snake2(-0.2, -0.2, 0, 1, 0);*/

}

void GameManager::setupAI()
{
	//Snake snake1(0.2, 0.2, 0.0, 1, 0);
	//Fruit fruit(1.0, 1.0, 1, 0, 1);
	//Snake snake2(-0.2, -0.2, 0, 1, 0);
}

void GameManager::runSingle()
{
	snake1.draw();
	count++;
	//snake1.grow();
	if (count >= speed)
	{
		//cout << "I'm going in if statement to make move\n";
			snake1.move(snake1.getDirection());

			/*if (woah.isThereCollision(snake1.getHead()))
			{
			snake1.grow();
			}*/
			snake1.isThereCollision(snake1.getHead(), true);
			//std::cout << "Snake is moving\n";

		count = 0;
	}

	if (snake1.isThereCollision(snake1.getHead(), true)) {
		status = GameOver;
	}

}

void GameManager::runTwoPlayer()
{
	if (turn == Player1)													// Player1's turn
	{
		// code here...
	}
	else																	// Player2's turn
	{
		// code here...
	}
}

void GameManager::runAI()
{
	if (turn == Player1)													// Player1's turn
	{
		// code here...
	}
	else																	// AI's turn
	{
		// code here...
	}
}

void GameManager::run()
{
	if (status == GameOver || (status == StandBy && keyboard != ' '))		// Does nothing if the game is over or is on standby (space bar is required to finish)
	{
		resetInput();														// Reset user input
		return;
	}
	if (status == StandBy && keyboard == ' ')								// Start initializing and start the game if first time
		status = InProgress;												// Start the game

	// Run/continue the game accordingly
	switch (mode)
	{
	case SinglePlayerMode: runSingle(); break;								// Single player game
	case TwoPlayerMode: runTwoPlayer(); break;								// Two player game
	case AIMode: runAI(); break;											// AI game
	}

	resetInput();															// Reset user input
}

void GameManager::end()
{
	if (mode == SinglePlayerMode)											// SinglePlayerMode ending
	{
		// code here...
	}
	else if (victory == Player1)											// Player1's victory
	{
		// code here...
	}
	else if (victory == Player2)											// Player2's victory
	{
		// code here...
	}
	else																	// AI's victory
	{
		// code here...
	}
	resetInput();															// Reset user input
}

void GameManager::displayMenu()
{
	// Display menu
	cout << "\t\t***Game menu***\n";
	cout << "Press 1 for Single Player Game\n";
	cout << "Press 2 for Two Player Game\n";
	cout << "Press 3 for Player vs AI Game\n";
	cout << "Press 4 for High Score Display\n";
	cout << "Note: Scoring system only applies to Single Player Game.\n";

	// Apply user response (not terminal)
	
	switch (keyboard)
	{
	case '1': mode = SinglePlayerMode; break;								// Single player mode
	case '2': mode = TwoPlayerMode; break;									// Two player mode
	case '3': mode = AIMode; break;											// AI mode
	case '4': mode = ScoreDisplay; resetInput(); return;					// Display scoreboard
	default: resetInput(); return;											// Reset user input for invalid responses
	}
	switch (mode)
	{
	case SinglePlayerMode: setupSingle(); break;
	case TwoPlayerMode: setupTwoPlayer(); break;
	case AIMode: setupAI(); break;
	}
	resetInput();
}

void GameManager::displayScoreboard()
{
	// Go back to the menu if space bar is pressed (not terminal)
	if (keyboard == ' ')
	{
		mode = Menu;
		return;
	}
	// Get the scores from scorekeeper
	vector<Score> displayMe;
	score.display(displayMe);

	// Display the scoreboard
	cout << "\t\t***Top 10 scores***\n";
	for (int i = 0; i < displayMe.size(); ++i)
		cout << displayMe[i].score << "\t:" << displayMe[i].player_name << endl;
	cout << "Press space bar to return to the menu\n";

	resetInput();
}