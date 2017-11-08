// Reza Naeemi

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

const int BUFFSIZE = 1500;
const int NUM_CONNECTIONS = 5;

enum myPartType 
{

  CLIENT, 
  SERVER
  
} myPart;

bool verbose = false;
bool stayAlive = false;

int main(int argc, char *argv[])
{

    if (argc == 2)
    {
        myPart = SERVER;
        if (verbose)
        {
            cout << "Running as server." << endl;
        }
    }
    else if (argc == 3)
    {
        myPart = CLIENT;
        if (verbose)
        {
            cout << "Running as client." << endl;
        }
    }
    else if (argc < 2 || argc > 3)
    {
        cerr << "usage:" << endl;
        cerr << "server invocation: ./hw3 ipPort" << endl;
        cerr << "client invocation: ./hw3 ipPort ipName" << endl;
        return -1;
    }
    
    
    // Validate port
    if (atoi(argv[1]) < 1024 || atoi(argv[1]) > 65536)
    {
        cerr << "Cannot bind the local address to the server socket." << endl;
        return -1;
    }
    
    // Set parameters
    int serverPort = atoi(argv[1]);
    const char *server = argv[2];
    
    // Allocate the data buffer
    char databuf[BUFFSIZE];
    bzero(databuf, BUFFSIZE);

    // Client code
    if (myPart == CLIENT)
    {   
        // Get Hostent structure to communicate with the server.
        struct hostent *host = gethostbyname(server);
        if (host == NULL)
        {
            cerr << "Cannot find hostname." << endl;
            return -1;
        }
        
        // Build the sending socket address of the client.
        sockaddr_in sendSocketAddress;
        bzero((char *)&sendSocketAddress, sizeof(sendSocketAddress));
        sendSocketAddress.sin_family = AF_INET;     // Address Family: Internet
        sendSocketAddress.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*) (*host->h_addr_list)));
        sendSocketAddress.sin_port = htons(serverPort);
        
        // Open the TCP socket.
        int clientSD = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSD < 0)
        {
            cerr << "Could not open socket." << endl;
            close(clientSD);
            return -1;
        }
        
        // Connect this TCP socket with the server
        int returnCode = connect(clientSD, (sockaddr *)&sendSocketAddress, sizeof(sendSocketAddress));
        if (returnCode < 0) // If the returnCode is negative, this will indicates failure
        {
            cerr << "Connection failed." << endl;
            close(clientSD);
            return -1;
        }
        
        // Perform actions required to mimick the professor's provided hw3 executable
        // from the perspective of the active participant.
        // Send 10 bytes and then receive an acknowledgement.
        int bytesWritten = write(clientSD, databuf, 10);
        if (verbose)
        {
            cout << "bytesWritten: " << bytesWritten << endl;            
        }
        // Receive 10 bytes and then send an acknowledgement.
        int bytesRead = read(clientSD, databuf, BUFFSIZE);
        if (verbose)
        {
            cout << "bytesRead: " << bytesRead << endl;         
        }
        // Send 1450 bytes and then receive an acknowledgement.
        bytesWritten = write(clientSD, databuf, 1450);
        if (verbose)
        {
            cout << "bytesWritten: " << bytesWritten << endl;            
        }
        // Send a FIN and then terminate the connection.
        shutdown(clientSD, SHUT_RDWR);
        close(clientSD);
    }
    
    // Code for the Server functionality
    if (myPart == SERVER)
    {
        // Build the receiving socket address for any of the available server interfaces.
        sockaddr_in acceptSocketAddress;
        bzero((char *)&acceptSocketAddress, sizeof(acceptSocketAddress));
        acceptSocketAddress.sin_family = AF_INET;   // Address Family:  Internet
        acceptSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        acceptSocketAddress.sin_port = htons(serverPort);
        
        // Open the TCP socket.
        int serverSD = socket(AF_INET, SOCK_STREAM, 0);
        const int on = 1;
        setsockopt(serverSD, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(int));
        
        // Bind the TCP socket.
        int returnCode = bind(serverSD, (sockaddr *)&acceptSocketAddress, sizeof(acceptSocketAddress));
        if (returnCode < 0) // If the returnCode is negative, this will indicates failure
        {
            cerr << "Bind failed." << endl;
            close(serverSD);
            return -1;
        }
        
        // Listen for a connection
        listen(serverSD, NUM_CONNECTIONS);
        
        do
        {
            // Wait for a new client connection
            sockaddr_in newSockAddr;
            socklen_t newSockAddrSize = sizeof(newSockAddr);
            int newSD = accept(serverSD, (sockaddr *) &newSockAddr, &newSockAddrSize);
            
            // Start a copy of a multithreaded process thread for every new connection.
            if (fork() == 0)
            {
                close(serverSD);
                
                // Perform actions required to mimick the professor's provided hw3 executable
                // from the perspective of the passive participant.
                // Receive 10 bytes then send an acknowledgement.
                read(newSD, databuf, BUFFSIZE);
                // Send 10 bytes then receive an acknowledgement.
                write(newSD, databuf, 10);
                // Send a FIN, but still read on this connection.
                shutdown(newSD, SHUT_WR);
                // Receive 1450 bytes and then send an acknowledgement.
                read(newSD, databuf, BUFFSIZE);
                // Disconnect the TCP session.
                close(newSD);
                exit(0);          
            }
            else
            {
                close(newSD);
            }
        } while (stayAlive);
        
        close(serverSD);
    }
    
    return 0;
}