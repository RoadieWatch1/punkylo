# Phase C Guardrails

**Status:** ACTIVE — enforced for all Phase C work
**Version:** Step 1 Clean Restart — 2026-03-31

---

## Purpose

Build the first playable cyberpunk district slice for PunkyLo.
This is a multiplayer-safe, identity-first world space — not a full city.

---

## Phase C Includes

- One district (PhaseC_District)
- Multiplayer-safe traversable space
- Zone identity (Arrival, Plaza, Routes, Authority)
- Early social systems — lightweight, surface-layer only
- 5 free base characters with visual identity
- Reputation shell (data structure only)
- Training flavor (environmental cues only)

---

## Phase C Excludes (Hard Locked)

- Monetization systems of any kind
- Backend persistence or account systems
- Full open world or streaming setup
- Traffic systems or vehicle logic
- Full building interiors
- Final lighting polish
- Dynamic economy or transaction systems
- NPC AI beyond static ambient presence
- Skill gain, stat systems, or tutorial flows

---

## Asset Source Rule (MANDATORY)

**ALL environment assets MUST come from:**
```
/Game/SoulCity
```
- Do NOT import external assets
- Do NOT duplicate SoulCity assets outside the SoulCity folder
- Do NOT rename or move the SoulCity folder

---

## Lighting Rule

❌ DO NOT add any directional light
❌ DO NOT add sky actors
❌ DO NOT add post-process volumes until Zone Mood bucket is active
✅ Wait for Zone Mood step before any lighting work

---

## Map Discipline

| Map | Purpose | Rule |
|---|---|---|
| `PhaseC_District` | Production world map | ALL Phase C world content |
| `/Maps/Test/` | Validation only | No production content — ever |
| `/Maps/Hub/` | Phase A/B hub | Do not break |

---

## System Discipline

- All systems: modular, independently loadable
- No hard cross-system dependencies at launch
- No backend service dependencies
- C++ prefix: `PL_`
- Blueprint prefix: `BP_PL_`
- Systems folders are **stub/shell only** until their bucket is activated

---

## Enforcement

Any work violating these guardrails must be reverted before merge.
When in doubt: scope down, validate, then expand.
