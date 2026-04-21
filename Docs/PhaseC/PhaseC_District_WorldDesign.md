# PL_PhaseC_District — World Design Reference

**Status:** ZONE MOOD — lighting + atmosphere added (Step 3)
**Last Updated:** 2026-03-29
**Scripts:**
- Step 2: `Content/Python/Build_PhaseC_District.py`
- Step 3: `Content/Python/Step3_PhaseC_ZoneMood.py`

---

## Spatial Overview

**Total footprint:** ~120m x 90m (compact and dense)
**UE5 coordinate convention:** X = East/West, Y = North/South, Z = Up
**Ground level (Social Plaza):** Z = 0

```
                        NORTH (+Y)

          ┌─────────────────────────────────┐
          │        AUTHORITY ZONE           │  Z = +500 (5m above plaza)
          │  Imposing. Elevated. Watching.  │  Y: 3200 → 5800
          │        [Central Tower]          │
          └───────────┬─────────────────────┘
                      │ ramp (both sides)
          ┌───────────▼─────────────────────┐
          │          SOCIAL PLAZA           │  Z = 0 (ground)
  ┌───────┤   Open. Central. Focal Point.   ├───────┐
  │ SIDE  │         [Plaza Center]          │ SIDE  │
  │ ROUTE │  entry/exit: S, N, E, W         │ ROUTE │
  │ WEST  └───────────┬─────────────────────┘ EAST  │
  │                   │ ramp                         │
  └────────────────── ▼ ──────────────────────────── ┘
          ┌───────────────────────────────────────┐
          │            ARRIVAL ZONE               │  Z = +300 (3m above plaza)
          │  [Entry Gate]   Controlled. Framed.   │  Y: -6000 → -3000
          │          first view into world        │
          └───────────────────────────────────────┘

                        SOUTH (-Y)
```

---

## Zone Specifications

### ARRIVAL ZONE
| Property | Value |
|---|---|
| Center | (0, -4500) |
| Size | 50m W x 30m L |
| Elevation | Z = +300 (3m above plaza) |
| Walls | Back + sides enclosed, north face open with gate frame |
| Entry Gate | 12m wide gap, flanked by two 5m pillars |
| Flow | Players spawn here, see plaza below, descend ramp |
| Feel | Controlled, compressed, technological |

**Key geometry:**
- Elevated platform (50m x 30m x 0.5m)
- Back wall (south face, full width, 5m tall)
- Side walls (east & west, full length, 5m tall)
- Entry pillar pair (5m x 5m x 5m each, flanking gate opening)
- Ramp down: 12m long, bridges Z=300 to Z=0, angled ~14°

**Player spawn positions (Arrival):**
- PS_Arrival_1: (−800, −4800, 400)
- PS_Arrival_2: ( 800, −4800, 400)
- PS_Arrival_3: (   0, −5200, 400)

---

### SOCIAL PLAZA
| Property | Value |
|---|---|
| Center | (0, 0) |
| Size | 70m W x 45m L |
| Elevation | Z = 0 |
| Boundaries | Semi-open: walls at east/west, open north to authority, open south to arrival ramp |
| Focal Point | Central plinth/platform (10m x 10m x 2m) at origin |
| Entries | 4: South (arrival ramp), North (authority ramp), East (side route), West (side route) |
| Feel | Visibility, status, social density |

**Key geometry:**
- Plaza floor slab (70m x 45m x 0.5m) at Z=0
- Central plinth (10m x 10m x 2m) at Z=0 center (focal gathering point)
- East boundary wall: partial (30m long, 4m tall), with 12m gap for side route entry
- West boundary wall: same (mirrored)
- North face: open (ramp to authority visible)
- South face: open (arrival ramp descends from here)

---

### SIDE ROUTE WEST
| Property | Value |
|---|---|
| Path | Plaza west edge → bends → loops to Authority Zone west side |
| Width | 12m |
| Length | ~70m total (with bend) |
| Elevation | Z = 0 (ground level) |
| Ceiling | 3m (low — creates pressure) |
| Feel | Hidden, narrow, less controlled |

**Route geometry:**
1. Entry mouth: West plaza edge at X=−3500, Y=−1000 to Y=+1000
2. Corridor segment A: runs west 20m (X: −3500 → −5500), Y center = 0
3. Bend: jogs north (Y: 0 → 2000), creates partial occlusion
4. Corridor segment B: runs back east toward Authority Zone west ramp
5. Low ceiling throughout (slab at Z=300, 3m clearance)
6. Inner wall: single perpendicular slab at bend for occlusion

**SIDE ROUTE EAST:** Mirror of West (positive X values)

---

### AUTHORITY ZONE
| Property | Value |
|---|---|
| Center | (0, 4500) |
| Size | 50m W x 26m L |
| Elevation | Z = +500 (5m above plaza) |
| Walls | Three sides enclosed (north, east, west), south face open toward plaza |
| Central Tower | 15m x 15m x 10m imposing structure at center |
| Feel | Pressure, intimidation, hierarchy |

**Key geometry:**
- Elevated platform (50m x 26m x 0.5m) at Z=500
- North wall (back, full width, 6m tall)
- East wall + West wall (full length, 6m tall)
- South face: open — unobstructed view down to plaza
- Central tower: 15m x 15m x 10m at platform center, slightly forward
- Ramp west: connects plaza Z=0 to authority Z=500, 20m run, angled ~14°
- Ramp east: mirror

---

## Player Flow Description

**Primary loop:**
```
Arrive → Arrival Gate → Ramp Down → Social Plaza ← → Authority (via ramp)
                                         ↕
                              Side Routes (west or east)
```

**On spawn:**
1. Player spawns in Arrival (elevated, compressed)
2. First sight line: looks down through gate into plaza — can see central plinth, authority zone in background
3. Walks down 12m ramp — descent creates a natural "entering the world" beat
4. Reaches plaza — open, multiple players visible, multiple destinations clear

**Side routes:**
- Accessed from plaza east/west gaps in boundary walls
- Players disappear from plaza view quickly (narrow + bend)
- Emerge near Authority zone's flanks
- Creates information asymmetry vs direct ramp players

**Authority zone:**
- Players ascending the authority ramp are visible from plaza (exposed)
- Once on Authority platform: overlook view of entire plaza
- High-ground tactical/social position — clear status signal

---

## Viewlines

| From | Can See | Cannot See |
|---|---|---|
| Arrival gate | Plaza center + Authority zone (distance) | Side routes |
| Plaza center | All 4 zone entry points | Interior of side routes |
| Side route interior | Nothing (partial occlusion) | Plaza until exit mouth |
| Authority platform | Entire plaza | Inside side routes |

---

## Verticality Summary

| Zone | Elevation | Relative to Plaza |
|---|---|---|
| Arrival | Z = +300 | +3m |
| Social Plaza | Z = 0 | baseline |
| Side Routes | Z = 0 | same as plaza |
| Side Route ceilings | Z = +300 | enclosed feel |
| Authority platform | Z = +500 | +5m |
| Authority tower top | Z = +1500 | +15m silhouette |

---

## NavMesh

- Single `NavMeshBoundsVolume` covering full district
- Bounds: 14000 x 12000 x 2000 (140m x 120m x 20m)
- Center: (0, 0, 750)
- Covers all floor surfaces including elevated zones and ramps
