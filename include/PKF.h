#pragma once

#include "KeyFormat.h"
#include "ProductKeyGenerator.h"

// Random Generator
#include "RandomGenerator/IRandomGenerator.h"
#include "RandomGenerator/LinearCongruentialGenerator.h"
#include "RandomGenerator/MTRandomGenerator.h"
#include "RandomGenerator/XorshiftGenerator.h"

// Checksum Algorithm
#include "Checksum/BaseChecksumAlgorithm.h"
#include "Checksum/CRC32ChecksumAlgorithm.h"
#include "Checksum/IChecksumAlgorithm.h"

// Encryption Algorithm
#include "Encryption/IEncryptionAlgorithm.h"
#include "Encryption/VigenereCipher.h"
#include "Encryption/XOREncryption.h"