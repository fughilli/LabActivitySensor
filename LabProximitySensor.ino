#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>
#include "stdlib.h"

byte mac[] =
{
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

void* get_insert_data(void)
{
    char* insert_data = (char*)malloc(10 * sizeof(char));
    strcpy(insert_data, "HELLO");
    return (void*) insert_data;
}

char* keyw_s_r(const char* buffer, size_t buf_size)
{
    char* buildBuffer = (char*) malloc(buf_size * sizeof(char));
    size_t buildBufferSize = buf_size * sizeof(char);
    for(int i = 0; i < NUM_KEYWORDS; i++)
    {
        char* occurence = strstr(buffer, keywords[i]);
        if(occurence != NULL)
        {
            size_t oldBuildBufferSize = buildBufferSize;
            buildBufferSize +=
            buildBuffer = (char*)realloc((void*) buildBuffer, )
        }
    }
}

#define NUM_KEYWORDS 1

char* keywords[NUM_KEYWORDS] =
{
    "#INSERT_DATA_HERE"
};

(void*) *keyfuncs[NUM_KEYWORDS](void) =
{
    get_insert_data
};

IPAddress ip(192,168,1,116);

EthernetServer server(80);

File logFile, webpageFile;

void setup()
{
    Serial.begin(115200);

    pinMode(8, INPUT);

    //Serial.println("Attempting DHCP startup...");
    Ethernet.begin(mac, ip);
    server.begin();
    Serial.print("Server started at ");
    Serial.print(Ethernet.localIP());
    Serial.print(" on port ");
    Serial.println(server.localPort());
    if(!SD.begin(4))
    {
        Serial.println("Could not initialize SD card!");
    }
    logFile = SD.open("log.txt", FILE_WRITE);
    logFile.println("Hello there!");
    logFile.close();
}

void loop()
{
    EthernetClient client = server.available();
    if(client)
    {
        boolean currentLineIsBlank = true;
        while(client.connected())
        {
            if(client.available())
            {
                char c = client.read();
                Serial.write(c);

                if(c == '\n' && currentLineIsBlank)
                {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println("Refresh: 0.5");
                    client.println();
//                    client.println("<!DOCTYPE HTML>");
//                    client.println("<html>");
//
//                    client.print("Digital pin 8: ");
//
//                    client.println((digitalRead(8))?("HIGH"):("LOW"));
//
//                    client.println("</html>");

                    break;
                }

                if(c=='\n')
                {
                    currentLineIsBlank = true;
                }

                else if (c != '\r')
                {
                    currentLineIsBlank = false;
                }
            }
        }

        delay(1);

        client.stop();
    }
}
