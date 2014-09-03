#include "stat_log.hpp"
#include "log_mgr.hpp"
#include "conf.hpp"
#include <iostream>
using namespace std;

int test_subroutine() {
   log_mgr tsub_log;
   tsub_log.set_id("stat_test::test_sub");
   tsub_log.msg("this is the test subroutine");
   tsub_log.msg("returning stat.pass(\"message\")");

   stat_log tsub_status("stat_test::test_sub");

   return tsub_status.pass("test_subroutine() had successful test run");
}

int main() {

   conf* config = conf::inst("./cls_test.conf");
   //log_mgr blah;
   //cout << "config->get('log_file') = " << config->get("log_file") << endl;

   cout << "--- stat_log.h_test: testing stat.h\n";

   config->set("log_file", "stat_test.log");
   config->set("write_to_stdout", "1");
   config->set("write_to_file", "1");

   stat_log status("stat_log.h_test");

   cout << "--- stat_log.h_test: testing stat.msg('stuff');\n";

//   status.msg("before set to 0");
//   config->set("write_to_stdout", "0");
//   status.msg("after set to 0");

   cout << "\n--- stat_test: testing log_mgr.h\n";
  
   log_mgr log("stat_test");

   cout << "--- stat_test: testing log.set_id(\"stat_test\");\n";

   log.msg("test message 1 using log.msg()");

   log.msg("test message 2 using log.msg(). testing return character \\n in log.msg();\nsection of message after a return character.");

   log.msg("testing status.pass();");

   status.pass();

   log.msg("testing status.fail();");

   status.fail();

   log.msg("testing status.pass(\"string\");");

   status.pass("hey this is the message from the passing status!");

   log.msg("testing status.fail(\"string\");");
   
   status.fail("hey this is the message from the failing status!");

   log.msg("testing status.fatal();");

   status.fatal();

   log.msg("testing status.is_pass()");

   if (status.is_pass()) {
      log.msg("status object in in passing condition");
   }
   else {
      log.msg("status object is not in passing condition");
   }

   log.msg("testing return value from status.pass(\"message\");");

   int st = status.pass("setting the status object to pass");

   if (st == 1) {
      log.msg("stat.pass returned 1!");
   }
   else {
      log.msg("stat.pass didn't return no 1");
   }

   log.msg("testing newline character \\n in stat.fail(\"message\");");

   status.fail("this is the message before the newline\nthis is the message after the newline");

   log.msg("testing newline character \\n in stat.pass(\"message\");");

   status.pass("message message message\nmessage message message\nthis is the message bro");

   log_mgr log_2;
   log_2.msg("testing log.msg() using default configuration\nyup. testing that.");

   log.msg("testing test_subroutine");

   int tsub_return = test_subroutine();

   if (tsub_return == 1) {
      log.msg("test_subroutine returned 1!");
   }
   else {
      log.msg("test_subroutine didn't return no 1");
      status.fail("test_subroutine did not pass");
   }  

}
