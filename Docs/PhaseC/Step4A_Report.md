# Phase C — Step 4A Report: First-Pass Visual Identity
**Status:** SCRIPT COMPLETE — Awaiting PIE validation
**Last Updated:** 2026-03-29
**Script:** `Content/Python/Step4A_PhaseC_VisualIdentity.py`

---

## 1. Materials Created / Applied

### Surface Material Instances (output: `/Game/Materials/PhaseC/`)

| Asset | Parent | Purpose | Key Parameters |
|---|---|---|---|
| `MI_PL_Concrete` | M_MS_Surface_Material | Arrival floors + ramps, Authority floor + tower, Plaza plinth + walls | Tint: cool gray (0.44, 0.45, 0.49), Roughness: 0.82, Tiling: 4.0 |
| `MI_PL_Concrete_Worn` | M_MS_Surface_Material | Side Routes — all surfaces | Tint: dark warm gray (0.21, 0.19, 0.17), Roughness: 0.93, Tiling: 3.0 |
| `MI_PL_Metal` | M_MS_Surface_Material | Arrival walls + lintel, Authority walls + parapets | Tint: dark blue-gray (0.27, 0.30, 0.36), Roughness: 0.50, Tiling: 2.0 |
| `MI_PL_Asphalt` | M_MS_Surface_Material | Base ground plane | Tint: near-black (0.09, 0.09, 0.11), Roughness: 0.88, Tiling: 5.0 |
| `MI_PL_WetSurface` | M_MS_Surface_Material | Plaza floor | Tint: dark blue (0.07, 0.08, 0.13), Roughness: 0.07 (wet), Tiling: 5.0 |

### Neon Emissive Material Instances

| Asset | Parent | Zone | Color |
|---|---|---|---|
| `MI_PL_Neon_Teal` | M_SimpleGlow | Plaza west walls | (0.0, 1.0, 0.85) @ 3.0 intensity |
| `MI_PL_Neon_Magenta` | M_SimpleGlow | Plaza east walls | (1.0, 0.14, 0.64) @ 3.0 intensity |
| `MI_PL_Neon_ColdBlue` | M_SimpleGlow | Arrival gate lintel | (0.54, 0.74, 1.0) @ 2.5 intensity |
| `MI_PL_Neon_Yellow` | M_SimpleGlow | Route entrance thresholds | (0.80, 0.68, 0.10) @ 1.8 intensity |
| `MI_PL_Neon_PlinthEdge` | M_GradientGlow | Plaza plinth floor edges | (0.74, 0.48, 1.0) @ 2.0 intensity |

### Material Application Map

| Zone | Floor | Walls | Special |
|---|---|---|---|
| Arrival | MI_PL_Concrete | MI_PL_Metal | Pillars + ramp = concrete |
| Social Plaza | MI_PL_WetSurface | MI_PL_Concrete | Plinth = concrete |
| Side Routes | MI_PL_Concrete_Worn | MI_PL_Concrete_Worn | Ceiling + occluder = worn |
| Authority | MI_PL_Concrete | MI_PL_Metal | Tower + tower base = concrete |
| Base Ground | MI_PL_Asphalt | — | — |

---

## 2. Megascans Assets Used

**Source:** Fab plugin Megascans parent materials (shipped with engine, always on disk — no download required for script execution)

| Asset Path | Role |
|---|---|
| `/Engine/Plugins/Fab/Content/Materials/Standard/M_MS_Surface_Material` | Parent for all 5 surface MIs |
| `/Engine/Plugins/Fab/Content/Materials/Standard/M_MS_Decal_Material` | Parent for all 13 decal actors |

**Texture status:** Material instances use Megascans default fallback textures until specific surface textures are downloaded from Fab and assigned manually.

**Upgrade path (when ready):**
1. In Fab, download free Megascans surfaces: concrete, worn concrete, metal panel, asphalt
2. Open each `MI_PL_*` → assign Albedo / Normal / Roughness / AO texture maps
3. Decal actors → assign Megascans grime decal texture to DecalComponent material

---

## 3. Existing Project Assets Used

| Asset | Location | Used For |
|---|---|---|
| `M_SimpleGlow` | LevelPrototyping/Interactable/JumpPad/Assets/Materials/ | Parent for 4 neon MIs |
| `M_GradientGlow` | same | Parent for plinth edge MI |
| `SM_ChamferCube` | LevelPrototyping/Meshes/ | 10 structural pillars / gate trim |
| `SM_Cylinder` | LevelPrototyping/Meshes/ | 4 pipe runs in side routes |
| `Cube` (BasicShapes) | /Engine/BasicShapes/ | 14 neon strip meshes |

**Not used this step** (available for later): SM_DoorFrame_Edge, SM_DoorFrame_Corner, SM_Ramp, NS_JumpPad

---

## 4. Zone-by-Zone Improvements

### Arrival Zone
- **Before:** Uniform gray cube geometry, default material
- **After:** Cool-gray concrete floors/ramps. Dark blue-gray metal walls. Cold blue neon strip on gate lintel. Two slender ChamferCube gate-trim accents flank the 12m gate opening. Two interior depth pillars at the back of the platform create spatial layering.
- **Result expected:** Clean, technological feel. Metal-on-concrete contrast reinforces the "controlled" read without requiring any prop assets.

### Social Plaza
- **Before:** Gray floor slab, gray walls, gray plinth
- **After:** Wet dark-reflective floor (neon color will bounce in Lumen). Concrete plinth and boundary walls. Teal strips on west walls, magenta on east. Four purple plinth edge floor accents. Four ChamferCube pillars flanking the central plinth create a defined gathering zone within the open plaza.
- **Result expected:** The neon + wet floor combination is the primary identity read. Even without downloaded Megascans textures, the contrast between the near-black wet floor and the emissive strips should establish the plaza's energy.

### Side Routes
- **Before:** Same gray as everything else
- **After:** Uniform dark worn concrete (floor, walls, ceiling, occluder). Dirty yellow threshold strips at both route entrances (visible from plaza as a warning signal). Four ceiling-level pipe runs (2 per route) break the uniform wall geometry and add industrial texture without any purchased props. Nine grime/stain decals at varied positions and rotations.
- **Result expected:** Darkest zone by material tint. Combined with Step 3's dim dirty yellow lighting, should read as clearly degraded vs plaza. Pipe runs ensure the ceiling isn't just a flat gray slab.

### Authority Zone
- **Before:** Gray platform, gray tower, gray walls
- **After:** Clean concrete floors/ramps/tower (same material family as Arrival — clean, controlled). Dark metal walls. Two 800 UU tall ChamferCube pillars on the south face, visible from the plaza looking north — creates imposing silhouette against Step 3's cold white lighting. One faint stain decal at tower base (minimal — authority is clean).
- **Result expected:** Clean authority materials + harsh cold lighting should create the strongest contrast with Side Routes. The tall south-face pillars contribute to the elevation read from plaza level.

---

## 5. What Still Looks Like Blockout

After Step 4A execution (before texture assignment):

- **All surfaces** will read as flat/uniform until Megascans textures are assigned to the MI_PL_* instances. The color-parameter tints differentiate zones but don't add surface detail.
- **Neon strips** are thin cube meshes. They provide light color and emissive contribution but don't look like real neon tubes yet. This is acceptable for Pass 1 — real neon geometry needs a Fab pack.
- **Plaza feels empty** beyond the plinth and 4 pillars. No world props, no ground-level debris, no signage. The zone mood and neon strips exist but there is nothing to look at except the lighting.
- **Authority tower** is a plain ChamferCube-shaped block. Geometry-only — no surface detail, no windows, no tech panels.
- **Route ceilings** are flat slabs. Pipes break this slightly but the ceiling is still recognizably a box.
- **Ramps** are flat slabs. No curb geometry, no handrails, no edge definition.

---

## 6. What Is Missing Visually

**Missing — will need Fab packs (deferred past Step 4A):**

| Gap | Zone(s) | Priority |
|---|---|---|
| Megascans surface textures assigned to MI_PL_* | All | HIGH — biggest delta from blockout to real |
| Megascans grime decal textures on decal actors | Routes, Plaza | HIGH |
| Neon tube mesh geometry (real cylinders/channel letters) | Plaza, Routes | HIGH |
| Ground-level props (crates, barriers, debris, cable bundles) | Routes, Plaza | HIGH |
| Signage (any sign, any language) | Plaza, Arrival | MEDIUM |
| Window panels / tech detail on tower and walls | Authority | MEDIUM |
| Holographic panel accent (authority tower face) | Authority | MEDIUM |
| Graffiti decal set (stylized, not grime) | Side Routes | MEDIUM |
| Ceiling cable runs / conduit detail | Routes | LOW |
| Edge trim pieces on ramps and platform edges | All | LOW |

---

## 7. Multiplayer Validation Results

**Status:** NOT YET RUN — requires manual PIE execution after script

**To run:**
1. Execute `Step4A_PhaseC_VisualIdentity.py` via `Tools > Execute Python Script`
2. Launch 2-player PIE (listen server mode)
3. Walk all 4 zones on both server and client viewports
4. Fill in `PhaseC_ValidationChecklist.md` → Surface Quality + Visual Identity Pass 1 + Multiplayer Regression sections

**Expected issues to check:**
- ChamferCube pillars near plaza plinth: confirm player can pass all 4 gaps freely (pillar offset is 1400 UU from origin, plinth edge is 500 UU — gap is 900 UU per side, should be fine for 180cm player)
- Authority south-face pillars (X = ±2000): confirm players on ramps don't clip pillar base
- Route pipe runs: pipes at Z = 270 with 30 UU diameter — well above player head height (180cm = 1800 UU), no collision risk
- Neon strip actors (8 UU deep cubes): confirm no collision issues at wall faces

---

## Stop Condition

Step 4A is complete when:
- Script has been executed successfully in editor
- All MI_PL_* have Megascans textures assigned
- 2-player PIE passes all checkboxes in PhaseC_ValidationChecklist.md → Surface Quality + Visual Identity Pass 1 sections
- No regression in any Step 2 or Step 3 checklist items

**Do NOT start Step 4B or Step 5 until this is done.**
