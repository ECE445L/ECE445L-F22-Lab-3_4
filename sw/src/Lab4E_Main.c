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
//#include "inc/Timers.h"
#include "inc/Timer2A.h"
#include "inc/Timer5A.h"
#include "inc/UART2.h"
#include "inc/UART5.h"
#include "inc/esp8266.h"
#include "inc/MQTT.h"
#include "inc//Unified_Port_Init.h"
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
  PLL_Init(Bus80MHz);                 // Bus clock at 80 MHz
  DisableInterrupts();        // Disable interrupts until finished with inits
  Unified_Port_Init();								// Initialize the Ports used for this lab
  Output_Init();              // Initialize ST7735 LCD
  UART2_Init();               // Enable Debug Serial Port
  UART5_Init();               // Enable ESP8266 Serial Port
  Reset_8266();               // Reset the WiFi module
  SetupWiFi();                // Setup communications to MQTT Broker via 8266 WiFi
  
  //Timer0_Init(&clock_1ms,80000);              // Timer0 trigger every 1ms 
  Timer2A_Init(&MQTT_to_TM4C, 400000, 7);         // Get data every 5ms 
  Timer5A_Init(&TM4C_to_MQTT, 80000000, 7);       // Send data back to MQTT Web App every second 
  
  EnableInterrupts();

  while(1){   
    //Insert your lab 3
    WaitForInterrupt();       // Wait to run the clock until the next interrupt
  }
}

