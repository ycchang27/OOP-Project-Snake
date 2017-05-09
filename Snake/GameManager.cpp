#include "GameManager.h"
#include <iomanip>
#include <random>

// Helper methods:
double aspect_ratio = 0;
void reshape(int w, int h)
{
	aspect_ratio = (double)w / (double)h;
	glViewport(0, 0, w, h);
}

void output(GLfloat x, GLfloat y, char* text)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(1 / 1000.0, 1 / 1000.0, 1 / 1000.0);
	for (char* p = text; *p; p++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
}

GameManager::GameManager()
{
	// code here...	
	mode = Menu;
	status = StandBy;
	keyboard = 'x';
	special_keyboard = -1;
	t = clock();
	background = Square(-1.0, 1.0);
	background.setToBackgroundSize();

	// Inititializing sound engine
	sound_effect = createIrrKlangDevice();
	if (!sound_effect)
		cout << "Error: Sound effect could not be created" << endl;
	background_music = createIrrKlangDevice();
	if (!background_music)
		cout << "Error: Background music could not be created" << endl;
	background_music->play2D("../background.mp3", true);
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
	score.resetScore();
	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);
	snake1 = Snake(0,0,0,1,0, loadTexture("../profile_single.bmp"));
	fruit = Fruit(fx,fy,1,0,1); 
	turn = Player1;
	texture = loadTexture("../difficulty_selection.bmp");
	difficulty = NotInitialized;
}

void GameManager::setupTwoPlayer()
{
	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);
	snake1 = Snake(0.5, 0.5, 1, 1, 0, loadTexture("../DIO.bmp"));
	fruit = Fruit(fx, fy, 1, 0, 1);
	snake2 = Snake(-0.5, -0.5, 0, 1, 0, loadTexture("../DIO.bmp"));

}

void GameManager::setupAI()
{
	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);
	snake1 = Snake(0.5, 0.5, 0, 1, 1, loadTexture("../DIO.bmp"));
	fruit = Fruit(fx, fy, 1, 0, 1);
	snake2 = Snake(-0.5, -0.5, 1, 0, 0, loadTexture("../DIO.bmp"));
}

void GameManager::runSingle()
{
	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);

	count++;
	//snake1.grow();
	fruit.draw();

	if (((float)(clock() - t))/CLOCKS_PER_SEC > game_speed)
	{
		snake1.move(snake1.getDirection());

		if (snake1.isThereCollision(snake1.getHead(), true)) {
			sound_effect->stopAllSounds();
			status = GameOver;
		}
		else if (fruit.isThereCollision(snake1.getHead())) {
			snake1.grow();
			fruit = Fruit((fx), (fy), 1, 0, 1);
			score.increaseScore();
			sound_effect->stopAllSounds();
			sound_effect->play2D("../fruit_single.wav", false);
		}


		/*if (woah.isThereCollision(snake1.getHead()))
		{
		snake1.grow();
		}*/

		//std::cout << "Snake is moving\n";


		count = 0;
		t = clock();
	}
	snake1.draw();									// Display snake

	// Display game background:
	// Display score
	glColor3d(0.0, 0.0, 0.0);						// Set the color
	char c;
	string line = "";
	int tempscore = score.getCurrentScore();
	if (tempscore == 0)
	{
		c = 48;
		line = c + line;
	}
	else
	{
		while (tempscore / 10 != 0 || tempscore % 10 != 0)
		{
			c = (tempscore % 10) + 48;
			line = c + line;
			tempscore /= 10;
		}
	}
	char* temp;
	switch (difficulty)									// Display game difficulty
	{
	case Easy: line = "Level: Easy  Score: " + line; break;
	case Intermediate: line = "Level: Normal  Score: " + line; break;
	case Hard: line = "Level: Hard  Score: " + line; break;
	}
	temp = new char[line.size() + 1];
	strcpy(temp, line.c_str());
	output(-1, -0.95, temp);

	// Draw Boundary line (to separate between score and the game)
	glBegin(GL_LINES);								// Start drawing
	glVertex2f(-1, -0.8);
	glVertex2f(1 , -0.8);
	glEnd();										// Stop drawing

	// Draw the background
	glColor3d(1.0, 1.0, 1.0);						// Set the color
	background.textureDraw(texture);
}

void GameManager::runTwoPlayer()
{
	srand(time(NULL));

	double fx = ((double)(rand() % 15 - 8) / 10);
	double fy = ((double)(rand() % 15 - 7) / 10);
	
	count++;

	


	if ((((float)(clock() - t)) / CLOCKS_PER_SEC > 0.1) ) {
		snake1.move(snake1.getDirection());

			if (snake1.isThereCollision(snake1.getHead(), true) || snake2.isThereCollision(snake1.getHead(), false)) {
				//cout << "Player 2 wins" << endl;
				sound_effect->stopAllSounds();
				sound_effect->play2D("../victory_player2.mp3");
				status = GameOver;
				victory = Player2;
			}
			else if (fruit.isThereCollision(snake1.getHead())) {
				sound_effect->stopAllSounds();
				sound_effect->play2D("../fruit_player1.mp3");
				snake1.grow();

				fruit = Fruit((fx), (fy), 1, 0, 1);
			}
			t = clock();

		// code here...
			snake2.move(snake2.getDirection());

			if (snake2.isThereCollision(snake2.getHead(), true) || snake1.isThereCollision(snake2.getHead(), false) && status != GameOver) {
				//cout << "Player 1 wins" << endl;
				sound_effect->stopAllSounds();
				sound_effect->play2D("../victory_player1.wav");
				status = GameOver;
				victory = Player1;
			}
			else if (fruit.isThereCollision(snake2.getHead())) {
				snake2.grow();
				sound_effect->stopAllSounds();
				sound_effect->play2D("../fruit_player2.wav");
				fruit = Fruit((fx), (fy), 1, 0, 1);
			}
		
			count = 0;
			t = clock();
	}// code here...


		fruit.draw();

	snake1.draw();
	snake2.draw();
	// Draw Boundary line (to separate between score and the game)
	glBegin(GL_LINES);								// Start drawing
	glVertex2f(-1, -0.8);
	glVertex2f(1, -0.8);
	glEnd();										// Stop drawing

													// Draw the background
	glColor3d(1.0, 1.0, 1.0);						// Set the color
	background.textureDraw(texture);
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

	//cout << rand_num;
	
	if ((((float)(clock() - t)) / CLOCKS_PER_SEC > 0.1)) {
		snake1.move(snake1.getDirection());

		switch (rand_num)
		{
		case 0: snake2.move(North); break;
		case 1: snake2.move(East); break;
		case 2: snake2.move(South); break;
		case 3: snake2.move(West); break;
		}

		if (snake1.isThereCollision(snake1.getHead(), true) || snake2.isThereCollision(snake1.getHead(), false)) {
			status = GameOver;
			victory = AI;
			sound_effect->stopAllSounds();
			sound_effect->play2D("../victory_player2.mp3");
		}
		else if (fruit.isThereCollision(snake1.getHead())) {
			snake1.grow();
			sound_effect->play2D("../fruit_player1.mp3");
			fruit = Fruit((fx), (fy), 1, 0, 1);
		}
		t = clock();
		
		if (snake2.isThereCollision(snake2.getHead(), true) || snake1.isThereCollision(snake2.getHead(), false) && status != GameOver) {
			//cout << "You win" << endl;
			sound_effect->stopAllSounds();
			sound_effect->play2D("../victory_player1.wav");
			status = GameOver;
			victory = Player1;
		}
		else if (fruit.isThereCollision(snake2.getHead())) {
			snake2.grow();
			sound_effect->stopAllSounds();
			sound_effect->play2D("../fruit_player2.wav");
			fruit = Fruit((fx), (fy), 1, 0, 1);
		}
		t = clock();
	}
// code here...

	fruit.draw();


	snake1.draw();
	snake2.draw();
	// Draw Boundary line (to separate between score and the game)
	glBegin(GL_LINES);								// Start drawing
	glVertex2f(-1, -0.8);
	glVertex2f(1, -0.8);
	glEnd();										// Stop drawing

													// Draw the background
	glColor3d(1.0, 1.0, 1.0);						// Set the color
	background.textureDraw(texture);
}

void GameManager::run()
{
	if (status == GameOver)													// Does nothing if the game is over
		return;
	if (mode == SinglePlayerMode && difficulty == NotInitialized)			// Get user to choose the game difficulty
	{
		glColor3d(1.0, 1.0, 1.0);											// Set the color
		background.textureDraw(texture);
		if (keyboard == '\0')												// Invalid input
		{
			resetInput();													// Reset user input
			return;
		}
		switch (keyboard)
		{
		case '1': difficulty = Easy; game_speed = 0.10; break;
		case '2': difficulty = Intermediate; game_speed = 0.05; break;
		case '3': difficulty = Hard; game_speed = 0.025; break;
		}
		score = ScoreKeeper(difficulty);									// Set up the score keeper
		resetInput();														// Reset user input
		return;
	}
	if (status == StandBy)													// Does nothing if the game is on standby (space bar is required to finish)
	{
		char* temp;
		string line = "Press space bar to start";
		temp = new char[line.size() + 1];
		strcpy(temp, line.c_str());
		output(-0.8, 0, temp);
		delete temp;
		if (keyboard != ' ')
		{
			resetInput();														// Reset user input
			return;
		}
		else
		{
			texture = loadTexture("../gamedisplay.bmp");
			status = InProgress;												// Start the game
			background_music->stopAllSounds();
		}
	}

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
		if (score.isTop10())	// in top 10 (high score)
			receiveName();
		else	// not in top 10 (no high score)
		{
			if (keyboard == 13)												// stops input when enter key is pressed (goes back to the menu)
			{
				mode = Menu;
				status = StandBy;
			}
			else
			{
				char c;
				string line = "";
				int tempscore = score.getCurrentScore();
				if (tempscore == 0)
				{
					c = 48;
					line = c + line;
				}
				else
				{
					while (tempscore / 10 != 0 || tempscore % 10 != 0)
					{
						c = (tempscore % 10) + 48;
						line = c + line;
						tempscore /= 10;
					}
				}
				line = "Your Score: " + line;
				char* temp = new char[line.size() + 1];
				strcpy(temp, line.c_str());
				glColor3d(0.0, 0.0, 0.0);									// Set the color
				output(-0.85, -0.45, temp);
				delete temp;
				output(-0.85, -0.6, "Enter key: return to menu");
				glColor3d(1.0, 1.0, 1.0);									// Set the color
				texture = loadTexture("../gameover_nohighscore.bmp");
				background.textureDraw(texture);
			}
		}
	}
	else if (victory == Player1)											// Player1's victory
	{
		if (keyboard == 13)													// stops input when enter key is pressed (goes back to the menu)
		{
			mode = Menu;
			status = StandBy;
		}
		else
		{
			/*output(-0.85, -0.6, "Enter key: return to menu");*/
			glColor3d(1.0, 1.0, 1.0);										// Set the color
			texture = loadTexture("../victory_player1.bmp");
			background.textureDraw(texture);
		}
	}
	else if (victory == Player2)											// Player2's victory
	{
		//sound_effect->play2D("../victory_player2.mp3");
		if (keyboard == 13)												// stops input when enter key is pressed (goes back to the menu)
		{
			mode = Menu;
			status = StandBy;
		}
		else
		{
			/*output(-0.85, -0.6, "Enter key: return to menu");*/
			glColor3d(1.0, 1.0, 1.0);									// Set the color
			texture = loadTexture("../victory_player2.bmp");
			background.textureDraw(texture);
		}
	}
	else																	// AI's victory
	{
		if (keyboard == 13)												// stops input when enter key is pressed (goes back to the menu)
		{
			mode = Menu;
			status = StandBy;
		}
		else
		{
			/*output(-0.85, -0.6, "Enter key: return to menu");*/
			glColor3d(1.0, 1.0, 1.0);									// Set the color
			texture = loadTexture("../victory_player2.bmp");
			background.textureDraw(texture);
		}

	}
	resetInput();															// Reset user input
}

void GameManager::receiveName()
{
	int size = player_name.size();
	if (keyboard == 13)									// stops input when enter key is pressed (goes back to the menu)
	{
		mode = Menu;
		status = StandBy;
		score.save(player_name, difficulty);
		score.resetScore();
		player_name.erase();
		score = ScoreKeeper();
		return;
	}
	else if ((keyboard == 127 || keyboard == 8) && size != 0)
	{
		player_name.erase(player_name.end() - 1);
		resetInput();
	}
	glColor3d(0.0, 0.0, 0.0);						// Set the color
	// display UI
	double startx = -0.95, starty = 0.0;				// determine where to start printing
	glLineWidth(2.0);									// line length = 2
	startx = -0.95;
	output(startx, starty, "Name:");
	starty -= 0.15;										// next line
	output(startx, starty, "(No more than 10 chars)");
	starty -= 0.15;										// next line

	// receive input
	if (keyboard != '\0' && size <= 10)
		player_name += keyboard;

	// display current input
	char* temp;
	temp = new char[player_name.size() + 1];
	strcpy(temp, player_name.c_str());
	output(startx, starty, temp);
	delete temp;

	// paint the screen
	// display score
	char c;
	string line = "";
	int tempscore = score.getCurrentScore();
	if (tempscore == 0)
	{
		c = 48;
		line = c + line;
	}
	else
	{
		while (tempscore / 10 != 0 || tempscore % 10 != 0)
		{
			c = (tempscore % 10) + 48;
			line = c + line;
			tempscore /= 10;
		}
	}
	line = "Score: " + line;
	temp = new char[line.size() + 1];
	strcpy(temp, line.c_str());
	output(startx, starty - 0.15, temp);
	output(startx, starty - 0.3, "Enter key: return to menu");
	delete temp;
	glColor3d(1.0, 1.0, 1.0);						// Set the color
	texture = loadTexture("../gameover_highscore.bmp");
	background.textureDraw(texture);

	glEnd();
}

void GameManager::displayMenu()
{
	// Display menu
	texture = loadTexture("../menu.bmp");
	background.textureDraw(texture);
	
	// Apply user response (not terminal)
	switch (keyboard)
	{
	case '1': mode = SinglePlayerMode; break;								// Single player mode
	case '2': mode = TwoPlayerMode; break;									// Two player mode
	case '3': mode = AIMode; break;											// AI mode
	case '4': mode = ScoreDisplayEasy; resetInput(); return;				// Display scoreboard (Easy)
	case '5': mode = ScoreDisplayInt; resetInput(); return;					// Display scoreboard (Intermediate)
	case '6': mode = ScoreDisplayHard; resetInput(); return;				// Display scoreboard (Hard)
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
	score.display(displayMe, mode);

	// Display the scoreboard
	double startx = -0.95, starty = 0.85;				// determine where to start printing
	glColor3d(255, 255, 255);							// text color = white
	glLineWidth(2.0);									// line length = 2
	startx = -0.95;
	output(startx, starty, "Name");
	startx = 0.2;
	output(startx, starty, "|");
	startx = 0.3;
	output(startx, starty, "Score");
	startx = -0.95;
	starty -= 0.15;										// next line
	output(startx, starty, "------------------");
	starty -= 0.15;

	// Print scores
	string line;
	char *temp;
	char c;
	for (int i = 0; i < displayMe.size(); ++i)
	{
		if (i == 9)										// # 10 case
			line = "10";
		else											// everything else
		{
			c = i + 49;
			line = c;
		}
		temp = new char[line.size() + 1];
		strcpy(temp, line.c_str());
		output(startx, starty, temp);

		startx = -0.8;
		line = ") " + displayMe[i].player_name;
		temp = new char[line.size() + 1];
		strcpy(temp, line.c_str());
		output(startx, starty, temp);

		startx = 0.2;
		output(startx, starty, "|");

		startx = 0.3;
		line = to_string(displayMe[i].score);
		temp = new char[line.size() + 1];
		strcpy(temp, line.c_str());
		output(startx, starty, temp);

		starty -= 0.15;
		startx = -0.95;									// next line
	}
	startx = -0.95;
	output(startx, starty, "Space bar: Return to menu");
	glEnd();
	resetInput();
}