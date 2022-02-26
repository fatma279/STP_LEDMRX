/*  Author  : Fatma                          */
/*  Date    : 17 February 2022               */
/*  version : V1                             */




#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "STK_interface.h"
#include "STP_interface.h"


u8 Data[8]={0, 254, 18, 18, 2, 0, 0, 0};


void main(void)
{
	MRCC_voidInitSysClock();                 /*chose clock system to HSE 8MHZ */
    MRCC_voidEnableClock(APB2, IOPA);         /*Enable GPIOA clock*/

    /*pin Direction */
    MGPIO_voidSetPinDirection(GPIOA,PIN0,OUTPUT_SPEED_2MHZ_PP);   /*  A0 output push pull  */
    MGPIO_voidSetPinDirection(GPIOA,PIN1,OUTPUT_SPEED_2MHZ_PP);   /*  A1 output push pull  */
    MGPIO_voidSetPinDirection(GPIOA,PIN2,OUTPUT_SPEED_2MHZ_PP);   /*  A2 output push pull  */

    /*timer initialization */
    MSTK_voidInit();

	u16 local_u16Num ;
	u8 Local_8_Coulmns ;
  // Infinite loop

	while(1){

		for (u8 iteration = 0 ; iteration <sizeof(Data) ; iteration++){

			 /* Get the desire column enabled and other disabled */
			Local_8_Coulmns = 255 &  (~(1 << iteration));

			/*set enabled column and other disabled on second shift register and set raws value on first shift register  */
			local_u16Num = (Local_8_Coulmns << 8) + Data[iteration];

			/* send data to two shift register */
			STP_voidSendSynchronus(local_u16Num);
            /* wait 2msec*/
			MSTK_voidSetBusyWait(2000);
	}

}
}



