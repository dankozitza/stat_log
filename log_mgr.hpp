// log_mgr
//
//    logging utility capable of writing to stdout and to disk. It also 
//    prefixes identifiers to all messages. you can print without adding 
//    the prefix by using log_mgr::raw_msg()
//

#ifndef _LOG_MGR
#define _LOG_MGR

#include <fstream>
#include <iostream>
#include <ctime>
#include "conf.hpp"

class log_mgr {

   private:
   
      const char* log_file = "/tmp/default_log.txt";
      const char* identifier = "msg";
      const char* indent = "\n           "; 
      const char* prefix_str = "";
      int to_file_flag = 1;
      int to_stdout_flag = 1;
      conf* config = conf::inst();

   public:

      log_mgr() {
         if (config->defined("log_file")) {
            log_file = config->get("log_file");
         }
         if (config->defined("write_to_stdout")) {
            to_stdout_flag = config->get("write_to_stdout", 0);
         }
         if (config->defined("write_to_file")) {
            to_file_flag = config->get("write_to_file", 0);
         }
      };

      log_mgr(const char* id) {
         identifier = id;

         if (config->defined("log_file")) {
            log_file = config->get("log_file");
         }
         if (config->defined("write_to_stdout")) {
            to_stdout_flag = config->get("write_to_stdout", 0);
         }
         if (config->defined("write_to_file")) {
            to_file_flag = config->get("write_to_file", 0);
         }
      }
      ~log_mgr() {
         if (to_file_flag) {
            std::ofstream fh (log_file, std::ios::app);
            fh << "\n";
            fh.close();
         }
         if (to_stdout_flag) {
            std::cout << std::endl;
         }
      };

      void msg(const char* message) {
         time_t time_thing = time(0);
         std::string the_time = ctime(&time_thing);
         the_time.replace(0, 11, "[");
         the_time.replace(9, 9, "] [");

         std::string replace_str = "\n";

         std::string str_msg = message;

         int found = 0;

         found = str_msg.find(replace_str, found);

         while (found != str_msg.npos) {
            std::string indent_str = indent;
            int indent_len = indent_str.size()-1;
            std::string the_prefix;
            the_prefix = indent;

            // this will add the identifier to the end of the indent after
            // every newline.
            the_prefix += "[";
            the_prefix += identifier;
            the_prefix +=  "] ";
            str_msg.replace(found, 1, the_prefix);
            found = str_msg.find(replace_str, found+1);
         }

         if (to_file_flag) {
            std::ofstream fh (log_file, std::ios::app);
            fh << "\n" << the_time << identifier << "] " <<  message;
            fh.close();
         }
         if (to_stdout_flag) {
            std::cout << "<br>\n" << the_time << identifier << "] " <<  str_msg;
         }
         return;
      }

      void raw_msg(const char* message) {
         if (to_file_flag) {
            std::ofstream fh (log_file, std::ios::app);
            fh << message;
            fh.close();
         }
         if (to_stdout_flag) {
            std::cout << message;
         }
         return;
      }

      void raw_msg(int integer) {
         if (to_file_flag) {
            std::ofstream fh (log_file, std::ios::app);
            fh << integer;
            fh.close();
         }
         if (to_stdout_flag) {
            std::cout << integer;
         }
         return;
      }

      void raw_msg(long unsigned int luinteger) {
         if (to_file_flag) {
            std::ofstream fh (log_file, std::ios::app);
            fh << luinteger;
            fh.close();
         }
         if (to_stdout_flag) {
            std::cout << luinteger;
         }
         return;
      }

      void set_id(const char* id) {
         identifier = id;
         return;
      }

      void prefix(const char* prefix_string) {
         prefix_str = prefix_string;
         return;
      }

      void set_file(const char* filename) {
         log_file = filename;
         return;
      }

      void to_file(int flag) {
         if (flag == 0 || flag == 1) {
            to_file_flag = flag;
         }
         return;
      }
      void to_stdout(int flag) {
         if (flag == 0 || flag == 1) {
            to_stdout_flag = flag;
         }
         return;
      }
};

#endif
