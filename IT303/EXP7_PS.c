/*
Pseudocode for leaky bucket algorithm.
*/

FUNCTION LeakyBucket(arrivalPackets[], bucketSize, outRate) RETURNS nothing
    bucket ← 0

    FOR each timeSlot FROM 0 TO length(arrivalPackets) - 1
        incoming ← arrivalPackets[timeSlot]

        IF bucket + incoming <= bucketSize
            bucket ← bucket + incoming
        ELSE
            overflow ← (bucket + incoming) - bucketSize
            bucket ← bucketSize
            OUTPUT "Overflow of " + overflow + " packets at time " + timeSlot
        END IF

        leaked ← MIN(bucket, outRate)
        bucket ← bucket - leaked
        OUTPUT "Transmitted " + leaked + " packets at time " + timeSlot
        OUTPUT "Bucket now holds " + bucket + " packets"
    END FOR
END FUNCTION
