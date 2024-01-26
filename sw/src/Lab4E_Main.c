// -------------------------------------------------------------------
// File name:     Lab4E_Main.c
// Description:   This code is the main loop for the new MQTT Clock Control IOT Lab
//               
// Authors:       Mark McDermott
// Date:          June 6, 2023
//
// 

#include <stdio.h>
#include <stdint.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/ST7735.h"
#include "inc/PLL.h"
#include "inc/Timer2A.h"
#include "inc/Timer5A.h"
#include "inc/UART.h"
#include "inc/UART5.h"
#include "inc/esp8266_base.h"
#include "inc/MQTT.h"
#include "inc/Unified_Port_Init.h"
//#include "Lab4E.h"

uint32_t         Mode_Value;      //
uint32_t         Left_Value;      //
uint32_t         Right_Value;     //
uint32_t         Up_Value;        //
uint32_t         Down_Value;      //


//----- Prototypes of functions in startup.s  ----------------------
//
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // Go into low power mode

// -----------------------------------------------------------------
// -------------------- MAIN LOOP ----------------------------------
//
int main(void){  
  DisableInterrupts();            // Disable interrupts until finished with inits     
  PLL_Init(Bus80MHz);             // Bus clock at 80 MHz
  UART_Init();                    // Allow us to talk to the PC via PuTTy!
  UART5_Init();                   // Enable ESP8266 Serial Port
  ST7735_InitR(INITR_REDTAB);     // Start up display.
  Unified_Port_Init();						// Initialize the Ports used for this lab
  Reset_8266();                   // Reset the WiFi module
  SetupWiFi();                    // Setup communications to MQTT Broker via 8266 WiFi
  
  Timer2A_Init(&MQTT_to_TM4C, 400000, 7);         // Check/Get data from the ESP every 5ms 
  Timer5A_Init(&TM4C_to_MQTT, 80000000, 7);       // Send data back to MQTT Web App every second 
  
  EnableInterrupts();

  //Integrate your lab 3 here
  while(1){   
    WaitForInterrupt();       // Wait to run the clock until the next interrupt
  }
}

