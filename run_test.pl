#!/usr/bin/perl

system("g++ -std=c++11 conf.hpp");

system("g++ -std=c++11 log_mgr.hpp");
system("g++ -std=c++11 stat_log.hpp");
system("g++ -std=c++11 stat_test.cpp -o stat_test");
system("./stat_test | ./add_color.pl");
