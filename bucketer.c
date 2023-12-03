#include <stdio.h>
#include <assert.h>

struct CountsBySoH {
    int healthy;
    int exchange;
    int failed;
};

// Function to classify batteries and count them based on SoH
struct CountsBySoH countBatteriesByHealth(const int* presentCapacities, int nBatteries) {
    struct CountsBySoH counts = {0, 0, 0};

    // Iterate through each battery's present capacity
    for (int i = 0; i < nBatteries; i++) {
        // Define the rated capacity of a new battery
        const int ratedCapacity = 120;

        // Calculate the state-of-health (SoH) percentage
        float sohPercentage = (float)presentCapacities[i] / ratedCapacity * 100;

        // Classify the battery based on SoH percentage
        if (sohPercentage > 80) {
            counts.healthy++;
        } else if (sohPercentage >= 62) {
            counts.exchange++;
        } else {
            counts.failed++;
        }
    }

    // Return the counts for each classification
    return counts;
}

// Test function
void testBucketingByHealth() {
    const int presentCapacities[] = {113, 116, 80, 95, 92, 70};
    const int numberOfBatteries = sizeof(presentCapacities) / sizeof(presentCapacities[0]);
    printf("Counting batteries by SoH...\n");
    struct CountsBySoH counts = countBatteriesByHealth(presentCapacities, numberOfBatteries);
    assert(counts.healthy == 2);
    assert(counts.exchange == 3);
    assert(counts.failed == 1);
    printf("Done counting :)\n");
}

// Additional test cases
void additionalTestCases() {
    // Test case 1: All batteries are healthy
    const int batteries1[] = {120, 121, 122, 125};
    struct CountsBySoH counts1 = countBatteriesByHealth(batteries1, 4);
    assert(counts1.healthy == 4);
    assert(counts1.exchange == 0);
    assert(counts1.failed == 0);

    // Test case 2: All batteries have failed
    const int batteries2[] = {60, 55, 40, 59};
    struct CountsBySoH counts2 = countBatteriesByHealth(batteries2, 4);
    assert(counts2.healthy == 0);
    assert(counts2.exchange == 0);
    assert(counts2.failed == 4);

    // Test case 3: Mix of healthy, exchange, and failed batteries
    const int batteries3[] = {105, 70, 80, 55, 90};
    struct CountsBySoH counts3 = countBatteriesByHealth(batteries3, 5);
    assert(counts3.healthy == 2);
    assert(counts3.exchange == 2);
    assert(counts3.failed == 1);

    printf("Additional test cases passed!\n");
}

int main() {
    testBucketingByHealth();
    additionalTestCases();
    return 0;
}
