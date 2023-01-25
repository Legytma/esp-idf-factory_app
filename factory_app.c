/**
 * Copyright 2023 Legytma Soluções Inteligentes LTDA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * factory_app.c
 *
 *  Created on: 17 de ago de 2022
 *      Author: Alex Manoel Ferreira Silva
 */

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_err.h"

#include "esp_rmaker_core.h"
#include "esp_rmaker_schedule.h"
#include "esp_rmaker_scenes.h"

#include "app_wifi.h"
#include "app_insights.h"

#include "log_utils.h"
#include "gpi_reset_button.h"

#include "factory_app.h"

LOG_TAG("factory_app");

void factory_app_init(factory_app_config_t *config) {
	/* Initialize Wi-Fi. Note that, this should be called before
	 * esp_rmaker_node_init()
	 */
	app_wifi_init();

	/* Initialize the ESP RainMaker Agent.
	 * Note that this should be called after app_wifi_init() but before
	 app_wifi_start()
	 * */
	config->node = esp_rmaker_node_init(&config->rain_maker_config,
										config->name, config->type);

	if (!config->node) {
		LOGE("Could not initialise node. Aborting!!!");
		vTaskDelay(pdMS_TO_TICKS(5000));
		abort();
	}

	/* Enable OTA */
	esp_rmaker_ota_enable_default();

	/* Enable timezone service which will be require for setting appropriate
	 * timezone from the phone apps for scheduling to work correctly. For more
	 * information on the various ways of setting timezone, please check
	 * https://rainmaker.espressif.com/docs/time-service.html.
	 */
	esp_rmaker_timezone_service_enable();

	/* Enable scheduling. */
	esp_rmaker_schedule_enable();

	/* Enable Scenes */
	esp_rmaker_scenes_enable();

	/* Enable Insights. Requires CONFIG_ESP_INSIGHTS_ENABLED=y */
	app_insights_enable();

	/* Start the ESP RainMaker Agent */
	esp_rmaker_start();

	gpi_reset_button_init(&config->gpi_reset_button_config);
}

void factory_app_start(factory_app_config_t *config) {
	/* Start the Wi-Fi.
	 * If the node is provisioned, it will start connection attempts,
	 * else, it will start Wi-Fi provisioning. The function will return
	 * after a connection has been successfully established
	 */
	esp_err_t err = app_wifi_start(config->pop_type);

	if (err != ESP_OK) {
		LOGE("Could not start Wifi. Aborting!!!");
		vTaskDelay(pdMS_TO_TICKS(5000));
		abort();
	}
}
