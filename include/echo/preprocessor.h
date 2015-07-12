#pragma once

#define ECHO_CONCATENATE_IMPL(S1, S2) S1##S2
#define ECHO_CONCATENATE(S1, S2) ECHO_CONCATENATE_IMPL(S1, S2)
#define ECHO_ANONYMOUS_VARIABLE(NAME) ECHO_CONCATENATE(NAME, __COUNTER__)
