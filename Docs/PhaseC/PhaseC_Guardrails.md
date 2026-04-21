# Phase C Guardrails

**Status:** ACTIVE — enforced for all Phase C work
**Last Updated:** 2026-03-28

---

## 1. What Phase C IS

Phase C establishes the first real world slice and the foundational identity, social, and presence systems.

In-scope categories:
- First real world slice (blockout → district layout)
- Spatial layout and zone identity
- Atmosphere and lighting identity
- Player presence and identity feel
- Social Heat (lightweight, surface layer)
- Reputation shell (data structure only)
- Training flavor (contextual cues)
- Role flavor beginnings (visual/audio differentiation)
- Signature visual ritual (stub/placeholder)
- Presence-first audio (environmental, non-reactive)
- Character support scaffolding (5 free characters only)
- Multiplayer validation at each milestone

---

## 2. What Phase C IS NOT

The following are **explicitly deferred** and must not be introduced in Phase C:

- Account or login systems
- Backend persistence of any kind
- Payment systems
- Character monetization or entitlement logic
- Jail or law enforcement systems
- Witness or reporting systems
- Full progression systems
- Large-scale city building
- Open world expansion
- Dynamic economy or transaction systems
- Any system requiring a live backend service

---

## 3. Map Discipline Rules

| Location | Purpose | Rule |
|---|---|---|
| `/Maps/Test` | Validation only | NO production content — ever |
| `/Maps/Hub` | Hub/Lobby space | Existing Phase A/B work — do not break |
| `/Maps/Worlds/PhaseC_District` | Phase C world work | ALL Phase C world content goes here |

**Hard rule:** If it is world-building content, it lives in `/Maps/Worlds/PhaseC_District`.
If it is a validation test, it lives in `/Maps/Test` and is deleted or archived when done.
There are no exceptions.

---

## 4. System Discipline Rules

- All new systems must be **modular and independently loadable**
- No system may introduce a hard dependency on another new Phase C system at launch
- No system may introduce a dependency on a backend service
- New C++ systems follow the `PL_` naming prefix convention
- New Blueprints follow the `BP_PL_` naming convention
- Systems in `/Systems/Reputation`, `/Systems/Training`, `/Systems/Social`, `/Systems/Ritual` are **stub/shell only** until their feature bucket is activated
- Character support scaffolding must remain forward-compatible but must NOT implement monetization hooks

---

## 5. Feature Isolation Rule

Before any Phase C feature is merged into a production map or system:

1. Feature must be validated in isolation in `/Maps/Test`
2. Multiplayer session must be confirmed stable with the feature active
3. Feature must be removable without breaking other systems
4. Validation checklist item must be marked complete (see `PhaseC_ValidationChecklist.md`)

---

## 6. Multiplayer Safety Requirement

- Every actor, component, and system added in Phase C must be evaluated for network replication requirements
- Do not assume single-player behavior is acceptable
- Replication must be explicitly set (replicated, not replicated, or server-only) — no implicit defaults
- Test all new content in a minimum 2-player local session before marking complete
- Do not introduce race conditions or authority assumptions without documenting them

---

## 7. Deferred Items — Explicit Notice

The following are **locked out of Phase C** by design:

**Character Monetization**
Character monetization systems, premium unlock flows, entitlement checks, and cosmetic purchase logic are deferred to a later phase. Do not scaffold, stub, or hook for these in Phase C code paths.

**Backend / Account Systems**
No login, account creation, session persistence, cloud save, or backend API integration is permitted in Phase C. All state is local and ephemeral.

---

## Enforcement

Any work that violates these guardrails must be reverted before merge.
When in doubt: scope down, validate, then expand.
