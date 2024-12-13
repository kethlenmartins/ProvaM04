# Prova Módulo 4 - 2024

Neste repositório, encontra-se o código desenvolvido na parte prática da prova do módulo 4 de 2024 do Inteli.
Também, estarão abaixo as fotos comprobatórias dos estados do protótipo.

## Estados do protótipo
O protótipo possui dois estados: o noturno e o diurno. Ambos funcionam a partir do status do LDR.

### Modo diurno
O modo diurno possui o funcionamento normal do semáforo, onde os leds verde, amarelo e vermelho acendem e apagam em sequência.

<div align="center">
<sub>Figura 1 - Led verde aceso e outros apagados</sub>
<img src="assets/modo_diurno_verde.png" width="100%">
<sup>Fonte: Material produzido pelos autores (2024)</sup>
</div>
<div align="center">
<sub>Figura 2 - Led amarelo aceso e outros apagados</sub>
<img src="assets/modo_diurno_amarelo.png" width="100%">
<sup>Fonte: Material produzido pelos autores (2024)</sup>
</div>
<div align="center">
<sub>Figura 3 - Led vermelho aceso e outros apagados</sub>
<img src="assets/modo_diurno_vermelho.png" width="100%">
<sup>Fonte: Material produzido pelos autores (2024)</sup>
</div>

### Modo noturno
O modo noturno possui o funcionamento somente do led amarelo, o qual pisca a cada 1s.
<div align="center">
<sub>Figura 4 - Led vermelho piscando</sub>
<img src="assets/modo_noturno.png" width="100%">
<sup>Fonte: Material produzido pelos autores (2024)</sup>
</div>

## Debounce
O debounce ocorre por um ruído causado na leitura do botão. Para isso, foi implementado o debounce via software no código do protótipo.

## Requisição HTTP
A cada vez que alguém aperta o botão 3 vezes, uma requisição do método GET é enviada a um site.
