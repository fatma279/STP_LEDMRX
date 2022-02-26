/*  Author  : Fatma                          */
/*  Date    : 15 February 2022               */
/*  version : V1                             */


#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "STK_interface.h"

#include "STP_interface.h"
#include "STP_config.h"
#include "STP_private.h"


void STP_voidSendSynchronus(u16 copy_u16DataToSend){
	s8 local_s8Counter;
	u8 local_u8Bit;
	for(local_s8Counter=15; local_s8Counter>=0; local_s8Counter--)
	{
		/* send bit by bit starting from MSB */
		local_u8Bit = GET_BIT(copy_u16DataToSend,local_s8Counter);

		MGPIO_voidSetPinValue(STP_SERIAL_DATA,local_u8Bit);

		/* Send pulse to shift clock */
		MGPIO_voidSetPinValue(STP_SHIFT_CLOCK,HIGH);
		MSTK_voidSetBusyWait(1);
		MGPIO_voidSetPinValue(STP_SHIFT_CLOCK,LOW);
		MSTK_voidSetBusyWait(1);

	}

	/* Send Pulse to store Clock */
	  MGPIO_voidSetPinValue(STP_STORE_CLOCK,HIGH);
      MSTK_voidSetBusyWait(1);
      MGPIO_voidSetPinValue(STP_STORE_CLOCK,LOW);
      MSTK_voidSetBusyWait(1);

}
