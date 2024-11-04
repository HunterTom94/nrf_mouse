#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>
#include <zephyr/drivers/adc.h>
#include "analog_config.h"

#define ADC_NODE DT_NODELABEL(adc)
static const struct device *adc_dev = DEVICE_DT_GET(ADC_NODE);

#define ADC_RESOLUTION 10
#define ADC_GAIN ADC_GAIN_1_2
#define ADC_REFERENCE ADC_REF_INTERNAL
#define NUMBER_OF_ADC_CHANNELS 3

// Define ADC channels
static const uint8_t adc_channels[NUMBER_OF_ADC_CHANNELS] = {
    SAADC_CH_PSELP_PSELP_AnalogInput1,
    SAADC_CH_PSELP_PSELP_AnalogInput2,
    SAADC_CH_PSELP_PSELP_AnalogInput3
};

int16_t sample_buffer[NUMBER_OF_ADC_CHANNELS];

struct adc_sequence sequence = {
    .channels = BIT(0) | BIT(1) | BIT(2), // Assuming channels are 0, 1, 2
    .buffer = sample_buffer,
    .buffer_size = sizeof(sample_buffer),
    .resolution = ADC_RESOLUTION,
};

int check_adc(void)
{
    if (!device_is_ready(adc_dev)) {
        printk("ADC device not ready\n");
        return -1;
    }
    return 0;
}

int adc_channel_config(void)
{
    int err = 0;

    for (int i = 0; i < NUMBER_OF_ADC_CHANNELS; ++i) {
        struct adc_channel_cfg channel_cfg = {
            .gain = ADC_GAIN,
            .reference = ADC_REFERENCE,
            .acquisition_time = ADC_ACQ_TIME_DEFAULT,
            .channel_id = i, // Channel ID
#ifdef CONFIG_ADC_NRFX_SAADC
            .input_positive = adc_channels[i],
#endif
        };

        err = adc_channel_setup(adc_dev, &channel_cfg);
        if (err != 0) {
            printk("Error in adc_channel_setup for channel %d: %d\n", i, err);
            return err;
        }
    }

    return err;
}

int analog_read(bool voltage)
{
    int err = adc_read(adc_dev, &sequence);
    if (err != 0) {
        printk("Error in adc_read: %d\n", err);
        return -99;
    }

    // Process and optionally convert each channel's data
    for (int i = 0; i < NUMBER_OF_ADC_CHANNELS; ++i) {
        int32_t mv_value = sample_buffer[i];
        if (voltage) {
            int32_t adc_vref = adc_ref_internal(adc_dev);
            adc_raw_to_millivolts(adc_vref, ADC_GAIN, ADC_RESOLUTION, &mv_value);
            printk("Channel %d: %d mV\n", i, mv_value);
        } else {
            printk("Channel %d: %d Raw\n", i, mv_value);
        }
    }

    return 0; // You might want to change this depending on how you wish to use the result
}
