CXX = gcc
CXXFLAGS += -g -pg -Wall -Wextra

NGX_ROOT = /home/lojunren/src/nginx

TARGETS = ngx_dump
TARGETS_C_FILE = $(TARGETS).c

CLEANUP = rm -f $(TARGETS) *.o

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

$(TARGETS): $(TARGETS_C_FILE)
	$(CXX) $(CXXFLAGS) $(CORE_INCS) $(NGX_ARRAY) $(NGX_LIST) -c $^
