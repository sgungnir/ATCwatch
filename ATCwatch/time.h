
#pragma once

#include "Arduino.h"

struct time_data_struct {
  int year;
  int month;
  int day;
  int hr;
  int min;
  int sec;
  int dayofweek;
};

struct sched_data_struct {
  int sch_hr;
  int sch_min;
  String sch_description;
};

void init_time();
time_data_struct get_time();
void SetDateTimeString(String datetime);
void SetDate(int year, int month, int day);
void SetTime(int hr, int min);
String GetDateTimeString();
void checkSchedule();
void clearscheduleNotified();
