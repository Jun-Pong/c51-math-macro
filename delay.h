#ifndef __DELAY_H__
#define __DELAY_H__

#include "config.h"

	#if defined(ARCH_C51)
			#include <REGX52.H>
			#include <intrins.h>
			
			#define PRIVATE_NOP_1()      _nop_()
			#define PRIVATE_NOP_2()      PRIVATE_NOP_1(); _nop_()
			#define PRIVATE_NOP_3()      PRIVATE_NOP_2(); _nop_()
			#define PRIVATE_NOP_4()      PRIVATE_NOP_3(); _nop_()
			#define PRIVATE_NOP_5()      PRIVATE_NOP_4(); _nop_()
			
			#define PRIVATE_NOP_GLUE(N)  PRIVATE_NOP_##N()
			#define MCU_GENERATE_NOP(N)  PRIVATE_NOP_GLUE(N)
	#endif

	#if defined(MCU_STC89_12T_11M)
	
			#define MCU_BIT_OPT_CYCLES	2
	
			/**===============纳秒补偿延时器===================================== */
			
			//12T单片机， 11.0592MHz，1个周期约1085ns
			#define CYCLE_NS	1085
			#define MCU_DELAY_OFFSET_TIME(N, DELAY_TIME) (DELAY_TIME - (N * CYCLE_NS))
			#define MCU_DELAY_NS_OFFSET(N, DELAY_TIME)	\
				do { \
					typedef char ERROR_GAP_TOO_LARGE[ (MCU_DELAY_OFFSET_TIME(N, DELAY_TIME) <= 5000) ? 1 : -1 ]; \
					\
					if (MCU_DELAY_OFFSET_TIME(N, DELAY_TIME) <= 0){}	\
					else if ((MCU_DELAY_OFFSET_TIME(N, DELAY_TIME) - (CYCLE_NS * 1)) <= 0) {MCU_GENERATE_NOP(1);} \
					else if ((MCU_DELAY_OFFSET_TIME(N, DELAY_TIME) - (CYCLE_NS * 2)) <= 0) {MCU_GENERATE_NOP(2);} \
					else if ((MCU_DELAY_OFFSET_TIME(N, DELAY_TIME) - (CYCLE_NS * 3)) <= 0) {MCU_GENERATE_NOP(3);} \
					else if ((MCU_DELAY_OFFSET_TIME(N, DELAY_TIME) - (CYCLE_NS * 4)) <= 0) {MCU_GENERATE_NOP(4);} \
					else if ((MCU_DELAY_OFFSET_TIME(N, DELAY_TIME) - (CYCLE_NS * 5)) <= 0) {MCU_GENERATE_NOP(5);} \
				} while (0)
			
			
			/**===============微秒补偿延时器===================================== */
			//微秒转纳秒
			#define US_TO_NS(N) MUL_T(u16, N, 1000)
			
			//以36轮（39US）为一个大周期， 输入X US时，算出 X/39（大周期）， X%39（剩余时间）
			#define CT 36
				
			//36个周期近似39微秒	
			#define CT_APPX 39
				
			//36周期当作39微秒产生的误差:39060 - 39000 = 60NS
			#define CT_OFFSET 60
				
			//大周期数（单位：周期)
			#define DE_TD(US_TIME) MUL(CT, DIV(US_TIME, CT_APPX))
				
			//计算剩余时间并转换成纳秒
			#define DE_TM_NS(US_TIME) US_TO_NS(REM(US_TIME, CT_APPX))
				
				//N个36周期积累的误差值 N * CT_OFFSET（NS）
			#define CTN_NS_OFF(US_TIME) MUL(DIV(US_TIME, CT_APPX), CT_OFFSET)
	
			//减去指令自身N个周期开销
			#define D_TIME(N, US_OFF_TIME) SUB(US_TO_NS(US_OFF_TIME), MUL(N, CYCLE_NS))
			
			//这里需要计算余数(DE_TM - CTN_NS_OFF) / T;
			//有可能整型溢出，因此使用数学公式变形：TICK_RATE(X/T) = ((X + T) / T) - 1 
			#define NEED_US_TIME(US_TIME) TICK_RATE(	SUB(DE_TM_NS(US_TIME), \
																										CTN_NS_OFF(US_TIME)), \
																								CYCLE_NS)																				
      //COND(E, T, F) 三目运算符E ? T :	F		
			#define ALL_TIME(N, US_TIME)	COND( \
																				GT(ADD(DE_TD(US_TIME), NEED_US_TIME(US_TIME)), N + 1), \
																				SUB(ADD(DE_TD(US_TIME), NEED_US_TIME(US_TIME)), N + 1), \
																				0)
			
			#define MCU_DELAY_US_OFFSET(N, US_TIME) \
				do{ \
					if(ALL_TIME(N, US_TIME) >= 2) { \
						DOOV( \
								IFF(CHECK_BIT(ALL_TIME(N, US_TIME), 0), \
									_nop_(), {}), \
								DIV(ALL_TIME(N, US_TIME), 2)); \
					} else if (ALL_TIME(N, US_TIME) == 1) {_nop_();} \
				} while (0)
				
			#define DOOV(CODE, VAL) \
			do { \
				u8 data i = VAL; \
				{CODE;} \
				do { \
				} while (--i); \
			} while (0)
				
			/**===============毫秒常量延时器===================================== */		
				
			#define DELAY_MS_IX(ms) (((ms)-2)/255 + 1)
			#define DELAY_MS_JX(ms) (((ms)-2)%255 + 1)
			/* KX = 255 - IX + 1 = ~IX + 1 = -IX */ 
			#define DELAY_MS_KX(ms) ((unsigned char)(-(DELAY_MS_IX(ms))))

			#define DELAY_MS(ms) do { \
					if ((ms) >= 2) \
					{ \
						Delay_1ms_core_plus( \
						DELAY_MS_IX(ms), \
						DELAY_MS_JX(ms), \
						DELAY_MS_KX(ms) \
						); \
					} else if ((ms) == 1) \
					{ \
						Delay_1ms_core_plus(1, 1, 24); \
					} \
				} while (0)

			void Delay_1ms_core_plus(unsigned char ix, unsigned char jx, unsigned char kx);
			
	#elif defined(MCU_STC8_1T_24M)
			//1T单片机，24MHz，1个周期约为41.6ns
			#define MCU_DELAY_35NS()
			#define MCU_DELAY_1CYCLE()	do { _nop_(); } while (0)
	#endif
			
#endif