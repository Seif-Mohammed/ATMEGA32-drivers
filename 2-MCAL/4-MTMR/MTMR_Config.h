#ifndef MTMR_CONFIG_H_
#define MTMR_CONFIG_H_

/*Choose config timer mode
 * 1-MTMR_U8_TMR0_NormalMode
 * 2-MTMR_U8_TMR0_CTCMode
   3-MTMR_U8_TMRO_FastPWM
   4-MTMR_U8_TMRO_PhaseCorrectPWM*/
#define MTMR_U8_TimerMode 				MTMR_U8_TMRO_PhaseCorrectPWM
#define MTMR_U8_TMRO_PreLoadValue		192

#endif /* MTMR_CONFIG_H_ */
