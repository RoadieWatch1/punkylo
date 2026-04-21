# PunkyLo — Multiplayer Vertical Slice
**Phase B Locked Document | Completed 2026-03-28**

This document records what Phase B proved, what was built, what was validated, and what settings remain active. Future development sessions must treat the working multiplayer slice as stable and validated. Do not replace or redesign the test path without a deliberate Phase C decision.

---

## 1. Phase B Goal

Establish a minimal, controlled multiplayer test environment and prove that the PunkyLo gameplay framework supports:

- Multiple players joining the same session
- Players seeing each other
- Independent movement control per player
- Movement and rotation replication across all connected instances

---

## 2. What Phase B Proved

| Validation Target | Result |
|---|---|
| Host (listen server) launches | Confirmed |
| Second player joins same session | Confirmed |
| Both players load into same map | Confirmed |
| Players can see each other | Confirmed |
| Independent control per player | Confirmed |
| Movement replication (client → server) | Confirmed |
| Movement replication (client → client) | Confirmed |
| Rotation replication | Confirmed |
| PL_ framework intact throughout | Confirmed |

---

## 3. Test Environment

**Map:** `/Game/Maps/Test/MultiplayerTestMap`

**Map contents:**
- Flat ground plane (10,000 × 10,000 UU, Engine Plane mesh)
- 6 PlayerStart actors at 800 UU spacing
- Directional light, Sky Atmosphere, Sky Light
- No decorative content

**Host method:** PIE Listen Server (`PIE_ListenServer`)

**Join method:** PIE automatic client connection (localhost:17777)

**Players tested:** 3 (Server 0 + Client 1 + Client 2)

**Active PIE config:**
- `PlayNetMode=PIE_ListenServer`
- `PlayNumberOfClients=3`
- Online subsystem: Null (no EOS credentials required)

---

## 4. Known Limitations

**Mac PIE host-window input:** On macOS, the PIE Listen Server window (Server 0) does not reliably capture gameplay keyboard input. The editor viewport competes with the game for focus. This is a UE5/Mac PIE environment limitation, not a framework bug. Replication was validated using the two client windows (Client 1 and Client 2), which are fully controllable.

**No animations:** `PL_Character` uses `SKM_Manny_Simple` in T-pose. No animation blueprint is assigned. Animation is not a Phase B requirement.

**No production session system:** The multiplayer path uses Unreal's built-in PIE listen server flow only. No EOS sessions, lobbies, or matchmaking are present. This is intentional for Phase B.

---

## 5. Files and Settings Modified During Phase B

### New Files
| File | Purpose |
|---|---|
| `Content/Maps/Test/MultiplayerTestMap.umap` | Multiplayer test map |
| `Content/Python/Setup_MultiplayerTestMap.py` | One-time editor script used to populate the test map |
| `Docs/PhaseB_MultiplayerVerticalSlice.md` | This document |

### Modified Source Files
| File | Change |
|---|---|
| `Source/PunkyLo/Player/PL_Character.cpp` | Added `SKM_Manny_Simple` mesh assignment for player visibility; added `ConstructorHelpers` include |
| `Source/PunkyLo/Player/PL_PlayerController.h` | Added `AcknowledgePossession` override declaration |
| `Source/PunkyLo/Player/PL_PlayerController.cpp` | Implemented `AcknowledgePossession` to re-register Enhanced Input IMC after possession is confirmed on local player |

### Modified Config Files
| File | Change |
|---|---|
| `Config/DefaultEngine.ini` | Added Null online subsystem to bypass EOS credential requirement for local PIE testing |
| `Config/DefaultEditorPerProjectUserSettings.ini` | Set `PIE_ListenServer` + `PlayNumberOfClients=3` for multiplayer PIE |

---

## 6. Architecture Integrity

Phase B used only the Phase A gameplay framework. No new classes were introduced.

Classes active throughout Phase B:

| Class | Role |
|---|---|
| `APL_GameMode` | Server authority, spawns PL_ classes |
| `APL_GameState` | Shared world state, replicated to all clients |
| `APL_PlayerController` | Input handling, Enhanced Input IMC registration |
| `APL_PlayerState` | Per-player identity, replicated |
| `APL_Character` | Player avatar, movement, replication |
| `APL_GameInstance` | Session lifetime management |

---

## 7. Phase B Stop Condition

Phase B is complete as of 2026-03-28.

The following were deliberately excluded from Phase B and remain out of scope until a future phase decision:

- Session browsing / matchmaking
- Lobby systems
- UI
- Chat
- Animation
- Combat or gameplay systems
- Worldbuilding
- Production EOS integration
