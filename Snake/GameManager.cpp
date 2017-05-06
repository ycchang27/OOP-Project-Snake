#include "GameManager.h"
#include <iomanip>
#include <random>

GameManager::GameManager()
{
	// code here...	
	mode = Menu;
	status = StandBy;
	keyboard = 'x';
	special_keyboard = -1;
	t = clock();
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
		case 'a': snake1.setDirection(West); break;
		case 'd': snake1.setDirection(East); break;
		case 's': snake1.setDirection(South); break;
		}
	}
	else if (turn == Player2)												// snake2
	{
		switch (special_keyboard)
		{
		case GLUT_KEY_LEFT: snake2.setDirection(West); break;
		case GLUT_KEY_RIGHT:snake2.setDirection(East); break;
		case GLUT_KEY_UP: snake2.setDirection(North); break;
		case GLUT_KEY_DOWN: snake2.setDirection(South); break;
		}
	}
}

void GameManager::setupSingle()
{
	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);
	snake1 = Snake(0,0,0,1,0);
	fruit = Fruit(fx,fy,1,0,1); 
	ScoreKeeper score;
	Player Player1;
}

void GameManager::setupTwoPlayer()
{
	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);
	snake1 = Snake(0.5, 0.5, 1, 1, 0);
	fruit = Fruit(fx, fy, 1, 0, 1);
	snake2 = Snake(-0.5, -0.5, 0, 1, 0);

}

void GameManager::setupAI()
{
	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);
	snake1 = Snake(0.5, 0.5, 0, 1, 1);
	fruit = Fruit(fx, fy, 1, 0, 1);
	snake2 = Snake(-0.5, -0.5, 1, 0, 0);
}

void GameManager::runSingle()
{

	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);


	count++;
	//snake1.grow();
	fruit.draw();

	if (((float)(clock() - t))/CLOCKS_PER_SEC > 0.05)
	{
		//cout << "I'm going in if statement to make move\n";
			snake1.move(snake1.getDirection());

			if (snake1.isThereCollision(snake1.getHead(), true) ) {
				if (score.isTop10()) {
					string highperson;

					cout << "HIGH SCORE " << endl;
					cout << "Enter Name: ";
					cin >> highperson;
					score.save(highperson);

					if (keyboard == ' ')
					{
						mode = Menu;
						return;
					}
				}
				status = GameOver;


			}
			else if (fruit.isThereCollision(snake1.getHead())) {
				snake1.grow();
			
				fruit = Fruit((fx), (fy), 1, 0, 1);

				score.increaseScore();

				cout << "current score is " << score.getCurrentScore() << endl;

			}


			/*if (woah.isThereCollision(snake1.getHead()))
			{
			snake1.grow();
			}*/				
		
			//std::cout << "Snake is moving\n";
			

		count = 0;
		t = clock();
	}

	
	snake1.draw();


}

void GameManager::runTwoPlayer()
{
	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);
	
	count++;

	


	if ((((float)(clock() - t)) / CLOCKS_PER_SEC > 0.05) ) {
		snake1.move(snake1.getDirection());

			if (snake1.isThereCollision(snake1.getHead(), true) || snake2.isThereCollision(snake1.getHead(), false)) {
				cout << "Player 2 wins" << endl;

				status = GameOver;
			}
			else if (fruit.isThereCollision(snake1.getHead())) {
				snake1.grow();

				fruit = Fruit((fx), (fy), 1, 0, 1);
			}
			t = clock();

		// code here...
			snake2.move(snake2.getDirection());

			if (snake2.isThereCollision(snake2.getHead(), true) || snake1.isThereCollision(snake2.getHead(), false) && status != GameOver) {
				cout << "Player 1 wins" << endl;

				status = GameOver;
			}
			else if (fruit.isThereCollision(snake2.getHead())) {
				snake2.grow();

				fruit = Fruit((fx), (fy), 1, 0, 1);
			}
		
			count = 0;
			t = clock();
	}// code here...


		fruit.draw();

	snake1.draw();
	snake2.draw();
}

void GameManager::runAI()
{
	srand(time(NULL));
	int rand_num = rand() % 4;

	
	time_t t_2;

	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);
	count++;

	fruit.draw();

	cout << rand_num;
	
	if ((((float)(clock() - t)) / CLOCKS_PER_SEC > 0.05)) {
		snake1.move(snake1.getDirection());

		switch (rand_num)
		{
		case 0: snake2.move(North); break;
		case 1: snake2.move(East); break;
		case 2: snake2.move(South); break;
		case 3: snake2.move(West); break;
		}

		if (snake1.isThereCollision(snake1.getHead(), true) || snake2.isThereCollision(snake1.getHead(), false)) {
			cout << "You lose" << endl;
			status = GameOver;
		}
		else if (fruit.isThereCollision(snake1.getHead())) {
			snake1.grow();

			fruit = Fruit((fx), (fy), 1, 0, 1);
			
		}

		t = clock();

	
	

		
		if (snake2.isThereCollision(snake2.getHead(), true) || snake1.isThereCollision(snake2.getHead(), false) && status != GameOver) {
			cout << "You win" << endl;
			status = GameOver;
		}
		else if (fruit.isThereCollision(snake2.getHead())) {
			snake2.grow();
			fruit = Fruit((fx), (fy), 1, 0, 1);

		}

		t = clock();
	}
// code here...

	fruit.draw();


	snake1.draw();
	snake2.draw();
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