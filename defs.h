#ifndef DEFS_H__
#define DEFS_H__

#include "config.h"

//==============胶水宏==================
#define GLUB(A, B) A##B
#define XGLUB(A, B) GLUB(A, B)

//类型定义
typedef unsigned char u8;
typedef unsigned int u16;

typedef signed char s8;
typedef signed int s16;

//时间单位
#define _NS 1UL
#define _US 1000UL
#define _MS 1000000UL

//频率单位
#define _HZ 1UL
#define _KHZ 1000UL
#define _MHZ 1000000UL

//=========类型转换====================
#define CA(T, V) 												((T)(V))
#define CAP(T, OP, V) 									CA(T, OP(CA(T, V)))
#define CAP2(T, OP, V1, V2) 						CA(T, OP(CA(T, V1), CA(T, V2)))
#define CAP3(T, OP, V1, V2, V3) 				CA(T, OP(CA(T, V1), CA(T, V2), CA(T, V3)))
#define CAP4(T, OP, V1, V2, V3, V4) 		CA(T, OP(CA(T, V1), CA(T, V2), CA(T, V3), CA(T, V4)))
#define CAP5(T, OP, V1, V2, V3, V4, V5) CA(T, OP(CA(T, V1), CA(T, V2), CA(T, V3), CA(T, V4), CA(T, V5)))
#define U8(OP, V) 											CAP(u8, OP, V)
#define U8_2(OP, V1, V2) 								CAP2(u8, OP, V1, V2)
#define U8_3(OP, V1, V2, V3) 						CAP3(u8, OP, V1, V2, V3)
#define U8_4(OP, V1, V2, V3, V4) 				CAP4(u8, OP, V1, V2, V3, V4)
#define U8_5(OP, V1, V2, V3, V4, V5) 		CAP5(u8, OP, V1, V2, V3, V4, V5)
#define U16(OP, V) 											CAP(u16, OP, V)
#define U16_2(OP, V1, V2) 							CAP2(u16, OP, V1, V2)
#define U16_3(OP, V1, V2, V3) 					CAP3(u16, OP, V1, V2, V3)
#define U16_4(OP, V1, V2, V3, V4) 			CAP4(u16, OP, V1, V2, V3, V4)
#define U16_5(OP, V1, V2, V3, V4, V5) 	CAP5(u16, OP, V1, V2, V3, V4, V5)
#define S8(OP, V) 											CAP(s8, OP, V)
#define S8_2(OP, V1, V2) 								CAP2(s8, OP, V1, V2)
#define S8_3(OP, V1, V2, V3) 						CAP3(s8, OP, V1, V2, V3)
#define S8_4(OP, V1, V2, V3, V4) 				CAP4(s8, OP, V1, V2, V3, V4)
#define S8_5(OP, V1, V2, V3, V4, V5) 		CAP5(s8, OP, V1, V2, V3, V4, V5)
#define S16(OP, V) 											CAP(s16, OP, V)
#define S16_2(OP, V1, V2) 							CAP2(s16, OP, V1, V2)
#define S16_3(OP, V1, V2, V3) 					CAP3(s16, OP, V1, V2, V3)
#define S16_4(OP, V1, V2, V3, V4) 			CAP4(s16, OP, V1, V2, V3, V4)
#define S16_5(OP, V1, V2, V3, V4, V5) 	CAP5(s16, OP, V1, V2, V3, V4, V5)

#define UL(X) ((unsigned long)(X))

//==============REDUCE================
#define R1_(OP, V1)														OP(V1)
#define R2_(OP, V1, V2)                       OP(V1, V2)
#define R3_(OP, V1, V2, V3) 									OP(OP(V1, V2), V3)
#define R4_(OP, V1, V2, V3, V4) 							OP(R3_(OP, V1, V2, V3), V4)
#define R5_(OP, V1, V2, V3, V4, V5) 					OP(R4_(OP, V1, V2, V3, V4), V5)
#define R6_(OP, V1, V2, V3, V4, V5, V6) 			OP(R5_(OP, V1, V2, V3, V4, V5), V6)

//==============延时==================
#define NOP_1()      _nop_()
#define NOP_2()      NOP_1(); _nop_()
#define NOP_3()      NOP_2(); _nop_()
#define NOP_4()      NOP_3(); _nop_()
#define NOP_5()      NOP_4(); _nop_()

#define NOP_BURST(N) XGLUB(NOP_, N)()

// ==========================================================
// 预处理器路由表：频率单位 (HZ, KHZ, MHZ)
// 命名规范：U1_U2_MIN -> 返回较小的单位标签
// ==========================================================
#define HZ_HZ_MIN       HZ
#define HZ_KHZ_MIN      HZ
#define HZ_MHZ_MIN      HZ

#define KHZ_HZ_MIN      HZ
#define KHZ_KHZ_MIN     KHZ
#define KHZ_MHZ_MIN     KHZ

#define MHZ_HZ_MIN      HZ
#define MHZ_KHZ_MIN     KHZ
#define MHZ_MHZ_MIN     MHZ

// ==========================================================
// 预处理器路由表：时间单位 (NS, US, MS)
// 命名规范：U1_U2_MIN -> 返回较小的单位标签
// ==========================================================
#define NS_NS_MIN       NS
#define NS_US_MIN       NS
#define NS_MS_MIN       NS

#define US_NS_MIN       NS
#define US_US_MIN       US
#define US_MS_MIN       US

#define MS_NS_MIN       NS
#define MS_US_MIN       US
#define MS_MS_MIN       MS

//===============TYPE UNIT====================
//=====时间=====
#define U_NS(X) 		NS
#define U_US(X) 		US
#define U_MS(X) 		MS

#define V_NS(X) 		UL(X)
#define V_US(X) 		UL(X)
#define V_MS(X) 		UL(X)

//=====频率=====
#define U_HZ(X) 		HZ
#define U_KHZ(X) 		KHZ
#define U_MHZ(X) 		MHZ

#define V_HZ(X) 		UL(X)
#define V_KHZ(X) 		UL(X)
#define V_MHZ(X) 		UL(X)


//===============BIT MASK=====================
#define MASK1(V)        																							_B(V)
#define MASK2(V1, V2)        							MASK1(V1) 								| _B(V2)
#define MASK3(V1, V2, V3)        					MASK2(V1, V2) 						| _B(V3)
#define MASK4(V1, V2, V3, V4)        			MASK3(V1, V2, V3) 				| _B(V4)
#define MASK5(V1, V2, V3, V4, V5)        	MASK4(V1, V2, V3, V4) 		| _B(V5)
#define MASK6(V1, V2, V3, V4, V5, V6)     MASK5(V1, V2, V3, V4, V5) | _B(V6)

//==============TYPE BIT=======================
#define P_BIT0(X) (0)
#define P_BIT1(X) (1)
#define P_BIT2(X) (2)
#define P_BIT3(X) (3)
#define P_BIT4(X) (4)
#define P_BIT5(X) (5)
#define P_BIT6(X) (6)
#define P_BIT7(X) (7)

#define V_BIT0(X) (X)
#define V_BIT1(X) (X)
#define V_BIT2(X) (X)
#define V_BIT3(X) (X)
#define V_BIT4(X) (X)
#define V_BIT5(X) (X)
#define V_BIT6(X) (X)
#define V_BIT7(X) (X)

#define BITP(B) (XGLUB(P_, B))
#define BITV(B) (XGLUB(V_, B))


#endif