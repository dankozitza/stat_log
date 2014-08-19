
#ifndef _STAT_LOG
#define _STAT_LOG

#include "log_mgr.hpp"

// stat_log
// 
// capabilities:
//    to be implemented into all functions with the ability to return int.
//    Maybe modify to be able to return any object but to wrap status object 
//    another object. Object's class would have to have return function.
//
// to do:
//    - get basic status conditions defined and accessable
//    - create some way of storing the last used status object, preferably one
//      that will allow for multiple processes
//          - could use diskhash,
//          - research ways of storing data within ram and accessing it from
//            any newly initialized stat object.
//
//    - use conf.h to store global status
//    - add status checker in destructor
//    - implement this class in a go method

class stat_log {

   private:
      enum condition { FAIL = 0, PASS = 1, FATAL = 2};
      condition status = PASS;
      const char *message = "initialization pass message";
      const char *id = "stat";
      const char *orig_id = NULL;
      std::string temp_id;
      log_mgr log;

   public:

      stat_log();
      stat_log(const char* identifier);


      int set_id(const char* identifier);
      int tmp_id(const char* identifier);
      void resolve();

      // stat::get
      //
      // returns the condition currently stored in status, conditions are
      // 0, 1, 2, FAIL, PASS, FATAL respectively.
      //
      int get();

      // stat::is_pass
      //
      // returns 1 or 0 so it can be used in if statements
      //
      int is_pass();

      // stat::msg
      //
      // returns the string stored in message. string may be a generic
      // status message or a custom message.
      //
      // currently only get one character
      //
      char msg();

      void msg(const char* m);
      void raw_msg(const char* m);
      void raw_msg(int i);

      // stat::pass
      //
      // sets the current condition to PASS and returns 1
      //
      int pass();
      int pass(const char* msg);

      // stat::fail
      //
      // sets the current condition to FAIL and returns 0
      //
      int fail();
      int fail(const char* msg);

      // stat::fatal
      //
      // sets the current condition to FATAL and returns 2
      //
      int fatal();
      int fatal(const char* msg);

      void set_log_file(const char* filename);

//      ~stat_log() {};
//         store stat_stack("stat");
//         std::string storable_stat;
//         storable_stat = "stat " + id + " " + status + " " + message;
//         stat_stack.push(
//      }
};

#include "stat_log.cpp"
#endif
