#include <iostream>            
#include <cstdlib>             
#include <iostream>             
#include <cstdlib>              
#include <sys/types.h>         
#include <sys/socket.h>         
#include <arpa/inet.h>         
#include <unistd.h>             
#include <netinet/in.h>
#include <cstring>
#include "config.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    if (argc != 3)      //TODO set fixed address and port
    {
        cerr << "Usage: " << argv[0] << " <Server> <Server Port>\n";
        exit(1);
    }

    unsigned short servPort = atoi(argv[2]);
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in saddr;

    memset(&saddr,0, sizeof(saddr));
    inet_aton(argv[1],&(saddr.sin_addr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(servPort);

    int jpegqual =  ENCODE_QUALITY; // Compression Parameter

    Mat frame, send;
    vector < uchar > encoded;
    VideoCapture cap(0); // Grab the camera
    if (!cap.isOpened()) {
        cerr << "OpenCV Failed to open camera";
        exit(1);
    }

    clock_t last_cycle = clock();

    while (1) {
        cap >> frame;
        if(frame.size().width==0)continue;//simple integrity check; skip erroneous data...
        resize(frame, send, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_LINEAR);
        vector < int > compression_params;
        compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
        compression_params.push_back(jpegqual);

        imencode(".jpg", send, encoded, compression_params);
        int total_pack = 1 + (encoded.size() - 1) / PACK_SIZE;

        if (sendto(sock,&total_pack, sizeof(int), 0, (struct sockaddr*) &saddr,sizeof(struct sockaddr_in)) != sizeof(int))     //send n. of packets necessary to send the frame
        {
            cerr << "sendto failed" << endl;
            exit(1);
        }

        for (int i = 0; i < total_pack; i++)
            if (sendto(sock,  & encoded[i * PACK_SIZE], PACK_SIZE, 0,  (struct sockaddr*) &saddr,sizeof(struct sockaddr_in))!=PACK_SIZE)        //send frame data
            {
                cerr << "sendto failed" << endl;
                exit(1);
            }

        clock_t next_cycle = clock();
        double duration = (next_cycle - last_cycle) / (double) CLOCKS_PER_SEC;
        cout << "\teffective FPS:" << (1 / duration) << " \tkbps:" << (PACK_SIZE * total_pack / duration / 1024 * 8) << endl;

        cout << next_cycle - last_cycle;
        last_cycle = next_cycle;
    }

    close(sock);
    return 0;
    }
