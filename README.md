# DEIXA EU 🚲🌧️🦀🦈

## Um jogo 2D em C inspirado no caos urbano e cultural do Recife

---

# 📖 SOBRE O PROJETO

**Deixa Eu** é um jogo 2D desenvolvido em linguagem C inspirado nos jogos Super Mario e Subway Surfers, ambientado na cidade do Recife.

O jogo mistura:

* plataforma 2D;
* endless runner;
* humor nordestino;
* cultura recifense;
* estruturas de dados;
* algoritmos de ordenação.

O jogador controla um adolescente recifense que foge de casa após discutir com sua mãe e atravessa diversos pontos icônicos da cidade enfrentando obstáculos urbanos, naturais e situações cômicas típicas do Recife.

---

# 🎮 HISTÓRIA

Tudo começa em uma manhã chuvosa no Recife.

O personagem tenta sair escondido de casa, mas sua mãe percebe e começa uma perseguição pela residência enquanto ele grita:

> “DEIXA EU, MÃE, DEIXA EU!”

Após escapar:

* ele pega uma bicicleta Itaú laranja;
* atravessa ruas caóticas do Recife;
* corre pela praia de Boa Viagem;
* foge de um tubarão;
* escala o Parque das Esculturas Francisco Brennand.

Ao chegar ao topo da escultura principal:

* contempla a vista do Recife;
* envia uma foto para sua mãe;
* e diz:

> “Valeu a pena, mãe.”

---

# 🗺️ FASES DO JOGO

---

# 🚲 FASE 1 — PEDALANDO NO CAOS

## Cenário

Ruas chuvosas do Recife.

## Objetivo

Pedalar desviando de obstáculos urbanos.

## Obstáculos

* Buracos;
* Fezes de pombo;
* Ônibus;
* Placas;
* Chuva intensa.

 

### Power-up

Guarda-chuva:

* impede retardo da chuva;

  

## Mecânicas

* Pular;
* Desviar;
* Abaixar;
* Acelerar.

---

# 🦀🌊 FASE 2 — BOA VIAGEM

## Parte 1 — Corrida na areia

### Obstáculos

* Caranguejos;
* Guarda-sóis;
* Ondas;
* Ambulantes.

### Power-up

Água de coco:

* aumenta velocidade;
* melhora desempenho temporariamente.

---

## Parte 2 — Fugindo do tubarão

### Obstáculos

* Correntes marítimas;
* Redes;
* Água-viva;
* Ondas gigantes.

### Mecânica especial

Barra de fôlego.

---

# 🗿 FASE 3 — PARQUE DAS ESCULTURAS

## Objetivo

Escalar a escultura principal do parque.

## Obstáculos

* Ventos fortes;
* Plataformas quebrando;
* Chuva;
* Partes escorregadias.

## Final

O personagem chega ao topo observando a paisagem do Recife.

---

# 🧠 ESTRUTURAS DE DADOS UTILIZADAS

O projeto utiliza estruturas de dados diretamente integradas à gameplay.

---

# 🔄 LISTA DUPLAMENTE ENCADEADA CIRCULAR

## Objetivo

Controlar o sistema de fases do jogo.

```text
[Fase 1] <-> [Fase 2] <-> [Fase 3]
      ^                         |
      |_________________________|
```

## Funções

* Navegação entre fases;
* Reinício automático;
* Progressão contínua;
* Modo infinito.

---

# 📥 FILAS DINÂMICAS

## Objetivo

Gerenciar spawn de obstáculos.

## Aplicações

* Buracos;
* Caranguejos;
* Obstáculos aquáticos;
* Objetos móveis.

## Funcionamento

FIFO (First In First Out).

---

# 📊 INSERTION SORT

## Objetivo

Ordenar ranking dos jogadores.

## Critérios

* Menor tempo;
* Maior pontuação;
* Menor número de colisões.

---

# ⚙️ TECNOLOGIAS

## Linguagem

* C

## Bibliotecas previstas

* SDL2
  ou
* Raylib

---

# 📂 ESTRUTURA DO PROJETO

```text
RecifeGame/
│
├── .gitignore
├── Makefile
├── README.md
│
├── assets/
│   ├── img/
│   ├── music/
│   └── sfx/
│
├── include/
│   └── raylib.h
│
└── src/
    ├── main.c
    │
    ├── entities/
    │   ├── obstacle.c
    │   ├── obstacle.h
    │   ├── player.c
    │   └── player.h
    │
    ├── gfx/
    │   ├── animation.c
    │   ├── animation.h
    │   ├── sprite.c
    │   └── sprite.h
    │
    ├── steps/
    │   ├── step.c
    │   ├── step.h
    │   ├── step1.c
    │   ├── step2.c
    │   └── step3.c
    │
    ├── structure/
    │   ├── obstacleQueue.c
    │   ├── obstacleQueue.h
    │   ├── stepList.c
    │   └── stepList.h
    │
    └── utils/
        ├── utils.c
        └── utils.h
```

---

# 🚀 COMO EXECUTAR

## Em desenvolvimento

Essa parte ainda será implementada futuramente.

Planejamos adicionar:

* instruções completas de instalação;
* configuração das dependências;
* compilação do projeto;
* execução em diferentes sistemas operacionais;
* suporte oficial para SDL2/Raylib.

Mais detalhes serão adicionados nas próximas versões do projeto.

---

# 🛠️ PRINCIPAIS FUNCIONALIDADES

* Sistema de fases;
* Spawn dinâmico de obstáculos;
* Sistema de colisão;
* Power-ups;
* Ranking;
* Progressão de dificuldade;
* Trilha sonora regional;
* Estruturas de dados aplicadas à gameplay.

---

# 📈 ALGORITMOS UTILIZADOS

| Algoritmo          | Objetivo               |
| ------------------ | ---------------------- |
| Insertion Sort     | Ordenar ranking        |
| FIFO               | Controle de obstáculos |
| Navegação Circular | Progressão de fases    |

---

# 🎨 ESTILO VISUAL

* Pixel Art 2D;
* Estética urbana recifense;
* Clima chuvoso;
* Humor regional;
* Referências culturais locais.

---

# 🎵 TRILHA SONORA

Mistura de:

* Frevo;
* Manguebeat;
* Percussão nordestina;
* Música urbana;
* Sons de chuva.

---

# 💡 DIFERENCIAL DO PROJETO

O diferencial técnico do projeto é que as estruturas de dados não são utilizadas apenas para armazenamento interno, mas fazem parte diretamente da lógica do jogo.

As estruturas influenciam:

* progressão;
* obstáculos;
* ranking;
* movimentação;
* gameplay.

---

# 🔮 EXPANSÕES FUTURAS

* Multiplayer local;
* Ranking online;
* Mais fases do Recife;
* Sistema de skins;
* Modo infinito;
* IA para obstáculos;
* Sistema de missões.

---

# 📚 REFERÊNCIAS

## Jogos

* Super Mario
* Subway Surfers

## Cultura

* Recife Antigo
* Praia de Boa Viagem
* Parque das Esculturas
* Manguebeat
* Cultura urbana recifense

---

# ❤️ “VALEU A PENA, MÃE.”
