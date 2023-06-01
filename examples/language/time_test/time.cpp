#include <ctime>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <chrono>

/*
  sizeof(time_t) = 8
  736941811 seconds since January 1, 2000 in the current timezone
  The day 2023/05/09 is a Tuesday.
  local: Sat Feb 15 10:15:00 2020 PST
  Sat Jan  1 00:00:00 2022
  sizeof(std::tm) = 56
  hours: 7
  min: 30
  sec: 0
  year: 113
  mon: 8
  mday: 10
  The time entered is: 7 hours and 30 minutes
  Parse failed
  tm_hour:  10
  tm_min:  3
  tm_sec:  31
  tm_mon:  4
  tm_mday:  9
  tm_year:  123
  tm_yday:  128
  tm_wday:  2
  f(42) = 267914296
  elapsed time: 1.60494s
 */
long fibonacci(unsigned n) {
  if (n < 2) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char **argv) {
  // https://cplusplus.com/reference/ctime/time/
  time_t timer;
  struct tm y2k = {0};
  double seconds;

  y2k.tm_hour = 0;
  y2k.tm_min = 0;
  y2k.tm_sec = 0;
  y2k.tm_year = 100;
  y2k.tm_mon = 0;
  y2k.tm_mday = 1;

  time(&timer);  /* get current time; same as: timer = time(NULL)  */

  seconds = difftime(timer, mktime(&y2k));

  printf("sizeof(time_t) = %ld\n", sizeof(timer));
  printf("%.f seconds since January 1, 2000 in the current timezone\n", seconds);

  time_t rawtime;
  struct tm *timeinfo;
  int year, month, day;
  const char *weekday[] = {"Sunday", "Monday",
                           "Tuesday", "Wednesday",
                           "Thursday", "Friday", "Saturday"
  };

  /* prompt user for date */
  //printf ("Enter year: "); fflush(stdout); scanf ("%d",&year);
  //printf ("Enter month: "); fflush(stdout); scanf ("%d",&month);
  //printf ("Enter day: "); fflush(stdout); scanf ("%d",&day);
  year = 2023;
  month = 5;
  day = 9;

  /* get current timeinfo and modify it to the user's choice */
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  timeinfo->tm_year = year - 1900;
  timeinfo->tm_mon = month - 1;
  timeinfo->tm_mday = day;

  /* call mktime: timeinfo->tm_wday will be set */
  // https://cplusplus.com/reference/ctime/mktime/
  mktime(timeinfo);

  printf("The day %4d/%02d/%02d is a %s.\n", year, month, day, weekday[timeinfo->tm_wday]);


  // https://en.cppreference.com/w/cpp/chrono/c/mktime
  setenv("TZ", "/usr/share/zoneinfo/America/Los_Angeles", 1); // POSIX-specific

  std::tm tm{};  // zero initialise
  tm.tm_year = 2020 - 1900; // 2020
  tm.tm_mon = 2 - 1; // February
  tm.tm_mday = 15; // 15th
  tm.tm_hour = 10;
  tm.tm_min = 15;
  tm.tm_isdst = 0; // Not daylight saving
  std::time_t t = std::mktime(&tm);
  std::tm local = *std::localtime(&t);

  std::cout << "local: " << std::put_time(&local, "%c %Z") << '\n';

  // https://en.cppreference.com/w/cpp/chrono/c/tm
  std::tm tm1{};
  tm1.tm_year = 2022 - 1900;
  tm1.tm_mday = 1;

  std::mktime(&tm1);
  std::cout << std::asctime(&tm1)
            << "sizeof(std::tm) = "
            << sizeof(std::tm) << '\n';

// https://cplusplus.com/reference/locale/time_get/get_time/
  std::locale loc;        // classic "C" locale

  // get time_get facet:
  const std::time_get<char> &tmget = std::use_facet<std::time_get<char> >(loc);

  std::ios::iostate state;
  std::istringstream iss("07:30:00");
  std::tm when;

  tmget.get_time(iss, std::time_get<char>::iter_type(), iss, state, &when);

  std::cout << "hours: " << when.tm_hour << '\n';
  std::cout << "min: " << when.tm_min << '\n';
  std::cout << "sec: " << when.tm_sec << '\n';

// https://cplusplus.com/reference/locale/time_get/get/

  // get time_get facet:
  auto &tmget1 = std::use_facet<std::time_get<char> >(loc);

  std::istringstream iss1("year:2013 month:09 day:10");
  std::string format("year:%Y month:%m day:%d");

  tmget1.get(iss1, std::time_get<char>::iter_type(), iss1, state, &when,
             format.data(), format.data() + format.length());

  std::cout << "year: " << when.tm_year << '\n';
  std::cout << "mon: " << when.tm_mon << '\n';
  std::cout << "mday: " << when.tm_mday << '\n';


  // https://cplusplus.com/reference/iomanip/get_time/
  //std::cout << "Please, enter the time: ";
// std::cin >> std::get_time(&when,"%R");   // extract time (24H format)

  if (std::cin.fail()) std::cout << "Error reading time\n";
  else {
    std::cout << "The time entered is: ";
    std::cout << when.tm_hour << " hours and " << when.tm_min << " minutes\n";
  }

// https://en.cppreference.com/w/cpp/locale/time_get
  std::tm t1 = {};
  std::istringstream ss("2011-Februar-18 23:12:34");
  //ss.imbue(std::locale("de_DE.utf-8"));

  ss >> std::get_time(&t1, "%Y-%b-%d %H:%M:%S");
  if (ss.fail())
    std::cout << "Parse failed\n";
  else
    std::cout << std::put_time(&t1, "%c") << '\n';

//https://www.ibm.com/docs/en/i/7.2?topic=functions-strptime-convert-string-datetime
  char buf[100];
  time_t t2;
  struct tm *timeptr, result;

  setlocale(LC_ALL, "/QSYS.LIB/EN_US.LOCALE");
  t2 = time(NULL);
  timeptr = localtime(&t2);
  strftime(buf, sizeof(buf), "%a %m/%d/%Y %r", timeptr);

  if (strptime(buf, "%a %m/%d/%Y %r", &result) == NULL)
    printf("\nstrptime failed\n");
  else {
    printf("tm_hour:  %d\n", result.tm_hour);
    printf("tm_min:  %d\n", result.tm_min);
    printf("tm_sec:  %d\n", result.tm_sec);
    printf("tm_mon:  %d\n", result.tm_mon);
    printf("tm_mday:  %d\n", result.tm_mday);
    printf("tm_year:  %d\n", result.tm_year);
    printf("tm_yday:  %d\n", result.tm_yday);
    printf("tm_wday:  %d\n", result.tm_wday);
  }

//  https://en.cppreference.com/w/cpp/chrono

  auto start = std::chrono::steady_clock::now();
  std::cout << "f(42) = " << fibonacci(42) << '\n';
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

