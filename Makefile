CWD=`pwd -P`
CC=g++
CSTDFL=-std=c++11

all: conf log_mgr stat_log test

conf:
	$(CC) $(CSTDFL) conf.hpp

log_mgr:
	$(CC) $(CSTDFL) log_mgr.hpp

stat_log:
	$(CC) $(CSTDFL) stat_log.hpp

test:
	$(CC) $(CSTDFL) cls_test.cpp -o stat_test
	./stat_test | ./add_color.pl

clean:
	rm -f *.gch
	rm -f *.log

