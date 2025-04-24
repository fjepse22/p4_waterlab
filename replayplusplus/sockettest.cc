

// Formål, at finde ud af om vi kan modtage alle pakker fra et interface og sende det til et andet.

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <iostream>
#include <string>


// C++ program to show the example of server application in
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

//https://unix.stackexchange.com/questions/648718/force-programs-bind-to-an-interface-not-ip-address
// to bind interface to spefici stuckt
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>

// F. For flotte parametre
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

string test;

class Interface{

    public:
    string inferface_name;
    int ServerSocket; 

    struct ifreq ifr; //F: ifr = interface reference

    sockaddr serverAdress;


    Interface(const string name){
        inferface_name = name;
        ServerSocket = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)); //htons(EHT_P_ALL) means all protocols are recieved.

        if (ServerSocket < 0) { // F: if socket is not made correctly
            perror("socket");
            return;
        }

        // F: to convert input of interfacename to a chararray, as it can not use string to input the name arrg
        // https://www.geeksforgeeks.org/convert-string-char-array-cpp/
        int name_length = name.length();
      

        //char name_char[name_length+1];
        char name_char[16];
        strcpy(name_char,name.c_str());
        strcpy(ifr.ifr_name,name_char); // F: Dette overfører inferfacename til struct ifr.
    
        // F: binds the socket to a spefiic interface
        // https://unix.stackexchange.com/questions/648718/force-programs-bind-to-an-interface-not-ip-address
        if (setsockopt(ServerSocket,SOL_SOCKET,SO_BINDTODEVICE,&ifr,sizeof(ifr))<0){
            perror("setsockopt");
            return;
        }

    }

    int send_packet(int packet){
        return packet;
    }


    int sock_listen(){ /*To listen for packets and then recive them*/
        
        listen(ServerSocket,5);

        int connection = accept(ServerSocket,nullptr,nullptr);

        // recieving data
        char buffer[1024] = { 0 };
        recv(connection, buffer, sizeof(buffer), 0);

        // this needs to be changed later as it is supposed to send the package to a que
        cout << "Message from client: " << buffer
              << endl;

        close(ServerSocket);

        return 0;
    }

};

int main(int argc, char* argv[]){

    string interface_name_a;
    string interface_name_b;
    bool evilmode = false; //default behaivor is invisible, unless input is (--evilmode "true")

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--interfacenames" && i + 2 < argc) {
            interface_name_a = argv[++i]; // first interfacename
            interface_name_b = argv[i+2]; // second interfacename
        } else if (arg == "--evilmode" && i + 1 < argc && (strcmp (argv[++i],"true") ==0)) { // if input is "true" chance evilmode to true, is to be implemented
            evilmode = true;
        }
    }

    cout << interface_name_a <<"\n";
    cout << interface_name_b <<"\n";
    cout << evilmode <<" n\"";

    // Further implementation would go here
    Interface interface_a(interface_name_a);
    
    interface_a.sock_listen();
    

    
    return 0;

    

}
