#ifndef _IDSO1070_H_
#define _IDSO1070_H_

#include "base.h"

class Protocol;
class PacketParser;

class IDSO1070
{
  friend class Protocol;
  friend class PacketParser;

public:
  static const int MaxPWM = 4095;
  static const int MemoryDepth = 2000;
  static const int SamplesCountPerPacket = 500;
  static const int MaxSample = 248;

  struct DeviceSettings
  {
    // freqDiv an timeBase are related to each other!
    TimeBase timeBase = HDIV_1mS;
    uint32_t freqDiv = 0;

    ScopeMode scopeMode = SCOMODE_ANALOG;
    CaptureMode captureMode = CAPMODE_NORMAL;

    uint8_t batteryLevel = 0;

    string armFirmwareVersion;
    string fpgaFirmwareVersion;
    string productName;
    string userName;

    uint8_t diffFixData[2][256];
    uint16_t caliLevel[100];
    uint8_t fpgaAlert[40];
  };
  struct ChannelSettings
  {
    bool enabled = true;
    VoltageDiv verticalDiv = VDIV_1V;
    InputCoupling coupling = COUPLING_AC;
    int16_t verticalPosition;
    uint16_t pwmArray[9][2];

    double voltage125;
    double voltageRL1;
    double voltageRL2;
  };
  struct TriggerSettings
  {
    bool isHold = false;
    TriggerMode mode = TRIGMODE_AUTO;
    TriggerChannel channel = TRIGCHAN_CH1;
    TriggerSlope slope = TRIGSLOPE_RISING;
    uint16_t level = 0;
    double xPosition = 0.5;
    uint16_t innerPWM[4];
    uint16_t outerPWM[2];
  };

  IDSO1070();
  ~IDSO1070()
  {
  }

  // Copy assignment operator
  IDSO1070 &operator=(IDSO1070 obj);

  // General device settings
  void setDeviceTimeBase(TimeBase timeBase);
  TimeBase getDeviceTimeBase();

  void setDeviceCaptureMode(CaptureMode captureMode);
  CaptureMode getDeviceCaptureMode();

  void setDeviceScopeMode(ScopeMode scopeMode);
  ScopeMode getDeviceScopeMode();

  void setARMFirmwareVersion(string version);
  string getARMFirmwareVersion();

  void setFPGAFirmwareVersion(string version);
  string getFPGAFirmwareVersion();

  void setProductName(string productName);
  string getProductName();

  void setUserName(string userName);
  string getUserName();

  void setCaliLevel(uint8_t *data);
  uint16_t *getCaliLevel();

  void setFPGAAlert(uint8_t *data);
  uint8_t *getFPGAAlert();

  void setDiffFixData(size_t channel, size_t offset, uint8_t *data);

  void setBatteryLevel(uint8_t batteryLevel);
  uint8_t getBatteryLevel();

  void setFreqDiv(uint32_t freqDiv);
  uint32_t getFreqDiv();

  // Channel data access methods
  ChannelSelector getSelectedChannel();

  bool isChannelEnabled(ChannelSelector channel);

  VoltageDiv getChannelVerticalDiv(ChannelSelector channel);

  InputCoupling getChannelCoupling(ChannelSelector channel);

  int16_t getChannelVerticalPosition(ChannelSelector channel);

  uint16_t getChannelPWM(ChannelSelector channel, uint8_t a, uint8_t b);
  uint16_t *getChannelPWM(ChannelSelector channel, uint8_t a);

  double getChannelVoltage125(ChannelSelector channel);

  double getChannelVoltageRL1(ChannelSelector channel);

  double getChannelVoltageRL2(ChannelSelector channel);

  // Trigger data access methods
  uint16_t getTriggerLevel();

  TriggerChannel getTriggerChannel();

  TriggerSlope getTriggerSlope();

  TriggerMode getTriggerMode();

  double getTriggerXPosition();

  uint16_t getTriggerInnerPWM(uint8_t index);
  uint16_t *getTriggerInnerPWM();

  uint16_t getTriggerOuterPWM(uint8_t index);
  uint16_t *getTriggerOuterPWM();

  uint16_t getTriggerBottomPWM();
  uint16_t getTriggerTopPWM();

  // Misc
  int getLittlePacketStatus();

  uint8_t getReceiveFreqDivStatus();

  bool isSampleRate200Mor250M();

  TimeBase getDeviceTimeBaseFromFreqDiv();

  size_t getSamplesNumberOfOneFrame();
  uint8_t getEnabledChannelsCount();
  uint8_t getPacketsNumber();

protected:
  // All setters are protected!
  void setSelectedChannel(ChannelSelector channel);
  void enableChannel(ChannelSelector channel);
  void disableChannel(ChannelSelector channel);
  void setChannelVerticalDiv(ChannelSelector channel, VoltageDiv verticalDiv);
  void setChannelCoupling(ChannelSelector channel, InputCoupling coupling);
  void setChannelVerticalPosition(ChannelSelector channel, int16_t verticalPosition);
  void setChannelPWM(ChannelSelector channel, uint16_t pwm, uint8_t a, uint8_t b);
  void setChannelVoltage125(ChannelSelector channel, double voltage);
  void setChannelVoltageRL1(ChannelSelector channel, double voltage);
  void setChannelVoltageRL2(ChannelSelector channel, double voltage);
  void setTriggerLevel(uint16_t i);
  void setTriggerChannel(TriggerChannel channel);
  void setTriggerSlope(TriggerSlope slope);
  void setTriggerMode(TriggerMode mode);
  void setTriggerXPosition(double xPosition);
  void setTriggerInnerPWM(uint8_t index, uint16_t pwm);
  void setTriggerOuterPWM(uint8_t index, uint16_t pwm);
  void setLittlePacketStatus(int littlePacketStatus);
  void setReceiveFreqDivStatus(uint8_t receiveFreqDivStatus);

  // Device members
  DeviceSettings deviceSettings;

  // Channel members
  ChannelSettings channels[2];
  ChannelSelector selectedChannel;

  // Trigger members
  TriggerSettings triggerSettings;

  // Misc
  int littlePacketStatus;
  uint8_t receiveFreqDivStatus;
};

#endif // _IDSO1070_H_