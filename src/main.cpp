/*
 * Copyright (c) 2024 Loic Domaigne
 * SPDX-License-Identifier: MIT
 */
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <stdarg.h>

/* tm_main() is defined in the respective benchmarking test */
extern "C" void tm_main();

extern "C" int printf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  const size_t MAX_STR_LEN = 128;
  char buf[MAX_STR_LEN];
  int rc;

  rc = vsnprintf(buf, MAX_STR_LEN - 1, format, args);
  Serial.print(buf);
  Serial.print("\r");
  va_end(args);
  return rc;
}

extern "C" void tm_main(void);
void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }

  Serial.println("FreeRTOS with Arduino framework up and running\n");

  tm_main();

  // Start the FreeRTOS scheduler
  vTaskStartScheduler();

  // Should never get here
  Serial.println("Scheduler failed to start!");
  while (1)
    ;
}

void loop() {
  // FreeRTOS takes over, this should never be called
  Serial.println("Oops, there's a bug!");
  while (1)
    ;
}
