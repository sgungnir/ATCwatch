

#include "Arduino.h"
#include "sleep.h"
#include "time.h"
#include "inputoutput.h"
#include "push.h"
#include <TimeLib.h>

time_data_struct time_data;

int scheduleNotified = 0;

sched_data_struct sch_breakfast = {7,30,"Breakfast!!"};
sched_data_struct sch_morning_meeting = {8,00,"Morning meeting (ZOOM)"};
sched_data_struct sch_math = {8,15,"MATH (zoom)"};
sched_data_struct sch_ind_smll_group = {8,30,"Independent / Small group"};
sched_data_struct sch_break = {9,30,"Take a break !!"};
sched_data_struct sch_writing = {9,45,"Writing (ZOOM)"};
sched_data_struct sch_ind_smll_group2 = {10,0,"Independent / Small group"};

sched_data_struct sch_spc_STEAM = {10,35,"Special:STEAM (ZOOM)"};
sched_data_struct sch_spc_PE = {10,35,"Special:P.E. (ZOOM)"};
sched_data_struct sch_spc_MUSIC = {10,35,"Special:Music (ZOOM)"};

sched_data_struct sch_handwriting_phonics = {11,25,"Handwriting and Phonics (ZOOM)"};
sched_data_struct sch_lunch = {11,45,"Time for lunch !!"};
sched_data_struct sch_sci_soc_stud = {12,15,"Science and Social Studies"};
sched_data_struct sch_ind_smll_group3 = {12,30,"Independent / Small group"};
sched_data_struct sch_break2 = {13,0,"Take a break !!"};
sched_data_struct sch_reading = {13,25,"Reading - ELD (ZOOM)"};
sched_data_struct sch_ind_smll_group4 = {14,5,"Talk with Mrs. Ortiz"};
sched_data_struct sch_reflection = {14,30,"Reflection time (ZOOM)"};
sched_data_struct sch_end = {14,45,"End of school day!"};
/*
sched_data_struct sch_breakfast = {22,0,"Breakfast!!"};
sched_data_struct sch_morning_meeting = {22,1,"Morning meeting (ZOOM)"};
sched_data_struct sch_math = {22,2,"MATH (zoom)"};
sched_data_struct sch_ind_smll_group = {23,1,"Independent / Small group"};
sched_data_struct sch_break = {23,2,"Take a break !!"};
sched_data_struct sch_writing = {23,3,"Writing (ZOOM)"};
sched_data_struct sch_ind_smll_group2 = {23,4,"Independent / Small group"};
sched_data_struct sch_spc_STEAM = {23,5,"Special:STEAM (ZOOM)"};
sched_data_struct sch_handwriting_phonics = {23,10,"Handwriting and Phonics (ZOOM)"};
sched_data_struct sch_lunch = {23,11,"Time for lunch !!"};
sched_data_struct sch_sci_soc_stud = {23,12,"Science and Social Studies"};
sched_data_struct sch_ind_smll_group3 = {23,13,"Independent / Small group"};
sched_data_struct sch_break2 = {23,14,"Take a break !!"};
sched_data_struct sch_reading = {23,15,"Reading - ELD (ZOOM)"};
sched_data_struct sch_ind_smll_group4 = {23,16,"Independent / Small group"};
sched_data_struct sch_reflection = {23,17,"Reflection time (ZOOM)"};
sched_data_struct sch_end = {23,18,"End of school day!"};
*/
sched_data_struct schedNULL = {99,2,"Shouldn't play"};
sched_data_struct schedList[7][17] = {{schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL}, //Sunday ? 
                                      {sch_breakfast,sch_morning_meeting,sch_math,sch_ind_smll_group,sch_break,sch_writing,sch_ind_smll_group2,sch_spc_STEAM,sch_handwriting_phonics,sch_lunch,sch_sci_soc_stud,sch_ind_smll_group3,sch_break2,sch_reading,sch_ind_smll_group4,sch_reflection,sch_end}, //Monday
                                      {sch_breakfast,sch_morning_meeting,sch_math,sch_ind_smll_group,sch_break,sch_writing,sch_ind_smll_group2,sch_spc_PE,sch_handwriting_phonics,sch_lunch,sch_sci_soc_stud,sch_ind_smll_group3,sch_break2,sch_reading,sch_ind_smll_group4,sch_reflection,sch_end}, //Tuesday
                                      {sch_breakfast,sch_morning_meeting,sch_math,sch_ind_smll_group,sch_break,sch_writing,sch_ind_smll_group2,sch_spc_MUSIC,sch_handwriting_phonics,sch_lunch,sch_sci_soc_stud,sch_ind_smll_group3,sch_break2,sch_reading,sch_ind_smll_group4,sch_reflection,sch_end}, //Wednesday
                                      {sch_breakfast,sch_morning_meeting,sch_math,sch_ind_smll_group,sch_break,sch_writing,sch_ind_smll_group2,sch_spc_PE,sch_handwriting_phonics,sch_lunch,sch_sci_soc_stud,sch_ind_smll_group3,sch_break2,sch_reading,sch_ind_smll_group4,sch_reflection,sch_end}, //Thursday
                                      {sch_breakfast,sch_morning_meeting,sch_math,sch_ind_smll_group,sch_break,sch_writing,sch_ind_smll_group2,sch_spc_STEAM,sch_handwriting_phonics,sch_lunch,sch_sci_soc_stud,sch_ind_smll_group3,sch_break2,sch_reading,sch_ind_smll_group4,sch_reflection,sch_end}, //Friday
                                      {schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL,schedNULL}};//Saturday


void init_time() {
  int year = 2020;
  int month = 1;
  int day = 1;
  int hr = 0;
  int min = 0;
  int sec = 0;
  setTime( hr, min, sec, day, month, year);
}

time_data_struct get_time() {
  time_data.year = year();
  time_data.month = month();
  time_data.day = day();
  time_data.hr = hour();
  time_data.min = minute();
  time_data.sec = second();
  time_data.dayofweek = weekday();
  return time_data;
}

void SetDateTimeString(String datetime) {
  int year = datetime.substring(0, 4).toInt();
  int month = datetime.substring(4, 6).toInt();
  int day = datetime.substring(6, 8).toInt();
  int hr = datetime.substring(8, 10).toInt();
  int min = datetime.substring(10, 12).toInt();
  int sec = datetime.substring(12, 14).toInt();
  setTime( hr, min, sec, day, month, year);

  //find next daily alarm
  time_data_struct time_data = get_time();
  scheduleNotified = 0;
  int dayoftheweek=time_data.dayofweek-1;
  if(dayoftheweek<0) dayoftheweek=0;
  while (scheduleNotified<17){
    if (time_data.hr>schedList[dayoftheweek][scheduleNotified].sch_hr){
      scheduleNotified++;
      continue;
    } 
    //else {
    //  break;
    //}

    if ((time_data.hr==schedList[dayoftheweek][scheduleNotified].sch_hr)&&(time_data.min>=schedList[dayoftheweek][scheduleNotified].sch_min)){
      scheduleNotified++;
      continue;
    } else {
      break;
    }
  }
  
}

void checkSchedule(){
    time_data_struct time_data = get_time();
    int dayoftheweek=time_data.dayofweek-1;
    if(dayoftheweek<0) dayoftheweek=0;

    if ((time_data.hr==schedList[dayoftheweek][scheduleNotified].sch_hr)&&(time_data.min==schedList[dayoftheweek][scheduleNotified].sch_min)) {// check for new day
        show_push(schedList[dayoftheweek][scheduleNotified].sch_description);
        scheduleNotified++;
        if(scheduleNotified>=17) {
          scheduleNotified==0;
        }
    }
}

void clearscheduleNotified(){
  scheduleNotified=0;
}

void SetDate(int year, int month, int day) {
  time_data = get_time();
  setTime( time_data.hr, time_data.min, time_data.sec, day, month, year);
}

void SetTime(int hr, int min) {
  time_data = get_time();
  setTime( hr, min, 0, time_data.day, time_data.month, time_data.year);
}

String GetDateTimeString() {
  String datetime = String(year());
  if (month() < 10) datetime += "0";
  datetime += String(month());
  if (day() < 10) datetime += "0";
  datetime += String(day());
  if (hour() < 10) datetime += "0";
  datetime += String(hour());
  if (minute() < 10) datetime += "0";
  datetime += String(minute());
  return datetime;
}
