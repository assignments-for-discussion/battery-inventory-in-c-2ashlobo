#include <stdio.h>
#include <assert.h>

struct CountsBySoH {
    int healthy;
    int exchange;
    int failed;
};


struct CountsBySoH countBatteriesByHealth(const int* presentCapacities, int nBatteries) {
    struct CountsBySoH counts = {0, 0, 0};

    
    for (int i = 0; i < nBatteries; i++) {
        
        const int ratedCapacity = 120;

        
        float sohPercentage = (float)presentCapacities[i] / ratedCapacity * 100;

        
        if (sohPercentage > 80) {
            counts.healthy++;
        } else if (sohPercentage >= 62) {
            counts.exchange++;
        } else {
            counts.failed++;
        }
    }

    
    return counts;
}


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


void additionalTestCases() {
    
    const int batteries1[] = {120, 121, 122, 125};
    struct CountsBySoH counts1 = countBatteriesByHealth(batteries1, 4);
    assert(counts1.healthy == 4);
    assert(counts1.exchange == 0);
    assert(counts1.failed == 0);

    
    const int batteries2[] = {60, 55, 40, 59};
    struct CountsBySoH counts2 = countBatteriesByHealth(batteries2, 4);
    assert(counts2.healthy == 0);
    assert(counts2.exchange == 0);
    assert(counts2.failed == 4);

    
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
