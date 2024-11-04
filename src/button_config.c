#include <zephyr/kernel.h>
#include <zephyr/device.h>

#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "button_config.h"

static void check_gpio_is_ready_dt(){
    if (!gpio_is_ready_dt(&left_button)) {
        printk("Error: button device %s is not ready\n",
               left_button.port->name);
        return 0;
    }
    if (!gpio_is_ready_dt(&right_button)) {
        printk("Error: button device %s is not ready\n",
               right_button.port->name);
        return 0;
    }
    if (!gpio_is_ready_dt(&mid_button)) {
        printk("Error: button device %s is not ready\n",
               mid_button.port->name);
        return 0;
    }
    if (!gpio_is_ready_dt(&scroll_up_button)) {
        printk("Error: button device %s is not ready\n",
               scroll_up_button.port->name);
        return 0;
    }
    if (!gpio_is_ready_dt(&scroll_down_button)) {
        printk("Error: button device %s is not ready\n",
               scroll_down_button.port->name);
        return 0;
    }

}

static void configure_pins_dt(){
    int ret;

    ret = gpio_pin_configure_dt(&left_button, GPIO_INPUT);
    if (ret != 0) {
        printk("Error %d: failed to configure %s pin %d\n",
               ret, left_button.port->name, left_button.pin);
        return 0;
    }

    ret = gpio_pin_interrupt_configure_dt(&left_button,
                                          GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
        printk("Error %d: failed to configure interrupt on %s pin %d\n",
            ret, left_button.port->name, left_button.pin);
        return 0;
    }

    ret = gpio_pin_configure_dt(&right_button, GPIO_INPUT);
    if (ret != 0) {
        printk("Error %d: failed to configure %s pin %d\n",
               ret, right_button.port->name, right_button.pin);
        return 0;
    }

    ret = gpio_pin_interrupt_configure_dt(&right_button,
                                          GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
        printk("Error %d: failed to configure interrupt on %s pin %d\n",
            ret, right_button.port->name, right_button.pin);
        return 0;
    }

    ret = gpio_pin_configure_dt(&mid_button, GPIO_INPUT);
    if (ret != 0) {
        printk("Error %d: failed to configure %s pin %d\n",
               ret, mid_button.port->name, mid_button.pin);
        return 0;
    }

    ret = gpio_pin_interrupt_configure_dt(&mid_button,
                                          GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
        printk("Error %d: failed to configure interrupt on %s pin %d\n",
            ret, mid_button.port->name, mid_button.pin);
        return 0;
    }

    ret = gpio_pin_configure_dt(&scroll_up_button, GPIO_INPUT);
    if (ret != 0) {
        printk("Error %d: failed to configure %s pin %d\n",
               ret, scroll_up_button.port->name, scroll_up_button.pin);
        return 0;
    }

    ret = gpio_pin_configure_dt(&scroll_down_button, GPIO_INPUT);
    if (ret != 0) {
        printk("Error %d: failed to configure %s pin %d\n",
               ret, scroll_down_button.port->name, scroll_down_button.pin);
        return 0;
    }

}



void button_init(){
    
    check_gpio_is_ready_dt();

    configure_pins_dt();

}