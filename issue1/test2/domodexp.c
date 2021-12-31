
#include "domodexp.h"

#include "cpa.h"
#include "cpa_dev.h"
#include "cpa_types.h"

#include "cpa_fips_sample.h"
#include "cpa_fips_sample_utils.h"

void myModExp()
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

    const char *msg = "Test";
    displayHexArray(msg,NULL,0);

    isFbALessThanFbB(NULL,NULL);
    
    return ;
}

