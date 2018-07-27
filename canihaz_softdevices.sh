wget http://www.nordicsemi.com/eng/content/download/80234/1351257/file/s110_nrf51_8.0.0.zip
wget http://www.nordicsemi.com/eng/content/download/95150/1606929/file/s130_nrf51_2.0.0.zip
wget http://www.nordicsemi.com/eng/content/download/95151/1606944/file/s132_nrf52_2.0.0.zip

unzip -o s110_nrf51_8.0.0.zip s110_nrf51_8.0.0_softdevice.hex && mv --force s110_nrf51_8.0.0_softdevice.hex ~/.arduino15/packages/sandeepmistry/hardware/nRF5/0.5.1/cores/nRF5/SDK/components/softdevice/s110/hex/
unzip -o s130_nrf51_2.0.0.zip s130_nrf51_2.0.1_softdevice.hex && mv --force s130_nrf51_2.0.1_softdevice.hex ~/.arduino15/packages/sandeepmistry/hardware/nRF5/0.5.1/cores/nRF5/SDK/components/softdevice/s130/hex/
unzip -o s132_nrf52_2.0.0.zip s132_nrf52_2.0.1_softdevice.hex && mv --force s132_nrf52_2.0.1_softdevice.hex ~/.arduino15/packages/sandeepmistry/hardware/nRF5/0.5.1/cores/nRF5/SDK/components/softdevice/s132/hex/