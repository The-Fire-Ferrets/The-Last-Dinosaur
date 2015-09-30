#include "ParamourusRex.h"

#include "ContactEvent.h"

int main(int argc, char* argv[])
{	
	//Instantiate a global EventManager
	EventManager* eventmanager = new EventManager();
	EventManagerInterfacePtr eventmanagerptr;
	eventmanagerptr.reset(eventmanager);
	EventManagerInterface::set(eventmanagerptr);
	
	//Load configuration
   	if (!(result = doc.load_file( ("./assets/" + config + ".xml").c_str() ))) {
		std::cout << "Main: Failed to load config" << std::endl;
		std::cout << "Filename: " << config << " Load result: " << result.description() << std::endl;
	}

	//Used to iterate over XML file to get attributes
	char * temp;
	char temp_path[30];

	pugi::xml_node tools = doc.child(config.c_str());
	for (pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling()) {
		for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute()) {
			if (!strcmp(attr.name(), "Height")) {
				window_height = std::strtol(attr.value(), &temp, 10);	
				if (*temp != '\0') {
					std::cout << "Main: Failed to load configuration: Error reading attribute for " << attr.name() << std::endl;
					return false;
				}					
			}
			else if (!strcmp(attr.name(), "Width")) {
				window_width = std::strtol(attr.value(), &temp, 10);	
				if (*temp != '\0') {
					std::cout << "Main: Failed to load configuration: Error reading attribute for " << attr.name() << std::endl;
					return false;
				}					
			}
		}
	}
	sf::RenderWindow App(sf::VideoMode(window_width, window_height,64), "The Last Dinosaur by Will Hollingsworth, Bina Kakusa, Belol Nessar, and Meghan Tinkler", sf::Style::Titlebar|sf::Style::Close);
	
	//Array holding levels in the order to be played
	const char* levels[] = {"Level0"};
	
	//Holds the current game state
	// 0 = At the map; 1 = In a level; 2 = Talking to Diana; 3 = At craftable; 4 = quit game
	int state = 0;
	
	/**
	 ** Main Game Loop
	 ** Uses a set frame rate to control game timing
	 ** Reads input and updates actors and components
	**/
	while(App.isOpen()) {
		sf::Event Event;
		
		//Start structure to control frame rate
		elapsed = fr_clock.getElapsedTime();
		elapsed_ms = elapsed.asSeconds();
		while(App.pollEvent(Event)) {
			if(Event.type == sf::Event::Closed) {
				for (int i = 0; i < LevelView::getNumActors(); i ++)
					LevelView::actors[i]->quit();
				App.close();
			}
		}
		switch(state) {
			case 0: //Create level, for now just load HelloWorldLevel
				LevelView::CreateLevel(levels[0], &state);
				state = 1;
				break;
			case 1:
				for (int i = 0; i < LevelView::getNumActors(); i ++)
					LevelView::actors[i]->update(elapsed_ms);
				break;
			case 2: //Display Diana
				break;
			case 3: //Display craftable
				break;
			case 4:
				for (int i = 0; i < LevelView::getNumActors(); i ++)
					LevelView::actors[i]->quit();
				return 0;
			default: 
				break;
		}
		//End structure to control frame rate
		
		//Controls rendering actors and components
		App.clear(sf::Color::Black);

		switch(state) {
			case 0: //Display map
				break;
			case 1: //Display level
				for (int i = 0; i < LevelView::getNumActors(); i ++)
					LevelView::actors[i]->render(&App);
				break;
			case 2: //Display female
				break;
			case 3: //Display craftable
				break;
			case 4: //Display exit screen
				break;
			default: 
				break;
		}
		App.display();

		//Proccess all events
		if (!eventmanagerptr->processEvents()) {	
			std::cout << "Main: Failed to process events" << std::endl;
		}
	}

	return 0;
}
