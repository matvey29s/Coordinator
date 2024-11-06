/*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  udpClientRAW.c
  Author:     ControllersTech.com
  Updated:    Jul 23, 2021

  ***************************************************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ***************************************************************************************************************
*/


#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "main.h"
#include "stdio.h"
#include "string.h"

#include "udpClientRAW.h"

#define SIZE 1203
static void udpClient_send(void);
struct udp_pcb *upcb;

extern uint8_t result_data[6015];
uint8_t dublicate[6015];
//extern uint8_t data_buffer[6015];
uint8_t data[300];
//uint8_t count=0;
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;
extern struct netif gnetif;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	ethernetif_input(&gnetif);
	udpClient_send();
	sys_check_timeouts();
/*
	count++;
	if(count>5) {
		count=0;
		memcpy(result_data,dublicate,6015);
	}*/
}



void udpClient_connect(void)
{
	err_t err;

	/* 1. Create a new UDP control block  */
	upcb = udp_new();

	/* Bind the block to module's IP and port */
	ip_addr_t myIPaddr;
	IP_ADDR4(&myIPaddr, 192, 168, 1, 123);
	//udp_bind(upcb, &myIPaddr, 8);
	udp_bind(upcb, &myIPaddr, 1027);


	/* configure destination IP address and port */
	ip_addr_t DestIPaddr;
	IP_ADDR4(&DestIPaddr, 192, 168, 1, 104);
	//err= udp_connect(upcb, &DestIPaddr, 7);
	err= udp_connect(upcb, &DestIPaddr, 1024);
	if (err == ERR_OK)
	{
		/* 2. Send message to server */
		udpClient_send ();

		/* 3. Set a receive callback for the upcb */
	}
}

static void udpClient_send(void)
{
  struct pbuf *txBuf;


  //int i=0;
	  //int len = sprintf(data,"* %u %u %u %u %u %u %u %u %u %u %u %u %u ! * %u %u %u %u %u %u %u %u %u %u %u %u %u ! * %u %u %u %u %u %u %u %u %u %u %u %u %u ! * %u %u %u %u %u %u %u %u %u %u %u %u %u ! * %u %u %u %u %u %u %u %u %u %u %u %u %u ! ",result_data[1],result_data[2+12*i],result_data[3+12*i],result_data[4+12*i],result_data[5+12*i],result_data[6+12*i],result_data[7+12*i],result_data[8+12*i],result_data[9+12*i],result_data[10+12*i],result_data[11+12*i],result_data[12+12*i],result_data[13+12*i],result_data[1204],result_data[1205+12*i],result_data[1206+12*i],result_data[1207+12*i],result_data[1208+12*i],result_data[1209+12*i],result_data[1210+12*i],result_data[1211+12*i],result_data[1212+12*i],result_data[1213+12*i],result_data[1214+12*i],result_data[1215+12*i],result_data[1216+12*i],result_data[2407],result_data[2408+12*i],result_data[2409+12*i],result_data[2410+12*i],result_data[2411+12*i],result_data[2412+12*i],result_data[2413+12*i],result_data[2414+12*i],result_data[2415+12*i],result_data[2416+12*i],result_data[2417+12*i],result_data[2418+12*i],result_data[2419+12*i],result_data[3610],result_data[3611+12*i],result_data[3612+12*i],result_data[3613+12*i],result_data[3614+12*i],result_data[3615+12*i],result_data[3616+12*i],result_data[3617+12*i],result_data[3618+12*i],result_data[3619+12*i],result_data[3620+12*i],result_data[3621+12*i],result_data[3622+12*i],result_data[4813],result_data[4814+12*i],result_data[4815+12*i],result_data[4816+12*i],result_data[4817+12*i],result_data[4818+12*i],result_data[4819+12*i],result_data[4820+12*i],result_data[4821+12*i],result_data[4822+12*i],result_data[4823+12*i],result_data[4824+12*i],result_data[4825+12*i]);
  for(int i=0;i<100;i++) {

	 int len = sprintf(data,"* 1 %u %u %u %u %u %u %u %u %u %u %u %u ! * 2 %u %u %u %u %u %u %u %u %u %u %u %u ! * 3 %u %u %u %u %u %u %u %u %u %u %u %u ! * 4 %u %u %u %u %u %u %u %u %u %u %u %u ! * 5 %u %u %u %u %u %u %u %u %u %u %u %u !",result_data[2+12*i],result_data[3+12*i],result_data[4+12*i],result_data[5+12*i],result_data[6+12*i],result_data[7+12*i],result_data[8+12*i],result_data[9+12*i],result_data[10+12*i],result_data[11+12*i],result_data[12+12*i],result_data[13+12*i],result_data[1205+12*i],result_data[1206+12*i],result_data[1207+12*i],result_data[1208+12*i],result_data[1209+12*i],result_data[1210+12*i],result_data[1211+12*i],result_data[1212+12*i],result_data[1213+12*i],result_data[1214+12*i],result_data[1215+12*i],result_data[1216+12*i],result_data[2408+12*i],result_data[2409+12*i],result_data[2410+12*i],result_data[2411+12*i],result_data[2412+12*i],result_data[2413+12*i],result_data[2414+12*i],result_data[2415+12*i],result_data[2416+12*i],result_data[2417+12*i],result_data[2418+12*i],result_data[2419+12*i],result_data[3611+12*i],result_data[3612+12*i],result_data[3613+12*i],result_data[3614+12*i],result_data[3615+12*i] ,result_data[3616+12*i],result_data[3617+12*i],result_data[3618+12*i],result_data[3619+12*i],result_data[3620+12*i],result_data[3621+12*i],result_data[3622+12*i],result_data[4814+12*i],result_data[4815+12*i],result_data[4816+12*i],result_data[4817+12*i],result_data[4818+12*i],result_data[4819+12*i],result_data[4820+12*i],result_data[4821+12*i],result_data[4822+12*i],result_data[4823+12*i],result_data[4824+12*i],result_data[4825+12*i]);
	  //int len = sprintf(data,"* %u %u %u %u %u %u %u %u %u %u %u %u %u !",result_data[4813],result_data[4814+12*i],result_data[4815+12*i],result_data[4816+12*i],result_data[4817+12*i],result_data[4818+12*i],result_data[4819+12*i],result_data[4820+12*i],result_data[4821+12*i],result_data[4822+12*i],result_data[4823+12*i],result_data[4824+12*i],result_data[4825+12*i]);
	  txBuf = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
	  if (txBuf != NULL)
	  	 {
		  /* copy data to pbuf */
		  pbuf_take(txBuf, data,len);

		  /* send udp data */
		  udp_send(upcb, txBuf);

		  /* free pbuf */
		 pbuf_free(txBuf);
	  	  }
  }


}



