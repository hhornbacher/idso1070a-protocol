#include "USBConnector.h"

USBConnector::USBConnector(const char *device)
{
    strncpy(this->device, device, 256);
}

USBConnector::~USBConnector()
{
    if (handle < 0)
        close(handle);
}

void USBConnector::start()
{
    termios tty;
    handle = open(device, O_RDWR | O_NOCTTY | O_SYNC);
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(handle, &tty) != 0)
    {
        printf("error %d from tcgetattr", errno);
    }

    cfsetospeed(&tty, USB_SERIAL_SPEED);
    cfsetispeed(&tty, USB_SERIAL_SPEED);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK; // disable break processing
    tty.c_lflag = 0;        // no signaling chars, no echo,
                            // no canonical processing
    tty.c_oflag = 0;        // no remapping, no delays
    tty.c_cc[VMIN] = 0;     // read doesn't block
    tty.c_cc[VTIME] = 5;    // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);   // ignore modem controls,
                                       // enable reading
    tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_cc[VMIN] = 0;  // Set non-blocking
    tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

    if (tcsetattr(handle, TCSANOW, &tty) != 0)
    {
        printf("error %d from tcsetattr", errno);
    }
}

void USBConnector::stop()
{
    close(handle);
    handle = -1;
}

void USBConnector::transmit(uint8_t *data, size_t length)
{
    write(handle, data, length);
}

size_t USBConnector::receive()
{
    if (packetBufferLength < PACKETBUFFER_LENGTH)
    {
        int result = read(handle, &packetBuffer[packetBufferLength], PACKETBUFFER_LENGTH - packetBufferLength);
        if (result > 0)
            packetBufferLength += result;
    }
    return packetBufferLength;
}