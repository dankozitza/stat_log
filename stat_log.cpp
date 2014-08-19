#include "stat_log.h"

stat_log::stat_log() {};

stat_log::stat_log(const char* identifier) {
   id = identifier;
   log.set_id(id);
   //log.set_file("/tad/log/xfs_crawl.log");
}

//~stat() {
//     store stat_stack("stat");
//     std::string storable_stat;
//     storable_stat = "stat " + id + " " + status + " " + message;
//     stat_stack.push(
//};

int stat_log::set_id(const char* identifier) {
   log.set_id(identifier);
   id = identifier;
   return 1;
}

int stat_log::tmp_id(const char* identifier) {
   orig_id = id;
   temp_id.assign(id);
   temp_id.append("::");
   temp_id.append(identifier);

   id = temp_id.c_str();
   log.set_id(id);
   return 1;
}

void stat_log::resolve() {
   if (orig_id != NULL) {
      id = orig_id;
      log.set_id(id);
      orig_id = NULL;
   }
}

// stat::get
//
// returns the condition currently stored in status, conditions are
// 0, 1, 2, FAIL, PASS, FATAL respectively.
//
int stat_log::get() {
   return status;
}

// stat::is_pass
//
// returns 1 or 0 so it can be used in if statements
//
int stat_log::is_pass() {

   if (status == PASS) {
      return 1;
   }
   else {
      return 0;
   }
}

// stat::msg
//
// returns the string stored in message. string may be a generic
// status message or a custom message.
//
// currently only get one character
//
char stat_log::msg() {
   return *message;
}

void stat_log::msg(const char* m) {
   log.msg(m);
}
void stat_log::raw_msg(const char* m) {
   log.raw_msg(m);
}
void stat_log::raw_msg(int i) {
   log.raw_msg(i);
}

// stat::pass
//
// sets the current condition to PASS and returns 1
//
int stat_log::pass() {
   status = PASS;
   message = "generic pass message";
   log.msg("[PASS] stat condition set to pass");
   resolve();
   return status;
}

int stat_log::pass(const char* msg) {
   status = PASS;
   message = msg;

   log.set_id("PASS");

   std::string tmp_msg = "[";
   tmp_msg += id;
   tmp_msg += "] stat condition set to pass";

   log.msg(tmp_msg.c_str());
   //log.msg("[", id, "] stat condition set to pass");
   log.set_id("PASS] [msg");
   log.msg(message);
   log.set_id(id);

   resolve();
   return status;
}
   

// stat::fail
//
// sets the current condition to FAIL and returns 0
//
int stat_log::fail() {
   status = FAIL;
   message = "generic fail message";
   log.msg("[FAIL] stat condition set to fail");
   resolve();
   return status;
}

int stat_log::fail(const char* msg) {
   status = FAIL;
   message = msg;

   log.set_id("FAIL");

   std::string tmp_msg = "[";
   tmp_msg += id;
   tmp_msg += "] stat condition set to fail";

   log.msg(tmp_msg.c_str());

   log.set_id("FAIL] [msg");
   log.msg(message);
   log.set_id(id);

   resolve();
   return status;
}


// stat::fatal
//
// sets the current condition to FATAL and returns 2
//
int stat_log::fatal() {
   status = FATAL;
   //
   // here should log stack and drop to shell mode.
   //
   log.msg("[FATAL] !!! generic fatal error!");
   resolve();
   return status;
}

int stat_log::fatal(const char* msg) {
   status = FATAL;
   message = msg;

   log.set_id("FATAL");

   std::string tmp_msg = "[";
   tmp_msg += id;
   tmp_msg += "] stat condition set to fatal";

   log.msg(tmp_msg.c_str());

   log.set_id("FATAL] [msg");
   log.msg(message);
   log.set_id(id);

   resolve();
   return status;
}

void stat_log::set_log_file(const char* filename) {
   log.set_file(filename);
   return;
}
