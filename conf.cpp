#include "conf.hpp"

// global static pointer. Ensures single instance of the class exists.
conf* conf::m_pInst = NULL;
int* conf::do_update = 0;
std::map<std::string, std::string>* conf::settings = NULL;
char* conf::config_file_path = NULL;

conf* conf::inst() {
   if (!m_pInst) {
      m_pInst   = new conf;
      do_update = new int(1);
      settings  = new std::map<std::string, std::string>;

#ifndef _WIN32
      std::string tmppath = getenv("HOME");
      tmppath += "/.conf_generic.conf";

      m_pInst->set_config_file_path(tmppath);
#else
      std::string tmppath = getenv("APPDATA");
      tmppath += "\\conf_generic.conf";
      m_pInst->set_config_file_path(tmppath);
#endif

      m_pInst->update();
   }

   return m_pInst;
}

conf* conf::inst(std::string const& new_config_path) {
   if (!m_pInst) {
      m_pInst   = new conf;
      do_update = new int(1);
      settings  = new std::map<std::string, std::string>;
      m_pInst->set_config_file_path(new_config_path);

      m_pInst->update();
   }
   else {
      m_pInst->set_config_file_path(new_config_path);
   }

   return m_pInst;
}

bool conf::set_config_file_path(std::string const& new_config_path) {

   config_file_path = (char *)malloc(new_config_path.size());
   memcpy( (void *) config_file_path, (void *) new_config_path.c_str(), new_config_path.size());
   config_file_path[new_config_path.size()] = '\0';

   return 0;
}

bool conf::update() {

   if (do_update) {
      // open config file
      // read line by line
      // grab variables from keys
      // store in memory

      //char* testing = config_file_path;

//    std::cout << "config_file_path: [" << config_file_path << "]\n";

      std::ifstream fh (config_file_path, std::ios::in);
      if (fh.is_open()) {
         while (fh.peek() != EOF) {
            std::string line;
            std::getline(fh, line);

            unsigned int found = line.find("//");
            if (found != std::string::npos) {
               if (found == 0) {
                  continue;
               }
               line = line.substr(0, found);
            }

//          std::cout << "found: [" << found << "]\nline: [" << line << "]\n";

            if (line.size() < 5) {
               continue;
            }

            found = line.find(" = ");
            if ((found != std::string::npos) && (found != 0)) {
               settings->operator[](line.substr(0, found)) = line.substr(found+3);
            }
         }
      }
      else {
         std::cerr << "\n\nERROR COULD NOT OPEN CONFIG FILE: [";
         std::cerr << config_file_path << "]\n\n";
         abort();
      }

      return 1;
   }
   //std::vector<std::string, std::string> newvec();
   //newvec[std::string("do_update")] = "no";
   return 0;
}

bool conf::defined(std::string const& key) {
   //std::map<std::string, std::string>::iterator it;
   //it = settings->find(key);

   if (settings->find(key) == settings->end()) {
      return 0;
   }
   else {
      return 1;
   }
}

/** conf::get
             bool get (const string &key, value_type &copy_val)
      const char* get (const string &key)
              int get (const string &key, int val)

   synopsis
      gives a pointer or a copy of the value associated with the given key.

*/
bool conf::get(std::string const& key, std::string& val) {
   if (defined(key)) {
      val.assign(settings->operator[](key));
      return 1;
   }
   else {
      return 0;
   }
}

const char* conf::get(std::string const& key) {
   return settings->operator[](key).c_str();
}

int conf::get(std::string const& key, int &val) {

   val = atoi(settings->operator[](key).c_str());
   return atoi(settings->operator[](key).c_str());
}

bool conf::set(std::string const& key, std::string const& val) {

   // THIS ISSUE was caused by classes calling conf* config;
   //                               instead of conf* config = conf::inst();
   //
   // program would segfault at setting->operator[](key)

   //std::cout << "\nset " << key << " to " << val << "\n";

   //std::cout << "key at: " << &key;
   //std::cout << "\nval at: " << &val;

   //std::string * v = new std::string;
   //v->assign(val);
   //std::string v = val.c_str();

   //std::cout << "\n  v at: " << &v << std::endl;

   //settings->operator[](key) = (std::string*) ::operator new(sizeof(std::string));

   //std::cout << "map at: " << &settings << std::endl;
   //std::cout << "mapkey at: " << &settings->operator[](key) << std::endl;
   
   //settings->erase(key);
   settings->operator[](key) = val;
   //new (settings->operator[](key)) std::string;

   //settings->insert(std::pair<std::string,std::string>(key, val));

   return 0;
}
