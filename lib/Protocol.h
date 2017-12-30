#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <unistd.h>

#include "hexdump.h"
#include "Timeout.h"
#include "TCPConnector.h"
#include "USBConnector.h"
#include "enums.h"
#include "IDSO1070A.h"
#include "EEROMData.h"
#include "ResponsePacket.h"
#include "Command.h"
#include "CommandGenerator.h"

class ResponseHandler
{
public:
  virtual bool onResponse(Command *cmd, bool success) = 0;
};

class Protocol
{
private:
  Connector *connection;

  CommandGenerator cmdGen;

  size_t expectedResponseCount = 0;
  bool requestSuccess = false;
  ResponseHandler *responseHandler;
  Command *lastCommand = NULL;
  CommandQueue commandQueue;

  enum States
  {
    STATE_IDLE,
    STATE_REQUEST,
    STATE_RESPONSE,
    STATE_DONE
  } state = STATE_IDLE;

  IDSO1070A device;
  EEROMData eeromData;

  void resolveCommandResponse(ResponsePacket *packet);
  void rejectCommandResponse(ResponsePacket *packet);

  void parsePacket(ResponsePacket *packet);
  void parseAAResponse(ResponsePacket *packet);
  void parseEEResponse(ResponsePacket *packet);
  void parseFPGAResponse(ResponsePacket *packet);
  void parseStateResponse(ResponsePacket *packet);
  void parseSampleData(ResponsePacket *packet);
  void parseFreqDivLowBytes(ResponsePacket *packet);
  void parseFreqDivHighBytes(ResponsePacket *packet);
  void parseRamChannelSelection(ResponsePacket *packet);
  void parseCh1ZeroLevel(ResponsePacket *packet);
  void parseCh2ZeroLevel(ResponsePacket *packet);
  void parseRelay(ResponsePacket *packet);
  void parseVoltsDiv125(ResponsePacket *packet);
  void parseTriggerLevel(ResponsePacket *packet);
  void parseTriggerSourceAndSlope(ResponsePacket *packet);
  void parseStartCapture(ResponsePacket *packet);

  void syncTimeBaseFromFreqDiv();

  void receive();
  void transmit();

public:
  Protocol(Connector *connection, ResponseHandler *responseHandler);
  ~Protocol();

  void start();
  void stop();
  void process();
  IDSO1070A &getDevice();
  EEROMData &getEEROMData();

  void sendCommands(CommandQueue cmd);
  void sendCommands(Command *cmd);
  CommandGenerator &getCmdGen();

  void resendLastCommand();
  void removeLastCommand();
};

#endif // _PROTOCOL_H_