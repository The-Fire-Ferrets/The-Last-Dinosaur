#include "LevelFactory.h"

//Total size of pointer arrays
int LevelFactory::size = 20;
//Current number of actors
int LevelFactory::num_actors = 0;
//Gives each actor a unique ID
ActorId LevelFactory::currActorId = 0;
//Array holding pointers of actors populating the level
StrongActorPtr LevelFactory::actors[size];
//Holds filename of background to load
std::string LevelFactory::background;
//Holds level name
std::string LevelFactory::name;
/** Creates and populates a level and all its components based on XML configuration
 ** resource: filename for xml
 ** state: current game state
**/
StrongActorPtr LevelFactory::CreateLevel(const char* resource, int* state) {
	//Reference to current location in Actor population array
	num_actors = 0;
	//Holds referenced to loaded XML file	
	pugi::xml_document doc;
	
	//Error check to see if file was loaded correctly
	pugi::xml_parse_result result;
    if (!(result = doc.load_file(resource))) {
		std::cout << "LevelFactory::CreateLevel(...): Failed to load" << std::endl;
		std::cout << "Filename: " << resource << " Load result: " << result.description() << std::endl;
	}

	//Used to iterate over XML file to get attributes
	pugi::xml_node tools = doc.child(((std::string) resource).substr(0, ((std::string) resource).size() - 4).c_str());

	//Iterates over XML to get components to add
	for (pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling()) {
		if (debug_mode)
			std::cout << tool.name() << std::endl;
		actors[num_actors++] = ActorFactory::CreateActor(tool.name(), state);
	}
}

std::string LevelFactory::getName(void) {
	return name;
}

int LevelFactory::getNumActors(void) {
	return num_actors;
}
