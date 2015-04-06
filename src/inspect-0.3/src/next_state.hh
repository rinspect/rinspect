#ifndef __INSPECT_NEXT_STATE_REL_HH_
#define __INSPECT_NEXT_STATE_REL_HH_


#include "state.hh"
#include "inspect_event.hh"
#include "event_buffer.hh"

State * next_state(State* state, 
		   InspectEvent &event, 
		   EventBuffer &event_buffer);

void update_pcb_count(State *state);
#endif


