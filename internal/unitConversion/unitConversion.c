/**
 * @file unitConversion.c
 * @brief Implementation of the unit conversion system.
 */

#include "unitConversion.h"
#include <string.h>
#include <stdio.h>

/* --- Conversion Functions --- */
// Linear conversion functions (Length units)
static double identity(double x) { return x; }

static double km_to_m(double x) { return x * 1000.0; }
static double m_to_km(double x) { return x / 1000.0; }

static double cm_to_m(double x) { return x * 0.01; }
static double m_to_cm(double x) { return x / 0.01; }

static double mm_to_m(double x) { return x * 0.001; }
static double m_to_mm(double x) { return x / 0.001; }

static double mi_to_m(double x) { return x * 1609.34; }
static double m_to_mi(double x) { return x / 1609.34; }

static double ft_to_m(double x) { return x * 0.3048; }
static double m_to_ft(double x) { return x / 0.3048; }

static double in_to_m(double x) { return x * 0.0254; }
static double m_to_in(double x) { return x / 0.0254; }

static double yd_to_m(double x) { return x * 0.9144; }
static double m_to_yd(double x) { return x / 0.9144; }

static double nmi_to_m(double x) { return x * 1852.0; }
static double m_to_nmi(double x) { return x / 1852.0; }

// Temperature conversion functions
static double C_to_K(double x) { return x + 273.15; }
static double K_to_C(double x) { return x - 273.15; }

static double F_to_K(double x) { return (x - 32.0) * 5.0 / 9.0 + 273.15; }
static double K_to_F(double x) { return (x - 273.15) * 9.0 / 5.0 + 32.0; }

static double R_to_K(double x) { return x * 5.0 / 9.0; }
static double K_to_R(double x) { return x * 9.0 / 5.0; }
/* ----------------------------------------- */

/* --- Units Table --- */
static const UnitEntry units[] = {
    // Length (base: meter)
    {"m",    CATEGORY_LENGTH,    identity, identity},
    {"km",   CATEGORY_LENGTH,    km_to_m, m_to_km},
    {"cm",   CATEGORY_LENGTH,    cm_to_m, m_to_cm},
    {"mm",   CATEGORY_LENGTH,    mm_to_m, m_to_mm},
    {"mi",   CATEGORY_LENGTH,    mi_to_m, m_to_mi},
    {"ft",   CATEGORY_LENGTH,    ft_to_m, m_to_ft},
    {"in",   CATEGORY_LENGTH,    in_to_m, m_to_in},
    {"yd",   CATEGORY_LENGTH,    yd_to_m, m_to_yd},
    {"nmi",  CATEGORY_LENGTH,    nmi_to_m, m_to_nmi},
    
    // Temperature (base: Kelvin)
    {"K",    CATEGORY_TEMPERATURE, identity, identity},
    {"C",    CATEGORY_TEMPERATURE, C_to_K, K_to_C},
    {"F",    CATEGORY_TEMPERATURE, F_to_K, K_to_F},
    {"R",    CATEGORY_TEMPERATURE, R_to_K, K_to_R},

    {NULL,  0, NULL, NULL}
};
/* ---------------------------- */

/* --- Helper: Lookup Unit --- */
static const UnitEntry* lookup_unit(const char *name) {
    for (int i = 0; units[i].name != NULL; i++) {
        if (strcmp(units[i].name, name) == 0) {
            return &units[i];
        }
    }
    return NULL;
}
/* --------------------------- */

/* --- Convert Units --- */
int convert_units(double value, const char *from_unit, const char *to_unit, double *result) {
    const UnitEntry *from = lookup_unit(from_unit);
    const UnitEntry *to = lookup_unit(to_unit);

    if (!from || !to) {
        printf("Error: Unknown unit '%s' or '%s'\n", from_unit, to_unit);
        return -1;
    }

    if (from->category != to->category) {
        printf("Error: Incompatible unit categories '%s' and '%s'\n", from_unit, to_unit);
        return -1;
    }

    // Convert to base unit
    double base_value = from->to_base(value);

    // Convert from base unit to target unit
    *result = to->from_base(base_value);

    return 0; // Success
}
/* -------------------- */
