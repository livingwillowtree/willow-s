TARGET = funcs_num_analysis
CXX = g++
OUTPUT_DIR = ../outputs

EXECUTE = $(OUTPUT_DIR)/$(TARGET)

all: $(EXECUTE)
	@echo ""
	@echo "--- Starting [$(TARGET)]... ---"
	@$(EXECUTE)

$(EXECUTE): $(TARGET).cpp
	@mkdir -p $(OUTPUT_DIR)
	$(CXX) -o $(EXECUTE) $(TARGET).cpp

clean:
	rm -f $(EXECUTE)
