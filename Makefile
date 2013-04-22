export JAVA_HOME=/home/panthera/jdk1.6.0_43

.PHONY: all
all: Producer.class AsyncConsumer.class libmetaq_clib.so sample.out


Producer.class : Producer.java
	javac -cp ./lib/metamorphosis-server-wrapper-1.4.4.jar:./lib/metamorphosis-client-1.4.4.jar:./lib/metamorphosis-commons-1.4.4.jar Producer.java
		
AsyncConsumer.class : AsyncConsumer.java
	javac -cp ./lib/metamorphosis-server-wrapper-1.4.4.jar:./lib/metamorphosis-client-1.4.4.jar:./lib/metamorphosis-commons-1.4.4.jar AsyncConsumer.java

libmetaq_clib.so : metaq_clib.c 
	gcc -fPIC  -I $(JAVA_HOME)/include/  -I $(JAVA_HOME)/include/linux/ -shared -o libmetaq_clib.so metaq_clib.c 
					  
sample.out : sample.c libmetaq_clib.so
	gcc -I $(JAVA_HOME)/include/  -I $(JAVA_HOME)/include/linux/  -L . -L $(JAVA_HOME)/jre/lib/amd64/server/ -ljvm  -lmetaq_clib -o sample.out  sample.c

clean : 
	rm -rf *.so *.class *.out

