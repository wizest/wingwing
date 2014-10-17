#include "run.h"
#include "motor.h"
#include "turn.h"
#include "edge.h"
#include "sensor.h"
#include "adj.h"
#include "adj_pos.h"
#include "algol.h"
#include "delay.h"
#include "scan.h"
#include "pathcvrt.h"
#include "drive.h"
#include "sampling.h"
#include "led.h"
#include "serial.h"
#include "set_run.h"
#include "key.h"
#include "info.h"

void 			init_run();

unsigned int 	get_run();   // if empty, return 0;
void 			put_run(void (*run_type)());
void 			clr_run();

void          	(*run)();
void          	(*run_queue[RUN_QUEUE_SIZE])();
unsigned int	run_fptr;
unsigned int	run_rptr;


void init_run()
{
	clr_run();
}

unsigned int get_run()
{
	if ( run_fptr == run_rptr ) 	return 0;	// empty
	run 		= run_queue[ run_fptr ];

	//run_fptr 	= ++run_fptr % RUN_QUEUE_SIZE;
	run_fptr ++; 		// CAUTION!! overflow
	return 1;
}

void put_run(void (*run_type)())
{
	run_queue[ run_rptr ] 	= run_type;

	//run_rptr 	= ++run_rptr % RUN_QUEUE_SIZE;
	run_rptr ++; 		// CAUTION!! overflow
}

void clr_run()
{
	run_fptr = run_rptr = 0;
}

/////////////////////////////////////////////////////////////////////
// RUNs body                                                       //
/////////////////////////////////////////////////////////////////////
#include "scan.run"
#include "rush.run"
#include "inter.run"
#include "auxil.run"

