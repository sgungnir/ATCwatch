

//You can use and edit the code as long as you mention me (Aaron Christophel and https://ATCnetz.de) in the source and somewhere in the menu of the working firmware, even when using small peaces of the code. :)
//If you want to use the code or parts of it commercial please write an email to: info@atcnetz.de

//This code uses the BMA421 Library wich is made by Bosch and this is under copyright by Bosch Sensortech GmbH

#include "pinout.h"
#include "watchdog.h"
#include "tasks.h"
#include "fast_spi.h"
#include "i2c.h"
#include "bootloader.h"
#include "inputoutput.h"
#include "backlight.h"
#include "battery.h"

#include "time.h"
#include "touch.h"
#include "sleep.h"
#include "ble.h"
#include "interrupt.h"
#include "menu.h"
#include "display.h"
#include "accl.h"
#include "push.h"
#include "flash.h"

bool stepsWhereReseted = false;
/*
int scheduleNotified = 0;


sched_data_struct sched1 = {0,20,"Sched item 1 Mon!!"};
sched_data_struct sched2 = {0,22,"Sched item 2 Mon!!"};
sched_data_struct sched3 = {0,23,"Sched item 3 Mon!!"};
sched_data_struct sched4 = {0,24,"Sched item 4 Mon!!"};
sched_data_struct sched5 = {0,25,"Sched item 5 Mon!!"};
sched_data_struct sched6 = {0,26,"Sched item 6 Mon!!"};
sched_data_struct sched7 = {99,2,"Shouldn't play"};
sched_data_struct schedList[7][10] = {{sched7,sched7,sched7,sched7,sched7,sched7}, //Sunday ? 
                                      {sched1,sched2,sched3,sched4,sched5,sched6}, //Monday
                                      {sched7,sched7,sched7,sched7,sched7,sched7}, //Tuesday
                                      {sched7,sched7,sched7,sched7,sched7,sched7}, //Wednesday
                                      {sched7,sched7,sched7,sched7,sched7,sched7}, //Thursday
                                      {sched7,sched7,sched7,sched7,sched7,sched7}, //Friday
                                      {sched7,sched7,sched7,sched7,sched7,sched7}};//Saturday

*/
void setup() {
  delay(500);
  if (get_button()) {//if button is pressed on startup goto Bootloader
    NRF_POWER->GPREGRET = 0x01;
    NVIC_SystemReset();
  }
  init_watchdog();// Init all kind of hardware and software
  initRTC2();
  init_tasks();
  init_bootloader();
  init_fast_spi();//needs to be before init_display and external flash
  init_i2c();//needs to be before init_hrs3300, init_touch and init_accl
  init_inputoutput();
  init_backlight();
  init_display();
  display_booting();
  set_backlight(3);
  init_battery();
  init_time();
  init_touch();
  init_sleep();
  init_menu();
  init_push();
  init_flash();
  init_accl();
  init_ble();//must be before interrupts!!!
  init_interrupt();//must be after ble!!!
  delay(100);
  set_backlight(3);
  display_home();
  
}

void loop() {
  ble_feed();//manage ble connection
  if (!get_button())watchdog_feed();//reset the watchdog if the push button is not pressed, if it is pressed for more then WATCHDOG timeout the watch will reset
  if (get_sleep()) {//see if we are sleeping
    sleep_wait();//just sleeping
  } else {//if  we are awake do display stuff etc
    check_sleep_times();//check if we should go sleeping again
    display_screen();//manage menu and display stuff
    check_battery_status();// check battery status. if lower than XX show message
  }
  if (get_timed_int()) {//Theorecticly every 40ms via RTC2 but since the display takes longer its not accurate at all when display on
    if (get_sleep()) {
      if (acc_input()){
         sleep_up(WAKEUP_ACCL);//check if the hand was lifted and turn on the display if so
      }
    }
    time_data_struct time_data = get_time();
    checkSchedule();
    if (time_data.hr == 0) {// check for new day
      if (!stepsWhereReseted) {//reset steps on a new day
        stepsWhereReseted = true;
        reset_step_counter();
        
      }
    } else stepsWhereReseted = false;

      }
  gets_interrupt_flag();//check interrupt flags and do something with it
}
