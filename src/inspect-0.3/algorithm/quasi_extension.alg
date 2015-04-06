//1.Preliminary:
/*
 * From the original trace
 * suppose we have 5 steps
 * quasi =2, we can get a table:
 * step |   enable_set  |	new enabled set
 * 1	|	1 2 3		|	1 2 3
 * 2	|	2 3 4		|	4
 * 3	|	3 4 5		|	5
 * 4	|	4 5 		|
 * 5 	|	5   		|
 *
 * this is the solid information that will never change
 * int any extension, any step should select an event not in the enable_set
 */

//2.define a quasi_state class, store the enable set of a state and the quasi cost
/*class quasi_state {
 *public:
 *	map<int,bool> new_enable_done;//the third column above
 *	map<int,bool> enable_done;//the second column above
 *	map<int,int> quasi_cost;
 *}
 */

//3.build the first state stack
//4.
void

void quasi_trace_backtrack_extension(trace) {
	map<int, quasi_state> steps_info; //store steps and for each step, the new_enable set
	map<int, quasi_state> states; //build the states stack according to the input trace(the table above),all cost=quasi=2

	while (true) {
	reverse: for each state in states {
		if(state has backtrack point) {

			//step 1: choose an up_event, if any event's cost==0, then we must select this event, else we choose according to the eid order
			select up_event;
			int up_event;//event to go earlier

			compute down_events according to partial order relationship
			int []down_events;//event to to later

			//step 2: enable_done set
			for all (this state.quasi_cost[down_event]-1)
			state.enable_done[up_event]=false;//mark the up_event to be not enabled

			//step 3: re-compute the rest trace ?????don't know how to compute future enable_done set
			trace new_trace;//(states)
			break;//(another while loop)
		}
		else return;

	}
}

}
