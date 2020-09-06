
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
#include "fonts.h"


class NotifyScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_gray_screen_style(&sans_regular);

      lv_style_copy( &st, &lv_style_plain );
      st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      st.text.font = &mksd50;

      lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(img1, &IsymbolMsgSmall);
      lv_obj_align(img1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

      label_datetime = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_long_mode(label_datetime, LV_LABEL_LONG_BREAK);
      lv_obj_set_width(label_datetime,200);
      lv_label_set_text(label_datetime, "00:00am, day 00.00");
      lv_obj_align(label_datetime, img1, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

      label_msg = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_long_mode(label_msg, LV_LABEL_LONG_BREAK);
      lv_obj_set_width(label_msg,240);
      lv_label_set_text(label_msg, "");
      lv_obj_set_style( label_msg, &st );

      //lv_label_set_text(label_msg, string2char(get_push_msg()));
      lv_obj_align(label_msg, img1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 5);

    }

    virtual void main()
    {
      
      time_data = get_time();
      char timedate_string[18];
      int hr=time_data.hr;
      bool pm=false;
      if (hr<12) {
        if (hr==0) hr=12;
        pm=false;
      } else {
        if (hr>12) hr-=12;
        pm=true;
      }

      if(pm){
      sprintf(timedate_string, "%02i:%02ipm, aaa %02i.%02i", hr, time_data.min, time_data.month,time_data.day);
      } else {
      sprintf(timedate_string, "%02i:%02iam, aaa %02i.%02i", hr, time_data.min, time_data.month,time_data.day);
      }

      switch(time_data.dayofweek)
      {
      case 1:
        timedate_string[9]='s';timedate_string[10]='u';timedate_string[11]='n';
        break;  
      case 2:
        timedate_string[9]='m';timedate_string[10]='o';timedate_string[11]='n';
        break;  
      case 3:
        timedate_string[9]='t';timedate_string[10]='u';timedate_string[11]='e';
        break;  
      case 4:
        timedate_string[9]='w';timedate_string[10]='e';timedate_string[11]='d';
        break;  
      case 5:
        timedate_string[9]='t';timedate_string[10]='h';timedate_string[11]='u';
        break;  
      case 6:
        timedate_string[9]='f';timedate_string[10]='r';timedate_string[11]='i';
        break;  
      case 7:
        timedate_string[9]='s';timedate_string[10]='a';timedate_string[11]='t';
        break;  
      }
      
      lv_label_set_text(label_datetime, timedate_string);
      lv_label_set_text(label_msg, string2char(get_push_msg()));
	  //lv_label_set_text(label_msg, "MATH IN 5 MINUTES!!!");
    }

    virtual void long_click()
    {
      display_home();
    }

    virtual void left()
    {
      inc_vars_sideways();
    }

    virtual void right()
    {
      set_last_menu();
    }

    virtual void up()
    {
      display_home();
    }
    virtual void down()
    {
      display_home();
    }

    virtual void click(touch_data_struct touch_data)
    {
      display_home();
    }

  private:
    time_data_struct time_data;
    lv_obj_t *label, *label_msg, *label_datetime;
    lv_style_t st;

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

NotifyScreen notifyScreen;
