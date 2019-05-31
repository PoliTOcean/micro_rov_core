#include <iostream>
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include "config.h"
#include "opencv2/opencv.hpp"

#define BUF_LEN 65540 // Larger than maximum UDP packet size

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    int sockDesc;

    if (argc != 2) { // Test for correct number of parameters       //TODO set fixed address and port
        cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
        exit(1);
    }

    unsigned short servPort = atoi(argv[1]); // First arg:  local port

    namedWindow("recv", CV_WINDOW_AUTOSIZE);

    sockDesc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(servPort);

    if (bind(sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0)
    {
        fprintf(stderr, "Error in binding");
        exit(1);
    }

    char buffer[BUF_LEN]; // Buffer for echo string
    int recvMsgSize; // Size of received message
    string sourceAddress; // Address of datagram source
    unsigned short sourcePort; // Port of datagram source
    sockaddr_in clntAddr;
    socklen_t addrLen = sizeof(clntAddr);

    clock_t last_cycle = clock();

    while(1)
    {
        // Block until receive message from a client
        do {

            if ((recvMsgSize = recvfrom(sockDesc, buffer, BUF_LEN, 0,  (sockaddr *) &clntAddr, (socklen_t *) &addrLen)) < 0)    //receive total n. of packets per frame
            {
                cerr << "Error in recvfrom" << endl;
                exit(1);
            }

        } while (recvMsgSize > sizeof(int));
        int total_pack = ((int * ) buffer)[0];

        cout << "\texpecting length of packs:" << total_pack;

        char * longbuf = new char[PACK_SIZE * total_pack];
        for (int i = 0; i < total_pack; i++) {
            if ((recvMsgSize = recvfrom(sockDesc, buffer, BUF_LEN, 0,  (sockaddr *) &clntAddr, (socklen_t *) &addrLen)) < 0)    //receive frame data (4096 bytes - max UDP lenght packet - at time)
            {
                cerr << "Error in recvfrom" << endl;
                exit(1);
            }
            else if (recvMsgSize != PACK_SIZE) {
                cerr << "Received unexpected size pack:" << recvMsgSize << endl;
                continue;
            }
            memcpy( & longbuf[i * PACK_SIZE], buffer, PACK_SIZE);
        }

        sourceAddress = inet_ntoa(clntAddr.sin_addr);
        sourcePort = ntohs(clntAddr.sin_port);

        cout << "\tReceived packet from " << sourceAddress << ":" << sourcePort;

        Mat rawData = Mat(1, PACK_SIZE * total_pack, CV_8UC1, longbuf);
        Mat frame = imdecode(rawData, CV_LOAD_IMAGE_COLOR);
        if (frame.size().width == 0) {
            cerr << "decode failure!" << endl;
            continue;
        }
        imshow("recv", frame);
        free(longbuf);

        waitKey(1);
        clock_t next_cycle = clock();
        double duration = (next_cycle - last_cycle) / (double) CLOCKS_PER_SEC;
        cout << "\teffective FPS:" << (1 / duration) << " \tkbps:" << (PACK_SIZE * total_pack / duration / 1024 * 8) << "\t" << endl;

        cout << next_cycle - last_cycle;
        last_cycle = next_cycle;
    }

    close(sockDesc);

    return 0;

}
