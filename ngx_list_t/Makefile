CXX = gcc
CXXFLAGS += -g -pg -Wall -Wextra

NGX_ROOT = /home/lojunren/Src/Nginx

TARGETS = ngx_list_t_test
TARGETS_C_FILE = $(TARGETS).c

CLEANUP = rm -f $(TARGETS) *.o gmon.out

all: $(TARGETS)

clean:
	$(CLEANUP)

CORE_INCS = -I. \
	-I ../ngx_dump \
	-I$(NGX_ROOT)/objs \
	-I$(NGX_ROOT)/src/core \
	-I$(NGX_ROOT)/src/event	\
	-I$(NGX_ROOT)/src/event/modules	\
	-I$(NGX_ROOT)/src/os/unix	\

NGX_DUMP = ../ngx_dump/ngx_dump.o
NGX_LIST = $(NGX_ROOT)/objs/src/core/ngx_list.o
NGX_PALLOC = $(NGX_ROOT)/objs/src/core/ngx_palloc.o
NGX_STRING = $(NGX_ROOT)/objs/src/core/ngx_string.o
NGX_ALLOC = $(NGX_ROOT)/objs/src/os/unix/ngx_alloc.o

$(TARGETS): $(TARGETS_C_FILE)
	$(CXX) $(CXXFLAGS) $(NGX_DUMP) $(NGX_LIST) $(CORE_INCS) $(NGX_PALLOC) $(NGX_STRING) $(NGX_ALLOC) $^ -o $@
