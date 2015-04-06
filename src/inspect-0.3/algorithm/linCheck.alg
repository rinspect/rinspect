//1.in event_buffer.cc, foreach approved obj_call or obj_resp, run lin_checker::add_to_trace(InspectEvent &event).
//2.in scheduler.cc, after each run, call event_buffer.linChecker->print_check_trace().

//in lin_checker.cc:

void print_check_trace(){
	split_trace();

	bool result=run_linearizable_check_by_diff();

	if(result==true){
		cout<<"trace is linearizable"<<endl;
	}
	else
	{
		cout<<"trace is not linearizable"<<endl;
	}
}

bool run_linearizable_check_by_diff(){
	if (any splitted trace match one of the serial traces)
		return true;
	else
		return false;
}

void split_trace(){
	traces.add(concurr_trace);

	for each trace in traces{
		vector<trace > ret=check_trace(trace);

		if(ret.size==0)//serial trace
		{
			trace_dump_to_file(trace);
		}
		else if(ret.size==2)
		{
			traces.add(everything in ret);
		}
		traces.remove(trace);
	}


}



vector<trace > check_trace(trace &curr_trace) {
	vector<trace > ret;
	InspectEvent this_call;
	InspectEvent this_resp;//this_resp happens before that_resp
	int this_tid;
	InspectEvent that_call;
	InspectEvent that_resp;
	int that_tid;

	if (not serial trace) {//we see this_call, that_call and this_resp, but not that_resp yet.

		//build the trace 1 this_call->this_resp->that_call->that_resp

		trace trace_1;
		container that_temp;

		for(each event) {
			if(event==that_call) {
				that_temp.add(event);
				continue;
			}

			if(event=this_resp) {
				trace_1.add(event);
				trace_1.add(everything in that_temp);
				continue;
			}

			trace_1.add(event);
		}
		ret.add(trace_1);

		//build the trace 2 that_call->that_resp->this_call->this_resp

		trace trace_2;
		container that_temp;
		bool that_resp_not_reached = true;
		for(each event) {
			if (event is in this_tid && no earliar that this_call && that_resp_not_reached) {
				that_temp.add(event);
			continue;
			}

			if(event=that_resp) {
				trace_2.add(event);
				trace_2.add(everything in that_temp);
				continue;
			}

			trace_2.add(event);
		}
		ret.add(trace_2);
	}
	return ret;
}

