#pragma once

#include "EntityStructs.h"
#include "OptionsManager.h"

#define M_PI		3.14159265358979323846f
#define M_PI_F		((float)(M_PI))
#define DEG2RAD(x)  ((float)(x) * (float)(M_PI_F / 180.f))
#define RAD2DEG(x)	((float)(x) * (float)(180.f / M_PI_F))
#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10

class Utilities {
public:
	static bool W2S(const SSDK::Vector& v3D, SSDK::Vector& v2D);
	static SSDK::Vector GetEntityBone(CBaseEntity* pEntity, int iBone);
	static void VectorTransform(SSDK::Vector& in1, SSDK::matrix3x4a_t& in2, SSDK::Vector &out);
	static void SinCos(float radians, float *sine, float *cosine);
	static void AngleVectors(const SSDK::QAngle &angles, SSDK::Vector *forward);
	static void AngleVectors(const SSDK::QAngle &angles, SSDK::Vector *forward, SSDK::Vector *right, SSDK::Vector *up);
	static void VectorAngles1(const SSDK::Vector& forward, SSDK::QAngle &angles);
	static void VectorAngles(const SSDK::Vector& forward, SSDK::QAngle &angles);
	static SSDK::QAngle CalcAngle(SSDK::Vector src, SSDK::Vector dst);
	static bool Clamp(SSDK::QAngle &angles);
	static void Normalize(SSDK::QAngle& angle);
	static void Normalize(float& angle);
	static void ClampAngles(SSDK::QAngle &angles);

	static SSDK::Vector extrapolateTick(SSDK::Vector p0, CBaseEntity* ent);

	static void SetClanTag(const char* tag, const char* name);
	static bool LineThroughSmoke(SSDK::Vector loc, SSDK::Vector rem);
	static void marquee(std::string& panicova_zlomena_noha);

	static float RandomFloat(float min, float max);
	static void RandomSeed(int iSeed);

	template< class T, class Y >
	static T ClampValue(T const &val, Y const &minVal, Y const &maxVal);

	static float GetInterp();
	static float GetNetworkLatency();
};