
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



char* generate_random_pick(int processValue, int arrivedNumber,char* lastEvent[]) {
    char* operationDescriptions[] = {"Arrived", "Start Running", "RequestIO", "IORequestFinish", "Stop Running","Exit"};
    int randomIndex;

    switch (processValue) {
        case 0:
            // Event value 0 can only have "Arrived" or "Exit"
            randomIndex = rand() % 2; // Random index between 0 and 1
            break;
        case 1:
            // Event value 1 can have "Arrived", "Start Running", or "Exit"
            randomIndex = rand() % 3; // Random index between 0 and 2
            break;
        default:
            // For other event values, all events are allowed except "Arrived"
            randomIndex = rand() % 4 + 1  ; // Random index between 1 and 5
            break;
    }

    // Check if the current event type is restricted based on the last event
    if (arrivedNumber > 1) {
        if (strcmp(lastEvent[arrivedNumber - 1], "Start Running") == 0) {
            if (strcmp(operationDescriptions[randomIndex], "Stop Running") != 0) {
                randomIndex = 4; // Set the event type to "Stop Running"
            }
        } else if (strcmp(lastEvent[arrivedNumber - 1], "RequestIO") == 0) {
            if (strcmp(operationDescriptions[randomIndex], "IORequestFinish") != 0) {
                randomIndex = 3; // Set the event type to "IORequestFinish"
            }
        } else if (strcmp(lastEvent[arrivedNumber - 1], "IORequestFinish") == 0) {
            if (strcmp(operationDescriptions[randomIndex], "Exit") != 0) {
                randomIndex = 5; // Set the event type to "Exit"
            }
        } else if (strcmp(lastEvent[arrivedNumber - 1], "Stop Running") == 0) {
            if (strcmp(operationDescriptions[randomIndex], "Arrived") != 0) {
                randomIndex = 1; // Set the event type to "Start Running"
            }
        }
    }

    return operationDescriptions[randomIndex];
}





void generate_random_values(int *finishTime, int *numOfEvents) {// Passing the pointers of finsihTime and numOfEvents to the function.

    srand(time(NULL));// Initializing random seed based on current time to get random values for the finsihTime of simulation.
    *finishTime = rand() % 100 + 1; // Generating a random value between 1 and 100, as it will be the picked finsihtime of simulation.
    *numOfEvents = rand() % (*finishTime); // Generating a random value between 1 and finishTime of simulation, as it will be the number of events in the simulation.
    int eventTimes[*numOfEvents]; // An array is created to hold events time for entering the simulation.
    char* eventPicks[*numOfEvents]; // An array is created to hold Processes events types values{1,3,5} for the simulation, where {1}:means the Process will have only one event to operate and it's Exit, {3}:means the Process will have three events to operate; Run, Stop, Exit,{5}:means the process will have five events to operate; Run, requestIo, IoFinish, Stop, Exit.
    char* lastEvent[*numOfEvents];
    int processValue  = 1; // Counter for the number of "Arrived" events
    int arrivedNumber = 1; // ID number for "Arrived" events
    for (int i = 0; i < *numOfEvents; i++) {// For loop to generate random values for the the numerber of events, that will represent the timing of each event entering the simulation.
        int eventTime = rand() % (*finishTime - 1) + 1; // Generating random values that are less than the finish time of simulation and they will represent the entering time of each event.
        eventTimes[i] = eventTime; // Storing the generated values inside the array "NOT SORTED YET!". 
        eventPicks[i] = generate_random_pick(processValue, arrivedNumber, lastEvent);
        lastEvent[arrivedNumber] = eventPicks[i];

        if (strcmp(eventPicks[i], "Arrived") == 0) {
            processValue++;
            arrivedNumber++;
        }
    }      

    // For loop to use Bubble sort algorithm for the event times array element that will be sorted in ascending order.
    for (int i = 0; i < *numOfEvents - 1; i++) { // Starting a loop that will run from the first element of array to the second-last element of the array.
        for (int j = 0; j < *numOfEvents - i - 1; j++) { // Starting another loop that will run from the first element to the index i from the end of the array.
            if (eventTimes[j] > eventTimes[j+1]) { // Checking if the current element is greater than the next element.
                int temp = eventTimes[j]; // Swap the elements using a temporary variable.
                eventTimes[j] = eventTimes[j+1]; // Moving the greater element value to the right side of the array.
                eventTimes[j+1] = temp; // Moving the smaller element value to the left side of the array.

                char* tempPick = eventPicks[j];
                eventPicks[j] = eventPicks[j+1];
                eventPicks[j+1] = tempPick;
            }
        }
    }

    arrivedNumber = 1; // Numbering the Arrived events starting from 1 to arrivedCount

    // Printing the sorted event numer and the sorted event timing.
    for (int i = 0; i < *numOfEvents; i++) {
        if (strcmp(eventPicks[i], "Arrived") == 0) {
            printf("Time: %03ds: Process ID %d %s\n", eventTimes[i], arrivedNumber, eventPicks[i]);
            arrivedNumber++;
        } else {
            printf("Time: %03ds: Process ID %d %s\n", eventTimes[i], arrivedNumber - 1 , eventPicks[i]); // Use the previous arrivedNumber - 1
        }
    }
}



int main() {
    int finishTime, numOfEvents; // Initializing the finish time of the simulation and the numer of events that will enter the simulation.
    generate_random_values(&finishTime, &numOfEvents); // Passing the arguments by reference.
    // Priniting the finish time of simulation and the number of event that will be in the simulation.
    printf("Finish Time: %d\n", finishTime);
    printf("Number Of Processes: %d\n", numOfEvents);
    return 0;
}
