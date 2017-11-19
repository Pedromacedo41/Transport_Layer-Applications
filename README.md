# Transport_Layer-Web-Chat-Applications

C++ codes implements UDP and TCP tranport layer protocols with sockets and Threads to implement 
multiple independent messages communication. The C++ librarios work **on linux**


## Compilation trought terminal command on linux systems

````
    $ g++ -std=c++11 UDPThread.cpp -o udp -pthread
    $ ./udp
    
````

The main code is UDPThread.cpp ,wheres the others are antecessors codes implementing funcionalities and TCP 
communication. The application works fine in localhost terminals. 
The application opens two fixed ports to stablish the communication process, 1234 nd 1235


