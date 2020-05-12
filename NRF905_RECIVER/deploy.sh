st-flash  erase
st-flash  write build/NRF905_RECIVER.bin 0x08000000
st-flash write config.bin 0x08060000