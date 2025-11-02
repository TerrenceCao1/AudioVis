idf_component_register(
			SRC_DIRS "../src" 
				"../../components/ESP32-FFT/src"
				${SRCDIRS}
			INCLUDE_DIRS 
				"../include" 
				"../../components/ESP32-FFT/inc"
				${INCLUDEDIRS}
			REQUIRES 
				ESP32-HUB75-MatrixPanel-I2S-DMA
				driver
				freertos
					   )
