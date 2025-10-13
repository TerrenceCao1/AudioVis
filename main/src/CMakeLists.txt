idf_component_register(
			SRC_DIRS "../src" 
				"../../components/esp32-fft/components/fft"	
				${SRCDIRS}
			INCLUDE_DIRS 
				"../include" 
				"../../components/esp32-fft/components/fft/include"
				${INCLUDEDIRS}
			REQUIRES 
				ESP32-HUB75-MatrixPanel-I2S-DMA
				driver
				freertos
					   )
