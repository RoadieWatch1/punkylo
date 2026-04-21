# Phase C Validation Checklist

**Status:** ACTIVE — World Slice blockout script ready, awaiting editor execution
**Last Updated:** 2026-03-28

Each item must be validated in `/Maps/Test` BEFORE the feature is used in `/Maps/Worlds/PhaseC_District`.

---

## World Traversal Readability

- [ ] Player can traverse full district without clipping or collision gaps
- [ ] No navigation mesh holes or dead zones
- [ ] All zone entry/exit points are traversable
- [ ] 2-player session: both players traverse simultaneously without desyncs
- [ ] Frame time acceptable at all district positions (target: 60fps, mid-spec)

**Status:** READY TO TEST — Run `Build_PhaseC_District.py`, then `Build > Build Paths`, then PIE.

**Design notes (pre-test):**
- Arrival → Plaza ramp: 20m run over 3m rise (~8.5°) — should feel natural
- Authority ramps (east + west): 18m run over 5m rise (~15.5°) — steeper, intentional
- Side routes have bend with occlusion slab — need to confirm sightline break works in PIE
- All zones have floor geometry — clipping risk low but check ramp junction edges
- NavMesh: single volume 140m x 120m x 25m — should cover all surfaces incl. elevated zones

---

## Zone Clarity (Arrival / Plaza / Routes / Authority)

- [ ] Arrival zone is identifiable as entry point without UI
- [ ] Plaza zone reads as social/gathering space without UI
- [ ] Routes read as directional transit corridors without UI
- [ ] Authority zone reads as high-tension / controlled area without UI
- [ ] Zone transitions are perceptible (light color shift at each boundary)
- [ ] Blind playtest: 3/3 testers identify zone type correctly

**Status:** READY TO TEST — Step 3 lighting script deployed. Run in PIE after executing Step3_PhaseC_ZoneMood.py.

**Design notes (pre-test):**
- Arrival: walled on 3 sides, single gate, elevated — clarity through compression
- Plaza: largest open space, central plinth as focal point, 4 clear entry mouths
- Side Routes: low ceiling (3m vs open sky plaza), narrow (12m), bent — clarity through pressure and partial blindness
- Authority: 5m elevated, 3-wall enclosure, imposing tower, overlooks entire plaza — clarity through height + framing
- Zone Mood (lighting) is a SEPARATE bucket — these clarity checks are layout-only at Step 2
- "Zone transitions perceptible" will remain partial until Zone Mood bucket is activated

---

## Multiplayer Gathering Stability

- [ ] 2-player session stable for 10 minutes in PhaseC_District
- [ ] No actor authority errors in output log
- [ ] No replication warnings for new Phase C components
- [ ] Player positions sync correctly between server and client
- [ ] Join-in-progress works: late-joining client sees correct world state

**Status:** READY TO TEST — run PIE after Build_PhaseC_District.py execution.

**What to look for:**
- Watch for: late-join actor state (run join test after 30s in session)
- Authority platform actors: confirm no replication warnings (elevated zones can expose transform sync issues)
- Run `stat net` in console during PIE to spot bandwidth spikes

---

## Identity Readability at Distance

- [ ] Player A can identify Player B's character at 20m (no UI)
- [ ] Player A can identify Player B's character at 50m (no UI)
- [ ] Player A can identify Player B's character at 100m (no UI)
- [ ] All 5 character slots are visually distinct from each other
- [ ] Identity reads correctly on both server and client

**Status:** TODO — depends on Character Support (5 free)

---

## Social Presence Clarity

- [ ] Empty zone feels distinct from zone with 2 players (visual only)
- [ ] No backend calls made during social presence evaluation
- [ ] No UI elements display social state
- [ ] Social presence logic is removable without breaking other systems

**Status:** TODO — depends on Social Heat

---

## Future Social Heat Visibility (STUB)

<!-- TODO: Define validation criteria when Social Heat bucket is activated -->
<!-- Expected: heat read at zone level, no backend dependency, UI-free in Phase C -->

- [ ] [STUB — not yet defined]

**Status:** DEFERRED — Social Heat bucket not yet active

---

## Ritual Visibility (STUB)

<!-- TODO: Define validation criteria when Signature Visual Ritual bucket is activated -->
<!-- Expected: input binding logs correctly, no visual output in Phase C stub state -->

- [ ] Input binding exists and logs server-side without error
- [ ] No visual output is produced (confirmed stub state)
- [ ] Animation slot reserved without breaking existing animations

**Status:** STUB — input binding only, no visual output expected in Phase C

---

## Audio Presence

- [ ] Each zone has a distinct ambient audio character
- [ ] No missing audio asset warnings in session
- [ ] Footstep surfaces: concrete, gravel, interior all play correctly
- [ ] Audio does not stutter or desync in 2-player session

**Status:** TODO — depends on Presence-First Audio

---

## Reputation Shell Integrity

- [ ] PL_ReputationComponent compiles without error
- [ ] Component attaches to PlayerState without conflict
- [ ] Server and client hold identical values in 2-player session
- [ ] No gameplay behavior triggered by component presence

**Status:** TODO — depends on Reputation Shell

---

## Zone Mood — Visual Readability

- [ ] Arrival reads as cool blue-white, controlled
- [ ] Plaza reads as neon-lit, energized, visually dominant
- [ ] Side Routes read as dim, uncertain, oppressive
- [ ] Authority reads as cold, harsh, watched
- [ ] Fog is present but does not obscure player movement
- [ ] Zone color transitions are perceptible at entry thresholds
- [ ] Volumetric fog visible around plaza neon sources

**Strongest zone:** _[fill in after PIE test]_
**Weakest zone:** _[fill in after PIE test]_
**Adjustments needed:** _[fill in after PIE test]_

**Status:** READY TO TEST — run Step3_PhaseC_ZoneMood.py then 2-player PIE

---

## Player Visibility Under Zone Lighting

- [ ] Players clearly visible in Arrival (cool panels — should be fine)
- [ ] Players clearly visible in Plaza (neon is bright — watch for silhouette loss in magenta)
- [ ] Players clearly visible in Side Routes (dim — this is intentional; confirm not unplayable)
- [ ] Players clearly visible on Authority platform (harsh spots — confirm no blown-out silhouettes)
- [ ] Player character reads at 20m in Plaza lighting
- [ ] No zone makes it impossible to distinguish friend from environment

**Status:** READY TO TEST

---

## Surface Quality — Step 4A

- [ ] All blockout actors have non-default materials (no world-grid gray visible)
- [ ] Arrival floor/ramp reads as clean concrete (cool-gray)
- [ ] Arrival walls read as metal (darker, slight sheen)
- [ ] Plaza floor reads as wet/reflective (dark, neon color pickup visible)
- [ ] Plaza plinth reads as distinct surface from floor
- [ ] Side routes read as clearly darker and dirtier than plaza
- [ ] Route ceilings and walls match floor tone (uniform worn concrete)
- [ ] Authority floor/tower reads as same material family as Arrival (clean but harsh)
- [ ] Authority walls read as metal (sharper than Arrival metal due to lighting)
- [ ] Base ground reads as asphalt (near-black, visible under/around zones)

**Strongest surface zone:** _[fill after PIE]_
**Weakest surface zone:** _[fill after PIE]_
**Texture assignment status:** ⚠ Color-tinted only until Megascans textures assigned to MI_PL_* instances

**Status:** READY TO TEST — run Step4A_PhaseC_VisualIdentity.py then PIE

---

## Visual Identity — Pass 1 (Step 4A)

- [ ] Neon prototype visible in scene (emissive strips on plaza walls + plinth)
- [ ] Teal strips visible on plaza west boundary
- [ ] Magenta strips visible on plaza east boundary
- [ ] Purple plinth floor edge accents visible
- [ ] Cold blue lintel strip visible at Arrival gate
- [ ] Dirty yellow threshold strips visible at route entrances
- [ ] Emissive materials contribute to Lumen GI (neon color visible on nearby floor/wall)
- [ ] Zone color differentiation readable without UI (Arrival = cool blue, Plaza = neon, Routes = dim, Auth = cold white)
- [ ] Structural dressing present: pillars at plaza plinth (4), authority south face (2), arrival gate (2), arrival interior (2)
- [ ] Pipe runs present in side routes (2 per route, ceiling level)
- [ ] Decals present: grime in side routes (9), edge wear in plaza (3), tower stain in authority (1)
- [ ] Dressing actors have no unintended collision blocking player paths
- [ ] No visual clutter — dressing feels intentional, not spammed

**Neon notes:** _[fill after PIE — which strips read strongest]_
**Dressing notes:** _[fill after PIE — what still looks sparse]_
**Still looks like blockout:** _[fill after PIE]_

**Status:** READY TO TEST — run Step4A_PhaseC_VisualIdentity.py then PIE

---

## Multiplayer — Step 4A Regression Check

- [ ] 2-player session stable after Step 4A (no new crashes or authority errors)
- [ ] Players clearly visible in all 4 zones under new materials + dressing
- [ ] No dressing actor causes player collision or pathing issue
- [ ] Frame time acceptable with ~40 new actors (target: 60fps mid-spec)
- [ ] Decals rendering without overdraw artifacts or log warnings
- [ ] Lumen GI updates correctly when moving between zones (no stale GI patches)

**PIE result:** _[fill after test]_
**Frame time delta:** _[fill — compare to pre-Step-4A baseline]_

**Status:** READY TO TEST

---

## Notes

- All validation sessions: minimum 2-player listen server
- Test map: `/Maps/Test` — delete or archive test-specific levels after validation
- Production map: `/Maps/Worlds/PhaseC_District` — never used for validation tests
- Document failures here before escalating

---

## Step 2 Pre-Execution Checklist

Before running Build_PhaseC_District.py:
- [ ] UE5 project compiled (PL_GameMode must exist)
- [ ] `/Content/Maps/Worlds/PhaseC_District/` folder visible in Content Browser
- [ ] No unsaved changes in editor that could conflict

After running the script:
- [ ] Level opens at `/Maps/Worlds/PhaseC_District/PL_PhaseC_District`
- [ ] All 4 zones visible in editor viewport
- [ ] Run `Build > Build Paths` to generate NavMesh
- [ ] Launch 2-player PIE (listen server mode)
- [ ] Walk each zone and record findings above
