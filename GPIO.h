
#ifndef GPIO
#define GPIO

///PortF switches
#define GPIO_SW1 0
#define GPIO_SW2 1
#define GPIO_SW_NOT_PRESSED 1

///PortF LED color
#define GPIO_RED_LED 0
#define GPIO_GREEN_LED 1
#define GPIO_BLUE_LED 2

///PortF LED state ON/OFF
#define GPIO_LED_OFF 0
#define GPIO_LED_ON 1




////////Functions Prototypes form inialize GPIO's ports
void GPIOB_Init ();
//void GPIO_PORTB_set (unsigned char Value);
void GPIOF_Init();
void GPIOA_Init ();
void GPIOD_Init ();

#endif
