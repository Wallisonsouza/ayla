Ayla

Ayla é uma linguagem baseada em composição.

A linguagem possui apenas quatro conceitos principais:

* data: define estruturas de dados.
* fn: define funções.
* compose: cria novos tipos a partir de dados.
* bind: conecta funções a uma composição.

O objetivo é manter estado, lógica e composição separados.

Data

Um data define apenas dados.

data Position {
    x: i32,
    y: i32
}
data Velocity {
    x: i32,
    y: i32
}

Functions

Toda lógica é implementada em funções.

fn move(position: Position, velocity: Velocity) {
    position.x += velocity.x
    position.y += velocity.y
}

As funções são independentes e podem ser reutilizadas em qualquer composição.

Compose

Um compose define um novo tipo.

compose Player {
    position: Position
    velocity: Velocity
}

Instanciando um tipo:

let player = Player()

Bind

Funções não pertencem automaticamente a uma composição.

Para utilizá-las é necessário criar um bind.

compose Player {
    position: Position
    velocity: Velocity
    bind move {
        position
        velocity
    }
}

Após o bind, a função pode ser utilizada pela composição.

player.move()

Equivalente a:

move(
    player.position,
    player.velocity
)

Reuse

A mesma função pode ser ligada a diferentes composições.

compose Enemy {
    position: Position
    velocity: Velocity
    bind move {
        position
        velocity
    }
}

Design Principles

* Dados não contêm lógica.
* Funções não pertencem a tipos.
* Composições apenas organizam dados.
* Toda ligação entre uma composição e uma função é explícita através de bind.