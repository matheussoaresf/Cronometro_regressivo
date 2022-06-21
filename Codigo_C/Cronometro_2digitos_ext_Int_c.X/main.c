
#
// PIC18F4550 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = EC_EC     // Oscillator Selection bits (EC oscillator, CLKO function on RA6 (EC))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000


unsigned char disp1, disp0;
char decrementar;           //Varivel responsavel por iniciar o decremento
int ligarbuzzer;            //Variavel responsavel para ligar o buzzer

void decrementa(void);      //Função que decrementa o cronometro
void PortD(void);           //Função que exibe no PORTD 
void delay(void);           //Função de delay de 1min

void main(void) {
    TRISBbits.RB0 = 1;      //RB0 como entrada
    TRISBbits.RB1 = 1;      //RB1 como entrada
    TRISBbits.RB4 = 0;      //RB4 como saida
    TRISD = 0;              //PORTD todos bits como saida
    INTCONbits.INT0IE = 1;  //Habilita interrupção INT0
    INTCON3bits.INT1IE = 1; //Habilita interrupção INT1
    INTCONbits.GIE = 1;     //Habilita interrupções globalmente
    INTCONbits.PEIE = 1;    //Habilita int. dos periféricos
    
    //Inicia o cronometro em 10min
    disp1 = 0b0001; 
    disp0 = 0;
    PortD();
    decrementar = 0;  
    ligarbuzzer = 0;
    
    
    while(1){   //Loop principal
        if (decrementar) {  //Se o decrementar == 1, inicia o cronometro.
            GIE = 0;        //Desabilitando a interrupçao global
            decrementa();   //função decrementa o cronometro
            PortD();        //Função que exibe o valor na tela 
            delay();        // Delay de 1 minuto
        }else{
            if(ligarbuzzer == 1){     //Aciona o buzzer
                PORTBbits.RB4 = 1;
            }else{                    //desabilita o buzzer
                PORTBbits.RB4 = 0;
            }
            
            GIE = 1;                //Habilita a interrupção global
            __delay_ms(100);        //Pequeno delay
            PortD();                
        }  
    }
    return;
}

void PortD(void){   //Função que exibe no PORTD
   PORTD = (disp1 << 4) | disp0;
} 
void decrementa(void){
    if( disp0!=0 | disp1!=0){  //Enquanto o tempo não estivez zerado
        if(disp0 == 0){        
            disp0 = 0b1001;
            disp1--;
        }else if(disp0 == 9){
           disp0--;
       }else{
            disp0--;
       } 
    }else{          //Se o tempo for zerado
        decrementar = 0;    //O decremento para
        ligarbuzzer = 1;    //Liga o BUZZER
    }
}

void __interrupt(high_priority) ISR(void){
   
    if(INTCONbits.INT0IF){ //Incrementa
        INT0IF = 0;
        ligarbuzzer = 0;
        if( disp1<6){       //incrementa até 60min
            disp1= disp1 + 1;
            PortD();
        }
    }else if(INT1IF){   //Inicia o decremento
        INT1IF = 0;
        if( disp0==0 && disp1==0){ //caso o botão SW1 foi acionado apos zerar o cronometro
            disp1 = 0b0001;        //Inicia o tempo em 10min
            disp0 = 0;
            ligarbuzzer = 0;       //Desliga o buzzer
            return;
        }
        decrementar^=1;             //inicia o decremento
        ligarbuzzer = 0;
    }   
}
void delay(void){   //Delay de 1min
    int x;
    for(x = 94; x>=0; x--){
       __delay_ms(500); 
    }
}