#pragma once

typedef char (*filter_func)(char);

char upper_filter(char);

char lower_filter(char);

char null_filter(char);
