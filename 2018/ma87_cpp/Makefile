all: compile

compile: guard-DAY
	g++ src/adc_${DAY}.cpp -o adc_${DAY}.out

guard-%:
	@ if [ "${${*}}" = "" ]; then \
        echo "Environment variable $* not set"; \
        exit 1; \
    fi
