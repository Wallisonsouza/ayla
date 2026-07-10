# Ayla

<p align="center">
  A programming language built around<br>
  <b>Data · Functions · Composition</b>
</p>

---

## Overview

Ayla is a programming language focused on clear separation of responsibilities.

The language is built around four core concepts:

| Concept | Purpose |
|---|---|
| `data` | Define data structures |
| `fn` | Define functions |
| `compose` | Create composed types |
| `bind` | Connect functions to compositions |

---

# Data

Data structures contain only state.

```ayla
data Position {
    x: i32,
    y: i32
}

data Velocity {
    x: i32,
    y: i32
}
```

---

# Functions

Functions contain logic and are independent from types.

```ayla
fn move(position: Position, velocity: Velocity) {
    position.x += velocity.x
    position.y += velocity.y
}
```

---

# Composition

Types are created by composing data.

```ayla
compose Player {
    position: Position
    velocity: Velocity
}
```

A composition does not own logic.
It only defines what it contains.

---

# Binding

Functions are connected explicitly using `bind`.

```ayla
compose Player {
    position: Position
    velocity: Velocity

    bind move {
        position
        velocity
    }
}
```

The generated interface:

```ayla
player.move()
```

is equivalent to:

```ayla
move(
    player.position,
    player.velocity
)
```

---

# Example

```ayla
data Position {
    x: i32,
    y: i32
}

data Velocity {
    x: i32,
    y: i32
}

fn update(position: Position, velocity: Velocity) {
    position.x += velocity.x
}

compose Player {
    position: Position
    velocity: Velocity

    bind update {
        position
        velocity
    }
}
```

---

# Philosophy

```
Data
 ↓
Functions
 ↓
Composition
 ↓
Bind
```

Ayla avoids mixing responsibilities.

- No classes
- No inheritance
- No implicit methods
- Explicit composition

---

## Status

🚧 Experimental language project