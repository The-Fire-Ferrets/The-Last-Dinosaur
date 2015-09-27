#include "Pong.h"

/**
 ** Usage: ./Pong [TwoPlayers]
 ** Controls:
 **     Player 1 Controls: Up = "W"; Down = "S"
 **     Player 2 Controls: Up = "Up" arrow; Down = "Down" arrow
 ** Objective:
 **     Keep the ball from getting past your paddle
 ** Rules:
 **     DONT LOSE!

**/
int main(int argc, char** argv) {
	//Checks command line arguments to see if two player mode was toggled
	std::string player_two = "CPU.xml";
	if (argc > 1)
		if (!strcmp(argv[1], "TwoPlayers"))
			player_two = "Player.xml";

	//Holds the names to the default actors that make up the game
	std::string actor_choices[] = {"Player.xml", player_two, "Ball.xml", "Wall.xml", "Wall.xml", "Wall.xml", "Wall.xml"};
	int num_actors = sizeof(actor_choices)/sizeof(actor_choices[0]);
	
	//Loads the Font and setups up text to be displayed at the end of each match
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text* result[] = {new sf::Text("Player 1 Wins \nPress R to Restart \nPress Q to quit", font, 40), new sf::Text("Player 2 Wins \nPress R to Restart \nPress Q to quit", font, 40)};
	result[0]->setPosition(sf::Vector2f(result_position.x - result[0]->getGlobalBounds().width/2, result_position.y - result[0]->getGlobalBounds().height/2));
	result[1]->setPosition(sf::Vector2f(result_position.x - result[1]->getGlobalBounds().width/2, result_position.y - result[1]->getGlobalBounds().height/2));
	
	//Holds the current game state
	// 1 = playing; 0 = reset game after score; 2 = player 1 wins; 3 = player 2 wins; 4 = restart game; 5 = quit game
	int state = 1;

	//Holds pointers to the actors in the game. Uses the Factory to create the selected actors			
	StrongActorPtr actors_list[num_actors];
	for (int i = 0; i < num_actors; i ++) {
		actors_list[i] = ActorFactory::CreateActor(actor_choices[i].c_str(), &state);
		if (debug_mode)
			std::cout << actors_list[i]->getId() << std::endl;
	}

	/**
	 ** Main Game Loop
	 ** Uses a set frame rate to control game timing
	 ** Reads input and updates actors and components
	**/
	while(App.isOpen()) {
		sf::Event Event;
		elapsed_f = fr_clock.restart().asSeconds();

		//Controls timing for updating actors and components after reading input
		while(elapsed_f < 1.f/frame_rate) {
			while(App.pollEvent(Event)) {
				if(Event.type == sf::Event::Closed)
					App.close();
				if ((state == 2 || state == 3) && Event.type == sf::Event::KeyPressed) {
    					if (Event.key.code == sf::Keyboard::R)
						state = 4;
					if (Event.key.code == sf::Keyboard::Q)
						state = 5;
				}
			}
	
			if (state == 1)
				for (int i = 0; i < num_actors; i ++)
					actors_list[i]->update(fr_clock.getElapsedTime().asSeconds());
			else if (state == 0) {
				for (int i = 0; i < num_actors; i ++)
					actors_list[i]->reset();
				if (!state)
					state = 1;
			}
			else if (state == 4) {
				for (int i = 0; i < num_actors; i ++)
					actors_list[i]->restart();
				state = 1;
			}
			else if (state == 5) {
				for (int i = 0; i < num_actors; i ++)
					actors_list[i]->quit();
				return 0;
			}
			
			elapsed_f = fr_clock.getElapsedTime().asSeconds();
		}

		//Controls rendering actors and components
		App.clear(sf::Color::Black);

		if (state == 1 || state == 6)
			for (int i = 0; i < num_actors; i ++)
				actors_list[i]->render(&App);
		else if (state == 2) {
			App.draw(*result[0]);
		}
		else if (state == 3) {
			App.draw(*result[1]);
		}

		App.display();
	}

	return 0;
}
