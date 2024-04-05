#pragma once
#include "BAE_Def.h"

/* 
* For each loops in #defines:
* 
* FOR_A_IN(<loop length>, <before A>, <after A>, <separator>, <values (separated with ',' and must be same length as loop length)>)
* FOR_AA_IN(<loop length>, <before As>, <between As>, <after As>, <separator>, <values (separated with ',' and must be same length as loop length)>)
* FOR_AB_IN(<loop length>, <before A>, <between A and B>, <after B>, <separator>, <value pairs (elements (not pairs) separated with ',' and must be same length as loop length x 2)>)
* (spaces around ',' are trimmed)
* 
* eg. FOR_A_IN(3, float , = 2.0f;, , a, b, c)
*             
*              length of 3 | "float [a, b or c] = 2.0f;" | no separator | values...
*     FOR_A_IN(     3      ,  float      ,      = 2.0f;  ,              , a, b, c   )
*     =
*     float a = 2.0f; float b = 2.0f; float c = 2.0f;
* 
* eg. FOR_AB_IN(3, int , = ,;, , a, 1, b, 2, c, 3)
*             
*               length of 3 | "int [a, b or c] = [1, 2 or 3 (respectively)];" | no separator | values...
*     FOR_AB_IN(     3      ,  int      ,      =              ,            ;  ,              , a, b, c   )
*     =
*     int a = 1; int b = 2; int c = 3;
* 
* eg. FOR_AA_IN_NOSPACES(3, this->, = copyFrom.v,;, , a, b, c)
*             
*                        length of 3 | "this-> [a, b or c] = copyFrom.v [a, b or c (respectively)] ;" | no separator | values...
*     FOR_AA_IN_NOSPACES(     3      ,  this->      ,      = copyFrom.v             ,              ;  ,              , a, b, c   )
*     =
*     this->a=copyFrom.va; this->b=copyFrom.vb; this->c=copyFrom.vc;
*/

#if false
C# to get loops:
//string format = "v_ a{0} _v";
//string format = "v_ a{0} _v_ a{0} _v";
//string format = "v_ a{0} _v_ b{0} _v";
for(int i=1;i<=8;i++){string total="";for(int ii=1;ii<=i;ii++){if(ii>1)total+=" s ";total+=String.Format(format, ii);}Console.WriteLine(total);}
#endif

#define FOR_A_IN_1(v_,_v, s, a1)                      v_ a1 _v
#define FOR_A_IN_2(v_,_v, s, a1,a2)                   v_ a1 _v s v_ a2 _v
#define FOR_A_IN_3(v_,_v, s, a1,a2,a3)                v_ a1 _v s v_ a2 _v s v_ a3 _v
#define FOR_A_IN_4(v_,_v, s, a1,a2,a3,a4)             v_ a1 _v s v_ a2 _v s v_ a3 _v s v_ a4 _v
#define FOR_A_IN_5(v_,_v, s, a1,a2,a3,a4,a5)          v_ a1 _v s v_ a2 _v s v_ a3 _v s v_ a4 _v s v_ a5 _v
#define FOR_A_IN_6(v_,_v, s, a1,a2,a3,a4,a5,a6)       v_ a1 _v s v_ a2 _v s v_ a3 _v s v_ a4 _v s v_ a5 _v s v_ a6 _v
#define FOR_A_IN_7(v_,_v, s, a1,a2,a3,a4,a5,a6,a7)    v_ a1 _v s v_ a2 _v s v_ a3 _v s v_ a4 _v s v_ a5 _v s v_ a6 _v s v_ a7 _v
#define FOR_A_IN_8(v_,_v, s, a1,a2,a3,a4,a5,a6,a7,a8) v_ a1 _v s v_ a2 _v s v_ a3 _v s v_ a4 _v s v_ a5 _v s v_ a6 _v s v_ a7 _v s v_ a8 _v

#define FOR_A_IN(n, v_,_v, s, ...) FOR_A_IN_##n BRACKET_OPEN v_,_v, s, __VA_ARGS__ BRACKET_CLOSE

#define FOR_AA_IN_1(v_,_v_,_v, s, a1)                      v_ a1 _v_ a1 _v
#define FOR_AA_IN_2(v_,_v_,_v, s, a1,a2)                   v_ a1 _v_ a1 _v s v_ a2 _v_ a2 _v
#define FOR_AA_IN_3(v_,_v_,_v, s, a1,a2,a3)                v_ a1 _v_ a1 _v s v_ a2 _v_ a2 _v s v_ a3 _v_ a3 _v
#define FOR_AA_IN_4(v_,_v_,_v, s, a1,a2,a3,a4)             v_ a1 _v_ a1 _v s v_ a2 _v_ a2 _v s v_ a3 _v_ a3 _v s v_ a4 _v_ a4 _v
#define FOR_AA_IN_5(v_,_v_,_v, s, a1,a2,a3,a4,a5)          v_ a1 _v_ a1 _v s v_ a2 _v_ a2 _v s v_ a3 _v_ a3 _v s v_ a4 _v_ a4 _v s v_ a5 _v_ a5 _v
#define FOR_AA_IN_6(v_,_v_,_v, s, a1,a2,a3,a4,a5,a6)       v_ a1 _v_ a1 _v s v_ a2 _v_ a2 _v s v_ a3 _v_ a3 _v s v_ a4 _v_ a4 _v s v_ a5 _v_ a5 _v s v_ a6 _v_ a6 _v
#define FOR_AA_IN_7(v_,_v_,_v, s, a1,a2,a3,a4,a5,a6,a7)    v_ a1 _v_ a1 _v s v_ a2 _v_ a2 _v s v_ a3 _v_ a3 _v s v_ a4 _v_ a4 _v s v_ a5 _v_ a5 _v s v_ a6 _v_ a6 _v s v_ a7 _v_ a7 _v
#define FOR_AA_IN_8(v_,_v_,_v, s, a1,a2,a3,a4,a5,a6,a7,a8) v_ a1 _v_ a1 _v s v_ a2 _v_ a2 _v s v_ a3 _v_ a3 _v s v_ a4 _v_ a4 _v s v_ a5 _v_ a5 _v s v_ a6 _v_ a6 _v s v_ a7 _v_ a7 _v s v_ a8 _v_ a8 _v

#define FOR_AA_IN(n, v_,_v_,_v, s, ...) FOR_AA_IN_##n BRACKET_OPEN v_,_v_,_v, s, __VA_ARGS__ BRACKET_CLOSE

#define FOR_AB_IN_1(v_,_v_,_v, s, a1,b1)                                           v_ a1 _v_ b1 _v
#define FOR_AB_IN_2(v_,_v_,_v, s, a1,b1,a2,b2)                                     v_ a1 _v_ b1 _v s v_ a2 _v_ b2 _v
#define FOR_AB_IN_3(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3)                               v_ a1 _v_ b1 _v s v_ a2 _v_ b2 _v s v_ a3 _v_ b3 _v
#define FOR_AB_IN_4(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4)                         v_ a1 _v_ b1 _v s v_ a2 _v_ b2 _v s v_ a3 _v_ b3 _v s v_ a4 _v_ b4 _v
#define FOR_AB_IN_5(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4,a5,b5)                   v_ a1 _v_ b1 _v s v_ a2 _v_ b2 _v s v_ a3 _v_ b3 _v s v_ a4 _v_ b4 _v s v_ a5 _v_ b5 _v
#define FOR_AB_IN_6(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6)             v_ a1 _v_ b1 _v s v_ a2 _v_ b2 _v s v_ a3 _v_ b3 _v s v_ a4 _v_ b4 _v s v_ a5 _v_ b5 _v s v_ a6 _v_ b6 _v
#define FOR_AB_IN_7(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6,a7,b7)       v_ a1 _v_ b1 _v s v_ a2 _v_ b2 _v s v_ a3 _v_ b3 _v s v_ a4 _v_ b4 _v s v_ a5 _v_ b5 _v s v_ a6 _v_ b6 _v s v_ a7 _v_ b7 _v
#define FOR_AB_IN_8(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6,a7,b7,a8,b8) v_ a1 _v_ b1 _v s v_ a2 _v_ b2 _v s v_ a3 _v_ b3 _v s v_ a4 _v_ b4 _v s v_ a5 _v_ b5 _v s v_ a6 _v_ b6 _v s v_ a7 _v_ b7 _v s v_ a8 _v_ b8 _v

#define FOR_AB_IN(n, v_,_v_,_v, s, ...) FOR_AB_IN_##n BRACKET_OPEN v_,_v_,_v, s, __VA_ARGS__ BRACKET_CLOSE


#define FOR_A_IN_1_NOSPACE(v_,_v, s, a1)                      v_##a1##_v
#define FOR_A_IN_2_NOSPACE(v_,_v, s, a1,a2)                   v_##a1##_v##s##v_##a2##_v
#define FOR_A_IN_3_NOSPACE(v_,_v, s, a1,a2,a3)                v_##a1##_v##s##v_##a2##_v##s##v_##a3##_v
#define FOR_A_IN_4_NOSPACE(v_,_v, s, a1,a2,a3,a4)             v_##a1##_v##s##v_##a2##_v##s##v_##a3##_v##s##v_##a4##_v
#define FOR_A_IN_5_NOSPACE(v_,_v, s, a1,a2,a3,a4,a5)          v_##a1##_v##s##v_##a2##_v##s##v_##a3##_v##s##v_##a4##_v##s##v_##a5##_v
#define FOR_A_IN_6_NOSPACE(v_,_v, s, a1,a2,a3,a4,a5,a6)       v_##a1##_v##s##v_##a2##_v##s##v_##a3##_v##s##v_##a4##_v##s##v_##a5##_v##s##v_##a6##_v
#define FOR_A_IN_7_NOSPACE(v_,_v, s, a1,a2,a3,a4,a5,a6,a7)    v_##a1##_v##s##v_##a2##_v##s##v_##a3##_v##s##v_##a4##_v##s##v_##a5##_v##s##v_##a6##_v##s##v_##a7##_v
#define FOR_A_IN_8_NOSPACE(v_,_v, s, a1,a2,a3,a4,a5,a6,a7,a8) v_##a1##_v##s##v_##a2##_v##s##v_##a3##_v##s##v_##a4##_v##s##v_##a5##_v##s##v_##a6##_v##s##v_##a7##_v##s##v_##a8##_v

#define FOR_A_IN_NOSPACE(n, v_,_v, s, ...) FOR_A_IN_##n##_NOSPACE BRACKET_OPEN v_,_v, s, __VA_ARGS__ BRACKET_CLOSE

#define FOR_AA_IN_1_NOSPACE(v_,_v_,_v, s, a1)                      v_##a1##_v_##a1##_v
#define FOR_AA_IN_2_NOSPACE(v_,_v_,_v, s, a1,a2)                   v_##a1##_v_##a1##_v##s##v_##a2##_v_##a2##_v
#define FOR_AA_IN_3_NOSPACE(v_,_v_,_v, s, a1,a2,a3)                v_##a1##_v_##a1##_v##s##v_##a2##_v_##a2##_v##s##v_##a3##_v_##a3##_v
#define FOR_AA_IN_4_NOSPACE(v_,_v_,_v, s, a1,a2,a3,a4)             v_##a1##_v_##a1##_v##s##v_##a2##_v_##a2##_v##s##v_##a3##_v_##a3##_v##s##v_##a4##_v_##a4##_v
#define FOR_AA_IN_5_NOSPACE(v_,_v_,_v, s, a1,a2,a3,a4,a5)          v_##a1##_v_##a1##_v##s##v_##a2##_v_##a2##_v##s##v_##a3##_v_##a3##_v##s##v_##a4##_v_##a4##_v##s##v_##a5##_v_##a5##_v
#define FOR_AA_IN_6_NOSPACE(v_,_v_,_v, s, a1,a2,a3,a4,a5,a6)       v_##a1##_v_##a1##_v##s##v_##a2##_v_##a2##_v##s##v_##a3##_v_##a3##_v##s##v_##a4##_v_##a4##_v##s##v_##a5##_v_##a5##_v##s##v_##a6##_v_##a6##_v
#define FOR_AA_IN_7_NOSPACE(v_,_v_,_v, s, a1,a2,a3,a4,a5,a6,a7)    v_##a1##_v_##a1##_v##s##v_##a2##_v_##a2##_v##s##v_##a3##_v_##a3##_v##s##v_##a4##_v_##a4##_v##s##v_##a5##_v_##a5##_v##s##v_##a6##_v_##a6##_v##s##v_##a7##_v_##a7##_v
#define FOR_AA_IN_8_NOSPACE(v_,_v_,_v, s, a1,a2,a3,a4,a5,a6,a7,a8) v_##a1##_v_##a1##_v##s##v_##a2##_v_##a2##_v##s##v_##a3##_v_##a3##_v##s##v_##a4##_v_##a4##_v##s##v_##a5##_v_##a5##_v##s##v_##a6##_v_##a6##_v##s##v_##a7##_v_##a7##_v##s##v_##a8##_v_##a8##_v

#define FOR_AA_IN_NOSPACE(n, v_,_v_,_v, s, ...) FOR_AA_IN_##n##_NOSPACE BRACKET_OPEN v_,_v_,_v, s, __VA_ARGS__ BRACKET_CLOSE

#define FOR_AB_IN_1_NOSPACE(v_,_v_,_v, s, a1,b1)                                           v_##a1##_v_##b1##_v
#define FOR_AB_IN_2_NOSPACE(v_,_v_,_v, s, a1,b1,a2,b2)                                     v_##a1##_v_##b1##_v##s##v_##a2##_v_##b2##_v
#define FOR_AB_IN_3_NOSPACE(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3)                               v_##a1##_v_##b1##_v##s##v_##a2##_v_##b2##_v##s##v_##a3##_v_##b3##_v
#define FOR_AB_IN_4_NOSPACE(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4)                         v_##a1##_v_##b1##_v##s##v_##a2##_v_##b2##_v##s##v_##a3##_v_##b3##_v##s##v_##a4##_v_##b4##_v
#define FOR_AB_IN_5_NOSPACE(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4,a5,b5)                   v_##a1##_v_##b1##_v##s##v_##a2##_v_##b2##_v##s##v_##a3##_v_##b3##_v##s##v_##a4##_v_##b4##_v##s##v_##a5##_v_##b5##_v
#define FOR_AB_IN_6_NOSPACE(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6)             v_##a1##_v_##b1##_v##s##v_##a2##_v_##b2##_v##s##v_##a3##_v_##b3##_v##s##v_##a4##_v_##b4##_v##s##v_##a5##_v_##b5##_v##s##v_##a6##_v_##b6##_v
#define FOR_AB_IN_7_NOSPACE(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6,a7,b7)       v_##a1##_v_##b1##_v##s##v_##a2##_v_##b2##_v##s##v_##a3##_v_##b3##_v##s##v_##a4##_v_##b4##_v##s##v_##a5##_v_##b5##_v##s##v_##a6##_v_##b6##_v##s##v_##a7##_v_##b7##_v
#define FOR_AB_IN_8_NOSPACE(v_,_v_,_v, s, a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6,a7,b7,a8,b8) v_##a1##_v_##b1##_v##s##v_##a2##_v_##b2##_v##s##v_##a3##_v_##b3##_v##s##v_##a4##_v_##b4##_v##s##v_##a5##_v_##b5##_v##s##v_##a6##_v_##b6##_v##s##v_##a7##_v_##b7##_v##s##v_##a8##_v_##b8##_v

#define FOR_AB_IN_NOSPACE(n, v_,_v_,_v, s, ...) FOR_AB_IN_##n##_NOSPACE BRACKET_OPEN v_,_v_,_v, s, __VA_ARGS__ BRACKET_CLOSE