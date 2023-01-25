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
 * factory_app.h
 *
 *  Created on: 17 de ago de 2022
 *      Author: Alex Manoel Ferreira Silva
 */

#pragma once

#include <stddef.h>

#include "esp_rmaker_core.h"

#include "gpi_reset_button.h"

#include "app_wifi.h"

#include "sdkconfig.h"

#define FACTORY_APP_CONFIG_DEFAULT                                  \
	{                                                               \
		.name = NULL, .type = NULL, .pop_type = POP_TYPE_RANDOM,    \
		.gpi_reset_button_config = GPI_RESET_BUTTON_CONFIG_DEFAULT, \
		.rain_maker_config =                                        \
			{                                                       \
				.enable_time_sync = true,                           \
			},                                                      \
		.node = NULL,                                               \
	}

typedef struct factory_app_config_s {
	const char			   *name;
	const char			   *type;
	app_wifi_pop_type_t       pop_type;
	gpi_reset_button_config_t gpi_reset_button_config;
	esp_rmaker_config_t       rain_maker_config;
	esp_rmaker_node_t        *node;
} factory_app_config_t;

#ifdef __cplusplus
extern "C" {
#endif
void factory_app_init(factory_app_config_t *config);
void factory_app_start(factory_app_config_t *config);
#ifdef __cplusplus
}
#endif
