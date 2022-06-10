#include "MicroBit.h"
#include "CodalHeapAllocator.h"
#include <sstream>

#define PACKET_ID_BYTES 2
#define FLAGS_BYTES 2
#define RECEIVER_ADDRESS_BYTES 8
#define SENDER_ADDRESS_BYTES 8
#define USER_DATA_BYTES MICROBIT_RADIO_MAX_PACKET_SIZE - (PACKET_ID_BYTES + SENDER_ADDRESS_BYTES + RECEIVER_ADDRESS_BYTES + FLAGS_BYTES) - 3
#define SERVER_ADDRESS 7349411279349683933

#define STD 1
#define SYN 2
#define SYN_RES 4

// TODO: address 0
// TODO: proper synchronise method

MicroBit uBit;
uint32_t messageCounter = 0;
PacketBuffer b(USER_DATA_BYTES);
bool isServer = false;
bool hasReceived = false;
uint64_t localAddress;

const int timeout = 2000;

// From: https://stackoverflow.com/questions/12240299/convert-bytes-to-int-uint-in-c
uint16_t bytesToUInt16(uint8_t *bytes)
{
    return bytes[0] + ((uint32_t)bytes[1] << 8);
}

uint32_t bytesToUInt32(uint8_t *bytes)
{
    return bytes[0] + ((uint32_t)bytes[1] << 8) + ((uint32_t)bytes[2] << 16) + ((uint32_t)bytes[3] << 24);
}

uint64_t bytesToUInt64(uint8_t *bytes)
{
        return bytes[0] + ((uint64_t)bytes[1] << 8) + ((uint64_t)bytes[2] << 16) +
           ((uint64_t)bytes[3] << 24) + ((uint64_t)bytes[4] << 32) + ((uint64_t)bytes[5] << 40) +
           ((uint64_t)bytes[6] << 48) + ((uint64_t)bytes[7] << 56);
}

PacketBuffer getUserData(uint8_t *buf)
{
    return {buf, USER_DATA_BYTES};
}

std::string timeToString()
{
    std::ostringstream ss;
    ss << system_timer_current_time_us();
    return ss.str();
}

void sendPacket(uint64_t targetId, uint8_t *payload, bool isForward=true, uint16_t flags=STD)
{
    PacketBuffer buffer(MICROBIT_RADIO_MAX_PACKET_SIZE);
    uint8_t *buf = buffer.getBytes();
    memcpy(buf, &messageCounter, PACKET_ID_BYTES);
    buf += PACKET_ID_BYTES;
    memcpy(buf, &flags, FLAGS_BYTES);
    buf += FLAGS_BYTES;
    memcpy(buf, &targetId, RECEIVER_ADDRESS_BYTES);
    buf += RECEIVER_ADDRESS_BYTES;
    memcpy(buf, &localAddress, SENDER_ADDRESS_BYTES);
    buf += SENDER_ADDRESS_BYTES;
    memcpy(buf, payload, USER_DATA_BYTES);

    uBit.radio.datagram.send(buffer);
    if (!isForward)
    {
        system_timer_event_after(timeout, DEVICE_ID_RADIO, 100);
        messageCounter++;
        DMESG("%s Sent %d bytes", timeToString().c_str(), USER_DATA_BYTES);
    }

}

bool checkData(PacketBuffer buffer, uint8_t &bytesCorrect)
{
    uint8_t *ourData = b.getBytes();
    uint8_t *incomingData = buffer.getBytes();

    bytesCorrect = 0;
    bool valid = true;

    for (int i = 0; i < USER_DATA_BYTES; i++)
    {
        if (ourData[i] != incomingData[i])
            valid =  false;
        else
            bytesCorrect++;
    }

    return valid;
}

void onRecv(MicroBitEvent e)
{
    //DMESG("onRecv");
    PacketBuffer buffer = uBit.radio.datagram.recv();
    uint8_t *buf = buffer.getBytes();
    uint16_t packetId = bytesToUInt16(buf);
    buf += PACKET_ID_BYTES;
    uint16_t flags = bytesToUInt16(buf);
    buf += FLAGS_BYTES;
    uint64_t receiverAddress = bytesToUInt64(buf);
    buf += RECEIVER_ADDRESS_BYTES;
    uint64_t senderAddress = bytesToUInt64(buf);
    buf += SENDER_ADDRESS_BYTES;
    PacketBuffer userData = getUserData(buf);

    //DMESG("Packet id: %d Message counter: %d", packetId, messageCounter);

    if (senderAddress == SERVER_ADDRESS)
        //("Received from server");

    if (receiverAddress == uBit.getSerialNumber())
        //DMESG("For local processing");

    if ((flags & SYN) == SYN)
    {
        DMESG("SYN");
        // We have received a synchronisation packet
        sendPacket(senderAddress, userData.getBytes(), flags=SYN_RES);
        return;
    }
    else if ((flags & SYN_RES) == SYN_RES)
    {
        DMESG("SYN-RES");
        if (receiverAddress == localAddress)
        {
            if (packetId > messageCounter)
                messageCounter = packetId;
        }

        return;
    }

    // If the packet is not a standard user packet by this point
    // We can ignore it
    if ((flags & STD) != STD)
        return;

    if (packetId == messageCounter)
    {
        // We haven't seen this packet before, relay it
        sendPacket(receiverAddress, userData.getBytes());
        messageCounter++;
    }
    else if(packetId > messageCounter)
    {
        // We are out of sync
        messageCounter = packetId;
        sendPacket(receiverAddress, userData.getBytes());
        messageCounter++;
        // Relay it?
    }
    else
    {
        // We have seen the packet before
        return;
    }

    if (receiverAddress == uBit.getSerialNumber() || receiverAddress == 0)
    {
        if (isServer)
        {
            DMESG("Server processing - Message counter: %d", messageCounter);
            // Create new packet here
            // Use the same data that we received
            // Change the device id to that of the client
            // Might hve to hardcode the device ids
            sendPacket(senderAddress, userData.getBytes(), false);
        }
        else
        {
            hasReceived = true;
            //DMESG("Client processing...");
            uint8_t bytesCorrect = 0;
            // This is our packet, this is the client so
            // Compare the user data to what we sent.
            // It should be the same
            // Print the time along with the bytes received and the bytes expected
            // Because the userdata is a fixed size and the data won't change
            // We don't need to include the expected size in the actual packet
            bool isValid = checkData(userData, bytesCorrect);

            if (isValid)
            {
                DMESG("%s Received and compared %d bytes, all ok", timeToString().c_str(), bytesCorrect);
            }
            else
            {
                DMESG("%s Received and compared %d bytes, data mismatch", timeToString().c_str(), bytesCorrect);
            }
        }
    }
}

void setUserData()
{
    for (int i = 0; i < USER_DATA_BYTES; i++)
    {
        b.setByte(i, i);
        // DMESG("Setting byte location [%d] to %d", i, b.getByte(i));
    }
}

// TODO: Timeout
void timeoutEvent(MicroBitEvent e)
{
    if (isServer)
        return;

    DMESG("TIMEOUT");
    //DMESG("%s Received and compared %d bytes, data mismatch", timeToString().c_str(), 0);
    uint8_t *bp = b.getBytes();
    sendPacket(SERVER_ADDRESS, bp, false);
    // system_timer_event_after(timeout, DEVICE_ID_RADIO, 100);
}

uint32_t getStackSize()
{
    PROCESSOR_WORD_TYPE stackDepth;

    Fiber *fibers = get_fiber_list();

    Fiber f{};

    if (fibers != nullptr)
        f = fibers[0];
    else
    {
        return 0;
    }

    // Calculate the stack depth.
    stackDepth = tcb_get_stack_base(f.tcb) - (PROCESSOR_WORD_TYPE)get_current_sp();
    return stackDepth;
}

void printMemoryStats()
{
    uint32_t heapUsed;
    uint32_t heapFree;
    uint32_t stackDepth = getStackSize();
    heap_stats(heapFree, heapUsed);

    DMESG("Stack: %d Heap used: %d Heap free: %d", stackDepth, heapUsed, heapFree);
}

#include <cstdio>

uint64_t startTime;
uint64_t endTime;

void onCpuEvent(MicroBitEvent e)
{
    endTime = system_timer_current_time_us();
    uint64_t totalTime = endTime - startTime;
    startTime = system_timer_current_time_us();
    uint64_t idleTime = getIdleCPUTime();
    resetIdleCPUTime();

    uint32_t heapUsed;
    uint32_t heapFree;
    uint32_t stackDepth = getStackSize();
    heap_stats(heapFree, heapUsed);

    std::ostringstream ttss;
    std::ostringstream itss;

    ttss << totalTime;
    itss << idleTime;

    DMESG("Total time: %s Idle Time: %s Stack: %d Heap used: %d Heap free: %d", ttss.str().c_str(), itss.str().c_str(), stackDepth, heapUsed, heapFree);
}

void cpuUsage()
{
    //DMESG("cpuUsage");
    startTime = system_timer_current_time_us();
    resetIdleCPUTime();
    system_timer_event_every(5000, DEVICE_ID_RADIO, 101);
    uBit.messageBus.listen(DEVICE_ID_RADIO, 101, onCpuEvent);
}

int main()
{
    uBit.init();
    uBit.messageBus.listen(DEVICE_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onRecv);
    uBit.radio.enable();
    //printMemoryStats();
    NRF_RADIO->TXPOWER = -30;

    DMESG(uBit.getSerial().toCharArray());

    if (uBit.getSerialNumber() == SERVER_ADDRESS)
    {
        isServer = true;
    }

    setUserData();

    localAddress = uBit.getSerialNumber();
    uint8_t *bp = b.getBytes();

    int timeToSleep = 200;

    uBit.messageBus.listen(DEVICE_ID_RADIO, 100, timeoutEvent);

    // printMemoryStats();

    cpuUsage();

    while (true)
    {
        if (uBit.buttonA.isPressed())
        {
            DMESG("Button A");
            sendPacket(SERVER_ADDRESS, bp, false);
            // system_timer_event_after(timeout, DEVICE_ID_RADIO, 100);
        }

        if (hasReceived)
        {
            //
            uBit.messageBus.ignore(DEVICE_ID_RADIO, 100, timeoutEvent);
            //DMESG("Received, sending another...");
            hasReceived = false;
            uBit.messageBus.listen(DEVICE_ID_RADIO, 100, timeoutEvent);
            sendPacket(SERVER_ADDRESS, bp, false);
            // system_timer_event_after(timeout, DEVICE_ID_RADIO, 100);
            timeToSleep = 0;
        }
        uBit.sleep(timeToSleep);
    }
}