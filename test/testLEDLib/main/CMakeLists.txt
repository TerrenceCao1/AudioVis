idf_component_register(
			SRC_DIRS "." 
				"../components/esp32-fft/components/fft"	
				${SRCDIRS}
			INCLUDE_DIRS 
				"." 
				"../components/esp32-fft/components/fft/include"
				${INCLUDEDIRS}
			REQUIRES 
				ESP32-HUB75-MatrixPanel-I2S-DMA
					   )
