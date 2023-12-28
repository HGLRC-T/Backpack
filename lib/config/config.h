#pragma once

#include "elrs_eeprom.h"

// CONFIG_MAGIC is ORed with CONFIG_VERSION in the version field
#define TX_BACKPACK_CONFIG_MAGIC    (0b01 << 30)
#define VRX_BACKPACK_CONFIG_MAGIC   (0b10 << 30)

#define TX_BACKPACK_CONFIG_VERSION      3
#define VRX_BACKPACK_CONFIG_VERSION     3

#if defined(TARGET_TX_BACKPACK)
typedef struct {
    uint32_t    version;
    bool        startWiFi;
    char        ssid[33];
    char        password[65];
    uint8_t     address[6];
} tx_backpack_config_t;

class TxBackpackConfig
{
public:
    void Load();
    void Commit();

    // Getters
    bool     IsModified() const { return m_modified; }
    bool     GetStartWiFiOnBoot() { return m_config.startWiFi; }
    char    *GetSSID() { return m_config.ssid; }
    char    *GetPassword() { return m_config.password; }
    uint8_t *GetGroupAddress() { return m_config.address; }

    // Setters
    void SetStorageProvider(ELRS_EEPROM *eeprom);
    void SetDefaults();
    void SetStartWiFiOnBoot(bool startWifi);
    void SetSSID(const char *ssid);
    void SetPassword(const char *ssid);
    void SetGroupAddress(const uint8_t address[6]);

private:
    tx_backpack_config_t    m_config;
    ELRS_EEPROM             *m_eeprom;
    bool                    m_modified;
};

extern TxBackpackConfig config;

#endif

///////////////////////////////////////////////////

#if defined(TARGET_VRX_BACKPACK)
typedef struct {
    uint32_t    version;
    uint8_t     bootCount;
    bool        startWiFi;
    char        ssid[33];
    char        password[65];
    uint8_t     address[6];

#if defined(AAT_BACKPACK)
    uint8_t     satelliteHomeMin; // minimum number of satellites to establish home
    uint8_t     servoSmooth;
    uint8_t     project; // 0=none, 1=projectAzim, 2=projectElev, 3=projectBoth
    uint8_t     servoMode; // reserved to declare 2:1 or 180+flip servo
    uint16_t    servoLowAzim;
    uint16_t    servoLowElev;
    uint16_t    servoHighAzim;
    uint16_t    servoHighElev;
#endif
} vrx_backpack_config_t;

class VrxBackpackConfig
{
public:
    void Load();
    void Commit();

    // Getters
    bool     IsModified() const { return m_modified; }
    uint8_t  GetBootCount() { return m_config.bootCount; }
    bool     GetStartWiFiOnBoot() { return m_config.startWiFi; }
    char    *GetSSID() { return m_config.ssid; }
    char    *GetPassword() { return m_config.password; }
    uint8_t *GetGroupAddress() { return m_config.address; }

    // Setters
    void SetStorageProvider(ELRS_EEPROM *eeprom);
    void SetDefaults();
    void SetBootCount(uint8_t count);
    void SetStartWiFiOnBoot(bool startWifi);
    void SetSSID(const char *ssid);
    void SetPassword(const char *ssid);
    void SetGroupAddress(const uint8_t address[6]);

#if defined(AAT_BACKPACK)
    uint8_t GetAatSatelliteHomeMin() const { return m_config.satelliteHomeMin; }
    uint8_t GetAatServoSmooth() const { return m_config.servoSmooth; }
    uint8_t GetAatProject() const { return m_config.project; }
    uint16_t GetAatServoLowAzim() const { return m_config.servoLowAzim; }
    uint16_t GetAatServoLowElev() const { return m_config.servoLowElev; }
    uint16_t GetAatServoHighAzim() const { return m_config.servoHighAzim; }
    uint16_t GetAatServoHighElev() const { return m_config.servoHighElev; }
#endif

private:
    vrx_backpack_config_t   m_config;
    ELRS_EEPROM             *m_eeprom;
    bool                    m_modified;
};

extern VrxBackpackConfig config;

#endif
