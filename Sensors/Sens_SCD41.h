
//---------------------------------------------------------
// Sens_SCD41
// HMSteve 2022-03-15 (cc by-nc-sa)
// +++
// 2019-07-14 Tom Major (Creative Commons)
// https://creativecommons.org/licenses/by-nc-sa/4.0/
// You are free to Share & Adapt under the following terms:
// Give Credit, NonCommercial, ShareAlike
// +++
// AskSin++ 2016-10-31 papa Creative Commons
//---------------------------------------------------------

#ifndef _SENS_SCD41_H_
#define _SENS_SCD41_H_

#include <Sensors.h>
#include <Wire.h>
#include "SparkFun_SCD4x_Arduino_Library.h"


namespace as {

class Sens_SCD41 : public Sensor {

    int16_t  _temperature;
    uint32_t _carbondioxide;
    uint8_t  _humidity;
    SCD4x    _scd41;



public:
    Sens_SCD41()
        : _temperature(0)
        , _carbondioxide(0)
        , _humidity(0)
        , _scd41(SCD4x_SENSOR_SCD41)
    {
    }


    void init(uint16_t altitude, uint16_t temperature_correction, bool auto_self_calib)
    {
        Wire.begin();
        //delay(200);

        if (_scd41.begin(false, auto_self_calib, false) == false)
        {
          DPRINTLN("Error: no Sensirion SCD4x CO2 sensor found");
        }
        else if(_scd41.measureSingleShot() == false)
        {
          DPRINTLN("Sensor Error - SCD41 single shot mode failed");
        }
        else
        {
          DPRINTLN(F("SCD41 found"));
          _present = true;
          //_scd41.enableDebugging();
          _scd41.setSensorAltitude(altitude);                                // Set altitude of the sensor in m
          _scd41.setTemperatureOffset((float)temperature_correction/10.0);   //temp offset between on-board sensor and ambient temp
        }
    }



    bool setForcedRecalibrationFactor(uint16_t concentration)
    {
      return(_scd41.performForcedRecalibration(concentration));
    }



    void measure(uint16_t pressureAmb)
    {
        _temperature = _carbondioxide = _humidity = 0;
        if (_present == true) {
            _scd41.setAmbientPressure((float)(pressureAmb) * 100.0);
            _scd41.measureSingleShot();
        }
    }



    void measure()
    {
      measure(1013); //overload: if no ambient pressure passed, use mean pressure at sea level
    }



    void readSCDvalues()
    {
      while (!_scd41.readMeasurement())
      {
          delay(100);
          DPRINT(".");
      }
      DPRINTLN("");
      _temperature      = (int16_t)(_scd41.getTemperature() * 10.0);
      _carbondioxide    = (uint16_t)(_scd41.getCO2());
      _humidity         = (uint8_t)(_scd41.getHumidity());
      DPRINT(F("SCD41   Temperature   : "));
      DDECLN(_temperature);
      DPRINT(F("SCD41   Humidity      : "));
      DDECLN(_humidity);
      DPRINT(F("SCD41   CO2           : "));
      DDECLN(_carbondioxide);
    }


    int16_t  temperature() { return _temperature; }
    uint32_t carbondioxide() { return _carbondioxide; }
    uint8_t  humidity() { return _humidity; }
};

}

#endif
