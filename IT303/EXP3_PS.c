/*
Pseudocode for Cyclic Redundancy Check (CRC).
*/

# Helper: perform modulo-2 division (binary long division) and return remainder
FUNCTION Mod2Divide(dividendBits[], divisorBits[]) RETURNS remainderBits[]
    n ← length(divisorBits)
    working ← copy(dividendBits)            # mutable copy
    FOR i FROM 0 TO length(dividendBits) - n
        IF working[i] == 1
            FOR j FROM 0 TO n-1
                working[i + j] ← working[i + j] XOR divisorBits[j]
            END FOR
        END IF
    END FOR
    remainderBits ← slice(working, length(dividendBits) - n + 1, n - 1)  # last (n-1) bits
    RETURN remainderBits
END FUNCTION

# Compute CRC codeword: append (deg) zeros, divide, append remainder
FUNCTION ComputeCRC(dataBits[], generatorBits[]) RETURNS codewordBits[]
    r ← length(generatorBits) - 1
    appended ← concat(dataBits, array_of_zeros(r))
    remainder ← Mod2Divide(appended, generatorBits)
    codewordBits ← concat(dataBits, remainder)
    RETURN codewordBits
END FUNCTION

# Verify received codeword: divide and check remainder equals zero
FUNCTION VerifyCRC(receivedBits[], generatorBits[]) RETURNS boolean
    remainder ← Mod2Divide(receivedBits, generatorBits)
    FOR bit IN remainder
        IF bit == 1
            RETURN FALSE
        END IF
    END FOR
    RETURN TRUE
END FUNCTION
