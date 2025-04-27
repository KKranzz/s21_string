CC=gcc
CC_FLAGS=-c -g -Wall -Werror -Wextra -std=c11
GCOV_FLAGS=--coverage
CHECK_FLAGS=-lcheck

# Узнаём название ядра системы
UNAME := $(shell uname -s)

# Для ubuntu нужен дополнительный флаг
ifeq ($(UNAME), Linux)
CHECK_FLAGS+=-lsubunit -lm
endif

# Директории
MODULES_DIR := modules
TESTS_DIR := tests

# ВСЕ тесты из папки tests
TESTS = $(notdir $(basename $(wildcard $(TESTS_DIR)/*.check)))
# ВСЕ функции из папки modules
MODULES := $(notdir $(basename $(wildcard $(MODULES_DIR)/*.c)))

# Объектные файлы для модулей и тестов
MODULES_OBJS := $(addprefix $(MODULES_DIR)/, $(addsuffix .o, $(MODULES)))
TESTS_OBJS = $(addprefix $(TESTS_DIR)/, $(addsuffix .o, $(TESTS)))

LIBRARY := s21_string.a

# Цель по умолчанию
all: $(LIBRARY)

# Правило для сборки библиотеки
$(LIBRARY): $(MODULES_OBJS)
	ar rcs $(LIBRARY) $(MODULES_OBJS)

# Шаблонное правило для компиляции объектных файлов модулей
$(MODULES_DIR)/%.o: $(MODULES_DIR)/%.c
	$(CC) $(CC_FLAGS) -c $< -o $@ -I.

# Шаблонное правило для компиляции объектных файлов тестов
$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CC_FLAGS) -c $< -o $@ -I.

# Правило для компиляции и линковки тестов
test: clean check $(TESTS_OBJS) $(LIBRARY)
	$(foreach file,$(TESTS),\
  		$(CC) $(TESTS_DIR)/$(file).o $(LIBRARY) $(CHECK_FLAGS) $(GCOV_FLAGS) -o $(file);)
	$(foreach file,$(TESTS), echo "TESTING $(file)"; ./$(file);)

# Правило для генерации отчета gcov
add_coverage:
	$(eval CC_FLAGS += --coverage)

gcov_report: clean add_coverage test
	mkdir -p gcovr
	gcovr -r . --exclude 'tests/.*' --html --html-details -o gcovr/index.html

open: gcov_report
	open gcovr/index.html

clean:
	rm -f modules/*.o tests/test_*.c s21_string.a test_* tests/*.o */*.gcda */*.gcno *.info */*.html */*.css *.gcda *.gcno

# Переменная для всех .check файлов
CHECK_FILES := $(wildcard tests/*.check)

CHECK_C_FILES := $(CHECK_FILES:.check=.c)

# Цель для обработки всех .check файлов
check: $(CHECK_C_FILES) format

# Правило для преобразования .check -> .c
tests/%.c: tests/%.check
	checkmk clean_mode=1 $< > $@

format:
	clang-format -i modules/*.c
	clang-format -i *.h

format_check:
	clang-format -n modules/*.c
	clang-format -n *.h

install_dos2unix:
	@echo "Installing dos2unix..."
	@if [ "$(UNAME)" = "Linux" ]; then \
	sudo apt-get update && sudo apt-get install -y dos2unix; \
	elif [ "$(UNAME)" = "Darwin" ]; then \
	brew install dos2unix; \
	else \
	echo "Unsupported OS. Please install dos2unix manually."; \
	fi

dos2unix_check:
	dos2unix tests/*.check

.PHONY: all clean test gcov_report