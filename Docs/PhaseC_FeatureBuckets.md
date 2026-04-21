# Phase C Feature Buckets

**Status:** ACTIVE — reference before starting any Phase C work item
**Version:** Step 1 Clean Restart — 2026-03-31

Do not implement features outside a bucket's scope without updating this document first.

---

## 1. World Slice

**Purpose:** First playable, traversable district as a physical space.

**In-Scope:**
- Landscape (already created — do not modify size)
- Blockout geometry for PhaseC_District zones: Arrival, Plaza, Routes, Authority
- Navigation mesh
- Zone boundary volumes (physical delineation only — no logic)

**Out-of-Scope:**
- Lighting (Zone Mood bucket)
- Final art or polished meshes
- NPC AI or population
- Dynamic weather or streaming

**Asset Source:** `/Game/SoulCity` only

**Status:** PENDING — Step 2 will define zone layout

---

## 2. Zone Identity (Zone Mood)

**Purpose:** Each zone communicates its identity through space and atmosphere — no UI labels.

**In-Scope:**
- Distinct light color temperature per zone
- Acoustic zones via Audio Volume actors
- Material variation per zone
- Fog/atmosphere variation

**Out-of-Scope:**
- Dynamic zone transitions triggered by gameplay
- Zone-based stat modifiers
- Zone unlock or progression gating

**Status:** LOCKED — activates after World Slice blockout is complete

---

## 3. Early Social Systems (Lightweight)

**Purpose:** Surface-level ambient social signal — the space feels alive without explicit systems.

**In-Scope:**
- Player proximity awareness (visual density read)
- Basic static/looping ambient NPC presence (blockout-grade)
- Visual energy variation tied to player count (light intensity tweak only)

**Out-of-Scope:**
- Backend social data
- Reactive NPC systems
- Social scoring, heat meters, or UI readouts
- Persistent social state

**Status:** LOCKED — activates after Zone Identity is complete

---

## 4. Character Support (5 Free Only)

**Purpose:** Scaffolding for 5 free base characters. Foundation only — no monetization.

**In-Scope:**
- 5 character slots in `PL_CharacterRoster` data asset
- Slot fields: Name, RoleType, BaseMeshRef, BaseColorPrimary, BaseColorSecondary
- Character selection stub (functional, UI-minimal)
- Correct multiplayer replication

**Out-of-Scope:**
- Premium or paid character slots
- Unlock conditions or entitlement checks
- Cosmetic shop integration
- Character progression

**Status:** PENDING — depends on Identity assets

---

## 5. Validation

**Purpose:** Confirm Phase C content is stable and correct in a networked session at each milestone.

**In-Scope:**
- Per-bucket validation in `/Maps/Test` before promotion to PhaseC_District
- Minimum 2-player listen server per validation pass
- Replication audit for all new components and actors
- Performance baseline (target: 60fps mid-spec in district with 2 players)

**Out-of-Scope:**
- Dedicated server infrastructure testing
- Load testing or stress testing
- Anti-cheat validation

**Status:** ACTIVE — runs after each bucket completion

---

## Bucket Activation Order

```
Step 1 (NOW)    → Environment Setup + Guardrails
Step 2          → District Design Brief + Zone Layout
Step 3          → World Slice Blockout
Step 4          → Zone Identity (Mood + Materials)
Step 5          → Social Presence
Step 6          → Character Support
Step 7          → Full Validation Pass
```
