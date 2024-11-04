#ifndef ANALOG_CONFIG_H_
#define ANALOG_CONFIG_H_

#include <zephyr/types.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if the ADC device is ready.
 * 
 * @return 0 if the device is ready, -1 otherwise.
 */
int check_adc(void);

/**
 * Configure the ADC channel.
 * 
 * @return 0 on success, error code on failure.
 */
int adc_channel_config(void);

/**
 * Read a value from the analog channel.
 * 
 * @param voltage Whether to convert the reading to millivolts.
 * @return The raw or converted ADC value, or -99 on error.
 */
int analog_read(bool voltage);

#ifdef __cplusplus
}
#endif

#endif // ANALOG_CONFIG_H_
