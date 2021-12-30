
#include "cpa.h"
#include "cpa_dev.h"
#include "cpa_types.h"

int main(int argc, char *argv[])
{
    // Get number of QAT devices
    Cpa16U numDevices = 0;
    CpaStatus status = CPA_STATUS_FAIL;
    
    status = cpaGetNumDevices(&numDevices);

    if (status == CPA_STATUS_SUCCESS) {
        printf("Number of QAT devices: %d\n", numDevices);
    } else {
        printf("Querying number of QAT devices.\n");
    } 
    
    return 0;
}

