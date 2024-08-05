#pragma once
#include <iostream>
#include <cstdint>

void isAccepted();
void init();
void update(const char* state, const char* key);
void end();
int solve(long var2);
void update_match(const char* matchsecret, const char* key, const char* state);