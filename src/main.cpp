#ifdef NATIVE_ENV
int main() {
    while (1);
    return 0;
}
#endif
 
#ifdef NEO_ENV
#include <SPI.h>
void setup() {}
void loop() {}
#endif