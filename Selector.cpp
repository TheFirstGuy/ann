#include "Selector.h"
/*Stefan Cherubin*/

Selector::Selector(int request_signal)
{
	signal_processing = request_signal;
	enable_accumalator = 0;
	enable_mult = 0;
}

void Selector::trafficControl()
{
	if (selected == 1)
		sel = 0;
	else if (selected == 2)
		sel = 1;
	else if (selected == 4)
		sel = 2;
	else if (selected == 16)
		sel = 3;
	else
		sel = 0;
	
}
