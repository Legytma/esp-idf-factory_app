idf_component_register(SRCS "factory_app.c"
    INCLUDE_DIRS "include" PRIV_REQUIRES log_utils gpi gpi_reset_button rmaker_common app_wifi app_insights esp_rainmaker app_reset)
