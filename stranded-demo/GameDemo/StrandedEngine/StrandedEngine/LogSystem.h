/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#ifndef _UGP_LOG_SYSTEM_H_
#define _UGP_LOG_SYSTEM_H_


#include<fstream>
#include<stdarg.h>


class CLogSystem
{
   public:
      CLogSystem() { ClearLog(NULL); }
      bool ClearLog(const char *filename);
      bool WriteLog(const char *filename, const char *message, ...);
      bool AppendLog(const char *filename, const char *message, ...);
      
   private:
      bool Write(std::ofstream &file, const char *message);
      bool Write(std::ofstream &file, const char *message, va_list &args);

   private:
      std::ofstream errorLog;
};

#endif