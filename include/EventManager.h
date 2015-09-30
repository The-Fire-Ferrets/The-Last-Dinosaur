#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Constants.h"
#include "EventManagerInterface.h"
#include "EventInterface.h"

class EventManager : public EventManagerInterface {
	public:
		explicit EventManager(void);
		virtual ~EventManager(void);

		EventQueue queues[2];
		EventQueuePtr process_queue = std::make_shared<EventQueue>(queues[0]);

		EventQueuePtr register_queue = std::make_shared<EventQueue>(queues[1]);

		EventDelegateMap eventDelegateMap;

		virtual bool queueEvent(const EventInterface* event) override;
		virtual bool addDelegate(const EventDelegate& d, const EventType& type) override;
		virtual bool removeDelegate(const EventDelegate& d, const EventType& type) override;
		virtual bool triggerEvent(const EventInterfacePtr& event) override;
		virtual bool processEvents(void) override;

};
#endif



