CXXFLAGS =	-std=c++11 -O2 -g -Wall
.PHONY:	GetTimeTest 
OBJS_2 =	GetTimeTest.o
LIBS = 

TARGET_2 =	GetTimeTest

$(TARGET_2):	$(OBJS_2)
	$(CXX) -o $(TARGET_2) $(OBJS_2) $(LIBS)
	
all:	$(TARGET_2)

info:	$(TARGET_2)
	otool -L $(TARGET_2)
	pkgutil --file-info /usr/lib/libc++.1.dylib 
	$(CXX) -v

clean:
	rm -f $(OBJS_2) $(TARGET_2)
