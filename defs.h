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

//时间单位转换
#define NS 1UL
#define US 1000UL
#define MS 1000000UL

//频率单位转换
#define HZ 1UL
#define KHZ 1000UL
#define MHZ 1000000UL


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

#define UL(X) XGLUB(X, UL)

//==============REDUCE宏================
#define R1_(OP, V1)														OP(V1)
#define R2_(OP, V1, V2)                       OP(V1, V2)
#define R3_(OP, V1, V2, V3) 									OP(OP(V1, V2), V3)
#define R4_(OP, V1, V2, V3, V4) 							OP(R3_(OP, V1, V2, V3), V4)
#define R5_(OP, V1, V2, V3, V4, V5) 					OP(R4_(OP, V1, V2, V3, V4), V5)
#define R6_(OP, V1, V2, V3, V4, V5, V6) 			OP(R5_(OP, V1, V2, V3, V4, V5), V6)



#endif