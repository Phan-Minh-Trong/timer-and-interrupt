#include "software_timer.h"	

// Variables
uint32_t g_totalSwTimer[NUMBER_OF_TIMERS] = {
	// Software Timer 1
	#ifdef NUMBER_OF_SW_TIMER1
	NUMBER_OF_SW_TIMER1
	#else
	0
	#endif
	,
	// Software Timer 2
	#ifdef NUMBER_OF_SW_TIMER2
	NUMBER_OF_SW_TIMER2
	#else
	0
	#endif
	,
	// Software Timer 3
	#ifdef NUMBER_OF_SW_TIMER3
	NUMBER_OF_SW_TIMER3
	#else
	0
	#endif
	,
	// Software Timer 4
	#ifdef NUMBER_OF_SW_TIMER4
	NUMBER_OF_SW_TIMER4
	#else
	0
	#endif
	,
	// Software Timer 5
	#ifdef NUMBER_OF_SW_TIMER5
	NUMBER_OF_SW_TIMER5
	#else
	0
	#endif
	,
	// Software Timer 6
	#ifdef NUMBER_OF_SW_TIMER6
	NUMBER_OF_SW_TIMER6
	#else
	0
	#endif
	,
	// Software Timer 7
	#ifdef NUMBER_OF_SW_TIMER7
	NUMBER_OF_SW_TIMER7
	#else
	0
	#endif
	,
	// Software Timer 8
	#ifdef NUMBER_OF_SW_TIMER8
	NUMBER_OF_SW_TIMER8
	#else
	0
	#endif
	,
	// Software Timer 9
	#ifdef NUMBER_OF_SW_TIMER9
	NUMBER_OF_SW_TIMER9
	#else
	0
	#endif
	,
	// Software Timer 10
	#ifdef NUMBER_OF_SW_TIMER10
	NUMBER_OF_SW_TIMER10
	#else
	0
	#endif
	,
	// Software Timer 11
	#ifdef NUMBER_OF_SW_TIMER11
	NUMBER_OF_SW_TIMER11
	#else
	0
	#endif
	,
	// Software Timer 12
	#ifdef NUMBER_OF_SW_TIMER12
	NUMBER_OF_SW_TIMER12
	#else
	0
	#endif
	,
	// Software Timer 13
	#ifdef NUMBER_OF_SW_TIMER13
	NUMBER_OF_SW_TIMER13
	#else
	0
	#endif
	,
	// Software Timer 14
	#ifdef NUMBER_OF_SW_TIMER14
	NUMBER_OF_SW_TIMER14
	#else
	0
	#endif
};

// Timer 1
#ifdef SW_TIMER1
SoftwareTimer g_softwareTimer1[NUMBER_OF_SW_TIMER1];
#endif

// Timer 2
#ifdef SW_TIMER2
SoftwareTimer g_softwareTimer2[NUMBER_OF_SW_TIMER2];
#endif

// Timer 3
#ifdef SW_TIMER3
SoftwareTimer g_softwareTimer3[NUMBER_OF_SW_TIMER3];
#endif

// Timer 4
#ifdef SW_TIMER4
SoftwareTimer g_softwareTimer4[NUMBER_OF_SW_TIMER4];
#endif

// Timer 5
#ifdef SW_TIMER5
SoftwareTimer g_softwareTimer5[NUMBER_OF_SW_TIMER5];
#endif

// Timer 6
#ifdef SW_TIMER6
SoftwareTimer g_softwareTimer6[NUMBER_OF_SW_TIMER6];
#endif

// Timer 7
#ifdef SW_TIMER7
SoftwareTimer g_softwareTimer7[NUMBER_OF_SW_TIMER7];
#endif

// Timer 8
#ifdef SW_TIMER8
SoftwareTimer g_softwareTimer8[NUMBER_OF_SW_TIMER8];
#endif

// Timer 9
#ifdef SW_TIMER9
SoftwareTimer g_softwareTimer9[NUMBER_OF_SW_TIMER9];
#endif

// Timer 10
#ifdef SW_TIMER10
SoftwareTimer g_softwareTimer10[NUMBER_OF_SW_TIMER10];
#endif

// Timer 11
#ifdef SW_TIMER11
SoftwareTimer g_softwareTimer11[NUMBER_OF_SW_TIMER11];
#endif

// Timer 12
#ifdef SW_TIMER12
SoftwareTimer g_softwareTimer12[NUMBER_OF_SW_TIMER12];
#endif

// Timer 13
#ifdef SW_TIMER13
SoftwareTimer g_softwareTimer13[NUMBER_OF_SW_TIMER13];
#endif

// Timer 14
#ifdef SW_TIMER14
SoftwareTimer g_softwareTimer14[NUMBER_OF_SW_TIMER14];
#endif

SoftwareTimer* g_timers[NUMBER_OF_TIMERS] = {
	// Software Timer 1
	#ifdef SW_TIMER1
	&g_softwareTimer1[0]
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
	&g_softwareTimer3[0]
	#else
	NULL
	#endif
	,
	// Software Timer 4
	#ifdef SW_TIMER4
	&g_softwareTimer4[0]
	#else
	NULL
	#endif
	,
	// Software Timer 5
	#ifdef SW_TIMER5
	&g_softwareTimer5[0]
	#else
	NULL
	#endif
	,
	// Software Timer 6
	#ifdef SW_TIMER6
	&g_softwareTimer6[0]
	#else
	NULL
	#endif
	,
	// Software Timer 7
	#ifdef SW_TIMER7
	&g_softwareTimer7[0]
	#else
	NULL
	#endif
	,
	// Software Timer 8
	#ifdef SW_TIMER8
	&g_softwareTimer8[0]
	#else
	NULL
	#endif
	,
	// Software Timer 9
	#ifdef SW_TIMER9
	&g_softwareTimer9[0]
	#else
	NULL
	#endif
	,
	// Software Timer 10
	#ifdef SW_TIMER10
	&g_softwareTimer10[0]
	#else
	NULL
	#endif
	,
	// Software Timer 11
	#ifdef SW_TIMER11
	&g_softwareTimer11[0]
	#else
	NULL
	#endif
	,
	// Software Timer 12
	#ifdef SW_TIMER12
	&g_softwareTimer12[0]
	#else
	NULL
	#endif
	,
	// Software Timer 13
	#ifdef SW_TIMER13
	&g_softwareTimer13[0]
	#else
	NULL
	#endif
	,
	// Software Timer 14
	#ifdef SW_TIMER14
	&g_softwareTimer14[0]
	#else
	NULL
	#endif
};

// Private Functions Definition
static int8_t checkSoftwareTimer(uint8_t timer){
	if (timer <= 0 || timer > NUMBER_OF_TIMERS || g_timers[timer-1] == NULL) {
		return -1;
	}
	
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
					--timer_ptr[i].repetition;
					if(timer_ptr[i].repetition > 0){
						setTimer(timer, &timer_ptr[i].duration, &i);
					}
				}
			}
		}
	}

	return 0;
}

// Global Functions Definition
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// Software Timer 1
	#ifdef SW_TIMER1
	if(htim->Instance == TIM1){
		// Handle TIM1 software timers
		checkSoftwareTimer(SW_TIMER1);
	}
	#endif

	// Software Timer 2
	#ifdef SW_TIMER2
	if(htim->Instance == TIM2){
		// Handle TIM2 software timers
		checkSoftwareTimer(SW_TIMER2);
	}
	#endif

	// Software Timer 3
	#ifdef SW_TIMER3
	if(htim->Instance == TIM3){
		// Handle TIM3 software timers
		checkSoftwareTimer(SW_TIMER3);
	}
	#endif

	// Software Timer 4
	#ifdef SW_TIMER4
	if(htim->Instance == TIM4){
		// Handle TIM4 software timers
		checkSoftwareTimer(SW_TIMER4);
	}
	#endif

	// Software Timer 5
	#ifdef SW_TIMER5
	if(htim->Instance == TIM5){
		// Handle TIM5 software timers
		checkSoftwareTimer(SW_TIMER5);
	}
	#endif

	// Software Timer 6
	#ifdef SW_TIMER6
	if(htim->Instance == TIM6){
		// Handle TIM6 software timers	
		checkSoftwareTimer(SW_TIMER6);
	}
	#endif

	// Software Timer 7
	#ifdef SW_TIMER7
	if(htim->Instance == TIM7){
		// Handle TIM7 software timers
		checkSoftwareTimer(SW_TIMER7);
	}
	#endif

	// Software Timer 8
	#ifdef SW_TIMER8
	if(htim->Instance == TIM8){
		// Handle TIM8 software timers
		checkSoftwareTimer(SW_TIMER8);
	}
	#endif

	// Software Timer 9
	#ifdef SW_TIMER9
	if(htim->Instance == TIM9){
		// Handle TIM9 software timers
		checkSoftwareTimer(SW_TIMER9);
	}
	#endif

	// Software Timer 10
	#ifdef SW_TIMER10
	if(htim->Instance == TIM10){
		// Handle TIM10 software timers
		checkSoftwareTimer(SW_TIMER10);
	}
	#endif

	// Software Timer 11
	#ifdef SW_TIMER11
	if(htim->Instance == TIM11){
		// Handle TIM11 software timers
		checkSoftwareTimer(SW_TIMER11);
	}
	#endif

	// Software Timer 12
	#ifdef SW_TIMER12
	if(htim->Instance == TIM12){
		// Handle TIM12 software timers
		checkSoftwareTimer(SW_TIMER12);
	}
	#endif

	// Software Timer 13
	#ifdef SW_TIMER13
	if(htim->Instance == TIM13){
		// Handle TIM13 software timers
		checkSoftwareTimer(SW_TIMER13);
	}
	#endif

	// Software Timer 14
	#ifdef SW_TIMER14
	if(htim->Instance == TIM14){
		// Handle TIM14 software timers
		checkSoftwareTimer(SW_TIMER14);
	}
	#endif
}

int8_t initSoftwareTimer(TIM_HandleTypeDef* htim){
	if(htim == NULL)
		return -1;
	HAL_TIM_Base_Start_IT(htim);
	return 0;
}

int8_t getFlag(uint8_t timer, uint32_t* sw_timer_index){
	if(timer <= 0 || timer > NUMBER_OF_TIMERS || g_timers[timer-1] == NULL)
		return -1;

	if(sw_timer_index == NULL || *sw_timer_index < 0 || *sw_timer_index >= g_totalSwTimer[timer-1]){
		return -1;
	}
	
	return g_timers[timer-1][*sw_timer_index].timer_flag;
}
	
int8_t resetFlag(uint8_t timer, uint32_t* sw_timer_index){
	if(timer <= 0 || timer > NUMBER_OF_TIMERS || g_timers[timer-1] == NULL)
		return -1;

	if(sw_timer_index == NULL || *sw_timer_index < 0 || *sw_timer_index >= g_totalSwTimer[timer-1]){
		return -1;
	}
	
	g_timers[timer-1][*sw_timer_index].timer_flag = 0;
	return 0;
}

int8_t setTimer(uint8_t timer, uint32_t* duration, int32_t* repetition, uint32_t* sw_timer_index){
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
	g_timers[timer-1][*sw_timer_index].repetition = (*repetition);

	return 0;
}

int8_t setRepetition(uint8_t timer, int32_t* repetition, uint32_t* sw_timer_index){
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



