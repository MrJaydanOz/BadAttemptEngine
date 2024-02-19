#pragma once

#define FOR_ELEMENT(v) v

#define FOR_A_2_NOSPACE(a1, a2, v_, _v, s) \
	FOR_ELEMENT(v_##a1##_v)##s##\
	FOR_ELEMENT(v_##a2##_v)
#define FOR_A_3_NOSPACE(a1, a2, a3, v_, _v, s) \
	FOR_ELEMENT(v_##a1##_v)##s##\
	FOR_ELEMENT(v_##a2##_v)##s##\
	FOR_ELEMENT(v_##a3##_v)
#define FOR_A_4_NOSPACE(a1, a2, a3, a4, v_, _v, s) \
	FOR_ELEMENT(v_##a1##_v)##s##\
	FOR_ELEMENT(v_##a2##_v)##s##\
	FOR_ELEMENT(v_##a3##_v)##s##\
	FOR_ELEMENT(v_##a4##_v)

#define FOR_AA_2_NOSPACE(a1, a2, v_, _v_, _v, s) \
	FOR_ELEMENT(v_##a1##_v_##a1##_v)##s##\
	FOR_ELEMENT(v_##a2##_v_##a2##_v)
#define FOR_AA_3_NOSPACE(a1, a2, a3, v_, _v_, _v, s) \
	FOR_ELEMENT(v_##a1##_v_##a1##_v)##s##\
	FOR_ELEMENT(v_##a2##_v_##a2##_v)##s##\
	FOR_ELEMENT(v_##a3##_v_##a3##_v)
#define FOR_AA_4_NOSPACE(a1, a2, a3, a4, v_, _v_, _v, s) \
	FOR_ELEMENT(v_##a1##_v_##a1##_v)##s##\
	FOR_ELEMENT(v_##a2##_v_##a2##_v)##s##\
	FOR_ELEMENT(v_##a3##_v_##a3##_v)##s##\
	FOR_ELEMENT(v_##a4##_v_##a4##_v)

#define FOR_AB_2_NOSPACE(a1, b1, a2, b2, v_, _v_, _v, s) \
	FOR_ELEMENT(v_##a1##_v_##b1##_v)##s##\
	FOR_ELEMENT(v_##a2##_v_##b2##_v)
#define FOR_AB_3_NOSPACE(a1, b1, a2, b2, a3, b3, v_, _v_, _v, s) \
	FOR_ELEMENT(v_##a1##_v_##b1##_v)##s##\
	FOR_ELEMENT(v_##a2##_v_##b2##_v)##s##\
	FOR_ELEMENT(v_##a3##_v_##b3##_v)
#define FOR_AB_4_NOSPACE(a1, b1, a2, b2, a3, b3, a4, b4, v_, _v_, _v, s) \
	FOR_ELEMENT(v_##a1##_v_##b1##_v)##s##\
	FOR_ELEMENT(v_##a2##_v_##b2##_v)##s##\
	FOR_ELEMENT(v_##a3##_v_##b3##_v)##s##\
	FOR_ELEMENT(v_##a4##_v_##b4##_v)

#define FOR_A_2(a1, a2, v_, _v, s) \
	FOR_ELEMENT(v_ a1 _v) s \
	FOR_ELEMENT(v_ a2 _v)
#define FOR_A_3(a1, a2, a3, v_, _v, s) \
	FOR_ELEMENT(v_ a1 _v) s \
	FOR_ELEMENT(v_ a2 _v) s \
	FOR_ELEMENT(v_ a3 _v)
#define FOR_A_4(a1, a2, a3, a4, v_, _v, s) \
	FOR_ELEMENT(v_ a1 _v) s \
	FOR_ELEMENT(v_ a2 _v) s \
	FOR_ELEMENT(v_ a3 _v) s \
	FOR_ELEMENT(v_ a4 _v)

#define FOR_AA_2(a1, a2, v_, _v_, _v, s) \
	FOR_ELEMENT(v_ a1 _v_ a1 _v) s \
	FOR_ELEMENT(v_ a2 _v_ a2 _v)
#define FOR_AA_3(a1, a2, a3, v_, _v_, _v, s) \
	FOR_ELEMENT(v_ a1 _v_ a1 _v) s \
	FOR_ELEMENT(v_ a2 _v_ a2 _v) s \
	FOR_ELEMENT(v_ a3 _v_ a3 _v)
#define FOR_AA_4(a1, a2, a3, a4, v_, _v_, _v, s) \
	FOR_ELEMENT(v_ a1 _v_ a1 _v) s \
	FOR_ELEMENT(v_ a2 _v_ a2 _v) s \
	FOR_ELEMENT(v_ a3 _v_ a3 _v) s \
	FOR_ELEMENT(v_ a4 _v_ a4 _v)

#define FOR_AB_2(a1, b1, a2, b2, v_, _v_, _v, s) \
	FOR_ELEMENT(v_ a1 _v_ b1 _v) s \
	FOR_ELEMENT(v_ a2 _v_ b2 _v)
#define FOR_AB_3(a1, b1, a2, b2, a3, b3, v_, _v_, _v, s) \
	FOR_ELEMENT(v_ a1 _v_ b1 _v) s \
	FOR_ELEMENT(v_ a2 _v_ b2 _v) s \
	FOR_ELEMENT(v_ a3 _v_ b3 _v)
#define FOR_AB_4(a1, b1, a2, b2, a3, b3, a4, b4, v_, _v_, _v, s) \
	FOR_ELEMENT(v_ a1 _v_ b1 _v) s \
	FOR_ELEMENT(v_ a2 _v_ b2 _v) s \
	FOR_ELEMENT(v_ a3 _v_ b3 _v) s \
	FOR_ELEMENT(v_ a4 _v_ b4 _v)