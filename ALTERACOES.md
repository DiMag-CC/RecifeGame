# Registro de Alterações (ALTERACOES.md)

Este arquivo registra todas as modificações, correções e novas funcionalidades implementadas no projeto **Deixa Eu**.

---

## 🖥️ 1. Modo Tela Cheia (Fullscreen)
* **Status**: Implementado e Testado.
* **Descrição**: Adicionada a funcionalidade que permite ao jogador alternar entre o modo janela e o modo tela cheia (fullscreen) de maneira dinâmica.
* **Detalhes da Implementação**:
  - Inserido um detector de teclado no loop principal (`while (!WindowShouldClose())`) no arquivo [main.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/main.c).
  - Pressionar a tecla **F** aciona a função nativa `ToggleFullscreen()` da Raylib.
* **Arquivos Modificados**:
  - [main.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/main.c)

---

## 🐛 2. Correção Geral de Erros de Compilação (fase3)
* **Status**: Resolvido.
* **Descrição**: Correção de múltiplos erros de sintaxe, escopo, referências nulas e constantes não declaradas que impediam a compilação do projeto.
* **Detalhes da Implementação**:
  - **[obstacle.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/entities/obstacle.c)**:
    - Ajustado o acesso a propriedades de ponteiros usando `->` em vez de `.` para o parâmetro `Obstacle* obstacle` na função `updateObstacle`.
    - Substituída a variável indefinida `position` por `obstacle->position`.
    - Ajustado o acesso ao union para `obstacle->data.bus` em vez de `obstacle->data->bus`.
    - Removido o `case OBSTACLE_SHARK` duplicado da função `drawObstacle`.
  - **[raindrop.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/entities/raindrop.c)**:
    - Substituído `LIGHTBLUE` (que não existe na Raylib) pela constante de cor padrão `BLUE`.
  - **[player.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/entities/player.c)**:
    - Corrigido o warning substituindo a expressão de subtração `player.hasUmbrella - 0;` pela atribuição correta `player.hasUmbrella = 0;`.
  - **[stage1.h](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/steps/stage1.h)**:
    - Adicionadas as definições das constantes `MAX_PIGEONS` e `MAX_RAINDROPS`.
    - Declarados todos os campos que estavam ausentes na estrutura `Stage1` (como `difficultyMultiplier`, `pigeons`, `raindrops`, `umbrellas`, etc.).
    - Alterado o tamanho do vetor `buildings` de `5` para `8` para evitar possíveis erros de *out-of-bounds* de memória durante a renderização (já que a fase tentava desenhar até 8 prédios).
    - Incluídos os arquivos de cabeçalho dos pombos, gotas de chuva e guarda-chuva.
    - Modificada a assinatura de `drawStage1` para receber o ponteiro de `Player` para desenhar o HUD adequadamente.
  - **[stage1.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/steps/stage1.c)**:
    - Removida a linha incorreta que tentava alterar a propriedade inexistente `.hitbox` em `Pigeon` (a colisão é apenas com o objeto do tipo fezes).
    - Ajustada a assinatura de `drawStage1` para coincidir com a nova declaração.
  - **[main.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/main.c)**:
    - Ajustada a chamada de `drawStage1(&stage)` para `drawStage1(&stage, &player)`.

---

## 🧗‍♂️ 3. Fase 3: A Torre de Cristal (Parque das Esculturas)
* **Status**: Implementado e Testado.
* **Descrição**: Inclusão de uma nova fase com mecânica dupla: progressão horizontal seguida por uma escalada vertical contínua na Torre de Cristal.
* **Detalhes da Implementação**:
  - **Criação de Assets Gráficos via IA**: Foram gerados e incluídos assets em Pixel Art para a Torre de Cristal, Nuvens e Pássaros.
  - **Nova Mecânica de Movimento (`player.h` e `player.c`)**: Adicionada a flag `isClimbing` ao struct `Player`. Quando verdadeira, a gravidade é desabilitada e o jogador pode se movimentar vertical e horizontalmente ao longo da superfície da torre.
  - **Desenvolvimento da Fase 3 (`stage3.h` e `stage3.c`)**:
    - **Fase Horizontal (Approach)**: O jogador corre para a direita enquanto o cenário (Torre) avança pela esquerda.
    - **Fase Vertical (Climbing)**: Ao colidir com a base da Torre de Cristal, a tela passa a rolar verticalmente enquanto o jogador sobe rumo ao topo.
    - Efeito de *Parallax Scrolling* infinito para nuvens e pássaros em diferentes velocidades.
  - **Integração (`main.c`)**: A fase 3 foi incluída nas importações e inicializada para carregar diretamente ao iniciar o jogo no menu para fins de teste rápidos.

---

## ☁️ 4. Ajustes das Nuvens e Pássaros (Fase 3)
* **Status**: Concluído.
* **Descrição**: Otimização estética e mecânica dos elementos de fundo.
* **Detalhes da Implementação**:
  * **Nuvens no Topo**: A geração vertical ($Y$) das nuvens foi redefinida entre as alturas `10` e `40` (garantindo que fiquem no céu e nunca encostem no chão).
  * **Tamanho Reduzido**: As escalas visuais foram reduzidas para `0.2` para as nuvens e `0.1` para os pássaros, melhorando a harmonia estética do cenário.
  * **Staggered Spawning**: Nuvens e pássaros são gerados e resetados com espaçamentos predefinidos para mantê-los bem distribuídos na tela.

---

## 🪶 5. Bando de Pássaros, Cocô com Física e Escalada Manual
* **Status**: Concluído.
* **Descrição**: Introdução de perigos aéreos de forma independente e refatoração da entrada na Torre.
* **Detalhes da Implementação**:
  * **Escalada Manual por Teclado**: O jogador agora pode caminhar na frente da torre e cruzá-la livremente. Ele é bloqueado apenas no canto direito da torre, e para começar a escalar, ele deve se posicionar em frente a ela e pressionar **W** ou **Seta para Cima**.
  * **Três Pássaros Ativos**: Elevado o limite de pássaros para `3`, com voos e velocidades independentes.
  * **Fezes dos Pássaros (Game Over)**: Cada pássaro possui seu próprio timer e intervalo randômico de cocô (`poopInterval`). Os dejetos caem com gravidades/velocidades verticais aleatórias (`150.0f` a `300.0f` px/s). Se o cocô atingir o hitbox do jogador, as vidas são zeradas instantaneamente (Derrota).
  * **Ajuste da Torre e Chão**: Eliminado o gap visual de 60px entre o chão verde e o pé da torre, afundando a torre em `20px` sob o plano do solo para garantir contato físico e perpendicular perfeito.

---

## 🔍 6. Visualização Expandida (Câmera 2D com Zoom-Out)
* **Status**: Concluído.
* **Descrição**: Implementação de uma câmera com zoom afastado para ver maior área do mapa e gameplay.
* **Detalhes da Implementação**:
  * **Camera2D da Raylib**: No desenho do jogo em [main.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/main.c), foi implementada uma `Camera2D` configurada com `zoom = 0.8f` e centralizada no meio da tela.
  * **Preenchimento do Chão**: Para cobrir a nova área exibida pela câmera, o chão verde foi expandido horizontalmente de `-200px` até `1000px`, e a verificação do limite vertical de reset foi ajustada para `560px`.
  * **HUD Fixo**: Toda a HUD de estatísticas (Vidas, Pontos, Tempo) é desenhada fora do modo de câmera, mantendo o texto nítido e estático no tamanho padrão da tela.

---

## 🎛️ 7. Correção da Navegação e Redirecionamento do Menu
* **Status**: Concluído.
* **Descrição**: Correção na lógica de transição e navegação dos botões do menu principal para evitar vazamento de inputs e comportamentos inesperados.
* **Detalhes da Implementação**:
  * **Isolamento de Estado**: Refatorada a função `updateMenu` em [menu.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/menu.c) para restringir as teclas de direção (`W/S`/`UP/DOWN`) exclusivamente à tela `MENU_MAIN`. Isso impede que o jogador altere as opções selecionadas em segundo plano enquanto visualiza a tela de Créditos.
  * **Retorno Preciso de Foco**: Ao fechar a tela de Créditos (seja com `Left/A`, `Escape` ou pressionando `Enter` na tela de créditos), o cursor retorna com precisão posicionado na própria opção "Créditos" (`menu->selectedOption = 1`), eliminando saltos indesejados.
  * **Limpeza de Código**: Removida a checagem redundante e duplicada de tecla `Escape` que ficava solta no arquivo [main.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/main.c).

---

## 🚧 8. Remoção de Barreira Invisível e Scroll Lateral Fluido (Fase 3)
* **Status**: Concluído.
* **Descrição**: Correção da sensação de "barreira no meio do mapa" e expansão da área explorável após a Torre de Cristal.
* **Detalhes da Implementação**:
  * **Scroll com Fim de Curso**: O scroll automático de câmera (`scrollX`) da Fase 3 agora cessa completamente de forma inteligente quando atinge `650.0f` (ponto ideal em que a Torre está perfeitamente centralizada e visível a `550px` na tela).
  * **Movimentação Livre Pós-Scroll**: Uma vez que a câmera para de rolar, a restrição de `400.0f` no eixo X da tela é desabilitada. O jogador ganha liberdade total para caminhar livremente em frente à torre, atravessá-la e explorar o espaço extra.
  * **Barreira Inteligente Expandida**: Substituído o clamp de colisão antigo (que empurrava o jogador para trás conforme a torre se movia). Agora, a barreira física foi movida `150px` para a direita da Torre (`barrierX = stage->towerPosition.x + towerWidth + 150.0f`). O jogador pode caminhar no espaço extra expandido após a torre e é bloqueado de forma limpa e estática exatamente na borda direita visível da tela.

---

## 🖥️ 9. Ativação da Categoria Tela Cheia (Botão Nativo do OS)
* **Status**: Concluído.
* **Descrição**: Ativação do botão natural de maximizar e colocar em tela cheia da janela (botão verde no macOS) que se encontrava desabilitado.
* **Detalhes da Implementação**:
  * **Flags do Sistema**: Adicionada a diretiva `SetConfigFlags(FLAG_WINDOW_RESIZABLE)` antes da chamada de `InitWindow` no arquivo principal [main.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/main.c).
  * **Resultado**: Habilitou perfeitamente o redimensionamento nativo e o botão verde padrão do macOS de colocar a aplicação em tela cheia/maximizar de forma completamente fluida e integrada ao sistema operacional.

---

## 🏆 10. Tela de Vitória Premium e Redirecionamento Livre de Memory Leak
* **Status**: Concluído.
* **Descrição**: Correção da falta de redirecionamento/softlock ao vencer o jogo e prevenção de vazamentos de textura.
* **Detalhes da Implementação**:
  * **Overlay de Vitória HUD**: Criada uma tela de vitória elegante em [main.c](file:///Users/godoy/Desktop/Projetos/DeixaEu/DeixaEu/src/main.c) quando o estado `STAGE3_FINISHED` é atingido. A renderização foi movida para fora do viewport da câmera 2D para manter os textos nítidos e centralizados em HSL/RGB em qualquer resolução de janela, com overlay translúcido e tom dourado.
  * **Redirecionamento Teclado (ENTER)**: Adicionada a detecção da tecla `ENTER` no estado de vitória para redefinir as variáveis do jogo, descarregar as texturas da Fase 3 e retornar o jogador ao Menu Principal com segurança.
  * **Eliminação de Leaks de Textura**: Removida a chamada redundante de `initStage3` do loop de reset automático do Game Over. As texturas agora são carregadas **exclusivamente** no clique de início de partida ("Iniciar Jogo"), liberando recursos antigos imediatamente através do `unloadStage3` sem duplicar instâncias de memória de vídeo.

---
