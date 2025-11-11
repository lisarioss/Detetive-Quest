# 🕵️‍♂️ Detetive Quest — O Desafio Final

**Detetive Quest** é um jogo interativo em C que desafia o jogador a resolver mistérios e tomar decisões estratégicas para escapar de uma ilha misteriosa.  
O projeto combina **lógica, estrutura de dados e simulação**, oferecendo um sistema de progressão por níveis e ações dinâmicas.

---

## 🎯 Objetivo do Jogo

O jogador assume o papel de um detetive que precisa **resolver enigmas, tomar decisões e planejar estratégias** para sobreviver até o final do jogo.  
A última **safe zone** está se fechando e apenas os mais habilidosos conseguirão escapar da ilha.

O jogo apresenta **níveis de dificuldade evolutivos**:
- 🟢 **Novato** — introdução às mecânicas e lógica do jogo.  
- 🟡 **Aventureiro** — desafios intermediários com decisões estratégicas.  
- 🔴 **Mestre** — nível final, com ações combinadas e planejamento tático.

---

## 🧩 Estrutura do Projeto

O programa é modularizado em funções que controlam:
- **Gerenciamento de inventário** (itens, armas e pistas)
- **Sistema de zonas seguras (safe zones)**
- **Progressão de dificuldade e níveis**
- **Interação com o jogador por meio de menus e escolhas**

Cada ação influencia o destino do jogador — suas decisões importam.

---

## ⚙️ Funcionalidades

| Código | Ação | Descrição |
|--------|------|-----------|
| 1 | Explorar a área | Coleta pistas ou enfrenta desafios aleatórios |
| 2 | Analisar pistas | Usa o raciocínio lógico para avançar no mistério |
| 3 | Usar item do inventário | Aplica recursos estratégicos coletados |
| 4 | Salvar progresso | Armazena o estado atual do jogador |
| 5 | Mostrar status | Exibe estatísticas, energia e progresso |
| 0 | Sair do jogo | Encerra a partida com resumo final |

---

## 🧠 Conceitos Aplicados

O projeto reforça os principais conceitos da linguagem **C**:
- Estruturas (`struct`) para representar o jogador e os itens
- Vetores e filas para controle de inventário
- Funções e modularização de código
- Controle de fluxo com decisões condicionais
- Geração aleatória de eventos (uso de `rand()` e `srand()`)

---

## 💾 Execução

### 🔧 Compilação
```bash
gcc detetive_quest.c -o detetive_quest

## ▶️ Execução
./detetive_quest

---

## 🕹️ Exemplo de Saída
Prepare-se para o desafio final!
A última safe zone está se fechando...
Você encontrou uma pista misteriosa! Deseja investigar?

Opções:
1 - Investigar
2 - Ignorar
3 - Usar item
0 - Sair

Escolha: 1
Você descobriu o esconderijo do inimigo! Nível concluído.

---

## 🧑‍💻 Desenvolvido por Lisa Rios
- Projeto acadêmico de lógica de programação e estruturas de dados.