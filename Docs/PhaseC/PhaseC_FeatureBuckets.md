# Phase C Feature Buckets

**Status:** ACTIVE — reference before starting any Phase C work item
**Last Updated:** 2026-03-28

Each bucket defines scope, dependencies, and what success looks like.
Do not implement features outside bucket scope without updating this document first.

---

## 1. World Slice

**Purpose:** Establish the first playable, traversable district as a physical space.

**In-Scope:**
- Blockout geometry for PhaseC_District (arrival area, plaza, routes, authority zone)
- Navigation mesh baked and functional
- Basic collision and player movement through the space
- Zone boundary volumes (no logic yet, just physical delineation)
- Lighting pass (base, non-final — sufficient for presence reads)

**Out-of-Scope:**
- Final art assets, hero props, or polished meshes
- Dynamic time-of-day or weather systems
- Streaming/open world setup
- Any NPC population or AI

**Dependencies:**
- UE5 base level setup from Phase A/B
- Player character movement working (Phase B)

**Validation Requirement:**
- Player can traverse entire district without clipping, gaps, or navigation breaks
- 2-player session: both players can move through district simultaneously without desyncs

---

## 2. Zone Mood

**Purpose:** Each zone in the district must communicate its identity through spatial and atmospheric design alone — no UI labels.

**In-Scope:**
- Distinct light color temperature per zone (arrival = neutral, plaza = warm/social, routes = directional/cool, authority = high-contrast)
- Acoustic zones via Audio Volume actors (no custom audio yet — reverb/occlusion profiles only)
- Material tint or material parameter variation per zone
- Fog/atmosphere variation between zones

**Out-of-Scope:**
- Dynamic zone transitions triggered by gameplay logic
- Zone-based stat modifiers or gameplay effects
- Any zone unlock or progression gating

**Dependencies:**
- World Slice blockout complete
- UE5 Lumen/lighting pipeline confirmed working

**Validation Requirement:**
- Blind playtest: player can identify zone type (arrival / plaza / route / authority) without UI assistance
- Zones read clearly in multiplayer with 2+ players present

---

## 3. Identity Presence

**Purpose:** Players must be readable as distinct presences at a distance — before any UI or nameplate appears.

**In-Scope:**
- Silhouette differentiation between player characters (height, stance width, accessory shape)
- Base color variation per character slot (5 free characters)
- Distance-readable visual marker (not a nameplate — shape/color only)
- Animation stance differentiation (idle pose variation per character)

**Out-of-Scope:**
- Cosmetic customization systems
- Premium character unlocks
- Nameplate or HUD-driven identity systems
- Character monetization of any kind

**Dependencies:**
- Characters/Roster folder populated with 5 base character assets
- Player replication working (Phase B)

**Validation Requirement:**
- 2-player session: each player can identify the other's character at 20m, 50m, and 100m without UI
- Identity reads correctly on all supported platforms

---

## 4. Social Heat

**Purpose:** Surface-level ambient social signal — the space should feel alive without explicit social systems.

**In-Scope:**
- Passive crowd-feel through player proximity awareness (visual density read)
- Basic ambient NPC presence (non-interactive, static or simple loop — blockout-grade only)
- Visual "energy" variation tied to number of players in a zone (light intensity tweak, nothing more)

**Out-of-Scope:**
- Real-time social data from backend
- Reactive NPC systems
- Social scoring, heat meters, or UI readouts
- Any persistence of social state

**Dependencies:**
- World Slice and Zone Mood complete
- Minimum 2 connected players for validation

**Validation Requirement:**
- A zone with 2+ players feels distinctly different from an empty zone (purely visual/audio)
- No backend calls are made; all logic is local and ephemeral

---

## 5. Reputation Shell

**Purpose:** Data structure stub for future reputation system. No gameplay behavior yet.

**In-Scope:**
- `PL_ReputationComponent` C++ class (data container only)
- Fields: `ReputationScore` (int32), `ReputationTier` (enum stub), `LastModifiedTimestamp`
- Component attaches to PlayerState — no logic, no mutation, no UI read
- Replicated via standard UE5 property replication (ready for future use)

**Out-of-Scope:**
- Reputation gain/loss logic
- UI display of reputation
- Backend persistence
- Reputation-gated content or systems

**Dependencies:**
- Phase B PlayerState setup

**Validation Requirement:**
- Component compiles and attaches without error
- Replication confirmed: server and client hold identical values in a 2-player session
- No gameplay behavior is triggered by component presence

---

## 6. Training Flavor

**Purpose:** Environmental cues that contextually suggest the world has training structures — no functional training system.

**In-Scope:**
- Static props suggesting training activity (training markers, obstacle silhouettes, chalk marks)
- Optional: ambient audio loop suggesting training activity in a designated zone area
- Environmental signage or graffiti cues (static, no interaction)

**Out-of-Scope:**
- Interactive training sequences
- Skill gain or stat systems
- Tutorial flows
- Any UI-driven training progress

**Dependencies:**
- World Slice complete (designated training zone area needed)
- World/Props folder

**Validation Requirement:**
- Player navigating through training area understands the space's purpose without instruction
- No interactive elements trigger unintended gameplay

---

## 7. Role Flavor Beginnings

**Purpose:** Begin visual and audio differentiation between character roles without implementing role logic.

**In-Scope:**
- Base role categories defined (e.g., Brawler, Runner, Strategist) — enum only
- Per-role idle animation variation (distinct stances)
- Per-role ambient sound profile (one short loop per role — no triggers)
- Role assigned at character selection — no gameplay effect in Phase C

**Out-of-Scope:**
- Role-specific abilities or stat modifiers
- Role unlock or progression gating
- Role-based matchmaking or team logic

**Dependencies:**
- Identity Presence bucket (character assets needed)
- Characters/Roster populated

**Validation Requirement:**
- 2-player session: players with different roles are visually distinct at distance
- Role assignment does not affect gameplay in any measurable way

---

## 8. Signature Visual Ritual

**Purpose:** Placeholder and vision stub for the signature action that defines player expression in the world.

**In-Scope:**
- Design document or in-engine comment block describing intended ritual
- Placeholder animation slot reserved on character skeletal mesh
- Input action mapped but bound to null/log-only (no visual output yet)

**Out-of-Scope:**
- Actual ritual animation
- VFX or audio for ritual
- Multiplayer-synced ritual execution
- Any social/reputation trigger from ritual

**Dependencies:**
- Identity Presence (character mesh needed)
- Input system (Phase A)

**Validation Requirement:**
- Input binding exists and logs correctly server-side
- No visual output is produced (confirmed intentional stub state)
- Slot is reserved on mesh without breaking existing animations

---

## 9. Presence-First Audio

**Purpose:** Audio that communicates the world's identity before any reactive audio system is built.

**In-Scope:**
- Ambient loop per zone (looping, non-reactive, non-spatial — basic AudioVolume driven)
- Footstep surface variation (2-3 surface types: concrete, gravel, interior)
- Player proximity audio cue (subtle — e.g., crowd murmur intensifies with player count)
- Zone-to-zone transition crossfade (simple blend, no logic)

**Out-of-Scope:**
- Dynamic music systems
- Reactive audio triggered by gameplay events
- Wwise or FMOD integration (unless already in project)
- Spatial audio simulation beyond UE5 native

**Dependencies:**
- World Slice and Zone Mood complete
- Audio/World folder populated with placeholder loops

**Validation Requirement:**
- Each zone has a distinct, identifiable audio character
- No audio errors or missing asset warnings in a 2-player session
- Audio does not stutter or desync in multiplayer

---

## 10. Character Support (5 Free Only)

**Purpose:** Scaffolding for 5 free base characters. Foundation only — no monetization.

**In-Scope:**
- 5 character slots defined in `PL_CharacterRoster` data asset
- Each slot: Name, RoleType, BaseMeshRef, BaseColorPrimary, BaseColorSecondary
- Character selection flow stub (functional but UI-minimal)
- Characters replicated correctly in multiplayer

**Out-of-Scope:**
- Premium or paid character slots
- Unlock conditions or entitlement checks
- Cosmetic shop integration
- Character progression or leveling

**Dependencies:**
- Identity Presence assets (5 character meshes needed)
- Role Flavor Beginnings (role enum needed)

**Validation Requirement:**
- All 5 characters selectable and functional in a 2-player session
- Character selection replicates correctly to all clients
- Zero monetization or entitlement code paths exist

---

## 11. Multiplayer Validation

**Purpose:** Confirm Phase C content is stable and correct in a networked session at each milestone.

**In-Scope:**
- Per-bucket validation checklist (see `PhaseC_ValidationChecklist.md`)
- Minimum: 2-player listen server session per validation pass
- Replication audit for all new components and actors
- Performance baseline check (frame time in district with 2 players)

**Out-of-Scope:**
- Dedicated server infrastructure testing
- Load testing or stress testing
- Anti-cheat validation

**Dependencies:**
- Each feature bucket must be complete before its validation pass
- Phase B multiplayer foundation must remain intact

**Validation Requirement:**
- All Phase C buckets pass their individual validation requirement in a 2-player session
- No regression introduced to Phase A or Phase B systems
- Frame time remains acceptable (target: 60fps on mid-spec hardware in PhaseC_District)
