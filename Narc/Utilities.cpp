#include "Utilities.h"

#include <math.h>

bool Utilities::W2S(const SSDK::Vector& v3D, SSDK::Vector& v2D) {
	return (SSDK::I::DebugOverlay()->ScreenPosition(v3D, v2D) != 1);
}

SSDK::Vector Utilities::GetEntityBone(CBaseEntity* pEntity, int iBone) {
	SSDK::matrix3x4_t boneMatrix[128];

	if (!pEntity->SetupBones(boneMatrix, 128, 256, SSDK::I::Engine()->GetLastTimeStamp()))
		return SSDK::Vector();

	SSDK::matrix3x4_t hitbox = boneMatrix[iBone];

	return SSDK::Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
}

void Utilities::VectorTransform(SSDK::Vector& in1, SSDK::matrix3x4a_t& in2, SSDK::Vector &out) {
	out.x = in1.Dot(in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
	out.y = in1.Dot(in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
	out.z = in1.Dot(in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
}

void Utilities::SinCos(float radians, float *sine, float *cosine) {
	*sine = sin(radians);
	*cosine = cos(radians);
}

void Utilities::AngleVectors(const SSDK::QAngle &angles, SSDK::Vector *forward) {
	float sp, sy, cp, cy;

	SinCos(DEG2RAD(angles[SSDK::MathThings::YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[SSDK::MathThings::PITCH]), &sp, &cp);

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

void Utilities::marquee(std::string& panicova_zlomena_noha)
{
	std::string temp_string = panicova_zlomena_noha;
	panicova_zlomena_noha.erase(0, 1);
	panicova_zlomena_noha += temp_string[0];
}

void Utilities::AngleVectors(const SSDK::QAngle &angles, SSDK::Vector *forward, SSDK::Vector *right, SSDK::Vector *up) {
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles[SSDK::MathThings::YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[SSDK::MathThings::PITCH]), &sp, &cp);
	SinCos(DEG2RAD(angles[SSDK::MathThings::ROLL]), &sr, &cr);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

void Utilities::VectorAngles1(const SSDK::Vector& forward, SSDK::QAngle &angles) {
	float	tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

void Utilities::VectorAngles(const SSDK::Vector& forward, SSDK::QAngle &angles) {
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
		angles[1] = 0.0f;
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90) angles[1] -= 180;
		else if (angles[1] < 90) angles[1] += 180;
		else if (angles[1] == 90) angles[1] = 0;
	}

	angles[2] = 0.0f;
}

SSDK::QAngle Utilities::CalcAngle(SSDK::Vector src, SSDK::Vector dst) {
	SSDK::QAngle angles;
	SSDK::Vector delta = src - dst;
	VectorAngles(delta, angles);
	Normalize(delta);
	return angles;
}

bool Utilities::Clamp(SSDK::QAngle &angles) {
	SSDK::QAngle a = angles;
	Normalize(a);
	ClampAngles(a);

	if (isnan(a.x) || isinf(a.x) ||
		isnan(a.y) || isinf(a.y) ||
		isnan(a.z) || isinf(a.z)) {
		return false;
	}
	else {
		angles = a;
		return true;
	}
}

void Utilities::Normalize(SSDK::QAngle& angle) {
	while (angle.x > 89.0f) {
		angle.x -= 180.f;
	}
	while (angle.x < -89.0f) {
		angle.x += 180.f;
	}
	while (angle.y > 180.f) {
		angle.y -= 360.f;
	}
	while (angle.y < -180.f) {
		angle.y += 360.f;
	}
}

void Utilities::Normalize(float& angle) {
	while (angle > 180.f) {
		angle -= 360.f;
	}
	while (angle < -180.f) {
		angle += 360.f;
	}
}

void Utilities::ClampAngles(SSDK::QAngle &angles) {
	if (angles.y > 180.0f)
		angles.y = 180.0f;
	else if (angles.y < -180.0f)
		angles.y = -180.0f;

	if (angles.x > 89.0f)
		angles.x = 89.0f;
	else if (angles.x < -89.0f)
		angles.x = -89.0f;

	angles.z = 0;
}


SSDK::Vector Utilities::extrapolateTick(SSDK::Vector p0, CBaseEntity* ent) {
	return p0 + (*ent->GetVelocity() * SSDK::I::GlobalVars()->interval_per_tick);
}

void Utilities::SetClanTag(const char* tag, const char* name) {
	using SetClanTagFn = void(__fastcall*) (const char *tag, const char *name);
	static SetClanTagFn SetClanTagEx = (SetClanTagFn)(SSDK::O::FindSignature(XorStr("engine.dll"), XorStr("53 56 57 8B DA 8B F9 FF 15")));
	SetClanTagEx(tag, name);
}

bool Utilities::LineThroughSmoke(SSDK::Vector loc, SSDK::Vector rem) {
	using LineThroughSmoke_t = void(__fastcall*) (SSDK::Vector loc, SSDK::Vector rem);
	static LineThroughSmoke_t LineThroughSmokeEx = (LineThroughSmoke_t)(SSDK::O::FindSignature(XorStr("engine.dll"), XorStr("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0")));
	LineThroughSmokeEx(loc, rem);
}

float Utilities::RandomFloat(float min, float max)
{
	typedef float(*RandomFloat_t)(float, float);
	static RandomFloat_t m_RandomFloat = (RandomFloat_t)GetProcAddress(GetModuleHandle(XorStr("vstdlib.dll")), XorStr("RandomFloat"));
	return m_RandomFloat(min, max);
}

void Utilities::RandomSeed(int iSeed)
{
	typedef void(*RandomSeed_t)(int);
	static RandomSeed_t m_RandomSeed = (RandomSeed_t)GetProcAddress(GetModuleHandle(XorStr("vstdlib.dll")), XorStr("RandomSeed"));
	return m_RandomSeed(iSeed);
}

template< class T, class Y >
T Utilities::ClampValue(T const &val, Y const &minVal, Y const &maxVal)
{
	if (val < minVal)
		return minVal;
	else if (val > maxVal)
		return maxVal;
	else
		return val;
}

float Utilities::GetInterp()
{
	float updaterate = SSDK::I::CVar()->FindVar(XorStr("cl_updaterate"))->GetFloat();
	SSDK::ConVar* minupdate = SSDK::I::CVar()->FindVar(XorStr("sv_minupdaterate"));
	SSDK::ConVar* maxupdate = SSDK::I::CVar()->FindVar(XorStr("sv_maxupdaterate"));

	if (minupdate && maxupdate)
		updaterate = maxupdate->GetFloat();

	float ratio = SSDK::I::CVar()->FindVar(XorStr("cl_interp_ratio"))->GetFloat();

	if (ratio == 0)
		ratio = 1.0f;

	float lerp = SSDK::I::CVar()->FindVar(XorStr("cl_interp"))->GetFloat();
	SSDK::ConVar* cmin = SSDK::I::CVar()->FindVar(XorStr("sv_client_min_interp_ratio"));
	SSDK::ConVar* cmax = SSDK::I::CVar()->FindVar(XorStr("sv_client_max_interp_ratio"));

	if (cmin && cmax && cmin->GetFloat() != 1)
		ratio = ClampValue(ratio, cmin->GetFloat(), cmax->GetFloat());

	return max(lerp, ratio / updaterate);
}

float Utilities::GetNetworkLatency()
{
	// Get true latency
	SSDK::INetChannelInfo *nci = SSDK::I::Engine()->GetNetChannelInfo();
	if (nci)
	{
		float OutgoingLatency = nci->GetAvgLatency(0);
		return OutgoingLatency;
	}
	else
		return 0.0f;
}