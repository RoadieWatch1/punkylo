# PunkyLo — World Pipeline Foundation
**Phase A Locked Document | Created 2026-03-28**

This document defines the visual direction, scale standards, construction methodology, lighting strategy, and map structure rules for all future PunkyLo worlds. These decisions are locked from Phase A forward. Future development sessions must treat this document as the authoritative reference before building any environment content.

---

## 1. World Style Direction

**Theme:** Cyberpunk social world.

**Tone:** Dark, neon-lit, and atmospheric. The world should feel alive, dense, and slightly dangerous — a place people inhabit rather than pass through.

**Visual direction:** Semi-realistic. Grounded in recognizable urban architecture and human-scaled spaces. Not cartoony. Not hyper-sim gritty realism. The art direction sits between stylized and photorealistic — enough fidelity to feel immersive, enough stylization to maintain a distinct identity.

**Contrast direction:** High-contrast lighting. Deep shadows punctuated by neon, emissive signage, and reflective wet surfaces. The world's mood is carried by light and its absence, not by ambient fill.

**Character of the space:** Social, explorable, and immersive. Players should want to linger and move through the environment. The world rewards exploration.

---

## 2. Scale Rules

All environments and assets must conform to the following standards without exception. Deviation from these values requires an explicit documented reason.

| Element | Target Dimension |
|---|---|
| Player character height | ~180 cm |
| Standard door height | 210–230 cm |
| Standard door width | 90–100 cm |
| Ceiling height (interior, standard) | 280–320 cm |
| Ceiling height (lobby / public space) | 400–600 cm |
| Narrow alley width | 180–250 cm |
| Standard street width (one lane) | 350–450 cm |
| Standard street width (two lane) | 700–900 cm |
| Building floor-to-floor height | 350–400 cm |
| Stair riser height | 16–18 cm |
| Stair tread depth | 28–30 cm |

**Scale enforcement:** All modular environment assets — walls, floors, ceilings, doorframes, props, and structural pieces — must be built to this scale system before integration. Future maps must be validated against these dimensions before moving to lighting or dressing passes. A single unified grid size (recommended: 100 cm base unit in Unreal) should govern the modular system.

---

## 3. Environment Pipeline

### Construction Methodology

Environments are built using modular assets. Buildings, walls, pathways, structural elements, and props should be composed from reusable components rather than monolithic bespoke meshes. The goal is a system that can be recombined efficiently across the Hub and future Worlds without redundant authoring work.

### Asset Sources

- **Phase B onward:** Unreal Marketplace / Fab assets are the primary source for the initial environment kit. Cyberpunk-appropriate urban modular packs are acceptable provided they conform to the project's scale rules and visual direction.
- **Later phases:** Custom assets will be introduced where marketplace assets cannot meet the project's specific needs (e.g., branded signage, unique architectural landmarks, hero props).

### Material Workflow

Materials must follow a **master material + material instance** workflow wherever practical. A small set of master materials (e.g., building surfaces, wet ground, emissive panels, metal trim) should underpin the majority of the environment. Variation is achieved through instances, not through one-off unique materials. This is mandatory for surface materials covering large areas. Unique hero-prop materials may deviate when necessary.

### Purpose

This methodology exists for three reasons:
1. **Scalability** — the world can grow without proportional growth in authoring time.
2. **Faster iteration** — individual pieces can be swapped, adjusted, or updated without reworking entire sections of a map.
3. **Consistency** — the Hub and all future Worlds share the same visual vocabulary and behave predictably under the lighting system.

---

## 4. Lighting Strategy

### Engine

**Lumen** is the project's lighting engine. Static and stationary lighting workflows are not used. All global illumination and reflections are fully dynamic via Lumen. This is locked. Do not introduce baked lightmass passes.

### World Mood

The primary world atmosphere is **night-time or low-light urban**. The sky is dark or heavily overcast. Direct sunlight is absent or heavily diffused. Artificial light sources — neon signs, streetlamps, shop fronts, vehicle lights, emissive panels, holographic displays — are the dominant light language.

### Emissive and Neon Lighting

Emissive materials are a first-class lighting source in this project. Neon-style lighting (tubes, signs, floor strips, architectural highlights) should contribute meaningfully to scene illumination, not merely serve as decoration. Lumen handles emissive-driven GI naturally — this should be leveraged intentionally.

### Volumetric Fog

Volumetric fog is expected and appropriate in most environments. It reinforces the atmospheric tone, catches light from neon sources, and softens harsh contrast at distance. Use it deliberately — it should enhance readability, not obscure it.

### Reflections

Wet surfaces (rain-slick roads, puddles, polished floors) and glossy urban materials (glass, metal, lacquered panels) are part of the visual language. Lumen reflections and screen-space reflections should be expected to contribute to the scene. Wet-surface material parameters should be treated as a standard toolkit element, not a special-case addition.

### Readability Constraint

Atmospheric lighting must not destroy gameplay readability. Players must be able to navigate spaces, read other characters, and perceive interactive elements clearly. Dark-for-dark's-sake is not acceptable. Every environment must pass a basic readability check before lighting is considered final.

---

## 5. Map Structure Rules

### Folder Layout and Intent

| Folder | Purpose |
|---|---|
| `/Maps/Test` | Multiplayer testing, systems validation, input/movement testing. Phase A `BaseMap` lives here. |
| `/Maps/Hub` | The main social world. The primary player destination. Production content only. |
| `/Maps/Worlds` | Future expansion spaces and additional world destinations reachable from the Hub. |

### Enforcement Rules

**Test maps are never promoted to production.** Maps in `/Maps/Test` are engineering and QA tools. They are not dressed, shipped to players, or used as the basis for Hub or World content. If test content proves useful for production, it is rebuilt in the correct folder from scratch.

**Hub and World content remain separated.** The Hub (`/Maps/Hub`) is a persistent social space. World expansion maps (`/Maps/Worlds`) are distinct destinations. Content, streaming setups, and gameplay logic must not be mixed between them. Each folder governs a distinct player experience context.

**Production maps are not started until the system they depend on is verified.** No Hub content is authored until multiplayer session management, player spawning, and core movement are validated in a Test map first. No World content is authored until Hub architecture decisions are locked.

---

## Summary

These rules govern all environment work in PunkyLo from Phase B forward:

- The world is a **dark, neon-lit, semi-realistic cyberpunk social space**.
- All assets use a **shared 100 cm grid scale system** anchored to a 180 cm player.
- Environments are built **modularly**, from shared asset kits, using **master material instances**.
- **Lumen** is the sole lighting strategy. The mood is **night-time urban with emissive/neon dominance**.
- Maps are strictly separated: **Test** for validation, **Hub** for the social world, **Worlds** for expansion.

Any deviation from these standards requires explicit documentation before implementation.
