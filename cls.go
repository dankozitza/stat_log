package main

// // $cgo CXX: g++
// // #cgo CPPFLAGS: -std=c++11
// #include </xfs/jklkbum/projects/stat_log/conf.hpp>
//
// typedef conf (*confFunc) ();
//
// conf bridge_conf_func(confFunc f) {
//      return f();
// }
//
// conf* confInst() {
//    return conf::inst();
// }
import "C"

func main() {
   conf := make(C.conf("testfile.log"), 1)
}
