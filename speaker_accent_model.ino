#include <time.h>
#include <EloquentTinyML.h>
#include "speaker_accent_model.h" // Update with your model file name

#define NUMBER_OF_INPUTS 12 // Update with your model input size
#define NUMBER_OF_OUTPUTS 10 // Update with your model output size
#define TENSOR_ARENA_SIZE 6*1024  // Allocates memory to run the model

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

void setup() {
    Serial.begin(115200); // Initialize serial communication for debugging
    while (!Serial);  // Wait for the serial to initialize (needed on some boards)
    
    Serial.println("Initializing Model...");
    ml.begin(speaker_accent_model); // Initialize the model
}

float y_pred[NUMBER_OF_OUTPUTS] = {0};
float fRes = NULL;

// Example input data for testing
float x_train0[NUMBER_OF_INPUTS] = { 7.07147563279846, -6.51289966399678, 7.65079980498752, 7.07147563279846, -6.51289966399678, 7.65079980498752, 7.07147563279846, -6.51289966399678, 7.65079980498752, 7.07147563279846, -6.51289966399678, 7.65079980498752 };
float x_test0[NUMBER_OF_INPUTS] = { 7.07147563279846, -6.51289966399678, 7.65079980498752, 7.07147563279846, -6.51289966399678, 7.65079980498752, 7.07147563279846, -6.51289966399678, 7.65079980498752, 7.07147563279846, -6.51289966399678, 7.65079980498752 };

void loop() {
    uint32_t startTime;
    uint32_t timeIt;
    initfResult(y_pred);

    // Example inference for training data
    startTime = micros();
    fRes = ml.predict(x_train0, y_pred);
    timeIt = micros() - startTime;

    Serial.print("Inference on training data took ");
    Serial.print(timeIt);
    Serial.println(" micros to run");

    displayOutput(y_pred);

    // Example inference for test data
    startTime = micros();
    fRes = ml.predict(x_test0, y_pred);
    timeIt = micros() - startTime;

    Serial.print("Inference on test data took ");
    Serial.print(timeIt);
    Serial.println(" micros to run");

    displayOutput(y_pred);

    delay(3000); // 3 seconds delay
}

void initfResult(float *fResult) {
    for(int i = 0; i < NUMBER_OF_OUTPUTS; i++) {
        fResult[i] = 0.0f;
    }
}

void displayOutput(float *fResult) {
    for(int i = 0; i < NUMBER_OF_OUTPUTS; i++) {
        Serial.print(fResult[i]);
        Serial.print(" ");
    }
    Serial.println();
}

int getMaxIndex(float *valArr) {
    byte maxIndex = 0;
    float maxValue = valArr[maxIndex];

    for(byte i = 1; i < NUMBER_OF_OUTPUTS; i++) {
        if(valArr[i] > maxValue) {
            maxValue = valArr[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}
