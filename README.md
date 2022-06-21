# Cronômetro regressivo

Desenvolva em assembler um programa para operação de um cronômetro regressivo de minutos tendo como base o hardware da Figura 1. O cronômetro inicia com a contagem fixada no valor de 10 minutos, momento no qual esta pode ser configurada até o valor máximo de 60 minutos, em incrementos de 10 minutos, através do acionamento de SW0. A contagem decrescente se inicia ao acionamento de SW1 e, uma vez iniciada, não poderá mais ser ajustada, parada ou interrompida. Chegando em zero, a contagem cessa e um buzzer de alarme é acionado sinalizando tal evento. Neste momento o beep é desativado e o cronômetro reiniciado (contagem congelada com valor inicial de 10 minutos ) ao se pressionar quaisquer uma das teclas. A todo momento, os dois displays devem ser atualizados para apresentar o valor do contador de tempo em BCD.


![image](https://user-images.githubusercontent.com/97004511/174892975-ccc3f8eb-6a27-4e4f-ba2e-a6c6758cd01f.png)
