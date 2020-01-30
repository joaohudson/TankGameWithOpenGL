#ifndef _TARGET_
#define _TARGET_

#include "Object.h"

class Target : public Object
{
	public:
		Target(Game *game, float x, float y, float z, float direction);
		~Target();
		void draw() const;
		void update(){}
		void destroy();
		
		static int getCount();
		static void resetCount();

	private:
	float direction;
	unsigned int texture;

};

#endif