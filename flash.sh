avrdude -C .\avrdude.conf -c arduino_as_isp -P COM3 -p AT89S51 -U flash:w:".\irrigation-system.hex":a
