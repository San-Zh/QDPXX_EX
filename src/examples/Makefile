Config = /home/Documents/Work/02_LQCDrefs/Chroma/chroma/cpu_double/bin/chroma-config
# Config = /home/Documents/Work/02_LQCDrefs/Chroma/qdpxx/double/bin/qdp++-config

INCLUDE = 
CXX = $(shell ${Config} --cxx)
CXX_FLAGS = $(shell ${Config} --cxxflags)
LD_FLAGS  = $(shell ${Config} --ldflags)
LIBS      = $(shell ${Config} --libs)


%.o: %.cpp
	${CXX} ${CXX_FLAGS} -o $@ -c $<

%.o: %.cc
	${CXX} ${CXX_FLAGS} -o $@ -c $<

io_prop.bin: io_prop.cpp
	${CXX} ${CXX_FLAGS} -Wl,-rpath=./ -o $@  $< ${LD_FLAGS} ${LIBS}

t_qio.bin: t_qio.cpp
	${CXX} ${CXX_FLAGS} -Wl,-rpath=./ -o $@  $< ${LD_FLAGS} ${LIBS}

clean:
	rm *.o *.bin -rf