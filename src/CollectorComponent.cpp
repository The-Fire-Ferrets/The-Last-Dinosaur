#include "CollectorComponent.h"

//Unique instance id among instances of the same component
int CollectorComponent::instances = -1;
//Unique component id
ComponentId CollectorComponent::id = "CollectorComponent";
//Registers component with factory
const bool CollectorComponent::registered = ActorFactory::registerComponent(&id, &create);

/** Returns the id shared by all components of this type
 **
**/
ComponentId CollectorComponent::getId(void) {
	return id;
}

/** Returns a reference to the components constructor
 **
**/
ActorComponent* CollectorComponent::create() { 
	//update the instance count
	instances++;
	return new CollectorComponent();
}

/** Constructor
 ** Sets up unique instance ID
**/
CollectorComponent::CollectorComponent(void) {
	instance = instances;
}

/** Initializer
 ** elem : node pointing to section of XML configuration holding more attribute defaults to setup
 ** Sets up additional attribute defaults
**/
bool CollectorComponent::Init(pugi::xml_node* elem) {	
	char * temp;
	//Iterate over the component's attributes
	for (pugi::xml_node tool = elem->first_child(); tool; tool = tool.next_sibling()) {
		for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute()) {
			if (!strcmp(attr.name(), "Vases")) {
				vases = std::strtol(attr.value(), &temp, 10);				
				if (*temp != '\0') {
					std::cout << "CollectorComponent::Init: Failed to initialize: Error reading attribute for " << attr.name() << std::endl;
					return false;
				}					
			}
		}
	}
	return true;
}

/** Final Initilizer
 ** Setups up additional attributes based on game configuration
**/
void CollectorComponent::PostInit(void) {
}

/** Updates the component's attributes
 ** time: current game time
**/
void CollectorComponent::update(float time) {
	
}

/** Renders the component
 ** window: canvas on which to draw the component
 ** 
**/
void CollectorComponent::render(sf::RenderWindow *window) {
}

/** Reset the component
 **
**/
void CollectorComponent::reset(void) {

}

/** Restart the component
 **
**/
void CollectorComponent::restart(void) {

}

/** Cleans up after quiting
 **
**/
void CollectorComponent::quit(void) {

}

void CollectorComponent::setVases(int b) {
	vases = b;
}

int CollectorComponent::getVases(void) {
	return vases;
}
