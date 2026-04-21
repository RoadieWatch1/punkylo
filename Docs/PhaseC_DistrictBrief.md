# Phase C — District Design Brief

**Status:** ACTIVE — Step 2 Complete
**Version:** Clean Restart — 2026-03-31
**Map:** `/Content/Maps/Worlds/PhaseC_District/PL_PhaseC_District.umap`
**Asset Source:** `/Game/SoulCity` only (locked)

---

## 1. District Identity

**Type:** Dense cyberpunk social block

**Core Purpose:**
- Multiplayer gathering space — not a combat arena
- Social visibility — players see and are seen
- First impression of the PunkyLo world

**Emotional Tone:**
- Controlled chaos — the space has rules, but players push against them
- Urban pressure — density, elevation, enclosure create psychological weight
- Social energy vs authority tension — the plaza pulls people together; the authority zone watches from above

**What makes this district feel intentional:**
- Every zone has a reason to exist in relation to every other zone
- Authority is always visible from the social center — power is never hidden
- Side routes offer escape from visibility, which makes visibility feel meaningful
- Arrival is a threshold — you descend into the world, you don't just appear in it

---

## 2. The 4 Mandatory Zones

### ZONE 1 — Arrival

| Property | Value |
|---|---|
| Role | First player spawn + orientation point |
| Elevation | +3m above plaza (Z = +300) |
| Size | 50m W × 30m L |
| Center | (0, −4500) |

**Purpose:** The threshold. Players enter here before they enter the world. Compressed, walled, controlled — forces orientation before freedom.

**Feel:** Controlled. Slightly clean. Transitional.
- Three walls surround the player immediately
- A gate frame (12m wide, flanked by two 5m pillars) frames the first view
- First sight line through the gate: plaza center, authority zone visible in the distance
- Ramp descends 3m into the plaza — the descent is the transition

**What it must NOT feel like:** An arbitrary spawn room. It is a deliberate airlock.

---

### ZONE 2 — Plaza (CORE)

| Property | Value |
|---|---|
| Role | Main multiplayer hub + social center |
| Elevation | Z = 0 (baseline) |
| Size | 70m W × 45m L |
| Center | (0, 0) |

**Purpose:** The center of everything. All other zones orbit this space. Players gather, see each other, and choose where to go from here.

**Feel:** Open. Visible. Active.
- Largest open space in the district
- Central plinth (10m × 10m × 2m) at the origin — natural gathering point, elevated enough to be a stage
- Four clear entry mouths: south (arrival), north (authority), east (side route), west (side route)
- Partial east/west boundary walls frame the space without sealing it
- Authority zone visible at the north face — players on the elevated platform can look down

**What it must NOT feel like:** An empty flat square. The plinth, wall framing, and viewlines give it structure.

---

### ZONE 3 — Side Routes (East + West)

| Property | Value |
|---|---|
| Role | Exploration + tension + future system hooks |
| Elevation | Z = 0, ceiling at Z = +300 (3m clearance) |
| Width | 12m each |
| Length | ~70m each (with bend) |

**Purpose:** Escape from visibility. Players who take the routes disappear from plaza view — which makes the choice feel meaningful.

**Feel:** Tight. Layered. Slightly hidden.
- Low ceiling creates pressure immediately on entry
- A bend in the route breaks sightlines — players inside cannot see the plaza, and plaza players cannot see inside
- Routes loop back toward the Authority Zone flanks (reconnect — no dead ends)
- Information asymmetry: route players can flank authority without being seen on the main ramp

**What they must NOT feel like:** Decoration. They must feel like a genuine alternative path with a trade-off (lose visibility, gain positioning).

---

### ZONE 4 — Authority

| Property | Value |
|---|---|
| Role | Power presence + psychological pressure |
| Elevation | +5m above plaza (Z = +500) |
| Size | 50m W × 26m L |
| Center | (0, +4500) |

**Purpose:** The watcher. Authority does not chase — it overlooks. Players who reach the platform gain a full view of the plaza; players in the plaza always know the authority zone is there.

**Feel:** Elevated. Structured. Dominant.
- Three-wall enclosure (north, east, west) — open south face looks straight down to plaza
- Central tower (15m × 15m × 10m) at platform center — largest vertical element in the district
- Two ramp approaches (east and west) — exposed ascent, intentionally vulnerable
- Side route exits emerge at the authority platform flanks — alternative arrival, less visible

**What it must NOT feel like:** Just a high platform. The tower, the open south face, and the exposed ramps make it a statement.

---

## 3. Player Flow

**Primary path:**
```
Arrival → ramp down → Plaza → (choice)
                                ├── Ramp up → Authority (exposed, direct)
                                ├── Side Route West → Authority flank (hidden, longer)
                                └── Side Route East → Authority flank (hidden, longer)
```

**On spawn:**
1. Player spawns in Arrival — compressed, walled
2. First view through gate: plaza center, plinth, authority zone tower at distance
3. Descends 12m ramp — the descent is a deliberate entering-the-world beat
4. Reaches plaza — open, multiple players visible, three destinations ahead

**Rules that must not break:**
- Arrival MUST lead naturally into Plaza — no fork, no confusion
- Plaza MUST be the anchor all other zones return to
- Routes MUST branch OFF Plaza and reconnect (no dead ends)
- Authority MUST be visible FROM Plaza at all times (partial or full)

---

## 4. Spatial Layout (Top-Down)

```
                        NORTH (+Y)

      ┌─────────────────────────────────┐
      │        AUTHORITY ZONE           │  Z = +500 (5m above plaza)
      │  Imposing. Elevated. Watching.  │  Y: 3200 → 5800
      │        [Central Tower]          │
      └───────────┬─────────────────────┘
                  │ ramp (east + west)
      ┌───────────▼─────────────────────┐
      │          SOCIAL PLAZA           │  Z = 0 (ground)
┌─────┤   Open. Central. Focal Point.   ├─────┐
│SIDE │       [Central Plinth]          │SIDE │
│ROUT │  entries: S, N, E, W           │ROUT │
│WEST └───────────┬─────────────────────┘EAST │
│                 │ ramp down                  │
└─────────────────▼──────────────────────────-┘
      ┌───────────────────────────────────┐
      │          ARRIVAL ZONE             │  Z = +300 (3m above plaza)
      │  [Entry Gate]  Controlled. First  │  Y: −6000 → −3000
      │       view into the world         │
      └───────────────────────────────────┘

                        SOUTH (−Y)
```

**Viewlines from Plaza center:**

| Looking | Can See | Cannot See |
|---|---|---|
| North | Authority platform + tower | Inside side routes |
| South | Arrival gate (above) | Arrival interior details |
| East | Side route entry mouth | Route interior (bend blocks it) |
| West | Side route entry mouth | Route interior (bend blocks it) |

**From Arrival gate:** Can see plaza center + authority zone at distance. Side routes not visible.
**From Authority platform:** Full overlook of entire plaza. Cannot see inside side routes.
**From side route interior:** Partial blindness — can only see plaza once at the exit mouth.

---

## 5. Zone Size Relationships

| Zone | Footprint | Relative Size | Why |
|---|---|---|---|
| Plaza | 70m × 45m | LARGEST | Must feel dominant — all flow passes through |
| Arrival | 50m × 30m | Medium | Enough to hold multiple spawned players |
| Authority | 50m × 26m | Medium (vertical emphasis) | Position + tower make it imposing, not scale |
| Side Routes | 12m × ~70m each | Narrow / smallest | Pressure through constraint, not size |

**Rule:** Plaza wins on footprint. Authority wins on height. Routes win on tension. Arrival wins on framing.

---

## 6. Elevation Summary

| Zone | Z Height | Relative to Plaza |
|---|---|---|
| Arrival floor | Z = +300 | +3m above plaza |
| Plaza floor | Z = 0 | baseline |
| Side routes | Z = 0 | same as plaza |
| Side route ceilings | Z = +300 | 3m clearance (low) |
| Authority platform | Z = +500 | +5m above plaza |
| Authority tower top | Z = +1500 | +15m — tallest silhouette |

---

## 7. Traversal Rules

- **No dead ends.** Every path returns to another zone.
- **Side routes loop.** West route exits near Authority west ramp. East route exits near Authority east ramp. Players who enter routes will emerge at authority flanks.
- **All zone connections are ramp-based.** No teleports, no gaps, no jump-required transitions.
- **Arrival → Plaza is one-way at spawn.** Players descend into the world. The ramp can be climbed back, but the spawn context makes it feel directional.
- **Plaza is always re-achievable.** From any zone, a player can return to plaza in one movement decision.

---

## 8. What This District Is NOT

- Not a combat arena (no cover-based layout)
- Not a hub lobby (it has identity and tension, not just a waiting room)
- Not a generic city block (every zone has a reason relative to the others)
- Not a complete city (one tight district, fully intentional)
