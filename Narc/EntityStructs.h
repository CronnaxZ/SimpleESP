#pragma once

#include "SqchSDK\Offsets.h"

#include "NetvarManager.h"

extern SSDK::QAngle CreateMoveAngles;

class CBaseAttributableItem;
class CBaseCSGrenade;
class CBaseEntity;

class CBaseCombatWeapon : public SSDK::IClientEntity {
	template<class T>
	T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	int *GetModelIndex() {
		static int m_nModelIndex = GET_NETVAR(XorStr("DT_BaseViewModel"), XorStr("m_nModelIndex"));
		return GetFieldPointer<int>(m_nModelIndex);
	}

	float NextPrimaryAttack() {
		static int m_flNextPrimaryAttack = GET_NETVAR(XorStr("DT_BaseCombatWeapon"), XorStr("LocalActiveWeaponData"), XorStr("m_flNextPrimaryAttack"));
		return GetFieldValue<float>(m_flNextPrimaryAttack);
	}
	float GetAccuracy() {
		static int m_fAccuracyPenalty = GET_NETVAR(XorStr("DT_WeaponCSBase"), XorStr("m_fAccuracyPenalty"));
		return GetFieldValue<float>(m_fAccuracyPenalty);
	}
	int GetState() {
		static int m_iState = GET_NETVAR(XorStr("DT_BaseCombatWeapon"), XorStr("m_iState"));
		return GetFieldValue<int>(m_iState);
	}
	int* GetItemDefinitionIndex() {
		static int m_iItemDefinitionIndex = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_AttributeManager"), XorStr("m_Item"), XorStr("m_iItemDefinitionIndex"));
		return GetFieldPointer<int>(m_iItemDefinitionIndex);
	}
	float PostponeFireReady()
	{
		static int offset = GET_NETVAR(XorStr("DT_WeaponCSBase"), XorStr("m_flPostponeFireReadyTime"));
		return GetFieldValue<float>(offset);
	}
	const char* GetName() {
		typedef const char* (__thiscall* tGetName)(void*);
		return SSDK::CallVFunction<tGetName>(this, 378)(this);
	}
	int GetId() {
		typedef int(__thiscall* tGetId)(void*);
		return SSDK::CallVFunction<tGetId>(this, 458)(this);
	}
	float GetCone() {
		typedef float(__thiscall* OriginFN)(void*);
		return SSDK::CallVFunction<OriginFN>(this, 469)(this);
	}
	float GetSpread() {
		typedef float(__thiscall* OriginFN)(void*);
		return SSDK::CallVFunction<OriginFN>(this, 439)(this);
	}
	void UpdateAccuracy() {
		typedef void(__thiscall* OriginFN)(void*);
		SSDK::CallVFunction<OriginFN>(this, 470)(this);
	}
	CBaseEntity* GetOwner()
	{
		static int m_hOwnerEntity = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_hOwnerEntity"));
		return (CBaseEntity*)SSDK::I::EntityList()->GetClientEntityFromHandle(m_hOwnerEntity);
	}
	SSDK::WeaponInfo_t* GetCSWpnData()
	{
		typedef SSDK::WeaponInfo_t*(__thiscall* OriginalFn)(void*);
		return SSDK::CallVFunction<OriginalFn>(this, 446)(this);
	}
	bool isGrenade() {
		return this->GetCSWpnData()->iWeaponType == SSDK::CSWeaponType::WEAPONTYPE_GRENADE;
	}
	CBaseCSGrenade *getGrenade() {
		return (CBaseCSGrenade*)this;
	}
	int GetMaxClip1() {
		typedef int(__thiscall* OriginalFn)(void*);
		return SSDK::CallVFunction<OriginalFn>(this, 367)(this);
	}
	int GetCurrentAmmo() {
		static int m_iClip1 = GET_NETVAR(XorStr("DT_BaseCombatWeapon"), XorStr("m_iClip1"));
		return GetFieldValue<int>(m_iClip1);
	}
	bool IsReloading() {
		static int m_bReloadVisuallyComplete = GET_NETVAR(XorStr("DT_WeaponCSBase"), XorStr("m_bReloadVisuallyComplete"));
		return !GetFieldValue<bool>(m_bReloadVisuallyComplete);
	}

	bool IsReloadingLocal() {
		return GetFieldValue<bool>(0x3235);
	}

	bool isWeaponScope()
	{
		int id = *this->GetItemDefinitionIndex();

		switch (id)
		{
		case SSDK::EItemDefinitionIndex::weapon_aug:
		case SSDK::EItemDefinitionIndex::weapon_awp:
		case SSDK::EItemDefinitionIndex::weapon_g3sg1:
		case SSDK::EItemDefinitionIndex::weapon_sg556:
		case SSDK::EItemDefinitionIndex::weapon_ssg08:
		case SSDK::EItemDefinitionIndex::weapon_scar20:
			return true;
		default:
			return false;
		}
	}

	bool isValidWeapon()
	{
		int id = *this->GetItemDefinitionIndex();

		switch (id)
		{
		case SSDK::EItemDefinitionIndex::weapon_deagle:
		case SSDK::EItemDefinitionIndex::weapon_elite:
		case SSDK::EItemDefinitionIndex::weapon_fiveseven:
		case SSDK::EItemDefinitionIndex::weapon_glock:
		case SSDK::EItemDefinitionIndex::weapon_ak47:
		case SSDK::EItemDefinitionIndex::weapon_aug:
		case SSDK::EItemDefinitionIndex::weapon_awp:
		case SSDK::EItemDefinitionIndex::weapon_famas:
		case SSDK::EItemDefinitionIndex::weapon_g3sg1:
		case SSDK::EItemDefinitionIndex::weapon_galilar:
		case SSDK::EItemDefinitionIndex::weapon_m249:
		case SSDK::EItemDefinitionIndex::weapon_m4a4:
		case SSDK::EItemDefinitionIndex::weapon_mac10:
		case SSDK::EItemDefinitionIndex::weapon_p90:
		case SSDK::EItemDefinitionIndex::weapon_ump:
		case SSDK::EItemDefinitionIndex::weapon_xm1014:
		case SSDK::EItemDefinitionIndex::weapon_bizon:
		case SSDK::EItemDefinitionIndex::weapon_mag7:
		case SSDK::EItemDefinitionIndex::weapon_negev:
		case SSDK::EItemDefinitionIndex::weapon_sawedoff:
		case SSDK::EItemDefinitionIndex::weapon_tec9:
			return true;
		case SSDK::EItemDefinitionIndex::weapon_taser:
			return false;
		case SSDK::EItemDefinitionIndex::weapon_hkp2000:
		case SSDK::EItemDefinitionIndex::weapon_mp7:
		case SSDK::EItemDefinitionIndex::weapon_mp9:
		case SSDK::EItemDefinitionIndex::weapon_nova:
		case SSDK::EItemDefinitionIndex::weapon_p250:
		case SSDK::EItemDefinitionIndex::weapon_scar20:
		case SSDK::EItemDefinitionIndex::weapon_sg556:
		case SSDK::EItemDefinitionIndex::weapon_ssg08:
			return true;
		case SSDK::EItemDefinitionIndex::weapon_knife:
		case SSDK::EItemDefinitionIndex::weapon_flashbang:
		case SSDK::EItemDefinitionIndex::weapon_hegrenade:
		case SSDK::EItemDefinitionIndex::weapon_smokegrenade:
		case SSDK::EItemDefinitionIndex::weapon_molotov:
		case SSDK::EItemDefinitionIndex::weapon_decoy:
		case SSDK::EItemDefinitionIndex::weapon_incgrenade:
		case SSDK::EItemDefinitionIndex::weapon_c4:
		case SSDK::EItemDefinitionIndex::weapon_knife_t:
			return false;
		case SSDK::EItemDefinitionIndex::weapon_m4a1_silencer:
		case SSDK::EItemDefinitionIndex::weapon_usp_silencer:
		case SSDK::EItemDefinitionIndex::weapon_cz75a:
		case SSDK::EItemDefinitionIndex::weapon_revolver:
			return true;
		default:
			return false;
		}
	}
	bool isPistol()
	{
		int id = *this->GetItemDefinitionIndex();

		switch (id)
		{
		case SSDK::EItemDefinitionIndex::weapon_deagle:
		case SSDK::EItemDefinitionIndex::weapon_elite:
		case SSDK::EItemDefinitionIndex::weapon_fiveseven:
		case SSDK::EItemDefinitionIndex::weapon_glock:
			return true;
		case SSDK::EItemDefinitionIndex::weapon_ak47:
		case SSDK::EItemDefinitionIndex::weapon_aug:
		case SSDK::EItemDefinitionIndex::weapon_awp:
		case SSDK::EItemDefinitionIndex::weapon_famas:
		case SSDK::EItemDefinitionIndex::weapon_g3sg1:
		case SSDK::EItemDefinitionIndex::weapon_galilar:
		case SSDK::EItemDefinitionIndex::weapon_m249:
		case SSDK::EItemDefinitionIndex::weapon_m4a4:
		case SSDK::EItemDefinitionIndex::weapon_mac10:
		case SSDK::EItemDefinitionIndex::weapon_p90:
		case SSDK::EItemDefinitionIndex::weapon_ump:
		case SSDK::EItemDefinitionIndex::weapon_xm1014:
		case SSDK::EItemDefinitionIndex::weapon_bizon:
		case SSDK::EItemDefinitionIndex::weapon_mag7:
		case SSDK::EItemDefinitionIndex::weapon_negev:
		case SSDK::EItemDefinitionIndex::weapon_sawedoff:
			return false;
		case SSDK::EItemDefinitionIndex::weapon_tec9:
		case SSDK::EItemDefinitionIndex::weapon_taser:
		case SSDK::EItemDefinitionIndex::weapon_hkp2000:
			return true;
		case SSDK::EItemDefinitionIndex::weapon_mp7:
		case SSDK::EItemDefinitionIndex::weapon_mp9:
		case SSDK::EItemDefinitionIndex::weapon_nova:
			return false;
		case SSDK::EItemDefinitionIndex::weapon_p250:
			return true;
		case SSDK::EItemDefinitionIndex::weapon_scar20:
		case SSDK::EItemDefinitionIndex::weapon_sg556:
		case SSDK::EItemDefinitionIndex::weapon_ssg08:
		case SSDK::EItemDefinitionIndex::weapon_knife:
		case SSDK::EItemDefinitionIndex::weapon_flashbang:
		case SSDK::EItemDefinitionIndex::weapon_hegrenade:
		case SSDK::EItemDefinitionIndex::weapon_smokegrenade:
		case SSDK::EItemDefinitionIndex::weapon_molotov:
		case SSDK::EItemDefinitionIndex::weapon_decoy:
		case SSDK::EItemDefinitionIndex::weapon_incgrenade:
		case SSDK::EItemDefinitionIndex::weapon_c4:
		case SSDK::EItemDefinitionIndex::weapon_knife_t:
		case SSDK::EItemDefinitionIndex::weapon_m4a1_silencer:
			return false;
		case SSDK::EItemDefinitionIndex::weapon_usp_silencer:
			return true;
		case SSDK::EItemDefinitionIndex::weapon_cz75a:
			return true;
		case SSDK::EItemDefinitionIndex::weapon_revolver:
			return false;
		default:
			return false;
		}
	}
};

class CBaseViewModel {
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	int *GetViewModelIndex() {
		static int m_iViewModelIndex = GET_NETVAR(XorStr("DT_BaseViewModel"), XorStr("m_nViewModelIndex"));
		return GetFieldPointer<int>(m_iViewModelIndex);
	}

	int *GetModelIndex() {
		static int m_nModelIndex = GET_NETVAR(XorStr("DT_BaseViewModel"), XorStr("m_nModelIndex"));
		return GetFieldPointer<int>(m_nModelIndex);
	}

	DWORD GetWeapon() {
		static DWORD m_hWeapon = GET_NETVAR(XorStr("DT_BaseViewModel"), XorStr("m_hWeapon"));
		return GetFieldValue<DWORD>(m_hWeapon);
	}

	void SetWeaponModel(const char* Filename, CBaseAttributableItem* Weapon) {
		return SSDK::CallVFunction<void(__thiscall*)(void*, const char*, CBaseAttributableItem*)>(this, 242)(this, Filename, Weapon);
	}
};

class CBaseEntity : public SSDK::IClientEntity {
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	static CBaseEntity* GetLocalPlayer() {
		return (CBaseEntity*)SSDK::I::EntityList()->GetClientEntity(SSDK::I::Engine()->GetLocalPlayer());
	}

	bool SetupBones(SSDK::matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) {
		//Invalidate cache PVSFIX
		//static uintptr_t m_nWritableBones = GET_NETVAR(XorStr("DT_BaseAnimating"), XorStr("m_nForceBone")) + 0x20;
		//static uintptr_t m_dwOcclusionArray = *(uintptr_t*)(SSDK::O::FindSignature(XorStr("client.dll"), XorStr("A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8")) + 0x1);
		//static uintptr_t m_bDidCheckForOcclusion = *(uintptr_t*)(SSDK::O::FindSignature(XorStr("client.dll"), XorStr("A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8")) + 0xE);
		//static uintptr_t InvalidateBoneCache = SSDK::O::FindSignature(XorStr("client.dll"), XorStr("80 3D ? ? ? ? 00 74 16 A1"));
		//*(int*)((uintptr_t)this + m_nWritableBones) = 0;
		//*(int*)((uintptr_t)this + m_bDidCheckForOcclusion) = reinterpret_cast<int*>(m_dwOcclusionArray)[1];
		//reinterpret_cast<void(__fastcall*)(void*)>(InvalidateBoneCache)(pEntity);

		__asm
		{
			mov edi, this
			lea ecx, DWORD ptr ds : [edi + 0x4]
			mov edx, DWORD ptr ds : [ecx]
			push currentTime
			push boneMask
			push nMaxBones
			push pBoneToWorldOut
			call DWORD ptr ds : [edx + 0x34]
		}
	}

	CBaseCombatWeapon* GetActiveWeapon() {
		static int m_hActiveWeapon = GET_NETVAR(XorStr("DT_BaseCombatCharacter"), XorStr("m_hActiveWeapon"));
		return (CBaseCombatWeapon*)SSDK::I::EntityList()->GetClientEntityFromHandle(GetFieldValue<SSDK::CBaseHandle>(m_hActiveWeapon));
	}

	int *GetModelIndex() {
		static int m_nModelIndex = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_nModelIndex"));
		return GetFieldPointer<int>(m_nModelIndex);
	}

	int GetShotFired() {
		static int m_iShotsFired = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("cslocaldata"), XorStr("m_iShotsFired"));
		return GetFieldValue<int>(m_iShotsFired);
	}

	SSDK::QAngle *GetEyeAngles() {
		static int m_angEyeAngles = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_angEyeAngles[0]"));
		return GetFieldPointer<SSDK::QAngle>(m_angEyeAngles);
	}

	int GetHealth() {
		static int m_iHealth = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_iHealth"));
		return GetFieldValue<int>(m_iHealth);
	}

	int GetArmor() {
		static int m_ArmorValue = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_ArmorValue"));
		return GetFieldValue<int>(m_ArmorValue);
	}

	bool HasHelmet() {
		static int m_bHasHelmet = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_bHasHelmet"));
		return GetFieldValue<bool>(m_bHasHelmet);
	}

	bool* GetSpotted() {
		static int m_bSpotted = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_bSpotted"));
		return GetFieldPointer<bool>(m_bSpotted);
	}

	int *GetTickBase() {
		static int m_nTickBase = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("localdata"), XorStr("m_nTickBase"));
		return GetFieldPointer<int>(m_nTickBase);
	}

	bool IsAlive() {
		static int m_lifeState = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_lifeState"));
		return GetFieldValue<int>(m_lifeState) == 0;
	}

	const SSDK::matrix3x4_t EntityToWorldTransform() {
		static int m_rgflCoordinateFrame = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_CollisionGroup")) - 48;
		return GetFieldValue<const SSDK::matrix3x4_t>(m_rgflCoordinateFrame);
	}

	int *GetTeamNum() {
		static int m_iTeamNum = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_iTeamNum"));
		return GetFieldPointer<int>(m_iTeamNum);
	}

	int *GetFlags() {
		static int m_fFlags = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_fFlags"));
		return GetFieldPointer<int>(m_fFlags);
	}

	CBaseEntity* GetObserved() {
		static int m_hObserverTarget = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_hObserverTarget"));
		return (CBaseEntity*)SSDK::I::EntityList()->GetClientEntityFromHandle(GetFieldValue<SSDK::CBaseHandle>(m_hObserverTarget));
	}

	UINT* GetWeapons() {
		static UINT m_hMyWeapons = GET_NETVAR(XorStr("DT_BaseCombatCharacter"), XorStr("m_hMyWeapons"));
		return GetFieldPointer<UINT>(m_hMyWeapons);
	}

	CBaseViewModel* GetViewModel() {
		static int m_hViewModel = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_hViewModel[0]"));
		return (CBaseViewModel*)SSDK::I::EntityList()->GetClientEntityFromHandle(GetFieldValue<int>(m_hViewModel));
	}

	SSDK::Vector* GetViewOffset() {
		static int m_vecViewOffset = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("localdata"), XorStr("m_vecViewOffset[0]"));
		return GetFieldPointer<SSDK::Vector>(m_vecViewOffset);
	}

	SSDK::Vector* GetOrigin() {
		static int m_vecOrigin = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_vecOrigin"));
		return GetFieldPointer<SSDK::Vector>(m_vecOrigin);
	}

	SSDK::Vector GetEyePos() {
		return *GetOrigin() + *GetViewOffset();
	}

	SSDK::Vector* ViewPunch() {
		static int m_viewPunchAngle = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("localdata"), XorStr("m_Local"), XorStr("m_viewPunchAngle"));
		return GetFieldPointer<SSDK::Vector>(m_viewPunchAngle);
	}

	SSDK::Vector* AimPunch() {
		static int m_aimPunchAngle = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("localdata"), XorStr("m_Local"), XorStr("m_aimPunchAngle"));
		return GetFieldPointer<SSDK::Vector>(m_aimPunchAngle);
	}

	int* iFov() {
		static int m_iFOV = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_iFOV"));
		return GetFieldPointer<int>(m_iFOV);
	}

	float* flashDuration() {
		static int m_flFlashDuration = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_flFlashDuration"));
		return GetFieldPointer<float>(m_flFlashDuration);
	}

	bool isVisible() {
		SSDK::Trace_t tr;
		SSDK::Ray_t ray;
		SSDK::CTraceFilter filter;
		filter.pSkip = CBaseEntity::GetLocalPlayer();

		SSDK::matrix3x4_t boneMatrix[128];

		if (!this->SetupBones(boneMatrix, 128, 256, SSDK::I::Engine()->GetLastTimeStamp()))
			return false;

		SSDK::matrix3x4_t hitbox = boneMatrix[SSDK::ECSPlayerBones::HEAD_0];
		//-------------------------

		ray.Init(this->GetLocalPlayer()->GetEyePos(), SSDK::Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]));
		SSDK::I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

		return tr.m_pEnt == this || tr.fraction > 0.97f;
	}

	bool isVisible2() {
		SSDK::Trace_t tr;
		SSDK::Ray_t ray;
		SSDK::CTraceFilter filter;
		filter.pSkip = CBaseEntity::GetLocalPlayer();

		SSDK::matrix3x4_t boneMatrix[128];

		if (!this->SetupBones(boneMatrix, 128, 256, SSDK::I::Engine()->GetLastTimeStamp()))
			return false;

		SSDK::matrix3x4_t hitbox = boneMatrix[SSDK::ECSPlayerBones::HEAD_0];
		//-------------------------

		ray.Init(this->GetLocalPlayer()->GetEyePos(), SSDK::Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]));
		SSDK::I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

		return tr.m_pEnt == this;
	}

	bool isVectorVisible(SSDK::Vector vec) {
		SSDK::Trace_t tr;
		SSDK::Ray_t ray;
		SSDK::CTraceFilter filter;
		filter.pSkip = CBaseEntity::GetLocalPlayer();

		ray.Init(this->GetLocalPlayer()->GetEyePos(), vec);
		SSDK::I::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

		return tr.m_pEnt == this;
	}

	bool canHit(SSDK::Vector end, CBaseEntity* ent) {
		SSDK::Ray_t ray;

		SSDK::Trace_t tr;

		SSDK::CTraceFilter traceFilter;
		traceFilter.pSkip = this;

		ray.Init(this->GetEyePos(), end);

		SSDK::I::EngineTrace()->ClipRayToEntity(ray, MASK_SHOT, (SSDK::IHandleEntity*)ent, &tr); // ignore grate

		if (!tr.m_pEnt)
			return false;

		CBaseEntity *pEnt = (CBaseEntity*)tr.m_pEnt;

		if (*pEnt->GetTeamNum() != *this->GetTeamNum())
			return true;

		return false;
	}

	bool isMoving() {
		return GetVelocity()->Length() > 0.1f;
	}

	DWORD glowIndex() {
		static int m_glowIndex = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_flFlashDuration")) + 0x18;
		return GetFieldValue<DWORD>(m_glowIndex);
	}

	SSDK::Vector *GetVelocity() {
		static int m_vecVelocity = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("localdata"), XorStr("m_vecVelocity[0]"));
		return GetFieldPointer<SSDK::Vector>(m_vecVelocity);
	}

	SSDK::Vector *GetBaseVelocity() {
		static int m_vecBaseVelocity = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("localdata"), XorStr("m_vecBaseVelocity"));
		return GetFieldPointer<SSDK::Vector>(m_vecBaseVelocity);
	}

	bool isScoped() {
		static int m_bIsScoped = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_bIsScoped"));
		return GetFieldValue<bool>(m_bIsScoped);
	}

	float *GetLowerBodyYaw() {
		static int m_flLowerBodyYawTarget = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_flLowerBodyYawTarget"));
		return GetFieldPointer<float>(m_flLowerBodyYawTarget);
	}

	float *GetSimulationTime() {
		static int m_flSimulationTime = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_flSimulationTime"));
		return GetFieldPointer<float>(m_flSimulationTime);
	}

	float *GetAnimTime() {
		static int m_flAnimTime = 0x0;
		return GetFieldPointer<float>(m_flAnimTime);
	}

	float *GetPosePosition() {
		static int m_flPoseParameter = GET_NETVAR(XorStr("DT_BaseAnimating"), XorStr("m_flPoseParameter"));
		return GetFieldPointer<float>(m_flPoseParameter);
	}

	bool *GetDucked() {
		static int m_bDucked = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("localdata"), XorStr("m_Local"), XorStr("m_bDucked"));
		return GetFieldPointer<bool>(m_bDucked);
	}

	bool *GetDucking() {
		static int m_bDucking = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("localdata"), XorStr("m_Local"), XorStr("m_bDucking"));
		return GetFieldPointer<bool>(m_bDucking);
	}

	float *GetDuckSpeed() {
		static int m_flDuckSpeed = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_flDuckSpeed"));
		return GetFieldPointer<float>(m_flDuckSpeed);
	}

	bool *GetDuckOverride() {
		static int m_bDuckOverride = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("cslocaldata"), XorStr("m_bDuckOverride"));
		return GetFieldPointer<bool>(m_bDuckOverride);
	}

	float *GetDuckAmount() {
		static int m_flDuckAmount = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_flDuckAmount"));
		return GetFieldPointer<float>(m_flDuckAmount);
	}

	bool InBuyZone() {
		static int m_bInBuyZone = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_bInBuyZone"));
		return GetFieldValue<bool>(m_bInBuyZone);
	}

	bool isDucking() {
		return (bool)(*this->GetFlags() & (int)SSDK::EntityFlags::FL_DUCKING);
	}

	SSDK::Vector *GetMin() {
		static int m_vecMins = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_Collision"), XorStr("m_vecMins"));
		return GetFieldPointer<SSDK::Vector>(m_vecMins);
	}

	SSDK::Vector *GetMax() {
		static int m_vecMaxs = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_Collision"), XorStr("m_vecMaxs"));
		return GetFieldPointer<SSDK::Vector>(m_vecMaxs);
	}

	void UpdateClientSideAnimation() {
		SSDK::CallVFunction<void(__thiscall*)(void*)>(this, 218)(this);
	}

	bool isValidPlayer(bool isLocalPlayer = false) {
		if (!this)
			return false;
		if (this->GetClientClass()->m_ClassID != SSDK::EClassIds::CCSPlayer)
			return false;
		if (this->IsDormant())
			return false;
		if (!isLocalPlayer) {
			if (this->EntIndex() == CBaseEntity::GetLocalPlayer()->EntIndex())
				return false;
			if (this->isSpawnImmune())
				return false;
		}
		if (!this->IsAlive())
			return false;
		return true;
	}

	bool isValidWeapon() {
		if (!this)
			return false;
		if (strstr(this->GetClientClass()->m_pNetworkName, XorStr("CWeapon")) ||
			strstr(this->GetClientClass()->m_pNetworkName, XorStr("CAK47")))
			return true;
		return false;
	}

	SSDK::Vector GetEntityHitbox(int iHitBox) {
		SSDK::matrix3x4_t boneMatrix[128];

		if (!this->SetupBones(boneMatrix, 128, 256, SSDK::I::Engine()->GetLastTimeStamp()))
			return SSDK::Vector();

		SSDK::studiohdr_t* hdr = SSDK::I::ModelInfo()->GetStudiomodel(this->GetModel());
		SSDK::mstudiohitboxset_t* set = hdr->pHitboxSet(0);

		SSDK::matrix3x4_t hitbox = boneMatrix[set->pHitbox(iHitBox)->bone];

		return SSDK::Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}

	bool isSpawnImmune() {
		static int m_bGunGameImmunity = GET_NETVAR(XorStr("DT_CSPlayer"), XorStr("m_bGunGameImmunity"));
		return GetFieldValue<bool>(m_bGunGameImmunity);
	}

	float *GetFallVelocity() {
		static int m_flFallVelocity = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("localdata"), XorStr("m_Local"), XorStr("m_flFallVelocity"));
		return GetFieldPointer<float>(m_flFallVelocity);
	}

	SSDK::Vector WorldSpaceCenter() {
		SSDK::Vector Max = *this->GetMax() + *this->GetOrigin();
		SSDK::Vector Min = *this->GetMin() + *this->GetOrigin();
		SSDK::Vector Size = Max - Min;
		Size /= 2;
		Size += Min;
		return Size;
	}

	int *GetRenderMode() {
		static int m_nRenderMode = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_nRenderMode"));
		return GetFieldPointer<int>(m_nRenderMode);
	}

	int *GetEffects() {
		static int m_fEffects = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_fEffects"));
		return GetFieldPointer<int>(m_fEffects);
	}

	SSDK::Color *GetColorRender() {
		static int m_clrRender = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_clrRender"));
		return GetFieldPointer<SSDK::Color>(m_clrRender);
	}

	int *GetTextureIndex() {
		static int m_iTextureFrameIndex = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_iTextureFrameIndex"));
		return GetFieldPointer<int>(m_iTextureFrameIndex);
	}

	float *GetFadeMax() {
		static int m_fadeMaxDist = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_fadeMaxDist"));
		return GetFieldPointer<float>(m_fadeMaxDist);
	}

	float *GetFadeScale() {
		static int m_flFadeScale = GET_NETVAR(XorStr("DT_BaseEntity"), XorStr("m_flFadeScale"));
		return GetFieldPointer<float>(m_flFadeScale);
	}
};

class CBaseAttributableItem : public CBaseEntity {
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	int* GetItemDefinitionIndex() {
		static int m_iItemDefinitionIndex = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_AttributeManager"), XorStr("m_Item"), XorStr("m_iItemDefinitionIndex"));
		return GetFieldPointer<int>(m_iItemDefinitionIndex);
	}

	int* GetItemIDHigh() {
		static int m_iItemIDHigh = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_AttributeManager"), XorStr("m_Item"), XorStr("m_iItemIDHigh"));
		return GetFieldPointer<int>(m_iItemIDHigh);
	}

	int* GetEntityQuality() {
		static int m_iEntityQuality = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_AttributeManager"), XorStr("m_Item"), XorStr("m_iEntityQuality"));
		return GetFieldPointer<int>(m_iEntityQuality);
	}

	char* GetCustomName() {
		static int m_szCustomName = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_AttributeManager"), XorStr("m_Item"), XorStr("m_szCustomName"));
		return GetFieldPointer<char>(m_szCustomName);
	}

	int* GetFallbackPaintKit() {
		static int m_nFallbackPaintKit = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_nFallbackPaintKit"));
		return GetFieldPointer<int>(m_nFallbackPaintKit);
	}

	int* GetFallbackSeed() {
		static int m_nFallbackSeed = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_nFallbackSeed"));
		return GetFieldPointer<int>(m_nFallbackSeed);
	}

	float* GetFallbackWear() {
		static int m_flFallbackWear = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_flFallbackWear"));
		return GetFieldPointer<float>(m_flFallbackWear);
	}

	int* GetFallbackStatTrak() {
		static int m_bSpotted = GET_NETVAR(XorStr("DT_BaseAttributableItem"), XorStr("m_nFallbackStatTrak"));
		return GetFieldPointer<int>(m_bSpotted);
	}
};

class CBaseCSGrenade : CBaseCombatWeapon {
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:
	float GetThrowTime()
	{
		static int m_fThrowTime = GET_NETVAR(XorStr("DT_BaseCSGrenade"), XorStr("m_fThrowTime"));
		return GetFieldValue<float>(m_fThrowTime);
	}
};