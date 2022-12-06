#pragma once
#include <Lib/Types.h>

/// @brief Check if character is of alpha-numerical type @param c Character to check @return Character is alpha-numeric
bool PICO_IsAlpha(char c);

/// @brief Check if character is a digit @param c Character to check @return Character is a digit
bool PICO_IsDigit(char c);

/// @brief Check if character is a hexadecimal digit @param c Character to check @return Character is hex
bool PICO_IsHexDigit(char c);

/// @brief Check if character is either of alpha-numerical type, or a digit @param c Character to check @return Character is alpha-numeric/hex
bool PICO_IsAlphaNum(char c);

/// @brief Check if character is a control character @param c Character to check @return Character is control
bool PICO_IsControl(char c);

/// @brief Check if character is a punctuation symbol @param c Character to check @return Character is punctual
bool PICO_IsPunctuation(char c);

/// @brief Check if character is a graphical character @param c Character to check @return Character is graphical
bool PICO_IsGraphical(char c);

/// @brief Check if alpha-numerical character is lowercase @param c Character to check @return Character is lowercase - returns false if character is not alpha-numerical
bool PICO_IsLower(char c);

/// @brief Check if alpha-numerical character is uppercase @param c Character to check @return Character is uppercase - returns false if character is not alpha-numerical
bool PICO_IsUpper(char c);

/// @brief Check if character is whitespace @param c Character to check @return Character is whitespace
bool PICO_IsSpace(char c);