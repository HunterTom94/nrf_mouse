#include <zephyr/drivers/gpio.h>

void button_init();

static struct gpio_callback left_button_cb;
static struct gpio_callback right_button_cb;
static struct gpio_callback mid_button_cb;

#define LEFT_BTN	DT_ALIAS(sw0)
#if !DT_NODE_HAS_STATUS(LEFT_BTN, okay)
#error "Unsupported board: sw0 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec left_button = GPIO_DT_SPEC_GET_OR(LEFT_BTN, gpios, {0});

#define RIGHT_BTN	DT_ALIAS(sw1)
#if !DT_NODE_HAS_STATUS(RIGHT_BTN, okay)
#error "Unsupported board: sw1 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec right_button = GPIO_DT_SPEC_GET_OR(RIGHT_BTN, gpios, {0});

#define MID_BTN    DT_NODELABEL(button4)
#if !DT_NODE_HAS_STATUS(MID_BTN, okay)
#error "Unsupported board: button4 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec mid_button = GPIO_DT_SPEC_GET_OR(MID_BTN, gpios, {0});

#define SCROLL_UP_BTN    DT_ALIAS(sw2)
#if !DT_NODE_HAS_STATUS(SCROLL_UP_BTN, okay)
#error "Unsupported board: sw2 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec scroll_up_button = GPIO_DT_SPEC_GET_OR(SCROLL_UP_BTN, gpios, {0});

#define SCROLL_DOWN_BTN    DT_ALIAS(sw3)
#if !DT_NODE_HAS_STATUS(SCROLL_DOWN_BTN, okay)
#error "Unsupported board: sw3 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec scroll_down_button = GPIO_DT_SPEC_GET_OR(SCROLL_DOWN_BTN, gpios, {0});
