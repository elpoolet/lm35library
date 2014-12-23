#ifndef LM35LIBRARY_H
#define LM35LIBRARY_H

// Obligatoire
#include <WProgram.h> 

class LM35 {
public:
	LM35();
	~LM35();
	void begin(int lm35pin);
	float lm35read();
};

#endif
