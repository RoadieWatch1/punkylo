# Phase C Validation Checklist

**Status:** ACTIVE — Step 3 blockout script ready, awaiting editor execution
**Rule:** Validate in `/Maps/Test` BEFORE promoting any feature to `PhaseC_District`.

---

## World Validation

**Script:** Run `Step3_PhaseC_Blockout.py` then `Build > Build Paths` then PIE.

- [ ] Player can traverse full district without clipping or collision gaps
- [ ] No navigation mesh holes or dead zones
- [ ] All zone entry/exit points are traversable
- [ ] 2-player session: both players traverse simultaneously without desyncs
- [ ] Frame time acceptable at all district positions (target: 60fps, mid-spec)
- [ ] Landscape is unmodified from clean state
- [ ] No visible map edges — perimeter walls fully enclose the district
- [ ] Walls are 3–5× player height (target 8m)
- [ ] All zones reachable by walking only (no jumps, no gaps)

---

## Presence Validation

- [ ] Arrival zone is identifiable as entry point without UI
- [ ] Plaza zone reads as social/gathering space without UI
- [ ] Routes read as directional transit corridors without UI
- [ ] Authority zone reads as high-tension / controlled area without UI
- [ ] Zone transitions are perceptible at boundaries
- [ ] Blind playtest: testers identify zone type correctly without UI

---

## System Validation

- [ ] All new Phase C components compile without error
- [ ] No new system introduces a hard dependency on another new system
- [ ] No backend calls made by any Phase C system
- [ ] Each system is removable without breaking other systems
- [ ] No monetization or entitlement code paths exist

---

## Multiplayer Validation

- [ ] 2-player session stable for 10 minutes in PhaseC_District
- [ ] No actor authority errors in output log
- [ ] No replication warnings for new Phase C components
- [ ] Player positions sync correctly between server and client
- [ ] Join-in-progress works: late-joining client sees correct world state
- [ ] No Phase A or Phase B regression introduced

---

## Step 1 Specific — Environment Setup

- [x] PhaseC_District map confirmed as main production map
- [x] Folder structure created: World, Systems, UI, Docs
- [x] World subfolders created: Maps, Geometry, Props, Materials, Decals, Audio, Signage, Landmarks, ZoneSetups
- [x] Systems subfolders created: Presence, SocialHeat, Reputation, Training, Characters, PremiumPlaceholders
- [x] UI subfolders created: World, Social
- [x] SoulCity asset source confirmed at /Game/SoulCity — locked, not moved
- [x] Guardrails document created: Docs/PhaseC_Guardrails.md
- [x] Feature buckets document created: Docs/PhaseC_FeatureBuckets.md
- [x] Validation checklist created: Docs/PhaseC_ValidationChecklist.md
- [x] No lighting added
- [x] No buildings placed
- [x] Landscape unchanged

---

## Notes

- All validation sessions: minimum 2-player listen server
- Test map: `/Maps/Test` — delete or archive after validation
- Production map: `PhaseC_District` — never used for raw validation tests
- Document all failures here before escalating
