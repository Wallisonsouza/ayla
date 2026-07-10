# Ayla

Ayla é uma linguagem baseada em três conceitos fundamentais:

- **data** — define apenas dados.
- **fn** — define apenas lógica.
- **compose** — organiza dados e conecta funções.

Não existem classes, herança ou métodos.

---

# Data

Um `data` representa apenas uma estrutura de dados.

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

Os dados não possuem lógica.

---

# Funções

Toda lógica é escrita em funções.

```ayla
fn move(position: Position, velocity: Velocity) {
    position.x += velocity.x
    position.y += velocity.y
}
```

As funções não pertencem a nenhum tipo.

---

# Compose

Um `compose` cria um novo tipo combinando dados.

```ayla
compose Player {
    position: Position
    velocity: Velocity
}
```

Agora existe um novo tipo chamado `Player`.

```ayla
let player = Player()
```

---

# Bind

Nenhuma função pertence automaticamente a uma composição.

Para utilizá-la é necessário criar um `bind`.

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

O compilador conecta os parâmetros da função aos campos da composição.

Uma chamada como:

```ayla
player.move()
```

é equivalente a:

```ayla
move(
    player.position,
    player.velocity
)
```

---

# Reutilização

A mesma função pode ser utilizada por diferentes composições.

```ayla
compose Enemy {
    position: Position
    velocity: Velocity

    bind move {
        position
        velocity
    }
}
```

A função `move` continua sendo única.

---

# Filosofia

A linguagem separa completamente cada responsabilidade.

- `data` representa estado.
- `fn` representa comportamento.
- `compose` representa organização.
- `bind` representa a ligação entre dados e funções.

Nada pertence implicitamente a outro elemento.

Tudo é explícito.