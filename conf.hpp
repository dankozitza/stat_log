#ifndef _CONF
#define _CONF

// NAME
//
//    conf
//
// SYNOPSIS
//
//    Configuration tool to be used by applications.
//
// DESCRIPTION
//
//    Reads lines from file to place strings into a map. Each line of the
//    config file is a key value pair. line syntax in Perl regular expressions 
//    would be if ($line =~ /^(.*?)\s\=\s(.*)$/) { $key = $1; $value = $2; }.
//
//    Default config file location is in the HOME env variable on *nix and the
//    APPDATA env variable on windows. File will be named .conf_generic.conf on
//    *nix and conf_generic.conf on windows. It is strongly suggested that you
//    set your own config file location per application.
//  
//  NOTES
//
//    Conf objects cannot be initialized with:
//
//       conf* config;
//
//    conf uses a single instance for storing the settings map. use:
//
//       conf* config = conf::inst();
//

//#include <fstream>
//#include <iostream>
#include <string.h>
//#include <map>
#include <stdlib.h>

class conf {
   public:
      static conf* inst();
      static conf* inst(std::string const& new_config_path);
      bool set_config_file_path(std::string const& new_config_path);
      bool update();
      bool defined(std::string const& key);
      bool get(std::string const& key, std::string& val);
      const char* get(std::string const& key);
      int get(std::string const& key, int val);
      bool set(std::string const& key, std::string const& val);

   private:
      conf(){};
      conf(conf const&){};
      //conf& operator=(conf const&){};

      static conf* m_pInst;

      static int* do_update;
      static std::map<std::string, std::string>* settings;
      static char* config_file_path;
};

#include "conf.cpp"
#endif
