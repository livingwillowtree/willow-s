TARGET = vector_temp_analyzer
CXX = g++
OUTPUT_DIR = ../outputs

EXECUTE = $(OUTPUT_DIR)/$(TARGET)

all: $(EXECUTE)
	@echo ""
	@echo "--- Starting [$(TARGET)]... ---"
	@echo ""
	@echo ""
	@$(EXECUTE)

$(EXECUTE): $(TARGET).cpp
	@mkdir -p $(OUTPUT_DIR)
	$(CXX) -o $(EXECUTE) $(TARGET).cpp

clean:
	rm -f $(EXECUTE)
