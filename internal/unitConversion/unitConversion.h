/**
 * @file unitConversion.h
 * @brief Header file for unit conversion system.
 *
 * Provides functionality to convert between different units
 * based on a common SI base unit.
 */

#ifndef UNITCONVERSION_H
#define UNITCONVERSION_H

#define CATEGORY_LENGTH      1
#define CATEGORY_TEMPERATURE  2

typedef struct {
    const char *name;                  // Unit name (e.g., "km", "mi", "C", "F")
    int category;                      // Unit category (length, temperature, etc.)
    double (*to_base)(double x);        // Convert to base unit (m, K, etc.)
    double (*from_base)(double x);      // Convert from base unit
} UnitEntry;

/**
 * @brief Converts a value from one unit to another.
 * 
 * @param value  Value to convert.
 * @param from_unit  Unit name to convert from.
 * @param to_unit    Unit name to convert to.
 * @param result     Pointer to store the converted result.
 * @return           0 on success, -1 on failure (e.g., incompatible units).
 */
int convert_units(double value, const char *from_unit, const char *to_unit, double *result);

#endif // UNITCONVERSION_H
