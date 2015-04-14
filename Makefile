CC= g++
CFLAGS = `pkg-config --cflags opencv`
#ifdef __arm__
	LIBS = `pkg-config --libs opencv` -I/usr/local/include -lraspicam -lraspicam_cv
#else
	LIBS = `pkg-config --libs opencv` -I/usr/local/include 
#endif	

% : %.cpp
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<

clean:
	rm -rf *~*
