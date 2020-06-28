
#pragma once
#include "Arduino.h"
#include "class.h"
#include "images.h"
#include "menu.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"
#include "mksd50.h"


class CalendarScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_gray_screen_style(&sans_regular);
      time_data = get_time();
  
      calendar = lv_calendar_create(lv_scr_act(), NULL);
      lv_obj_set_size(calendar, 240, 240);
      lv_obj_align(calendar, NULL, LV_ALIGN_CENTER, 0, 0);
  
      /*Set the today*/
      today.year = time_data.year;
      today.month = time_data.month;
      today.day = time_data.day;

      showDate.year = time_data.year;
      showDate.month = time_data.month;
      showDate.day = 1;

      lv_calendar_set_today_date(calendar, &today);
      lv_calendar_set_showed_date(calendar, &showDate);
    }

    virtual void main()
    {
    }
    virtual void left()
    {
      inc_vars_sideways();
    }

    virtual void right()
    {
      set_last_menu();
    }
    
    virtual void down()
    {
      //change to previous month
      if(showDate.month >1) {
        showDate.month --;
      } else {
        showDate.year --;
        showDate.month = 12;
      }

      lv_calendar_set_showed_date(calendar, &showDate);

    }
    virtual void up()
    {
      //change to next month
      if(showDate.month <12) {
        showDate.month ++;
      } else {
        showDate.year ++;
        showDate.month = 1;
      }

      lv_calendar_set_showed_date(calendar, &showDate);

    }

  private:
    time_data_struct time_data;
    lv_obj_t *calendar;
    lv_calendar_date_t today;
    lv_calendar_date_t showDate;
};
