/*
Pseudocode for Bit stuffing.
*/

FUNCTION BitStuff(dataBits[]) RETURNS stuffedBits[]
    stuffed ← empty list
    count ← 0

    FOR bit IN dataBits
        append bit TO stuffed

        IF bit == 1
            count ← count + 1
            IF count == 5
                append 0 TO stuffed      # insert stuffed zero
                count ← 0
            END IF
        ELSE
            count ← 0
        END IF
    END FOR

    RETURN stuffed
END FUNCTION
