#pragma once

#include "..\SDKHelper\Utilities.h"

namespace SSDK {
	struct surfacephysicsparams_t
	{
		// vphysics physical properties
		float			friction;
		float			elasticity;				// collision elasticity - used to compute coefficient of restitution
		float			density;				// physical density (in kg / m^3)
		float			thickness;				// material thickness if not solid (sheet materials) in inches
		float			dampening;
	};

	struct surfaceaudioparams_t // +16
	{
		// sounds / audio data
		float			reflectivity;		// like elasticity, but how much sound should be reflected by this surface
		float			hardnessFactor;	// like elasticity, but only affects impact sound choices
		float			roughnessFactor;	// like friction, but only affects scrape sound choices

											// audio thresholds
		float			roughThreshold;	// surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
		float			hardThreshold;	// surface hardness > this causes "hard" impacts, < this causes "soft" impacts
		float			hardVelocityThreshold;	// collision velocity > this causes "hard" impacts, < this causes "soft" impacts
												// NOTE: Hard impacts must meet both hardnessFactor AND velocity thresholds
	};

	struct surfacesoundnames_t // +36
	{
		unsigned short	stepleft;
		unsigned short	stepright;

		unsigned short	impactSoft;
		unsigned short	impactHard;

		unsigned short	scrapeSmooth;

		unsigned short	scrapeRough;

		unsigned short	bulletImpact;
		unsigned short	rolling;

		unsigned short	breakSound;
		unsigned short	strainSound;
	};

	struct surfacegameprops_t // +56
	{
		// game movement data
		float			maxSpeedFactor;			// Modulates player max speed when walking on this surface
		float			jumpFactor;				// Ini jdicates how much higher the player should jump when on the surface
		float unk1, flPenetrationModifier, flDamageModifier;
		// Game-specific data
		unsigned short	material; // +84
								  // Indicates whether or not the player is on a ladder.
		unsigned char	climbable;
		unsigned char	pad;
	};

	struct surfacedata_t
	{
		surfacephysicsparams_t	physics;	// physics parameters
		surfaceaudioparams_t	audio;		// audio parameters
		surfacesoundnames_t		sounds;		// names of linked sounds
		surfacegameprops_t		game;		// Game data / properties
	};

	class IPhysicsSurfaceProps {
	public:
		surfacedata_t* GetSurfaceData(int surfaceDataIndex) {
			typedef surfacedata_t*(__thiscall *OrigFn)(void*, int);
			return CallVFunction<OrigFn>(this, 5)(this, surfaceDataIndex);
		}
	};
}