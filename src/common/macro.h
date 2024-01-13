#define _GUI_LOCK(BODY)                                                        \
  if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {                \
    BODY;                                                                      \
    xSemaphoreGive(xGuiSemaphore);                                             \
  } else {                                                                     \
    ESP.restart();                                                             \
  }
