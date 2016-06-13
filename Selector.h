#pragma once
/*Stefan Cherubin*/

class Selector {
	enum state {forward, backward};
	int signal_processing, selected;
	int enable_mult, enable_accumalator, pre_res, sel;


public:
	Selector(int request_signal);

	void trafficControl();
};
