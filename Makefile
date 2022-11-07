include config.mk



openocd:
	@ $(OPENOCD_CMD) -f $(OPENOCD_DIR)/scripts/interface/$(INTERFACE).cfg -f $(ENV_DIR)/rpiz2w.cfg

gdb:
	@ $(GDB_CMD) --eval-command="target extended-remote $(OPENOCD_GDB_ADDR):$(OPENOCD_GDB_PORT)"

