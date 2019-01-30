CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++0x

OBJS =		roman2int.o main.o

TESTOBJS =	roman2int.o test.o

LIBS =

TARGET =	roman2int

TESTTARGET = test

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

$(TESTTARGET):	$(TESTOBJS)
	$(CXX) -o $(TESTTARGET) $(TESTOBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TESTOBJS) $(TESTTARGET)
