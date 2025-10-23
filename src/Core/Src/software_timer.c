#include "software_timer.h"	

// Variables
uint32_t g_totalSwTimer[NUMBER_OF_TIMERS] = {
	0,
	NUMBER_OF_SW_TIMER2,
	0,
	0,
	0
};

SoftwareTimer g_softwareTimer2[NUMBER_OF_SW_TIMER2];

SoftwareTimer* g_timers[NUMBER_OF_TIMERS] = {
	// Software Timer 1
	#ifdef SW_TIMER1
	&g_softwareTimer1
	#else
	NULL
	#endif
	,
	// Software Timer 2
	#ifdef SW_TIMER2
	&g_softwareTimer2[0]
	#else
	NULL
	#endif
	,
	// Software Timer 3
	#ifdef SW_TIMER3
	&g_softwareTimer3
	#else
	NULL
	#endif
	,
	// Software Timer 4
	#ifdef SW_TIMER4
	&g_softwareTimer4
	#else
	NULL
	#endif
	,
	// Software Timer 5
	#ifdef SW_TIMER5
	&g_softwareTimer5
	#else
	NULL
	#endif
	,
	// Software Timer 6
	#ifdef SW_TIMER6
	&g_softwareTimer6
	#else
	NULL
	#endif
	,
	// Software Timer 7
	#ifdef SW_TIMER7
	&g_softwareTimer7
	#else
	NULL
	#endif
	,
	// Software Timer 8
	#ifdef SW_TIMER8
	&g_softwareTimer8
	#else
	NULL
	#endif
	,
	// Software Timer 9
	#ifdef SW_TIMER9
	&g_softwareTimer9
	#else
	NULL
	#endif
	,
	// Software Timer 10
	#ifdef SW_TIMER10
	&g_softwareTimer10
	#else
	NULL
	#endif
	,
	// Software Timer 11
	#ifdef SW_TIMER11
	&g_softwareTimer11
	#else
	NULL
	#endif
	,
	// Software Timer 12
	#ifdef SW_TIMER12
	&g_softwareTimer12
	#else
	NULL
	#endif
	,
	// Software Timer 13
	#ifdef SW_TIMER13
	&g_softwareTimer13
	#else
	NULL
	#endif
	,
	// Software Timer 14
	#ifdef SW_TIMER14
	&g_softwareTimer14
	#else
	NULL
	#endif
};

// Private Functions Definition
void checkSoftwareTimer(uint8_t timer){
	SoftwareTimer* timer_ptr = g_timers[timer-1];

	for(uint32_t i = 0; i < g_totalSwTimer[timer-1]; ++i){
		if(timer_ptr[i].timer_counter > 0){
			timer_ptr[i].timer_counter--;
			if(timer_ptr[i].timer_counter == 0){
				timer_ptr[i].timer_flag = 1;
				
				if(timer_ptr[i].repetition < 0){
					setTimer(timer, &timer_ptr[i].duration, &i);
				}
				else if(timer_ptr[i].repetition > 0){
					timer_ptr[i].repetition--;
					if(timer_ptr[i].repetition > 0){
						setTimer(timer, &timer_ptr[i].duration, &i);
					}
				}
			}
		}
	}
}

// Global Functions Definition
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// Software Timer 1
	#ifdef SW_TIMER1
	if(htim->Instance == TIM1){
		
	}
	#endif

	// Software Timer 2
	#ifdef SW_TIMER2
	if(htim->Instance == TIM2){
		// Handle all software timers
		checkSoftwareTimer(SW_TIMER2);
	}
	#endif

	// Software Timer 3
	#ifdef SW_TIMER3
	if(htim->Instance == TIM3){

	}
	#endif

	// Software Timer 4
	#ifdef SW_TIMER4
	if(htim->Instance == TIM4){

	}
	#endif
}

void initSoftwareTimer(TIM_HandleTypeDef* htim){
	HAL_TIM_Base_Start_IT(htim);
}

uint8_t getFlag(uint8_t timer, uint32_t* sw_timer_index){
	if(timer <= 0 || timer > NUMBER_OF_TIMERS || g_timers[timer-1] == NULL)
		return -1;

	if(sw_timer_index == NULL || *sw_timer_index < 0 || *sw_timer_index >= g_totalSwTimer[timer-1]){
		return -1;
	}
	
	return g_timers[timer-1][*sw_timer_index].timer_flag;
}
	
uint8_t resetFlag(uint8_t timer, uint32_t* sw_timer_index){
	if(timer <= 0 || timer > NUMBER_OF_TIMERS || g_timers[timer-1] == NULL)
		return -1;

	if(sw_timer_index == NULL || *sw_timer_index < 0 || *sw_timer_index >= g_totalSwTimer[timer-1]){
		return -1;
	}
	
	g_timers[timer-1][*sw_timer_index].timer_flag = 0;
	return 0;
}

uint8_t setTimer(uint8_t timer, uint32_t* duration, uint32_t* sw_timer_index){
	if(timer <= 0 || timer > NUMBER_OF_TIMERS || g_timers[timer-1] == NULL)
		return -1;
	
	if(sw_timer_index == NULL || *sw_timer_index < 0 || *sw_timer_index >= g_totalSwTimer[timer-1]){
		return -1;
	}

	if(duration == NULL || *duration <= 0){
		return -1;
	}

	if(resetFlag(timer, sw_timer_index) != 0){
		return -1;
	}

	g_timers[timer-1][*sw_timer_index].duration = (*duration)/TIM2_INTERVAL;
	
	return 0;
}

uint8_t setRepetition(uint8_t timer, uint32_t* repetition, uint32_t* sw_timer_index){
	if(timer <= 0 || timer > NUMBER_OF_TIMERS || g_timers[timer-1] == NULL)
		return -1;
	
	if(sw_timer_index == NULL || *sw_timer_index < 0 || *sw_timer_index >= g_totalSwTimer[timer-1]){
		return -1;
	}

	if(repetition == NULL){
		return -1;
	}

	g_timers[timer-1][*sw_timer_index].repetition = *repetition;
	return 0;
}



